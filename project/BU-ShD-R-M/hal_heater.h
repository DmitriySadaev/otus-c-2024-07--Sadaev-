<<<<<<< HEAD
/*!
\file
\defgroup hal_heater
\brief Заголовочный файл hal_heater.h

*/

#ifndef HAL_HEATER_H_
#define HAL_HEATER_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef HEATER_ON
#define HEATER_ON 1U
#endif /* HEATER_ON */

#ifndef HEATER_OFF
#define HEATER_OFF 0U
#endif /* HEATER_OFF */

struct heater_data
{
	uint8_t status; //on/off
	uint8_t power_watt;//30..100 watt
	uint8_t load_ohm;//15..200 ohm
	uint8_t voltage;
	uint8_t heater_pin;
	volatile uint8_t * heater_port;
};

void hal_heater_init(struct heater_data * heater, uint8_t voltage, uint8_t power_watt, uint8_t load_ohm, uint8_t heater_pin, volatile uint8_t * heater_port);
void hal_heater_pin_on(struct heater_data * heater);
void hal_heater_pin_off(struct heater_data * heater);
uint8_t hal_heater_get_period_percent(struct heater_data * heater);

=======
/*!
\file
\defgroup hal_heater
\brief Заголовочный файл hal_heater.h

*/

#ifndef HAL_HEATER_H_
#define HAL_HEATER_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef HEATER_ON
#define HEATER_ON 1U
#endif /* HEATER_ON */

#ifndef HEATER_OFF
#define HEATER_OFF 0U
#endif /* HEATER_OFF */

struct heater_data
{
	uint8_t status; //on/off
	uint8_t power_watt;//30..100 watt
	uint8_t load_ohm;//15..200 ohm
	uint8_t voltage;
	uint8_t heater_pin;
	volatile uint8_t * heater_port;
};

void hal_heater_init(struct heater_data * heater, uint8_t voltage, uint8_t power_watt, uint8_t load_ohm, uint8_t heater_pin, volatile uint8_t * heater_port);
void hal_heater_pin_on(struct heater_data * heater);
void hal_heater_pin_off(struct heater_data * heater);
uint8_t hal_heater_get_period_percent(struct heater_data * heater);

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* HAL_HEATER_H_ */