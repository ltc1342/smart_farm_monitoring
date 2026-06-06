/*
 * I2C.c
 *
 * Optimized I2C master implementation for STM32F411.
 * Supports I2C1, I2C2, I2C3 with Fast (400kHz) and Normal (100kHz) modes.
 * Assumes SYSCLK = 48 MHz (can be changed via SYSCLK_FREQ macro).
 */

#include "I2C.h"
#include "delay.h"      // DWT_delay_us

#define I2C_TIMEOUT     100000U
#define SYSCLK_FREQ     48000000U   // 48 MHz (adjust if different)

/**
 * @brief Compute CR2, CCR, TRISE values based on desired mode and SYSCLK.
 * @param mode    I2C_Fast_Mode or I2C_Normal_Mode
 * @param freq    APB1 clock frequency (usually SYSCLK)
 */
static void I2C_CalculateClockRegisters(I2C_TypeDef *I2Cx, bool mode, uint32_t freq)
{
    uint32_t tmp = 0;

    // CR2: Peripheral clock frequency in MHz
    I2Cx->CR2 = (freq / 1000000U) & 0x3F;

    if (mode == I2C_Fast_Mode)
    {
        // Fast mode (400 kHz)
        tmp = (freq + 400000U * 2) / (400000U * 2); // CCR = freq / (400k * 2)
        I2Cx->CCR = (1 << 15) | (tmp & 0xFFF);      // FS = 1, duty cycle (default = 0: 2x t_low = t_high)
        // TRISE: 300ns + 1 = (freq * 0.3us) + 1
        I2Cx->TRISE = (freq / 1000000U) * 300 / 1000 + 1;
    }
    else
    {
        // Normal mode (100 kHz)
        tmp = freq / (100000U * 2);
        I2Cx->CCR = tmp & 0xFFF;                    // FS = 0
        I2Cx->TRISE = (freq / 1000000U) + 1;
    }
}

/**
 * @brief Initialize I2C peripheral as master.
 * @param I2C    Configuration (I2Cx and mode)
 */
void I2C_Master_Init(I2C_Config I2C)
{
    // Enable clocks and configure GPIO pins (using AF values from GPIO.h)
    if (I2C.I2C == I2C1) // PB6 (SCL1), PB7 (SDA1)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        GPIO_Pin_Setup(GPIOB, GPIO_PIN_6, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, AF4_I2C1_I2C2);
        GPIO_Pin_Setup(GPIOB, GPIO_PIN_7, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, AF4_I2C1_I2C2);
    }
    else if (I2C.I2C == I2C2) // PB10 (SCL2), PB3 (SDA2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
        GPIO_Pin_Setup(GPIOB, GPIO_PIN_10, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, AF4_I2C1_I2C2);
        GPIO_Pin_Setup(GPIOB, GPIO_PIN_3 , ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, AF4_I2C1_I2C2);
    }
    else if (I2C.I2C == I2C3) // PA8 (SCL3), PB4 (SDA3)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_8, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, AF9_I2C3);
        GPIO_Pin_Setup(GPIOB, GPIO_PIN_4, ALTERNATE_FUNCTION_OUTPUT_OPENDRAIN_PULLUP, AF9_I2C3);
    }

    // Disable I2C peripheral before configuration
    I2C.I2C->CR1 &= ~I2C_CR1_PE;

    // Reset the peripheral (SWRST)
    I2C.I2C->CR1 |= I2C_CR1_SWRST;
    I2C.I2C->CR1 &= ~I2C_CR1_SWRST;

    // Configure clock registers
    I2C_CalculateClockRegisters(I2C.I2C, I2C.mode, SYSCLK_FREQ);

    // Enable No-Stretch mode (optional, but used in original)
    I2C.I2C->CR1 |= I2C_CR1_NOSTRETCH;

    // Enable the peripheral
    I2C.I2C->CR1 |= I2C_CR1_PE;
}

/**
 * @brief Send I2C START condition.
 * @return 0 on success, -1 on timeout.
 */
int I2C_Master_Start(I2C_Config I2C)
{
    uint32_t timeout = I2C_TIMEOUT;
    I2C.I2C->CR1 |= I2C_CR1_START;
    while (!(I2C.I2C->SR1 & I2C_SR1_SB))
    {
        if (--timeout == 0) return -1;
    }
    return 0;
}

/**
 * @brief Send I2C address with read/write flag.
 * @param address     7-bit device address
 * @param read_write  0 = write, 1 = read
 * @return 0 on success, -1 on NACK or timeout.
 */
int I2C_Master_Address(I2C_Config I2C, uint8_t address, uint8_t read_write)
{
    uint32_t timeout = I2C_TIMEOUT;
    I2C.I2C->DR = (address << 1) | (read_write & 0x01);

    // Wait for ADDR or AF (NACK)
    while (!(I2C.I2C->SR1 & I2C_SR1_ADDR) && !(I2C.I2C->SR1 & I2C_SR1_AF))
    {
        if (--timeout == 0)
        {
            I2C_Master_Stop(I2C);
            I2C.I2C->SR1 &= ~I2C_SR1_AF;   // Clear AF
            return -1;
        }
    }

    if (I2C.I2C->SR1 & I2C_SR1_AF)
    {
        I2C_Master_Stop(I2C);
        I2C.I2C->SR1 &= ~I2C_SR1_AF;
        return -1;
    }

    // Clear ADDR flag by reading SR1 then SR2
    (void)I2C.I2C->SR1;
    (void)I2C.I2C->SR2;

    return 0;
}

/**
 * @brief Send one data byte.
 * @return 0 on success, -1 on timeout.
 */
