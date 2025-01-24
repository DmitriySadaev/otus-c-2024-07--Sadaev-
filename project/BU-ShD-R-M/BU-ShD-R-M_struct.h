<<<<<<< HEAD
/*!
\file
\defgroup BU-ShD-R-M
\brief Заголовочный файл BU-ShD-R-M_struct.h

С помощью этого заголовочного файла определены структуры данных основной программы
*/

#ifndef BU_SHD_R_M_STRUCT_H_
#define BU_SHD_R_M_STRUCT_H_

//----------------------------------------------------------------------------------
//--------Флаги ошибок--------------------------------------------------------------

#ifndef ERROR_T1_SHORT
#define ERROR_T1_SHORT 0U
#endif /* ERROR_T1_SHORT */

#ifndef ERROR_T1_BREAK
#define ERROR_T1_BREAK 1U
#endif /* ERROR_T1_BREAK */

#ifndef ERROR_T1_OVERHEAT
#define ERROR_T1_OVERHEAT 2U
#endif /* ERROR_T1_OVERHEAT */

#ifndef ERROR_T2_SHORT
#define ERROR_T2_SHORT 3U
#endif /* ERROR_T2_SHORT */

#ifndef ERROR_T2_BREAK
#define ERROR_T2_BREAK 4U
#endif /* ERROR_T2_BREAK */

#ifndef ERROR_T2_OVERHEAT
#define ERROR_T2_OVERHEAT 5U
#endif /* ERROR_T2_OVERHEAT */

#ifndef ERROR_KU_PHASE_A
#define ERROR_KU_PHASE_A 6U
#endif /* ERROR_KU_PHASE_A */

#ifndef ERROR_KU_PHASE_B
#define ERROR_KU_PHASE_B 7U
#endif /* ERROR_KU_PHASE_B */

#ifndef ERROR_KU_PHASE_C
#define ERROR_KU_PHASE_C 8U
#endif /* ERROR_KU_PHASE_C */

#ifndef ERROR_KU_WRONG_PHASE_SEQUENCE
#define ERROR_KU_WRONG_PHASE_SEQUENCE 9U
#endif /* ERROR_KU_WRONG_PHASE_SEQUENCE */

#ifndef ERROR_KU_OVERLOAD
#define ERROR_KU_OVERLOAD 10U
#endif /* ERROR_KU_OVERLOAD */

#ifndef ERROR_BKO_OVERLOAD
#define ERROR_BKO_OVERLOAD 11U
#endif /* ERROR_BKO_OVERLOAD */

#ifndef ERROR_STEPPER_CURCUIT_BREAK
#define ERROR_STEPPER_CURCUIT_BREAK 12U
#endif /* ERROR_STEPPER_CURCUIT_BREAK */

#ifndef ERROR_HEATER_SHORT
#define ERROR_HEATER_SHORT 13U
#endif /* ERROR_HEATER_SHORT */

#ifndef ERROR_HEATER_BREAK
#define ERROR_HEATER_BREAK 14U
#endif /* ERROR_HEATER_BREAK */

#ifndef ERROR_BKO_SENSOR_SHORT
#define ERROR_BKO_SENSOR_SHORT 15U
#endif /* ERROR_BKO_SENSOR_SHORT */

#ifndef ERROR_BKO_SENSOR_BREAK
#define ERROR_BKO_SENSOR_BREAK 16U
#endif /* ERROR_BKO_SENSOR_BREAK */

#ifndef ERROR_BKO_NOT_CONNECTED
#define ERROR_BKO_NOT_CONNECTED 17U
#endif /* ERROR_BKO_NOT_CONNECTED */

#ifndef ERROR_IT3_NO_CONNECTION
#define ERROR_IT3_NO_CONNECTION 18U
#endif /* ERROR_IT3_NO_CONNECTION */

#ifndef ERROR_BKO_SENSOR_T_LOWER_73_K
#define ERROR_BKO_SENSOR_T_LOWER_73_K 19U
#endif /* ERROR_BKO_SENSOR_T_LOWER_73_K */

