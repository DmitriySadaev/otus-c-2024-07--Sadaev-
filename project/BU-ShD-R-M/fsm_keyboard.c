/*! 
  \file
  \defgroup		fsm_keyboard
  \brief		Файл исходного кода программы fsm_keyboard.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) клавиатуры
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_keyboard.h"
uint8_t fsm_keyboard_state; 
uint32_t fsm_keyboard_code; 

void fsm_keyboard_init(void)
{
	sn74als165d_init();
	fsm_keyboard_state = 0;
	fsm_keyboard_code = 0;
	virtual_timers_timer_reset(KEYBOARD_TIMER);
}

void fsm_keyboard_send_message(uint32_t fsm_keyboard_code)
{
	for (uint8_t i = 0; i < 17; i++)
	{
		if (fsm_keyboard_code & (1 << i))
		{
			fsm_messages_send_broadcast_message(i);
		}
	}	
}

uint32_t fsm_keyboard_keycode_get(uint8_t * button_array)
{
	uint32_t result = 0;
	for (uint8_t i = 0; i < 17; i++)
	{
		if (*(button_array + i) == 1)
		{
			result |= ((uint32_t)1 << i);
		}
		else if (*(button_array + i) == 0)
		{
			result &= ~((uint32_t)1 << i);
		}
	}
	return result;
}

void fsm_keyboard_handle_fast_signals(uint32_t code)
{
	if (code & (1 << MSG_KEY_PRESSED_PHASE_A))
	{
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_PHASE_A);
	}	
	if (code & (1 << MSG_KEY_PRESSED_PHASE_B))
	{
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_PHASE_B);
	}
	if (code & (1 << MSG_KEY_PRESSED_PHASE_C))
	{
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_PHASE_C);
	}
}

void fsm_keyboard_autorepeat_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	static uint8_t autorepeat_iterator = 0;
	
	if (fsm_keyboard_state == FSM_KEYBOARD_STATE_AUTOREPEAT_PASSED)
	{	
		if ((virtual_timers_timer_get(KEYBOARD_TIMER) >= 1) && (autorepeat_iterator < 255))  
		{
			autorepeat_iterator++;
		}
		if (autorepeat_iterator > AUTO_REPEAT_ITERATOR_COUNT)
		{
			bu_shd_r_m->keyboard_autorepeat_mode_on = TRUE;
			autorepeat_iterator = 0;
		}
	}
	if (fsm_keyboard_state == FSM_KEYBOARD_STATE_KEY_NOT_PRESSED)
	{
		if ((virtual_timers_timer_get(KEYBOARD_TIMER) >= AUTO_REPEAT_TIME_MS)&& (autorepeat_iterator < 255))  
		{
			autorepeat_iterator++;
		}
		if (autorepeat_iterator > AUTO_REPEAT_ITERATOR_COUNT)
		{
			bu_shd_r_m->keyboard_autorepeat_mode_on = FALSE;
			autorepeat_iterator = 0;
		}
	}
}

void fsm_keyboard_process(uint8_t * button_array, struct bu_shd_r_m_data * bu_shd_r_m)
{
	static uint32_t fsm_keyboard_code_acquired = 0;
	
	sn74als165d_read(button_array);
	fsm_keyboard_code = fsm_keyboard_keycode_get(button_array);
	fsm_keyboard_handle_fast_signals(fsm_keyboard_code);	
	fsm_keyboard_autorepeat_process(bu_shd_r_m);
	switch(fsm_keyboard_state)
	{
		case FSM_KEYBOARD_STATE_KEY_NOT_PRESSED: //неактивное состояние
		{
			if ((fsm_keyboard_code & ~(1 << MSG_KEY_PRESSED_PHASE_C) & ~(1 << MSG_KEY_PRESSED_PHASE_B) & ~(1 << MSG_KEY_PRESSED_PHASE_A)) > 0)
			{
				fsm_keyboard_code_acquired = fsm_keyboard_code;
				fsm_keyboard_state = FSM_KEYBOARD_STATE_KEY_PRESSED;
				virtual_timers_timer_reset(KEYBOARD_TIMER);
			}
			break;
		}
		case FSM_KEYBOARD_STATE_KEY_PRESSED:
		{
			if (virtual_timers_timer_get(KEYBOARD_TIMER) >= DEBOUNCE_TIME_MS)
			{
				fsm_keyboard_state = FSM_KEYBOARD_STATE_DEBOUNCE_PASSED;
			}
			break;
		}
		case FSM_KEYBOARD_STATE_DEBOUNCE_PASSED:
		{		
			if (fsm_keyboard_code_acquired == fsm_keyboard_keycode_get(button_array))
			{
				virtual_timers_timer_reset(KEYBOARD_TIMER);
				fsm_keyboard_send_message(fsm_keyboard_code);
				fsm_keyboard_state = FSM_KEYBOARD_STATE_FIRST_DELAY_PASSED;
			}
			else
			{
				fsm_keyboard_state = 0;
			}
			break;
		}
		case FSM_KEYBOARD_STATE_FIRST_DELAY_PASSED:
		{
			if (fsm_keyboard_keycode_get(button_array) & ~(1 << MSG_KEY_PRESSED_PHASE_C) & ~(1 << MSG_KEY_PRESSED_PHASE_A) & ~(1 << MSG_KEY_PRESSED_PHASE_B))
			{
				if (virtual_timers_timer_get(KEYBOARD_TIMER) >= FIRST_DELAY_TIME_MS)
				{
					virtual_timers_timer_reset(KEYBOARD_TIMER);
					fsm_keyboard_state = FSM_KEYBOARD_STATE_AUTOREPEAT_PASSED;			
				}
			}
			else
			{
				fsm_keyboard_state = 0;
			}
			break;			
		}
		case FSM_KEYBOARD_STATE_AUTOREPEAT_PASSED:
		{
			if (fsm_keyboard_code_acquired == fsm_keyboard_keycode_get(button_array))
			{
				if (virtual_timers_timer_get(KEYBOARD_TIMER) >= AUTO_REPEAT_TIME_MS)
				{
					virtual_timers_timer_reset(KEYBOARD_TIMER);
					fsm_keyboard_send_message(fsm_keyboard_code);
				}
			}
			else
			{
				fsm_keyboard_state = FSM_KEYBOARD_STATE_KEY_NOT_PRESSED;
			}
			break;	
		}
	}
}
