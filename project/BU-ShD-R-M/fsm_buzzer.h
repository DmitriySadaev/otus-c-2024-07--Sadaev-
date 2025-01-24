/*!
\file
\defgroup fsm_buzzer
\brief Заголовочный файл fsm_buzzer.h

*/

#ifndef FSM_BUZZER_H_
#define FSM_BUZZER_H_

#include "hal_buzzer.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"

#ifndef FSM_BUZZER_SURVEY_PERIOD
#define FSM_BUZZER_SURVEY_PERIOD 10U
#endif /* FSM_BUZZER_SURVEY_PERIOD */

#ifndef FSM_BUZZER_SOUND_GENERATION_PERIOD_MS
#define FSM_BUZZER_SOUND_GENERATION_PERIOD_MS 10U
#endif /* FSM_BUZZER_SOUND_GENERATION_PERIOD_MS */

void fsm_buzzer_init (struct buzzer_data * buzzer, uint32_t duty_cycle, uint8_t period, uint8_t buzzer_pin, volatile uint8_t * buzzer_port);
void fsm_buzzer_process (struct buzzer_data * buzzer, uint8_t buzzer_work_enable);

#endif /* FSM_BUZZER_H_ */