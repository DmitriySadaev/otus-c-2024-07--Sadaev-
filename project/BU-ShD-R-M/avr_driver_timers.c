/*! 
  \file
  \defgroup		avr_driver_timers
  \brief		Файл исходного кода программы avr_driver_timers.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя драйвер аппаратных таймеров микроконтроллеров ядра AVR.
 
  - Compiler:           GNU AVR toolchain
  - Supported devices:  AtMega64A
  - AppNote:            
*/
#include "avr_driver_timers.h"

/**
 * \fn void timer_prescaler_set(uint8_t timer_n, uint16_t timer_prescaler)
 * \brief Функция настраивает предделитель таймера
 *
 * \param timer_n номер настраиваемого таймера
 * \param timer_prescaler настраиваемый предделитель для этого таймера
 *
 * Допустимые значения предделителя: 0, 1, 8, 32, 64, 128, 256, 1024
 * При нуле таймер/счетчик выключен, при единице частота - без предделителя
 */
void timer_prescaler_set(uint8_t timer_n, uint16_t timer_prescaler)
{
	if (timer_n == 0)
	{
		switch (timer_prescaler)
		{
			case 0:
			{
				TCCR0 &= ~(1 << CS02); 
				TCCR0 &= ~(1 << CS01);
				TCCR0 &= ~(1 << CS00);
				break;
			}
			case 1:
			{
				TCCR0 &= ~(1 << CS02);
				TCCR0 &= ~(1 << CS01);
				TCCR0 |=  (1 << CS00);
				break;
			}		
			case 8:
			{
				TCCR0 &= ~(1 << CS02);
				TCCR0 |=  (1 << CS01);
				TCCR0 &= ~(1 << CS00);
				break;
			}	
			case 32:
			{
				TCCR0 &= ~(1 << CS02);
				TCCR0 |=  (1 << CS01);
				TCCR0 |=  (1 << CS00);
				break;
			}				
			case 64:
			{
				TCCR0 |=  (1 << CS02);
				TCCR0 &= ~(1 << CS01);
				TCCR0 &= ~(1 << CS00);
				break;
			}		
			case 128:
			{
				TCCR0 |=  (1 << CS02);
				TCCR0 &= ~(1 << CS01);
				TCCR0 |=  (1 << CS00);
				break;
			}		
			case 256:
			{
				TCCR0 |=  (1 << CS02);
				TCCR0 |=  (1 << CS01);
				TCCR0 &= ~(1 << CS00);
				break;
			}		
			case 1024:
			{
				TCCR0 |= (1 << CS02);
				TCCR0 |= (1 << CS01);
				TCCR0 |= (1 << CS00);
				break;
			}		
		}
	}
	if (timer_n == 2)
	{
		switch (timer_prescaler)
		{
			case 0:
			{
				TCCR2 &= ~(1 << CS22);
				TCCR2 &= ~(1 << CS21);
				TCCR2 &= ~(1 << CS20);
				break;
			}
			case 1:
			{
				TCCR2 &= ~(1 << CS22);
				TCCR2 &= ~(1 << CS21);
				TCCR2 |=  (1 << CS20);
				break;
			}
			case 8:
			{
				TCCR2 &= ~(1 << CS22);
				TCCR2 |=  (1 << CS21);
				TCCR2 &= ~(1 << CS20);
				break;
			}
			case 32:
			{
				TCCR2 &= ~(1 << CS22);
				TCCR2 |=  (1 << CS21);
				TCCR2 |=  (1 << CS20);
				break;
			}
			case 64:
			{
				TCCR2 |=  (1 << CS22);
				TCCR2 &= ~(1 << CS21);
				TCCR2 &= ~(1 << CS20);
				break;
			}
			case 128:
			{
				TCCR2 |=  (1 << CS22);
				TCCR2 &= ~(1 << CS21);
				TCCR2 |=  (1 << CS20);
				break;
			}
			case 256:
			{
				TCCR2 |=  (1 << CS22);
				TCCR2 |=  (1 << CS21);
				TCCR2 &= ~(1 << CS20);
				break;
			}
			case 1024:
			{
				TCCR2 |= (1 << CS22);
				TCCR2 |= (1 << CS21);
				TCCR2 |= (1 << CS20);
				break;
			}
		}
	}
}

