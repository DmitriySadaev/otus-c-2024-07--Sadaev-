#ifndef PROTOCOL_BU_SH_D_R_M_MODBUS_H_
#define PROTOCOL_BU_SH_D_R_M_MODBUS_H_

//----------------------------------------------------------------------------------
//--------Поддерживаемые функции MODBUS---------------------------------------------

#ifndef MODBUS_COMMAND_READ_INPUT_REGISTERS		
#define MODBUS_COMMAND_READ_INPUT_REGISTERS								(0x04)
#endif /* MODBUS_COMMAND_READ_INPUT_REGISTERS */

#ifndef MODBUS_COMMAND_FORCE_SINGLE_COIL
#define MODBUS_COMMAND_FORCE_SINGLE_COIL								(0x05)
#endif /* MODBUS_COMMAND_FORCE_SINGLE_COIL */

//----------------------------------------------------------------------------------
//--------Поддерживаемые ошибки MODBUS----------------------------------------------
// MODBUS_ANSWER_DO_NOT_NEEDED - не ошибка, а флаг о том, что ответ не требуется
#ifndef MODBUS_ANSWER_DO_NOT_NEEDED
#define MODBUS_ANSWER_DO_NOT_NEEDED										(0x00)
#endif /* MODBUS_ANSWER_DO_NOT_NEEDED */

#ifndef MODBUS_ERROR_ILLEGAL_FUNCTION
#define MODBUS_ERROR_ILLEGAL_FUNCTION									(0x01)
#endif /* MODBUS_ERROR_ILLEGAL_FUNCTION */

#ifndef MODBUS_ERROR_ILLEGAL_DATA_ADDRESS
#define MODBUS_ERROR_ILLEGAL_DATA_ADDRESS								(0x02)
#endif /* MODBUS_ERROR_ILLEGAL_DATA_ADDRESS */

#ifndef MODBUS_ERROR_ILLEGAL_DATA_VALUE
#define MODBUS_ERROR_ILLEGAL_DATA_VALUE									(0x03)
#endif /* MODBUS_ERROR_ILLEGAL_DATA_VALUE */

//----------------------------------------------------------------------------------
//--------Передаваемые параметры по команде 0х04------------------------------------

#ifndef MODBUS_TRANS_PARAMETR_T1_TEMPERATURE
#define MODBUS_TRANS_PARAMETR_T1_TEMPERATURE							(0x0100)
#endif /* MODBUS_TRANS_PARAMETR_T1_TEMPERATURE */

#ifndef MODBUS_TRANS_PARAMETR_T2_TEMPERATURE
#define MODBUS_TRANS_PARAMETR_T2_TEMPERATURE							(0x0101)
#endif /* MODBUS_TRANS_PARAMETR_T2_TEMPERATURE */

#ifndef MODBUS_TRANS_PARAMETR_BKO1_TEMPERATURE
#define MODBUS_TRANS_PARAMETR_BKO1_TEMPERATURE							(0x0102)
#endif /* MODBUS_TRANS_PARAMETR_BKO1_TEMPERATURE */

#ifndef MODBUS_TRANS_PARAMETR_BKO2_TEMPERATURE
#define MODBUS_TRANS_PARAMETR_BKO2_TEMPERATURE							(0x0103)
#endif /* MODBUS_TRANS_PARAMETR_BKO2_TEMPERATURE */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32
#define MODBUS_TRANS_PARAMETR_BU_STATE_32								(0x0104)
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32 */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10
#define MODBUS_TRANS_PARAMETR_BU_STATE_10								(0x0105)
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10 */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE								(0x0106)
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE */

#ifndef MODBUS_TRANS_PARAMETR_OP_TIME_KH
#define MODBUS_TRANS_PARAMETR_OP_TIME_KH								(0x0107)
#endif /* MODBUS_TRANS_PARAMETR_OP_TIME_KH */

#ifndef MODBUS_TRANS_PARAMETR_OP_TIME_H
#define MODBUS_TRANS_PARAMETR_OP_TIME_H									(0x0108)
#endif /* MODBUS_TRANS_PARAMETR_OP_TIME_H */

