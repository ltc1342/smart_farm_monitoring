/**
 * @file ADC.c
 * @brief Implementation of single-channel ADC using GPIO.h for pin config.
 *
 * Features:
 * - Uses GPIO_Pin_Setup(..., ANALOG_INPUT, ...) for analog pin.
 * - ADC calibration, clock prescaler, and timeout protection.
 */

#include "ADC.h"
#include "stm32f4xx.h"
#include "GPIO.h"          // for GPIO_Pin_Setup and ANALOG_INPUT macro

/* ============================================================
 * USER CONFIGURATION
 * ============================================================ */
#define ADC_PORT        GPIOA
#define ADC_PIN         GPIO_PIN_4     // PA4 = ADC1_IN4
#define ADC_CHANNEL     4

/* ADC clock prescaler: 11 = PCLK2/8 (safe for 48MHz -> 6MHz) */
#define ADC_PRESCALER   0b11

/* Sampling time: 7 = 480 cycles (most accurate) */
#define ADC_SAMPLING_TIME   7

/* Timeout for EOC polling */
#define ADC_TIMEOUT     100000U

/* ============================================================
 * DERIVED MACROS
 * ============================================================ */
#define ADC_CHANNEL_MASK    (ADC_CHANNEL & 0x1F)

/* Select SMPR register based on channel number */
#if (ADC_CHANNEL < 10)
    #define ADC_SMPR_REG    ADC1->SMPR2
    #define ADC_SMPR_SHIFT  (ADC_CHANNEL * 3)
#else
    #define ADC_SMPR_REG    ADC1->SMPR1
    #define ADC_SMPR_SHIFT  ((ADC_CHANNEL - 10) * 3)
#endif

/* ============================================================
 * INITIALIZATION
 * ============================================================ */

/**
 * @brief Initialize ADC1 for single conversion on the selected channel.
 *
 * GPIO configuration is done via GPIO_Pin_Setup() with ANALOG_INPUT mode.
 */
void ADC_Init(void)
{
    /* ----- 1. Enable clocks ----- */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;   // GPIOA clock (needed even when using GPIO_Pin_Setup)
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;    // ADC1 clock

    /* ----- 2. Configure GPIO as analog input using GPIO library ----- */
    GPIO_Pin_Setup(ADC_PORT, ADC_PIN, ANALOG_INPUT, NONE);
    // ANALOG_INPUT = 0xC0 (MODER=11, PUPDR=00, OTYPER/OSPEEDR ignored)

    /* ----- 3. Configure ADC common registers (prescaler) ----- */
    ADC->CCR &= ~(ADC_CCR_ADCPRE_Msk | ADC_CCR_TSVREFE_Msk);
    ADC->CCR |= (ADC_PRESCALER << ADC_CCR_ADCPRE_Pos);

    /* ----- 4. Configure ADC1 ----- */
    // Disable ADC before config
    ADC1->CR2 &= ~ADC_CR2_ADON;

    // Reset configuration registers
    ADC1->CR1 = 0;
    ADC1->CR2 = 0;
    ADC1->SQR1 = 0;
    ADC1->SQR2 = 0;
    ADC1->SQR3 = 0;

    // Single conversion mode, right-aligned data
    ADC1->CR2 = ADC_CR2_ALIGN;   // ALIGN=0 (right), CONT=0

    // Enable ADC
    ADC1->CR2 |= ADC_CR2_ADON;

    // Stabilization delay
    for (volatile uint32_t i = 0; i < 1000; i++);

    /* ----- 5. Calibration (mandatory for STM32F4) ----- */
	#if !defined(STM32F411xE)
		ADC1->CR2 |= ADC_CR2_RSTCAL;
		while (ADC1->CR2 & ADC_CR2_RSTCAL);
		ADC1->CR2 |= ADC_CR2_CAL;
		while (ADC1->CR2 & ADC_CR2_CAL);
	#endif
    /* ----- 6. Sampling time and channel sequence ----- */
    ADC_SMPR_REG &= ~(0x7U << ADC_SMPR_SHIFT);
    ADC_SMPR_REG |= ((ADC_SAMPLING_TIME & 0x7) << ADC_SMPR_SHIFT);

    ADC1->SQR1 &= ~ADC_SQR1_L_Msk;          // 1 conversion
    ADC1->SQR3 = (ADC_CHANNEL_MASK & 0x1F); // Channel number
}

/* ============================================================
 * READ FUNCTION
 * ============================================================ */

/**
 * @brief Start conversion and read 12-bit result.
 * @return ADC value (0–4095) or 0xFFFF on timeout.
 */
uint16_t ADC_Read(void)
{
    uint32_t timeout = ADC_TIMEOUT;

    // Start conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;

    // Wait for End of Conversion
    while (!(ADC1->SR & ADC_SR_EOC)) {
        if (--timeout == 0) return 0xFFFF;
    }

    // Read result (clears EOC automatically)
    return (uint16_t)(ADC1->DR & 0x0FFF);
}