/**
 * \fn void timer_waveform_generation_mode_set(uint8_t timer_n, uint8_t timer_waveform_generation_mode)
 * \brief Функция настраивает режим работы таймера/счетчика
 *
 * \param timer_n номер настраиваемого таймера
 * \param timer_waveform_generation_mode настраиваемый режим работы для этого таймера
 *
 * Счетчик/Таймер0 поддерживает следующие режимы работы:
 * - Нормальная работа (Normal mode);
 * - Очистка таймера по совпадению значения (Clear Timer on Compare Match - CTC):
 * - ШИМ (PWM);
 * - Быстрая ШИМ (Fast PWM).
 * Mode | WGM01 | WGM00 | Timer/Counter Mode of Operation | TOP | Update of | TOV0 Flag
 *      |(CTC0) | (PWM0)|                                 |     |    OCR0   | Set
 * -------------------------------------------------------------------------------------
 * 0    |0	    |0	    |Normal							  |0xFF |Immediate  | MAX
 * 1    |0	    |1	    |PWM, Phase correct				  |0xFF |TOP		| BOTTOM
 * 2    |1	    |0	    |CTC						      |OCR0 |Immediate  | MAX
 * 3    |1      |1      |Fast PWM						  |0xFF |BOTTOM	    | MAX
 */
void timer_waveform_generation_mode_set(uint8_t timer_n, uint8_t timer_waveform_generation_mode)
{
	if (timer_n == 0)
	{
		switch (timer_waveform_generation_mode)
		{
			case NORMAL:
			{
				TCCR0 &= ~(1 << WGM01);
				TCCR0 &= ~(1 << WGM00);
				break;
			}
			case PWM:
			{
				TCCR0 &= ~(1 << WGM01);
				TCCR0 |=  (1 << WGM00);
				break;
			}	
			case CTC:
			{
				TCCR0 |=  (1 << WGM01);
				TCCR0 &= ~(1 << WGM00);
				break;
			}	
			case FAST_PWM:
			{
				TCCR0 |=  (1 << WGM01);
				TCCR0 |=  (1 << WGM00);
				break;
			}										
		}
	}
	if (timer_n == 2)
	{
		switch (timer_waveform_generation_mode)
		{
			case NORMAL:
			{
				TCCR2 &= ~(1 << WGM21);
				TCCR2 &= ~(1 << WGM20);
				break;
			}
			case PWM:
			{
				TCCR2 &= ~(1 << WGM21);
				TCCR2 |=  (1 << WGM20);
				break;
			}	
			case CTC:
			{
				TCCR2 |=  (1 << WGM21);
				TCCR2 &= ~(1 << WGM20);
				break;
			}	
			case FAST_PWM:
			{
				TCCR2 |=  (1 << WGM21);
				TCCR2 |=  (1 << WGM20);
				break;
			}										
		}
	}
}

/**
 * \fn void timer_compare_output_mode_set(uint8_t timer_n, uint8_t timer_compare_output_mode, uint8_t compare_interrupt_value)
 * \brief Функция настраивает выходной режим порта если таймер/счетчик0 настроен как счетчик
 *
 * \param timer_n номер настраиваемого таймера
 * \param timer_compare_output_mode настраиваемый режим работы для этого таймера
 * \param compare_interrupt_value значение для записи в регистр сравнения
 *
 * Если установлен хотя бы один из битов COM01:0, то вывод счетчика ОС0 заменит собой
 * нормальную работу I/O пина порта ввода/вывода.
 * Тем не менее, для корректной работы (настройки вывода) потребуется также установить
 * соответствующий бит в регистре Data Direction Register (DDR).
 */
