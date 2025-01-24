/*! 
  \file
  \defgroup		fsm_current_sensor
  \brief		Файл исходного кода программы fsm_current_sensor.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) датчика тока
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_current_sensor.h"

int16_t current_measurement_array[FSM_CURRENT_SENSOR_ARRAY_SIZE];
uint8_t fsm_current_sensor_status;

void fsm_current_sensor_clear_array(void)
{
	for (uint8_t i = 0; i < FSM_CURRENT_SENSOR_ARRAY_SIZE; i++)
	{
		current_measurement_array[i] = 0;
	}
}

void fsm_current_sensor_init(int16_t * current, struct current_shunt_data * current_shunt, uint8_t adc_pin, uint16_t v_ref, uint16_t r_shunt_100ohm, int16_t shift_ma)
{
	fsm_current_sensor_status = 0;
	* current = 0;
	hal_current_shunt_init(current_shunt, adc_pin, v_ref, r_shunt_100ohm, shift_ma);
	fsm_current_sensor_clear_array();
	virtual_timers_timer_reset(CURRENT_SENSOR_TIMER);
}

void fsm_current_sensor_process(int16_t * current, struct current_shunt_data * current_shunt)
{
	if (virtual_timers_timer_get(CURRENT_SENSOR_TIMER) >= FSM_CURRENT_SENSOR_MEASUREMENT_PERIOD_MS)
	{
		if (fsm_current_sensor_status >= FSM_CURRENT_SENSOR_ARRAY_SIZE)
		{
			fsm_current_sensor_status = 0;
		}
		hal_current_shunt_update(current_shunt);
		current_measurement_array[fsm_current_sensor_status] = (int16_t)hal_current_shunt_read_current(current_shunt)/10;
		if (fsm_current_sensor_status == 0)
		{
			int16_t buffer = 0;
			for (uint8_t j = 0; j < FSM_CURRENT_SENSOR_ARRAY_SIZE; j++)
			{
				buffer = buffer+current_measurement_array[j];
			}
			if (current_shunt->shift_ma/10 >= buffer/FSM_CURRENT_SENSOR_ARRAY_SIZE)
			{
				* current = 0;
			}
			else
			{
				* current = buffer/FSM_CURRENT_SENSOR_ARRAY_SIZE;
			}
		}
		fsm_current_sensor_status++;

		virtual_timers_timer_reset(CURRENT_SENSOR_TIMER);
	}
}