#ifndef ERROR_CHANGE_ADSORBER
#define ERROR_CHANGE_ADSORBER 20U
#endif /* ERROR_CHANGE_ADSORBER */

//-----------------------------------------------------------------------------
//--------Флаги состояния БУ ШД------------------------------------------------
#ifndef SYSTEM_KU
#define SYSTEM_KU 0U
#endif /* SYSTEM_KU */

#ifndef SYSTEM_FAN
#define SYSTEM_FAN 1U
#endif /* SYSTEM_FAN */

#ifndef SYSTEM_BKO1
#define SYSTEM_BKO1 2U
#endif /* SYSTEM_BKO1 */

#ifndef SYSTEM_BKO2
#define SYSTEM_BKO2 3U
#endif /* SYSTEM_BKO2 */

#ifndef SYSTEM_HEATER1
#define SYSTEM_HEATER1 4U
#endif /* SYSTEM_HEATER1 */

#ifndef SYSTEM_HEATER2
#define SYSTEM_HEATER2 5U
#endif /* SYSTEM_HEATER2 */

#ifndef SYSTEM_MO_II_ACTIVE
#define SYSTEM_MO_II_ACTIVE 6U
#endif /* SYSTEM_HEATER2 */

#ifndef SYSTEM_UPDATE_EEPROM
#define SYSTEM_UPDATE_EEPROM 9U
#endif /* SYSTEM_UPDATE_EEPROM */

#ifndef SYSTEM_REINIT_FROM_EEPROM
#define SYSTEM_REINIT_FROM_EEPROM 10U
#endif /* SYSTEM_REINIT_FROM_EEPROM */

#ifndef SYSTEM_UPDATE_TIME_IN_EEPROM
#define SYSTEM_UPDATE_TIME_IN_EEPROM 11U
#endif /* SYSTEM_UPDATE_TIME_IN_EEPROM */

#ifndef SYSTEM_REINIT_SENSORS
#define SYSTEM_REINIT_SENSORS 12U
#endif /* SYSTEM_REINIT_SENSORS */

#ifndef SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY
#define SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY 13U
#endif /* SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY */

#ifndef SYSTEM_SET_TO_DEFAULTS_PASSWORD_ENTERED_CORRECTLY
#define SYSTEM_SET_TO_DEFAULTS_PASSWORD_ENTERED_CORRECTLY 14U
#endif /* SYSTEM_SET_TO_DEFAULTS_PASSWORD_ENTERED_CORRECTLY */

#ifndef SYSTEM_BKO1_CONNECTED
#define SYSTEM_BKO1_CONNECTED 15U
#endif /* SYSTEM_BKO1_CONNECTED */


