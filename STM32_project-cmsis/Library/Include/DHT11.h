/*
 * DHT11.h
 *
 * Updated on: 31.10.2020
 * Updated on: 28.06.2020
 * Created on: 24.03.2019
 *     Author: Admin
 */

#ifndef DHT11_H_
#define DHT11_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include "GPIO.h"

// -----------------------------------------------
// public struct
// -----------------------------------------------
typedef struct {
	uint8_t humidity;
	uint8_t temperature;
} DHT11_TypeDef;
// -----------------------------------------------

// -----------------------------------------------
// public functions
// -----------------------------------------------
void DHT11_Init(GPIO_TypeDef *port, uint8_t pin);
uint8_t DHT11_read(DHT11_TypeDef *dht11);
// -----------------------------------------------

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DHT11_H_ */
