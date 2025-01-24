/*! 
  \file
  \defgroup		fsm_ui_bu_shd_r_m
  \brief		Файл исходного кода программы fsm_ui_bu_shd_r_m.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) интерфейса пользователя БУ-ШД-Р-М
 
  - Compiler:           GNU AVR toolchain       
*/

#include "fsm_ui_bu_shd_r_m.h"

uint8_t ui_page; 
uint8_t ui_previos_page;
uint8_t ui_archive_page;
uint8_t ui_cursor;
const uint8_t ui_cursor_max_position[9] = {0, 0, 5, 10, 3, 2, 5, 14, 0};
uint8_t ui_screen_shift;
uint8_t ui_last_message;
uint8_t cursor_mode;
uint8_t cursor_new_mode;
uint16_t displaying_password;
uint8_t temp_clock_data;

void fsm_ui_cursor_clear(void)
{
	for (uint8_t i = 0; i <=3; i++)
	{
		lcd_com(lcd_addr(0,i));
		lcd_string_direct_rus(" ");
	}
}

void fsm_ui_cursor_repaint(void)
{
	lcd_com(lcd_addr(0,ui_cursor%4));
	lcd_string_direct_rus(">");
}

uint8_t fsm_ui_cursor_check_is_exist_in_this_page(void)
{
	if (ui_cursor_max_position[ui_page] != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void fsm_ui_clear_screen(void)
{
	for (uint8_t i = 0; i <=3; i++)
	{
		lcd_com(lcd_addr(0,i));
		lcd_string_direct_rus("                    ");
	}
}

void fsm_ui_cursor_move(void)
{
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) & (ui_cursor >= 0) & (cursor_mode == UI_CURSOR_MOVING_MODE))
	{
		if (ui_cursor%4 == 0) 
		{
			if (ui_cursor == 0)
			{
				ui_cursor = 0;
			}
			else
			{
				ui_cursor--;
			}
			if (ui_screen_shift > 0)
			{
				ui_screen_shift--;
				fsm_ui_clear_screen();
			}
		}
		else
		{
			ui_cursor--;
		}	
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) & (ui_cursor <= (ui_cursor_max_position[ui_page] - 1)) & (cursor_mode == UI_CURSOR_MOVING_MODE))
	{
		if ((ui_cursor+1)%4 == 0)
		{
			if ((ui_screen_shift*4-1) <= ui_cursor_max_position[ui_page])
			{
				fsm_ui_clear_screen();
				ui_screen_shift++;
			}
		}
		ui_cursor++;
	}
}

void fsm_ui_cursor_process(void)
{
	if (fsm_ui_cursor_check_is_exist_in_this_page() == TRUE)
	{
		fsm_ui_cursor_move();
		if (virtual_timers_timer_get(UI_TIMER) >= UI_UPDATE_PERIOD_MS)
		{
			if (cursor_mode == UI_CURSOR_MOVING_MODE)
			{
				fsm_ui_cursor_clear();
				fsm_ui_cursor_repaint();
			}
			if (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE)
			{
				static uint8_t counter = 0;
				if (counter >= 0)
				{
				fsm_ui_cursor_clear();					
				}
				if (counter >= 3)
				{
					fsm_ui_cursor_repaint();
				}
				if (counter >= 6)
				{
					counter = 0;
				}
				counter++;
			}
		}
	}
}

void fsm_ui_page_move(struct bu_shd_r_m_data * bu_shd_r_m)
{
	static uint8_t page_just_been_moved = 0;
	if (!page_just_been_moved)
	{
		if (ui_page == UI_MENU_FORMULAR)
		{
			if ((ui_cursor == 0) && fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER) && (cursor_mode == UI_CURSOR_MOVING_MODE))
			{
				fsm_ui_clear_screen();
				ui_page = UI_SENSORS_FORMULAR;
				ui_previos_page = UI_MENU_FORMULAR;
			}
			if ((ui_cursor == 1) && fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER) && (cursor_mode == UI_CURSOR_MOVING_MODE))
			{
				ui_cursor = 0;
				fsm_ui_clear_screen();
				ui_page = UI_BKO_FORMULAR;
				ui_previos_page = UI_MENU_FORMULAR;
			}
			if ((ui_cursor == 2) && fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER) && (cursor_mode == UI_CURSOR_MOVING_MODE))
			{
				ui_cursor = 0;
				fsm_ui_clear_screen();
				ui_page = UI_DU_FORMULAR;
				ui_previos_page = UI_MENU_FORMULAR;
			}
			if ((ui_cursor == 3) && fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER) && (cursor_mode == UI_CURSOR_MOVING_MODE))
			{
				ui_cursor = 0;
				fsm_ui_clear_screen();
				ui_page = UI_TIME_FORMULAR;
				ui_previos_page = UI_MENU_FORMULAR;
			}
			if ((ui_cursor == 4) && fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER) && (cursor_mode == UI_CURSOR_MOVING_MODE))
			{
				ui_cursor = 0;
				ui_screen_shift = 0;
				fsm_ui_clear_screen();
				ui_page = UI_OTHERS_FORMULAR;
				ui_previos_page = UI_MENU_FORMULAR;
			}
			if ((ui_cursor == 5) && fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER) && (cursor_mode == UI_CURSOR_MOVING_MODE))
			{
				ui_cursor = 0;
				ui_archive_page = bu_shd_r_m->archive_starting_record;
				fsm_ui_clear_screen();
				ui_page = UI_ARCHIVE_FORMULAR;
				ui_previos_page = UI_MENU_FORMULAR;
			}
		}
		if (virtual_timers_timer_get(UI_TIMER) >= UI_INITIAL_SCREEN_TIME_MS)
		{
			fsm_ui_clear_screen();
			ui_page = UI_MAIN_FORMULAR;
		}
		if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER) && (ui_page == UI_MAIN_FORMULAR) &&  (bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE))
		{
			fsm_ui_clear_screen();
			ui_cursor = 0;
			ui_previos_page = ui_page;
			ui_page = UI_MENU_FORMULAR;
			page_just_been_moved = TRUE;
		}
		if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ESC) && (cursor_mode == UI_CURSOR_MOVING_MODE))
		{
			ui_cursor = 0;
			ui_screen_shift = 0;
			fsm_ui_clear_screen();
			if (ui_previos_page != ui_page)
			{
				ui_page = ui_previos_page;
			}
			else
			{
				ui_page = UI_MAIN_FORMULAR;
				ui_previos_page = UI_MAIN_FORMULAR;
			}
		}
		if (ui_page > UI_ARCHIVE_FORMULAR)
		{
			ui_page = UI_MAIN_FORMULAR;
		}
	}
	if ((virtual_timers_timer_get(UI_TIMER) >= UI_UPDATE_PERIOD_MS) && page_just_been_moved)
	{
		page_just_been_moved++;
	}
	if (page_just_been_moved >=5)
	{
		page_just_been_moved = 0;
	}	
}

uint8_t fsm_ui_cursor_is_able_to_enter_changing_mode(struct bu_shd_r_m_data * bu_shd_r_m)
{
	uint8_t result = FALSE;
	if (ui_page == UI_SENSORS_FORMULAR)
	{
		if ((ui_cursor == 6) || (ui_cursor == 7) || (ui_cursor == 8))
		{
			result = TRUE;
		}
		if (((ui_cursor == 0) || (ui_cursor == 1) || (ui_cursor == 3) || (ui_cursor == 4) || (ui_cursor == 5) || (ui_cursor == 10)) && (bu_shd_r_m->system_flags & (1 << SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY)))
		{
			result = TRUE;
		}		
	}	
	if (ui_page == UI_BKO_FORMULAR)
	{
		if ((ui_cursor == 0) || (ui_cursor == 1) || (ui_cursor == 2))
		{
			result = TRUE;
		}
		if ((ui_cursor == 3) && (bu_shd_r_m->system_flags & (1 << SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY)))
		{
			result = TRUE;
		}
	}
	if (ui_page == UI_DU_FORMULAR)
	{
		if ((ui_cursor == 0) || (ui_cursor == 1) || (ui_cursor == 2))
		{
			result = TRUE;
		}		
	}
	if (ui_page == UI_TIME_FORMULAR)
	{
		if ((ui_cursor == 1) || (ui_cursor == 2) || (ui_cursor == 3)|| (ui_cursor == 4) || (ui_cursor == 5))
		{
			result = TRUE;
		}
	}
	if (ui_page == UI_OTHERS_FORMULAR)
	{
		if ((ui_cursor == 2) || (ui_cursor == 3) || (ui_cursor == 8) || (ui_cursor == 9))
		{
			result = TRUE;
		}
		if (((ui_cursor == 5) || (ui_cursor == 6) || (ui_cursor == 7) || (ui_cursor == 10) || (ui_cursor == 11) || (ui_cursor == 12)) && (bu_shd_r_m->system_flags & (1 << SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY)))
		{
			result = TRUE;
		}
	}
	return result;
}

uint8_t fsm_ui_get_current_time(struct ds1302_data * time)
{
		switch (ui_cursor)
		{
			case 1:
			{
				return time->minute;
				break;
			}
			case 2:
			{
				return time->hour;
				break;
			}
			case 3:
			{
				return time->date;
				break;
			}
			case 4:
			{
				return time->month;
				break;
			}
			case 5:
			{
				return time->year;
				break;
			}
			default:
			{
				return 0;
				break;
			}	
		} 
}