//--------------------------------------------------------------------------
//--------Мин-максные значения основных параметров--------------------------
#define SENSOR_T1_T2_TYPE_MIN					0
#define SENSOR_T1_T2_TYPE_MAX					3
#define SENSOR_T1_ERROR_OVERHEAT_MIN			500
#define SENSOR_T1_ERROR_OVERHEAT_MAX			1250
#define SENSOR_T2_ERROR_OVERHEAT_MIN			400
#define SENSOR_T2_ERROR_OVERHEAT_MAX			700
#define BKO_LOW_SPEED_MIN						35
#define BKO_LOW_SPEED_MAX						92
#define BKO_HIGH_SPEED_MIN						40
#define BKO_HIGH_SPEED_MAX						99
#define LOW_SPEED_BKO_TEMPERATURE_SETTING_MIN	200
#define LOW_SPEED_BKO_TEMPERATURE_SETTING_MAX	2730
#define HEATER_POWER_MIN						20
#define HEATER_POWER_MAX						100
#define MINUTE_MIN								0
#define MINUTE_MAX								59
#define HOUR_MIN								0
#define HOUR_MAX								23
#define DATE_MIN								1
#define DATE_MAX								31
#define MONTH_MIN								1							
#define MONTH_MAX								12
#define YEAR_MIN								0
#define YEAR_MAX								99
#define BUZZER_DUTY_CYCLE_MIN					20
#define BUZZER_DUTY_CYCLE_MAX					80
#define BUZZER_ENABLED_MIN						FALSE
#define BUZZER_ENABLED_MAX						TRUE
#define INNER_TEMPERATURE_SETTING_MIN			0
#define INNER_TEMPERATURE_SETTING_MAX			1200
#define SERIAL_NUMBER_MIN						1
#define SERIAL_NUMBER_MAX						255
#define CURRENT_SHIFT_MIN						-2000
#define CURRENT_SHIFT_MAX						2000
#define VOLTAGE_SHIFT_MIN						-2000
#define VOLTAGE_SHIFT_MAX						2000
#define INNER_TEMPERATURE_SHIFT_MIN				-50
#define INNER_TEMPERATURE_SHIFT_MAX				50
#define T1_TEMPERATURE_SHIFT_MIN				-50
#define T1_TEMPERATURE_SHIFT_MAX				50
#define T2_TEMPERATURE_SHIFT_MIN				-50
#define T2_TEMPERATURE_SHIFT_MAX				50
#define BKO_TEMPERATURE_SHIFT_MIN				-50
#define BKO_TEMPERATURE_SHIFT_MAX				50
#define PASSWORD_MIN							0
#define PASSWORD_MAX							9999
#define BU_SH_D_ADDRESS_MIN						1
#define BU_SH_D_ADDRESS_MAX						255
#define BU_SH_D_PROT_MIN						0
#define BU_SH_D_PROT_MAX						1
#define BU_SH_D_BAUD_MIN						0
#define BU_SH_D_BAUD_MAX						4
#define IT3_ADDRESS_MIN							1
#define IT3_ADDRESS_MAX							32
#define BKO_SENSOR_ERRORS_ENABLED_MIN			FALSE
#define BKO_SENSOR_ERRORS_ENABLED_MAX			TRUE

//--------------------------------------------------------------------------
//--------Основная структура данных-----------------------------------------
struct bu_shd_r_m_data
{
	uint8_t programm_version_00;
	
	uint8_t serial_number;
	uint8_t production_month;
	uint8_t production_year;
	
	int16_t inner_temperature_setting_grad10;
	int16_t t1_temperature_setting_grad10;
	int16_t t2_temperature_setting_grad10;
	int16_t low_speed_bko_temperature_setting_grad10;
	int16_t finish_regen_setting_grad10;
	int16_t current_setting_break_shd;
	int16_t current_setting_break_heater;
	int16_t current_setting_overload;
	uint8_t bko_sensor_errors_enabled;

	int16_t inner_temperature_shift;
	int16_t t1_temperature_shift;
	int16_t t2_temperature_shift;
	int16_t bko1_temperature_shift;
	int16_t current_shift;
	int16_t voltage_shift;
	
	uint8_t t1_type;
	uint8_t t2_type;
	
	uint16_t pul_rev_selected;
	uint8_t rpm_low_s_selected;
	uint8_t rpm_high_s_selected;
	
	uint8_t heater_power;
	uint8_t heater_resistance;
	
	uint8_t buzzer_duty_cycle;
	uint8_t buzzer_enabled;
	
	uint16_t operation_time_1000_h;
	uint16_t operation_time_h10;
	
	int16_t inner_temperature_grad10;
	int16_t t1_temperature_grad10;
	int16_t t2_temperature_grad10;
	int16_t bko1_temperature_grad10;
	uint16_t voltage;
	int16_t current;
	
	uint16_t right_password;
	uint16_t to_defaults_password;
	
	uint8_t du_address;
	uint8_t du_prot;
	uint8_t du_baudrate;
	
	uint8_t it3_address;
	uint8_t it3_reset_enabled; //пока эта функция не используется
	uint8_t it3_dot_position; //(0 - 0,1; 1 - 0,01)
	uint16_t it3_temperature;
	
	uint32_t error_flags;
	uint16_t system_flags;
	
	uint8_t archive_starting_record;
	
	uint16_t digital_input; 
	
