/*! 
  \file
  \defgroup		avr_driver_adc
  \brief		Файл исходного кода программы avr_driver_adc.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя драйвер АЦП микроконтроллеров ядра AVR.
 
  - Compiler:           GNU AVR toolchain
  - Supported devices:  AtMega64A
*/
#include "avr_driver_adc.h"

/**
 * \fn void avr_driver_adc_enable(void)
 * \brief Функция разрешения работы АЦП
 *
 * ADCSRA - регистр контроля и статуса АЦП 
 * ADEN - бит разрешения работы АЦП 
 * Установка данного бита в состояние 1 разрешает ADC. 
 * Очистка бита запрещает ADC. 
 * Запрещение ADC в процессе преобразования прекращает преобразование.
 */
void avr_driver_adc_enable(void)
{
	ADCSRA |= (1 << ADEN);
}

/**
 * \fn void avr_driver_adc_disable(void)
 * \brief Функция запрещения работы АЦП
 *
 * ADCSRA - регистр контроля и статуса АЦП 
 * ADEN - бит разрешения работы АЦП 
 * Установка данного бита в состояние 1 разрешает ADC. 
 * Очистка бита запрещает ADC. 
 * Запрещение ADC в процессе преобразования прекращает преобразование.
 */
void avr_driver_adc_disable(void)
{		
	ADCSRA &= ~(1 << ADEN);
}

/**
 * \fn void avr_driver_adc_prescaler_set(uint8_t prescaler)
 * \brief Функция выбора предделителя частоты работы АЦП
 *
 * \param prescaler выбранный предделитель частоты работы АЦП
 *
 * ADCSRA - регистр контроля и статуса АЦП 
 * ADPS2..ADPS0 - биты выбора коэффициента предварительного деления
 * Данные биты определяют коэффициент деления частоты XTAL для получения необходимой тактовой частоты АЦП.
 */
void avr_driver_adc_prescaler_set(uint8_t prescaler)
{
	switch(prescaler)
	{
		case 2:
		{
			ADCSRA &= ~(1 << ADPS2);
			ADCSRA &= ~(1 << ADPS1);
			ADCSRA |=  (1 << ADPS0);
			break;
		}
		case 4:
		{
			ADCSRA &= ~(1 << ADPS2);
			ADCSRA |=  (1 << ADPS1);
			ADCSRA &= ~(1 << ADPS0);
			break;
		}
		case 8:
		{
			ADCSRA &= ~(1 << ADPS2);
			ADCSRA |=  (1 << ADPS1);
			ADCSRA |=  (1 << ADPS0);
			break;
		}
		case 16:
		{
			ADCSRA |=  (1 << ADPS2);
			ADCSRA &= ~(1 << ADPS1);
			ADCSRA &= ~(1 << ADPS0);
			break;
		}
		case 32:
		{
			ADCSRA |=  (1 << ADPS2);
			ADCSRA &= ~(1 << ADPS1);
			ADCSRA |=  (1 << ADPS0);
			break;
		}
		case 64:
		{
			ADCSRA |=  (1 << ADPS2);
			ADCSRA |=  (1 << ADPS1);
			ADCSRA &= ~(1 << ADPS0);
			break;
		}
		case 128:
		{
			ADCSRA |=  (1 << ADPS2);
			ADCSRA |=  (1 << ADPS1);
			ADCSRA |=  (1 << ADPS0);
			break;
		}
	}	
}

/**
 * \fn void avr_driver_voltage_reference_set(uint8_t voltage_reference)
 * \brief Функция выбора опорного напряжения АЦП
 *
 * \param voltage_reference выбранный источник опорного напряжения
 *
 * ADMUX - регистр задаёт входной контакт порта A для подключения АЦП, ориентирование результата и выбор опорной частоты. 
 * REFS1:REFS0 - биты выбора опорного напряжения. 
 * Если менять эти биты во время преобразования, то изменения вступят в силу только после текущего преобразования. 
 * В качестве опорного напряжения может быть выбран AVcc (напряжение источника питания), AREF или внутренний 2.56В источник опорного напряжения.
 */
