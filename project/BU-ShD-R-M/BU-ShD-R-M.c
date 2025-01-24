/*! 
  \file
  \defgroup		BU-ShD-R-M
  \brief		Файл исходного кода программы BU-ShD-R-M.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя программу для управления блоком управления БУ-ШД-Р-М
  Для корректной компиляции частота работы контроллера должна быть передана чарез опции компилятора (-D) F_CPU=14745600UL
  Для корректной компиляции опорное напряжение должно быть передано чарез опции компилятора (-D) V_REF_MV=2501U
 
  - Compiler:           GNU AVR toolchain         
*/

/*
* -----Fuses-----
* High		0x91
* Low		0xBF
* Extended	0xFF
*/

#include "BU-ShD-R-M_config.h"
#include "BU-ShD-R-M_struct.h"

uint8_t button_array[17];

struct ds1302_data ds1302_time;
struct kty82_data kty82_110_temperature;
struct voltage_divider_data voltage_divider;
struct ds1302_data ds1302_time;
struct dm542_driver_data dm542_driver1;
struct buzzer_data buzzer1;
struct status_led_data status_led1;
struct t_100p_data sensor_100p1;
struct t_100p_data sensor_100p2;
struct pt100_pt300_data sensor_pt100_1;
struct pt100_pt300_data sensor_pt100_2;
struct bu_shd_r_m_data bu_shd_r_m;
struct fan_data fan;
struct heater_data heater1;
struct current_shunt_data current_shunt1;
struct adm2483brw_data adm2483brw1_d7;
struct adm2483brw_data adm2483brw1_d8;

uint8_t EEMEM eeprom_serial_number									= 1;
uint8_t EEMEM eeprom_production_month								= 7;
uint8_t EEMEM eeprom_production_year								= 24;
int16_t EEMEM eeprom_inner_temperature_setting_grad10				= 450;
int16_t EEMEM eeprom_t1_temperature_setting_grad10					= 820;
int16_t EEMEM eeprom_t2_temperature_setting_grad10					= 520;
int16_t EEMEM eeprom_low_speed_bko_temperature_setting_grad10		= 220;
int16_t EEMEM eeprom_t1_temperature_shift							= 4;
int16_t EEMEM eeprom_t2_temperature_shift							= 9;
int16_t EEMEM eeprom_bko1_temperature_shift							= 0;
uint8_t EEMEM eeprom_t1_type										= PT100_MODE;
uint8_t EEMEM eeprom_t2_type										= PT100_MODE;
uint8_t EEMEM eeprom_heater_power									= 30;
uint8_t EEMEM eeprom_rpm_low_speed_selected							= 76;
uint8_t EEMEM eeprom_rpm_high_speed_selected						= 96;
uint8_t EEMEM eeprom_buzzer_duty_cycle								= 70;
uint8_t EEMEM eeprom_buzzer_enabled									= TRUE;
uint8_t EEMEM eeprom_bko_sensor_errors_enabled						= TRUE;
uint16_t EEMEM eeprom_operation_time_1000_h							= 0;
uint16_t EEMEM eeprom_operation_time_h10							= 0;
uint8_t EEMEM archive_starting_record								= 0;
uint8_t EEMEM eeprom_it3_address									= 1;

uint8_t EEMEM eeprom_du_address										= 1;
uint8_t EEMEM eeprom_du_prot										= PROT_TYPE_MODBUS;
uint8_t EEMEM eeprom_du_baudrate									= MODBUS_BAUDRATE_57600;

uint8_t EEMEM eeprom_mo2_active										= TRUE;

uint8_t EEMEM eeprom_adsorber_is_ok									= TRUE;

struct archive_record EEMEM bu_shd_r_m_archive[FSM_ARCHIVE_SIZE+1];

