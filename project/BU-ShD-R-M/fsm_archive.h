/*!
\file
\defgroup fsm_archive
\brief Заголовочный файл fsm_archive.h

*/

#ifndef FSM_ARCHIVE_H_
#define FSM_ARCHIVE_H_

#include <stdint.h>
#include <avr/eeprom.h>
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "hal_ds1302.h"
#include "BU-ShD-R-M_struct.h"

#ifndef FSM_ARCHIVE_READY 
#define FSM_ARCHIVE_READY 0U
#endif /* FSM_ARCHIVE_READY */

#ifndef FSM_ARCHIVE_UPDATING 
#define FSM_ARCHIVE_UPDATING 1U
#endif /* FSM_ARCHIVE_UPDATING */

#ifndef FSM_ARCHIVE_WAITING_TIMEOUT 
#define FSM_ARCHIVE_WAITING_TIMEOUT 2U
#endif /* FSM_ARCHIVE_WAITING_TIMEOUT */

#ifndef FSM_ARCHIVE_TIMEOUT_MS
#define FSM_ARCHIVE_TIMEOUT_MS	1000UL
#endif /* FSM_ARCHIVE_TIMEOUT_MS */

#ifndef FSM_ARCHIVE_SIZE 
#define FSM_ARCHIVE_SIZE 64U
#endif /* FSM_ARCHIVE_SIZE */


struct archive_record
{
	uint8_t message;
	uint8_t hour;
	uint8_t minute;
	uint8_t date;
	uint8_t month;
	uint8_t year;
};

void fsm_archive_init(void);
void fsm_archive_process(struct archive_record * bu_shd_r_m_archive, struct bu_shd_r_m_data * bu_shd_r_m, struct ds1302_data * time);

#endif /* FSM_ARCHIVE_H_ */