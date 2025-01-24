/*! 
  \file
  \defgroup		hal_status_led
  \brief		Файл исходного кода программы hal_status_led.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций статусного светодиода.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
*/

#include "hal_status_led.h"

void hal_status_led_init_struct(struct status_led_data * status_led, uint8_t status_led_pin, volatile uint8_t * status_led_port)
{
	status_led->status_led_pin = status_led_pin;
	status_led->status_led_port = status_led_port;
}

void hal_status_led_init_ddr(struct status_led_data * status_led)
{
	* (status_led->status_led_port  -1)	|= (1 << status_led->status_led_pin); //из адреса регистра PORT получаем адрес регистра DDR

}

void hal_status_led_turn_off(struct status_led_data * status_led)
{
	* status_led->status_led_port &= ~(1 << status_led->status_led_pin);	
}

void hal_status_led_turn_on(struct status_led_data * status_led)
{
	* status_led->status_led_port |= (1 << status_led->status_led_pin);
}

uint8_t hal_status_led_is_on(struct status_led_data * status_led)
{
	if ((* status_led->status_led_port) & (1 << status_led->status_led_pin))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void hal_status_led_init(struct status_led_data * status_led, uint8_t status_led_pin, volatile uint8_t * status_led_port)
{
	hal_status_led_init_struct(status_led, status_led_pin, status_led_port);
	hal_status_led_init_ddr(status_led);
	hal_status_led_turn_off(status_led);
}

void hal_status_led_toggle(struct status_led_data * status_led)
{
	if (hal_status_led_is_on(status_led))
	{
		hal_status_led_turn_off(status_led);
	}
	else
	{
		hal_status_led_turn_on(status_led);
	}
}