void bu_shd_r_m_main_structure_init(void)
{
	bu_shd_r_m.programm_version_00							= 5;
	
	bu_shd_r_m.serial_number								= eeprom_read_byte(&eeprom_serial_number);
	bu_shd_r_m.production_month								= eeprom_read_byte(&eeprom_production_month);
	bu_shd_r_m.production_year								= eeprom_read_byte(&eeprom_production_year);
	
	bu_shd_r_m.inner_temperature_setting_grad10				= eeprom_read_word(&eeprom_inner_temperature_setting_grad10);
	bu_shd_r_m.t1_temperature_setting_grad10				= eeprom_read_word(&eeprom_t1_temperature_setting_grad10);
	bu_shd_r_m.t2_temperature_setting_grad10				= eeprom_read_word(&eeprom_t2_temperature_setting_grad10);
	bu_shd_r_m.low_speed_bko_temperature_setting_grad10		= eeprom_read_word(&eeprom_low_speed_bko_temperature_setting_grad10);
	bu_shd_r_m.finish_regen_setting_grad10					= 3130;
	bu_shd_r_m.current_setting_break_shd					= 150;
	bu_shd_r_m.current_setting_break_heater					= 200;
	bu_shd_r_m.current_setting_overload						= 3200;
	bu_shd_r_m.bko_sensor_errors_enabled					= eeprom_read_byte(&eeprom_bko_sensor_errors_enabled);
	
	bu_shd_r_m.inner_temperature_shift						= -1;
	bu_shd_r_m.t1_temperature_shift							= eeprom_read_word(&eeprom_t1_temperature_shift);
	bu_shd_r_m.t2_temperature_shift							= eeprom_read_word(&eeprom_t2_temperature_shift);
	bu_shd_r_m.bko1_temperature_shift						= eeprom_read_word(&eeprom_bko1_temperature_shift);
	bu_shd_r_m.current_shift								= -1750;
	bu_shd_r_m.voltage_shift								= 300;
	
	bu_shd_r_m.t1_type										= eeprom_read_byte(&eeprom_t1_type);
	bu_shd_r_m.t2_type										= eeprom_read_byte(&eeprom_t2_type);
	
	bu_shd_r_m.pul_rev_selected								= 25000;
	bu_shd_r_m.rpm_low_s_selected							= eeprom_read_byte(&eeprom_rpm_low_speed_selected);
	bu_shd_r_m.rpm_high_s_selected							= eeprom_read_byte(&eeprom_rpm_high_speed_selected);
	
	bu_shd_r_m.heater_power									= eeprom_read_byte(&eeprom_heater_power);
	bu_shd_r_m.heater_resistance							= 100;
	
	bu_shd_r_m.buzzer_duty_cycle							= eeprom_read_byte(&eeprom_buzzer_duty_cycle);
	bu_shd_r_m.buzzer_enabled								= eeprom_read_byte(&eeprom_buzzer_enabled);
	
	bu_shd_r_m.operation_time_1000_h						= eeprom_read_word(&eeprom_operation_time_1000_h);
	bu_shd_r_m.operation_time_h10							= eeprom_read_word(&eeprom_operation_time_h10);	
	
	bu_shd_r_m.right_password								= 10;
	bu_shd_r_m.to_defaults_password							= 15;
	
	bu_shd_r_m.it3_address									= eeprom_read_byte(&eeprom_it3_address);
	bu_shd_r_m.it3_dot_position								= 0;
	
	bu_shd_r_m.du_address									= eeprom_read_byte(&eeprom_du_address);
	bu_shd_r_m.du_prot										= eeprom_read_byte(&eeprom_du_prot);
	bu_shd_r_m.du_baudrate									= eeprom_read_byte(&eeprom_du_baudrate);
	
	bu_shd_r_m.error_flags									= 0;
	bu_shd_r_m.system_flags									= 0;
	
	bu_shd_r_m.archive_starting_record						= eeprom_read_byte(&archive_starting_record);
	
	bu_shd_r_m.digital_input								= 0;
	
	if (eeprom_read_byte(&eeprom_mo2_active))
	{
		bu_shd_r_m.system_flags |= (1 << SYSTEM_MO_II_ACTIVE);
	}
	
	if (eeprom_read_byte(&eeprom_adsorber_is_ok) == FALSE)
	{
		bu_shd_r_m.error_flags |= ((uint32_t)1 << ERROR_CHANGE_ADSORBER);
	}
}

