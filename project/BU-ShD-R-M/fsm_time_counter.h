#ifndef FSM_TIME_COUNTER_H_
#define FSM_TIME_COUNTER_H_

#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef FSM_TIME_COUTER_STATUS_NOT_COUNTING
#define FSM_TIME_COUTER_STATUS_NOT_COUNTING 0U
#endif /* FSM_TIME_COUTER_STATUS_NOT_COUNTING */

#ifndef FSM_TIME_COUTER_STATUS_COUNTING
#define FSM_TIME_COUTER_STATUS_COUNTING 1U
#endif /* FSM_TIME_COUTER_STATUS_COUNTING */

#ifndef FSM_TIME_COUNTER_MAX_VALUE_H10
#define FSM_TIME_COUNTER_MAX_VALUE_H10 9999UL
#endif /* FSM_TIME_COUNTER_MAX_VALUE_H10 */

#ifndef FSM_TIME_COUTER_UPDATE_PERIOD_MINUTE
#define FSM_TIME_COUTER_UPDATE_PERIOD_MINUTE 6U
#endif /* FSM_TIME_COUTER_UPDATE_PERIOD_MINUTE */

#ifndef FSM_TIME_COUTER_SURVEY_PERIOD_MS
#define FSM_TIME_COUTER_SURVEY_PERIOD_MS 2000UL
#endif /* FSM_TIME_COUTER_SURVEY_PERIOD_MS */

void fsm_time_counter_init(void);
void fsm_time_counter_process(struct bu_shd_r_m_data * bu_shd_r_m, uint8_t * current_minute);


#endif /* FSM_TIME_COUNTER_H_ */