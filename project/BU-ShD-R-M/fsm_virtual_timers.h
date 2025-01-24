/*!
\file
\defgroup fsm_virtual_timers
\brief Заголовочный файл fsm_virtual_timers.h

*/

#ifndef FSM_VIRTUAL_TIMERS_H_
#define FSM_VIRTUAL_TIMERS_H_

#include <stdint.h>
#include "avr_driver_timers.h"

#define SEC 1000 // в одной секунде тысяча срабатываний прерываний F_CPU/timer_prescaler/compare_interrupt_value
#define MIN (60 * SEC)
#define HOUR (60 * MIN)
#define DAY (24 * HOUR)

#define KEYBOARD_TIMER			0U
#define LED_VECTOR_TIMER		1U
#define UI_TIMER				2U
#define BUZZER_TIMER			3U
#define STATUS_LED_TIMER		4U
#define INNER_SENSOR_TIMER		5U
#define FAN_TIMER				6U
#define KU_TIMER				7U
#define T1_TIMER				8U
#define T2_TIMER				9U
#define VOLTAGE_SENSOR_TIMER	10U
#define BKO_SENSOR_TIMER		11U
#define REGENERATOR_TIMER		12U
#define BKO_TIMER				13U
#define CURRENT_SENSOR_TIMER	14U
#define CLOCK_TIMER				15U
#define TIME_COUNTER_TIMER		16U
#define ARCHIVE_TIMER			17U
#define PHASE_CONTROLLER_TIMER	18U
#define DIGITAL_INPUT_TIMER		19U
#define DU_TIMER				20U
#define IT3_TIMER				21U
#define ADSORBER_CHECK_TIMER	22U		

#ifndef MAX_TIMERS
#define MAX_TIMERS 32 //количество таймеров
#endif /* MAX_TIMERS */

#ifndef MAX_GLOBAL_TIMERS
#define MAX_GLOBAL_TIMERS 32 //количество таймеров
#endif /* MAX_GLOBAL_TIMERS */

#ifndef TIMER_STOPPED
#define TIMER_STOPPED 0U //Таймер остановлен
#endif /* TIMER_STOPPED */

#ifndef TIMER_RUNNING
#define TIMER_RUNNING 1U //Таймер работает
#endif /* TIMER_RUNNING */

#ifndef TIMER_PAUSED
#define TIMER_PAUSED  2U //Таймер на паузе
#endif /* TIMER_PAUSED */

void virtual_timers_process(void);
void virtual_timers_init(uint16_t timer_prescaler, uint8_t compare_interrupt_value);
uint16_t virtual_timers_timer_get(uint8_t virtual_timer);
void virtual_timers_timer_reset(uint8_t virtual_timer);
void virtual_timers_global_timers_init(void);
void virtual_timers_global_timer_start(uint8_t global_timer_id);
void virtual_timers_global_timer_stop(uint8_t global_timer_id);
void virtual_timers_global_timer_pause(uint8_t global_timer_id);
void virtual_timers_global_timer_release(uint8_t global_timer_id);
uint16_t virtual_timers_global_timer_get(uint8_t global_timer_id);
void virtual_global_timers_process(void);

#endif /* FSM_VIRTUAL_TIMERS_H_ */