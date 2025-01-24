<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_fan
  \brief		Файл исходного кода программы fsm_fan.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) вентилятора
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_fan.h"

uint8_t fan_status;

void fsm_fan_init_struct(struct fan_data * fan,  uint8_t fan_pin, volatile uint8_t * fan_port)
{
	fan->fan_pin = fan_pin;
	fan->fan_port = fan_port;
}

void fsm_fan_init_ddr(struct fan_data * fan)
{
	* (fan->fan_port  -1)	|= (1 << fan->fan_pin); //из адреса регистра PORT получаем адрес регистра DDR
}

void fsm_fan_turn_off(struct fan_data * fan)
{
	* fan->fan_port |= (1 << fan->fan_pin);
}

void fsm_fan_turn_on(struct fan_data * fan)
{
	* fan->fan_port &= ~(1 << fan->fan_pin);
}

void fsm_fan_init(struct fan_data * fan, uint8_t fan_pin, volatile uint8_t * fan_port)
{
    fsm_fan_init_struct(fan, fan_pin, fan_port);
	fsm_fan_init_ddr(fan);
	fsm_fan_turn_off(fan);
	virtual_timers_timer_reset(FAN_TIMER);
}

void fsm_fan_process(struct fan_data * fan, struct bu_shd_r_m_data * bu_shd_r_m)
{
	switch (fan_status)
	{
		case FSM_FAN_IDLE:
		{
			if (bu_shd_r_m->inner_temperature_grad10 > bu_shd_r_m->inner_temperature_setting_grad10)
			{
				fan_status = FSM_FAN_WORKING;
				fsm_messages_send_broadcast_message(MSG_FAN_IS_TURNED_ON);
				bu_shd_r_m->system_flags |= (1 << SYSTEM_FAN);
			}
			break;
		}
		case FSM_FAN_WORKING:
		{
			if (bu_shd_r_m->inner_temperature_grad10 < (bu_shd_r_m->inner_temperature_setting_grad10 - FSM_FAN_HYSTERESIS))
			{
				fan_status = FSM_FAN_IDLE;
				fsm_messages_send_broadcast_message(MSG_FAN_IS_TURNED_OFF);
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_FAN);
			}
			break;
		}
	}		
	if (virtual_timers_timer_get(FAN_TIMER) >= FSM_FAN_SURVEY_PERIOD_MS)
	{
		switch (fan_status)
		{
			case FSM_FAN_IDLE:
			{
				fsm_fan_turn_off(fan);
				break;
			}
			case FSM_FAN_WORKING:
			{
				fsm_fan_turn_on(fan);
				break;
			}	
		}
		virtual_timers_timer_reset(FAN_TIMER);
	}	
=======
/*! 
  \file
  \defgroup		fsm_fan
  \brief		Файл исходного кода программы fsm_fan.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) вентилятора
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_fan.h"

uint8_t fan_status;

void fsm_fan_init_struct(struct fan_data * fan,  uint8_t fan_pin, volatile uint8_t * fan_port)
{
	fan->fan_pin = fan_pin;
	fan->fan_port = fan_port;
}

void fsm_fan_init_ddr(struct fan_data * fan)
{
	* (fan->fan_port  -1)	|= (1 << fan->fan_pin); //из адреса регистра PORT получаем адрес регистра DDR
}

void fsm_fan_turn_off(struct fan_data * fan)
{
	* fan->fan_port |= (1 << fan->fan_pin);
}

void fsm_fan_turn_on(struct fan_data * fan)
{
	* fan->fan_port &= ~(1 << fan->fan_pin);
}

void fsm_fan_init(struct fan_data * fan, uint8_t fan_pin, volatile uint8_t * fan_port)
{
    fsm_fan_init_struct(fan, fan_pin, fan_port);
	fsm_fan_init_ddr(fan);
	fsm_fan_turn_off(fan);
	virtual_timers_timer_reset(FAN_TIMER);
}

void fsm_fan_process(struct fan_data * fan, struct bu_shd_r_m_data * bu_shd_r_m)
{
	switch (fan_status)
	{
		case FSM_FAN_IDLE:
		{
			if (bu_shd_r_m->inner_temperature_grad10 > bu_shd_r_m->inner_temperature_setting_grad10)
			{
				fan_status = FSM_FAN_WORKING;
				fsm_messages_send_broadcast_message(MSG_FAN_IS_TURNED_ON);
				bu_shd_r_m->system_flags |= (1 << SYSTEM_FAN);
			}
			break;
		}
		case FSM_FAN_WORKING:
		{
			if (bu_shd_r_m->inner_temperature_grad10 < (bu_shd_r_m->inner_temperature_setting_grad10 - FSM_FAN_HYSTERESIS))
			{
				fan_status = FSM_FAN_IDLE;
				fsm_messages_send_broadcast_message(MSG_FAN_IS_TURNED_OFF);
				bu_shd_r_m->system_flags &= ~(1 << SYSTEM_FAN);
			}
			break;
		}
	}		
	if (virtual_timers_timer_get(FAN_TIMER) >= FSM_FAN_SURVEY_PERIOD_MS)
	{
		switch (fan_status)
		{
			case FSM_FAN_IDLE:
			{
				fsm_fan_turn_off(fan);
				break;
			}
			case FSM_FAN_WORKING:
			{
				fsm_fan_turn_on(fan);
				break;
			}	
		}
		virtual_timers_timer_reset(FAN_TIMER);
	}	
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
}