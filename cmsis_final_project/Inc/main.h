/*
 * main.h
 *
 *  Created on: 09-Jul-2021
 *      Author: Kunal
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include "stm32f4xx.h"

/* Configuration Parameters External */
#define OLED_PORT 	I2C1
#define BH1750_PORT I2C1
#define DHT11_PORT 	GPIOB
#define DHT11_PIN 	5
#define ESP32_PORT 	USART2

/* OLED display parameters */
#define MAX_OLED_CHARS ((uint8_t)(SH1106_WIDTH / 7))  // 18 chars for 7px font

/* MCU Clock Configuration */
#define MCU_TARGET_SYSCLK_HZ  96000000ULL
#define MCU_HSE_HZ            25000000ULL
#define MCU_PLL_M_VALUE       25ULL
#define MCU_PLL_P_VALUE       2ULL

#endif /* MAIN_H_ */
