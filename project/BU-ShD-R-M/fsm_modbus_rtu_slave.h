
#ifndef FSM_MODBUS_RTU_SLAVE_H_
#define FSM_MODBUS_RTU_SLAVE_H_

#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include "hal_adm2483brw.h"
#include "protocol_bu_sh_d_r_m_modbus.h"
#include "protocol_modbus_crc.h"
#include "protocol_bu_sh_d_r_m_dubna.h"
#include "protocol_dubna_cr.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#ifndef MODBUS_SURVEY_PERIOD_MS
#define MODBUS_SURVEY_PERIOD_MS							500					
#endif /* MODBUS_SURVEY_PERIOD_MS */

#ifndef BU_SH_D_R_M
#define BU_SH_D_R_M										5
#endif /* BU_SH_D_R_M */

#ifndef MODBUS_STATUS_IDLE
#define MODBUS_STATUS_IDLE								0
#endif /* MODBUS_STATUS_IDLE */

#ifndef MODBUS_STATUS_RECIEVING_DATA
#define MODBUS_STATUS_RECIEVING_DATA					1
#endif /* MODBUS_STATUS_RECIEVING_DATA */

#ifndef MODBUS_STATUS_AWAITING_TO_TRANCIEVE_DATA
#define MODBUS_STATUS_AWAITING_TO_TRANCIEVE_DATA		2
#endif /* MODBUS_STATUS_AWAITING_TO_TRANCIEVE_DATA */

#ifndef MODBUS_STATUS_TRANCIEVING_DATA
#define MODBUS_STATUS_TRANCIEVING_DATA					3
#endif /* MODBUS_STATUS_TRANCIEVING_DATA */

#ifndef MODBUS_STATUS_TRANCIEVING_FINISHED
#define MODBUS_STATUS_TRANCIEVING_FINISHED				4
#endif /* MODBUS_STATUS_TRANCIEVING_FINISHED */

#ifndef	MODBUS_TX_MAX_SYMBOLS
#define MODBUS_TX_MAX_SYMBOLS							33
#endif /* MODBUS_TX_MAX_SYMBOLS */

#ifndef	MODBUS_RX_MAX_SYMBOLS
#define MODBUS_RX_MAX_SYMBOLS							8
#endif /* MODBUS_RX_MAX_SYMBOLS */

#ifndef MODBUS_BAUDRATE_9600
#define MODBUS_BAUDRATE_9600 0U
#endif /* MODBUS_BAUDRATE_9600 */

#ifndef MODBUS_BAUDRATE_19200
#define MODBUS_BAUDRATE_19200							1U
#endif /* MODBUS_BAUDRATE_19200 */

#ifndef MODBUS_BAUDRATE_38400
#define MODBUS_BAUDRATE_38400							2U
#endif /* MODBUS_BAUDRATE_38400 */

#ifndef MODBUS_BAUDRATE_57600
#define MODBUS_BAUDRATE_57600							3U
#endif /* MODBUS_BAUDRATE_57600 */

#ifndef MODBUS_BAUDRATE_115200
#define MODBUS_BAUDRATE_115200							4U
#endif /* MODBUS_BAUDRATE_57600 */

#ifndef	DUBNA_TX_MAX_SYMBOLS
#define DUBNA_TX_MAX_SYMBOLS							49
#endif /* DUBNA_TX_MAX_SYMBOLS */

#ifndef	DUBNA_RX_MAX_SYMBOLS
#define DUBNA_RX_MAX_SYMBOLS							15
#endif /* DUBNA_RX_MAX_SYMBOLS */

#ifndef PROT_TYPE_MODBUS
#define PROT_TYPE_MODBUS								0U
#endif /* PROT_TYPE_MODBUS */

#ifndef PROT_TYPE_DUBNA
#define PROT_TYPE_DUBNA									1U
#endif /* PROT_TYPE_DUBNA */

#ifndef ASCII_TO_INT_DIFFERENTIAL
#define ASCII_TO_INT_DIFFERENTIAL						48U
#endif /* ASCII_TO_INT_DIFFERENTIAL */

void fsm_modbus_rtu_init(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m, uint16_t baudrate, uint8_t transmitter_enable_pin, volatile uint8_t * transmitter_enable_port, uint32_t f_cpu);
void fsm_modbus_rtu_process(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m);
uint32_t fsm_modbus_rtu_calculate_baud(uint8_t baud);

#endif /* FSM_MODBUS_RTU_SLAVE_H_ */