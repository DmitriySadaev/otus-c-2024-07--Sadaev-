/*!
\file
\defgroup fsm_messages
\brief Заголовочный файл fsm_messages.h

*/

#ifndef FSM_MESSAGES_H_
#define FSM_MESSAGES_H_

#include <stdint.h>

#ifndef MESSAGE_NOT_ACTIVE
#define MESSAGE_NOT_ACTIVE 0U
#endif /* MESSAGE_NOT_ACTIVE */

#ifndef MESSAGE_SET
#define MESSAGE_SET 1U
#endif /* MESSAGE_SET */

#ifndef MESSAGE_ACTIVE
#define MESSAGE_ACTIVE 2U
#endif /* MESSAGE_ACTIVE */

#ifndef MESSAGE_RECIEVED
#define MESSAGE_RECIEVED 1U
#endif /* MESSAGE_RECIEVED */

#ifndef MESSAGE_NOT_RECIEVED
#define MESSAGE_NOT_RECIEVED 0U
#endif /* MESSAGE_RECIEVED */

#ifndef MAX_MESSAGES
#define MAX_MESSAGES 64
#endif /* MAX_MESSAGES */

#ifndef MAX_BROADCAST_MESSAGES
#define MAX_BROADCAST_MESSAGES 64
#endif /* MAX_BROADCAST_MESSAGES */

/*Список сообщений*/
#define MSG_KEY_PRESSED_PHASE_C		0U
#define MSG_KEY_PRESSED_PHASE_B		1U
#define MSG_KEY_PRESSED_PHASE_A		2U
#define MSG_KEY_PRESSED_RPM			3U
#define MSG_KEY_PRESSED_RIGHT		4U
#define MSG_KEY_PRESSED_LEFT		5U
#define MSG_KEY_PRESSED_ESC			6U
#define MSG_KEY_PRESSED_ENTER		7U
#define MSG_KEY_PRESSED_REG2_STOP	8U
#define MSG_KEY_PRESSED_REG2_START	9U
#define MSG_KEY_PRESSED_REG1_STOP	10U
#define MSG_KEY_PRESSED_REG1_START	11U
#define MSG_KEY_PRESSED_BKO2_STOP	12U
#define MSG_KEY_PRESSED_BKO2_START	13U
#define MSG_KEY_PRESSED_BKO1_STOP	14U
#define MSG_KEY_PRESSED_BKO1_START	15U
#define MSG_KEY_PRESSED_OL			16U

#define MSG_BUZZER_TURN_ON			17U
#define MSG_BUZZER_TURN_OFF			18U

#define MSG_INNER_T_SENSOR_SHORT	19U
#define MSG_INNER_T_SENSOR_BREAK	20U

#define MSG_FAN_IS_TURNED_ON		21U
#define MSG_FAN_IS_TURNED_OFF		22U

#define MSG_NEW_ERROR				23U
#define MSG_UPDATE_ERRORS			24U

#define MSG_REGEN1_STARTED			25U
#define MSG_REGEN1_STOPPED			26U
#define MSG_REGEN1_FINISHED			27U

#define MSG_REGEN2_STARTED			28U
#define MSG_REGEN2_STOPPED			29U
#define MSG_REGEN2_FINISHED			30U

#define MSG_WRONG_PHASE_SEQUENCE	32U
#define MSG_T1_OVERHEAT				33U
#define MSG_T2_OVERHEAT				34U
#define MSG_T1_SHORT				35U
#define MSG_T1_BREAK				36U
#define MSG_T2_SHORT				37U
#define MSG_T2_BREAK				38U
#define MSG_HEATER_SHORT			39U
#define MSG_HEATER_BREAK			40U
#define MSG_STEPPER_BREAK			41U
#define MSG_BKO_STARTED				42U
#define MSG_BKO_STOPPED				43U
#define MSG_IT3_NO_CONNECTION		44U
#define MSG_BKO_NO_DATA				45U
#define MSG_BKO_NOT_CONNECTED		46U
#define MSG_BKO_CONNECTED			47U
#define MSG_BKO_SENSOR_SHORT		48U
#define MSG_BKO_SENSOR_BREAK		49U
#define MSG_ADSORBER_LIMIT			50U
#define MSG_MODE_CHANGE				51U
#define MSG_BKO_OVERLOAD			52U
#define MSG_EEPROM_UPDATED			53U
#define MSG_UPDATE_AFSORBER_EEPROM	53U

void fsm_messages_init(void);
void fsm_messages_send_message(uint8_t message);
void fsm_messages_send_broadcast_message(uint8_t message);
void fsm_messages_process(void);
uint8_t fsm_messages_get_message(uint8_t message);
uint8_t fsm_messages_get_broadcast_message(uint8_t message);

#endif /* FSM_MESSAGES_H_ */