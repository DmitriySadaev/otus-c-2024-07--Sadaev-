/*! 
  \file
  \defgroup		hal_current_shunt
  \brief		Файл исходного кода программы hal_current_shunt.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций токового шунта
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
*/

#include "hal_current_shunt.h"

/* Схема включения шунта
 *							Vload
 *                        |
 *                       ---  R load
 *                   |   | |
 *                   |   | |
 *                   |   ---
 *				     |    |-------------------- to MC
 *                   |   ---  R shunt  
 *                   |   | |      
 *                   |   | |      
 *                   |   ---         
 *					 |	  |			 
 *			Iload	 V	 --- 
 *						 GND	    
 */


void hal_current_shunt_set_adc_pin(struct current_shunt_data * current_shunt, uint8_t adc_pin)
{
	current_shunt->adc_pin = adc_pin;
}

void hal_current_shunt_set_vref(struct current_shunt_data * current_shunt, uint16_t v_ref)
{
	current_shunt->v_ref = v_ref;
}

void hal_current_shunt_set_r_shunt_100ohm(struct current_shunt_data * current_shunt, uint16_t r_shunt_100ohm)
{
	current_shunt->r_shunt_100ohm = r_shunt_100ohm;
}

void hal_current_shunt_set_shift(struct current_shunt_data * current_shunt, int16_t shift_ma)
{
	current_shunt->shift_ma = shift_ma;
}

void hal_current_shunt_init(struct current_shunt_data * current_shunt, uint8_t adc_pin, uint16_t v_ref, uint16_t r_shunt_100ohm, int16_t shift_ma)
{
	avr_driver_adc_init(ADC_PRESCALER_DEFAULT, ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT, ADC_ADJUST_SELECTION_DEFAULT);
	hal_current_shunt_set_adc_pin(current_shunt, adc_pin);
	hal_current_shunt_set_vref(current_shunt, v_ref);
	hal_current_shunt_set_r_shunt_100ohm(current_shunt, r_shunt_100ohm);
	hal_current_shunt_set_shift(current_shunt, shift_ma);
}

uint16_t hal_current_shunt_adc_to_ma_conversion(struct current_shunt_data * current_shunt, uint16_t adc)
{
	float result = 0;
	result = (float)current_shunt->v_ref/(float)1023*(float)adc; //mv
	result = result/current_shunt->r_shunt_100ohm*100; //ma
	
	return (uint16_t)result;
}

void hal_current_shunt_set_adc(struct current_shunt_data * current_shunt)
{
	avr_driver_adc_select_channel_single_ended_input(current_shunt->adc_pin);
	current_shunt->current_adc = adc_driver_convert();
}

void hal_current_shunt_update(struct current_shunt_data * current_shunt)
{
	hal_current_shunt_set_adc(current_shunt);
	current_shunt->measured_current_ma = hal_current_shunt_adc_to_ma_conversion(current_shunt, current_shunt->current_adc);
}

int16_t hal_current_shunt_read_current(struct current_shunt_data * current_shunt)
{
	return (int16_t)current_shunt->measured_current_ma+current_shunt->shift_ma;
}