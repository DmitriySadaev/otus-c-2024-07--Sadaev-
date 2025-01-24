/*!
\file
\defgroup hal_t_100p
\brief Заголовочный файл hal_t_100p.h

*/

#ifndef HAL_T_100P_H_
#define HAL_T_100P_H_

#include <stdint.h>
#include "avr_driver_adc.h"

#ifndef T_100P_SHORT
#define T_100P_SHORT 0x8000
#endif /* T_100P_SHORT */

#ifndef T_100P_BREAK
#define T_100P_BREAK 0x8FFF
#endif /* T_100P_BREAK */

struct t_100p_data
{
uint8_t adc_pin;
uint16_t v_ref;													
uint16_t current_adc;		
int16_t temperature_grad10;
int16_t shift_grad10;
uint8_t control_pin;
volatile uint8_t * control_port; 
};

//основные функции
void hal_t_100p_init(struct t_100p_data * t_sensor, uint8_t adc_pin, uint16_t v_ref, uint8_t control_pin, volatile  uint8_t * control_port);
void hal_t_100p_update(struct t_100p_data * t_sensor);

//функция для чтения температуры с учетом сдвига характеристики
int16_t hal_t_100p_read_temperature(struct t_100p_data * t_sensor);

//функция для смещения характеристики
void hal_t_100p_set_temperature_shift(struct t_100p_data * t_sensor, int16_t temperature_shift);

#endif /* HAL_T_100P_H_ */