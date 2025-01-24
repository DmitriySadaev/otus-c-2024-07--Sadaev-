/*! 
  \file
  \defgroup		fsm_bko
  \brief		Файл исходного кода программы fsm_bko.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) блока криооткачки 
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_bko.h"

uint8_t  fsm_bko_status;
uint8_t fsm_bko_counter;

uint8_t fsm_bko_check_is_connected(struct dm542_driver_data * dm542_driver)
{
	uint8_t result = TRUE;
	volatile uint8_t * port = dm542_driver->dm542_connection_check_port;
	
	if (*(port-2) & (1 << dm542_driver->dm542_connection_check_pin))
	{
		result = FALSE;
	}
	
	return result;
}

void fsm_bko_init(struct dm542_driver_data * dm542_driver, uint8_t dm542_control_pul_pin, uint8_t dm542_control_ena_pin, volatile uint8_t * dm542_control_port, uint8_t dm542_power_drv_pin, volatile uint8_t * dm542_power_drv_port, uint8_t dm542_connection_check_pin, volatile uint8_t * dm542_connection_check_port, uint32_t f_cpu)
{
	fsm_bko_counter = 0;
	hal_dm542_init(dm542_driver, dm542_control_pul_pin, dm542_control_ena_pin, dm542_control_port, dm542_power_drv_pin, dm542_power_drv_port, dm542_connection_check_pin, dm542_connection_check_port, f_cpu);
	if (fsm_bko_check_is_connected(dm542_driver))
	{
		hal_dm542_power_drv_off(dm542_driver);
		hal_dm542_control_ena_off(dm542_driver);
		fsm_bko_status = FSM_BKO_STATUS_OFF;
		virtual_timers_timer_reset(BKO_TIMER);
	}
}

void fsm_bko_speed_select_via_keyboard(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RPM))
	{
		if (bu_shd_r_m->system_flags & (1 << SYSTEM_MO_II_ACTIVE))
		{
			bu_shd_r_m->system_flags &= ~(1 << SYSTEM_MO_II_ACTIVE);
			fsm_messages_send_broadcast_message(MSG_MODE_CHANGE);
		}
		else 
		{
			bu_shd_r_m->system_flags |= (1 << SYSTEM_MO_II_ACTIVE);
			fsm_messages_send_broadcast_message(MSG_MODE_CHANGE);
		}
	}
}

void fsm_bko_send_mode_message()
{
	static uint8_t bko_send_mode_iterator = 0;
	
	if (bko_send_mode_iterator < 6)
	{
		bko_send_mode_iterator++;	
	}
	
	if (bko_send_mode_iterator == 6)
	{
		fsm_messages_send_broadcast_message(MSG_MODE_CHANGE);
		bko_send_mode_iterator = 0;	
	}
}

void fsm_bko_start_rotation(struct dm542_driver_data * dm542_driver, struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (bu_shd_r_m->system_flags & (1 << SYSTEM_MO_II_ACTIVE))
	{
		if (bu_shd_r_m->bko1_temperature_grad10 >= FSM_BKO_LOW_SPEED_ACTIVE_TEMPERARTURE_GRAD)
		{
			hal_dm542_start_rotation(dm542_driver, bu_shd_r_m->pul_rev_selected, bu_shd_r_m->rpm_high_s_selected);
		}
		if (bu_shd_r_m->bko1_temperature_grad10 < FSM_BKO_LOW_SPEED_ACTIVE_TEMPERARTURE_GRAD)
		{
			hal_dm542_start_rotation(dm542_driver, bu_shd_r_m->pul_rev_selected, bu_shd_r_m->rpm_low_s_selected);
		}
	}
	else
	{
		hal_dm542_start_rotation(dm542_driver, bu_shd_r_m->pul_rev_selected, bu_shd_r_m->rpm_low_s_selected);
	}	
}

void fsm_bko_process(struct bu_shd_r_m_data * bu_shd_r_m, struct dm542_driver_data * dm542_driver)
{
	fsm_bko_speed_select_via_keyboard(bu_shd_r_m);
	if (virtual_timers_timer_get(BKO_TIMER) >= FSM_BKO_SURVEY_PERIOD_MS)
	{
		if (!fsm_bko_check_is_connected(dm542_driver))
		{
			bu_shd_r_m->system_flags &= ~(1 << SYSTEM_BKO1_CONNECTED);
			if (!(bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED)))
			{
				fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
				fsm_messages_send_broadcast_message(MSG_BKO_NOT_CONNECTED);
				bu_shd_r_m->error_flags |= ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED);
				fsm_bko_status = FSM_BKO_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_BKO1);
			}
		}
		if (fsm_bko_check_is_connected(dm542_driver))
		{
			if ((!(bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1_CONNECTED))) && !(bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED)))
			{
				bu_shd_r_m->system_flags |= (1 << SYSTEM_BKO1_CONNECTED);
				fsm_messages_send_broadcast_message(MSG_BKO_CONNECTED);
			}
		}
	}
	switch (fsm_bko_status)
	{
		case FSM_BKO_STATUS_OFF:
		{
			fsm_bko_counter = 0;
			if (virtual_timers_timer_get(BKO_TIMER) >= FSM_BKO_SURVEY_PERIOD_MS)
			{
				fsm_bko_send_mode_message();
				virtual_timers_timer_reset(BKO_TIMER);	
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_START) && !(bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED)))
			{
				fsm_bko_status = FSM_BKO_STATUS_POWERED;
				hal_dm542_power_drv_on(dm542_driver);
				hal_dm542_control_ena_on(dm542_driver);
			}
			break;
		}
		case FSM_BKO_STATUS_POWERED:
		{
			if (virtual_timers_timer_get(BKO_TIMER) >= FSM_BKO_SURVEY_PERIOD_MS)
			{
				fsm_bko_status = FSM_BKO_STATUS_ON;
				if (!(bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1)))
				{
					bu_shd_r_m->system_flags |= (1 << SYSTEM_BKO1);
					fsm_messages_send_broadcast_message(MSG_BKO_STARTED);
				}			
				fsm_bko_start_rotation(dm542_driver, bu_shd_r_m);
				fsm_bko_send_mode_message();
				virtual_timers_timer_reset(BKO_TIMER);
			}
			break;
		}
		case FSM_BKO_STATUS_ON:
		{
			if (fsm_messages_get_broadcast_message(MSG_MODE_CHANGE) || fsm_messages_get_broadcast_message(MSG_EEPROM_UPDATED))
			{
				fsm_bko_start_rotation(dm542_driver, bu_shd_r_m);
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP) || fsm_check_errors_to_turn_off_bko_ku(bu_shd_r_m))
			{
				fsm_bko_status = FSM_BKO_STATUS_STOPPING;
				virtual_timers_timer_reset(BKO_TIMER);
			}
			if (virtual_timers_timer_get(BKO_TIMER) >= FSM_BKO_SURVEY_PERIOD_MS)
			{
				fsm_bko_send_mode_message();
				fsm_bko_counter++;
			}
			if (fsm_bko_counter >= 10)
			{
				fsm_bko_status = FSM_BKO_STATUS_ON_CURRENT_STABILIZED;
				fsm_bko_counter = 0;
			}
			break;
		}
		case FSM_BKO_STATUS_ON_CURRENT_STABILIZED:
		{
			static uint8_t  fsm_bko_current_break_short_counter = 0;
			
			if (fsm_messages_get_broadcast_message(MSG_MODE_CHANGE) || fsm_messages_get_broadcast_message(MSG_EEPROM_UPDATED))
			{
				fsm_bko_start_rotation(dm542_driver, bu_shd_r_m);
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP) || fsm_check_errors_to_turn_off_bko_ku(bu_shd_r_m))
			{
				fsm_bko_status = FSM_BKO_STATUS_STOPPING;
				virtual_timers_timer_reset(BKO_TIMER);
			}
			if (bu_shd_r_m->current <= FSM_BKO_BREAK_SETPOINT)
			{				
				fsm_bko_current_break_short_counter++;
				
				if (fsm_bko_current_break_short_counter >= FSM_BKO_BREAK_SHORT_MAX_COUNT)
				{
					fsm_bko_current_break_short_counter = 0;
					fsm_bko_status = FSM_BKO_STATUS_OFF;
					bu_shd_r_m->system_flags &= ~(1 << SYSTEM_BKO1);
					bu_shd_r_m->error_flags |= (1 << ERROR_STEPPER_CURCUIT_BREAK);
					hal_dm542_stop_rotation(dm542_driver);
					hal_dm542_power_drv_off(dm542_driver);
					hal_dm542_control_ena_off(dm542_driver);
					fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
					fsm_messages_send_broadcast_message(MSG_STEPPER_BREAK);				
				}
			}
			if (bu_shd_r_m->current >= FSM_BKO_SHORT_SETPOINT)
			{
				fsm_bko_current_break_short_counter++;
				
				if (fsm_bko_current_break_short_counter >= FSM_BKO_BREAK_SHORT_MAX_COUNT)
				{
					fsm_bko_current_break_short_counter = 0;
					fsm_bko_status = FSM_BKO_STATUS_OFF;
					bu_shd_r_m->system_flags &= ~(1 << SYSTEM_BKO1);
					bu_shd_r_m->error_flags |= (1 << ERROR_BKO_OVERLOAD);
					hal_dm542_stop_rotation(dm542_driver);
					hal_dm542_power_drv_off(dm542_driver);
					hal_dm542_control_ena_off(dm542_driver);
					fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
					fsm_messages_send_broadcast_message(MSG_BKO_OVERLOAD);				
				}
			}
			if (!(bu_shd_r_m->current >= FSM_BKO_SHORT_SETPOINT) && !(bu_shd_r_m->current <= FSM_BKO_BREAK_SETPOINT))
			{
				fsm_bko_current_break_short_counter = 0;
			}
			break;
		}
		case FSM_BKO_STATUS_STOPPING:
		{
			static uint8_t ii = 0;
			if (virtual_timers_timer_get(BKO_TIMER) >= FSM_BKO_STOP_PERIOD_MS)
			{
				ii++;
				fsm_bko_send_mode_message();
				virtual_timers_timer_reset(BKO_TIMER);
			}
			if (ii >=2)
			{	
				fsm_bko_status = FSM_BKO_STATUS_OFF;
				virtual_timers_timer_reset(BKO_TIMER);
				fsm_messages_send_broadcast_message(MSG_BKO_STOPPED);
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_BKO1);
				hal_dm542_stop_rotation(dm542_driver);
				hal_dm542_power_drv_off(dm542_driver);
				hal_dm542_control_ena_off(dm542_driver);
				ii=0;
			}
			break;
		}
	}
}
