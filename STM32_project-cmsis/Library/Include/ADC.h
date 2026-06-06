/**
 * @file ADC.h
 * @brief Single-channel ADC driver for STM32F4xx.
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void ADC_Init(void);
uint16_t ADC_Read(void);

#endif /* ADC_H_ */
