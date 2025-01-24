/*! 
  \file
  \defgroup		hal_adm2483brw
  \brief		Файл исходного кода программы hal_adm2483brw.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
	Исходный код представляет из себя слой аппаратных абстракций приемопередатчика интерфейса RS-485 
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  ADM2483BRW   
*/

#include "hal_adm2483brw.h"

void hal_adm2483brw_init_struct(struct adm2483brw_data * adm2483brw, uint8_t n_uart, uint32_t baudrate, uint8_t speed_mode, uint8_t op_mode, uint8_t n_stop_bits, uint8_t n_characters, uint8_t parity, uint8_t transmitter_enable_pin, volatile uint8_t * transmitter_enable_port)
{
	
	adm2483brw->n_uart = n_uart;
	adm2483brw->baudrate = baudrate;
	adm2483brw->speed_mode = speed_mode;
	adm2483brw->op_mode = op_mode;
	adm2483brw->n_stop_bits = n_stop_bits;
	adm2483brw->n_characters = n_characters;
	adm2483brw->parity = parity;
	adm2483brw->transmitter_enable_pin = transmitter_enable_pin;
	adm2483brw->transmitter_enable_port = transmitter_enable_port;
}

void hal_adm2483brw_init_enable_ddr(struct adm2483brw_data * adm2483brw)
{
	*(adm2483brw->transmitter_enable_port  -1)	|= (1 << adm2483brw->transmitter_enable_pin); //из адреса регистра PORT получаем адрес регистра DDR	
}

void hal_adm2483brw_enable_pin_on(struct adm2483brw_data * adm2483brw)
{
	*adm2483brw->transmitter_enable_port |= (1 << adm2483brw->transmitter_enable_pin);
}

void hal_adm2483brw_enable_pin_off(struct adm2483brw_data * adm2483brw)
{
	*adm2483brw->transmitter_enable_port &= ~(1 << adm2483brw->transmitter_enable_pin);	
}

void hal_adm2483brw_init(struct adm2483brw_data * adm2483brw, uint8_t n_uart, uint32_t baudrate, uint8_t speed_mode, uint8_t op_mode, uint8_t n_stop_bits, uint8_t n_characters, uint8_t parity, uint8_t transmitter_enable_pin, volatile uint8_t * transmitter_enable_port, uint32_t f_cpu)
{
	hal_adm2483brw_init_struct(adm2483brw, n_uart, baudrate, speed_mode, op_mode, n_stop_bits, n_characters, parity, transmitter_enable_pin, transmitter_enable_port);
	hal_adm2483brw_init_enable_ddr(adm2483brw);
	hal_adm2483brw_enable_pin_off(adm2483brw);
	avr_driver_uart_init(n_uart, f_cpu, speed_mode, baudrate, op_mode, n_stop_bits, n_characters, 0, parity, AVR_DRIVER_UART_INTERRUPTS_ON);
}

void hal_adm2483brw_transmitt(struct adm2483brw_data * adm2483brw, uint8_t data_to_trasmitt)
{
	hal_adm2483brw_enable_pin_on(adm2483brw);
	avr_driver_uart_transmitt(adm2483brw->n_uart, data_to_trasmitt);   //не забыть выключить enable pin когда передача завершится
}

uint8_t hal_adm2483brw_receive(struct adm2483brw_data * adm2483brw)
{
	uint8_t result = 0;
	
	hal_adm2483brw_enable_pin_off(adm2483brw);
	result = avr_driver_uart_receive(adm2483brw->n_uart);
	
	return result;
}