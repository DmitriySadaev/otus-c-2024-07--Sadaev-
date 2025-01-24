/*! 
  \file
  \defgroup		fsm_archive
  \brief		Файл исходного кода программы fsm_archive.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) архива событий
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_archive.h"

uint8_t fsm_archive_status;
uint8_t fsm_archive_message_to_be_written;

extern uint8_t EEMEM archive_starting_record;

void fsm_archive_init(void)
{
	fsm_archive_status = FSM_ARCHIVE_WAITING_TIMEOUT;
	virtual_timers_timer_reset(ARCHIVE_TIMER);
}

uint8_t fsm_archive_check_recieved_message_to_be_written(void)
{
	uint8_t result = FALSE; 
	
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_OL))				{result = MSG_KEY_PRESSED_OL;}
	if (fsm_messages_get_broadcast_message(MSG_INNER_T_SENSOR_SHORT))		{result = MSG_INNER_T_SENSOR_SHORT;}
	if (fsm_messages_get_broadcast_message(MSG_INNER_T_SENSOR_BREAK))		{result = MSG_INNER_T_SENSOR_BREAK;}
	if (fsm_messages_get_broadcast_message(MSG_FAN_IS_TURNED_ON))			{result = MSG_FAN_IS_TURNED_ON;}
	if (fsm_messages_get_broadcast_message(MSG_FAN_IS_TURNED_OFF))			{result = MSG_FAN_IS_TURNED_OFF;}
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_STARTED))				{result = MSG_REGEN1_STARTED;}
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_STOPPED))				{result = MSG_REGEN1_STOPPED;}
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_FINISHED))			{result = MSG_REGEN1_FINISHED;}
	if (fsm_messages_get_broadcast_message(MSG_WRONG_PHASE_SEQUENCE))		{result = MSG_WRONG_PHASE_SEQUENCE;}
	if (fsm_messages_get_broadcast_message(MSG_T1_OVERHEAT))				{result = MSG_T1_OVERHEAT;}
	if (fsm_messages_get_broadcast_message(MSG_T2_OVERHEAT))				{result = MSG_T2_OVERHEAT;}
	if (fsm_messages_get_broadcast_message(MSG_T1_SHORT))					{result = MSG_T1_SHORT;}
	if (fsm_messages_get_broadcast_message(MSG_T1_BREAK))					{result = MSG_T1_BREAK;}
	if (fsm_messages_get_broadcast_message(MSG_T2_SHORT))					{result = MSG_T2_SHORT;}
	if (fsm_messages_get_broadcast_message(MSG_T2_BREAK))					{result = MSG_T2_BREAK;}
	if (fsm_messages_get_broadcast_message(MSG_HEATER_SHORT))				{result = MSG_HEATER_SHORT;}
	if (fsm_messages_get_broadcast_message(MSG_HEATER_BREAK))				{result = MSG_HEATER_BREAK;}
	if (fsm_messages_get_broadcast_message(MSG_STEPPER_BREAK))				{result = MSG_STEPPER_BREAK;}
	if (fsm_messages_get_broadcast_message(MSG_BKO_STARTED))				{result = MSG_BKO_STARTED;}
	if (fsm_messages_get_broadcast_message(MSG_BKO_STOPPED))				{result = MSG_BKO_STOPPED;}
	if (fsm_messages_get_broadcast_message(MSG_IT3_NO_CONNECTION))			{result = MSG_IT3_NO_CONNECTION;}
	if (fsm_messages_get_broadcast_message(MSG_BKO_SENSOR_SHORT))			{result = MSG_BKO_SENSOR_SHORT;}
	if (fsm_messages_get_broadcast_message(MSG_BKO_SENSOR_BREAK))			{result = MSG_BKO_SENSOR_BREAK;}
	if (fsm_messages_get_broadcast_message(MSG_ADSORBER_LIMIT))				{result = MSG_ADSORBER_LIMIT;}
	if (fsm_messages_get_broadcast_message(MSG_BKO_OVERLOAD))				{result = MSG_BKO_OVERLOAD;}	
	
	return result;
}

void fsm_archive_write_new_record(struct archive_record * bu_shd_r_m_archive, struct ds1302_data * time, struct bu_shd_r_m_data * bu_shd_r_m)
{
	struct archive_record temp_record;
		
	temp_record.date = (uint8_t)time->date;
	temp_record.hour = (uint8_t)time->hour;
	temp_record.minute = (uint8_t)time->minute;
	temp_record.month = (uint8_t)time->month;
	temp_record.year = (uint8_t)time->year;
	temp_record.message = fsm_archive_message_to_be_written;	
		
	eeprom_write_block((const void*)&temp_record, (void*)(bu_shd_r_m_archive+ bu_shd_r_m->archive_starting_record), 6);
}

uint8_t fsm_archive_check_record_to_be_written_is_new(struct archive_record * bu_shd_r_m_archive, struct ds1302_data * time, struct bu_shd_r_m_data * bu_shd_r_m)
{
		struct archive_record temp_record;
		struct archive_record current_record;
		
		temp_record.date = (uint8_t)time->date;
		temp_record.hour = (uint8_t)time->hour;
		temp_record.minute = (uint8_t)time->minute;
		temp_record.month = (uint8_t)time->month;
		temp_record.year = (uint8_t)time->year;
		temp_record.message = fsm_archive_message_to_be_written;
		
		eeprom_read_block((void*)&current_record, (const void*)(bu_shd_r_m_archive+bu_shd_r_m->archive_starting_record), 6);
		
		do 
		{
			if (temp_record.date != current_record.date) {return TRUE; break;}
			if (temp_record.hour != current_record.hour) {return TRUE; break;}
			if (temp_record.minute != current_record.minute) {return TRUE; break;}
			if (temp_record.month != current_record.month) {return TRUE; break;}
			if (temp_record.year != current_record.year) {return TRUE; break;}
			if (temp_record.message != current_record.message) {return TRUE; break;}
			return FALSE;
			
		} while (0);
} 

void fsm_archive_shift_to_a_new_starting_record_position(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (bu_shd_r_m->archive_starting_record > 0)
	{
		bu_shd_r_m->archive_starting_record --;
	}
	else
	{
		bu_shd_r_m->archive_starting_record = FSM_ARCHIVE_SIZE-1;
	}
}

void fsm_archive_process(struct archive_record * bu_shd_r_m_archive, struct bu_shd_r_m_data * bu_shd_r_m, struct ds1302_data * time)
{
	switch(fsm_archive_status)
	{
		case FSM_ARCHIVE_READY:
		{
			if(fsm_archive_check_recieved_message_to_be_written())
			{
				fsm_archive_message_to_be_written = fsm_archive_check_recieved_message_to_be_written();
				fsm_archive_status = FSM_ARCHIVE_UPDATING;
			}
			break;
		}
		case FSM_ARCHIVE_UPDATING:
		{
			if (fsm_archive_check_record_to_be_written_is_new(bu_shd_r_m_archive, time, bu_shd_r_m))
			{
				fsm_archive_shift_to_a_new_starting_record_position(bu_shd_r_m);
				fsm_archive_write_new_record(bu_shd_r_m_archive, time, bu_shd_r_m);
				eeprom_write_byte(&archive_starting_record, bu_shd_r_m->archive_starting_record);
				fsm_archive_status = FSM_ARCHIVE_WAITING_TIMEOUT;				
			}
			else 
			{
				fsm_archive_status = FSM_ARCHIVE_WAITING_TIMEOUT;
			}
			break;	
		}
		case FSM_ARCHIVE_WAITING_TIMEOUT:
		{
			if (virtual_timers_timer_get(ARCHIVE_TIMER) >= FSM_ARCHIVE_TIMEOUT_MS)
			{
				fsm_archive_status = FSM_ARCHIVE_READY;
			}
			break;
		}
	}
	if (virtual_timers_timer_get(ARCHIVE_TIMER) >= FSM_ARCHIVE_TIMEOUT_MS)
	{
		virtual_timers_timer_reset(ARCHIVE_TIMER);
	}
}
