/*! 
  \file
  \defgroup		clock
  \brief		���� ��������� ���� ��������� clock.c
  \author		������ �.�.
 
  ���� ��������� ���� �������� � ���� �������� �������, ������������ � �������� ���������.
  �������� ��� ������������ �� ���� ������ ��������� (�������� �������) ����� �������� �������
 
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
}