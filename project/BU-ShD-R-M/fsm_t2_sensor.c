/*! 
  \file
  \defgroup		fsm_t2_sensor
  \brief		Файл исходного кода программы fsm_t2_sensor.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) датчика температуры Т2 с характристикой PT100, Pt300, Cu100, Cu300
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_t2_sensor.h"

int16_t t2_measurement_array[FSM_T2_SENSOR_ARRAY_SIZE];
uint8_t fsm_t2_sensor_status;

void fsm_t2_temp_sensor_clear_array(void)
{
	for (uint8_t i = 0; i < FSM_T2_SENSOR_ARRAY_SIZE; i++)
	{
		t2_measurement_array[i] = 0;
	}
}

void fsm_t2_temp_sensor_init(struct bu_shd_r_m_data * bu_shd_r_m, struct pt100_pt300_data * t_sensor, uint8_t pt100_pt300_mode, uint8_t pt300_control_pin, volatile uint8_t * pt300_control_port, uint8_t adc_pin, uint16_t v_ref)
{
	bu_shd_r_m->t2_temperature_grad10 = 0;
	fsm_t2_sensor_status = 0;
	fsm_t2_temp_sensor_clear_array();
	hal_pt100_pt300_init(t_sensor, pt100_pt300_mode, pt300_control_pin, pt300_control_port, adc_pin, v_ref);
	virtual_timers_timer_reset(T2_TIMER);
}

uint8_t fsm_t2_temp_sensor_is_break(void)
{
	uint8_t counter = 0;
	for (uint8_t j = 0; j < FSM_T2_SENSOR_ARRAY_SIZE; j++)
	{
		if (t2_measurement_array[j] == PT100_PT300_BREAK)
		{
			counter++;
		}
	}
	if (counter >= FSM_T2_SENSOR_ERRORS_COUNT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t fsm_t2_temp_sensor_is_short(void)
{
	uint8_t counter = 0;
	for (uint8_t j = 0; j < FSM_T2_SENSOR_ARRAY_SIZE; j++)
	{
		if (t2_measurement_array[j] == PT100_PT300_SHORT)
		{
			counter++;
		}
	}
	if (counter >= FSM_T2_SENSOR_ERRORS_COUNT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void fsm_t2_temp_sensor_process(struct bu_shd_r_m_data * bu_shd_r_m, struct pt100_pt300_data * t_sensor)
{
	if (virtual_timers_timer_get(T2_TIMER) >= FSM_T2_SENSOR_MEASUREMENT_PERIOD_MS)
	{
		
		if (fsm_t2_sensor_status >= FSM_T2_SENSOR_ARRAY_SIZE)
		{
			fsm_t2_sensor_status = 0;
		}
		hal_pt100_pt300_update(t_sensor);
		t2_measurement_array[fsm_t2_sensor_status] = hal_pt100_pt300_read_temperature(t_sensor);
		if (fsm_t2_sensor_status == 0)
		{
			if(!(fsm_t2_temp_sensor_is_break() || fsm_t2_temp_sensor_is_short()))
			{
				int16_t buffer = 0;
				for (uint8_t j = 0; j < FSM_T2_SENSOR_ARRAY_SIZE; j++)
				{
					buffer = buffer+t2_measurement_array[j];
				}
				bu_shd_r_m->t2_temperature_grad10 = buffer/FSM_T2_SENSOR_ARRAY_SIZE;
			}
			if(fsm_t2_temp_sensor_is_break())
			{
				bu_shd_r_m->t2_temperature_grad10 = PT100_PT300_BREAK;
				if (!(bu_shd_r_m->error_flags & (1 << ERROR_T2_BREAK)))
				{
					fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
					fsm_messages_send_broadcast_message(MSG_T2_BREAK);
					bu_shd_r_m->error_flags |= (1 << ERROR_T2_BREAK);
				}
			}
			
			if(fsm_t2_temp_sensor_is_short())
			{
				bu_shd_r_m->t2_temperature_grad10 = PT100_PT300_SHORT;
				if (!(bu_shd_r_m->error_flags & (1 << ERROR_T2_SHORT)))
				{
					fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
					fsm_messages_send_broadcast_message(MSG_T2_SHORT);
					bu_shd_r_m->error_flags |= (1 << ERROR_T2_SHORT);
				}
			}

			if (bu_shd_r_m->t2_temperature_grad10 > bu_shd_r_m->t2_temperature_setting_grad10)
			{
				if (!(bu_shd_r_m->error_flags & (1 << ERROR_T2_OVERHEAT)))
				{
					fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
					fsm_messages_send_broadcast_message(MSG_T2_OVERHEAT);
					bu_shd_r_m->error_flags |= (1 << ERROR_T2_OVERHEAT);
				}
			}	
		}
		fsm_t2_sensor_status++;
		virtual_timers_timer_reset(T2_TIMER);
	}
}