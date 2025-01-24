<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_inner_temp_sensor
  \brief		Файл исходного кода программы fsm_inner_temp_sensor.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) датчика температуры, измеряющего внутреннюю температуры БУ-ШД
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_inner_temp_sensor.h"

int16_t inner_temp_measurement_array[FSM_INNER_SENSOR_ARRAY_SIZE];
uint8_t fsm_inner_sensor_status;

void fsm_inner_temp_sensor_clear_array(void)
{
	for (uint8_t i = 0; i < FSM_INNER_SENSOR_ARRAY_SIZE; i++)
	{
		inner_temp_measurement_array[i] = 0;
	}
}

void fsm_inner_temp_sensor_init(int16_t * inner_temperature_grad10, struct kty82_data * t_sensor, uint8_t sensor_type, uint8_t sensor_adc_pin)
{
	inner_temperature_grad10 = 0;
	fsm_inner_sensor_status = 0;
	fsm_inner_temp_sensor_clear_array();
	hal_kty82_init(t_sensor, sensor_type, sensor_adc_pin);
	virtual_timers_timer_reset(INNER_SENSOR_TIMER);
}

uint8_t fsm_inner_temp_sensor_is_break(void)
{
	uint8_t counter = 0;
	for (uint8_t j = 0; j < FSM_INNER_SENSOR_ARRAY_SIZE; j++)
	{
		if (inner_temp_measurement_array[j] == KTY82_BREAK)
		{
			counter++;
		}
	}
	if (counter >= FSM_INNER_SENSOR_ERRORS_COUNT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t fsm_inner_temp_sensor_is_short(void)
{
	uint8_t counter = 0;
	for (uint8_t j = 0; j < FSM_INNER_SENSOR_ARRAY_SIZE; j++)
	{
		if (inner_temp_measurement_array[j] == KTY82_SHORT)
		{
			counter++;
		}
	}
	if (counter >= FSM_INNER_SENSOR_ERRORS_COUNT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void fsm_inner_temp_sensor_process(int16_t * inner_temperature_grad10, struct kty82_data * t_sensor)
{
	if (virtual_timers_timer_get(INNER_SENSOR_TIMER) >= FSM_INNER_SENSOR_MEASUREMENT_PERIOD_MS)
	{		
		
		if (fsm_inner_sensor_status >= FSM_INNER_SENSOR_ARRAY_SIZE)
		{
			fsm_inner_sensor_status = 0;
		}
		hal_kty82_update(t_sensor);
		inner_temp_measurement_array[fsm_inner_sensor_status] = hal_kty_read_temperature(t_sensor);
		if (fsm_inner_sensor_status == 0)
		{
			if(fsm_inner_temp_sensor_is_break())
			{
				* inner_temperature_grad10 = KTY82_BREAK;
				fsm_messages_send_broadcast_message(MSG_INNER_T_SENSOR_BREAK);
			}
			if(fsm_inner_temp_sensor_is_short())
			{
				* inner_temperature_grad10 = KTY82_SHORT;
				fsm_messages_send_broadcast_message(MSG_INNER_T_SENSOR_SHORT);
			}
			if(!(fsm_inner_temp_sensor_is_break() || fsm_inner_temp_sensor_is_short()))
			{
			int16_t buffer = 0;
			for (uint8_t j = 0; j < FSM_INNER_SENSOR_ARRAY_SIZE; j++)
			{
				buffer = buffer+inner_temp_measurement_array[j];
			}
			* inner_temperature_grad10 = buffer/FSM_INNER_SENSOR_ARRAY_SIZE;
			}
		}
		fsm_inner_sensor_status++;
		virtual_timers_timer_reset(INNER_SENSOR_TIMER);
	}
}

=======
/*! 
  \file
  \defgroup		fsm_inner_temp_sensor
  \brief		Файл исходного кода программы fsm_inner_temp_sensor.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) датчика температуры, измеряющего внутреннюю температуры БУ-ШД
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_inner_temp_sensor.h"

int16_t inner_temp_measurement_array[FSM_INNER_SENSOR_ARRAY_SIZE];
uint8_t fsm_inner_sensor_status;

void fsm_inner_temp_sensor_clear_array(void)
{
	for (uint8_t i = 0; i < FSM_INNER_SENSOR_ARRAY_SIZE; i++)
	{
		inner_temp_measurement_array[i] = 0;
	}
}

void fsm_inner_temp_sensor_init(int16_t * inner_temperature_grad10, struct kty82_data * t_sensor, uint8_t sensor_type, uint8_t sensor_adc_pin)
{
	inner_temperature_grad10 = 0;
	fsm_inner_sensor_status = 0;
	fsm_inner_temp_sensor_clear_array();
	hal_kty82_init(t_sensor, sensor_type, sensor_adc_pin);
	virtual_timers_timer_reset(INNER_SENSOR_TIMER);
}

uint8_t fsm_inner_temp_sensor_is_break(void)
{
	uint8_t counter = 0;
	for (uint8_t j = 0; j < FSM_INNER_SENSOR_ARRAY_SIZE; j++)
	{
		if (inner_temp_measurement_array[j] == KTY82_BREAK)
		{
			counter++;
		}
	}
	if (counter >= FSM_INNER_SENSOR_ERRORS_COUNT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t fsm_inner_temp_sensor_is_short(void)
{
	uint8_t counter = 0;
	for (uint8_t j = 0; j < FSM_INNER_SENSOR_ARRAY_SIZE; j++)
	{
		if (inner_temp_measurement_array[j] == KTY82_SHORT)
		{
			counter++;
		}
	}
	if (counter >= FSM_INNER_SENSOR_ERRORS_COUNT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void fsm_inner_temp_sensor_process(int16_t * inner_temperature_grad10, struct kty82_data * t_sensor)
{
	if (virtual_timers_timer_get(INNER_SENSOR_TIMER) >= FSM_INNER_SENSOR_MEASUREMENT_PERIOD_MS)
	{		
		
		if (fsm_inner_sensor_status >= FSM_INNER_SENSOR_ARRAY_SIZE)
		{
			fsm_inner_sensor_status = 0;
		}
		hal_kty82_update(t_sensor);
		inner_temp_measurement_array[fsm_inner_sensor_status] = hal_kty_read_temperature(t_sensor);
		if (fsm_inner_sensor_status == 0)
		{
			if(fsm_inner_temp_sensor_is_break())
			{
				* inner_temperature_grad10 = KTY82_BREAK;
				fsm_messages_send_broadcast_message(MSG_INNER_T_SENSOR_BREAK);
			}
			if(fsm_inner_temp_sensor_is_short())
			{
				* inner_temperature_grad10 = KTY82_SHORT;
				fsm_messages_send_broadcast_message(MSG_INNER_T_SENSOR_SHORT);
			}
			if(!(fsm_inner_temp_sensor_is_break() || fsm_inner_temp_sensor_is_short()))
			{
			int16_t buffer = 0;
			for (uint8_t j = 0; j < FSM_INNER_SENSOR_ARRAY_SIZE; j++)
			{
				buffer = buffer+inner_temp_measurement_array[j];
			}
			* inner_temperature_grad10 = buffer/FSM_INNER_SENSOR_ARRAY_SIZE;
			}
		}
		fsm_inner_sensor_status++;
		virtual_timers_timer_reset(INNER_SENSOR_TIMER);
	}
}

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
