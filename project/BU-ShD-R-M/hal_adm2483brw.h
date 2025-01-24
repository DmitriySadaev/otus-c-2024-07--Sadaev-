/*!
\file
\defgroup hal_adm2483brw
\brief Заголовочный файл hal_adm2483brw.h

*/

#ifndef HAL_ADM2483BRW_H_
#define HAL_ADM2483BRW_H_

#include <stdint.h>
#include <avr/io.h>
#include "avr_driver_uart.h"

struct adm2483brw_data
{
	uint8_t n_uart;
	uint32_t baudrate;
	uint8_t speed_mode;
	uint8_t op_mode;
	uint8_t n_stop_bits;
	uint8_t n_characters;
	uint8_t parity;
	uint8_t transmitter_enable_pin;
	volatile uint8_t * transmitter_enable_port;
};

void hal_adm2483brw_init(struct adm2483brw_data * adm2483brw, uint8_t n_uart, uint32_t baudrate, uint8_t speed_mode, uint8_t op_mode, uint8_t n_stop_bits, uint8_t n_characters, uint8_t parity, uint8_t transmitter_enable_pin, volatile uint8_t * transmitter_enable_port, uint32_t f_cpu);
void hal_adm2483brw_transmitt(struct adm2483brw_data * adm2483brw, uint8_t data_to_trasmitt);
uint8_t hal_adm2483brw_receive(struct adm2483brw_data * adm2483brw);

#endif /* HAL_ADM2483BRW_H_ */