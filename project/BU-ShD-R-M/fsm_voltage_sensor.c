<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_voltage_sensor
  \brief		Файл исходного кода программы fsm_voltage_sensor.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) датчика напряжения
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_voltage_sensor.h"

uint16_t voltage_measurement_array[FSM_VOLTAGE_SENSOR_ARRAY_SIZE];
uint8_t fsm_voltage_sensor_status;

void fsm_voltage_sensor_clear_array(void)
{
	for (uint8_t i = 0; i < FSM_VOLTAGE_SENSOR_ARRAY_SIZE; i++)
	{
		voltage_measurement_array[i] = 0;
	}
}

void fsm_voltage_sensor_init(uint16_t * voltage, struct voltage_divider_data * v_sensor, uint8_t sensor_adc_pin, uint16_t v_ref, int16_t shift)
{
	fsm_voltage_sensor_status = 0;
	* voltage = 0;
	hal_voltage_divider_init(v_sensor, sensor_adc_pin);
	hal_voltage_divider_set_vref(v_sensor, v_ref);
	hal_voltage_divider_set_shift(v_sensor, shift);	
	fsm_voltage_sensor_clear_array();
	virtual_timers_timer_reset(VOLTAGE_SENSOR_TIMER);
}

void fsm_voltage_sensor_process(uint16_t * voltage, struct voltage_divider_data * v_sensor)
{
	if (virtual_timers_timer_get(VOLTAGE_SENSOR_TIMER) >= FSM_VOLTAGE_SENSOR_MEASUREMENT_PERIOD_MS)
	{
		if (fsm_voltage_sensor_status >= FSM_VOLTAGE_SENSOR_ARRAY_SIZE)
		{
			fsm_voltage_sensor_status = 0;
		}
		hal_voltage_divider_update(v_sensor);
		voltage_measurement_array[fsm_voltage_sensor_status] = (uint16_t)hal_voltage_divider_read_voltage(v_sensor)/10;
		if (fsm_voltage_sensor_status == 0)
		{
			uint16_t buffer = 0;
			for (uint8_t j = 0; j < FSM_VOLTAGE_SENSOR_ARRAY_SIZE; j++)
			{					
				buffer = buffer+voltage_measurement_array[j];
			}
			if (v_sensor->shift_mv >= buffer/FSM_VOLTAGE_SENSOR_ARRAY_SIZE)
			{
				* voltage = 0;
			}
			else
			{
				* voltage = buffer/FSM_VOLTAGE_SENSOR_ARRAY_SIZE;
			}
		}
		fsm_voltage_sensor_status++;

		virtual_timers_timer_reset(VOLTAGE_SENSOR_TIMER);
	}
}
=======
/*! 
  \file
  \defgroup		fsm_voltage_sensor
  \brief		Файл исходного кода программы fsm_voltage_sensor.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) датчика напряжения
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_voltage_sensor.h"

uint16_t voltage_measurement_array[FSM_VOLTAGE_SENSOR_ARRAY_SIZE];
uint8_t fsm_voltage_sensor_status;

void fsm_voltage_sensor_clear_array(void)
{
	for (uint8_t i = 0; i < FSM_VOLTAGE_SENSOR_ARRAY_SIZE; i++)
	{
		voltage_measurement_array[i] = 0;
	}
}

void fsm_voltage_sensor_init(uint16_t * voltage, struct voltage_divider_data * v_sensor, uint8_t sensor_adc_pin, uint16_t v_ref, int16_t shift)
{
	fsm_voltage_sensor_status = 0;
	* voltage = 0;
	hal_voltage_divider_init(v_sensor, sensor_adc_pin);
	hal_voltage_divider_set_vref(v_sensor, v_ref);
	hal_voltage_divider_set_shift(v_sensor, shift);	
	fsm_voltage_sensor_clear_array();
	virtual_timers_timer_reset(VOLTAGE_SENSOR_TIMER);
}

void fsm_voltage_sensor_process(uint16_t * voltage, struct voltage_divider_data * v_sensor)
{
	if (virtual_timers_timer_get(VOLTAGE_SENSOR_TIMER) >= FSM_VOLTAGE_SENSOR_MEASUREMENT_PERIOD_MS)
	{
		if (fsm_voltage_sensor_status >= FSM_VOLTAGE_SENSOR_ARRAY_SIZE)
		{
			fsm_voltage_sensor_status = 0;
		}
		hal_voltage_divider_update(v_sensor);
		voltage_measurement_array[fsm_voltage_sensor_status] = (uint16_t)hal_voltage_divider_read_voltage(v_sensor)/10;
		if (fsm_voltage_sensor_status == 0)
		{
			uint16_t buffer = 0;
			for (uint8_t j = 0; j < FSM_VOLTAGE_SENSOR_ARRAY_SIZE; j++)
			{					
				buffer = buffer+voltage_measurement_array[j];
			}
			if (v_sensor->shift_mv >= buffer/FSM_VOLTAGE_SENSOR_ARRAY_SIZE)
			{
				* voltage = 0;
			}
			else
			{
				* voltage = buffer/FSM_VOLTAGE_SENSOR_ARRAY_SIZE;
			}
		}
		fsm_voltage_sensor_status++;

		virtual_timers_timer_reset(VOLTAGE_SENSOR_TIMER);
	}
}
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
