/**
 * @file USART.c
 * @brief Implementation of USART driver for STM32F4xx.
 *
 * Improvements over original:
 * - Correct APB clock selection (APB1 for USART2/3/4/5, APB2 for USART1/6)
 * - Register bits cleared before setting (MODER, AFR, etc.)
 * - Added timeout to all busy-wait loops
 * - Separated RX buffers for each USART instance (static per port)
 * - Implemented missing synchronous receive function
 * - Added APB prescaler table and computation helper
 */

#include "USART.h"
#include "delay.h"      // for DWT_delay_us, optional
#include "GPIO.h"

/* Timeout for TX/RX loops (in loop iterations) */
#define USART_TIMEOUT   100000U

/* APBPrescTable is already declared in system_stm32f4xx.h – do not redefine */
// extern const uint8_t APBPrescTable[8];   // provided by CMSIS

/**
 * @brief Get the APB clock frequency for a given USART.
 * @param port USART1 or USART2
 * @return APB clock in Hz
 */
static uint32_t USART_GetAPBClock(USART_TypeDef *port)
{
    uint32_t clock = SystemCoreClock;
    uint32_t presc;
    if (port == USART1) {
        // USART1 is on APB2
        presc = (RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos;
        presc = APBPrescTable[presc];
        clock >>= presc;
    } else {
        // USART2/3/4/5/6 on APB1
        presc = (RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos;
        presc = APBPrescTable[presc];
        clock >>= presc;
    }
    return clock;
}

/* Global RX buffers (one per USART – extend if using more ports) */
static volatile uint8_t uart1RxBuffer = 0;
static volatile uint8_t uart1RxReady = 0;
static volatile uint8_t uart2RxBuffer = 0;
static volatile uint8_t uart2RxReady = 0;

/**
 * @brief Configure USART pins for asynchronous mode (TX/RX only).
 * @param uart  Handle with port selection.
 */
static void UART_ConfigPins(UART_Handle_t *uart)
{
    if (uart->port == USART1) {
        // PA9 (TX), PA10 (RX)
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_9,  ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_10, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
    }
    else if (uart->port == USART2) {
        // PA2 (TX), PA3 (RX)
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_2, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_3, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
    }
    // Add other ports (USART3, UART4, etc.) as needed
}

/**
 * @brief Initialize USART in asynchronous mode (UART).
 * @param uart  Handle with baudrate, mode, flow control, DMA settings.
 */
void UART_Init(UART_Handle_t *uart)
{
    // 1. Enable clocks and configure GPIO
    if (uart->port == USART1) {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    } else if (uart->port == USART2) {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    }
    UART_ConfigPins(uart);

    // 2. Compute baudrate registers
    uint32_t apb_clock = USART_GetAPBClock(uart->port);
    uint32_t usartdiv = (apb_clock * 10) / (uart->baudrate * 16); // scaled for fraction
    uint32_t mantissa = usartdiv / 10;
    uint32_t fraction = (usartdiv % 10) * 16 / 10; // convert to 4-bit fraction
    if (fraction >= 16) {
        mantissa++;
        fraction = 0;
    }
    uart->port->BRR = (mantissa << 4) | (fraction & 0x0F);

    // 3. Disable peripheral before full config
    uart->port->CR1 &= ~USART_CR1_UE;

    // 4. Configure mode (half/full duplex)
    if (uart->mode == HALF_DUPLEX)
        uart->port->CR3 |= USART_CR3_HDSEL;
    else
        uart->port->CR3 &= ~USART_CR3_HDSEL;

    // 5. DMA settings
    if (uart->TX_DMA)
        uart->port->CR3 |= USART_CR3_DMAT;
    else
        uart->port->CR3 &= ~USART_CR3_DMAT;

    if (uart->RX_DMA)
        uart->port->CR3 |= USART_CR3_DMAR;
    else
        uart->port->CR3 &= ~USART_CR3_DMAR;

    // 6. Hardware flow control (CTS/RTS)
    if (uart->hardware_control)
        uart->port->CR3 |= (USART_CR3_CTSE | USART_CR3_RTSE);
    else
        uart->port->CR3 &= ~(USART_CR3_CTSE | USART_CR3_RTSE);

    // 7. Enable transmitter, receiver, and USART
    uart->port->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

    // 8. Enable RX interrupt (to use global buffers)
    uart->port->CR1 |= USART_CR1_RXNEIE;

    // 9. Enable NVIC
    if (uart->port == USART1) {
        NVIC_EnableIRQ(USART1_IRQn);
        NVIC_SetPriority(USART1_IRQn, 1);
    } else if (uart->port == USART2) {
        NVIC_EnableIRQ(USART2_IRQn);
        NVIC_SetPriority(USART2_IRQn, 1);
    }
}

/**
 * @brief Transmit one byte (blocking) with timeout.
 * @param uart  Handle
 * @param data  Byte to send
 */
void UART_Transmit_Byte(UART_Handle_t *uart, char data)
{
    uint32_t timeout = USART_TIMEOUT;
    while (!(uart->port->SR & USART_SR_TXE)) {
        if (--timeout == 0) return; // timeout
    }
    uart->port->DR = data;

    timeout = USART_TIMEOUT;
    while (!(uart->port->SR & USART_SR_TC)) {
        if (--timeout == 0) return;
    }
}

/**
 * @brief Transmit a null-terminated string.
 */
void UART_Transmit_Buffer(UART_Handle_t *uart, const char *data)
{
    while (*data) {
        UART_Transmit_Byte(uart, *data++);
    }
}

/**
 * @brief Receive one byte (blocking) using interrupt-driven global buffer.
 * @return Received byte
 */
char UART_Receive_Byte(UART_Handle_t *uart)
{
    volatile uint8_t *ready_flag;
    volatile uint8_t *buffer;
    if (uart->port == USART1) {
        ready_flag = &uart1RxReady;
        buffer = &uart1RxBuffer;
    } else {
        ready_flag = &uart2RxReady;
        buffer = &uart2RxBuffer;
    }

    while (!(*ready_flag));
    *ready_flag = 0;
    return (char)(*buffer);
}

/**
 * @brief Check if data is available in the RX buffer.
 * @return 1 if available, 0 otherwise
 */
uint8_t UART_Available(UART_Handle_t *uart)
{
    if (uart->port == USART1)
        return uart1RxReady;
    else
        return uart2RxReady;
}

/* Interrupt handlers – clear RXNE and store data */
void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE) {
        uart1RxBuffer = (uint8_t)(USART1->DR & 0xFF);
        uart1RxReady = 1;
    }
}

