<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_led_vector
  \brief		Файл исходного кода программы fsm_led_vector.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) светодиодной матрицы
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_led_vector.h"

uint8_t fsm_led_vector_state[8]; //вектор состояний светодиодов
uint8_t fsm_led_vector_data; //переменна из которой берутся данные для регистра

void fsm_led_vector_clear_states(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		fsm_led_vector_state[i] = FSM_LED_OFF;
	}
}

void fsm_led_on(uint8_t led_adress)
{
	fsm_led_vector_data |= (1 << led_adress);
}

void fsm_led_off(uint8_t led_adress)
{
	fsm_led_vector_data &= ~(1 << led_adress);
}

void fsm_led_toggle(uint8_t led_adress)
{
	if (fsm_led_vector_data & (1 << led_adress))
	{
		fsm_led_off(led_adress);
	}
	else
	{
		fsm_led_on(led_adress);
	}
}

void fsm_led_overheat_t1_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
		{
			fsm_led_vector_state[LED_OVERHEAT_T1_ADDRESS] = FSM_LED_OFF;
			if (bu_shd_r_m->error_flags & (1 << ERROR_T1_SHORT))
			{
				fsm_led_vector_state[LED_OVERHEAT_T1_ADDRESS] = FSM_LED_BLINKING;
			}
			if (bu_shd_r_m->error_flags & (1 << ERROR_T1_BREAK))
			{
				fsm_led_vector_state[LED_OVERHEAT_T1_ADDRESS] = FSM_LED_BLINKING;
			}
			if (bu_shd_r_m->error_flags & (1 << ERROR_T1_OVERHEAT))
			{
				fsm_led_vector_state[LED_OVERHEAT_T1_ADDRESS] = FSM_LED_ON;
			}
		}
}

void fsm_led_overheat_t2_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		fsm_led_vector_state[LED_OVERHEAT_T2_ADDRESS] = FSM_LED_OFF;
		if ( bu_shd_r_m->error_flags & (1 << ERROR_T2_SHORT))
		{
			fsm_led_vector_state[LED_OVERHEAT_T2_ADDRESS] = FSM_LED_BLINKING;
		}
		if ( bu_shd_r_m->error_flags & (1 << ERROR_T2_BREAK))
		{
			fsm_led_vector_state[LED_OVERHEAT_T2_ADDRESS] = FSM_LED_BLINKING;
		}
		if ( bu_shd_r_m->error_flags & (1 << ERROR_T2_OVERHEAT))
		{
			fsm_led_vector_state[LED_OVERHEAT_T2_ADDRESS] = FSM_LED_ON;
		}
	}
}

void fsm_led_phase_seq_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		if (bu_shd_r_m->error_flags & (1 << ERROR_KU_PHASE_A))
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_ON;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_KU_PHASE_B))
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_ON;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_KU_PHASE_C))
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_ON;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_KU_WRONG_PHASE_SEQUENCE))
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_ON;
		}
		else
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_OFF;
		}
	}
}

void fsm_led_regen_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_STARTED))
	{
		fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_ON;
	}
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_STOPPED))
	{
		fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_OFF;
	}
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_FINISHED))
	{
		fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_BLINKING;
	}
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_SHORT))
		{
			fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_BLINKING;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_BREAK))
		{
			fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_BLINKING;
		}
		else if (!(bu_shd_r_m->system_flags & (1 << SYSTEM_HEATER1))) 
		{
			fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_OFF;
		}
	}
}

void fsm_led_ku_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (virtual_timers_timer_get(LED_VECTOR_TIMER) >= FSM_LED_BLINK_HALF_PERIOD_MS)
	{
		if (bu_shd_r_m->system_flags & (1 << SYSTEM_KU))
		{
			fsm_led_vector_state[LED_KU_ADDRESS] = FSM_LED_ON;
		}
		else
		{
			fsm_led_vector_state[LED_KU_ADDRESS] = FSM_LED_OFF;
		}	
	}
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		if (bu_shd_r_m->error_flags & (1 << ERROR_KU_OVERLOAD))
		{
			fsm_led_vector_state[LED_KU_ADDRESS] = FSM_LED_BLINKING;
		}
		else
		{
			fsm_led_vector_state[LED_KU_ADDRESS] = FSM_LED_OFF;
		}
	}
}

void fsm_led_bko_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (virtual_timers_timer_get(LED_VECTOR_TIMER) >= FSM_LED_BLINK_HALF_PERIOD_MS)
	{
		if (bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1))
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_ON;
		}
		else if (!((bu_shd_r_m->error_flags & (1 << ERROR_BKO_OVERLOAD)) || (bu_shd_r_m->error_flags & (1 << ERROR_STEPPER_CURCUIT_BREAK))))
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_OFF;
		}
	}
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		if (bu_shd_r_m->error_flags & (1 << ERROR_BKO_OVERLOAD))
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_BLINKING;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_STEPPER_CURCUIT_BREAK))
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_BLINKING;
		}
		else
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_OFF;
		}
	}
}

