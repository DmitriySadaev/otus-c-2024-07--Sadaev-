/*!
\file
\defgroup hal_dm542
\brief Заголовочный файл hal_dm542.h

*/

#ifndef HAL_DM542_H_
#define HAL_DM542_H_

#include <avr/io.h>
#include <stdint.h>
#include "avr_driver_timers.h"

struct dm542_driver_data
{
	uint8_t dm542_control_pul_pin;
	uint8_t dm542_control_ena_pin;
	uint8_t dm542_power_drv_pin;
	uint8_t dm542_connection_check_pin;
	volatile uint8_t * dm542_control_port;
	volatile uint8_t * dm542_power_drv_port;
	volatile uint8_t * dm542_connection_check_port;
	uint32_t f_cpu;
};

void hal_dm542_init(struct dm542_driver_data * dm542_driver, uint8_t dm542_control_pul_pin, uint8_t dm542_control_ena_pin, volatile uint8_t * dm542_control_port, uint8_t dm542_power_drv_pin, volatile uint8_t * dm542_power_drv_port, uint8_t dm542_connection_check_pin, volatile uint8_t * dm542_connection_check_port, uint32_t f_cpu);


void hal_dm542_power_drv_on(struct dm542_driver_data * dm542_driver);
void hal_dm542_power_drv_off(struct dm542_driver_data * dm542_driver);
void hal_dm542_control_ena_on(struct dm542_driver_data * dm542_driver);
void hal_dm542_control_ena_off(struct dm542_driver_data * dm542_driver);
void hal_dm542_control_pul_on(struct dm542_driver_data * dm542_driver);
void hal_dm542_control_pul_off(struct dm542_driver_data * dm542_driver);

void hal_dm542_start_rotation(struct dm542_driver_data * dm542_driver, uint16_t pul_rev_selected, uint8_t rpm_selected);
void hal_dm542_stop_rotation(struct dm542_driver_data * dm542_driver);

#endif /* HAL_DM542_H_ */