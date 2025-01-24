/*!
\file
\defgroup fsm_regenerator
\brief Заголовочный файл fsm_regenerator.h

*/

#ifndef FSM_REGENERATOR_H_
#define FSM_REGENERATOR_H_

#include <stdint.h>
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"
#include "hal_heater.h"

#ifndef FSM_REGENERATOR_STATUS_OFF
#define FSM_REGENERATOR_STATUS_OFF 0U
#endif /* FSM_REGENERATOR_STATUS_OFF */

#ifndef FSM_REGENERATOR_STATUS_ON
#define FSM_REGENERATOR_STATUS_ON 1U
#endif /* FSM_REGENERATOR_STATUS_ON */

#ifndef FSM_REGENERATOR_STATUS_ON_CURRENT_STABILIZED
#define FSM_REGENERATOR_STATUS_ON_CURRENT_STABILIZED 2U
#endif /* FSM_REGENERATOR_STATUS_ON_CURRENT_STABILIZED */

#ifndef FSM_REGENERATOR_HEATER_BREAK_SETPOINT
#define FSM_REGENERATOR_HEATER_BREAK_SETPOINT 15U
#endif /* FSM_REGENERATOR_HEATER_BREAK_SETPOINT */

#ifndef FSM_REGENERATOR_HEATER_SHORT_SETPOINT
#define FSM_REGENERATOR_HEATER_SHORT_SETPOINT 250U
#endif /* FSM_REGENERATOR_HEATER_SHORT_SETPOINT */

#ifndef FSM_REGENERATOR_SURVEY_PERIOD_MS
#define FSM_REGENERATOR_SURVEY_PERIOD_MS 1000U
#endif /* FSM_REGENERATOR_SURVEY_PERIOD_MS */

#ifndef FSM_REGENERATOR_TURN_OFF_SETPOINT_GRAD10
#define FSM_REGENERATOR_TURN_OFF_SETPOINT_GRAD10 3130
#endif /* FSM_REGENERATOR_TURN_OFF_SETPOINT_GRAD10 */

void fsm_regenerator_init(struct heater_data * heater, uint8_t voltage, uint8_t power_watt, uint8_t load_ohm, uint8_t heater_pin, volatile uint8_t * heater_port);
void fsm_regenerator_process(struct bu_shd_r_m_data * bu_shd_r_m, struct heater_data * heater);


#endif /* FSM_REGENERATOR_H_ */