void fsm_ui_cursor_change_mode(struct bu_shd_r_m_data * bu_shd_r_m, struct ds1302_data * time)
{
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER) && fsm_ui_cursor_is_able_to_enter_changing_mode(bu_shd_r_m))
	{
		cursor_new_mode = UI_CURSOR_CHANGING_PARAMETR_MODE;
		if ((ui_page == UI_TIME_FORMULAR) && (cursor_new_mode == UI_CURSOR_CHANGING_PARAMETR_MODE) && (temp_clock_data == 0))
		{
			temp_clock_data = fsm_ui_get_current_time(time);
		}
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ESC))
	{
		cursor_new_mode = UI_CURSOR_MOVING_MODE;
	}

}

void fsm_ui_finish_changing_parametr(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER))
	{
		bu_shd_r_m->system_flags |= (1 << SYSTEM_UPDATE_EEPROM);
		cursor_new_mode = UI_CURSOR_MOVING_MODE;
		if ((ui_page == UI_SENSORS_FORMULAR) || (ui_page == UI_OTHERS_FORMULAR))
		{
			bu_shd_r_m->system_flags |= (1 << SYSTEM_REINIT_SENSORS);
		}
		fsm_ui_clear_screen();
		if (displaying_password == bu_shd_r_m->right_password)
		{
			bu_shd_r_m->system_flags |= (1 << SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY);
		}
		if (displaying_password == bu_shd_r_m->to_defaults_password)
		{
			bu_shd_r_m->system_flags |= (1 << SYSTEM_SET_TO_DEFAULTS_PASSWORD_ENTERED_CORRECTLY);
		}
		displaying_password = 0;
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ESC))
	{
		bu_shd_r_m->system_flags |= (1 << SYSTEM_REINIT_FROM_EEPROM);
		fsm_ui_clear_screen();
		displaying_password = 0;
	}	
}

void fsm_ui_finish_changing_time(struct ds1302_data * time, uint8_t * data_to_write)
{
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ENTER))
	{
		ds1302_set_time(time, DS1302_DATA_FIELD_SECOND, 0);
		switch (ui_cursor)
		{
		case 1:
			{
				ds1302_set_time(time, DS1302_DATA_FIELD_MINUTE, *data_to_write);
				break;
			}
		case 2:
			{
				ds1302_set_time(time, DS1302_DATA_FIELD_HOUR, *data_to_write);
				break;
			}
		case 3:
			{
				ds1302_set_time(time, DS1302_DATA_FIELD_DATE, *data_to_write);
				break;
			}
		case 4:
			{
				ds1302_set_time(time, DS1302_DATA_FIELD_MONTH, *data_to_write);
				break;
			}
		case 5:
			{
				ds1302_set_time(time, DS1302_DATA_FIELD_YEAR, *data_to_write);
				break;
			}
		}
		cursor_new_mode = UI_CURSOR_MOVING_MODE;
		fsm_ui_clear_screen();
		temp_clock_data = 0;
	}
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_ESC))
	{
		fsm_ui_clear_screen();
		temp_clock_data = 0;
	}
}

void fsm_ui_sensors_formular_change_parametres(struct bu_shd_r_m_data * bu_shd_r_m)
{
	switch (ui_cursor)
	{
		case 0:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->t1_temperature_shift > T1_TEMPERATURE_SHIFT_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->t1_temperature_shift > T1_TEMPERATURE_SHIFT_MIN + UI_STICK_KEYS_STEP)) 
				{
					bu_shd_r_m->t1_temperature_shift = bu_shd_r_m->t1_temperature_shift - UI_STICK_KEYS_STEP;;
				}
				else
				{
					bu_shd_r_m->t1_temperature_shift = bu_shd_r_m->t1_temperature_shift - UI_SINGLE_KEYS_STEP;;
				}			
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->t1_temperature_shift < T1_TEMPERATURE_SHIFT_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->t1_temperature_shift < T1_TEMPERATURE_SHIFT_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->t1_temperature_shift = bu_shd_r_m->t1_temperature_shift + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->t1_temperature_shift = bu_shd_r_m->t1_temperature_shift + UI_SINGLE_KEYS_STEP;					
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 1:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->t2_temperature_shift > T2_TEMPERATURE_SHIFT_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->t2_temperature_shift > T2_TEMPERATURE_SHIFT_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->t2_temperature_shift = bu_shd_r_m->t2_temperature_shift - UI_STICK_KEYS_STEP;
				} 
				else
				{
					bu_shd_r_m->t2_temperature_shift = bu_shd_r_m->t2_temperature_shift - UI_SINGLE_KEYS_STEP;
				}
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->t2_temperature_shift < T2_TEMPERATURE_SHIFT_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->t2_temperature_shift < T2_TEMPERATURE_SHIFT_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->t2_temperature_shift = bu_shd_r_m->t2_temperature_shift + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->t2_temperature_shift = bu_shd_r_m->t2_temperature_shift + UI_SINGLE_KEYS_STEP;
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 3:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->bko1_temperature_shift > BKO_TEMPERATURE_SHIFT_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->bko1_temperature_shift > BKO_TEMPERATURE_SHIFT_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->bko1_temperature_shift = bu_shd_r_m->bko1_temperature_shift - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->bko1_temperature_shift = bu_shd_r_m->bko1_temperature_shift - UI_SINGLE_KEYS_STEP;
				}		
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->bko1_temperature_shift < BKO_TEMPERATURE_SHIFT_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->bko1_temperature_shift < BKO_TEMPERATURE_SHIFT_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->bko1_temperature_shift = bu_shd_r_m->bko1_temperature_shift + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->bko1_temperature_shift = bu_shd_r_m->bko1_temperature_shift + UI_SINGLE_KEYS_STEP;					
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 4:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->t1_type > SENSOR_T1_T2_TYPE_MIN))
			{
				bu_shd_r_m->t1_type = bu_shd_r_m->t1_type - UI_SINGLE_KEYS_STEP;
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->t1_type < SENSOR_T1_T2_TYPE_MAX))
			{
				bu_shd_r_m->t1_type = bu_shd_r_m->t1_type + UI_SINGLE_KEYS_STEP;
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 5:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->t2_type > SENSOR_T1_T2_TYPE_MIN))
			{
				bu_shd_r_m->t2_type = bu_shd_r_m->t2_type - UI_SINGLE_KEYS_STEP;
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->t2_type < SENSOR_T1_T2_TYPE_MAX))
			{
				bu_shd_r_m->t2_type = bu_shd_r_m->t2_type + UI_SINGLE_KEYS_STEP;
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 6:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->t1_temperature_setting_grad10 > SENSOR_T1_ERROR_OVERHEAT_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->t1_temperature_setting_grad10 > SENSOR_T1_ERROR_OVERHEAT_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->t1_temperature_setting_grad10 = bu_shd_r_m->t1_temperature_setting_grad10 - UI_STICK_KEYS_STEP;
				}
				else
				{ 
					bu_shd_r_m->t1_temperature_setting_grad10 = bu_shd_r_m->t1_temperature_setting_grad10 - UI_SINGLE_KEYS_STEP;					
				}
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->t1_temperature_setting_grad10 < SENSOR_T1_ERROR_OVERHEAT_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->t1_temperature_setting_grad10 < SENSOR_T1_ERROR_OVERHEAT_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->t1_temperature_setting_grad10 = bu_shd_r_m->t1_temperature_setting_grad10 + UI_STICK_KEYS_STEP;					
				}
				else
				{
					bu_shd_r_m->t1_temperature_setting_grad10 = bu_shd_r_m->t1_temperature_setting_grad10 + UI_SINGLE_KEYS_STEP;				
				}

			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 7:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->t2_temperature_setting_grad10 > SENSOR_T2_ERROR_OVERHEAT_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->t2_temperature_setting_grad10 > SENSOR_T2_ERROR_OVERHEAT_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->t2_temperature_setting_grad10 = bu_shd_r_m->t2_temperature_setting_grad10 - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->t2_temperature_setting_grad10 = bu_shd_r_m->t2_temperature_setting_grad10 - UI_SINGLE_KEYS_STEP;
				}				
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->t2_temperature_setting_grad10 < SENSOR_T2_ERROR_OVERHEAT_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->t2_temperature_setting_grad10 < SENSOR_T2_ERROR_OVERHEAT_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->t2_temperature_setting_grad10 = bu_shd_r_m->t2_temperature_setting_grad10 + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->t2_temperature_setting_grad10 = bu_shd_r_m->t2_temperature_setting_grad10 + UI_SINGLE_KEYS_STEP;					
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 8:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->it3_address > IT3_ADDRESS_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->it3_address > IT3_ADDRESS_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->it3_address = bu_shd_r_m->it3_address - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->it3_address = bu_shd_r_m->it3_address - UI_SINGLE_KEYS_STEP;				
				}
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->it3_address < IT3_ADDRESS_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->it3_address < IT3_ADDRESS_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->it3_address = bu_shd_r_m->it3_address + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->it3_address = bu_shd_r_m->it3_address + UI_SINGLE_KEYS_STEP;
				}			
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 10:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->bko_sensor_errors_enabled > BKO_SENSOR_ERRORS_ENABLED_MIN))
			{
				bu_shd_r_m->bko_sensor_errors_enabled = bu_shd_r_m->bko_sensor_errors_enabled-1;
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->bko_sensor_errors_enabled < BKO_SENSOR_ERRORS_ENABLED_MAX))
			{
				bu_shd_r_m->bko_sensor_errors_enabled = bu_shd_r_m->bko_sensor_errors_enabled+1;
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
	}
}

