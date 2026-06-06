/*
 * relay.c
 *
 *  Created on: Jun 3, 2026
 *      Author: ChienLe
 */

// relay.c
#include "relay.h"
#include "GPIO.h"


#define PUMP_PIN    0  // PB0
#define MIST_PIN    1  // PB1
#define RELAY_PORT  GPIOB

static uint8_t pumpState = 0;
static uint8_t mistState = 0;

void Relay_Init(GPIO_TypeDef* port, uint8_t pin)
{
    GPIO_Pin_Setup(port, pin, GENERAL_PURPOSE_OUTPUT_PUSHPULL, NONE);
    // Default OFF (HIGH because low level trigger)
    port->BSRR = (1 << (pin + 16));
}

void Relay_SetPump(uint8_t state)
{
    pumpState = state ? 1 : 0;
    if(pumpState) {
    	RELAY_PORT->BSRR &= ~(1 << PUMP_PIN);
        RELAY_PORT->BSRR = (1 << (PUMP_PIN + 16));  // LOW -> ON
    } else
        RELAY_PORT->BSRR = (1 << PUMP_PIN);         // HIGH -> OFF
}

void Relay_SetMist(uint8_t state)
{
    mistState = state ? 1 : 0;
    if(mistState)
        RELAY_PORT->BSRR = (1 << (MIST_PIN + 16));
    else
        RELAY_PORT->BSRR = (1 << MIST_PIN);
}

uint8_t Relay_GetPumpState(void) { return pumpState; }
uint8_t Relay_GetMistState(void) { return mistState; }

void Relay_TogglePump(void) { Relay_SetPump(!pumpState); }
void Relay_ToggleMist(void) { Relay_SetMist(!mistState); }
