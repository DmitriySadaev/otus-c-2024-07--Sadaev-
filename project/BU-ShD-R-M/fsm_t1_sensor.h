/*!
\file
\defgroup fsm_t1_sensor
\brief Заголовочный файл fsm_t1_sensor.h

*/

#ifndef FSM_T1_SENSOR_H_
#define FSM_T1_SENSOR_H_

#include "hal_pt100_pt300.h"
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "BU-ShD-R-M_struct.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef FSM_T1_SENSOR_ARRAY_SIZE
#define FSM_T1_SENSOR_ARRAY_SIZE 12
#endif /* FSM_T1_SENSOR_ARRAY_SIZE */

#ifndef FSM_T1_SENSOR_ERRORS_COUNT
#define FSM_T1_SENSOR_ERRORS_COUNT 6
#endif /* FSM_T1_SENSOR_ERRORS_COUNT */

#ifndef FSM_T1_SENSOR_MEASUREMENT_PERIOD_MS
#define FSM_T1_SENSOR_MEASUREMENT_PERIOD_MS 100U
#endif /* FSM_T1_SENSOR_MEASUREMENT_PERIOD_MS */

void fsm_t1_temp_sensor_init(struct bu_shd_r_m_data * bu_shd_r_m, struct pt100_pt300_data * t_sensor, uint8_t pt100_pt300_mode, uint8_t pt300_control_pin, volatile uint8_t * pt300_control_port, uint8_t adc_pin, uint16_t v_ref);
void fsm_t1_temp_sensor_process(struct bu_shd_r_m_data * bu_shd_r_m, struct pt100_pt300_data * t_sensor);

#endif /* FSM_T1_SENSOR_H_ */