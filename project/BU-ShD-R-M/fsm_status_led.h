/*!
\file
\defgroup fsm_status_led
\brief Заголовочный файл fsm_status_led.h

*/

#ifndef FSM_STATUS_LED_H_
#define FSM_STATUS_LED_H_

#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "hal_status_led.h"

#ifndef FSM_STATUS_LED_PERIOD_MS
#define FSM_STATUS_LED_PERIOD_MS 1000
#endif /* FSM_STATUS_LED_PERIOD_MS */

void fsm_status_led_init (struct status_led_data * status_led, uint8_t status_led_pin, volatile uint8_t * status_led_port);
void fsm_status_led_process (struct status_led_data * status_led);

#endif /* FSM_STATUS_LED_H_ */