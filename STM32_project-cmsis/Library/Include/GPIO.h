/*
 * GPIO.h
 *
 * Optimized and commented library for STM32F4xx GPIO handling.
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "stm32f4xx.h"

/* Pin definitions */
#define GPIO_PIN_0   0
#define GPIO_PIN_1   1
#define GPIO_PIN_2   2
#define GPIO_PIN_3   3
#define GPIO_PIN_4   4
#define GPIO_PIN_5   5
#define GPIO_PIN_6   6
#define GPIO_PIN_7   7
#define GPIO_PIN_8   8
#define GPIO_PIN_9   9
#define GPIO_PIN_10 10
#define GPIO_PIN_11 11
#define GPIO_PIN_12 12
#define GPIO_PIN_13 13
#define GPIO_PIN_14 14
#define GPIO_PIN_15 15
#define NONE 0

/* ========== Output modes (function byte format) ==========
   Byte: bits 7-6 = MODER, bits 5-4 = OTYPER, bits 3-2 = OSPEEDR, bits 1-0 = PUPDR
   Example: GENERAL_PURPOSE_OUTPUT_PUSHPULL = 0x4C
             -> MODER=01 (GP output), OTYPER=00 (push-pull), OSPEEDR=11 (high speed), PUPDR=00 (no pull)
*/
#define GENERAL_PURPOSE_OUTPUT_PUSHPULL              0x4C
#define GENERAL_PURPOSE_OUTPUT_PUSHPULL_PULLUP       0x4D
#define GENERAL_PURPOSE_OUTPUT_PUSHPULL_PULLDW       0x4E
#define GENERAL_PURPOSE_OUTPUT_OPENDRAIN             0x5C
#define GENERAL_PURPOSE_OUTPUT_OPENDRAIN_PULLUP      0x5D
#define GENERAL_PURPOSE_OUTPUT_OPENDRAIN_PULLDW      0x5E

#define ALTERNATE_FUNCTION_OUTPUT_PUSHPULL           0x8C
#define ALTERNATE_FUNCTION_OUTPUT_PUSHPULL_PULLUP    0x8D
#define ALTERNATE_FUNCTION_OUTPUT_PUSHPULL_PULLDW    0x8E
#define ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN          0x9C
#define ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP   0x9D
#define ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLDW   0x9E

/* Input modes */
#define INPUT_FLOATING  0x00
#define INPUT_PULLUP    0x01
#define INPUT_PULLDW    0x02

/* Analog mode */
#define ANALOG_INPUT    0xC0

/* ========== Alternate function numbers (AF0 – AF15) ==========
   For detailed mapping, refer to the STM32F4xx datasheet.
   Below are common examples – adjust according to your MCU.
*/
#define AF0_MCO         0
#define AF1_TIM1        1
#define AF2_TIM3_TIM4   2
#define AF3_TIM9_TIM11  3
#define AF4_I2C1_I2C2   4
#define AF5_SPI1_SPI2   5
#define AF6_SPI3        6
#define AF7_USART1_USART2 7
#define AF8_SPI4        8
#define AF9_I2C3        9
#define AF10_USART6     10
#define AF11            11
#define AF12_SDIO       12
#define AF13            13
#define AF14            14
#define AF15            15

/* Interrupt edge selection */
#define RISING_EDGE             0
#define FALLING_EDGE            1
#define RISING_FALLING_EDGE     2

/* Function prototypes */
void GPIO_Pin_Setup(GPIO_TypeDef* port, uint8_t pin, uint8_t function, uint8_t alternate_function);
uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);
void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t value);
void GPIO_Interrupt_Setup(GPIO_TypeDef* port, uint8_t pin, uint8_t edge_select);

#endif /* GPIO_GPIO_H_ */