void fsm_ui_bko_formular_change_parametres(struct bu_shd_r_m_data * bu_shd_r_m)
{
	switch (ui_cursor)
	{	
		case 0:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->rpm_high_s_selected > BKO_HIGH_SPEED_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->rpm_high_s_selected > BKO_HIGH_SPEED_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->rpm_high_s_selected = bu_shd_r_m->rpm_high_s_selected - UI_STICK_KEYS_STEP;
				}
				else 
				{
					bu_shd_r_m->rpm_high_s_selected = bu_shd_r_m->rpm_high_s_selected - UI_SINGLE_KEYS_STEP;
				}		
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->rpm_high_s_selected < BKO_HIGH_SPEED_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->rpm_high_s_selected < BKO_HIGH_SPEED_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->rpm_high_s_selected = bu_shd_r_m->rpm_high_s_selected + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->rpm_high_s_selected = bu_shd_r_m->rpm_high_s_selected + UI_SINGLE_KEYS_STEP;
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}		
		case 1:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->rpm_low_s_selected > BKO_LOW_SPEED_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->rpm_low_s_selected > BKO_LOW_SPEED_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->rpm_low_s_selected = bu_shd_r_m->rpm_low_s_selected - UI_STICK_KEYS_STEP;
				} 
				else
				{
					bu_shd_r_m->rpm_low_s_selected = bu_shd_r_m->rpm_low_s_selected - UI_SINGLE_KEYS_STEP;
				}			
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->rpm_low_s_selected < BKO_LOW_SPEED_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->rpm_low_s_selected < BKO_LOW_SPEED_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->rpm_low_s_selected = bu_shd_r_m->rpm_low_s_selected + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->rpm_low_s_selected = bu_shd_r_m->rpm_low_s_selected + UI_SINGLE_KEYS_STEP;					
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 2:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->low_speed_bko_temperature_setting_grad10 > LOW_SPEED_BKO_TEMPERATURE_SETTING_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->low_speed_bko_temperature_setting_grad10 > LOW_SPEED_BKO_TEMPERATURE_SETTING_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->low_speed_bko_temperature_setting_grad10 = bu_shd_r_m->low_speed_bko_temperature_setting_grad10 - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->low_speed_bko_temperature_setting_grad10 = bu_shd_r_m->low_speed_bko_temperature_setting_grad10 - UI_SINGLE_KEYS_STEP;
				}	
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->low_speed_bko_temperature_setting_grad10 < LOW_SPEED_BKO_TEMPERATURE_SETTING_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->low_speed_bko_temperature_setting_grad10 < LOW_SPEED_BKO_TEMPERATURE_SETTING_MAX + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->low_speed_bko_temperature_setting_grad10 = bu_shd_r_m->low_speed_bko_temperature_setting_grad10 + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->low_speed_bko_temperature_setting_grad10 = bu_shd_r_m->low_speed_bko_temperature_setting_grad10 + UI_SINGLE_KEYS_STEP;
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 3:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->heater_power > HEATER_POWER_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->heater_power > HEATER_POWER_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->heater_power = bu_shd_r_m->heater_power - UI_STICK_KEYS_STEP;				
				}
				else
				{
					bu_shd_r_m->heater_power = bu_shd_r_m->heater_power - UI_SINGLE_KEYS_STEP;
				}
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->heater_power < HEATER_POWER_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->heater_power < HEATER_POWER_MAX - UI_STICK_KEYS_STEP)) 
				{
					bu_shd_r_m->heater_power = bu_shd_r_m->heater_power + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->heater_power = bu_shd_r_m->heater_power + UI_SINGLE_KEYS_STEP;
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
	}
}

void fsm_ui_du_formular_change_parametres(struct bu_shd_r_m_data * bu_shd_r_m)
{
	switch (ui_cursor)
	{
		case 0:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->du_address > BU_SH_D_ADDRESS_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->du_address > BU_SH_D_ADDRESS_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->du_address = bu_shd_r_m->du_address - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->du_address = bu_shd_r_m->du_address - UI_SINGLE_KEYS_STEP;
				}				
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->du_address < BU_SH_D_ADDRESS_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->du_address < BU_SH_D_ADDRESS_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->du_address = bu_shd_r_m->du_address + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->du_address = bu_shd_r_m->du_address + UI_SINGLE_KEYS_STEP;
				}				
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 1:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->du_prot > BU_SH_D_PROT_MIN))
			{
				bu_shd_r_m->du_prot = bu_shd_r_m->du_prot - UI_SINGLE_KEYS_STEP;
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->du_prot < BU_SH_D_PROT_MAX))
			{
				bu_shd_r_m->du_prot = bu_shd_r_m->du_prot + UI_SINGLE_KEYS_STEP;
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 2:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->du_baudrate > BU_SH_D_BAUD_MIN))
			{
				bu_shd_r_m->du_baudrate = bu_shd_r_m->du_baudrate - UI_SINGLE_KEYS_STEP;
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->du_baudrate < BU_SH_D_BAUD_MAX))
			{
				bu_shd_r_m->du_baudrate = bu_shd_r_m->du_baudrate + UI_SINGLE_KEYS_STEP;
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
	}
}

void fsm_ui_time_formular_change_parametres(struct ds1302_data * time, struct bu_shd_r_m_data * bu_shd_r_m)
{
	switch (ui_cursor)
		{
			case 1:
			{
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (temp_clock_data > MINUTE_MIN))
				{
					if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (temp_clock_data > MINUTE_MIN + UI_STICK_KEYS_STEP))
					{
						temp_clock_data = temp_clock_data - UI_STICK_KEYS_STEP;
					}
					else
					{
						temp_clock_data = temp_clock_data - UI_SINGLE_KEYS_STEP;
					}
				}
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (temp_clock_data < MINUTE_MAX))
				{
					if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (temp_clock_data < MINUTE_MAX - UI_STICK_KEYS_STEP))
					{
						temp_clock_data = temp_clock_data + UI_STICK_KEYS_STEP;
					}
					else
					{
						temp_clock_data = temp_clock_data + UI_SINGLE_KEYS_STEP;
					}	
				}
				fsm_ui_finish_changing_time(time, &temp_clock_data);
				break;
			}
			case 2:
			{
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (temp_clock_data > HOUR_MIN))
				{
					temp_clock_data = temp_clock_data - UI_SINGLE_KEYS_STEP;
				}
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (temp_clock_data < HOUR_MAX))
				{
					temp_clock_data = temp_clock_data + UI_SINGLE_KEYS_STEP;
				}
				fsm_ui_finish_changing_time(time, &temp_clock_data);
				break;
			}
			case 3:
			{
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (temp_clock_data > DATE_MIN))
				{
					if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (temp_clock_data > DATE_MIN + UI_STICK_KEYS_STEP))
					{
						temp_clock_data = temp_clock_data - UI_STICK_KEYS_STEP;
					}
					else
					{
						temp_clock_data = temp_clock_data - UI_SINGLE_KEYS_STEP;
					}
				}
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (temp_clock_data < DATE_MAX))
				{
					if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (temp_clock_data < DATE_MAX - UI_STICK_KEYS_STEP))
					{
						temp_clock_data = temp_clock_data + UI_STICK_KEYS_STEP;
					}
					else
					{
						temp_clock_data = temp_clock_data + UI_SINGLE_KEYS_STEP;					
					}
				}
				fsm_ui_finish_changing_time(time, &temp_clock_data);
				break;
			}
			case 4:
			{
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (temp_clock_data > MONTH_MIN))
				{
					temp_clock_data = temp_clock_data - UI_SINGLE_KEYS_STEP;
				}
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (temp_clock_data < MONTH_MAX))
				{
					temp_clock_data = temp_clock_data + UI_SINGLE_KEYS_STEP;
				}
				fsm_ui_finish_changing_time(time, &temp_clock_data);
				break;
			}
			case 5:
			{
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (temp_clock_data > YEAR_MIN))
				{
					if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (temp_clock_data > YEAR_MIN + UI_STICK_KEYS_STEP))
					{
						temp_clock_data = temp_clock_data - UI_STICK_KEYS_STEP;
					}
					else
					{
						temp_clock_data = temp_clock_data - UI_SINGLE_KEYS_STEP;
					}		
				}
				if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (temp_clock_data < YEAR_MAX))
				{
					if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (temp_clock_data < YEAR_MAX - UI_STICK_KEYS_STEP))
					{
						temp_clock_data = temp_clock_data + UI_STICK_KEYS_STEP;
					}
					else
					{
						temp_clock_data = temp_clock_data + UI_SINGLE_KEYS_STEP;
					}	
				}
				fsm_ui_finish_changing_time(time, &temp_clock_data);
				break;
			}	
		}
}

