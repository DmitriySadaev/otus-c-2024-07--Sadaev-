<<<<<<< HEAD
/*!
\file
\defgroup fsm_ku
\brief Заголовочный файл fsm_ku.h

*/

#ifndef FSM_KU_H_
#define FSM_KU_H_

#include <stdint.h>
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "fsm_error_handling.h"
#include "BU-ShD-R-M_struct.h"

#ifndef FSM_KU_SURVEY_PERIOD_MS
#define FSM_KU_SURVEY_PERIOD_MS 1000U
#endif /* FSM_KU_SURVEY_PERIOD_MS */

#ifndef FSM_KU_WAITING_START_BKO_TIMEOUT_MS
#define FSM_KU_WAITING_START_BKO_TIMEOUT_MS 4000U
#endif /* FSM_KU_WAITING_START_BKO_TIMEOUT_MS */

#ifndef FSM_KU_STATUS_OFF
#define FSM_KU_STATUS_OFF 0U
#endif /* FSM_KU_STATUS */

#ifndef FSM_KU_STATUS_WAITING_START_BKO
#define FSM_KU_STATUS_WAITING_START_BKO 1U
#endif /* FSM_KU_STATUS_WAITING_START_BKO */

#ifndef FSM_KU_STATUS_ON
#define FSM_KU_STATUS_ON 2U
#endif /* FSM_KU_STATUS_ON */

void fsm_ku_init(uint8_t pin, volatile uint8_t * port);
void fsm_ku_process(struct bu_shd_r_m_data * bu_shd_r_m);

=======
/*!
\file
\defgroup fsm_ku
\brief Заголовочный файл fsm_ku.h

*/

#ifndef FSM_KU_H_
#define FSM_KU_H_

#include <stdint.h>
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "fsm_error_handling.h"
#include "BU-ShD-R-M_struct.h"

#ifndef FSM_KU_SURVEY_PERIOD_MS
#define FSM_KU_SURVEY_PERIOD_MS 1000U
#endif /* FSM_KU_SURVEY_PERIOD_MS */

#ifndef FSM_KU_WAITING_START_BKO_TIMEOUT_MS
#define FSM_KU_WAITING_START_BKO_TIMEOUT_MS 4000U
#endif /* FSM_KU_WAITING_START_BKO_TIMEOUT_MS */

#ifndef FSM_KU_STATUS_OFF
#define FSM_KU_STATUS_OFF 0U
#endif /* FSM_KU_STATUS */

#ifndef FSM_KU_STATUS_WAITING_START_BKO
#define FSM_KU_STATUS_WAITING_START_BKO 1U
#endif /* FSM_KU_STATUS_WAITING_START_BKO */

#ifndef FSM_KU_STATUS_ON
#define FSM_KU_STATUS_ON 2U
#endif /* FSM_KU_STATUS_ON */

void fsm_ku_init(uint8_t pin, volatile uint8_t * port);
void fsm_ku_process(struct bu_shd_r_m_data * bu_shd_r_m);

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* FSM_KU_H_ */