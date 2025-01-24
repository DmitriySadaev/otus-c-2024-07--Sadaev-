/*! 
  \file
  \defgroup		fsm_ui_bu_shd_r_m
  \brief		Файл исходного кода программы fsm_ui_bu_shd_r_m.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя программный модуль обработки управления виртуальными таймерами, используемый при построении программы на основе конечных автоматов
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_virtual_timers.h"

uint16_t virtual_timers[MAX_TIMERS]; 
uint16_t global_virtual_timers[MAX_GLOBAL_TIMERS];
uint8_t global_virtual_timers_states[MAX_GLOBAL_TIMERS];

void virtual_timers_process(void) 
{	if (timer_check_compare_match(2) == TRUE)	{		for(uint8_t i = 0; i < MAX_TIMERS; i++)
		{
			virtual_timers[i]++;
		}		}
}

void virtual_timers_init(uint16_t timer_prescaler, uint8_t compare_interrupt_value) 
{
	for(uint8_t i = 0; i < MAX_TIMERS; i++)
	{
		virtual_timers[i] = 0;
	}
	
	timer_init(2, timer_prescaler, NORMAL, NORMAL_PORT_OPERATION, FALSE, FALSE, compare_interrupt_value); 
}

uint16_t virtual_timers_timer_get(uint8_t virtual_timer)
{
	return virtual_timers[virtual_timer];
}

void virtual_timers_timer_reset(uint8_t virtual_timer)
{
	virtual_timers[virtual_timer] = 0;
}

void virtual_timers_global_timers_init(void)
{
	for(uint8_t i = 0; i < MAX_GLOBAL_TIMERS; i++)
	{
		global_virtual_timers_states[i] = TIMER_STOPPED;
	}
}

void virtual_timers_global_timer_start(uint8_t global_timer_id)
{
	if (global_virtual_timers_states[global_timer_id] == TIMER_STOPPED)
	{
		global_virtual_timers[global_timer_id] = 0;
		global_virtual_timers_states[global_timer_id] = TIMER_RUNNING;
	}
}

void virtual_timers_global_timer_stop(uint8_t global_timer_id)
{
	global_virtual_timers_states[global_timer_id] = TIMER_STOPPED;
}

void virtual_timers_global_timer_pause(uint8_t global_timer_id)
{
	if (global_virtual_timers_states[global_timer_id] == TIMER_RUNNING)
	{
		global_virtual_timers_states[global_timer_id] = TIMER_PAUSED;
	}
}

void virtual_timers_global_timer_release(uint8_t global_timer_id)
{
	if (global_virtual_timers_states[global_timer_id] == TIMER_PAUSED)
	{
		global_virtual_timers_states[global_timer_id] = TIMER_RUNNING;
	}
}

uint16_t virtual_timers_global_timer_get(uint8_t global_timer_id)
{
	return global_virtual_timers[global_timer_id];
}

void virtual_global_timers_process(void)
{
	if (timer_check_compare_match(2) == TRUE)	{		for(uint8_t i = 0; i < MAX_GLOBAL_TIMERS; i++)
		{
			if (global_virtual_timers_states[i] == TIMER_RUNNING)
			{
				global_virtual_timers[i]++;
			}
		}		}
}