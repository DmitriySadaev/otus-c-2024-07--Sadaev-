/*!
\file
\defgroup fsm_keyboard
\brief Заголовочный файл fsm_keyboard.h

*/

#ifndef FSM_PHASE_CONTROLLER_H_
#define FSM_PHASE_CONTROLLER_H_

#include <stdint.h>
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#ifndef FSM_PHASE_CONTROLLER_SURVEY_PERIOD_MS
#define FSM_PHASE_CONTROLLER_SURVEY_PERIOD_MS 5000U
#endif /* FSM_PHASE_CONTROLLER_SURVEY_PERIOD_MS */

#ifndef FSM_PHASE_CONTROLLER_PHASE_CHECK_COUNT
#define FSM_PHASE_CONTROLLER_PHASE_CHECK_COUNT	1U
#endif /* FSM_PHASE_CONTROLLER_H_ */

#ifndef FSM_PHASE_CONTROLLER_POSITIVE_PHASE_SEQUENCE
#define FSM_PHASE_CONTROLLER_POSITIVE_PHASE_SEQUENCE	1U
#endif /* FSM_PHASE_CONTROLLER_POSITIVE_PHASE_SEQUENCE */

#ifndef FSM_PHASE_CONTROLLER_NEGATIVE_PHASE_SEQUENCE
#define FSM_PHASE_CONTROLLER_NEGATIVE_PHASE_SEQUENCE	0U
#endif /* FSM_PHASE_CONTROLLER_NEGATIVE_PHASE_SEQUENCE */


void fsm_phase_controller_init(void);
void fsm_phase_controller_process(struct bu_shd_r_m_data * bu_shd_r_m);


#endif /* FSM_PHASE_CONTROLLER_H_ */