void bu_shd_r_m_update_eeprom(void)
{
	eeprom_write_byte(&eeprom_serial_number, bu_shd_r_m.serial_number);
	eeprom_write_byte(&eeprom_production_month, bu_shd_r_m.production_month);
	eeprom_write_byte(&eeprom_production_year, bu_shd_r_m.production_year);
	eeprom_write_byte(&eeprom_rpm_low_speed_selected, bu_shd_r_m.rpm_low_s_selected);
	eeprom_write_byte(&eeprom_rpm_high_speed_selected, bu_shd_r_m.rpm_high_s_selected);
	eeprom_write_byte(&eeprom_heater_power, bu_shd_r_m.heater_power);
	eeprom_write_byte(&eeprom_buzzer_duty_cycle, bu_shd_r_m.buzzer_duty_cycle);
	eeprom_write_byte(&eeprom_buzzer_enabled, bu_shd_r_m.buzzer_enabled);
	eeprom_write_byte(&eeprom_t1_type, bu_shd_r_m.t1_type);
	eeprom_write_byte(&eeprom_t2_type, bu_shd_r_m.t2_type);
	eeprom_write_byte(&eeprom_du_address, bu_shd_r_m.du_address);
	eeprom_write_byte(&eeprom_du_prot, bu_shd_r_m.du_prot);
	eeprom_write_byte(&eeprom_du_baudrate, bu_shd_r_m.du_baudrate);
	eeprom_write_byte(&eeprom_it3_address, bu_shd_r_m.it3_address);
	eeprom_write_byte(&eeprom_bko_sensor_errors_enabled, bu_shd_r_m.bko_sensor_errors_enabled);
	
	eeprom_write_word(&eeprom_inner_temperature_setting_grad10, bu_shd_r_m.inner_temperature_setting_grad10);
	eeprom_write_word(&eeprom_t1_temperature_setting_grad10, bu_shd_r_m.t1_temperature_setting_grad10);
	eeprom_write_word(&eeprom_t2_temperature_setting_grad10, bu_shd_r_m.t2_temperature_setting_grad10);
	eeprom_write_word(&eeprom_low_speed_bko_temperature_setting_grad10, bu_shd_r_m.low_speed_bko_temperature_setting_grad10);
	eeprom_write_word(&eeprom_t1_temperature_shift, bu_shd_r_m.t1_temperature_shift);
	eeprom_write_word(&eeprom_t2_temperature_shift, bu_shd_r_m.t2_temperature_shift);
	eeprom_write_word(&eeprom_bko1_temperature_shift, bu_shd_r_m.bko1_temperature_shift);
	eeprom_write_word(&eeprom_operation_time_1000_h, bu_shd_r_m.operation_time_1000_h);
	eeprom_write_word(&eeprom_operation_time_h10, bu_shd_r_m.operation_time_h10);
}

void bu_shd_r_m_reinit_from_eeprom(void)
{
	bu_shd_r_m.serial_number								= eeprom_read_byte(&eeprom_serial_number);
	bu_shd_r_m.production_month								= eeprom_read_byte(&eeprom_production_month);
	bu_shd_r_m.production_year								= eeprom_read_byte(&eeprom_production_year);
	bu_shd_r_m.inner_temperature_setting_grad10				= eeprom_read_word(&eeprom_inner_temperature_setting_grad10);
	bu_shd_r_m.t1_temperature_setting_grad10				= eeprom_read_word(&eeprom_t1_temperature_setting_grad10);
	bu_shd_r_m.t2_temperature_setting_grad10				= eeprom_read_word(&eeprom_t2_temperature_setting_grad10);
	bu_shd_r_m.low_speed_bko_temperature_setting_grad10		= eeprom_read_word(&eeprom_low_speed_bko_temperature_setting_grad10);
	bu_shd_r_m.t1_temperature_shift							= eeprom_read_word(&eeprom_t1_temperature_shift);
	bu_shd_r_m.t2_temperature_shift							= eeprom_read_word(&eeprom_t2_temperature_shift);
	bu_shd_r_m.bko1_temperature_shift						= eeprom_read_word(&eeprom_bko1_temperature_shift);
	bu_shd_r_m.rpm_low_s_selected							= eeprom_read_byte(&eeprom_rpm_low_speed_selected);
	bu_shd_r_m.rpm_high_s_selected							= eeprom_read_byte(&eeprom_rpm_high_speed_selected);
	bu_shd_r_m.heater_power									= eeprom_read_byte(&eeprom_heater_power);
	bu_shd_r_m.buzzer_duty_cycle							= eeprom_read_byte(&eeprom_buzzer_duty_cycle);
	bu_shd_r_m.operation_time_1000_h						= eeprom_read_word(&eeprom_operation_time_1000_h);
	bu_shd_r_m.operation_time_h10							= eeprom_read_word(&eeprom_operation_time_h10);
	bu_shd_r_m.buzzer_enabled								= eeprom_read_byte(&eeprom_buzzer_enabled);
	bu_shd_r_m.t1_type										= eeprom_read_byte(&eeprom_t1_type);
	bu_shd_r_m.t2_type										= eeprom_read_byte(&eeprom_t2_type);
	bu_shd_r_m.du_address									= eeprom_read_byte(&eeprom_du_address);
	bu_shd_r_m.du_prot										= eeprom_read_byte(&eeprom_du_prot);
	bu_shd_r_m.du_baudrate									= eeprom_read_byte(&eeprom_du_baudrate);
	bu_shd_r_m.it3_address									= eeprom_read_byte(&eeprom_it3_address);
	bu_shd_r_m.bko_sensor_errors_enabled					= eeprom_read_byte(&eeprom_bko_sensor_errors_enabled);
}

