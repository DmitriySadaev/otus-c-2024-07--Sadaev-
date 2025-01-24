/*!
\file
\defgroup hal_kty82
\brief Заголовочный файл hal_kty82.h

*/

#ifndef HAL_KTY82_H_
#define HAL_KTY82_H_

#include <stdint.h>
#include "avr_driver_adc.h"

#ifndef KTY82_110
#define KTY82_110 0U
#define KTY82_110_RESISTANCE_DEFAULT_OHM 1000U
#define KTY82_110_TEMPERATURE_DEFAULT_10GRAD 250U
#define KTY82_110_TEMPERATURE_SHIFT_DEFAULT_10GRAD 0
#define KTY82_110_BALLAST_DEFAULT_OHM 2501U
#endif /* KTY82_110 */

// Здесь можно добавить другие датчики, аналогично объявлению KTY82/110

#ifndef V_REF_KTY_MV
#define V_REF_KTY_MV 4940
#endif /* V_REF_KTY_MV */

#ifndef KTY82_SHORT
#define KTY82_SHORT 0x8000
#endif /* KTY82_SHORT */

#ifndef KTY82_BREAK
#define KTY82_BREAK 0x8FFF
#endif /* KTY82_BREAK */

struct kty82_data
{
uint8_t type;
uint8_t adc_pin;
uint16_t v_ref;	
uint16_t v_ref_kty;														
uint16_t initial_kty82_resistance_ohm;	
uint16_t initial_kty82_temperature_grad10;
int16_t shift_grad10;
uint16_t ballast_resistance_ohm;
uint16_t current_adc;		
int16_t temperature_grad10;
};

//основные функции
void hal_kty82_init(struct kty82_data * t_sensor, uint8_t sensor_type, uint8_t sensor_adc_pin);
void hal_kty82_update(struct kty82_data * t_sensor);

//функция для чтения температуры с учетом сдвига характеристики
int16_t hal_kty_read_temperature(struct kty82_data * t_sensor);

//функции для подстройки значений
void hal_kty82_set_initial_kty82_resistance_ohm(struct kty82_data * t_sensor, uint16_t sensor_resistance_25);
void hal_kty82_set_initial_kty82_temperature_grad10(struct kty82_data * t_sensor, uint16_t sensor_resistance_measurement_temperature);
void hal_kty82_set_initial_temperature_shift(struct kty82_data * t_sensor, int16_t temperature_shift);
void hal_kty82_set_ballast_resistance(struct kty82_data * t_sensor, uint16_t ballast_resistance);
void hal_kty82_set_vref(struct kty82_data * t_sensor, uint16_t v_ref);
void hal_kty82_set_vref_kty(struct kty82_data * t_sensor, uint16_t v_ref_kty);

#endif /* HAL_KTY82_H_ */