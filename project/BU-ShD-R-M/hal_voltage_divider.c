/*! 
  \file
  \defgroup		hal_voltage_divider
  \brief		Файл исходного кода программы hal_voltage_divider.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций измерительного резистивного делителя напряжения.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
*/

/* Схема включения делителя
 *
 *			Input					
 *              ----------|
 *                       ---  R upper
 *                       | |
 *                       | |
 *          Output       ---
 *				----------|
 *                       ---  R lower   
 *                       | |      
 *                       | |      
 *                       ---         
 *						  |			 
 *						 --- 
 *						 GND	    
 */

#include "hal_voltage_divider.h"

void hal_voltage_divider_set_adc_pin(struct voltage_divider_data * v_sensor, uint8_t sensor_adc_pin)
{
	v_sensor->adc_pin = sensor_adc_pin;
}

void hal_voltage_divider_set_vref(struct voltage_divider_data * v_sensor, uint16_t v_ref)
{
	v_sensor->v_ref = v_ref;
}

void hal_voltage_divider_set_upper_resistance_ohm(struct voltage_divider_data * v_sensor, uint16_t sensor_resistance)
{
	v_sensor->upper_resistor_ohm = sensor_resistance;
}

void hal_voltage_divider_set_lower_resistance_ohm(struct voltage_divider_data * v_sensor, uint16_t sensor_resistance)
{
	v_sensor->lower_resistor_ohm = sensor_resistance;
}

void hal_voltage_divider_set_shift(struct voltage_divider_data * v_sensor, int16_t shift)
{
	v_sensor->shift_mv = shift;
}

void hal_voltage_divider_init(struct voltage_divider_data * v_sensor, uint8_t sensor_adc_pin)
{
	avr_driver_adc_init(ADC_PRESCALER_DEFAULT, ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT, ADC_ADJUST_SELECTION_DEFAULT);
	hal_voltage_divider_set_adc_pin(v_sensor, sensor_adc_pin);
	hal_voltage_divider_set_vref(v_sensor, V_REF_MV);
	hal_voltage_divider_set_upper_resistance_ohm(v_sensor, VOLTAGE_DIVIDER_UP_RESISTANCE_DEFAULT_OHM);
	hal_voltage_divider_set_lower_resistance_ohm(v_sensor, VOLTAGE_DIVIDER_LOW_RESISTANCE_DEFAULT_OHM);
	hal_voltage_divider_set_shift(v_sensor, 0);
}

uint16_t hal_voltage_divider_adc_to_mv_conversion(struct voltage_divider_data * v_sensor, uint16_t adc)
{
	float result = 0;
	result = (float)v_sensor->v_ref/(float)1023*(float)adc;
	result = result*((float)v_sensor->upper_resistor_ohm+(float)v_sensor->lower_resistor_ohm)/((float)v_sensor->lower_resistor_ohm);
	return (uint16_t)result;
}

void hal_voltage_divider_set_adc(struct voltage_divider_data * v_sensor)
{
	avr_driver_adc_select_channel_single_ended_input(v_sensor->adc_pin);
	v_sensor->current_adc = adc_driver_convert();
}

void hal_voltage_divider_update(struct voltage_divider_data * v_sensor)
{
	hal_voltage_divider_set_adc(v_sensor);
	v_sensor->measured_voltage_mv = hal_voltage_divider_adc_to_mv_conversion(v_sensor, v_sensor->current_adc);
}

int16_t hal_voltage_divider_read_voltage(struct voltage_divider_data * v_sensor)
{
	return (int16_t)v_sensor->measured_voltage_mv+v_sensor->shift_mv;
}