void avr_driver_voltage_reference_set(uint8_t voltage_reference)
{
	switch(voltage_reference)
	{
		case ADC_VOLTAGE_REFERENCE_AREF:
		{
			ADMUX &= ~(1 << REFS1);
			ADMUX &= ~(1 << REFS0);
			break;
		}
		case ADC_VOLTAGE_REFERENCE_AVCC:
		{
			ADMUX &= ~(1 << REFS1);
			ADMUX |=  (1 << REFS0);
			break;
		}
		case ADC_VOLTAGE_REFERENCE_INTERNAL_2_56V:
		{
			ADMUX |=  (1 << REFS1);
			ADMUX |=  (1 << REFS0);
			break;
		}
	}
}

/**
 * \fn void avr_driver_left_adjust_set(void)
 * \brief Функция выбора выравниваня результатов работы АЦП влево
 *
 * ADMUX - регистр задаёт входной контакт порта A для подключения АЦП, ориентирование результата и выбор опорной частоты. 
 * ADLAR - бит определяет как результат преобразования запишется в регистры ADCL и ADCH. 
 * При ADLAR = 0 выравнивание производится вправо. При этом в регистр ADCH записывается два старших бита результата, а в регистр ADCL - восемь младших.
 * При ADLAR = 1 выравнивание производится влево. При этом в регистр ADCH записывается восемь старших битов результата, а в регистр ADCL (а именно в его старшие биты: 7 и 6) - два младших.
 */
void avr_driver_left_adjust_set(void)
{
	ADMUX |= (1 << ADLAR);
/*
  15  |  14  |  13  |  12  |  11  |  10  |  09  |  08  | 
 -------------------------------------------------------
 ADC9 | ADC8 | ADC7 | ADC6 | ADC5 | ADC4 | ADC3 | ADC2 | 
  
  07  |  06  |  05  |  04  |  03  |  02  |  01  |  00  |
  -------------------------------------------------------
 ADC1 | ADC0 |  -   |  -   |   -  |   -  |   -  |   -  |  
*/
}

/**
 * \fn void avr_driver_left_adjust_set(void)
 * \brief Функция выбора выравниваня результатов работы АЦП вправо
 *
 * ADMUX - регистр задаёт входной контакт порта A для подключения АЦП, ориентирование результата и выбор опорной частоты. 
 * ADLAR - бит определяет как результат преобразования запишется в регистры ADCL и ADCH. 
 * При ADLAR = 0 выравнивание производится вправо. При этом в регистр ADCH записывается два старших бита результата, а в регистр ADCL - восемь младших.
 * При ADLAR = 1 выравнивание производится влево. При этом в регистр ADCH записывается восемь старших битов результата, а в регистр ADCL (а именно в его старшие биты: 7 и 6) - два младших.
 */
void avr_driver_right_adjust_set(void)
{
	ADMUX &= ~(1 << ADLAR);
/*
  15  |  14  |  13  |  12  |  11  |  10  |  09  |  08  | 
 -------------------------------------------------------
  -   |  -   |   -  |   -  |   -  |   -  | ADC9 | ADC8 | 
  
  07  |  06  |  05  |  04  |  03  |  02  |  01  |  00  |
  -------------------------------------------------------
 ADC7 | ADC6 | ADC5 | ADC4 | ADC3 | ADC2 | ADC1 | ADC0 |  
*/
}

/**
 * \fn void avr_driver_adc_adjust_set(uint8_t adc_adjust)
 * \brief Функция выбора выравниваня результатов работы АЦП 
 *
 * \param adc_adjust выбранное выравнивание
 */
void avr_driver_adc_adjust_set(uint8_t adc_adjust)
{
	switch (adc_adjust)
	{
		case ADC_ADJUST_LEFT:
		{
			avr_driver_left_adjust_set();
			break;
		}
		case ADC_ADJUST_RIGHT:
		{
			avr_driver_right_adjust_set();
			break;
		}
	}
}