	uint8_t keyboard_autorepeat_mode_on;
	
};

=======
/*!
\file
\defgroup BU-ShD-R-M
\brief Заголовочный файл BU-ShD-R-M_struct.h

С помощью этого заголовочного файла определены структуры данных основной программы
*/

#ifndef BU_SHD_R_M_STRUCT_H_
#define BU_SHD_R_M_STRUCT_H_

//----------------------------------------------------------------------------------
//--------Флаги ошибок--------------------------------------------------------------

#ifndef ERROR_T1_SHORT
#define ERROR_T1_SHORT 0U
#endif /* ERROR_T1_SHORT */

#ifndef ERROR_T1_BREAK
#define ERROR_T1_BREAK 1U
#endif /* ERROR_T1_BREAK */

#ifndef ERROR_T1_OVERHEAT
#define ERROR_T1_OVERHEAT 2U
#endif /* ERROR_T1_OVERHEAT */

#ifndef ERROR_T2_SHORT
#define ERROR_T2_SHORT 3U
#endif /* ERROR_T2_SHORT */

#ifndef ERROR_T2_BREAK
#define ERROR_T2_BREAK 4U
#endif /* ERROR_T2_BREAK */

#ifndef ERROR_T2_OVERHEAT
#define ERROR_T2_OVERHEAT 5U
#endif /* ERROR_T2_OVERHEAT */

#ifndef ERROR_KU_PHASE_A
#define ERROR_KU_PHASE_A 6U
#endif /* ERROR_KU_PHASE_A */

#ifndef ERROR_KU_PHASE_B
#define ERROR_KU_PHASE_B 7U
#endif /* ERROR_KU_PHASE_B */

#ifndef ERROR_KU_PHASE_C
#define ERROR_KU_PHASE_C 8U
#endif /* ERROR_KU_PHASE_C */

#ifndef ERROR_KU_WRONG_PHASE_SEQUENCE
#define ERROR_KU_WRONG_PHASE_SEQUENCE 9U
#endif /* ERROR_KU_WRONG_PHASE_SEQUENCE */

#ifndef ERROR_KU_OVERLOAD
#define ERROR_KU_OVERLOAD 10U
#endif /* ERROR_KU_OVERLOAD */

#ifndef ERROR_BKO_OVERLOAD
#define ERROR_BKO_OVERLOAD 11U
#endif /* ERROR_BKO_OVERLOAD */

#ifndef ERROR_STEPPER_CURCUIT_BREAK
#define ERROR_STEPPER_CURCUIT_BREAK 12U
#endif /* ERROR_STEPPER_CURCUIT_BREAK */

#ifndef ERROR_HEATER_SHORT
#define ERROR_HEATER_SHORT 13U
#endif /* ERROR_HEATER_SHORT */

#ifndef ERROR_HEATER_BREAK
#define ERROR_HEATER_BREAK 14U
#endif /* ERROR_HEATER_BREAK */

#ifndef ERROR_BKO_SENSOR_SHORT
#define ERROR_BKO_SENSOR_SHORT 15U
#endif /* ERROR_BKO_SENSOR_SHORT */

#ifndef ERROR_BKO_SENSOR_BREAK
#define ERROR_BKO_SENSOR_BREAK 16U
#endif /* ERROR_BKO_SENSOR_BREAK */

#ifndef ERROR_BKO_NOT_CONNECTED
#define ERROR_BKO_NOT_CONNECTED 17U
#endif /* ERROR_BKO_NOT_CONNECTED */

#ifndef ERROR_IT3_NO_CONNECTION
#define ERROR_IT3_NO_CONNECTION 18U
#endif /* ERROR_IT3_NO_CONNECTION */

#ifndef ERROR_BKO_SENSOR_T_LOWER_73_K
#define ERROR_BKO_SENSOR_T_LOWER_73_K 19U
#endif /* ERROR_BKO_SENSOR_T_LOWER_73_K */

#ifndef ERROR_CHANGE_ADSORBER
#define ERROR_CHANGE_ADSORBER 20U
#endif /* ERROR_CHANGE_ADSORBER */