void bu_shd_r_m_update_time_in_eeprom(void)
{
	eeprom_write_word(&eeprom_operation_time_1000_h, bu_shd_r_m.operation_time_1000_h);
	eeprom_write_word(&eeprom_operation_time_h10, bu_shd_r_m.operation_time_h10);
}

void bu_shd_r_m_update_adsorber_status_in_eeprom(void)
{
	if ((bu_shd_r_m.error_flags & ((uint32_t)1 << ERROR_CHANGE_ADSORBER)) && (eeprom_read_byte(&eeprom_adsorber_is_ok) == TRUE))
	{
		eeprom_write_byte(&eeprom_adsorber_is_ok, FALSE);
	}
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_AFSORBER_EEPROM))
	{
		eeprom_write_byte(&eeprom_adsorber_is_ok, TRUE);
		eeprom_write_word(&eeprom_operation_time_h10, 1);
		bu_shd_r_m.operation_time_h10 = eeprom_read_word(&eeprom_operation_time_h10);
	}
}

void bu_shd_r_m_set_eeprom_to_defaults(void)
{
	eeprom_write_byte(&eeprom_rpm_low_speed_selected, 60);
	eeprom_write_byte(&eeprom_rpm_high_speed_selected, 96);
	eeprom_write_byte(&eeprom_heater_power, 100);
	eeprom_write_byte(&eeprom_buzzer_duty_cycle, 100);
	eeprom_write_byte(&eeprom_buzzer_enabled, TRUE);
	eeprom_write_byte(&eeprom_t1_type, PT100_MODE);
	eeprom_write_byte(&eeprom_t2_type, PT100_MODE);
	eeprom_write_word(&eeprom_inner_temperature_setting_grad10, 450);
	eeprom_write_word(&eeprom_t1_temperature_setting_grad10, 820);
	eeprom_write_word(&eeprom_t2_temperature_setting_grad10, 520);
	eeprom_write_word(&eeprom_low_speed_bko_temperature_setting_grad10, 220);
	eeprom_write_word(&eeprom_t1_temperature_shift, 4);
	eeprom_write_word(&eeprom_t2_temperature_shift, 9);
	eeprom_write_word(&eeprom_bko1_temperature_shift, -1);
	eeprom_write_byte(&eeprom_du_address, 1);
	eeprom_write_byte(&eeprom_du_prot, PROT_TYPE_MODBUS);
	eeprom_write_byte(&eeprom_du_baudrate, MODBUS_BAUDRATE_57600);
	eeprom_write_byte(&eeprom_it3_address, 1);
	eeprom_write_byte(&eeprom_bko_sensor_errors_enabled, TRUE);
}

