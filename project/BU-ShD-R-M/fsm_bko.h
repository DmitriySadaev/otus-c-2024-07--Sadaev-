/*!
\file
\defgroup fsm_bko
\brief Заголовочный файл fsm_bko.h

*/

#ifndef FSM_BKO_H_
#define FSM_BKO_H_

#include <stdint.h>
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "fsm_error_handling.h"
#include "hal_dm542.h"
#include "BU-ShD-R-M_struct.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef FSM_BKO_SURVEY_PERIOD_MS
#define FSM_BKO_SURVEY_PERIOD_MS 1000U
#endif /* FSM_BKO_SURVEY_PERIOD_MS */

#ifndef FSM_BKO_STOP_PERIOD_MS
#define FSM_BKO_STOP_PERIOD_MS 60000
#endif /* FSM_BKO_STOP_PERIOD_MS */

#ifndef FSM_BKO_STATUS_OFF
#define FSM_BKO_STATUS_OFF 0U
#endif /* FSM_BKO_STATUS_OFF */

#ifndef FSM_BKO_STATUS_POWERED
#define FSM_BKO_STATUS_POWERED 1U
#endif /* FSM_BKO_STATUS_POWERED */

#ifndef FSM_BKO_STATUS_ON
#define FSM_BKO_STATUS_ON 2U
#endif /* FSM_BKO_STATUS_ON */

#ifndef FSM_BKO_STATUS_ON_CURRENT_STABILIZED
#define FSM_BKO_STATUS_ON_CURRENT_STABILIZED 3U
#endif /* FSM_BKO_STATUS_ON_CURRENT_STABILIZED */

#ifndef FSM_BKO_STATUS_STOPPING
#define FSM_BKO_STATUS_STOPPING 4U
#endif /* FSM_BKO_STATUS_STOPPING */

#ifndef FSM_BKO_LOW_SPEED_ACTIVE_TEMPERARTURE_GRAD
#define FSM_BKO_LOW_SPEED_ACTIVE_TEMPERARTURE_GRAD 20
#endif /* FSM_BKO_LOW_SPEED_ACTIVE_TEMPERARTURE_GRAD */

#ifndef FSM_BKO_BREAK_SETPOINT
#define FSM_BKO_BREAK_SETPOINT 20U
#endif /* FSM_BKO_BREAK_SETPOINT */

#ifndef FSM_BKO_SHORT_SETPOINT
#define FSM_BKO_SHORT_SETPOINT 200U
#endif /* FSM_BKO_SHORT_SETPOINT */

#ifndef FSM_BKO_BREAK_SHORT_MAX_COUNT
#define FSM_BKO_BREAK_SHORT_MAX_COUNT 5U
#endif /* FSM_BKO_BREAK_SHORT_MAX_COUNT */

void fsm_bko_init(struct dm542_driver_data * dm542_driver, uint8_t dm542_control_pul_pin, uint8_t dm542_control_ena_pin, volatile uint8_t * dm542_control_port, uint8_t dm542_power_drv_pin, volatile uint8_t * dm542_power_drv_port, uint8_t dm542_connection_check_pin, volatile uint8_t * dm542_connection_check_port, uint32_t f_cpu);
void fsm_bko_process(struct bu_shd_r_m_data * bu_shd_r_m, struct dm542_driver_data * dm542_driver);

#endif /* FSM_BKO_H_ */

