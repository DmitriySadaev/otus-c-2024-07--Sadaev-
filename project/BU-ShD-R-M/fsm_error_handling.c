/*! 
  \file
  \defgroup		fsm_error_handling
  \brief		Файл исходного кода программы fsm_error_handling.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) обработчика ошибок
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_error_handling.h"

void fsm_error_handler_clear_all_but_supply_voltage_errors(struct bu_shd_r_m_data * bu_shd_r_m)
{
	//ошибки связанные с питанием сбрасываются только при перезагрузке питания
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_T1_SHORT);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_T1_BREAK);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_T1_OVERHEAT);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_T2_SHORT);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_T2_BREAK);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_T2_OVERHEAT);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_KU_OVERLOAD);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_BKO_OVERLOAD);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_STEPPER_CURCUIT_BREAK);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_HEATER_SHORT);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_HEATER_BREAK);
	bu_shd_r_m->error_flags &= ~ (1 << ERROR_BKO_SENSOR_SHORT);
	bu_shd_r_m->error_flags &= ~ ((uint32_t)1 << ERROR_BKO_SENSOR_BREAK);
	bu_shd_r_m->error_flags &= ~ ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED);
	bu_shd_r_m->error_flags &= ~ ((uint32_t)1 << ERROR_IT3_NO_CONNECTION);
}

uint8_t fsm_check_errors_to_turn_off_bko_ku(struct bu_shd_r_m_data * bu_shd_r_m)
{
	uint8_t result;
	do
	{
		if (bu_shd_r_m->error_flags & (1 << ERROR_T1_SHORT)) {result = TRUE; break;}; 
		if (bu_shd_r_m->error_flags & (1 << ERROR_T1_BREAK)) {result = TRUE; break;}; 
		if (bu_shd_r_m->error_flags & (1 << ERROR_T1_OVERHEAT)) {result = TRUE; break;}; 
		if (bu_shd_r_m->error_flags & (1 << ERROR_T2_SHORT)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_T2_BREAK)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_T2_OVERHEAT)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_KU_PHASE_A)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_KU_PHASE_B)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_KU_PHASE_C)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_KU_WRONG_PHASE_SEQUENCE)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_KU_OVERLOAD)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_BKO_OVERLOAD)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_STEPPER_CURCUIT_BREAK)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_SHORT)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_BREAK)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & (1 << ERROR_BKO_SENSOR_SHORT)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_SENSOR_BREAK)) {result = TRUE; break;};
		if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED)) {result = TRUE; break;};
		result = FALSE;
	} while (0);
	
	return result;
}

void fsm_error_handler_adsorber_status_change(struct bu_shd_r_m_data * bu_shd_r_m)
{
	static uint8_t adsorber_status_iterator = 0;
	
	if (((bu_shd_r_m->operation_time_1000_h*1000+bu_shd_r_m->operation_time_h10) % 100000 == 0) && (bu_shd_r_m->operation_time_1000_h != 0) && (bu_shd_r_m->operation_time_h10 != 0))
	{		
		if (((bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_CHANGE_ADSORBER)) == 0))
		{
			fsm_messages_send_broadcast_message(MSG_UPDATE_AFSORBER_EEPROM);
			bu_shd_r_m->error_flags |= ((uint32_t)1 << ERROR_CHANGE_ADSORBER);
		}
	}
	if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_CHANGE_ADSORBER))
	{
		if (adsorber_status_iterator < 3)
		{
			adsorber_status_iterator++;
		}
		if (adsorber_status_iterator == 3)
		{
			adsorber_status_iterator = 0;
			fsm_messages_send_broadcast_message(MSG_ADSORBER_LIMIT);
		}	
	}
}

void fsm_error_handler_init(void)
{
	virtual_timers_timer_reset(ADSORBER_CHECK_TIMER);
}

void fsm_error_handler_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	static uint8_t error_handler_esc_counter = 0;
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ESC) || fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP) || fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_REG1_STOP))
	{
		fsm_error_handler_clear_all_but_supply_voltage_errors(bu_shd_r_m);
		fsm_messages_send_broadcast_message(MSG_UPDATE_ERRORS);
		error_handler_esc_counter++;
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_OL))
	{
		bu_shd_r_m->error_flags |=  (1 << ERROR_KU_OVERLOAD);
		fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
	}
	if (virtual_timers_timer_get(ADSORBER_CHECK_TIMER) >= ADSORBER_CHECK_TIMECUT)
	{
		fsm_error_handler_adsorber_status_change(bu_shd_r_m);
		virtual_timers_timer_reset(ADSORBER_CHECK_TIMER);
		if ((error_handler_esc_counter > 10) && (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_CHANGE_ADSORBER)))
		{
			bu_shd_r_m->error_flags &=  ~((uint32_t)1 << ERROR_CHANGE_ADSORBER);
			fsm_messages_send_broadcast_message(MSG_UPDATE_AFSORBER_EEPROM);
		}
	}	
}