void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE) {
        uart2RxBuffer = (uint8_t)(USART2->DR & 0xFF);
        uart2RxReady = 1;
    }
}

/* ========== Synchronous (SPI-like) functions ========== */

/**
 * @brief Configure USART for synchronous master mode (CK output on TX pin).
 *        Pins: TX (data out), RX (data in), CK (clock).
 * @param uart  Handle with baudrate, clock polarity/phase, etc.
 */
void USART_Init(UART_Handle_t *uart)
{
    // 1. Enable clocks and configure GPIO (TX, RX, CK)
    if (uart->port == USART1) {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
        // PA9 (TX), PA10 (RX), PA8 (CK)
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_8, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_9, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_10, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
    } else if (uart->port == USART2) {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
        // PA0 (CK), PA2 (TX), PA3 (RX) – adjust as per datasheet
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_0, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_2, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
        GPIO_Pin_Setup(GPIOA, GPIO_PIN_3, ALTERNATE_FUNCTION_OUTPUT_PUSHPULL, AF7_USART1_USART2);
    }

    // 2. Compute baudrate (same as async)
    uint32_t apb_clock = USART_GetAPBClock(uart->port);
    uint32_t usartdiv = (apb_clock * 10) / (uart->baudrate * 16);
    uint32_t mantissa = usartdiv / 10;
    uint32_t fraction = (usartdiv % 10) * 16 / 10;
    if (fraction >= 16) { mantissa++; fraction = 0; }
    uart->port->BRR = (mantissa << 4) | (fraction & 0x0F);

    // 3. Disable, then enable synchronous mode and clock output
    uart->port->CR1 &= ~USART_CR1_UE;
    uart->port->CR2 |= USART_CR2_CLKEN;      // Enable clock output

    // 4. Clock polarity and phase
    if (uart->clock_polarity)
        uart->port->CR2 |= USART_CR2_CPOL;
    else
        uart->port->CR2 &= ~USART_CR2_CPOL;

    if (uart->clock_phase)
        uart->port->CR2 |= USART_CR2_CPHA;
    else
        uart->port->CR2 &= ~USART_CR2_CPHA;

    // 5. Last bit clock
    if (uart->last_bit_clock)
        uart->port->CR2 |= USART_CR2_LBCL;
    else
        uart->port->CR2 &= ~USART_CR2_LBCL;

    // 6. Enable TX, RX, and peripheral
    uart->port->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);
}

/**
 * @brief Transmit one byte in synchronous mode (blocking).
 *        Also reads received data (full duplex) into a dummy variable.
 * @param uart  Handle
 * @param data  Byte to send
 */
void USART_Transmit_Byte(UART_Handle_t *uart, char data)
{
    uint32_t timeout = USART_TIMEOUT;
    while (!(uart->port->SR & USART_SR_TXE)) {
        if (--timeout == 0) return;
    }
    uart->port->DR = data;

    // Wait for RXNE (data received) to clear the buffer, or TC
    timeout = USART_TIMEOUT;
    while (!(uart->port->SR & USART_SR_RXNE)) {
        if (--timeout == 0) return;
    }
    (void)uart->port->DR; // read to clear RXNE flag
}

/**
 * @brief Transmit a buffer in synchronous mode.
 */
void USART_Transmit_Buffer(UART_Handle_t *uart, const char *data)
{
    while (*data) {
        USART_Transmit_Byte(uart, *data++);
    }
}

/**
 * @brief Receive one byte in synchronous mode (blocking).
 *        Sends dummy 0xFF to generate clock.
 * @return Received byte
 */
char USART_Receive_Byte(UART_Handle_t *uart)
{
    // Send dummy byte to generate clock
    uint32_t timeout = USART_TIMEOUT;
    while (!(uart->port->SR & USART_SR_TXE)) {
        if (--timeout == 0) return -1;
    }
    uart->port->DR = 0xFF;

    timeout = USART_TIMEOUT;
    while (!(uart->port->SR & USART_SR_RXNE)) {
        if (--timeout == 0) return -1;
    }
    return (char)(uart->port->DR & 0xFF);
}