void fsm_ui_others_formular_change_parametres(struct bu_shd_r_m_data * bu_shd_r_m)
{
	switch (ui_cursor)
	{
		case 2:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->buzzer_enabled > BUZZER_ENABLED_MIN))
			{
				bu_shd_r_m->buzzer_enabled = bu_shd_r_m->buzzer_enabled - UI_SINGLE_KEYS_STEP;
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->buzzer_enabled < BUZZER_ENABLED_MAX))
			{
				bu_shd_r_m->buzzer_enabled = bu_shd_r_m->buzzer_enabled + UI_SINGLE_KEYS_STEP;
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;			
		}
		case 3:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->buzzer_duty_cycle > BUZZER_DUTY_CYCLE_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->buzzer_duty_cycle > BUZZER_DUTY_CYCLE_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->buzzer_duty_cycle = bu_shd_r_m->buzzer_duty_cycle - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->buzzer_duty_cycle = bu_shd_r_m->buzzer_duty_cycle - UI_SINGLE_KEYS_STEP;
				}
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->buzzer_duty_cycle < BUZZER_DUTY_CYCLE_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->buzzer_duty_cycle < BUZZER_DUTY_CYCLE_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->buzzer_duty_cycle = bu_shd_r_m->buzzer_duty_cycle + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->buzzer_duty_cycle = bu_shd_r_m->buzzer_duty_cycle + UI_SINGLE_KEYS_STEP;					
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 5:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->current_shift > CURRENT_SHIFT_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->current_shift > CURRENT_SHIFT_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->current_shift = bu_shd_r_m->current_shift - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->current_shift = bu_shd_r_m->current_shift - UI_SINGLE_KEYS_STEP;
				}			
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->current_shift < CURRENT_SHIFT_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->current_shift < CURRENT_SHIFT_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->current_shift = bu_shd_r_m->current_shift + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->current_shift = bu_shd_r_m->current_shift + UI_SINGLE_KEYS_STEP;
				}	
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;			
		}
		case 6:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->voltage_shift > VOLTAGE_SHIFT_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->voltage_shift > VOLTAGE_SHIFT_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->voltage_shift = bu_shd_r_m->voltage_shift - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->voltage_shift = bu_shd_r_m->voltage_shift - UI_SINGLE_KEYS_STEP;					
				}
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->voltage_shift < VOLTAGE_SHIFT_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->voltage_shift < VOLTAGE_SHIFT_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->voltage_shift = bu_shd_r_m->voltage_shift + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->voltage_shift = bu_shd_r_m->voltage_shift + UI_SINGLE_KEYS_STEP;	
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;			
		}
		case 7:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->inner_temperature_shift > INNER_TEMPERATURE_SHIFT_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->inner_temperature_shift > INNER_TEMPERATURE_SHIFT_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->inner_temperature_shift = bu_shd_r_m->inner_temperature_shift - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->inner_temperature_shift = bu_shd_r_m->inner_temperature_shift - UI_SINGLE_KEYS_STEP;	
				}			
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->inner_temperature_shift < INNER_TEMPERATURE_SHIFT_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->inner_temperature_shift < INNER_TEMPERATURE_SHIFT_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->inner_temperature_shift = bu_shd_r_m->inner_temperature_shift + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->inner_temperature_shift = bu_shd_r_m->inner_temperature_shift + UI_SINGLE_KEYS_STEP;
				}			
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;			
		}
		case 8:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->inner_temperature_setting_grad10 > INNER_TEMPERATURE_SETTING_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->inner_temperature_setting_grad10 > INNER_TEMPERATURE_SETTING_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->inner_temperature_setting_grad10 = bu_shd_r_m->inner_temperature_setting_grad10 - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->inner_temperature_setting_grad10 = bu_shd_r_m->inner_temperature_setting_grad10 - UI_SINGLE_KEYS_STEP;
				}				
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->inner_temperature_setting_grad10 < INNER_TEMPERATURE_SETTING_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->inner_temperature_setting_grad10 < INNER_TEMPERATURE_SETTING_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->inner_temperature_setting_grad10 = bu_shd_r_m->inner_temperature_setting_grad10 + UI_STICK_KEYS_STEP;				
				}
				else
				{
					bu_shd_r_m->inner_temperature_setting_grad10 = bu_shd_r_m->inner_temperature_setting_grad10 + UI_SINGLE_KEYS_STEP;				
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 9:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (displaying_password > PASSWORD_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (displaying_password > PASSWORD_MIN + UI_STICK_KEYS_STEP))
				{
					displaying_password = displaying_password - UI_STICK_KEYS_STEP;
				}
				else
				{
					displaying_password = displaying_password - UI_SINGLE_KEYS_STEP;
				}	
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (displaying_password < PASSWORD_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (displaying_password < PASSWORD_MAX - UI_STICK_KEYS_STEP))
				{
					displaying_password = displaying_password + UI_STICK_KEYS_STEP;
				}
				else
				{
					displaying_password = displaying_password + UI_SINGLE_KEYS_STEP;
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;			
		}
		case 10:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->production_year > YEAR_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->production_year > YEAR_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->production_year = bu_shd_r_m->production_year - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->production_year = bu_shd_r_m->production_year - UI_SINGLE_KEYS_STEP;
				}			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->production_year < YEAR_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->production_year < YEAR_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->production_year = bu_shd_r_m->production_year + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->production_year = bu_shd_r_m->production_year + UI_SINGLE_KEYS_STEP;
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 11:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->production_month > MONTH_MIN))
			{
				bu_shd_r_m->production_month = bu_shd_r_m->production_month - UI_SINGLE_KEYS_STEP;
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->production_month < MONTH_MAX))
			{
				bu_shd_r_m->production_month = bu_shd_r_m->production_month + UI_SINGLE_KEYS_STEP;
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
		case 12:
		{
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (bu_shd_r_m->serial_number > SERIAL_NUMBER_MIN))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->serial_number > SERIAL_NUMBER_MIN + UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->serial_number = bu_shd_r_m->serial_number - UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->serial_number = bu_shd_r_m->serial_number - UI_SINGLE_KEYS_STEP;
				}				
			}
			if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (bu_shd_r_m->serial_number < SERIAL_NUMBER_MAX))
			{
				if ((bu_shd_r_m->keyboard_autorepeat_mode_on == TRUE) && (bu_shd_r_m->serial_number < SERIAL_NUMBER_MAX - UI_STICK_KEYS_STEP))
				{
					bu_shd_r_m->serial_number = bu_shd_r_m->serial_number + UI_STICK_KEYS_STEP;
				}
				else
				{
					bu_shd_r_m->serial_number = bu_shd_r_m->serial_number + UI_SINGLE_KEYS_STEP;	
				}
			}
			fsm_ui_finish_changing_parametr(bu_shd_r_m);
			break;
		}
	}
}

void fsm_ui_change_parametres(struct bu_shd_r_m_data * bu_shd_r_m, struct ds1302_data * time)
{
	fsm_ui_cursor_change_mode(bu_shd_r_m, time);
	if ((ui_page == UI_SENSORS_FORMULAR) && (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE))
	{
		fsm_ui_sensors_formular_change_parametres(bu_shd_r_m);
	}	
	if ((ui_page == UI_BKO_FORMULAR) && (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE))
	{
		fsm_ui_bko_formular_change_parametres(bu_shd_r_m);
	}	
	if ((ui_page == UI_DU_FORMULAR) && (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE))
	{
		fsm_ui_du_formular_change_parametres(bu_shd_r_m);
	}
	if ((ui_page == UI_TIME_FORMULAR) && (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE))
	{
		fsm_ui_time_formular_change_parametres(time, bu_shd_r_m);
	}
	if ((ui_page == UI_OTHERS_FORMULAR) && (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE))
	{
		fsm_ui_others_formular_change_parametres(bu_shd_r_m);
	}
}

void fsm_ui_init(void)
{
	ui_page = UI_INITIAL_FORMULAR;
	ui_previos_page = UI_MAIN_FORMULAR;
	ui_cursor = 0;
	ui_screen_shift = 0;
	displaying_password = 0;
	cursor_mode = UI_CURSOR_MOVING_MODE;
	ui_last_message = UI_NO_MESSAGES;
	lcd_init();
	virtual_timers_timer_reset(UI_TIMER);
}

void fsm_ui_paint_initial_formular(struct bu_shd_r_m_data * bu_shd_r_m)
{
	lcd_com(lcd_addr(0,0));
	lcd_string_direct_rus("Блок управления");
	lcd_com(lcd_addr(0,1));
	lcd_string_direct_rus("БУ-ШД-Р-М");
	lcd_com(lcd_addr(0,2));
	lcd_string_direct_rus("Зав. #");
	lcd_num_to_str(bu_shd_r_m->production_year,2);
	lcd_num_to_str(bu_shd_r_m->production_month,2);	
	lcd_num_to_str(bu_shd_r_m->serial_number,3);	
	lcd_com(lcd_addr(0,3));
	lcd_string_direct_rus("Версия ПО: v");
	lcd_int100(bu_shd_r_m->programm_version_00,4);	
}