void timer_compare_output_mode_set(uint8_t timer_n, uint8_t timer_compare_output_mode, uint8_t compare_interrupt_value)
{
	if (timer_n == 0)
	{
		switch (timer_compare_output_mode)
		{
			case NORMAL_PORT_OPERATION:
			{
				TCCR0 &= ~(1 << COM01);
				TCCR0 &= ~(1 << COM00);
				break;
			}
			case TOGGLE_OC0_ON_COMPARE_MATCH:
			{
				if ((timer_compare_output_mode == NORMAL) || (timer_compare_output_mode == CTC))
				{
					TCCR0 &= ~(1 << COM01);
					TCCR0 |=  (1 << COM00);
				}
				break;
			}
			case CLEAR_OC0_ON_COMPARE_MATCH:
			{
				TCCR0 |=  (1 << COM01);
				TCCR0 &= ~(1 << COM00);
				break;
			}
			case SET_OC0_ON_COMPARE_MATCH:
			{
				TCCR0 |=  (1 << COM01);
				TCCR0 |=  (1 << COM00);
				break;
			}
		}	
	OCR0 = compare_interrupt_value;
	} 
	if (timer_n == 2)
	{
		switch (timer_compare_output_mode)
		{
			case NORMAL_PORT_OPERATION:
			{
				TCCR2 &= ~(1 << COM21);
				TCCR2 &= ~(1 << COM20);
				break;
			}
			case TOGGLE_OC0_ON_COMPARE_MATCH:
			{
				if ((timer_compare_output_mode == NORMAL) || (timer_compare_output_mode == CTC))
				{
					TCCR2 &= ~(1 << COM21);
					TCCR2 |=  (1 << COM20);
				}
				break;
			}
			case CLEAR_OC0_ON_COMPARE_MATCH:
			{
				TCCR2 |=  (1 << COM21);
				TCCR2 &= ~(1 << COM20);
				break;
			}
			case SET_OC0_ON_COMPARE_MATCH:
			{
				TCCR2 |=  (1 << COM21);
				TCCR2 |=  (1 << COM20);
				break;
			}
		}
		OCR2 = compare_interrupt_value;
	}
}

/**
 * \fn void timer_compare_match_interrupt_enable_set(uint8_t timer_n, uint8_t timer_compare_match_interrupt_enable)
 * \brief Функция настраивает разрешение на срабатывание вектора прерывания по сравнению значения таймера
 *
 * \param timer_n номер настраиваемого таймера
 * \param timer_compare_match_interrupt_enable разрешение/запрещение прерывавания по сравнени указанного таймера
 *
 */
void timer_compare_match_interrupt_enable_set(uint8_t timer_n, uint8_t timer_compare_match_interrupt_enable)
{
	if (timer_n == 0)
	{
		switch (timer_compare_match_interrupt_enable)
		{
			case FALSE:
			{
				TIMSK &= ~(1 << OCIE0);
				break;
			}		
			case TRUE:
			{
				TIMSK |= (1 << OCIE0);
				break;
			}
		}
	}
	if (timer_n == 2)
	{
		switch (timer_compare_match_interrupt_enable)
		{
			case FALSE:
			{
				TIMSK &= ~(1 << OCIE2);
				break;
			}
			case TRUE:
			{
				TIMSK |= (1 << OCIE2);
				break;
			}
		}
	}
}

/**
 * \fn void timer_overflow_interrupt_enable_set(uint8_t timer_n, uint8_t timer_overflow_interrupt_enable)
 * \brief Функция настраивает разрешение на срабатывание вектора прерывания по переполнению значения таймера
 *
 * \param timer_n номер настраиваемого таймера
 * \param timer_overflow_interrupt_enable разрешение/запрещение прерывавания по переполнению указанного таймера
 *
 */