int I2C_Master_Send_Byte(I2C_Config I2C, uint8_t data)
{
    uint32_t timeout = I2C_TIMEOUT;
    while (!(I2C.I2C->SR1 & I2C_SR1_TXE))
    {
        if (--timeout == 0) return -1;
    }
    I2C.I2C->DR = data;

    timeout = I2C_TIMEOUT;
    while (!(I2C.I2C->SR1 & I2C_SR1_TXE))
    {
        if (--timeout == 0) return -1;
    }
    return 0;
}

/**
 * @brief Send multiple bytes.
 * @return 0 on success, -1 on timeout.
 */
int I2C_Master_Send_Buffer(I2C_Config I2C, uint8_t *data, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (I2C_Master_Send_Byte(I2C, data[i]) != 0)
            return -1;
    }
    return 0;
}

/**
 * @brief Receive one byte (with ACK management).
 * @details This function is intended for multi‑byte reception where
 *          the caller has already set the appropriate ACK/NACK state.
 *          For single‑byte reads, use I2C_Master_Read_Register which handles NACK correctly.
 * @return received byte (0-255) or -1 on timeout.
 */
int I2C_Master_Receive_Byte(I2C_Config I2C)
{
    uint32_t timeout = I2C_TIMEOUT;
    while (!(I2C.I2C->SR1 & I2C_SR1_RXNE))
    {
        if (--timeout == 0) return -1;
    }
    return (int)I2C.I2C->DR;
}

/**
 * @brief Receive multiple bytes.
 * @param data   Buffer to store received bytes.
 * @param length Number of bytes to receive.
 * @return 0 on success, -1 on timeout.
 */
int I2C_Master_Receive_Buffer(I2C_Config I2C, uint8_t *data, int length)
{
    if (length <= 0) return -1;

    // For single byte: NACK before the byte arrives
    if (length == 1)
    {
        I2C_Master_NACK(I2C);
        int byte = I2C_Master_Receive_Byte(I2C);
        if (byte < 0) return -1;
        data[0] = (uint8_t)byte;
        return 0;
    }

    // For multiple bytes: ACK for all but the last
    for (int i = 0; i < length; i++)
    {
        if (i == (length - 1))
            I2C_Master_NACK(I2C);   // NACK before last byte
        else
            I2C_Master_ACK(I2C);

        int byte = I2C_Master_Receive_Byte(I2C);
        if (byte < 0) return -1;
        data[i] = (uint8_t)byte;
    }

    // Leave ACK enabled for future transfers
    I2C_Master_ACK(I2C);
    return 0;
}

void I2C_Master_NACK(I2C_Config I2C)
{
    I2C.I2C->CR1 &= ~I2C_CR1_ACK;
}

void I2C_Master_ACK(I2C_Config I2C)
{
    I2C.I2C->CR1 |= I2C_CR1_ACK;
}

void I2C_Master_Stop(I2C_Config I2C)
{
    I2C.I2C->CR1 |= I2C_CR1_STOP;
}

/******************************************************************************
 * High-level register access functions
 ******************************************************************************/

/**
 * @brief Write a single byte to a device register.
 */
void I2C_Master_Write_Register(I2C_Config I2C, uint8_t device_address, uint8_t reg_address, uint8_t data)
{
    if (I2C_Master_Start(I2C) != 0) return;
    if (I2C_Master_Address(I2C, device_address, 0) != 0) return;
    if (I2C_Master_Send_Byte(I2C, reg_address) != 0) return;
    if (I2C_Master_Send_Byte(I2C, data) != 0) return;
    I2C_Master_Stop(I2C);
}

/**
 * @brief Read a single byte from a device register.
 * @return register value (0-255) or -1 on error.
 */
int I2C_Master_Read_Register(I2C_Config I2C, uint8_t device_address, uint8_t reg_address)
{
    // Write the register address
    if (I2C_Master_Start(I2C) != 0) return -1;
    if (I2C_Master_Address(I2C, device_address, 0) != 0) return -1;
    if (I2C_Master_Send_Byte(I2C, reg_address) != 0) return -1;

    // Repeated start for reading
    if (I2C_Master_Start(I2C) != 0) return -1;
    if (I2C_Master_Address(I2C, device_address, 1) != 0) return -1;

    // For a single byte read: set NACK before the byte arrives
    I2C_Master_NACK(I2C);
    int byte = I2C_Master_Receive_Byte(I2C);
    I2C_Master_Stop(I2C);

    // Re-enable ACK for future transfers
    I2C_Master_ACK(I2C);
    return byte;
}

/**
 * @brief Set or clear specific bits in a register.
 * @param SET_RESET_FLAG  1 to set bits, 0 to clear them.
 * @param bits            Bits to modify.
 */
void I2C_Master_Write_Register_bits(I2C_Config I2C, uint8_t device_address, uint8_t reg_address,
                                    uint8_t SET_RESET_FLAG, uint8_t bits)
{
    int reg = I2C_Master_Read_Register(I2C, device_address, reg_address);
    if (reg < 0) return;

    if (SET_RESET_FLAG)
        reg |= bits;
    else
        reg &= ~bits;

    I2C_Master_Write_Register(I2C, device_address, reg_address, (uint8_t)reg);
}

/**
 * @brief Read a single bit from a register.
 * @param bit  Bit mask (e.g., 1 << 3)
 * @return 1 if bit is set, 0 if cleared, -1 on error.
 */
int I2C_Master_Read_Register_bit(I2C_Config I2C, uint8_t device_address, uint8_t reg_address, uint8_t bit)
{
    int reg = I2C_Master_Read_Register(I2C, device_address, reg_address);
    if (reg < 0) return -1;
    return (reg & bit) ? 1 : 0;
}