//-----------------------------------------------------------------------------
//--------Флаги состояния БУ ШД------------------------------------------------
#ifndef SYSTEM_KU
#define SYSTEM_KU 0U
#endif /* SYSTEM_KU */

#ifndef SYSTEM_FAN
#define SYSTEM_FAN 1U
#endif /* SYSTEM_FAN */

#ifndef SYSTEM_BKO1
#define SYSTEM_BKO1 2U
#endif /* SYSTEM_BKO1 */

#ifndef SYSTEM_BKO2
#define SYSTEM_BKO2 3U
#endif /* SYSTEM_BKO2 */

#ifndef SYSTEM_HEATER1
#define SYSTEM_HEATER1 4U
#endif /* SYSTEM_HEATER1 */

#ifndef SYSTEM_HEATER2
#define SYSTEM_HEATER2 5U
#endif /* SYSTEM_HEATER2 */

#ifndef SYSTEM_MO_II_ACTIVE
#define SYSTEM_MO_II_ACTIVE 6U
#endif /* SYSTEM_HEATER2 */

#ifndef SYSTEM_UPDATE_EEPROM
#define SYSTEM_UPDATE_EEPROM 9U
#endif /* SYSTEM_UPDATE_EEPROM */

#ifndef SYSTEM_REINIT_FROM_EEPROM
#define SYSTEM_REINIT_FROM_EEPROM 10U
#endif /* SYSTEM_REINIT_FROM_EEPROM */

#ifndef SYSTEM_UPDATE_TIME_IN_EEPROM
#define SYSTEM_UPDATE_TIME_IN_EEPROM 11U
#endif /* SYSTEM_UPDATE_TIME_IN_EEPROM */

#ifndef SYSTEM_REINIT_SENSORS
#define SYSTEM_REINIT_SENSORS 12U
#endif /* SYSTEM_REINIT_SENSORS */

#ifndef SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY
#define SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY 13U
#endif /* SYSTEM_MAIN_PASSWORD_ENTERED_CORRECTLY */

#ifndef SYSTEM_SET_TO_DEFAULTS_PASSWORD_ENTERED_CORRECTLY
#define SYSTEM_SET_TO_DEFAULTS_PASSWORD_ENTERED_CORRECTLY 14U
#endif /* SYSTEM_SET_TO_DEFAULTS_PASSWORD_ENTERED_CORRECTLY */

#ifndef SYSTEM_BKO1_CONNECTED
#define SYSTEM_BKO1_CONNECTED 15U
#endif /* SYSTEM_BKO1_CONNECTED */


