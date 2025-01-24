/*!
\file
\defgroup hal_pt100_pt300
\brief Заголовочный файл hal_pt100_pt300.h

*/

#ifndef HAL_PT100_PT300_H_
#define HAL_PT100_PT300_H_

#include <stdint.h>
#include "avr_driver_adc.h"

#ifndef PT100_MODE
#define PT100_MODE 0U
#endif  /* PT100_MODE */

#ifndef PT300_MODE
#define PT300_MODE 1U
#endif  /* PT300_MODE */

#ifndef CU100_MODE
#define CU100_MODE 2U
#endif  /* CU100_MODE */

#ifndef CU300_MODE
#define CU300_MODE 3U
#endif  /* CU300_MODE */

#ifndef PT100_PT300_SHORT
#define PT100_PT300_SHORT 0x8000
#endif /* PT100_PT300_SHORT */

#ifndef PT100_PT300_BREAK
#define PT100_PT300_BREAK 0x8FFF
#endif /* PT100_PT300_SHORT */

struct pt100_pt300_data
{
	uint8_t pt100_pt300_mode;
	uint8_t pt300_control_pin;
	volatile uint8_t * pt300_control_port;
	uint8_t adc_pin;
	uint16_t v_ref;													
	uint16_t current_adc;		
	int16_t temperature_grad10;
	int16_t shift_grad10;
};

//основные функции
void hal_pt100_pt300_init(struct pt100_pt300_data * t_sensor, uint8_t pt100_pt300_mode, uint8_t pt300_control_pin, volatile uint8_t * pt300_control_port, uint8_t adc_pin, uint16_t v_ref);
void hal_pt100_pt300_update(struct pt100_pt300_data * t_sensor);

//функция для чтения температуры с учетом сдвига характеристики
int16_t hal_pt100_pt300_read_temperature(struct pt100_pt300_data * t_sensor);

//функция для смещения характеристики
void hal_pt100_pt300_set_temperature_shift(struct pt100_pt300_data * t_sensor, int16_t temperature_shift);

#endif /* HAL_PT100_PT300_H_ */