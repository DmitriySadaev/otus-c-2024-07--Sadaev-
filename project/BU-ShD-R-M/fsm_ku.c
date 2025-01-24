<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_ku
  \brief		Файл исходного кода программы fsm_ku.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) компрессорной установки
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_ku.h"

uint8_t fsm_ku_pin = 0;
volatile uint8_t * fsm_ku_port = 0;
uint8_t  fsm_ku_status = 0;

void fsm_ku_init_ddr(void)
{
	* (fsm_ku_port  -1)	|= (1 << fsm_ku_pin); //из адреса регистра PORT получаем адрес регистра DDR
}

void fsm_ku_turn_off(void)
{
	* (fsm_ku_port)	|= (1 << fsm_ku_pin);
}

void fsm_ku_turn_on(void)
{
	* (fsm_ku_port)	&= ~(1 << fsm_ku_pin);
}

void fsm_ku_init(uint8_t pin, volatile uint8_t * port)
{
	fsm_ku_pin = pin;
	fsm_ku_port = port;
	fsm_ku_status = FSM_KU_STATUS_OFF;
	fsm_ku_init_ddr();
	fsm_ku_turn_off();
	virtual_timers_timer_reset(KU_TIMER);
}

void fsm_ku_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_check_errors_to_turn_off_bko_ku(bu_shd_r_m))
	{
		fsm_ku_status = FSM_KU_STATUS_OFF;
		bu_shd_r_m->system_flags &= ~(1 << SYSTEM_KU);
	}
	switch (fsm_ku_status)
	{
		case FSM_KU_STATUS_OFF:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_START) && !(bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED)) && !(bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1)))
			{
				fsm_ku_status = FSM_KU_STATUS_WAITING_START_BKO;
			}
			break;	
		}
		case FSM_KU_STATUS_WAITING_START_BKO:
		{
			if (virtual_timers_timer_get(KU_TIMER) >= FSM_KU_WAITING_START_BKO_TIMEOUT_MS)
			{
				if (bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1)) //включаемся только если работает бко, таймаута нет
				{
					fsm_ku_status = FSM_KU_STATUS_ON;
					bu_shd_r_m->system_flags |= (1 << SYSTEM_KU);
				}
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP))
			{
				fsm_ku_status = FSM_KU_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_KU);
			}
			break;
		}
		case FSM_KU_STATUS_ON:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP))
			{
				fsm_ku_status = FSM_KU_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_KU);
			}
			break;
		}
	}
	if ((virtual_timers_timer_get(KU_TIMER) >= FSM_KU_SURVEY_PERIOD_MS) && (fsm_ku_status != FSM_KU_STATUS_WAITING_START_BKO))
	{
		virtual_timers_timer_reset(KU_TIMER);
		if (fsm_ku_status == FSM_KU_STATUS_ON)
		{
			fsm_ku_turn_on();
		}
		else 
		{
			fsm_ku_turn_off();
		}
	}
=======
/*! 
  \file
  \defgroup		fsm_ku
  \brief		Файл исходного кода программы fsm_ku.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) компрессорной установки
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_ku.h"

uint8_t fsm_ku_pin = 0;
volatile uint8_t * fsm_ku_port = 0;
uint8_t  fsm_ku_status = 0;

void fsm_ku_init_ddr(void)
{
	* (fsm_ku_port  -1)	|= (1 << fsm_ku_pin); //из адреса регистра PORT получаем адрес регистра DDR
}

void fsm_ku_turn_off(void)
{
	* (fsm_ku_port)	|= (1 << fsm_ku_pin);
}

void fsm_ku_turn_on(void)
{
	* (fsm_ku_port)	&= ~(1 << fsm_ku_pin);
}

void fsm_ku_init(uint8_t pin, volatile uint8_t * port)
{
	fsm_ku_pin = pin;
	fsm_ku_port = port;
	fsm_ku_status = FSM_KU_STATUS_OFF;
	fsm_ku_init_ddr();
	fsm_ku_turn_off();
	virtual_timers_timer_reset(KU_TIMER);
}

void fsm_ku_process(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_check_errors_to_turn_off_bko_ku(bu_shd_r_m))
	{
		fsm_ku_status = FSM_KU_STATUS_OFF;
		bu_shd_r_m->system_flags &= ~(1 << SYSTEM_KU);
	}
	switch (fsm_ku_status)
	{
		case FSM_KU_STATUS_OFF:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_START) && !(bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED)) && !(bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1)))
			{
				fsm_ku_status = FSM_KU_STATUS_WAITING_START_BKO;
			}
			break;	
		}
		case FSM_KU_STATUS_WAITING_START_BKO:
		{
			if (virtual_timers_timer_get(KU_TIMER) >= FSM_KU_WAITING_START_BKO_TIMEOUT_MS)
			{
				if (bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1)) //включаемся только если работает бко, таймаута нет
				{
					fsm_ku_status = FSM_KU_STATUS_ON;
					bu_shd_r_m->system_flags |= (1 << SYSTEM_KU);
				}
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP))
			{
				fsm_ku_status = FSM_KU_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_KU);
			}
			break;
		}
		case FSM_KU_STATUS_ON:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP))
			{
				fsm_ku_status = FSM_KU_STATUS_OFF;
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_KU);
			}
			break;
		}
	}
	if ((virtual_timers_timer_get(KU_TIMER) >= FSM_KU_SURVEY_PERIOD_MS) && (fsm_ku_status != FSM_KU_STATUS_WAITING_START_BKO))
	{
		virtual_timers_timer_reset(KU_TIMER);
		if (fsm_ku_status == FSM_KU_STATUS_ON)
		{
			fsm_ku_turn_on();
		}
		else 
		{
			fsm_ku_turn_off();
		}
	}
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
}