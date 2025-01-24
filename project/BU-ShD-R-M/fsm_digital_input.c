/*! 
  \file
  \defgroup		fsm_digital_input
  \brief		Файл исходного кода программы fsm_buzzer.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний цифровых входов
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_digital_input.h"

void fsm_digital_input_init(void)
{
	virtual_timers_timer_reset(DIGITAL_INPUT_TIMER);
}

void fsm_digital_input_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_START))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_BKO1_START);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_BKO1_STOP);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO2_START))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_BKO2_START);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO2_STOP))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_BKO2_STOP);
	}	
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_REG1_START))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_REG1_START);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_REG1_STOP))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_REG1_STOP);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_REG2_START))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_REG2_START);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_REG2_STOP))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_REG2_STOP);
	}	
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_ENTER);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_RIGHT);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_LEFT);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ESC))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_INPUT_ESC);
	}	
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_PHASE_A))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_PHASE_A);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_PHASE_B))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_PHASE_B);
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_PHASE_C))
	{
		bu_shd_r_m->digital_input |= (1 << FSM_DIGITAL_PHASE_C);
	}
	if (virtual_timers_timer_get(DIGITAL_INPUT_TIMER) >= FSM_DIGITAL_INPUT_SURVEY_PERIOD_MS)
	{	
		bu_shd_r_m->digital_input = 0;
		virtual_timers_timer_reset(DIGITAL_INPUT_TIMER);
	}
}