void fsm_ui_paint_message(struct bu_shd_r_m_data * bu_shd_r_m)
{
	lcd_com(lcd_addr(0,3));
	switch (ui_last_message)
	{
		case MSG_KEY_PRESSED_OL:
		{
			lcd_string_direct_rus("Перегрузка КУ       ");
			break;			
		}
		case MSG_FAN_IS_TURNED_ON:
		{
			lcd_string_direct_rus("Включен вентилятор  ");
			break;
		}		
		case MSG_FAN_IS_TURNED_OFF:
		{
			lcd_string_direct_rus("Отключен вентилятор ");
			break;
		}
		case MSG_REGEN1_STARTED:
		{
			lcd_string_direct_rus("Включен РЕГ         ");
			break;
		}
		case MSG_REGEN1_STOPPED:
		{
			lcd_string_direct_rus("Отключен РЕГ        ");
			break;
		}		
		case MSG_REGEN1_FINISHED:
		{
			lcd_string_direct_rus("БКО отогрет         ");
			break;
		}
		case MSG_WRONG_PHASE_SEQUENCE:
		{
			lcd_string_direct_rus("Перефазировка       ");
			break;
		}
		case MSG_T1_OVERHEAT:
		{
			lcd_string_direct_rus("Перегрев по Т1      ");
			break;
		}		
		case MSG_T2_OVERHEAT:
		{
			lcd_string_direct_rus("Перегрев по Т2      ");
			break;
		}
		case MSG_T1_SHORT:
		{
			lcd_string_direct_rus("КЗ датчика Т1       ");
			break;
		}
		case MSG_T1_BREAK:
		{
			lcd_string_direct_rus("Обрыв датчика Т1    ");
			break;
		}
		case MSG_T2_SHORT:
		{
			lcd_string_direct_rus("КЗ датчика Т2       ");
			break;
		}
		case MSG_T2_BREAK:
		{
			lcd_string_direct_rus("Обрыв датчика Т2    ");
			break;
		}
		case MSG_HEATER_SHORT:
		{
			lcd_string_direct_rus("КЗ РЕГ              ");
			break;
		}
		case MSG_HEATER_BREAK:
		{
			lcd_string_direct_rus("Обрыв РЕГ           ");
			break;
		}
		case MSG_STEPPER_BREAK:
		{
			lcd_string_direct_rus("Обрыв ШД            ");
			break;
		}
		case MSG_BKO_STARTED:
		{
			lcd_string_direct_rus("Включен БКО         ");
			break;
		}
		case MSG_BKO_STOPPED:
		{
			lcd_string_direct_rus("Отключен БКО        ");
			break;
		}
		case MSG_BKO_OVERLOAD:
		{
			lcd_string_direct_rus("Перегрузка БКО      ");
			break;
		}
		case MSG_IT3_NO_CONNECTION:
		{
			lcd_string_direct_rus("Нет связи с ИТ-3    ");
			break;
		}
		case MSG_BKO_NO_DATA:
		{
			lcd_string_direct_rus("Нет температуры БКО ");
			break;
		}
		case MSG_BKO_NOT_CONNECTED:
		{
			lcd_string_direct_rus("Не подключен БКО    ");
			break;
		}
		case MSG_BKO_CONNECTED:
		{
			lcd_string_direct_rus("Подключен БКО       ");
			break;
		}
		case MSG_BKO_SENSOR_SHORT:
		{
			lcd_string_direct_rus("КЗ датчика Тбко     ");
			break;
		}
		case MSG_BKO_SENSOR_BREAK:
		{
			lcd_string_direct_rus("Обрыв датчика Тбко  ");
			break;
		}
		case MSG_ADSORBER_LIMIT:
		{
			lcd_string_direct_rus("Замените адсорбер   ");
			break;
		}
		case MSG_MODE_CHANGE:
		{
			if (bu_shd_r_m->system_flags & (1 << SYSTEM_MO_II_ACTIVE))
			{
				lcd_string_direct_rus("Режим IIст. МО      ");
			}
			if (!(bu_shd_r_m->system_flags & (1 << SYSTEM_MO_II_ACTIVE)))
			{
				lcd_string_direct_rus("Режим Iст. МО       ");
			}
		}	
		case MSG_UPDATE_ERRORS:
		{
			lcd_string_direct_rus("Нет сообщений       ");
			break;
		}		
		case UI_NO_MESSAGES:
		{
			lcd_string_direct_rus("Нет сообщений       ");
			break;
		}					
	}
}

void fsm_ui_paint_main_formular(struct bu_shd_r_m_data * bu_shd_r_m, struct ds1302_data * time)
{
	lcd_com(lcd_addr(0,0));
	lcd_string_direct_rus("Т1=");
	if (!((bu_shd_r_m->t1_temperature_grad10 == SHORT) || (bu_shd_r_m->t1_temperature_grad10 == BREAK)))
	{
		if ((bu_shd_r_m->t1_temperature_grad10) < 0)
		{
			lcd_string_direct_rus("-");
			lcd_int10((-1)*bu_shd_r_m->t1_temperature_grad10,4);
			lcd_string_direct_rus("С  ");
		}
		else
		{
			if (bu_shd_r_m->t1_temperature_grad10 >= 1000)
			{
				lcd_string_direct_rus("");
				lcd_int10(bu_shd_r_m->t1_temperature_grad10,5);
				lcd_string_direct_rus("С  ");
			}
			else
			{
				lcd_string_direct_rus(" ");
				lcd_int10(bu_shd_r_m->t1_temperature_grad10,4);
				lcd_string_direct_rus("С  ");
			}
		}
	}	
	if (bu_shd_r_m->t1_temperature_grad10 == SHORT)
	{
		lcd_string_direct_rus(" КЗ     ");
	}
	if (bu_shd_r_m->t1_temperature_grad10 == BREAK)
	{
		lcd_string_direct_rus("Обрыв   ");
	}
	lcd_string_direct_rus("Т2=");
	if (!((bu_shd_r_m->t2_temperature_grad10 == SHORT) || (bu_shd_r_m->t2_temperature_grad10 == BREAK)))
	{
		if ((bu_shd_r_m->t2_temperature_grad10) < 0)
		{
			lcd_string_direct_rus("-");
			lcd_int10((-1)*bu_shd_r_m->t2_temperature_grad10,4);
			lcd_string_direct_rus("С");
		}
		else
		{
			if (bu_shd_r_m->t2_temperature_grad10 >= 1000)
			{
				lcd_string_direct_rus("");
				lcd_int10(bu_shd_r_m->t2_temperature_grad10,5);
				lcd_string_direct_rus("С");			
			}
			else
			{
				lcd_string_direct_rus(" ");
				lcd_int10(bu_shd_r_m->t2_temperature_grad10,4);
				lcd_string_direct_rus("С");				
			}
		}
	}
	if (bu_shd_r_m->t2_temperature_grad10 == SHORT)
	{
		lcd_string_direct_rus(" КЗ     ");
	}
	if (bu_shd_r_m->t2_temperature_grad10 == BREAK)
	{
		lcd_string_direct_rus("Обрыв   ");
	}
	lcd_com(lcd_addr(0,1));				   
	lcd_string_direct_rus("Тбко= ");
	if ((bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_IT3_NO_CONNECTION)) || (bu_shd_r_m->it3_temperature == 0))	
	{
		lcd_string_direct_rus("н/д    ");
	}
	else if (bu_shd_r_m->it3_dot_position)
	{
		lcd_int100(bu_shd_r_m->it3_temperature,5);
		lcd_string_direct_rus("К ");		
	}
	else
	{
		lcd_int10(bu_shd_r_m->it3_temperature,5);
		lcd_string_direct_rus("К ");		
	}
	lcd_string_direct_rus("/");
	if (bu_shd_r_m->bko_sensor_errors_enabled)
	{
		if (bu_shd_r_m->bko1_temperature_grad10 == SHORT)
		{
			lcd_string_direct_rus("КЗ    ");
		}
		if (bu_shd_r_m->bko1_temperature_grad10 == BREAK)
		{
			lcd_string_direct_rus("ОБРЫВ ");
		}
		if (!((bu_shd_r_m->bko1_temperature_grad10 == SHORT) || (bu_shd_r_m->bko1_temperature_grad10 == BREAK)))
		{
			lcd_int10(bu_shd_r_m->bko1_temperature_grad10,5);
			lcd_string_direct_rus("K");
		}	
	}
	else
	{
		if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_SENSOR_T_LOWER_73_K))
		{
			lcd_string_direct_rus("<73.0К");
		}
		else
		{
			lcd_int10(bu_shd_r_m->bko1_temperature_grad10,5);
			lcd_string_direct_rus("K");
		}
	}
	lcd_com(lcd_addr(0,2));
	lcd_string_direct_rus("М/ч= ");
	lcd_num_to_str(bu_shd_r_m->operation_time_1000_h, 4);
	lcd_int10(bu_shd_r_m->operation_time_h10, 5);
	lcd_string_direct_rus("ч");
	fsm_ui_paint_message(bu_shd_r_m);
}

void fsm_ui_paint_menu_formular(void)
{
	if (ui_screen_shift == 0)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Датчики температуры");
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("БКО");
		lcd_com(lcd_addr(1,2));
		lcd_string_direct_rus("ДУ");
		lcd_com(lcd_addr(1,3));
		lcd_string_direct_rus("Часы");
	}
	if (ui_screen_shift == 1)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Прочие");
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Архив");
	}	
}

