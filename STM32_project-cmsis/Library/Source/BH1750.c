/*
 * BH1750.c
 *
 *  Created on: May 30, 2026
 *      Author: ChienLe
 */

#include "BH1750.h"
#include <stdint.h>
#include "delay.h"

static I2C_Config BH1750_I2C;

void BH1750_Init(I2C_TypeDef *I2C)
{
    BH1750_I2C.I2C = I2C;
    BH1750_I2C.mode = I2C_Fast_Mode;
    I2C_Master_Init(BH1750_I2C);

    // Power on and reset sensor
    BH1750_SendCommand(BH1750_POWER_ON);
    DWT_delay_ms(10);
    BH1750_SendCommand(BH1750_RESET);
    DWT_delay_ms(10);
}

void BH1750_SendCommand(uint8_t cmd)
{
    if(I2C_Master_Start(BH1750_I2C) != 0) return;
	if(I2C_Master_Address(BH1750_I2C, BH1750_ADDRESS, 0) != 0) return;
	if(I2C_Master_Send_Byte(BH1750_I2C, cmd) != 0) return;
    I2C_Master_Stop(BH1750_I2C);
}

uint16_t BH1750_ReadMeasurement(void)
{
    uint8_t buf[2] = {0,0};

    if(I2C_Master_Start(BH1750_I2C) != 0) return 0;
	if(I2C_Master_Address(BH1750_I2C, BH1750_ADDRESS, 1) != 0) return 0;

    // Read two bytes with proper ACK/NACK handling
    if(I2C_Master_Receive_Buffer(BH1750_I2C, buf, 2) != 0) {
        I2C_Master_Stop(BH1750_I2C);
        return 0;
    }
    I2C_Master_Stop(BH1750_I2C);

    uint16_t raw = ((uint16_t)buf[0] << 8) | (uint16_t)buf[1];
    return raw;
}

float BH1750_ReadLux(uint8_t mode)
{
    uint16_t raw = 0;
    BH1750_SendCommand(BH1750_POWER_ON);
    DWT_delay_ms(10);
    BH1750_SendCommand(mode);
    DWT_delay_ms(120);
    raw = BH1750_ReadMeasurement();
    if (raw == 0) {
        return -1.0f; // Indicate error
    }
    BH1750_SendCommand(BH1750_POWER_DOWN);
    float lux = (float)raw / 1.2f;
    return lux;
}
