/*!
\file
\defgroup hal_voltage_divider
\brief Заголовочный файл hal_voltage_divider.h

*/

#ifndef HAL_VOLTAGE_DIVIDER_H_
#define HAL_VOLTAGE_DIVIDER_H_

#include <stdint.h>
#include "avr_driver_adc.h"

#ifndef VOLTAGE_DIVIDER_UP_RESISTANCE_DEFAULT_OHM 
#define VOLTAGE_DIVIDER_UP_RESISTANCE_DEFAULT_OHM 56000
#endif /* VOLTAGE_DIVIDER_UP_RESISTANCE_DEFAULT_OHM */

#ifndef VOLTAGE_DIVIDER_LOW_RESISTANCE_DEFAULT_OHM
#define VOLTAGE_DIVIDER_LOW_RESISTANCE_DEFAULT_OHM 2400
#endif /* VOLTAGE_DIVIDER_LOW_RESISTANCE_DEFAULT_OHM */

struct voltage_divider_data
{
uint8_t adc_pin;
uint16_t v_ref;
uint16_t upper_resistor_ohm;
uint16_t lower_resistor_ohm;
uint16_t current_adc;
uint16_t measured_voltage_mv;	
int16_t shift_mv;
};

//основные функции
void hal_voltage_divider_init(struct voltage_divider_data * v_sensor, uint8_t sensor_adc_pin);
void hal_voltage_divider_update(struct voltage_divider_data * v_sensor);

//функция для чтения напряжения с учетом сдвига характеристики
int16_t hal_voltage_divider_read_voltage(struct voltage_divider_data * v_sensor);

//функции для подстройки значений
void hal_voltage_divider_set_vref(struct voltage_divider_data * v_sensor, uint16_t v_ref);
void hal_voltage_divider_set_upper_resistance_ohm(struct voltage_divider_data * v_sensor, uint16_t sensor_resistance);
void hal_voltage_divider_set_lower_resistance_ohm(struct voltage_divider_data * v_sensor, uint16_t sensor_resistance);
void hal_voltage_divider_set_shift(struct voltage_divider_data * v_sensor, int16_t shift);

#endif /* HAL_VOLTAGE_DIVIDER_H_ */