//--------------------------------------------------------------------------
//--------Мин-максные значения основных параметров--------------------------
#define SENSOR_T1_T2_TYPE_MIN					0
#define SENSOR_T1_T2_TYPE_MAX					3
#define SENSOR_T1_ERROR_OVERHEAT_MIN			500
#define SENSOR_T1_ERROR_OVERHEAT_MAX			1250
#define SENSOR_T2_ERROR_OVERHEAT_MIN			400
#define SENSOR_T2_ERROR_OVERHEAT_MAX			700
#define BKO_LOW_SPEED_MIN						35
#define BKO_LOW_SPEED_MAX						92
#define BKO_HIGH_SPEED_MIN						40
#define BKO_HIGH_SPEED_MAX						99
#define LOW_SPEED_BKO_TEMPERATURE_SETTING_MIN	200
#define LOW_SPEED_BKO_TEMPERATURE_SETTING_MAX	2730
#define HEATER_POWER_MIN						20
#define HEATER_POWER_MAX						100
#define MINUTE_MIN								0
#define MINUTE_MAX								59
#define HOUR_MIN								0
#define HOUR_MAX								23
#define DATE_MIN								1
#define DATE_MAX								31
#define MONTH_MIN								1							
#define MONTH_MAX								12
#define YEAR_MIN								0
#define YEAR_MAX								99
#define BUZZER_DUTY_CYCLE_MIN					20
#define BUZZER_DUTY_CYCLE_MAX					80
#define BUZZER_ENABLED_MIN						FALSE
#define BUZZER_ENABLED_MAX						TRUE
#define INNER_TEMPERATURE_SETTING_MIN			0
#define INNER_TEMPERATURE_SETTING_MAX			1200
#define SERIAL_NUMBER_MIN						1
#define SERIAL_NUMBER_MAX						255
#define CURRENT_SHIFT_MIN						-2000
#define CURRENT_SHIFT_MAX						2000
#define VOLTAGE_SHIFT_MIN						-2000
#define VOLTAGE_SHIFT_MAX						2000
#define INNER_TEMPERATURE_SHIFT_MIN				-50
#define INNER_TEMPERATURE_SHIFT_MAX				50
#define T1_TEMPERATURE_SHIFT_MIN				-50
#define T1_TEMPERATURE_SHIFT_MAX				50
#define T2_TEMPERATURE_SHIFT_MIN				-50
#define T2_TEMPERATURE_SHIFT_MAX				50
#define BKO_TEMPERATURE_SHIFT_MIN				-50
#define BKO_TEMPERATURE_SHIFT_MAX				50
#define PASSWORD_MIN							0
#define PASSWORD_MAX							9999
#define BU_SH_D_ADDRESS_MIN						1
#define BU_SH_D_ADDRESS_MAX						255
#define BU_SH_D_PROT_MIN						0
#define BU_SH_D_PROT_MAX						1
#define BU_SH_D_BAUD_MIN						0
#define BU_SH_D_BAUD_MAX						4
#define IT3_ADDRESS_MIN							1
#define IT3_ADDRESS_MAX							32
#define BKO_SENSOR_ERRORS_ENABLED_MIN			FALSE
#define BKO_SENSOR_ERRORS_ENABLED_MAX			TRUE

//--------------------------------------------------------------------------
//--------Основная структура данных-----------------------------------------
struct bu_shd_r_m_data
{
	uint8_t programm_version_00;
	
	uint8_t serial_number;
	uint8_t production_month;
	uint8_t production_year;
	
	int16_t inner_temperature_setting_grad10;
	int16_t t1_temperature_setting_grad10;
	int16_t t2_temperature_setting_grad10;
	int16_t low_speed_bko_temperature_setting_grad10;
	int16_t finish_regen_setting_grad10;
	int16_t current_setting_break_shd;
	int16_t current_setting_break_heater;
	int16_t current_setting_overload;
	uint8_t bko_sensor_errors_enabled;

	int16_t inner_temperature_shift;
	int16_t t1_temperature_shift;
	int16_t t2_temperature_shift;
	int16_t bko1_temperature_shift;
	int16_t current_shift;
	int16_t voltage_shift;
	
	uint8_t t1_type;
	uint8_t t2_type;
	
	uint16_t pul_rev_selected;
	uint8_t rpm_low_s_selected;
	uint8_t rpm_high_s_selected;
	
	uint8_t heater_power;
	uint8_t heater_resistance;
	
	uint8_t buzzer_duty_cycle;
	uint8_t buzzer_enabled;
	
	uint16_t operation_time_1000_h;
	uint16_t operation_time_h10;
	
	int16_t inner_temperature_grad10;
	int16_t t1_temperature_grad10;
	int16_t t2_temperature_grad10;
	int16_t bko1_temperature_grad10;
	uint16_t voltage;
	int16_t current;
	
	uint16_t right_password;
	uint16_t to_defaults_password;
	
	uint8_t du_address;
	uint8_t du_prot;
	uint8_t du_baudrate;
	
	uint8_t it3_address;
	uint8_t it3_reset_enabled; //пока эта функция не используется
	uint8_t it3_dot_position; //(0 - 0,1; 1 - 0,01)
	uint16_t it3_temperature;
	
	uint32_t error_flags;
	uint16_t system_flags;
	
	uint8_t archive_starting_record;
	
	uint16_t digital_input; 
	
	uint8_t keyboard_autorepeat_mode_on;
	
};

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* BU-SHD-R-M_STRUCT_H_ */