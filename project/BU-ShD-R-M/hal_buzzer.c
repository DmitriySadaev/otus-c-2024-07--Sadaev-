<<<<<<< HEAD
/*! 
  \file
  \defgroup		hal_buzzer
  \brief		Файл исходного кода программы hal_buzzer.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций зуммера
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  EFM-310B, HCM1206X
*/

#include "hal_buzzer.h"

void hal_buzzer_init_struct(struct buzzer_data * buzzer, uint32_t duty_cycle, uint8_t period, uint8_t buzzer_pin, volatile uint8_t * buzzer_port)
{
	buzzer->status = BUZZER_OFF;
	buzzer->duty_cycle = duty_cycle;
	buzzer->period = period;
	buzzer->buzzer_pin = buzzer_pin;
	buzzer->buzzer_port = buzzer_port;
}

void hal_buzzer_init_ddr(struct buzzer_data * buzzer)
{
	* (buzzer->buzzer_port  -1)	|= (1 << buzzer->buzzer_pin); //из адреса регистра PORT получаем адрес регистра DDR
}

void hal_buzzer_pin_on(struct buzzer_data * buzzer)
{
	* buzzer->buzzer_port |= (1 << buzzer->buzzer_pin);
}

void hal_buzzer_pin_off(struct buzzer_data * buzzer)
{
	* buzzer->buzzer_port &= ~(1 << buzzer->buzzer_pin);
}

void hal_buzzer_init(struct buzzer_data * buzzer, uint32_t duty_cycle, uint8_t period, uint8_t buzzer_pin, volatile uint8_t * buzzer_port)
{
	hal_buzzer_init_struct(buzzer, duty_cycle, period, buzzer_pin, buzzer_port);
	hal_buzzer_init_ddr(buzzer);
	hal_buzzer_pin_off(buzzer);
=======
/*! 
  \file
  \defgroup		hal_buzzer
  \brief		Файл исходного кода программы hal_buzzer.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций зуммера
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  EFM-310B, HCM1206X
*/

#include "hal_buzzer.h"

void hal_buzzer_init_struct(struct buzzer_data * buzzer, uint32_t duty_cycle, uint8_t period, uint8_t buzzer_pin, volatile uint8_t * buzzer_port)
{
	buzzer->status = BUZZER_OFF;
	buzzer->duty_cycle = duty_cycle;
	buzzer->period = period;
	buzzer->buzzer_pin = buzzer_pin;
	buzzer->buzzer_port = buzzer_port;
}

void hal_buzzer_init_ddr(struct buzzer_data * buzzer)
{
	* (buzzer->buzzer_port  -1)	|= (1 << buzzer->buzzer_pin); //из адреса регистра PORT получаем адрес регистра DDR
}

void hal_buzzer_pin_on(struct buzzer_data * buzzer)
{
	* buzzer->buzzer_port |= (1 << buzzer->buzzer_pin);
}

void hal_buzzer_pin_off(struct buzzer_data * buzzer)
{
	* buzzer->buzzer_port &= ~(1 << buzzer->buzzer_pin);
}

void hal_buzzer_init(struct buzzer_data * buzzer, uint32_t duty_cycle, uint8_t period, uint8_t buzzer_pin, volatile uint8_t * buzzer_port)
{
	hal_buzzer_init_struct(buzzer, duty_cycle, period, buzzer_pin, buzzer_port);
	hal_buzzer_init_ddr(buzzer);
	hal_buzzer_pin_off(buzzer);
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
}