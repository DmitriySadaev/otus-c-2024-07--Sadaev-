/*!
\file
\defgroup fsm_clock
\brief Заголовочный файл fsm_clock.h

*/

#ifndef FSM_CLOCK_H_
#define FSM_CLOCK_H_

#include "hal_ds1302.h"
#include "fsm_virtual_timers.h"

#ifndef FSM_CLOCK_SURVEY_PERIOD_MS
#define FSM_CLOCK_SURVEY_PERIOD_MS 1000
#endif /* FSM_CLOCK_SURVEY_PERIOD_MS */

void fsm_clock_init(struct ds1302_data * time);
void fsm_clock_process(struct ds1302_data * time);

#endif /* FSM_CLOCK_H_ */