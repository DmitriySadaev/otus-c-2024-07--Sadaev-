<<<<<<< HEAD
/*! 
  \file
  \defgroup		clock
  \brief		Файл исходного кода программы clock.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) часов рального времени
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_clock.h"

void fsm_clock_init(struct ds1302_data * time)
{
	ds1302_init();
	ds1302_update(time);
	virtual_timers_timer_reset(CLOCK_TIMER);
}

void fsm_clock_process(struct ds1302_data * time)
{
	if (virtual_timers_timer_get(CLOCK_TIMER) >= FSM_CLOCK_SURVEY_PERIOD_MS)
	{
		ds1302_update(time);
		virtual_timers_timer_reset(CLOCK_TIMER);
	} 
=======
/*! 
  \file
  \defgroup		clock
  \brief		Файл исходного кода программы clock.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) часов рального времени
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_clock.h"

void fsm_clock_init(struct ds1302_data * time)
{
	ds1302_init();
	ds1302_update(time);
	virtual_timers_timer_reset(CLOCK_TIMER);
}

void fsm_clock_process(struct ds1302_data * time)
{
	if (virtual_timers_timer_get(CLOCK_TIMER) >= FSM_CLOCK_SURVEY_PERIOD_MS)
	{
		ds1302_update(time);
		virtual_timers_timer_reset(CLOCK_TIMER);
	} 
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
}