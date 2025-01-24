<<<<<<< HEAD
/*!
\file
\defgroup fsm_ui_bu_shd_r_m
\brief Заголовочный файл fsm_ui_bu_shd_r_m.h

*/

#ifndef FSM_UI_BU_SHD_R_M_H_
#define FSM_UI_BU_SHD_R_M_H_

#include <stdint.h>
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "hal_lcd.h"
#include "fsm_clock.h"
#include "BU-ShD-R-M_struct.h"
#include "fsm_archive.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef SHORT
#define SHORT 0x8000
#endif /* SHORT */

#ifndef BREAK
#define BREAK 0x8FFF
#endif /* BREAK */

#ifndef UI_NO_MESSAGES
#define UI_NO_MESSAGES 255
#endif /* UI_NO_MESSAGES */

#ifndef UI_INITIAL_SCREEN_TIME_MS 
#define UI_INITIAL_SCREEN_TIME_MS 1000U
#endif /* UI_INITIAL_SCREEN_TIME_MS */

#ifndef UI_UPDATE_PERIOD_MS 
#define UI_UPDATE_PERIOD_MS 300U
#endif /* UI_UPDATE_PERIOD_MS */

#ifndef UI_ENTER_MENU_COUNT
#define UI_ENTER_MENU_COUNT 2U
#endif /* UI_ENTER_MENU_COUNT */

#ifndef UI_INITIAL_FORMULAR
#define UI_INITIAL_FORMULAR 0U
#endif /* UI_INITIAL_FORMULAR */

#ifndef UI_MAIN_FORMULAR
#define UI_MAIN_FORMULAR 1U
#endif /* UI_MAIN_FORMULAR */

#ifndef UI_MENU_FORMULAR
#define UI_MENU_FORMULAR 2U
#endif /* UI_MENU_FORMULAR */

#ifndef UI_SENSORS_FORMULAR
#define UI_SENSORS_FORMULAR 3U
#endif /* UI_SENSORS_FORMULAR */

#ifndef UI_BKO_FORMULAR
#define UI_BKO_FORMULAR 4U
#endif /* UI_BKO_FORMULAR */

#ifndef UI_DU_FORMULAR
#define UI_DU_FORMULAR 5U
#endif /* UI_BKO_FORMULAR */

#ifndef UI_TIME_FORMULAR
#define UI_TIME_FORMULAR 6U
#endif /* UI_TIME_FORMULAR */

#ifndef UI_OTHERS_FORMULAR
#define UI_OTHERS_FORMULAR 7U
#endif /* UI_OTHERS_FORMULAR */

#ifndef UI_ARCHIVE_FORMULAR
#define UI_ARCHIVE_FORMULAR 8U
#endif /* UI_ARCHIVE_FORMULAR */

#ifndef UI_CURSOR_MOVING_MODE
#define UI_CURSOR_MOVING_MODE 0U
#endif /* UI_CURSOR_MOVING_MODE */

#ifndef UI_CURSOR_CHANGING_PARAMETR_MODE
#define UI_CURSOR_CHANGING_PARAMETR_MODE 1U
#endif /* UI_CURSOR_CHANGING_PARAMETR_MODE */

#ifndef UI_SINGLE_KEYS_STEP
#define UI_SINGLE_KEYS_STEP 1U
#endif /* UI_SINGLE_KEYS_STEP */

#ifndef UI_STICK_KEYS_STEP
#define UI_STICK_KEYS_STEP 10U
#endif /* UI_STICK_KEYS_STEP */

void fsm_ui_init(void);
void fsm_ui_process(struct bu_shd_r_m_data * bu_shd_r_m, struct ds1302_data * time, struct archive_record * bu_shd_r_m_archive);


=======
/*!
\file
\defgroup fsm_ui_bu_shd_r_m
\brief Заголовочный файл fsm_ui_bu_shd_r_m.h

*/

#ifndef FSM_UI_BU_SHD_R_M_H_
#define FSM_UI_BU_SHD_R_M_H_

#include <stdint.h>
#include "fsm_messages.h"
#include "fsm_virtual_timers.h"
#include "hal_lcd.h"
#include "fsm_clock.h"
#include "BU-ShD-R-M_struct.h"
#include "fsm_archive.h"

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef SHORT
#define SHORT 0x8000
#endif /* SHORT */

#ifndef BREAK
#define BREAK 0x8FFF
#endif /* BREAK */

#ifndef UI_NO_MESSAGES
#define UI_NO_MESSAGES 255
#endif /* UI_NO_MESSAGES */

#ifndef UI_INITIAL_SCREEN_TIME_MS 
#define UI_INITIAL_SCREEN_TIME_MS 1000U
#endif /* UI_INITIAL_SCREEN_TIME_MS */

#ifndef UI_UPDATE_PERIOD_MS 
#define UI_UPDATE_PERIOD_MS 300U
#endif /* UI_UPDATE_PERIOD_MS */

#ifndef UI_ENTER_MENU_COUNT
#define UI_ENTER_MENU_COUNT 2U
#endif /* UI_ENTER_MENU_COUNT */

#ifndef UI_INITIAL_FORMULAR
#define UI_INITIAL_FORMULAR 0U
#endif /* UI_INITIAL_FORMULAR */

#ifndef UI_MAIN_FORMULAR
#define UI_MAIN_FORMULAR 1U
#endif /* UI_MAIN_FORMULAR */

#ifndef UI_MENU_FORMULAR
#define UI_MENU_FORMULAR 2U
#endif /* UI_MENU_FORMULAR */

#ifndef UI_SENSORS_FORMULAR
#define UI_SENSORS_FORMULAR 3U
#endif /* UI_SENSORS_FORMULAR */

#ifndef UI_BKO_FORMULAR
#define UI_BKO_FORMULAR 4U
#endif /* UI_BKO_FORMULAR */

#ifndef UI_DU_FORMULAR
#define UI_DU_FORMULAR 5U
#endif /* UI_BKO_FORMULAR */

#ifndef UI_TIME_FORMULAR
#define UI_TIME_FORMULAR 6U
#endif /* UI_TIME_FORMULAR */

#ifndef UI_OTHERS_FORMULAR
#define UI_OTHERS_FORMULAR 7U
#endif /* UI_OTHERS_FORMULAR */

#ifndef UI_ARCHIVE_FORMULAR
#define UI_ARCHIVE_FORMULAR 8U
#endif /* UI_ARCHIVE_FORMULAR */

#ifndef UI_CURSOR_MOVING_MODE
#define UI_CURSOR_MOVING_MODE 0U
#endif /* UI_CURSOR_MOVING_MODE */

#ifndef UI_CURSOR_CHANGING_PARAMETR_MODE
#define UI_CURSOR_CHANGING_PARAMETR_MODE 1U
#endif /* UI_CURSOR_CHANGING_PARAMETR_MODE */

#ifndef UI_SINGLE_KEYS_STEP
#define UI_SINGLE_KEYS_STEP 1U
#endif /* UI_SINGLE_KEYS_STEP */

#ifndef UI_STICK_KEYS_STEP
#define UI_STICK_KEYS_STEP 10U
#endif /* UI_STICK_KEYS_STEP */

void fsm_ui_init(void);
void fsm_ui_process(struct bu_shd_r_m_data * bu_shd_r_m, struct ds1302_data * time, struct archive_record * bu_shd_r_m_archive);


>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* FSM_UI_BU_SHD_R_M_H_ */