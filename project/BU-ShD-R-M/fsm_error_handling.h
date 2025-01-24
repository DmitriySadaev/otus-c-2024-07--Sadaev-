/*!
\file
\defgroup fsm_error_handling
\brief Заголовочный файл fsm_error_handling.h

*/

#ifndef FSM_ERROR_HANDLING_H_
#define FSM_ERROR_HANDLING_H_

#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#ifndef ADSORBER_CHECK_TIMECUT
#define ADSORBER_CHECK_TIMECUT 3000U
#endif /* ADSORBER_CHECK_TIMECUT */

void fsm_error_handler_init(void);
uint8_t fsm_check_errors_to_turn_off_bko_ku(struct bu_shd_r_m_data * bu_shd_r_m);
void fsm_error_handler_process(struct bu_shd_r_m_data * bu_shd_r_m);

#endif /* FSM_ERROR_HANDLING_H_ */