void timer_overflow_interrupt_enable_set(uint8_t timer_n, uint8_t timer_overflow_interrupt_enable)
{
	if (timer_n == 0)
	{	
		switch (timer_overflow_interrupt_enable)
		{
			case FALSE:
			{
				TIMSK &= ~(1 << TOIE0);
				break;
			}
			case TRUE:
			{
				TIMSK |= (1 << TOIE0);
				break;
			}
		}
	}
		if (timer_n == 2)
		{
			switch (timer_overflow_interrupt_enable)
			{
				case FALSE:
				{
					TIMSK &= ~(1 << TOIE2);
					break;
				}
				case TRUE:
				{
					TIMSK |= (1 << TOIE2);
					break;
				}
			}
		}
}

/**
 * \fn void timer_init(uint8_t timer_n, uint16_t timer_prescaler, uint8_t timer_waveform_generation_mode, uint8_t timer_compare_output_mode, uint8_t timer_compare_match_interrupt_enable, uint8_t timer_overflow_interrupt_enable, uint8_t compare_interrupt_value)
 * \brief Функция инициализации и настройки указанного таймера
 *
 * \param timer_n номер настраиваемого таймера
 * \param timer_prescaler номер настраиваемого таймера
 * \param timer_waveform_generation_mode настраиваемый режим работы для этого таймера (Normal, CTC, PWM, Fast PWM)
 * \param timer_compare_output_mode настраиваемый режим работы для этого таймера (Normal, Toggle on Compare, Set on Compare, Clear on Compare)
 * \param timer_compare_match_interrupt_enable разрешение/запрещение прерывавания по сравнению указанного таймера
 * \param timer_overflow_interrupt_enable разрешение/запрещение прерывавания по переполнению указанного таймера
 * \param compare_interrupt_value значение для записи в регистр сравнения
 */
void timer_init(uint8_t timer_n, uint16_t timer_prescaler, uint8_t timer_waveform_generation_mode, uint8_t timer_compare_output_mode, uint8_t timer_compare_match_interrupt_enable, uint8_t timer_overflow_interrupt_enable, uint8_t compare_interrupt_value)
{
    timer_compare_match_interrupt_enable_set(timer_n, timer_compare_match_interrupt_enable);
    timer_overflow_interrupt_enable_set(timer_n, timer_overflow_interrupt_enable);
    timer_prescaler_set(timer_n, timer_prescaler);
    timer_waveform_generation_mode_set(timer_n, timer_waveform_generation_mode);
    timer_compare_output_mode_set(timer_n, timer_compare_output_mode, compare_interrupt_value);	
}

/**
 * \fn uint8_t timer_check_compare_match(uint8_t timer_n)
 * \brief Функция проверяет наличие флага о том, что значение счетного регистра совпало с регистром сравнения
 *
 * \param timer_n номер  таймера
 */
uint8_t timer_check_compare_match(uint8_t timer_n)
{
	if ((TIFR & (1 << OCF0)) && (timer_n == 0))
	{
		TIFR |= (1 << OCF0);
		return TRUE;
	} 
	if ((TIFR & (1 << OCF2)) && (timer_n == 2))
	{
		TIFR |= (1 << OCF2);
		return TRUE;
	}	
	else
	{
		return FALSE;
	}
}

/**
 * \fn uint8_t timer_check_overflow(uint8_t timer_n)
 * \brief Функция проверяет что произошло переполнение таймера
 *
 * \param timer_n номер  таймера
 */
uint8_t timer_check_overflow(uint8_t timer_n)
{
	if ((TIFR & (1 << TOV0)) && (timer_n == 0))
	{
		TIFR |= (1 << TOV0);
		return TRUE;
	}
	if ((TIFR & (1 << TOV2)) && (timer_n == 2))
	{
		TIFR |= (1 << TOV2);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}