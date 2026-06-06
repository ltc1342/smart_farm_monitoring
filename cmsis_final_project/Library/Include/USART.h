/**
 * @file USART.h
 * @brief Lightweight CMSIS USART driver for STM32F4xx.
 *
 * Supported Features:
 * - Asynchronous mode (full/half duplex, hardware flow control, DMA)
 * - Synchronous master mode (SPI-like, with CK output)
 *
 * @note For synchronous mode, use USART_Init(), USART_Transmit_Byte(), etc.
 *       For asynchronous mode, use UART_Init(), UART_Transmit_Byte(), etc.
 */

#ifndef USART_USART_H_
#define USART_USART_H_

#include <stdbool.h>
#include "stm32f4xx.h"

/* USART mode selection */
typedef enum {
    FULL_DUPLEX = 0,
    HALF_DUPLEX = 1
} UART_Mode;

/**
 * @brief USART/UART handle structure.
 * @param port            USART1, USART2, etc.
 * @param mode            FULL_DUPLEX or HALF_DUPLEX (async only)
 * @param baudrate        Desired baud rate (e.g., 115200)
 * @param hardware_control Enable CTS/RTS flow control (async only)
 * @param TX_DMA          Enable DMA for TX
 * @param RX_DMA          Enable DMA for RX
 * @param clock_polarity  Synchronous: CPOL (0=idle low, 1=idle high)
 * @param clock_phase     Synchronous: CPHA (0=first edge capture, 1=second edge)
 * @param last_bit_clock  Synchronous: LBCL (0=no clock on last bit, 1=clock on last bit)
 */
typedef struct {
    USART_TypeDef *port;
    UART_Mode mode;
    uint32_t baudrate;
    bool hardware_control;
    bool TX_DMA;
    bool RX_DMA;
    uint8_t clock_polarity;
    uint8_t clock_phase;
    uint8_t last_bit_clock;
} UART_Handle_t;

/* ========== Asynchronous API (UART) ========== */
void UART_Init(UART_Handle_t *uart);
void UART_Transmit_Byte(UART_Handle_t *uart, char data);
void UART_Transmit_Buffer(UART_Handle_t *uart, const char *data);
char UART_Receive_Byte(UART_Handle_t *uart);          // blocking, uses global buffer per USART
uint8_t UART_Available(UART_Handle_t *uart);          // check if data available

/* ========== Synchronous API (USART as SPI master) ========== */
void USART_Init(UART_Handle_t *uart);
void USART_Transmit_Byte(UART_Handle_t *uart, char data);
void USART_Transmit_Buffer(UART_Handle_t *uart, const char *data);
char USART_Receive_Byte(UART_Handle_t *uart);         // blocking read

#endif /* USART_USART_H_ */
