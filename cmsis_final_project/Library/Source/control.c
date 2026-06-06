/*
 * control.c
 *
 *  Created on: Jun 3, 2026
 *      Author: ChienLe
 */

#include "control.h"
#include "relay.h"
#include "dht11.h"
#include "bh1750.h"
#include "ADC.h"
#include "USART.h"
#include "delay.h"
#include <string.h>
#include <stdlib.h>
#include <main.h>

static ControlMode currentMode = MODE_AUTO;
static uint32_t lastAutoCheck = 0;
static uint32_t pumpHysteresisTimer = 0;
static uint32_t mistHysteresisTimer = 0;

// Default  Threshold
#define SOIL_DRY_THRESHOLD   40   // Down 40% then turn on pump
#define SOIL_WET_THRESHOLD   70   // Up 70% then turn off pump
#define AIR_DRY_THRESHOLD    50   // Down 50% then turn on mist
#define AIR_WET_THRESHOLD    70   // Up 70% then turn off mist
#define HYSTERESIS_DELAY_MS  5000 // 5s

// Save variable global
extern DHT11_TypeDef dht11;
extern float lux_f;
extern uint16_t soilMoisture;
extern UART_Handle_t ESP32_UART;

void Control_Init(void)
{
    currentMode = MODE_AUTO;
    Relay_SetPump(0);
    Relay_SetMist(0);
    lastAutoCheck = 0;
}

void Control_SetMode(ControlMode mode)
{
    currentMode = mode;
    // Notification current Mode across UART
    if(currentMode == MODE_AUTO)
    	UART_Transmit_Buffer(&ESP32_UART, "MODE_AUTO\r\n");
    else
    	UART_Transmit_Buffer(&ESP32_UART, "MODE_MANUAL\r\n");
}

ControlMode Control_GetMode(void)
{
    return currentMode;
}

void Control_AutoUpdate(void)
{
    static uint8_t pumpReq = 0, mistReq = 0;
    //uint32_t now = 0; // You can use SysTick count or millis()

    // Update pump status based on soil moisture
    if(soilMoisture < SOIL_DRY_THRESHOLD)
    {
        if(pumpReq == 0)
            pumpReq = 1;
        pumpHysteresisTimer = 0;
    }
    else if(soilMoisture > SOIL_WET_THRESHOLD)
    {
        if(pumpReq == 1)
            pumpReq = 0;
        pumpHysteresisTimer = 0;
    }
    else
    {
    	// Keep it as is; you can increase the timer if you want time hysteresis.
    }

    // Update mist status based on air humidity.
    if(dht11.humidity < AIR_DRY_THRESHOLD)
    {
        if(mistReq == 0)
            mistReq = 1;
        mistHysteresisTimer = 0;
    }
    else if(dht11.humidity > AIR_WET_THRESHOLD)
    {
        if(mistReq == 1)
            mistReq = 0;
        mistHysteresisTimer = 0;
    }

    Relay_SetPump(pumpReq);
    Relay_SetMist(mistReq);
}

void Control_ProcessCommand(char* cmd)
{
	// Process commands from ESP32
	// Format: "PUMP_ON", "PUMP_OFF", "MIST_ON", "MIST_OFF", "AUTO_ENABLE", "AUTO_DISABLE"
    if(strcmp(cmd, "PUMP_ON") == 0)
    {
        if(currentMode == MODE_MANUAL)
            Relay_SetPump(1);
        UART_Transmit_Buffer(&ESP32_UART, "ACK:PUMP_ON\r\n");
    }
    else if(strcmp(cmd, "PUMP_OFF") == 0)
    {
        if(currentMode == MODE_MANUAL)
            Relay_SetPump(0);
        UART_Transmit_Buffer(&ESP32_UART, "ACK:PUMP_OFF\r\n");
    }
    else if(strcmp(cmd, "MIST_ON") == 0)
    {
        if(currentMode == MODE_MANUAL)
            Relay_SetMist(1);
        UART_Transmit_Buffer(&ESP32_UART, "ACK:MIST_ON\r\n");
    }
    else if(strcmp(cmd, "MIST_OFF") == 0)
    {
        if(currentMode == MODE_MANUAL)
            Relay_SetMist(0);
        UART_Transmit_Buffer(&ESP32_UART, "ACK:MIST_OFF\r\n");
    }
    else if(strcmp(cmd, "AUTO_ENABLE") == 0)
    {
        Control_SetMode(MODE_AUTO);
        UART_Transmit_Buffer(&ESP32_UART, "ACK:AUTO_ENABLE\r\n");
    }
    else if(strcmp(cmd, "AUTO_DISABLE") == 0)
    {
        Control_SetMode(MODE_MANUAL);
        UART_Transmit_Buffer(&ESP32_UART, "ACK:AUTO_DISABLE\r\n");
    }
    else
    {
        UART_Transmit_Buffer(&ESP32_UART, "ACK:UNKNOWN\r\n");
    }
}

void Control_Process(void)
{
    static uint32_t lastRun = 0;
    uint32_t now = DWT_millis(); // millis()

    // Checking commands from UART
    if(UART_Available(&ESP32_UART))
    {
        char cmd[32];
        uint8_t idx = 0;
        memset(cmd, 0, 32);
        while(UART_Available(&ESP32_UART) && idx < 31)
        {
            cmd[idx++] = UART_Receive_Byte(&ESP32_UART);
        }
        cmd[idx] = '\0';
        // Delete \r\n if present
        for(uint8_t i=0; i<idx; i++)
        {
            if(cmd[i] == '\r' || cmd[i] == '\n')
            {
                cmd[i] = '\0';
                break;
            }
        }
        Control_ProcessCommand(cmd);
    }

    // Automatic control every 2 seconds (in AUTO mode)
    if(currentMode == MODE_AUTO)
    {
        if(now - lastRun >= 2000)
        {
            Control_AutoUpdate();
            lastRun = now;
        }
    }
}
