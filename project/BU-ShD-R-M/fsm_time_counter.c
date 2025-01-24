<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_time_counter
  \brief		Файл исходного кода программы fsm_time_counter.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) счетчика времени  наработки
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_time_counter.h"

uint8_t fsm_time_counter_status;
uint8_t start_counting_minute;
uint8_t update_counter_minute;

uint8_t fsm_time_counter_calculate_update_counter_minute(void)
{
	if ((start_counting_minute+6) >= 60)
	{
		return (start_counting_minute+FSM_TIME_COUTER_UPDATE_PERIOD_MINUTE-60);
	}
	else
	{
		return (start_counting_minute+FSM_TIME_COUTER_UPDATE_PERIOD_MINUTE);	
	}
}

void fsm_time_counter_init(void)
{
	start_counting_minute	= 0;
	update_counter_minute	= 0;
	fsm_time_counter_status = FSM_TIME_COUTER_STATUS_NOT_COUNTING;
	virtual_timers_timer_reset(TIME_COUNTER_TIMER);
}

void fsm_time_counter_update_operation_data(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (bu_shd_r_m->operation_time_h10 >= FSM_TIME_COUNTER_MAX_VALUE_H10)
	{
		bu_shd_r_m->operation_time_h10 = 0;
		bu_shd_r_m->operation_time_1000_h++;
	}
	else
	{
		bu_shd_r_m->operation_time_h10++;
	}
	bu_shd_r_m->system_flags |= (1 << SYSTEM_UPDATE_TIME_IN_EEPROM);
}

void fsm_time_counter_process(struct bu_shd_r_m_data * bu_shd_r_m, uint8_t * current_minute)
{
	if (virtual_timers_timer_get(TIME_COUNTER_TIMER) >= FSM_TIME_COUTER_SURVEY_PERIOD_MS)
	{
		switch(fsm_time_counter_status)
		{
			case FSM_TIME_COUTER_STATUS_NOT_COUNTING:
			{
				if (bu_shd_r_m->system_flags & (1 << SYSTEM_KU))
				{
					start_counting_minute = *current_minute;
					update_counter_minute = fsm_time_counter_calculate_update_counter_minute();
					fsm_time_counter_status = FSM_TIME_COUTER_STATUS_COUNTING;
				}
				break;
			}
			case FSM_TIME_COUTER_STATUS_COUNTING:
			{
				if (!(bu_shd_r_m->system_flags & (1 << SYSTEM_KU)))
				{
					fsm_time_counter_status = FSM_TIME_COUTER_STATUS_NOT_COUNTING;
					start_counting_minute	= 0;
					update_counter_minute	= 0;
				}
				if (*current_minute == update_counter_minute)
				{
					fsm_time_counter_update_operation_data(bu_shd_r_m);
					start_counting_minute = *current_minute;
					update_counter_minute = fsm_time_counter_calculate_update_counter_minute();					
				}
				break;
			}
		}
		virtual_timers_timer_reset(TIME_COUNTER_TIMER);	
	}
=======
/*! 
  \file
  \defgroup		fsm_time_counter
  \brief		Файл исходного кода программы fsm_time_counter.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) счетчика времени  наработки
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_time_counter.h"

uint8_t fsm_time_counter_status;
uint8_t start_counting_minute;
uint8_t update_counter_minute;

uint8_t fsm_time_counter_calculate_update_counter_minute(void)
{
	if ((start_counting_minute+6) >= 60)
	{
		return (start_counting_minute+FSM_TIME_COUTER_UPDATE_PERIOD_MINUTE-60);
	}
	else
	{
		return (start_counting_minute+FSM_TIME_COUTER_UPDATE_PERIOD_MINUTE);	
	}
}

void fsm_time_counter_init(void)
{
	start_counting_minute	= 0;
	update_counter_minute	= 0;
	fsm_time_counter_status = FSM_TIME_COUTER_STATUS_NOT_COUNTING;
	virtual_timers_timer_reset(TIME_COUNTER_TIMER);
}

void fsm_time_counter_update_operation_data(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (bu_shd_r_m->operation_time_h10 >= FSM_TIME_COUNTER_MAX_VALUE_H10)
	{
		bu_shd_r_m->operation_time_h10 = 0;
		bu_shd_r_m->operation_time_1000_h++;
	}
	else
	{
		bu_shd_r_m->operation_time_h10++;
	}
	bu_shd_r_m->system_flags |= (1 << SYSTEM_UPDATE_TIME_IN_EEPROM);
}

void fsm_time_counter_process(struct bu_shd_r_m_data * bu_shd_r_m, uint8_t * current_minute)
{
	if (virtual_timers_timer_get(TIME_COUNTER_TIMER) >= FSM_TIME_COUTER_SURVEY_PERIOD_MS)
	{
		switch(fsm_time_counter_status)
		{
			case FSM_TIME_COUTER_STATUS_NOT_COUNTING:
			{
				if (bu_shd_r_m->system_flags & (1 << SYSTEM_KU))
				{
					start_counting_minute = *current_minute;
					update_counter_minute = fsm_time_counter_calculate_update_counter_minute();
					fsm_time_counter_status = FSM_TIME_COUTER_STATUS_COUNTING;
				}
				break;
			}
			case FSM_TIME_COUTER_STATUS_COUNTING:
			{
				if (!(bu_shd_r_m->system_flags & (1 << SYSTEM_KU)))
				{
					fsm_time_counter_status = FSM_TIME_COUTER_STATUS_NOT_COUNTING;
					start_counting_minute	= 0;
					update_counter_minute	= 0;
				}
				if (*current_minute == update_counter_minute)
				{
					fsm_time_counter_update_operation_data(bu_shd_r_m);
					start_counting_minute = *current_minute;
					update_counter_minute = fsm_time_counter_calculate_update_counter_minute();					
				}
				break;
			}
		}
		virtual_timers_timer_reset(TIME_COUNTER_TIMER);	
	}
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
}