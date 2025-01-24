/*!
\file
\defgroup fsm_keyboard
\brief Заголовочный файл fsm_keyboard.h

*/

#ifndef FSM_KEYBOARD_H_
#define FSM_KEYBOARD_H_

#include <stdint.h>
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "hal_sn74als165d.h"
#include "BU-ShD-R-M_struct.h"

#ifndef FSM_KEYBOARD_STATE_KEY_NOT_PRESSED
#define FSM_KEYBOARD_STATE_KEY_NOT_PRESSED 0U
#endif /* FSM_KEYBOARD_STATE_KEY_NOT_PRESSED */

#ifndef FSM_KEYBOARD_STATE_KEY_PRESSED
#define FSM_KEYBOARD_STATE_KEY_PRESSED 1U
#endif /* FSM_KEYBOARD_STATE_KEY_PRESSED */

#ifndef FSM_KEYBOARD_STATE_DEBOUNCE_PASSED
#define FSM_KEYBOARD_STATE_DEBOUNCE_PASSED 2U
#endif /* FSM_KEYBOARD_STATE_DEBOUNCE_PASSED */

#ifndef FSM_KEYBOARD_STATE_FIRST_DELAY_PASSED
#define FSM_KEYBOARD_STATE_FIRST_DELAY_PASSED 3U
#endif /* FSM_KEYBOARD_STATE_FIRST_DELAY_PASSED */

#ifndef FSM_KEYBOARD_STATE_AUTOREPEAT_PASSED
#define FSM_KEYBOARD_STATE_AUTOREPEAT_PASSED 4U
#endif /* FSM_KEYBOARD_STATE_AUTOREPEAT_PASSED */

#ifndef DEBOUNCE_TIME_MS 
#define DEBOUNCE_TIME_MS 30U
#endif /* DEBOUNCE_TIME_MS */

#ifndef FIRST_DELAY_TIME_MS
#define FIRST_DELAY_TIME_MS 200U
#endif /* FIRST_DELAY_TIME_MS */

#ifndef AUTO_REPEAT_TIME_MS
#define AUTO_REPEAT_TIME_MS 300UL
#endif /* AUTO_REPEAT_TIME_MS */

#ifndef AUTO_REPEAT_ITERATOR_COUNT
#define AUTO_REPEAT_ITERATOR_COUNT 10U
#endif /* AUTO_REPEAT_ITERATOR_COUNT */

void fsm_keyboard_init(void);
void fsm_keyboard_process(uint8_t * button_array, struct bu_shd_r_m_data * bu_shd_r_m);

#endif /* FSM_KEYBOARD_H_ */