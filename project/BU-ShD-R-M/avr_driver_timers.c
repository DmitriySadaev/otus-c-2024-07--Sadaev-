/*! 
  \file
  \defgroup		avr_driver_timers
  \brief		���� ��������� ���� ��������� avr_driver_timers.c
  \author		������ �.�.
 
  ���� ��������� ���� �������� � ���� �������� �������, ������������ � �������� ���������.
  �������� ��� ������������ �� ���� ������� ���������� �������� ����������������� ���� AVR.
 
  - Compiler:           GNU AVR toolchain
  - Supported devices:  AtMega64A
  - AppNote:            
*/
#include "avr_driver_timers.h"

/**
 * \fn void timer_prescaler_set(uint8_t timer_n, uint16_t timer_prescaler)
 * \brief ������� ����������� ������������ �������
 *
 * \param timer_n ����� �������������� �������
 * \param timer_prescaler ������������� ������������ ��� ����� �������
 *
 * ���������� �������� ������������: 0, 1, 8, 32, 64, 128, 256, 1024
 * ��� ���� ������/������� ��������, ��� ������� ������� - ��� ������������
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
 * \brief ������� ����������� ����� ������ �������/��������
 *
 * \param timer_n ����� �������������� �������
 * \param timer_waveform_generation_mode ������������� ����� ������ ��� ����� �������
 *
 * �������/������0 ������������ ��������� ������ ������:
 * - ���������� ������ (Normal mode);
 * - ������� ������� �� ���������� �������� (Clear Timer on Compare Match - CTC):
 * - ��� (PWM);
 * - ������� ��� (Fast PWM).
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
 * \brief ������� ����������� �������� ����� ����� ���� ������/�������0 �������� ��� �������
 *
 * \param timer_n ����� �������������� �������
 * \param timer_compare_output_mode ������������� ����� ������ ��� ����� �������
 * \param compare_interrupt_value �������� ��� ������ � ������� ���������
 *
 * ���� ���������� ���� �� ���� �� ����� COM01:0, �� ����� �������� ��0 ������� �����
 * ���������� ������ I/O ���� ����� �����/������.
 * ��� �� �����, ��� ���������� ������ (��������� ������) ����������� ����� ����������
 * ��������������� ��� � �������� Data Direction Register (DDR).
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
 * \brief ������� ����������� ���������� �� ������������ ������� ���������� �� ��������� �������� �������
 *
 * \param timer_n ����� �������������� �������
 * \param timer_compare_match_interrupt_enable ����������/���������� ������������ �� �������� ���������� �������
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
 * \brief ������� ����������� ���������� �� ������������ ������� ���������� �� ������������ �������� �������
 *
 * \param timer_n ����� �������������� �������
 * \param timer_overflow_interrupt_enable ����������/���������� ������������ �� ������������ ���������� �������
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
 * \brief ������� ������������� � ��������� ���������� �������
 *
 * \param timer_n ����� �������������� �������
 * \param timer_prescaler ����� �������������� �������
 * \param timer_waveform_generation_mode ������������� ����� ������ ��� ����� ������� (Normal, CTC, PWM, Fast PWM)
 * \param timer_compare_output_mode ������������� ����� ������ ��� ����� ������� (Normal, Toggle on Compare, Set on Compare, Clear on Compare)
 * \param timer_compare_match_interrupt_enable ����������/���������� ������������ �� ��������� ���������� �������
 * \param timer_overflow_interrupt_enable ����������/���������� ������������ �� ������������ ���������� �������
 * \param compare_interrupt_value �������� ��� ������ � ������� ���������
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
 * \brief ������� ��������� ������� ����� � ���, ��� �������� �������� �������� ������� � ��������� ���������
 *
 * \param timer_n �����  �������
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
 * \brief ������� ��������� ��� ��������� ������������ �������
 *
 * \param timer_n �����  �������
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