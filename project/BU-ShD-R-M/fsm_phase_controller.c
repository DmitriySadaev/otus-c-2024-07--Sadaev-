<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_phase_controller
  \brief		Файл исходного кода программы fsm_phase_controller.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) контроллера фаз
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_phase_controller.h"

uint8_t fsm_phase_controller_phase_a_count;
uint8_t fsm_phase_controller_phase_b_count;
uint8_t fsm_phase_controller_phase_c_count;


void fsm_phase_controller_phase_count(void)
{
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_PHASE_A))
	{
		if (fsm_phase_controller_phase_a_count < 255) fsm_phase_controller_phase_a_count++;
	}	
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_PHASE_B))
	{
		if (fsm_phase_controller_phase_b_count < 255) fsm_phase_controller_phase_b_count++;
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_PHASE_C))
	{
		if (fsm_phase_controller_phase_c_count < 255) fsm_phase_controller_phase_c_count++;
	}
}

void fsm_phase_controller_phase_count_init(void)
{
	fsm_phase_controller_phase_a_count = 0;
	fsm_phase_controller_phase_b_count = 0;
	fsm_phase_controller_phase_c_count = 0;	
}

void fsm_phase_controller_handle_phase_a(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_phase_controller_phase_a_count < FSM_PHASE_CONTROLLER_PHASE_CHECK_COUNT)
	{	
		bu_shd_r_m->error_flags |= (1 << ERROR_KU_PHASE_A);
		fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
		fsm_messages_send_broadcast_message(MSG_WRONG_PHASE_SEQUENCE);
	}	
}

void fsm_phase_controller_handle_phase_b(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_phase_controller_phase_b_count < FSM_PHASE_CONTROLLER_PHASE_CHECK_COUNT)
	{
		bu_shd_r_m->error_flags |= (1 << ERROR_KU_PHASE_B);
		fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
		fsm_messages_send_broadcast_message(MSG_WRONG_PHASE_SEQUENCE);
	}
}

void fsm_phase_controller_handle_phase_c(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_phase_controller_phase_c_count < FSM_PHASE_CONTROLLER_PHASE_CHECK_COUNT)
	{
		bu_shd_r_m->error_flags |= (1 << ERROR_KU_PHASE_C);
		fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
		fsm_messages_send_broadcast_message(MSG_WRONG_PHASE_SEQUENCE);
	}
}

void fsm_phase_controller_init(void)
{
	fsm_phase_controller_phase_count_init();
	virtual_timers_timer_reset(PHASE_CONTROLLER_TIMER);
}

void fsm_phase_controller_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	fsm_phase_controller_phase_count();
	if (virtual_timers_timer_get(PHASE_CONTROLLER_TIMER) >= FSM_PHASE_CONTROLLER_SURVEY_PERIOD_MS)
	{
		fsm_phase_controller_handle_phase_a(bu_shd_r_m);
		fsm_phase_controller_handle_phase_b(bu_shd_r_m);
		fsm_phase_controller_handle_phase_c(bu_shd_r_m);
		fsm_phase_controller_phase_count_init();
		virtual_timers_timer_reset(PHASE_CONTROLLER_TIMER);
	} 
}

=======
/*! 
  \file
  \defgroup		fsm_phase_controller
  \brief		Файл исходного кода программы fsm_phase_controller.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) контроллера фаз
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_phase_controller.h"

uint8_t fsm_phase_controller_phase_a_count;
uint8_t fsm_phase_controller_phase_b_count;
uint8_t fsm_phase_controller_phase_c_count;


void fsm_phase_controller_phase_count(void)
{
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_PHASE_A))
	{
		if (fsm_phase_controller_phase_a_count < 255) fsm_phase_controller_phase_a_count++;
	}	
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_PHASE_B))
	{
		if (fsm_phase_controller_phase_b_count < 255) fsm_phase_controller_phase_b_count++;
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_PHASE_C))
	{
		if (fsm_phase_controller_phase_c_count < 255) fsm_phase_controller_phase_c_count++;
	}
}

void fsm_phase_controller_phase_count_init(void)
{
	fsm_phase_controller_phase_a_count = 0;
	fsm_phase_controller_phase_b_count = 0;
	fsm_phase_controller_phase_c_count = 0;	
}

void fsm_phase_controller_handle_phase_a(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_phase_controller_phase_a_count < FSM_PHASE_CONTROLLER_PHASE_CHECK_COUNT)
	{	
		bu_shd_r_m->error_flags |= (1 << ERROR_KU_PHASE_A);
		fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
		fsm_messages_send_broadcast_message(MSG_WRONG_PHASE_SEQUENCE);
	}	
}

void fsm_phase_controller_handle_phase_b(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_phase_controller_phase_b_count < FSM_PHASE_CONTROLLER_PHASE_CHECK_COUNT)
	{
		bu_shd_r_m->error_flags |= (1 << ERROR_KU_PHASE_B);
		fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
		fsm_messages_send_broadcast_message(MSG_WRONG_PHASE_SEQUENCE);
	}
}

void fsm_phase_controller_handle_phase_c(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_phase_controller_phase_c_count < FSM_PHASE_CONTROLLER_PHASE_CHECK_COUNT)
	{
		bu_shd_r_m->error_flags |= (1 << ERROR_KU_PHASE_C);
		fsm_messages_send_broadcast_message(MSG_NEW_ERROR);
		fsm_messages_send_broadcast_message(MSG_WRONG_PHASE_SEQUENCE);
	}
}

void fsm_phase_controller_init(void)
{
	fsm_phase_controller_phase_count_init();
	virtual_timers_timer_reset(PHASE_CONTROLLER_TIMER);
}

void fsm_phase_controller_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	fsm_phase_controller_phase_count();
	if (virtual_timers_timer_get(PHASE_CONTROLLER_TIMER) >= FSM_PHASE_CONTROLLER_SURVEY_PERIOD_MS)
	{
		fsm_phase_controller_handle_phase_a(bu_shd_r_m);
		fsm_phase_controller_handle_phase_b(bu_shd_r_m);
		fsm_phase_controller_handle_phase_c(bu_shd_r_m);
		fsm_phase_controller_phase_count_init();
		virtual_timers_timer_reset(PHASE_CONTROLLER_TIMER);
	} 
}

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
