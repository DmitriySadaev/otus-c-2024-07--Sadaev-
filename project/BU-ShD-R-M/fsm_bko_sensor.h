/*!
\file
\defgroup fsm_bko_sensor
\brief Заголовочный файл fsm_bko_sensor.h

*/

#ifndef FSM_BKO_SENSOR_H_
#define FSM_BKO_SENSOR_H_

#include "hal_t_100p.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef FSM_BKO_SENSOR_ARRAY_SIZE
#define FSM_BKO_SENSOR_ARRAY_SIZE 25
#endif /* FSM_BKO_SENSOR_ARRAY_SIZE */

#ifndef FSM_BKO_SENSOR_ERRORS_COUNT
#define FSM_BKO_SENSOR_ERRORS_COUNT 25
#endif /* FSM_BKO_SENSOR_ERRORS_COUNT */

#ifndef FSM_BKO_SENSOR_MEASUREMENT_PERIOD_MS
#define FSM_BKO_SENSOR_MEASUREMENT_PERIOD_MS 100U
#endif /* FSM_BKO_SENSOR_MEASUREMENT_PERIOD_MS */

#ifndef FSM_BKO_IT3_TEMPERATURE00_BKO_SENSOR_SHORT_IGNORE
#define FSM_BKO_IT3_TEMPERATURE00_BKO_SENSOR_SHORT_IGNORE 5000
#endif /* FSM_BKO_IT3_TEMPERATURE00_BKO_SENSOR_SHORT_IGNORE */

#ifndef CELSIUM_TO_KELVIN_CONVERSION_SHIFT_GRAD0
#define CELSIUM_TO_KELVIN_CONVERSION_SHIFT_GRAD0 2732
#endif /* CELSIUM_TO_KELVIN_CONVERSION_SHIFT_GRAD0 */

void fsm_bko_temp_sensor_init(struct bu_shd_r_m_data * bu_shd_r_m, struct t_100p_data * t_sensor,  uint8_t adc_pin, uint16_t v_ref, uint8_t control_pin, volatile  uint8_t * control_port, int16_t temperature_shift);
void fsm_bko_temp_sensor_process(struct bu_shd_r_m_data * bu_shd_r_m, struct t_100p_data * t_sensor);

#endif /* FSM_BKO_SENSOR_H_ */