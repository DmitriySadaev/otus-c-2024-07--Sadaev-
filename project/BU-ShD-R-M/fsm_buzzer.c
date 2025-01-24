<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_buzzer
  \brief		Файл исходного кода программы fsm_buzzer.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) зуммера
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_buzzer.h"

uint8_t fsm_buzzer_count;

void fsm_buzzer_init (struct buzzer_data * buzzer, uint32_t duty_cycle, uint8_t period, uint8_t buzzer_pin, volatile uint8_t * buzzer_port)
{
	fsm_buzzer_count = 0;
	hal_buzzer_init(buzzer, duty_cycle, period, buzzer_pin, buzzer_port);
	virtual_timers_timer_reset(BUZZER_TIMER);
}

void fsm_buzzer_process (struct buzzer_data * buzzer, uint8_t buzzer_work_enable)
{
	if (buzzer_work_enable)
	{
		switch (buzzer->status)
		{
			case BUZZER_ON:
			{
				if (virtual_timers_timer_get(BUZZER_TIMER) >= FSM_BUZZER_SURVEY_PERIOD)
				{
					fsm_buzzer_count ++;
					virtual_timers_timer_reset(BUZZER_TIMER);
				}
				if (fsm_buzzer_count > 100)
				{
					fsm_buzzer_count = 0;
				}
				if (fsm_buzzer_count <= buzzer->duty_cycle)
				{
					if (virtual_timers_timer_get(BUZZER_TIMER) < (buzzer->period*(float)buzzer->duty_cycle/100))
					{
						hal_buzzer_pin_on(buzzer);
					}
					if (virtual_timers_timer_get(BUZZER_TIMER) >= (buzzer->period*(float)buzzer->duty_cycle/100))
					{
						hal_buzzer_pin_off(buzzer);
					}
				}
				if (fsm_buzzer_count > buzzer->duty_cycle)
				{
					hal_buzzer_pin_off(buzzer);
				}
				if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS))
				{
					buzzer->status = BUZZER_OFF;
					hal_buzzer_pin_off(buzzer);
				}
				if (fsm_messages_get_broadcast_message(MSG_BUZZER_TURN_OFF))
				{
					buzzer->status = BUZZER_OFF;
					hal_buzzer_pin_off(buzzer);
				}
				break;
			}
			case BUZZER_OFF:
			{
				if (fsm_messages_get_broadcast_message(MSG_BUZZER_TURN_ON))
				{
					buzzer->status = BUZZER_ON;
				}
				if (fsm_messages_get_broadcast_message(MSG_REGEN1_FINISHED))
				{
					buzzer->status = BUZZER_ON;
				}
				if (fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
				{
					buzzer->status = BUZZER_ON;
				}
				virtual_timers_timer_reset(BUZZER_TIMER);
				break;
			}
		}	
	}
	else
	{
		hal_buzzer_pin_off(buzzer);
	}
=======
/*! 
  \file
  \defgroup		fsm_buzzer
  \brief		Файл исходного кода программы fsm_buzzer.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) зуммера
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_buzzer.h"

uint8_t fsm_buzzer_count;

void fsm_buzzer_init (struct buzzer_data * buzzer, uint32_t duty_cycle, uint8_t period, uint8_t buzzer_pin, volatile uint8_t * buzzer_port)
{
	fsm_buzzer_count = 0;
	hal_buzzer_init(buzzer, duty_cycle, period, buzzer_pin, buzzer_port);
	virtual_timers_timer_reset(BUZZER_TIMER);
}

void fsm_buzzer_process (struct buzzer_data * buzzer, uint8_t buzzer_work_enable)
{
	if (buzzer_work_enable)
	{
		switch (buzzer->status)
		{
			case BUZZER_ON:
			{
				if (virtual_timers_timer_get(BUZZER_TIMER) >= FSM_BUZZER_SURVEY_PERIOD)
				{
					fsm_buzzer_count ++;
					virtual_timers_timer_reset(BUZZER_TIMER);
				}
				if (fsm_buzzer_count > 100)
				{
					fsm_buzzer_count = 0;
				}
				if (fsm_buzzer_count <= buzzer->duty_cycle)
				{
					if (virtual_timers_timer_get(BUZZER_TIMER) < (buzzer->period*(float)buzzer->duty_cycle/100))
					{
						hal_buzzer_pin_on(buzzer);
					}
					if (virtual_timers_timer_get(BUZZER_TIMER) >= (buzzer->period*(float)buzzer->duty_cycle/100))
					{
						hal_buzzer_pin_off(buzzer);
					}
				}
				if (fsm_buzzer_count > buzzer->duty_cycle)
				{
					hal_buzzer_pin_off(buzzer);
				}
				if (fsm_messages_get_broadcast_message(MSG_UPDATE_ERRORS))
				{
					buzzer->status = BUZZER_OFF;
					hal_buzzer_pin_off(buzzer);
				}
				if (fsm_messages_get_broadcast_message(MSG_BUZZER_TURN_OFF))
				{
					buzzer->status = BUZZER_OFF;
					hal_buzzer_pin_off(buzzer);
				}
				break;
			}
			case BUZZER_OFF:
			{
				if (fsm_messages_get_broadcast_message(MSG_BUZZER_TURN_ON))
				{
					buzzer->status = BUZZER_ON;
				}
				if (fsm_messages_get_broadcast_message(MSG_REGEN1_FINISHED))
				{
					buzzer->status = BUZZER_ON;
				}
				if (fsm_messages_get_broadcast_message(MSG_NEW_ERROR))
				{
					buzzer->status = BUZZER_ON;
				}
				virtual_timers_timer_reset(BUZZER_TIMER);
				break;
			}
		}	
	}
	else
	{
		hal_buzzer_pin_off(buzzer);
	}
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
}