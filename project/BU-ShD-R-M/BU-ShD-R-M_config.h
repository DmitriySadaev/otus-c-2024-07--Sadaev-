/*!
\file
\defgroup BU-ShD-R-M
\brief Заголовочный файл BU-ShD-R-M_config.h

При помощи этого заголовочного файла осуществлено подключение программых модулей к основной программе
*/

#ifndef BU_SHD_R_M_CONFIG_H_
#define BU_SHD_R_M_CONFIG_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>

#include "fsm_virtual_timers.h"
#include "fsm_messages.h"
#include "fsm_keyboard.h"
#include "fsm_ui_bu_shd_r_m.h"
#include "fsm_buzzer.h"
#include "fsm_status_led.h"
#include "fsm_inner_temp_sensor.h"
#include "fsm_fan.h"
#include "fsm_led_vector.h"
#include "fsm_ku.h"
#include "fsm_t1_sensor.h"
#include "fsm_t2_sensor.h"
#include "fsm_bko_sensor.h"
#include "fsm_bko.h"
#include "fsm_regenerator.h"
#include "fsm_current_sensor.h"
#include "fsm_voltage_sensor.h"
#include "fsm_error_handling.h"
#include "fsm_time_counter.h"
#include "fsm_archive.h"
#include "fsm_phase_controller.h"
#include "fsm_digital_input.h"
#include "fsm_modbus_rtu_slave.h"
#include "fsm_it3.h"

#endif /* BU_SHD_R_M_CONFIG_H_ */