void fsm_led_shd_rm_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (virtual_timers_timer_get(LED_VECTOR_TIMER) >= FSM_LED_BLINK_HALF_PERIOD_MS)
	{
		if (bu_shd_r_m->system_flags & (1 << SYSTEM_MO_II_ACTIVE))
		{
			fsm_led_vector_state[LED_SHD_RM_ADDRESS] = FSM_LED_ON;
		} 
		else
		{
			fsm_led_vector_state[LED_SHD_RM_ADDRESS] = FSM_LED_BLINKING;
		}
	}
}

void fsm_led_vector_set(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (fsm_led_vector_state[i] == FSM_LED_OFF)
		{
			fsm_led_off(i);
		}
		if (fsm_led_vector_state[i] == FSM_LED_ON)
		{
			fsm_led_on(i);
		}
		if (fsm_led_vector_state[i] == FSM_LED_BLINKING)
		{
			fsm_led_toggle(i);
		}
	}
}

void fsm_led_vector_init(void)
{
	fsm_led_vector_clear_states();
	cd54ac164_init();
	virtual_timers_timer_reset(LED_VECTOR_TIMER);
}

void fsm_led_vector_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	fsm_led_overheat_t1_process(bu_shd_r_m);
	fsm_led_overheat_t2_process(bu_shd_r_m);
	fsm_led_phase_seq_process(bu_shd_r_m);
	fsm_led_regen_process(bu_shd_r_m);
	fsm_led_ku_process(bu_shd_r_m);
	fsm_led_bko_process(bu_shd_r_m);
	fsm_led_shd_rm_process(bu_shd_r_m);
	
	if (virtual_timers_timer_get(LED_VECTOR_TIMER) >= FSM_LED_BLINK_HALF_PERIOD_MS)
	{	
		fsm_led_vector_set();
		cd54ac164_set(fsm_led_vector_data);
		virtual_timers_timer_reset(LED_VECTOR_TIMER);
	}
