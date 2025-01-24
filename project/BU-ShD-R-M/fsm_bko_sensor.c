/*! 
  \file
  \defgroup		fsm_bko_sensor
  \brief		Файл исходного кода программы fsm_bko_sensor.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) датчика температуры блока криооткачки
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_bko_sensor.h"

int16_t bko_measurement_array[FSM_BKO_SENSOR_ARRAY_SIZE];
uint8_t fsm_bko_sensor_status;

void fsm_bko_temp_sensor_clear_array(void)
{
	for (uint8_t i = 0; i < FSM_BKO_SENSOR_ARRAY_SIZE; i++)
	{
		bko_measurement_array[i] = 0;
	}
}

void fsm_bko_temp_sensor_init(struct bu_shd_r_m_data * bu_shd_r_m, struct t_100p_data * t_sensor,  uint8_t adc_pin, uint16_t v_ref, uint8_t control_pin, volatile  uint8_t * control_port, int16_t temperature_shift)
{
	bu_shd_r_m->bko1_temperature_grad10 = 0;
	fsm_bko_sensor_status = 0;
	fsm_bko_temp_sensor_clear_array();
	hal_t_100p_init(t_sensor, adc_pin, v_ref, control_pin, control_port);
	hal_t_100p_set_temperature_shift(t_sensor, temperature_shift);
	virtual_timers_timer_reset(BKO_SENSOR_TIMER);
}

uint8_t fsm_bko_temp_sensor_is_break(void)
{
	uint8_t counter = 0;
	for (uint8_t j = 0; j < FSM_BKO_SENSOR_ARRAY_SIZE; j++)
	{
		if (bko_measurement_array[j] == T_100P_BREAK)
		{
			counter++;
		}
	}
	if (counter >= FSM_BKO_SENSOR_ERRORS_COUNT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t fsm_bko_temp_sensor_is_short(void)
{
	uint8_t counter = 0; 
	for (uint8_t j = 0; j < FSM_BKO_SENSOR_ARRAY_SIZE; j++)
	{
		if (bko_measurement_array[j] == T_100P_SHORT)
		{
			counter++;
		}
	}
	if (counter >= FSM_BKO_SENSOR_ERRORS_COUNT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t fsm_bko_check_it3_is_not_in_short_range(struct bu_shd_r_m_data * bu_shd_r_m)
{
	uint8_t result = FALSE;
	
	do 
	{
		if (!(bu_shd_r_m->it3_dot_position == 1))												{break;}
		if (!(bu_shd_r_m->it3_temperature > FSM_BKO_IT3_TEMPERATURE00_BKO_SENSOR_SHORT_IGNORE)) {break;}
			
		result = TRUE;	
	} while (0);
	
	if (bu_shd_r_m->it3_temperature == 0)
	{
		result = TRUE;	
	}
	
	 return result;
}

void fsm_bko_temp_sensor_process(struct bu_shd_r_m_data * bu_shd_r_m, struct t_100p_data * t_sensor)
{
	if (virtual_timers_timer_get(BKO_SENSOR_TIMER) >= FSM_BKO_SENSOR_MEASUREMENT_PERIOD_MS)
	{
		
		if (fsm_bko_sensor_status >= FSM_BKO_SENSOR_ARRAY_SIZE)
		{
			fsm_bko_sensor_status = 0;
		}
		hal_t_100p_update(t_sensor);
		bko_measurement_array[fsm_bko_sensor_status] = hal_t_100p_read_temperature(t_sensor);
		if (fsm_bko_sensor_status == 0)
		{
			if(!(fsm_bko_temp_sensor_is_break() || fsm_bko_temp_sensor_is_short()))
			{
				int32_t buffer = 0;
				uint8_t t_100p_error_counter = 0;
				bu_shd_r_m->error_flags &= ~((uint32_t)1 << ERROR_BKO_SENSOR_BREAK);
				bu_shd_r_m->error_flags &= ~((uint32_t)1 << ERROR_BKO_SENSOR_SHORT);
				bu_shd_r_m->error_flags &= ~((uint32_t)1 << ERROR_BKO_SENSOR_T_LOWER_73_K);
				for (uint8_t j = 0; j < FSM_BKO_SENSOR_ARRAY_SIZE; j++)
				{
					if ((bko_measurement_array[j] != T_100P_BREAK) && (bko_measurement_array[j] != T_100P_SHORT))
					{
						buffer = buffer+bko_measurement_array[j];
					}
					else
					{
						t_100p_error_counter++;
					}
				}
				bu_shd_r_m->bko1_temperature_grad10 = (int16_t)(buffer/(FSM_BKO_SENSOR_ARRAY_SIZE - t_100p_error_counter) + CELSIUM_TO_KELVIN_CONVERSION_SHIFT_GRAD0);
			}
			if(fsm_bko_temp_sensor_is_break() && bu_shd_r_m->bko_sensor_errors_enabled)
			{
				bu_shd_r_m->bko1_temperature_grad10 = T_100P_BREAK;
				bu_shd_r_m->error_flags |= ((uint32_t)1 << ERROR_BKO_SENSOR_BREAK);
				fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
				fsm_messages_send_broadcast_message(MSG_BKO_SENSOR_BREAK);	
			}
			if(fsm_bko_temp_sensor_is_short() && fsm_bko_check_it3_is_not_in_short_range(bu_shd_r_m) && bu_shd_r_m->bko_sensor_errors_enabled)
			{
				bu_shd_r_m->bko1_temperature_grad10 = T_100P_SHORT;
				bu_shd_r_m->error_flags |= ((uint32_t)1 << ERROR_BKO_SENSOR_SHORT);
				fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
				fsm_messages_send_broadcast_message(MSG_BKO_SENSOR_SHORT);		
			}
			if ((fsm_bko_temp_sensor_is_break() || fsm_bko_temp_sensor_is_short()) && !(bu_shd_r_m->bko_sensor_errors_enabled))
			{
				bu_shd_r_m->error_flags |= ((uint32_t)1 << ERROR_BKO_SENSOR_T_LOWER_73_K);
			}
		}
		fsm_bko_sensor_status++;
		virtual_timers_timer_reset(BKO_SENSOR_TIMER);
	}
}