void eeprom_process(void)
{
	if (fsm_messages_get_broadcast_message(MSG_MODE_CHANGE))
	{
		if (bu_shd_r_m.system_flags & (1 << SYSTEM_MO_II_ACTIVE))
		{
			eeprom_write_byte(&eeprom_mo2_active, TRUE);
		}
		else
		{
			eeprom_write_byte(&eeprom_mo2_active, FALSE);
		}
	}
	if (fsm_messages_get_broadcast_message(MSG_UPDATE_AFSORBER_EEPROM))
	{
		bu_shd_r_m_update_adsorber_status_in_eeprom();
	}
	if (eeprom_read_byte(&eeprom_adsorber_is_ok) == FALSE)
	{
		bu_shd_r_m.error_flags |= ((uint32_t)1 << ERROR_CHANGE_ADSORBER);
	}
	if (bu_shd_r_m.system_flags & (1 << SYSTEM_UPDATE_EEPROM))
	{
		bu_shd_r_m_update_eeprom();
		fsm_regenerator_init(&heater1, 48 /*регулируемое напряжение, вольт*/, bu_shd_r_m.heater_power, bu_shd_r_m.heater_resistance, PE4, &PORTE);
		fsm_buzzer_init(&buzzer1, bu_shd_r_m.buzzer_duty_cycle, FSM_BUZZER_SOUND_GENERATION_PERIOD_MS, PD5, &PORTD);	
		bu_shd_r_m.system_flags &= ~(1 << SYSTEM_UPDATE_EEPROM);
		fsm_messages_send_broadcast_message(MSG_EEPROM_UPDATED);
	}
	if (bu_shd_r_m.system_flags & (1 << SYSTEM_REINIT_FROM_EEPROM))
	{
		bu_shd_r_m_reinit_from_eeprom();
		bu_shd_r_m.system_flags &= ~(1 << SYSTEM_REINIT_FROM_EEPROM);
	}
	if (bu_shd_r_m.system_flags & (1 << SYSTEM_UPDATE_TIME_IN_EEPROM))
	{
		bu_shd_r_m_update_time_in_eeprom();
		bu_shd_r_m.system_flags &= ~(1 << SYSTEM_UPDATE_TIME_IN_EEPROM);
	}
	if (bu_shd_r_m.system_flags & (1 << SYSTEM_SET_TO_DEFAULTS_PASSWORD_ENTERED_CORRECTLY))
	{
		bu_shd_r_m_set_eeprom_to_defaults();
		bu_shd_r_m_reinit_from_eeprom();
		bu_shd_r_m.system_flags &= ~(1 << SYSTEM_SET_TO_DEFAULTS_PASSWORD_ENTERED_CORRECTLY);
	}		
}

void bu_shd_r_m_reinit_sensors(void)
{
	if (bu_shd_r_m.system_flags & (1 << SYSTEM_REINIT_SENSORS))
	{
		fsm_t1_temp_sensor_init(&bu_shd_r_m, &sensor_pt100_1, bu_shd_r_m.t1_type, PB0, &PORTB, 0/*номер пина ацп*/, V_REF_MV);
		hal_pt100_pt300_set_temperature_shift(&sensor_pt100_1, bu_shd_r_m.t1_temperature_shift);
		fsm_t2_temp_sensor_init(&bu_shd_r_m, &sensor_pt100_2, bu_shd_r_m.t2_type, PD0, &PORTD, 1/*номер пина ацп*/, V_REF_MV);
		hal_pt100_pt300_set_temperature_shift(&sensor_pt100_2, bu_shd_r_m.t2_temperature_shift);
		fsm_bko_temp_sensor_init(&bu_shd_r_m, &sensor_100p1, 2/*номер пина ацп*/, V_REF_MV, PD1, &PORTD, bu_shd_r_m.bko1_temperature_shift);
		fsm_current_sensor_init(&bu_shd_r_m.current, &current_shunt1, 4/*номер пина ацп*/, V_REF_MV, 10/*сопротивление шунта умноженное на 100*/, bu_shd_r_m.current_shift);
		fsm_voltage_sensor_init(&bu_shd_r_m.voltage, &voltage_divider, 6/*номер пина ацп*/, V_REF_MV, bu_shd_r_m.voltage_shift);
		fsm_inner_temp_sensor_init(&bu_shd_r_m.inner_temperature_grad10, &kty82_110_temperature, KTY82_110, 7/*номер пина ацп*/);
		hal_kty82_set_initial_temperature_shift(&kty82_110_temperature, bu_shd_r_m.inner_temperature_shift);		
		bu_shd_r_m.system_flags &= ~(1 << SYSTEM_REINIT_SENSORS);
	}	
}

