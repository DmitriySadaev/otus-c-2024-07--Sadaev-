#ifndef PROTOCOL_BU_SH_D_R_M_DUBNA_H_
#define PROTOCOL_BU_SH_D_R_M_DUBNA_H_

//----------------------------------------------------------------------------------
//--------Поддерживаемые команды Дубна ---------------------------------------------

#ifndef DUBNA_COMMAND_BKO1_START
#define DUBNA_COMMAND_BKO1_START						7
#endif /* DUBNA_COMMAND_BKO1_START */

#ifndef DUBNA_COMMAND_BKO2_START
#define DUBNA_COMMAND_BKO2_START						8
#endif /* DUBNA_COMMAND_BKO2_START */

#ifndef DUBNA_COMMAND_BKO1_STOP
#define DUBNA_COMMAND_BKO1_STOP							9
#endif /* DUBNA_COMMAND_BKO1_STOP */

#ifndef DUBNA_COMMAND_BKO2_STOP
#define DUBNA_COMMAND_BKO2_STOP							10
#endif /* DUBNA_COMMAND_BKO2_STOP */

#ifndef DUBNA_COMMAND_REG1_START
#define DUBNA_COMMAND_REG1_START						11
#endif /* DUBNA_COMMAND_REG1_START */

#ifndef DUBNA_COMMAND_REG2_START
#define DUBNA_COMMAND_REG2_START						12
#endif /* DUBNA_COMMAND_REG2_START */

#ifndef DUBNA_COMMAND_REG1_STOP
#define DUBNA_COMMAND_REG1_STOP							13
#endif /* DUBNA_COMMAND_REG1_STOP */

#ifndef DUBNA_COMMAND_REG2_STOP
#define DUBNA_COMMAND_REG2_STOP							14
#endif /* DUBNA_COMMAND_REG2_STOP */

#ifndef DUBNA_COMMAND_STATUS
#define DUBNA_COMMAND_STATUS							15
#endif /* DUBNA_COMMAND_STATUS */

#ifndef DUBNA_COMMAND_TIME
#define DUBNA_COMMAND_TIME								16
#endif /* DUBNA_COMMAND_TIME */

#ifndef DUBNA_COMMAND_BKO_TEMP
#define DUBNA_COMMAND_BKO_TEMP							17
#endif /* DUBNA_COMMAND_BKO_TEMP */

#ifndef DUBNA_COMMAND_KU_TEMP
#define DUBNA_COMMAND_KU_TEMP							18
#endif /* DUBNA_COMMAND_KU_TEMP */

//----------------------------------------------------------------------------------
//--------Поддерживаемые сообщения об ошибке Дубна ---------------------------------

#ifndef DUBNA_ERROR_PARITY
#define DUBNA_ERROR_PARITY								1
#endif /* DUBNA_ERROR_PARITY */

#ifndef DUBNA_ERROR_INVALID_COMMAND
#define DUBNA_ERROR_INVALID_COMMAND						2
#endif /* DUBNA_ERROR_INVALID_COMMAND */

#ifndef DUBNA_ERROR_UNRECOGNIZABLE_COMMAND
#define DUBNA_ERROR_UNRECOGNIZABLE_COMMAND				3
#endif /* DUBNA_ERROR_UNRECOGNIZABLE_COMMAND */

#ifndef DUBNA_ERROR_MANUAL_MODE
#define DUBNA_ERROR_MANUAL_MODE							4
#endif /* DUBNA_ERROR_MANUAL_MODE */

#ifndef DUBNA_ERROR_HARDWARE_FAULT
#define DUBNA_ERROR_HARDWARE_FAULT						5
#endif /* DUBNA_ERROR_HARDWARE_FAULT */

#ifndef DUBNA_ERROR_CHECK_SUM_FAILURE
#define DUBNA_ERROR_CHECK_SUM_FAILURE					6
#endif /* DUBNA_ERROR_CHECK_SUM_FAILURE */

#endif /* PROTOCOL_BU_SH_D_R_M_DUBNA_H_ */