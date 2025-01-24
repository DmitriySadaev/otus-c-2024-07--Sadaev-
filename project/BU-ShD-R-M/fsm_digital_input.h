/*!
\file
\defgroup fsm_digital_input
\brief Заголовочный файл fsm_digital_input.h

*/


#ifndef FSM_DIGITAL_INPUT_H_
#define FSM_DIGITAL_INPUT_H_

#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#ifndef FSM_DIGITAL_INPUT_SURVEY_PERIOD_MS
#define FSM_DIGITAL_INPUT_SURVEY_PERIOD_MS 2000U
#endif /* FSM_DIGITAL_INPUT_SURVEY_PERIOD_MS */

#define FSM_DIGITAL_INPUT_BKO1_START		0U
#define FSM_DIGITAL_INPUT_BKO1_STOP			1U
#define FSM_DIGITAL_INPUT_BKO2_START		2U
#define FSM_DIGITAL_INPUT_BKO2_STOP			3U
#define FSM_DIGITAL_INPUT_REG1_START		4U
#define FSM_DIGITAL_INPUT_REG1_STOP			5U
#define FSM_DIGITAL_INPUT_REG2_START		6U
#define FSM_DIGITAL_INPUT_REG2_STOP			7U
#define FSM_DIGITAL_INPUT_ENTER				8U
#define FSM_DIGITAL_INPUT_RIGHT				9U
#define FSM_DIGITAL_INPUT_LEFT				10U
#define FSM_DIGITAL_INPUT_ESC				11U
#define FSM_DIGITAL_PHASE_A					12U
#define FSM_DIGITAL_PHASE_B					13U
#define FSM_DIGITAL_PHASE_C					14U

void fsm_digital_input_init(void);
void fsm_digital_input_process(struct bu_shd_r_m_data * bu_shd_r_m);

#endif /* FSM_DIGITAL_INPUT_H_ */