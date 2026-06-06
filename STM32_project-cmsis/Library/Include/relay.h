/*
 * relay.h
 *
 *  Created on: Jun 3, 2026
 *      Author: ChienLe
 */

#ifndef RELAY_H_
#define RELAY_H_

#include <stdint.h>
#include <stm32f4xx.h>

void Relay_Init(GPIO_TypeDef* port, uint8_t pin);
void Relay_SetPump(uint8_t state);  // 1: ON, 0: OFF (low level trigger)
void Relay_SetMist(uint8_t state);
uint8_t Relay_GetPumpState(void);
uint8_t Relay_GetMistState(void);
void Relay_TogglePump(void);
void Relay_ToggleMist(void);

#endif /* RELAY_H_ */
