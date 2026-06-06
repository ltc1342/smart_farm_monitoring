/*
 * GPIO.c
 *
 * Optimized for STM32F411xE – supports ports A, B, C, D, E, H.
 */

#include "GPIO.h"

/**
 * @brief Helper: convert GPIO_TypeDef* to port index (0=A, 1=B, 2=C, 3=D, 4=E, 7=H).
 *        Used for SYSCFG_EXTICR configuration.
 */
static uint8_t GPIO_GetPortIndex(GPIO_TypeDef* port)
{
    if(port == GPIOA) return 0;
    if(port == GPIOB) return 1;
    if(port == GPIOC) return 2;
    if(port == GPIOD) return 3;
    if(port == GPIOE) return 4;
    if(port == GPIOH) return 7;   // Port H index is 7
    return 0; // fallback
}

/**
 * @brief Configure a GPIO pin for any mode (input, output, alternate, analog).
 * @param port      GPIO port (GPIOA..GPIOH)
 * @param pin       Pin number (0-15)
 * @param function  Packed configuration byte (MODER, OTYPER, OSPEEDR, PUPDR)
 * @param alternate_function AF number (0-15) – used only in alternate function mode
 */
void GPIO_Pin_Setup(GPIO_TypeDef* port, uint8_t pin, uint8_t function, uint8_t alternate_function)
{
    // Enable clock for the selected port (STM32F411 specific)
    if(port == GPIOA)      RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if(port == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if(port == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if(port == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    else if(port == GPIOE) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    else if(port == GPIOH) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    // Note: GPIOF, GPIOG, GPIOI are not available on F411 – omitted.

    // Clear and set MODER (2 bits per pin)
    port->MODER   &= ~(0x3U << (2 * pin));
    port->MODER   |= (((function & 0xC0) >> 6) << (2 * pin));

    // Clear and set OTYPER (1 bit per pin)
    port->OTYPER  &= ~(0x1U << pin);
    port->OTYPER  |= (((function & 0x30) >> 4) << pin);

    // Clear and set OSPEEDR (2 bits per pin)
    port->OSPEEDR &= ~(0x3U << (2 * pin));
    port->OSPEEDR |= (((function & 0x0C) >> 2) << (2 * pin));

    // Clear and set PUPDR (2 bits per pin)
    port->PUPDR   &= ~(0x3U << (2 * pin));
    port->PUPDR   |= ((function & 0x03) << (2 * pin));

    // Configure alternate function registers (AFR) if needed (MODER = 10b)
    if ((function & 0xC0) == 0x80) // Alternate function mode
    {
        if(pin < 8)
        {
            port->AFR[0] &= ~(0xFU << (4 * pin));
            port->AFR[0] |= (alternate_function << (4 * pin));
        }
        else
        {
            port->AFR[1] &= ~(0xFU << (4 * (pin - 8)));
            port->AFR[1] |= (alternate_function << (4 * (pin - 8)));
        }
    }
}

/**
 * @brief Read the digital value of a GPIO pin.
 * @param port  GPIO port
 * @param pin   Pin number
 * @return      0 or 1
 */
uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin)
{
    return (uint8_t)((port->IDR >> pin) & 1U);
}

/**
 * @brief Write a digital value to a GPIO pin (atomic using BSRR).
 * @param port  GPIO port
 * @param pin   Pin number
 * @param value 0 or 1
 */
void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t value)
{
    if(value)
        port->BSRR = (1U << pin);         // Set bit
    else
        port->BSRR = (1U << (pin + 16));  // Reset bit
}

/**
 * @brief Configure an external interrupt on a GPIO pin.
 *        Automatically sets the pin as input (floating) and enables the correct NVIC line.
 * @param port          GPIO port
 * @param pin           Pin number (0-15)
 * @param edge_select   RISING_EDGE, FALLING_EDGE, or RISING_FALLING_EDGE
 */
void GPIO_Interrupt_Setup(GPIO_TypeDef* port, uint8_t pin, uint8_t edge_select)
{
    // 1. Configure the pin as input (floating by default – change if needed)
    GPIO_Pin_Setup(port, pin, INPUT_FLOATING, NONE);

    // 2. Enable SYSCFG clock (required for EXTI configuration)
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // 3. Connect the GPIO pin to the EXTI line via SYSCFG_EXTICR
    uint8_t exti_register = pin / 4;
    uint8_t exti_shift = (pin % 4) * 4;
    SYSCFG->EXTICR[exti_register] &= ~(0xFU << exti_shift);
    SYSCFG->EXTICR[exti_register] |= (GPIO_GetPortIndex(port) << exti_shift);

    // 4. Configure the edge trigger
    EXTI->IMR |= (1U << pin);   // Unmask interrupt line
    EXTI->RTSR &= ~(1U << pin);
    EXTI->FTSR &= ~(1U << pin);
    switch(edge_select)
    {
        case RISING_EDGE:
            EXTI->RTSR |= (1U << pin);
            break;
        case FALLING_EDGE:
            EXTI->FTSR |= (1U << pin);
            break;
        case RISING_FALLING_EDGE:
            EXTI->RTSR |= (1U << pin);
            EXTI->FTSR |= (1U << pin);
            break;
    }

    // 5. Enable NVIC interrupt for the correct EXTI line
    uint8_t irqn;
    if(pin <= 4)
        irqn = EXTI0_IRQn + pin;          // EXTI0..EXTI4 are separate
    else if(pin <= 9)
        irqn = EXTI9_5_IRQn;              // Pins 5-9 share one handler
    else
        irqn = EXTI15_10_IRQn;            // Pins 10-15 share one handler

    NVIC_SetPriority((IRQn_Type)irqn, 0);
    NVIC_EnableIRQ((IRQn_Type)irqn);
}
