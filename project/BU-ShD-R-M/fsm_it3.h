/*!
\file
\defgroup fsm_it3
\brief Заголовочный файл fsm_it3.h

*/

#ifndef FSM_IT3_H_
#define FSM_IT3_H_

#include <stdio.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "hal_adm2483brw.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#define IT3_SYNC						0x16
#define IT3_LEN_ASK						0x03
#define IT3_LEN_RESP_INIT				0x04
#define IT3_LEN_RESP_TEMP				0x06
#define IT3_NUM							0x00
#define IT3_COMMAND_TYPE_INIT			0x00
#define IT3_COMMAND_TYPE_READ_TEMP		0xC3
#define IT3_RESP_TYPE_ERRORS			0x80
#define IT3_RESP_TYPE_INIT				0x85

#define IT3_STATUS_INITIALIZING				0
#define IT3_STATUS_IDLE						1
#define IT3_STATUS_TRANCIEVING				2
#define IT3_STATUS_TRANCIEVING_FINISHED		3
#define IT3_STATUS_RECIEVING				4
#define IT3_TX_MAX_LENGTH					9
#define IT3_RX_INIT_MAX_LENGTH				20
#define IT3_RX_TEMP_MAX_LENGTH				22
#define IT3_TIMER_SURVEY_PERIOD				1500
#define IT3_COMMUNICATION_ERROR_MAX_COUNT	5
#define IT3_BAUD_SPEED						4800

#define IT3_DOT_POSITION_BIT				3
#define IT3_00_DOT_FORMAT					1
#define IT3_0_DOT_FORMAT					0

void fsm_it3_init(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m, uint8_t transmitter_enable_pin, volatile uint8_t * transmitter_enable_port, uint32_t f_cpu);
void fsm_it3_process(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m);


#endif /* FSM_IT3_H_ */