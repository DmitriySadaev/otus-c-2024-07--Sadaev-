<<<<<<< HEAD
/*!
\file
\defgroup hal_status_led
\brief Заголовочный файл hal_status_led.h

*/

#ifndef HAL_STATUS_LED_H_
#define HAL_STATUS_LED_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

struct status_led_data
{
	uint8_t status_led_pin;
	volatile uint8_t * status_led_port;
};

void hal_status_led_init(struct status_led_data * status_led, uint8_t status_led_pin, volatile uint8_t * status_led_port);
void hal_status_led_toggle(struct status_led_data * status_led);

=======
/*!
\file
\defgroup hal_status_led
\brief Заголовочный файл hal_status_led.h

*/

#ifndef HAL_STATUS_LED_H_
#define HAL_STATUS_LED_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

struct status_led_data
{
	uint8_t status_led_pin;
	volatile uint8_t * status_led_port;
};

void hal_status_led_init(struct status_led_data * status_led, uint8_t status_led_pin, volatile uint8_t * status_led_port);
void hal_status_led_toggle(struct status_led_data * status_led);

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* HAL_STATUS_LED_H_ */