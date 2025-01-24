/*!
\file
\defgroup fsm_led_vector
\brief Заголовочный файл fsm_led_vector.h

*/

#ifndef FSM_LED_VECTOR_H_
#define FSM_LED_VECTOR_H_

#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "hal_cd54ac164.h"
#include "BU-ShD-R-M_struct.h"

#ifndef FSM_LED_OFF
#define FSM_LED_OFF 0U
#endif /* FSM_LED_OFF */

#ifndef FSM_LED_ON
#define FSM_LED_ON 1U
#endif /* FSM_LED_ON */

#ifndef FSM_LED_BLINKING
#define FSM_LED_BLINKING 2U
#endif /* FSM_LED_BLINKING */

#ifndef LED_BKO2_ADDRESS
#define LED_SHD_RM_ADDRESS 0U
#endif /* LED_BKO2_ADDRESS */

#ifndef LED_BKO1_ADDRESS
#define LED_BKO1_ADDRESS 1U
#endif /* LED_BKO1_ADDRESS */

#ifndef LED_KU_ADDRESS
#define LED_KU_ADDRESS 2U
#endif /* LED_KU_ADDRESS */

#ifndef LED_REGEN2_ADDRESS
#define LED_REGEN2_ADDRESS 3U
#endif /* LED_REGEN2_ADDRESS */

#ifndef LED_REGEN1_ADDRESS
#define LED_REGEN1_ADDRESS 4U
#endif /* LED_REGEN1_ADDRESS */

#ifndef LED_PHASE_SEQ_ADDRESS
#define LED_PHASE_SEQ_ADDRESS 5U
#endif /* LED_PHASE_SEQ_ADDRESS */

#ifndef LED_OVERHEAT_T2_ADDRESS
#define LED_OVERHEAT_T2_ADDRESS 6U
#endif /* LED_OVERHEAT_T2_ADDRESS */

#ifndef LED_OVERHEAT_T1_ADDRESS
#define LED_OVERHEAT_T1_ADDRESS 7U
#endif /* LED_OVERHEAT_T1_ADDRESS */

#ifndef FSM_LED_BLINK_HALF_PERIOD_MS
#define FSM_LED_BLINK_HALF_PERIOD_MS 500
#endif /* FSM_STATUS_LED_PERIOD_MS */

void fsm_led_vector_init(void);
void fsm_led_vector_process(struct bu_shd_r_m_data * bu_shd_r_m);

#endif /* FSM_LED_VECTOR_H_ */