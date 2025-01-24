/*!
\file
\defgroup fsm_inner_temp_sensor
\brief Заголовочный файл fsm_inner_temp_sensor.h

*/

#ifndef FSM_INNER_SENSOR_H_
#define FSM_INNER_SENSOR_H_

#include "hal_kty82.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef FSM_INNER_SENSOR_ARRAY_SIZE 
#define FSM_INNER_SENSOR_ARRAY_SIZE 8
#endif /* FSM_INNER_SENSOR_ARRAY_SIZE */

#ifndef FSM_INNER_SENSOR_ERRORS_COUNT
#define FSM_INNER_SENSOR_ERRORS_COUNT 3
#endif /* FSM_INNER_SENSOR_ERRORS_COUNT */

#ifndef FSM_INNER_SENSOR_MEASUREMENT_PERIOD_MS
#define FSM_INNER_SENSOR_MEASUREMENT_PERIOD_MS 100U
#endif /* FSM_INNER_SENSOR_MEASUREMENT_PERIOD_MS */

void fsm_inner_temp_sensor_init(int16_t * inner_temperature_grad10, struct kty82_data * t_sensor, uint8_t sensor_type, uint8_t sensor_adc_pin);
void fsm_inner_temp_sensor_process(int16_t * inner_temperature_grad10, struct kty82_data * t_sensor);

#endif /* FSM_INNER_SENSOR_H_ */