#ifndef MODBUS_TRANS_PARAMETR_PROD_YEAR_MOUNTH
#define MODBUS_TRANS_PARAMETR_PROD_YEAR_MOUNTH							(0x0109)
#endif /* MODBUS_TRANS_PARAMETR_PROD_YEAR_MOUNTH */

#ifndef MODBUS_TRANS_PARAMETR_SERIAL
#define MODBUS_TRANS_PARAMETR_SERIAL									(0x010A)
#endif /* MODBUS_TRANS_PARAMETR_SERIAL */

#ifndef MODBUS_TRANS_PARAMETR_PO_VERSION
#define MODBUS_TRANS_PARAMETR_PO_VERSION								(0x010B)
#endif /* MODBUS_TRANS_PARAMETR_PO_VERSION */

#ifndef MODBUS_TRANS_PARAMETR_BU_TYPE
#define MODBUS_TRANS_PARAMETR_BU_TYPE									(0x010C)
#endif /* MODBUS_TRANS_PARAMETR_BU_TYPE */

#ifndef MODBUS_TRANS_PARAMETR_STEPPER_SPEED
#define MODBUS_TRANS_PARAMETR_STEPPER_SPEED								(0x010D)
#endif /* MODBUS_TRANS_PARAMETR_STEPPER_SPEED */

//----------------------------------------------------------------------------------
//--------Расшифровка слово состояния MODBUS_TRANS_PARAMETR_BU_STATE_32-------------

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_OVERHEAT
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_OVERHEAT					0U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_OVERHEAT */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_OVERHEAT
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_OVERHEAT					1U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_OVERHEAT */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO3_OVERHEAT
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO3_OVERHEAT					2U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_OVERHEAT */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_T1_OVERHEAT
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_T1_OVERHEAT					3U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_T1_OVERHEAT */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_T2_OVERHEAT
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_T2_OVERHEAT					4U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_T2_OVERHEAT */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_WILL_OFF
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_WILL_OFF					5U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_WILL_OFF */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_WILL_OFF
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_WILL_OFF					6U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_WILL_OFF */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO3_WILL_OFF
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO3_WILL_OFF					7U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO3_WILL_OFF */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_KU_ON
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_KU_ON							8U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_KU_ON */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO3_ON
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO3_ON						9U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO3_ON */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_ON
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_ON						10U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO2_ON */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_ON
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_ON						11U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_ON */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_REG1_ON
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_REG1_ON						12U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_REG1_ON */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_REG2_ON
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_REG2_ON						13U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_REG2_ON */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_32_REG3_ON
#define MODBUS_TRANS_PARAMETR_BU_STATE_32_REG3_ON						14U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_32_REG3_ON */

//----------------------------------------------------------------------------------
//--------Расшифровка слово состояния MODBUS_TRANS_PARAMETR_BU_STATE_10-------------

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_KU_SENSORS_FAILURE
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_KU_SENSORS_FAILURE			1U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_KU_SENSORS_FAILURE */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO_SENSORS_FAILURE
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO_SENSORS_FAILURE			2U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO_SENSORS_FAILURE */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_HEATERS_BREAK
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_HEATERS_BREAK					3U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_HEATERS_BREAK */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_OVERLOAD
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_OVERLOAD						4U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_OVERLOAD */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_HEATER_BREAK
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_HEATER_BREAK				8U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_HEATER_BREAK */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_HEATER_BREAK
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_HEATER_BREAK				8U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_HEATER_BREAK */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO2_HEATER_BREAK
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO2_HEATER_BREAK				9U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO2_HEATER_BREAK */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO3_HEATER_BREAK
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO3_HEATER_BREAK				10U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO3_HEATER_BREAK */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_NOT_CONNECTED
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_NOT_CONNECTED			11U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_NOT_CONNECTED */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO2_NOT_CONNECTED
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO2_NOT_CONNECTED			12U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO2_NOT_CONNECTED */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO3_NOT_CONNECTED
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO3_NOT_CONNECTED			13U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO3_NOT_CONNECTED */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_ALL_BKO_ARE_DISCONNECTED
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_ALL_BKO_ARE_DISCONNECTED		14U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_ALL_BKO_ARE_DISCONNECTED */