void fsm_ui_paint_sensors_formular(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (ui_screen_shift == 0)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Т1=       ");
		if (cursor_mode == UI_CURSOR_MOVING_MODE)
		{
			if (bu_shd_r_m->t1_temperature_grad10 == SHORT)
			{
				lcd_string_direct_rus(" КЗ    ");
			}
			else if (bu_shd_r_m->t1_temperature_grad10 == BREAK)
			{
				lcd_string_direct_rus(" Обрыв ");
			}
			if (!((bu_shd_r_m->t1_temperature_grad10 == SHORT) || (bu_shd_r_m->t1_temperature_grad10 == BREAK)))
			{
				if ((bu_shd_r_m->t1_temperature_grad10) < 0)
				{
					lcd_string_direct_rus("-");
					lcd_int10((-1)*bu_shd_r_m->t1_temperature_grad10,4);
					lcd_string_direct_rus(" С");
				}
				else
				{
					if (bu_shd_r_m->t1_temperature_grad10 >= 1000)
					{
						lcd_string_direct_rus("");
						lcd_int10(bu_shd_r_m->t1_temperature_grad10,5);
						lcd_string_direct_rus(" С");
					}
					else
					{
						lcd_string_direct_rus(" ");
						lcd_int10(bu_shd_r_m->t1_temperature_grad10,4);
						lcd_string_direct_rus(" С");
					}
				}
			}			
		}
		if (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE)
		{
			if ((bu_shd_r_m->t1_temperature_shift) < 0)
			{
				lcd_string_direct_rus("-");
				lcd_int10((-1)*bu_shd_r_m->t1_temperature_shift,4);
				lcd_string_direct_rus(" С");
			}
			else
			{
				if (bu_shd_r_m->t1_temperature_shift >= 1000)
				{
					lcd_string_direct_rus("");
					lcd_int10(bu_shd_r_m->t1_temperature_shift,5);
					lcd_string_direct_rus(" С");
				}
				else
				{
					lcd_string_direct_rus(" ");
					lcd_int10(bu_shd_r_m->t1_temperature_shift,4);
					lcd_string_direct_rus(" С");
				}
			}
		}	
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Т2=       ");
		if (cursor_mode == UI_CURSOR_MOVING_MODE)
		{
			if (bu_shd_r_m->t2_temperature_grad10 == SHORT)
			{
				lcd_string_direct_rus(" КЗ    ");
			}
			else if (bu_shd_r_m->t2_temperature_grad10 == BREAK)
			{
				lcd_string_direct_rus(" Обрыв ");
			}
			if (!((bu_shd_r_m->t2_temperature_grad10 == SHORT) || (bu_shd_r_m->t2_temperature_grad10 == BREAK)))
			{
				if ((bu_shd_r_m->t2_temperature_grad10) < 0)
				{
					lcd_string_direct_rus("-");
					lcd_int10((-1)*bu_shd_r_m->t2_temperature_grad10,4);
					lcd_string_direct_rus(" С");
				}
				else
				{
					if (bu_shd_r_m->t2_temperature_grad10 >= 1000)
					{
						lcd_string_direct_rus("");
						lcd_int10(bu_shd_r_m->t2_temperature_grad10,5);
						lcd_string_direct_rus(" С");
					}
					else
					{
						lcd_string_direct_rus(" ");
						lcd_int10(bu_shd_r_m->t2_temperature_grad10,4);
						lcd_string_direct_rus(" С");
					}
				}
			}
		}
		if (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE)
		{
			if ((bu_shd_r_m->t2_temperature_shift) < 0)
			{
				lcd_string_direct_rus("-");
				lcd_int10((-1)*bu_shd_r_m->t2_temperature_shift,4);
				lcd_string_direct_rus(" С");
			}
			else
			{
				if (bu_shd_r_m->t2_temperature_shift >= 1000)
				{
					lcd_string_direct_rus("");
					lcd_int10(bu_shd_r_m->t2_temperature_shift,5);
					lcd_string_direct_rus(" С");
				}
				else
				{
					lcd_string_direct_rus(" ");
					lcd_int10(bu_shd_r_m->t2_temperature_shift,4);
					lcd_string_direct_rus(" С");
				}
			}
		}			
		lcd_com(lcd_addr(1,2));
		lcd_string_direct_rus("Тбко-ИТ3  ");
		if ((bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_IT3_NO_CONNECTION)) || (bu_shd_r_m->it3_temperature == 0))
		{
			lcd_string_direct_rus("н/д    ");
		}
		else if (bu_shd_r_m->it3_dot_position)
		{
			lcd_int100(bu_shd_r_m->it3_temperature,5);
			lcd_string_direct_rus(" К");
		}
		else
		{
			lcd_int10(bu_shd_r_m->it3_temperature,5);
			lcd_string_direct_rus(" К");
		}	
		lcd_com(lcd_addr(1,3));
		lcd_string_direct_rus("Тбко-датч ");
		if (cursor_mode == UI_CURSOR_MOVING_MODE)
		{
			if (bu_shd_r_m->bko1_temperature_grad10 == BREAK)
			{
				lcd_string_direct_rus("Обрыв   ");
			}
			if (bu_shd_r_m->bko1_temperature_grad10 == SHORT)
			{
				lcd_string_direct_rus("КЗ      ");
			}
			if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_SENSOR_T_LOWER_73_K))
			{
				lcd_string_direct_rus("<73.0 К ");
			}
			else if (!((bu_shd_r_m->bko1_temperature_grad10 == SHORT) || (bu_shd_r_m->bko1_temperature_grad10 == BREAK)))
			{
				lcd_int10(bu_shd_r_m->bko1_temperature_grad10,5);
				lcd_string_direct_rus(" K");
			}	
		}
		if (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE)
		{
			if ((bu_shd_r_m->bko1_temperature_shift) < 0)
			{
				lcd_string_direct_rus("-");
				lcd_int10((-1)*bu_shd_r_m->bko1_temperature_shift,4);
				lcd_string_direct_rus(" С");
			}
			else
			{
				if (bu_shd_r_m->bko1_temperature_shift >= 1000)
				{
					lcd_string_direct_rus("");
					lcd_int10(bu_shd_r_m->bko1_temperature_shift,5);
					lcd_string_direct_rus(" С");
				}
				else
				{
					lcd_string_direct_rus(" ");
					lcd_int10(bu_shd_r_m->bko1_temperature_shift,4);
					lcd_string_direct_rus(" С");
				}
			}
		}
	}	
	if (ui_screen_shift == 1)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Датчик Т1 ");
		if (bu_shd_r_m->t1_type == 0)
		{
			lcd_string_direct_rus("Pt100");
		}		
		if (bu_shd_r_m->t1_type == 1)
		{
			lcd_string_direct_rus("Pt300");
		}
		if (bu_shd_r_m->t1_type == 2)
		{
			lcd_string_direct_rus("Cu100");
		}
		if (bu_shd_r_m->t1_type == 3)
		{
			lcd_string_direct_rus("Cu300");
		}
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Датчик Т2 ");
		if (bu_shd_r_m->t2_type == 0)
		{
			lcd_string_direct_rus("Pt100");
		}
		if (bu_shd_r_m->t2_type == 1)
		{
			lcd_string_direct_rus("Pt300");
		}
		if (bu_shd_r_m->t2_type == 2)
		{
			lcd_string_direct_rus("Cu100");
		}
		if (bu_shd_r_m->t2_type == 3)
		{
			lcd_string_direct_rus("Cu300");
		}
		lcd_com(lcd_addr(1,2));
		lcd_string_direct_rus("Порог  Т1 ");
		lcd_int10(bu_shd_r_m->t1_temperature_setting_grad10, 5);
		lcd_string_direct_rus("С");
		lcd_com(lcd_addr(1,3));
		lcd_string_direct_rus("Порог  Т2 ");
		lcd_int10(bu_shd_r_m->t2_temperature_setting_grad10, 5);
		lcd_string_direct_rus("С");	
	}
	if (ui_screen_shift == 2)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Адрес ИТ3 ");
		lcd_num_to_str(bu_shd_r_m->it3_address,3);
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Сброс ИТ3 Запрещён");
		lcd_com(lcd_addr(1,2));	
		lcd_string_direct_rus("Защита Тбко ");
		if (bu_shd_r_m->bko_sensor_errors_enabled)
		{
			lcd_string_direct_rus("Вкл.   ");
		}
		else
		{
			lcd_string_direct_rus("Откл.  ");
		}
	}
}

void fsm_ui_paint_bko_formular(struct bu_shd_r_m_data * bu_shd_r_m)
{
	lcd_com(lcd_addr(1,0));
	lcd_string_direct_rus("Больш ск. ");
	lcd_num_to_str(bu_shd_r_m->rpm_high_s_selected, 2);
	lcd_string_direct_rus(" об/мин");	
	lcd_com(lcd_addr(1,1));
	lcd_string_direct_rus("Малая ск. ");
	lcd_num_to_str(bu_shd_r_m->rpm_low_s_selected, 2);
	lcd_string_direct_rus(" об/мин");
	lcd_com(lcd_addr(1,2));
	lcd_string_direct_rus("Т перекл. ");
	lcd_int10(bu_shd_r_m->low_speed_bko_temperature_setting_grad10, 5);
	lcd_string_direct_rus(" К");
	lcd_com(lcd_addr(1,3));
	lcd_string_direct_rus("Мощн. РЕГ ");	
	lcd_num_to_str(bu_shd_r_m->heater_power, 3);
	lcd_string_direct_rus(" Вт");	
}