/**
 * \fn void avr_driver_adc_select_channel_single_ended_input(uint8_t adc_channel)
 * \brief Функция выбора канала в качестве входа для АЦП
 *
 * \param adc_channel выбранный канал
 *
 * ADMUX - регистр задаёт входной контакт порта A для подключения АЦП, ориентирование результата и выбор опорной частоты. 
 * MUX3:MUX0 – биты выбора аналогового канала.
 */
void avr_driver_adc_select_channel_single_ended_input(uint8_t adc_channel)
{
	switch (adc_channel)
	{
		case 0:
		{
			ADMUX &= ~(1 << MUX0);
			ADMUX &= ~(1 << MUX1);
			ADMUX &= ~(1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			ADMUX &= ~(1 << MUX4);
			break;
		}
		case 1:
		{
			ADMUX |=  (1 << MUX0);
			ADMUX &= ~(1 << MUX1);
			ADMUX &= ~(1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			ADMUX &= ~(1 << MUX4);
			break;
		}
		case 2:
		{
			ADMUX &= ~(1 << MUX0);
			ADMUX |=  (1 << MUX1);
			ADMUX &= ~(1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			ADMUX &= ~(1 << MUX4);
			break;
		}
		case 3:
		{
			ADMUX |=  (1 << MUX0);
			ADMUX |=  (1 << MUX1);
			ADMUX &= ~(1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			ADMUX &= ~(1 << MUX4);
			break;
		}
		case 4:
		{
			ADMUX &= ~(1 << MUX0);
			ADMUX &= ~(1 << MUX1);
			ADMUX |=  (1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			ADMUX &= ~(1 << MUX4);
			break;
		}
		case 5:
		{
			ADMUX |=  (1 << MUX0);
			ADMUX &= ~(1 << MUX1);
			ADMUX |=  (1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			ADMUX &= ~(1 << MUX4);
			break;
		}
		case 6:
		{
			ADMUX &= ~(1 << MUX0);
			ADMUX |=  (1 << MUX1);
			ADMUX |=  (1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			ADMUX &= ~(1 << MUX4);
			break;
		}
		case 7:
		{
			ADMUX |=  (1 << MUX0);
			ADMUX |=  (1 << MUX1);
			ADMUX |=  (1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			ADMUX &= ~(1 << MUX4);
			break;
		}
	}
}

/**
 * \fn void avr_driver_adc_interrupt_enable(void)
 * \brief Функция разрешения прерывания по завершению преобразования
 *
 * ADCSRA - регистр контроля и статуса АЦП 
 * ADIE - бит разрешения прерывания по завершению преобразования. Если в этом бите установлена единица, и прерывания разрешены глобально, то при окончании преобразования будет выполнен переход по вектору прерывания от АЦП..
 */
void avr_driver_adc_interrupt_enable(void)
{
	ADCSRA |= (1 << ADIE);
}

/**
 * \fn void avr_driver_adc_interrupt_disable(void)
 * \brief Функция запрещения прерывания по завершению преобразования
 *
 * ADCSRA - регистр контроля и статуса АЦП 
 * ADIE - бит разрешения прерывания по завершению преобразования. Если в этом бите установлена единица, и прерывания разрешены глобально, то при окончании преобразования будет выполнен переход по вектору прерывания от АЦП..
 */
void avr_driver_adc_interrupt_disable(void)
{
	ADCSRA &= ~(1 << ADIE);
}

/**
 * \fn void avr_driver_adc_init(uint8_t prescaler, uint8_t voltage_reference, uint8_t adc_adjust)
 * \brief Функция инициализации модуля АЦП
 *
 * \param prescaler выбранный предделитель частоты работы АЦП
 * \param voltage_reference выбранный источник опорного напряжения
 * \param adc_adjust выбранное выравнивание
 */
void avr_driver_adc_init(uint8_t prescaler, uint8_t voltage_reference, uint8_t adc_adjust)
{
	avr_driver_adc_enable();
	avr_driver_adc_prescaler_set(prescaler);
	avr_driver_voltage_reference_set(voltage_reference);
	avr_driver_adc_adjust_set(adc_adjust);
}

/**
 * \fn void adc_driver_start_conversion(void)
 * \brief Функция запуска преобразования
 *
 * ADCSRA - регистр контроля и статуса АЦП 
 * ADSC - бит запуска преобразования. Одиночное преобразование может быть вызвано записью бита ADSC в регистр ADCSRA. 
 * Этот бит остаётся установленным всё время, занимаемое преобразованием. Когда преобразование закончено, бит автоматически устанавливается в 0. Можно также начинать преобразования по событиям из разных источников. 
 * Модуль АЦП также может работать в режиме "свободного полёта". В таком случае АЦП постоянно производит преобразование и обновляет регистры ADCH и ADCL новыми значениями.
 */
void adc_driver_start_conversion(void)
{
	ADCSRA |= (1 << ADSC);
}

/**
 * \fn void adc_driver_wait_till_conversion_is_complete_interrrupt(void)
 * \brief Функция ожидания завершения преобразования (через прерывание)
 *
 * ADCSRA - регистр контроля и статуса АЦП 
 * ADIF - флаг прерывания АЦП. Этот бит устанавливается в 1 когда АЦП завершено преобразование и в регистрах ADCL и ADCH находятся актуальные данные. 
 * Этот флаг устанавливается даже в том случае, если прерывания запрещены. Это необходимо для случая программного опроса АЦП. 
 * Если используются прерывания, то флаг сбрасывается автоматически. Если используется программный опрос, то флаг может быть сброшен записью лог.1 в этот бит.
 */
void adc_driver_wait_till_conversion_is_complete_interrrupt(void)
{
	while ((ADCSRA & (1 << ADIF)) != 0x10); 
}

/**
 * \fn void adc_driver_wait_till_conversion_is_complete(void)
 * \brief Функция ожидания завершения преобразования 
 *
 * ADCSRA - регистр контроля и статуса АЦП 
 * ADSC - бит запуска преобразования. Одиночное преобразование может быть вызвано записью бита ADSC в регистр ADCSRA. 
 * Этот бит остаётся установленным всё время, занимаемое преобразованием. Когда преобразование закончено, бит автоматически устанавливается в 0. Можно также начинать преобразования по событиям из разных источников. 
 * Модуль АЦП также может работать в режиме "свободного полёта". В таком случае АЦП постоянно производит преобразование и обновляет регистры ADCH и ADCL новыми значениями.
 */
void adc_driver_wait_till_conversion_is_complete(void)
{
	while((ADCSRA & (1 << ADSC)));    
}

/**
 * \fn void adc_driver_clear_conversion_complete_interrupt_flag(void)
 * \brief Функция сброса флага о завершении преобразования
 *
 * ADCSRA - регистр контроля и статуса АЦП 
 * ADIF - флаг прерывания АЦП. Этот бит устанавливается в 1 когда АЦП завершено преобразование и в регистрах ADCL и ADCH находятся актуальные данные. 
 * Этот флаг устанавливается даже в том случае, если прерывания запрещены. Это необходимо для случая программного опроса АЦП. 
 * Если используются прерывания, то флаг сбрасывается автоматически. Если используется программный опрос, то флаг может быть сброшен записью лог.1 в этот бит.
 */
void adc_driver_clear_conversion_complete_interrupt_flag(void)
{	
	ADCSRA |= (1 << ADIF);
}

/**
 * \fn uint16_t adc_driver_read_adc_result(void)
 * \brief Функция чтения значения АЦП
 *
 */
uint16_t adc_driver_read_adc_result(void)
{
	return ADC;
}

/**
 * \fn uint16_t adc_driver_convert(void)
 * \brief Функция полного цикла работы АЦП (без прерываний)
 *
 */
uint16_t adc_driver_convert(void)
{
	uint16_t result = 0;

	adc_driver_start_conversion();
	adc_driver_wait_till_conversion_is_complete();
	result = adc_driver_read_adc_result();
	
	return result;
}