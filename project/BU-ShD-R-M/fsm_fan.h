<<<<<<< HEAD
/*!
\file
\defgroup fsm_fan
\brief Заголовочный файл fsm_fan.h

*/

#ifndef FSM_FAN_H_
#define FSM_FAN_H_

#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#ifndef FSM_FAN_IDLE
#define FSM_FAN_IDLE 0U
#endif /* FSM_FAN_IDLE */

#ifndef FSM_FAN_WORKING
#define FSM_FAN_WORKING 1U
#endif /* FSM_FAN_WORKING */

#ifndef FSM_FAN_HYSTERESIS
#define FSM_FAN_HYSTERESIS 10
#endif /* FSM_FAN_HYSTERESIS */

#ifndef FSM_FAN_SURVEY_PERIOD_MS
#define FSM_FAN_SURVEY_PERIOD_MS 2000
#endif /* FSM_FAN_SURVEY_PERIOD_MS */

struct fan_data
{
	uint8_t fan_pin;
	volatile uint8_t * fan_port;
};

void fsm_fan_init(struct fan_data * fan, uint8_t fan_pin, volatile uint8_t * fan_port);
void fsm_fan_process(struct fan_data * fan, struct bu_shd_r_m_data * bu_shd_r_m);

=======
/*!
\file
\defgroup fsm_fan
\brief Заголовочный файл fsm_fan.h

*/

#ifndef FSM_FAN_H_
#define FSM_FAN_H_

#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#ifndef FSM_FAN_IDLE
#define FSM_FAN_IDLE 0U
#endif /* FSM_FAN_IDLE */

#ifndef FSM_FAN_WORKING
#define FSM_FAN_WORKING 1U
#endif /* FSM_FAN_WORKING */

#ifndef FSM_FAN_HYSTERESIS
#define FSM_FAN_HYSTERESIS 10
#endif /* FSM_FAN_HYSTERESIS */

#ifndef FSM_FAN_SURVEY_PERIOD_MS
#define FSM_FAN_SURVEY_PERIOD_MS 2000
#endif /* FSM_FAN_SURVEY_PERIOD_MS */

struct fan_data
{
	uint8_t fan_pin;
	volatile uint8_t * fan_port;
};

void fsm_fan_init(struct fan_data * fan, uint8_t fan_pin, volatile uint8_t * fan_port);
void fsm_fan_process(struct fan_data * fan, struct bu_shd_r_m_data * bu_shd_r_m);

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* FSM_FAN_H_ */