=======
/*! 
  \file
  \defgroup		fsm_led_vector
  \brief		Файл исходного кода программы fsm_led_vector.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) светодиодной матрицы
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_led_vector.h"

uint8_t fsm_led_vector_state[8]; //вектор состояний светодиодов
uint8_t fsm_led_vector_data; //переменна из которой берутся данные для регистра

void fsm_led_vector_clear_states(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		fsm_led_vector_state[i] = FSM_LED_OFF;
	}
}

void fsm_led_on(uint8_t led_adress)
{
	fsm_led_vector_data |= (1 << led_adress);
}

void fsm_led_off(uint8_t led_adress)
{
	fsm_led_vector_data &= ~(1 << led_adress);
}

void fsm_led_toggle(uint8_t led_adress)
{
	if (fsm_led_vector_data & (1 << led_adress))
	{
		fsm_led_off(led_adress);
	}
	else
	{
		fsm_led_on(led_adress);
	}
}

void fsm_led_overheat_t1_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
		{
			fsm_led_vector_state[LED_OVERHEAT_T1_ADDRESS] = FSM_LED_OFF;
			if (bu_shd_r_m->error_flags & (1 << ERROR_T1_SHORT))
			{
				fsm_led_vector_state[LED_OVERHEAT_T1_ADDRESS] = FSM_LED_BLINKING;
			}
			if (bu_shd_r_m->error_flags & (1 << ERROR_T1_BREAK))
			{
				fsm_led_vector_state[LED_OVERHEAT_T1_ADDRESS] = FSM_LED_BLINKING;
			}
			if (bu_shd_r_m->error_flags & (1 << ERROR_T1_OVERHEAT))
			{
				fsm_led_vector_state[LED_OVERHEAT_T1_ADDRESS] = FSM_LED_ON;
			}
		}
}

void fsm_led_overheat_t2_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		fsm_led_vector_state[LED_OVERHEAT_T2_ADDRESS] = FSM_LED_OFF;
		if ( bu_shd_r_m->error_flags & (1 << ERROR_T2_SHORT))
		{
			fsm_led_vector_state[LED_OVERHEAT_T2_ADDRESS] = FSM_LED_BLINKING;
		}
		if ( bu_shd_r_m->error_flags & (1 << ERROR_T2_BREAK))
		{
			fsm_led_vector_state[LED_OVERHEAT_T2_ADDRESS] = FSM_LED_BLINKING;
		}
		if ( bu_shd_r_m->error_flags & (1 << ERROR_T2_OVERHEAT))
		{
			fsm_led_vector_state[LED_OVERHEAT_T2_ADDRESS] = FSM_LED_ON;
		}
	}
}

void fsm_led_phase_seq_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		if (bu_shd_r_m->error_flags & (1 << ERROR_KU_PHASE_A))
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_ON;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_KU_PHASE_B))
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_ON;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_KU_PHASE_C))
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_ON;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_KU_WRONG_PHASE_SEQUENCE))
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_ON;
		}
		else
		{
			fsm_led_vector_state[LED_PHASE_SEQ_ADDRESS] = FSM_LED_OFF;
		}
	}
}

void fsm_led_regen_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_STARTED))
	{
		fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_ON;
	}
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_STOPPED))
	{
		fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_OFF;
	}
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_FINISHED))
	{
		fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_BLINKING;
	}
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_SHORT))
		{
			fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_BLINKING;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_BREAK))
		{
			fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_BLINKING;
		}
		else if (!(bu_shd_r_m->system_flags & (1 << SYSTEM_HEATER1))) 
		{
			fsm_led_vector_state[LED_REGEN1_ADDRESS] = FSM_LED_OFF;
		}
	}
}

void fsm_led_ku_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (virtual_timers_timer_get(LED_VECTOR_TIMER) >= FSM_LED_BLINK_HALF_PERIOD_MS)
	{
		if (bu_shd_r_m->system_flags & (1 << SYSTEM_KU))
		{
			fsm_led_vector_state[LED_KU_ADDRESS] = FSM_LED_ON;
		}
		else
		{
			fsm_led_vector_state[LED_KU_ADDRESS] = FSM_LED_OFF;
		}	
	}
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		if (bu_shd_r_m->error_flags & (1 << ERROR_KU_OVERLOAD))
		{
			fsm_led_vector_state[LED_KU_ADDRESS] = FSM_LED_BLINKING;
		}
		else
		{
			fsm_led_vector_state[LED_KU_ADDRESS] = FSM_LED_OFF;
		}
	}
}

void fsm_led_bko_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (virtual_timers_timer_get(LED_VECTOR_TIMER) >= FSM_LED_BLINK_HALF_PERIOD_MS)
	{
		if (bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1))
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_ON;
		}
		else if (!((bu_shd_r_m->error_flags & (1 << ERROR_BKO_OVERLOAD)) || (bu_shd_r_m->error_flags & (1 << ERROR_STEPPER_CURCUIT_BREAK))))
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_OFF;
		}
	}
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
	{
		if (bu_shd_r_m->error_flags & (1 << ERROR_BKO_OVERLOAD))
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_BLINKING;
		}
		else if (bu_shd_r_m->error_flags & (1 << ERROR_STEPPER_CURCUIT_BREAK))
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_BLINKING;
		}
		else
		{
			fsm_led_vector_state[LED_BKO1_ADDRESS] = FSM_LED_OFF;
		}
	}
}

void fsm_led_shd_rm_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (virtual_timers_timer_get(LED_VECTOR_TIMER) >= FSM_LED_BLINK_HALF_PERIOD_MS)
	{
		if (bu_shd_r_m->system_flags & (1 << SYSTEM_MO_II_ACTIVE))
		{
			fsm_led_vector_state[LED_SHD_RM_ADDRESS] = FSM_LED_ON;
		} 
		else
		{
			fsm_led_vector_state[LED_SHD_RM_ADDRESS] = FSM_LED_BLINKING;
		}
	}
}

void fsm_led_vector_set(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		if (fsm_led_vector_state[i] == FSM_LED_OFF)
		{
			fsm_led_off(i);
		}
		if (fsm_led_vector_state[i] == FSM_LED_ON)
		{
			fsm_led_on(i);
		}
		if (fsm_led_vector_state[i] == FSM_LED_BLINKING)
		{
			fsm_led_toggle(i);
		}
	}
}

void fsm_led_vector_init(void)
{
	fsm_led_vector_clear_states();
	cd54ac164_init();
	virtual_timers_timer_reset(LED_VECTOR_TIMER);
}

void fsm_led_vector_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	fsm_led_overheat_t1_process(bu_shd_r_m);
	fsm_led_overheat_t2_process(bu_shd_r_m);
	fsm_led_phase_seq_process(bu_shd_r_m);
	fsm_led_regen_process(bu_shd_r_m);
	fsm_led_ku_process(bu_shd_r_m);
	fsm_led_bko_process(bu_shd_r_m);
	fsm_led_shd_rm_process(bu_shd_r_m);
	
	if (virtual_timers_timer_get(LED_VECTOR_TIMER) >= FSM_LED_BLINK_HALF_PERIOD_MS)
	{	
		fsm_led_vector_set();
		cd54ac164_set(fsm_led_vector_data);
		virtual_timers_timer_reset(LED_VECTOR_TIMER);
	}
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
}