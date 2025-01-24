/*!
\file
\defgroup avr_driver_timers
\brief Заголовочный файл avr_driver_timers.h

*/


#ifndef AVR_DRIVER_TIMER_H_
#define AVR_DRIVER_TIMER_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

//Настройки ?Waveform Generation Mode
/* TIMER_WAVEFORM_GENERATION_MODE */

	#ifndef NORMAL
	#define NORMAL 0U
	#endif /* NORMAL */

	#ifndef PWM
	#define PWM 1U
	#endif /* PWM */

	#ifndef CTC
	#define CTC 2U
	#endif /* CTC */

	#ifndef FAST_PWM
	#define FAST_PWM 3U
	#endif /* FAST_PWM */

//Настройки Compare Output Mode
/* TIMER_COMPARE_OUTPUT_MODE */

	#ifndef NORMAL_PORT_OPERATION
	#define NORMAL_PORT_OPERATION 1U
	#endif /* NORMAL_PORT_OPERATION */
	
	#ifndef TOGGLE_OC0_ON_COMPARE_MATCH				// не может быть применен для Fast PWM Mode и Phase correct PWM Mode
	#define TOGGLE_OC0_ON_COMPARE_MATCH 2U
	#endif /* TOGGLE_OC0_ON_COMPARE_MATCH */	

	#ifndef CLEAR_OC0_ON_COMPARE_MATCH
	#define CLEAR_OC0_ON_COMPARE_MATCH 3U
	#endif /* CLEAR_OC0_ON_COMPARE_MATCH */

	#ifndef SET_OC0_ON_COMPARE_MATCH
	#define SET_OC0_ON_COMPARE_MATCH 4U
	#endif /* CLEAR_OC0_ON_COMPARE_MATCH */

void timer_init(uint8_t timer_n, uint16_t timer_prescaler, uint8_t timer_waveform_generation_mode, uint8_t timer_compare_output_mode, uint8_t timer_compare_match_interrupt_enable, uint8_t timer_overflow_interrupt_enable, uint8_t compare_interrupt_value);
uint8_t timer_check_compare_match(uint8_t timer_n);
uint8_t timer_check_overflow(uint8_t timer_n);

#endif /* AVR_DRIVER_TIMER_H_ */

