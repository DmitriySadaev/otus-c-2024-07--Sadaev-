/*! 
  \file
  \defgroup		fsm_regenerator
  \brief		Файл исходного кода программы fsm_regenerator.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) регенератора
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_regenerator.h"

uint8_t  fsm_regenerator_status;
uint8_t  fsm_regenerator_counter;

void fsm_regenerator_init(struct heater_data * heater, uint8_t voltage, uint8_t power_watt, uint8_t load_ohm, uint8_t heater_pin, volatile uint8_t * heater_port)
{
	fsm_regenerator_counter = 0;
	hal_heater_init(heater, voltage, power_watt, load_ohm, heater_pin, heater_port);
	fsm_regenerator_status = FSM_REGENERATOR_STATUS_OFF;
	virtual_timers_timer_reset(REGENERATOR_TIMER);
}

uint8_t fsm_regeneration_allowed_to_start(struct bu_shd_r_m_data * bu_shd_r_m)
{
	uint8_t result = FALSE;
	
	do 
	{
		if (bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1))				{break;}
		if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_SHORT))		{break;}	
		if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_BREAK))		{break;}				
		if (bu_shd_r_m->error_flags & (1 << ERROR_BKO_SENSOR_SHORT))	{break;}	
		if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_SENSOR_BREAK))	{break;}				
		result = TRUE;						
	} while (0);
		
	return result;
}

void fsm_regenerator_process(struct bu_shd_r_m_data * bu_shd_r_m, struct heater_data * heater)
{
	switch (fsm_regenerator_status)
	{
		case FSM_REGENERATOR_STATUS_OFF:
		{
			if ((fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_REG1_START)) && fsm_regeneration_allowed_to_start(bu_shd_r_m))
			{
				fsm_regenerator_status = FSM_REGENERATOR_STATUS_ON;
				bu_shd_r_m->system_flags |= (1 << SYSTEM_HEATER1);
				fsm_messages_send_broadcast_message(MSG_REGEN1_STARTED);
			}
			break;
		}
		case FSM_REGENERATOR_STATUS_ON:
		{

			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_REG1_STOP))
			{
				fsm_regenerator_status = FSM_REGENERATOR_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_HEATER1);
				fsm_messages_send_broadcast_message(MSG_REGEN1_STOPPED);
			}
			if (bu_shd_r_m->bko1_temperature_grad10 >= FSM_REGENERATOR_TURN_OFF_SETPOINT_GRAD10)
			{
				fsm_regenerator_status = FSM_REGENERATOR_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_HEATER1);
				fsm_messages_send_broadcast_message(MSG_REGEN1_FINISHED);		
			}
			if (fsm_regenerator_counter >= 2)
			{
				fsm_regenerator_status = FSM_REGENERATOR_STATUS_ON_CURRENT_STABILIZED;
				fsm_regenerator_counter = 0;
			} 
			
			break;
		}
		case FSM_REGENERATOR_STATUS_ON_CURRENT_STABILIZED:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_REG1_STOP))
			{
				fsm_regenerator_status = FSM_REGENERATOR_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_HEATER1);
				fsm_messages_send_broadcast_message(MSG_REGEN1_STOPPED);
			}
			if (bu_shd_r_m->bko1_temperature_grad10 >= FSM_REGENERATOR_TURN_OFF_SETPOINT_GRAD10)
			{
				fsm_regenerator_status = FSM_REGENERATOR_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_HEATER1);
				fsm_messages_send_broadcast_message(MSG_REGEN1_FINISHED);
			}
			if (bu_shd_r_m->current <= FSM_REGENERATOR_HEATER_BREAK_SETPOINT)
			{
				fsm_regenerator_status = FSM_REGENERATOR_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_HEATER1);
				bu_shd_r_m->error_flags |= (1 << ERROR_HEATER_BREAK);
				fsm_messages_send_broadcast_message(MSG_REGEN1_STOPPED);
				fsm_messages_send_broadcast_message(MSG_HEATER_BREAK);	
				fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
			}
			if (bu_shd_r_m->current >= FSM_REGENERATOR_HEATER_SHORT_SETPOINT)
			{
				fsm_regenerator_status = FSM_REGENERATOR_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_HEATER1);
				bu_shd_r_m->error_flags |= (1 << ERROR_HEATER_SHORT);
				fsm_messages_send_broadcast_message(MSG_REGEN1_STOPPED);
				fsm_messages_send_broadcast_message(MSG_HEATER_SHORT);
				fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
			}
			break;			
		}
	}
	if ((fsm_regenerator_status == FSM_REGENERATOR_STATUS_ON) || (fsm_regenerator_status == FSM_REGENERATOR_STATUS_ON_CURRENT_STABILIZED))
	{
		if (hal_heater_get_period_percent(heater) > virtual_timers_timer_get(REGENERATOR_TIMER)/10)
		{
			hal_heater_pin_on(heater);
		}
		if (hal_heater_get_period_percent(heater) <= virtual_timers_timer_get(REGENERATOR_TIMER)/10)
		{
			hal_heater_pin_off(heater);
		}
	}
	if (fsm_regenerator_status == FSM_REGENERATOR_STATUS_OFF)
	{
		hal_heater_pin_off(heater);
	}
	if (virtual_timers_timer_get(REGENERATOR_TIMER) >= FSM_REGENERATOR_SURVEY_PERIOD_MS)
	{
		virtual_timers_timer_reset(REGENERATOR_TIMER);
		if (fsm_regenerator_status == FSM_REGENERATOR_STATUS_ON)
		{
			fsm_regenerator_counter++;
		}
	}
}