int main(void)
{
	cli();
	
	bu_shd_r_m_main_structure_init();

	fsm_fan_init(&fan, PE7, &PORTE);
	fsm_buzzer_init(&buzzer1, bu_shd_r_m.buzzer_duty_cycle, FSM_BUZZER_SOUND_GENERATION_PERIOD_MS, PD5, &PORTD);
	fsm_ku_init(PG0, &PORTG);
	fsm_regenerator_init(&heater1, 48 /*регулируемое напряжение, вольт*/, bu_shd_r_m.heater_power, bu_shd_r_m.heater_resistance, PE4, &PORTE);
	fsm_bko_init(&dm542_driver1, PB4, PB5, &PORTB, PE3, &PORTE, PC0, &PORTC, F_CPU);

	fsm_led_vector_init();
	fsm_ui_init();
	fsm_status_led_init(&status_led1, PC7, &PORTC);
	fsm_keyboard_init();
	
	fsm_t1_temp_sensor_init(&bu_shd_r_m, &sensor_pt100_1, bu_shd_r_m.t1_type, PB0, &PORTB, 0/*номер пина ацп*/, V_REF_MV);
	hal_pt100_pt300_set_temperature_shift(&sensor_pt100_1, bu_shd_r_m.t1_temperature_shift);	
	fsm_t2_temp_sensor_init(&bu_shd_r_m, &sensor_pt100_2, bu_shd_r_m.t2_type, PD0, &PORTD, 1/*номер пина ацп*/, V_REF_MV);
	hal_pt100_pt300_set_temperature_shift(&sensor_pt100_2, bu_shd_r_m.t2_temperature_shift);	
	fsm_bko_temp_sensor_init(&bu_shd_r_m, &sensor_100p1, 2/*номер пина ацп*/, V_REF_MV, PD1, &PORTD, bu_shd_r_m.bko1_temperature_shift);
	fsm_current_sensor_init(&bu_shd_r_m.current, &current_shunt1, 4/*номер пина ацп*/, V_REF_MV, 10/*сопротивление шунта умноженное на 100*/, bu_shd_r_m.current_shift);
	fsm_voltage_sensor_init(&bu_shd_r_m.voltage, &voltage_divider, 6/*номер пина ацп*/, V_REF_MV, bu_shd_r_m.voltage_shift);
	fsm_inner_temp_sensor_init(&bu_shd_r_m.inner_temperature_grad10, &kty82_110_temperature, KTY82_110, 7/*номер мина ацп*/);
	hal_kty82_set_initial_temperature_shift(&kty82_110_temperature, bu_shd_r_m.inner_temperature_shift);

	fsm_modbus_rtu_init(&adm2483brw1_d7, &bu_shd_r_m, fsm_modbus_rtu_calculate_baud(bu_shd_r_m.du_baudrate), PE2/*пин включения разрешения передачи*/, &PORTE/*порт дискретного вывода разрешения передачи*/, F_CPU);
	fsm_it3_init(&adm2483brw1_d8, &bu_shd_r_m, PA3/*пин включения разрешения передачи*/, &PORTA/*порт дискретного вывода разрешения передачи*/, F_CPU);

	fsm_phase_controller_init();
	fsm_digital_input_init();
	fsm_clock_init(&ds1302_time);
	fsm_time_counter_init();
	virtual_timers_init(1, 13);
	fsm_messages_init();
	fsm_archive_init();
	fsm_error_handler_init();
	
	sei();

	while (1)
	{
		wdt_enable(WDTO_1S);

		fsm_ui_process(&bu_shd_r_m, &ds1302_time, &bu_shd_r_m_archive[0]);

		fsm_buzzer_process(&buzzer1, bu_shd_r_m.buzzer_enabled);
		fsm_status_led_process(&status_led1);
		fsm_keyboard_process(&button_array[0], &bu_shd_r_m);
		fsm_inner_temp_sensor_process(&bu_shd_r_m.inner_temperature_grad10, &kty82_110_temperature);
		fsm_fan_process(&fan, &bu_shd_r_m);
		fsm_led_vector_process(&bu_shd_r_m);
		fsm_ku_process(&bu_shd_r_m);
		fsm_t1_temp_sensor_process(&bu_shd_r_m, &sensor_pt100_1);
		fsm_t2_temp_sensor_process(&bu_shd_r_m, &sensor_pt100_2);
		fsm_voltage_sensor_process(&bu_shd_r_m.voltage, &voltage_divider);
		fsm_bko_temp_sensor_process(&bu_shd_r_m, &sensor_100p1);
		fsm_regenerator_process(&bu_shd_r_m, &heater1);
		fsm_bko_process(&bu_shd_r_m, &dm542_driver1);
		fsm_current_sensor_process(&bu_shd_r_m.current, &current_shunt1);
		fsm_clock_process(&ds1302_time);
		fsm_time_counter_process(&bu_shd_r_m, &ds1302_time.minute);
		fsm_phase_controller_process(&bu_shd_r_m);
		fsm_digital_input_process(&bu_shd_r_m);

		fsm_error_handler_process(&bu_shd_r_m);
		fsm_archive_process(&bu_shd_r_m_archive[0], &bu_shd_r_m, &ds1302_time);
		eeprom_process();
		bu_shd_r_m_reinit_sensors();
		
		virtual_global_timers_process();
		virtual_timers_process();
		fsm_messages_process();

		fsm_modbus_rtu_process(&adm2483brw1_d7, &bu_shd_r_m);
		fsm_it3_process(&adm2483brw1_d8, &bu_shd_r_m);

		wdt_reset();
	}
}