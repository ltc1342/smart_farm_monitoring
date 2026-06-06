/*
 * DHT11.c
 */

#include "DHT11.h"
#include "delay.h"

// -----------------------------------------------
// private functions
// -----------------------------------------------
uint8_t DHT11_start(void);
static uint8_t DHT11_read_byte(uint8_t *data);
static uint8_t wait_for_state(uint8_t state, uint32_t timeout_us);
static GPIO_TypeDef *DHT11_PORT;
static uint16_t DHT11_PIN;

#define DHT11_WAIT_TIMEOUT_US 200U

void DHT11_Init(GPIO_TypeDef *port, uint8_t pin)
{
	DHT11_PORT = port;
	DHT11_PIN = pin;
}
static uint8_t wait_for_state(uint8_t state, uint32_t timeout_us)
{
	uint32_t start = DWT_micros();

	while (GPIO_ReadPin(DHT11_PORT, DHT11_PIN) != state)
	{
		if ((DWT_micros() - start) >= timeout_us)
		{
			return 0;
		}
	}

	return 1;
}

static uint8_t DHT11_read_bit(void) {
    wait_for_state(1, DHT11_WAIT_TIMEOUT_US);  // wait for high
    uint32_t high_start = DWT_micros();
    wait_for_state(0, DHT11_WAIT_TIMEOUT_US); // wait for low
    uint32_t high_duration = DWT_micros() - high_start;
    return (high_duration > 40) ? 1 : 0;  // Typical threshold: 28us = 0, 70us = 1
}
// -----------------------------------------------
// DHT Send start command
// -----------------------------------------------
uint8_t DHT11_start()
{
	// Start Request
	GPIO_Pin_Setup(DHT11_PORT, DHT11_PIN, GENERAL_PURPOSE_OUTPUT_OPENDRAIN_PULLUP, 0);
	GPIO_WritePin(DHT11_PORT, DHT11_PIN, 0);
	DWT_delay_ms(20);
	GPIO_WritePin(DHT11_PORT, DHT11_PIN, 1);
	//DWT_delay_us(30);

	// Check response
	GPIO_Pin_Setup(DHT11_PORT, DHT11_PIN, INPUT_FLOATING, 0); // Set pin as input to read response from DHT11

	if (!wait_for_state(0, DHT11_WAIT_TIMEOUT_US))
		return 0;
	if (!wait_for_state(1, DHT11_WAIT_TIMEOUT_US))
		return 0;
	if (!wait_for_state(0, DHT11_WAIT_TIMEOUT_US))
		return 0;

	return 1;
}

// -----------------------------------------------
// DHT Read byte
// -----------------------------------------------
static uint8_t DHT11_read_byte(uint8_t *data)
{

	uint8_t value = 0, j;
	for (j = 0; j < 8; ++j)
	{
		if (DHT11_read_bit())
		{
			value |= (1 << (7 - j));
		}
	}

	*data = value;
	return 1;
}

// -----------------------------------------------
// DHT Read all data
// -----------------------------------------------
uint8_t DHT11_read(DHT11_TypeDef *dht11)
{

	if (DHT11_start())
	{
		uint8_t hum_b1;
		uint8_t hum_b2;
		uint8_t tmp_b1;
		uint8_t tmp_b2;
		uint8_t ch_sum;

		if (!DHT11_read_byte(&hum_b1)) return 0;
		if (!DHT11_read_byte(&hum_b2)) return 0;
		if (!DHT11_read_byte(&tmp_b1)) return 0;
		if (!DHT11_read_byte(&tmp_b2)) return 0;
		if (!DHT11_read_byte(&ch_sum)) return 0;

		if (ch_sum == (uint8_t)(hum_b1 + hum_b2 + tmp_b1 + tmp_b2))
		{
			dht11->humidity = hum_b1;
			dht11->temperature = tmp_b1;
			return 1;
		}
	}

	return 0;
}
