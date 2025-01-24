<<<<<<< HEAD
/*!
\file
\defgroup fsm_voltage_sensor
\brief Заголовочный файл fsm_voltage_sensor.h

*/

#ifndef FSM_VOLTAGE_SENSOR_H_
#define FSM_VOLTAGE_SENSOR_H_

#include "hal_voltage_divider.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef FSM_VOLTAGE_SENSOR_ARRAY_SIZE
#define FSM_VOLTAGE_SENSOR_ARRAY_SIZE 3
#endif /* FSM_VOLTAGE_SENSOR_ARRAY_SIZE */

#ifndef FSM_VOLTAGE_SENSOR_MEASUREMENT_PERIOD_MS
#define FSM_VOLTAGE_SENSOR_MEASUREMENT_PERIOD_MS 300U
#endif /* FSM_VOLTAGE_SENSOR_MEASUREMENT_PERIOD_MS */

void fsm_voltage_sensor_init(uint16_t * voltage, struct voltage_divider_data * v_sensor, uint8_t sensor_adc_pin, uint16_t v_ref, int16_t shift);
void fsm_voltage_sensor_process(uint16_t * voltage, struct voltage_divider_data * v_sensor);

=======
/*!
\file
\defgroup fsm_voltage_sensor
\brief Заголовочный файл fsm_voltage_sensor.h

*/

#ifndef FSM_VOLTAGE_SENSOR_H_
#define FSM_VOLTAGE_SENSOR_H_

#include "hal_voltage_divider.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef FSM_VOLTAGE_SENSOR_ARRAY_SIZE
#define FSM_VOLTAGE_SENSOR_ARRAY_SIZE 3
#endif /* FSM_VOLTAGE_SENSOR_ARRAY_SIZE */

#ifndef FSM_VOLTAGE_SENSOR_MEASUREMENT_PERIOD_MS
#define FSM_VOLTAGE_SENSOR_MEASUREMENT_PERIOD_MS 300U
#endif /* FSM_VOLTAGE_SENSOR_MEASUREMENT_PERIOD_MS */

void fsm_voltage_sensor_init(uint16_t * voltage, struct voltage_divider_data * v_sensor, uint8_t sensor_adc_pin, uint16_t v_ref, int16_t shift);
void fsm_voltage_sensor_process(uint16_t * voltage, struct voltage_divider_data * v_sensor);

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* FSM_VOLTAGE_SENSOR_H_ */