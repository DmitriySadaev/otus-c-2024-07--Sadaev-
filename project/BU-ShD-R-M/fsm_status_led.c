<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_status_led
  \brief		Файл исходного кода программы fsm_status_led.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) статусного светодиода
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_status_led.h"

void fsm_status_led_init (struct status_led_data * status_led, uint8_t status_led_pin, volatile uint8_t * status_led_port)
{
	hal_status_led_init(status_led, status_led_pin, status_led_port);
	virtual_timers_timer_reset(STATUS_LED_TIMER);
}

void fsm_status_led_process (struct status_led_data * status_led)
{
	if (virtual_timers_timer_get(STATUS_LED_TIMER) >= FSM_STATUS_LED_PERIOD_MS)
	{
		hal_status_led_toggle(status_led);
		virtual_timers_timer_reset(STATUS_LED_TIMER);	
	}
=======
/*! 
  \file
  \defgroup		fsm_status_led
  \brief		Файл исходного кода программы fsm_status_led.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) статусного светодиода
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_status_led.h"

void fsm_status_led_init (struct status_led_data * status_led, uint8_t status_led_pin, volatile uint8_t * status_led_port)
{
	hal_status_led_init(status_led, status_led_pin, status_led_port);
	virtual_timers_timer_reset(STATUS_LED_TIMER);
}

void fsm_status_led_process (struct status_led_data * status_led)
{
	if (virtual_timers_timer_get(STATUS_LED_TIMER) >= FSM_STATUS_LED_PERIOD_MS)
	{
		hal_status_led_toggle(status_led);
		virtual_timers_timer_reset(STATUS_LED_TIMER);	
	}
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
}