void fsm_ui_paint_du_formular(struct bu_shd_r_m_data * bu_shd_r_m)
{
	lcd_com(lcd_addr(1,0));
	lcd_string_direct_rus("Адрес     ");
	lcd_num_to_str(bu_shd_r_m->du_address, 3);
	lcd_com(lcd_addr(1,1));
	lcd_string_direct_rus("Протокол  ");
	if (bu_shd_r_m->du_prot == 0)
	{
		lcd_string_direct_rus("ModbusRTU");
	}
	if (bu_shd_r_m->du_prot == 1)
	{
		lcd_string_direct_rus("Дубна    ");
	}
	lcd_com(lcd_addr(1,2));
	lcd_string_direct_rus("Скорость  ");
	if (bu_shd_r_m->du_baudrate == 0)
	{
		lcd_num_to_str(9600, 4);
		lcd_string_direct_rus("  ");
	}
	if (bu_shd_r_m->du_baudrate == 1)
	{
		lcd_num_to_str(19200, 5);
		lcd_string_direct_rus(" ");
	}	
	if (bu_shd_r_m->du_baudrate == 2)
	{
		lcd_num_to_str(38400, 5);
		lcd_string_direct_rus(" ");
	}
	if (bu_shd_r_m->du_baudrate == 3)
	{
		lcd_num_to_str(57600, 5);
		lcd_string_direct_rus(" ");
	}
	if (bu_shd_r_m->du_baudrate == 4)
	{
		lcd_string_direct_rus("115200");
	}
}

void fsm_ui_paint_time_formular(struct ds1302_data * time)
{
	if (ui_screen_shift == 0)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Секунды ");
		lcd_num_to_str(time->second, 2);
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Минута  ");
		if ((cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE) && (ui_cursor == 1))
		{
			lcd_num_to_str(temp_clock_data, 2);
		}
		else
		{
			lcd_num_to_str(time->minute, 2);
		}
		lcd_com(lcd_addr(1,2));
		lcd_string_direct_rus("Час     ");
		if ((cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE) && (ui_cursor == 2))
		{
			lcd_num_to_str(temp_clock_data, 2);
		}
		else
		{
			lcd_num_to_str(time->hour, 2);
		}
		lcd_com(lcd_addr(1,3));
		lcd_string_direct_rus("Число   ");
		if ((cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE) && (ui_cursor == 3))
		{
			lcd_num_to_str(temp_clock_data, 2);
		}
		else
		{
			lcd_num_to_str(time->date, 2);
		}
	}
	if (ui_screen_shift == 1)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Месяц   ");
		if ((cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE) && (ui_cursor == 4))
		{
			lcd_num_to_str(temp_clock_data, 2);
		}
		else
		{
			lcd_num_to_str(time->month, 2);
		}
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Год   ");
		lcd_num_to_str(20, 2);		
		if ((cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE) && (ui_cursor == 5))
		{
			lcd_num_to_str(temp_clock_data, 2);
		}
		else
		{
			lcd_num_to_str(time->year, 2);
		}
	}	
}

void fsm_ui_paint_others_formular(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (ui_screen_shift == 0)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Версия ПО ");
		lcd_int100(bu_shd_r_m->programm_version_00,4);
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Наработка ");
		lcd_num_to_str(bu_shd_r_m->operation_time_1000_h, 4);
		lcd_int10(bu_shd_r_m->operation_time_h10, 5);
		lcd_com(lcd_addr(1,2));
		lcd_string_direct_rus("Звук      ");
		if (bu_shd_r_m->buzzer_enabled == TRUE)
		{
			lcd_string_direct_rus("Включен ");
		}
		if (bu_shd_r_m->buzzer_enabled == FALSE)
		{
			lcd_string_direct_rus("Выключен");
		}
		lcd_com(lcd_addr(1,3));
		lcd_string_direct_rus("Сква-ость ");
		lcd_num_to_str(bu_shd_r_m->buzzer_duty_cycle, 3);
		lcd_string_direct_rus("%");
	}
	if (ui_screen_shift == 1)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Дискр. вх  0x");
		lcd_hex(bu_shd_r_m->digital_input, 4);
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Ток ИП     ");
		if (cursor_mode == UI_CURSOR_MOVING_MODE)
		{
			lcd_int100((uint16_t)bu_shd_r_m->current,5);
			lcd_string_direct_rus(" А");			
		}
		if (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE)
		{
			if ((bu_shd_r_m->current_shift) < 0)
			{
				lcd_string_direct_rus("-");
				lcd_int100((-1)*bu_shd_r_m->current_shift,5);
				lcd_string_direct_rus("А");
			}
			else
			{
				lcd_int100(bu_shd_r_m->current_shift,5);
				lcd_string_direct_rus(" А");
			}
		}
		lcd_com(lcd_addr(1,2));
		lcd_string_direct_rus("Напр. ИП   ");
		if (cursor_mode == UI_CURSOR_MOVING_MODE)
		{
			lcd_int100(bu_shd_r_m->voltage,5);
			lcd_string_direct_rus(" В");			
		}
		if (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE)
		{
			if ((bu_shd_r_m->voltage_shift) < 0)
			{
				lcd_string_direct_rus("-");
				lcd_int100((-1)*bu_shd_r_m->voltage_shift,5);
				lcd_string_direct_rus("В");
			}
			else
			{
				lcd_int100(bu_shd_r_m->voltage_shift,5);
				lcd_string_direct_rus(" В");
			}
		}
		lcd_com(lcd_addr(1,3));
		lcd_string_direct_rus("Тблока     ");
		if (cursor_mode == UI_CURSOR_MOVING_MODE)
		{
			if (bu_shd_r_m->inner_temperature_grad10 == SHORT)
			{
				lcd_string_direct_rus(" КЗ  ");
			}
			else if (bu_shd_r_m->inner_temperature_grad10 == BREAK)
			{
				lcd_string_direct_rus("Обрыв");
			}
			else
			{
				if ((bu_shd_r_m->inner_temperature_grad10) < 0)
				{
					lcd_string_direct_rus("-");
					lcd_int10((-1)*bu_shd_r_m->inner_temperature_grad10,4);
					lcd_string_direct_rus(" С");
				}
				else
				{
					lcd_int10(bu_shd_r_m->inner_temperature_grad10,4);
					lcd_string_direct_rus("  С");
				}
			}
		}
		if (cursor_mode == UI_CURSOR_CHANGING_PARAMETR_MODE)
		{
			if ((bu_shd_r_m->inner_temperature_shift) < 0)
			{
				lcd_string_direct_rus("-");
				lcd_int10((-1)*bu_shd_r_m->inner_temperature_shift,4);
				lcd_string_direct_rus(" С");
			}
			else
			{
				lcd_int10(bu_shd_r_m->inner_temperature_shift,4);
				lcd_string_direct_rus("  С");
			}
		}	
	}
	if (ui_screen_shift == 2)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Твкл.вент. ");
		if (bu_shd_r_m->inner_temperature_setting_grad10 < 1000)
		{
			lcd_int10(bu_shd_r_m->inner_temperature_setting_grad10,4);		
			lcd_string_direct_rus("С ");	
		}
		else
		{
			lcd_int10(bu_shd_r_m->inner_temperature_setting_grad10,5);
			lcd_string_direct_rus("С");			
		}
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Пароль     ");
		lcd_num_to_str(displaying_password,4);
		lcd_com(lcd_addr(1,2));
		lcd_string_direct_rus("Год вып.   20");
		lcd_num_to_str(bu_shd_r_m->production_year,2);
		lcd_com(lcd_addr(1,3));
		lcd_string_direct_rus("Месяц вып. ");
		lcd_num_to_str(bu_shd_r_m->production_month,2);
	}
	if (ui_screen_shift == 3)
	{
		lcd_com(lcd_addr(1,0));
		lcd_string_direct_rus("Сер.номер  ");
		lcd_num_to_str(bu_shd_r_m->serial_number,3);
		lcd_com(lcd_addr(1,1));
		lcd_string_direct_rus("Н/ч мл.    ");
		lcd_int10(bu_shd_r_m->operation_time_h10,5);
		lcd_string_direct_rus(" Ч");
		lcd_com(lcd_addr(1,2));
		lcd_string_direct_rus("Н/с ст.    ");
		lcd_num_to_str(bu_shd_r_m->operation_time_1000_h,4);
		lcd_string_direct_rus(" кЧ");
	}
}