#ifndef MODBUS_TRANS_PARAMETR_BU_STATE_10_WRONG_PHASE_SEQUENCE
#define MODBUS_TRANS_PARAMETR_BU_STATE_10_WRONG_PHASE_SEQUENCE			15U
#endif /* MODBUS_TRANS_PARAMETR_BU_STATE_10_WRONG_PHASE_SEQUENCE */

//----------------------------------------------------------------------------------
//--------Расшифровка слово состояния MODBUS_TRANS_PARAMETR_SENSORS_STATE-----------

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_SHORT
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_SHORT					0U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_SHORT */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_BREAK
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_BREAK					1U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_BREAK */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_SHORT
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_SHORT					2U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_SHORT */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_BREAK
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_BREAK					3U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_BREAK */

#ifndef MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_SHORT
#define MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_SHORT					4U
#endif /* MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_SHORT */

#ifndef MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_BREAK
#define MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_BREAK					5U
#endif /* MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_BREAK */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_BKO2_SENSOR_SHORT
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_BKO2_SENSOR_SHORT			6U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_BKO2_SENSOR_SHORT */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_BKO2_SENSOR_BREAK
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_BKO2_SENSOR_BREAK			7U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_BKO2_SENSOR_BREAK */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_IT3_BKO1_NO_CONNECTION
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_IT3_BKO1_NO_CONNECTION		8U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_IT3_BKO1_NO_CONNECTION */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_IT3_BKO2_NO_CONNECTION
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_IT3_BKO2_NO_CONNECTION		9U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_IT3_BKO2_NO_CONNECTION */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_REG1_FINISHED
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_REG1_FINISHED				10U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_REG1_FINISHED */

#ifndef MODBUS_TRANS_PARAMETR_SENSORS_STATE_REG2_FINISHED
#define MODBUS_TRANS_PARAMETR_SENSORS_STATE_REG2_FINISHED				11U
#endif /* MODBUS_TRANS_PARAMETR_SENSORS_STATE_REG2_FINISHED */

//----------------------------------------------------------------------------------
//--------Исполняемые команды по команде 0х05---------------------------------------

#ifndef MODBUS_ORDER_START_BKO1
#define MODBUS_ORDER_START_BKO1											0U
#endif /* MODBUS_ORDER_START_BKO1 */

#ifndef MODBUS_ORDER_START_BKO2
#define MODBUS_ORDER_START_BKO2											1U
#endif /* MODBUS_ORDER_START_BKO2 */

#ifndef MODBUS_ORDER_START_REG1
#define MODBUS_ORDER_START_REG1											2U
#endif /* MODBUS_ORDER_START_REG1 */

#ifndef MODBUS_ORDER_START_REG2
#define MODBUS_ORDER_START_REG2											3U
#endif /* MODBUS_ORDER_START_REG2 */

#ifndef MODBUS_ORDER_STOP_BKO1
#define MODBUS_ORDER_STOP_BKO1											4U
#endif /* MODBUS_ORDER_STOP_BKO1 */

#ifndef MODBUS_ORDER_STOP_BKO2
#define MODBUS_ORDER_STOP_BKO2											5U
#endif /* MODBUS_ORDER_STOP_BKO2 */

#ifndef MODBUS_ORDER_STOP_REG1
#define MODBUS_ORDER_STOP_REG1											6U
#endif /* MODBUS_ORDER_STOP_REG1 */

#ifndef MODBUS_ORDER_STOP_REG2
#define MODBUS_ORDER_STOP_REG2											7U
#endif /* MODBUS_ORDER_STOP_REG2 */

//----------------------------------------------------------------------------------

#ifndef MODBUS_COMMAND_FORCE_SINGLE_COIL_ADDRESS
#define MODBUS_COMMAND_FORCE_SINGLE_COIL_ADDRESS						(0x0201)
#endif /* MODBUS_COMMAND_FORCE_SINGLE_COIL_ADDRESS */

#endif /* PROTOCOL_BU_SH_D-R-PROTOCOL_BU_SH_D_R_M_MODBUS_H_ */