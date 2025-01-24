/*!
\file
\defgroup hal_current_shunt
\brief Заголовочный файл hal_current_shunt.h

*/

#ifndef HAL_CURRENT_SHUNT_H_
#define HAL_CURRENT_SHUNT_H_

#include <stdint.h>
#include "avr_driver_adc.h"

struct current_shunt_data
{
	uint8_t adc_pin;
	uint16_t v_ref;
	uint8_t r_shunt_100ohm; //умножить на 100 то есть при 0,1 Ом - r_shunt_100ohm = 10
	uint16_t current_adc;
	uint16_t measured_current_ma;
	int16_t shift_ma;
};

void hal_current_shunt_init(struct current_shunt_data * current_shunt, uint8_t adc_pin, uint16_t v_ref, uint16_t r_shunt_100ohm, int16_t shift_ma);
void hal_current_shunt_update(struct current_shunt_data * current_shunt);

int16_t hal_current_shunt_read_current(struct current_shunt_data * current_shunt);

void hal_current_shunt_set_shift(struct current_shunt_data * current_shunt, int16_t shift_ma);

#endif /* HAL_CURRENT_SHUNT_H_ */