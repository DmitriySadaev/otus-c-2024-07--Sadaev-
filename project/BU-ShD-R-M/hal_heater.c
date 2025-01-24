/*! 
  \file
  \defgroup		hal_heater
  \brief		Файл исходного кода программы hal_heater.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций регулируемого нагревателя
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
*/

#include "hal_heater.h"

void hal_heater_init_struct(struct heater_data * heater, uint8_t voltage, uint8_t power_watt, uint8_t load_ohm, uint8_t heater_pin, volatile uint8_t * heater_port)
{
	heater->status = HEATER_OFF;
	heater->power_watt = power_watt;
	heater->load_ohm = load_ohm;
	heater->voltage = voltage;	
	heater->heater_pin = heater_pin;
	heater->heater_port = heater_port;
}

void hal_heater_init_ddr(struct heater_data * heater)
{
	* (heater->heater_port  -1)	|= (1 << heater->heater_pin); //из адреса регистра PORT получаем адрес регистра DDR
}

void hal_heater_pin_on(struct heater_data * heater)
{
	* heater->heater_port |= (1 << heater->heater_pin);
	heater->status = HEATER_ON;
}

void hal_heater_pin_off(struct heater_data * heater)
{
	* heater->heater_port &= ~(1 << heater->heater_pin);
	heater->status = HEATER_OFF;
}

uint8_t hal_heater_get_period_percent(struct heater_data * heater)
{
	uint8_t result = 0;
	
	result =(uint8_t)((float)heater->power_watt*heater->load_ohm*100/heater->voltage/heater->voltage);
	
	if (result > 99)
	{
		result = 99;
	}
	
	if (result < 1)
	{
		result = 1;
	}
	
	return result;
}

void hal_heater_init(struct heater_data * heater, uint8_t voltage, uint8_t power_watt, uint8_t load_ohm, uint8_t heater_pin, volatile uint8_t * heater_port)
{
	hal_heater_init_struct(heater, voltage, power_watt, load_ohm, heater_pin, heater_port);
	hal_heater_init_ddr(heater);
	hal_heater_pin_off(heater);
}