void fsm_ui_paint_archive_formular(struct archive_record * bu_shd_r_m_archive, struct bu_shd_r_m_data * bu_shd_r_m)
{
	struct archive_record ui_temp_record;
	eeprom_read_block((void*)&ui_temp_record, (const void*)(bu_shd_r_m_archive+ui_archive_page), 6);
	lcd_com(lcd_addr(0,0));
	lcd_string_direct_rus("Архив. Запись ");
	if (ui_archive_page >= bu_shd_r_m->archive_starting_record)
	{
		lcd_num_to_str(ui_archive_page-bu_shd_r_m->archive_starting_record,2);
	}
	else
	{
		lcd_num_to_str(FSM_ARCHIVE_SIZE+ui_archive_page-bu_shd_r_m->archive_starting_record,2);
	}
	lcd_com(lcd_addr(0,1));
	switch (ui_temp_record.message)
	{
		case 0:
		{
			lcd_string_direct_rus("                    ");
			break;			
		}
		case MSG_KEY_PRESSED_OL:
		{
			lcd_string_direct_rus("Перегрузка КУ       ");
			break;
		}
		case MSG_INNER_T_SENSOR_SHORT:
		{
			lcd_string_direct_rus("КЗ вн. датчика      ");	
			break;
		}
		case MSG_INNER_T_SENSOR_BREAK:
		{
			lcd_string_direct_rus("ОБРЫВ вн. датчика   ");
			break;
		}
		case MSG_FAN_IS_TURNED_ON:
		{
			lcd_string_direct_rus("Включен вентилятор  ");
			break;
		}
		case MSG_FAN_IS_TURNED_OFF:
		{
			lcd_string_direct_rus("Отключен вентилятор ");
			break;
		}
		case MSG_REGEN1_STARTED:
		{
			lcd_string_direct_rus("Включен РЕГ         ");
			break;
		}
		case MSG_REGEN1_STOPPED:
		{
			lcd_string_direct_rus("Отключен РЕГ        ");
			break;
		}
		case MSG_REGEN1_FINISHED:
		{
			lcd_string_direct_rus("БКО отогрет         ");
			break;
		}
		case MSG_REGEN2_STARTED:
		{
			lcd_string_direct_rus("Включен РЕГ2        ");
			break;
		}
		case MSG_REGEN2_STOPPED:
		{
			lcd_string_direct_rus("Отключен РЕГ2       ");
			break;
		}
		case MSG_REGEN2_FINISHED:
		{
			lcd_string_direct_rus("БКО2 отогрет        ");
			break;
		}
		case MSG_WRONG_PHASE_SEQUENCE:
		{
			lcd_string_direct_rus("Перефазировка       ");
			break;
		}
		case MSG_T1_OVERHEAT:
		{
			lcd_string_direct_rus("Перегрев по Т1      ");
			break;
		}
		case MSG_T2_OVERHEAT:
		{
			lcd_string_direct_rus("Перегрев по Т2      ");
			break;
		}
		case MSG_T1_SHORT:
		{
			lcd_string_direct_rus("КЗ датчика Т1       ");
			break;
		}
		case MSG_T1_BREAK:
		{
			lcd_string_direct_rus("Обрыв датчика Т1    ");
			break;
		}
		case MSG_T2_SHORT:
		{
			lcd_string_direct_rus("КЗ датчика Т2       ");
			break;
		}
		case MSG_T2_BREAK:
		{
			lcd_string_direct_rus("Обрыв датчика Т2    ");
			break;
		}
		case MSG_HEATER_SHORT:
		{
			lcd_string_direct_rus("КЗ РЕГ              ");
			break;
		}
		case MSG_HEATER_BREAK:
		{
			lcd_string_direct_rus("Обрыв РЕГ           ");
			break;
		}
		case MSG_STEPPER_BREAK:
		{
			lcd_string_direct_rus("Обрыв ШД            ");
			break;
		}
		case MSG_BKO_STARTED:
		{
			lcd_string_direct_rus("Включен БКО         ");
			break;
		}
		case MSG_BKO_STOPPED:
		{
			lcd_string_direct_rus("Отключен БКО        ");
			break;
		}
		case MSG_IT3_NO_CONNECTION:
		{
			lcd_string_direct_rus("Нет связи с ИТ-3    ");
			break;
		}
		case MSG_BKO_SENSOR_SHORT:
		{
			lcd_string_direct_rus("КЗ датчика Тбко     ");
			break;
		}
		case MSG_BKO_SENSOR_BREAK:
		{
			lcd_string_direct_rus("Обрыв датчика Тбко  ");
			break;
		}
		case MSG_ADSORBER_LIMIT:
		{
			lcd_string_direct_rus("Замените адсорбер   ");
			break;
		}
		case MSG_BKO_OVERLOAD:
		{
			lcd_string_direct_rus("Перегрузка БКО      ");
			break;
		}
		case MSG_EEPROM_UPDATED:
		{
			lcd_string_direct_rus("EEPROM обновлен     ");
			break;
		}
		default:
		{
			lcd_num_to_str(ui_temp_record.message, 2);
			break;
		}
	}
	lcd_com(lcd_addr(0,2));
	if (ui_temp_record.message != 0)
	{
		lcd_num_to_str(ui_temp_record.hour, 2);
		lcd_string_direct_rus(":");
		lcd_num_to_str(ui_temp_record.minute, 2);	
		lcd_com(lcd_addr(0,3));
		lcd_num_to_str(ui_temp_record.date, 2);
		lcd_string_direct_rus(".");
		lcd_num_to_str(ui_temp_record.month, 2);
		lcd_string_direct_rus(".");
		lcd_num_to_str(ui_temp_record.year, 2);
	}
	else
	{
		lcd_string_direct_rus("                    ");
		lcd_com(lcd_addr(0,3));
		lcd_string_direct_rus("                    ");
	}
}

void fsm_ui_archive_switch_pages(void)
{
	if (ui_page == UI_ARCHIVE_FORMULAR)
	{
		if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (ui_archive_page == 0))
		{
			ui_archive_page = FSM_ARCHIVE_SIZE;
		}
		if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_LEFT) && (ui_archive_page > 0))
		{
			ui_archive_page--;
		}
		if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (ui_archive_page == FSM_ARCHIVE_SIZE-1))
		{
			ui_archive_page = 0;
		}
		if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_RIGHT) && (ui_archive_page < (FSM_ARCHIVE_SIZE-1)))
		{
			ui_archive_page++;
		}
	}
}

uint8_t fsm_ui_process_check_message_to_be_painted(uint8_t message)
{
	if (
	(message == MSG_KEY_PRESSED_OL) ||
	(message == MSG_FAN_IS_TURNED_ON) ||
	(message == MSG_FAN_IS_TURNED_OFF) ||
	(message == MSG_REGEN1_STARTED) ||
	(message == MSG_REGEN1_STOPPED) ||
	(message == MSG_REGEN1_FINISHED) ||
	(message == MSG_WRONG_PHASE_SEQUENCE) ||
	(message == MSG_T1_OVERHEAT) ||
	(message == MSG_T2_OVERHEAT) ||
	(message == MSG_T1_SHORT) ||
	(message == MSG_T1_BREAK) ||
	(message == MSG_T2_SHORT) ||
	(message == MSG_T2_BREAK) ||
	(message == MSG_HEATER_SHORT) ||
	(message == MSG_HEATER_BREAK) ||
	(message == MSG_STEPPER_BREAK) ||
	(message == MSG_BKO_STARTED) ||
	(message == MSG_BKO_STOPPED) ||
	(message == MSG_BKO_OVERLOAD) ||
	(message == MSG_IT3_NO_CONNECTION) ||
	(message == MSG_BKO_NO_DATA) ||
	(message == MSG_BKO_NOT_CONNECTED) ||
	(message == MSG_BKO_CONNECTED) ||
	(message == MSG_BKO_SENSOR_SHORT) ||
	(message == MSG_BKO_SENSOR_BREAK) ||
	(message == MSG_ADSORBER_LIMIT) ||
	(message == MSG_MODE_CHANGE) ||
	(message == MSG_UPDATE_ERRORS) ||
	(message == UI_NO_MESSAGES)
	)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

void fsm_ui_process(struct bu_shd_r_m_data * bu_shd_r_m, struct ds1302_data * time, struct archive_record * bu_shd_r_m_archive)
{
	if (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP))
	{
		lcd_init();
		virtual_timers_timer_reset(UI_TIMER);
	}
	for (uint8_t i = 0; i < MAX_BROADCAST_MESSAGES; i++)
	{
		if (fsm_messages_get_broadcast_message(i) && fsm_ui_process_check_message_to_be_painted(i))
		{
			ui_last_message = i;
		}
	}
	fsm_ui_change_parametres(bu_shd_r_m, time);
	fsm_ui_page_move(bu_shd_r_m);	
	fsm_ui_archive_switch_pages();
	fsm_ui_cursor_process();

	if (virtual_timers_timer_get(UI_TIMER) >= UI_UPDATE_PERIOD_MS)
	{
		cursor_mode = cursor_new_mode;
		switch(ui_page)
		{
			case UI_INITIAL_FORMULAR:
			{
				fsm_ui_paint_initial_formular(bu_shd_r_m);
				break;
			}
			case UI_MAIN_FORMULAR:
			{
				fsm_ui_paint_main_formular(bu_shd_r_m, time);
				virtual_timers_timer_reset(UI_TIMER);
				break;
			}
			case UI_MENU_FORMULAR:
			{
				fsm_ui_paint_menu_formular();
				virtual_timers_timer_reset(UI_TIMER);
				break;
			}			
			case UI_SENSORS_FORMULAR:
			{
				fsm_ui_paint_sensors_formular(bu_shd_r_m);
				virtual_timers_timer_reset(UI_TIMER);
				break;
			}
			case UI_BKO_FORMULAR:
			{
				fsm_ui_paint_bko_formular(bu_shd_r_m);
				virtual_timers_timer_reset(UI_TIMER);
				break;
			}
			case UI_DU_FORMULAR:
			{
				fsm_ui_paint_du_formular(bu_shd_r_m);
				virtual_timers_timer_reset(UI_TIMER);
				break;
			}
			case UI_TIME_FORMULAR:
			{
				fsm_ui_paint_time_formular(time);
				virtual_timers_timer_reset(UI_TIMER);
				break;
			}
			case UI_OTHERS_FORMULAR:
			{
				fsm_ui_paint_others_formular(bu_shd_r_m);
				virtual_timers_timer_reset(UI_TIMER);
				break;
			}
			case UI_ARCHIVE_FORMULAR:
			{
				fsm_ui_paint_archive_formular(bu_shd_r_m_archive, bu_shd_r_m);
				virtual_timers_timer_reset(UI_TIMER);
				break;
			}
		}	
	}	
}
