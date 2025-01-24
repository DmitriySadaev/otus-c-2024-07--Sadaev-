/*!
\file
\defgroup hal_buzzer
\brief Заголовочный файл hal_buzzer.h

*/

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef BUZZER_ON
#define BUZZER_ON 1U
#endif /* BUZZER_ON */

#ifndef BUZZER_OFF
#define BUZZER_OFF 0U
#endif /* BUZZER_OFF */

struct buzzer_data
{
	uint8_t status; //on/off
	uint32_t duty_cycle;//1..100
	uint8_t period;
	uint8_t buzzer_pin;
	volatile uint8_t * buzzer_port;
};

void hal_buzzer_pin_on(struct buzzer_data * buzzer);
void hal_buzzer_pin_off(struct buzzer_data * buzzer);
void hal_buzzer_init(struct buzzer_data * buzzer, uint32_t duty_cycle, uint8_t period, uint8_t buzzer_pin, volatile uint8_t * buzzer_port);

#endif /* HAL_BUZZER_H_ */