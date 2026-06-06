/*
 * BH1750.h
 *
 *  Created on: May 30, 2026
 *      Author: ChienLe
 */

#ifndef BH1750_BH1750_H_
#define BH1750_BH1750_H_

#include <stdint.h>
#include "I2C.h"

// 7-bit device address for BH1750 (shifted left by 1 for 8-bit I2C addressing)
#define BH1750_ADDRESS_LOW 0x23 //ADDR pin low (GND)
#define BH1750_ADDRESS_HIGH 0x5C //ADDR pin high (VCC)

#define BH1750_ADDRESS          BH1750_ADDRESS_LOW

// BH1750 commands
#define BH1750_POWER_ON        0x01
#define BH1750_POWER_DOWN      0x00
#define BH1750_RESET           0x07
#define BH1750_CONT_H_RES_MODE 0x10
#define BH1750_ONE_TIME_H_RES  0x20

// Initialize BH1750 using specified I2C peripheral (e.g., I2C1)
void BH1750_Init(I2C_TypeDef *I2C);

// Send a single command to BH1750
void BH1750_SendCommand(uint8_t cmd);

// Read current measurement (2 bytes) into `lux` (device must be in measurement mode)
uint16_t BH1750_ReadMeasurement(void);

// Read light intensity in lux based on specified mode (e.g., continuous high-res)
float BH1750_ReadLux(uint8_t mode);

#endif /* BH1750_BH1750_H_ */
