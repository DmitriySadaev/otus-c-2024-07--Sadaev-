<<<<<<< HEAD
/*!
\file
\defgroup fsm_current_sensor
\brief Заголовочный файл fsm_current_sensor.h

*/

#ifndef FSM_CURRENT_SENSOR_H_
#define FSM_CURRENT_SENSOR_H_

#include "hal_current_shunt.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef FSM_CURRENT_SENSOR_ARRAY_SIZE
#define FSM_CURRENT_SENSOR_ARRAY_SIZE 10
#endif /* FSM_CURRENT_SENSOR_ARRAY_SIZE */

#ifndef FSM_CURRENT_SENSOR_MEASUREMENT_PERIOD_MS
#define FSM_CURRENT_SENSOR_MEASUREMENT_PERIOD_MS 10U
#endif /* FSM_CURRENT_SENSOR_MEASUREMENT_PERIOD_MS */

void fsm_current_sensor_init(int16_t * current, struct current_shunt_data * current_shunt, uint8_t adc_pin, uint16_t v_ref, uint16_t r_shunt_100ohm, int16_t shift_ma);
void fsm_current_sensor_process(int16_t * current, struct current_shunt_data * current_shunt);

=======
/*!
\file
\defgroup fsm_current_sensor
\brief Заголовочный файл fsm_current_sensor.h

*/

#ifndef FSM_CURRENT_SENSOR_H_
#define FSM_CURRENT_SENSOR_H_

#include "hal_current_shunt.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef FSM_CURRENT_SENSOR_ARRAY_SIZE
#define FSM_CURRENT_SENSOR_ARRAY_SIZE 10
#endif /* FSM_CURRENT_SENSOR_ARRAY_SIZE */

#ifndef FSM_CURRENT_SENSOR_MEASUREMENT_PERIOD_MS
#define FSM_CURRENT_SENSOR_MEASUREMENT_PERIOD_MS 10U
#endif /* FSM_CURRENT_SENSOR_MEASUREMENT_PERIOD_MS */

void fsm_current_sensor_init(int16_t * current, struct current_shunt_data * current_shunt, uint8_t adc_pin, uint16_t v_ref, uint16_t r_shunt_100ohm, int16_t shift_ma);
void fsm_current_sensor_process(int16_t * current, struct current_shunt_data * current_shunt);

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* FSM_CURRENT_SENSOR_H_ */