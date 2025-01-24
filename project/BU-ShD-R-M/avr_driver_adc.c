/*! 
  \file
  \defgroup		avr_driver_adc
  \brief		���� ��������� ���� ��������� avr_driver_adc.c
  \author		������ �.�.
 
  ���� ��������� ���� �������� � ���� �������� �������, ������������ � �������� ���������.
  �������� ��� ������������ �� ���� ������� ��� ����������������� ���� AVR.
 
  - Compiler:           GNU AVR toolchain
  - Supported devices:  AtMega64A
*/
#include "avr_driver_adc.h"

/**
 * \fn void avr_driver_adc_enable(void)
 * \brief ������� ���������� ������ ���
 *
 * ADCSRA - ������� �������� � ������� ��� 
 * ADEN - ��� ���������� ������ ��� 
 * ��������� ������� ���� � ��������� 1 ��������� ADC. 
 * ������� ���� ��������� ADC. 
 * ���������� ADC � �������� �������������� ���������� ��������������.
 */
void avr_driver_adc_enable(void)
{
	ADCSRA |= (1 << ADEN);
}

/**
 * \fn void avr_driver_adc_disable(void)
 * \brief ������� ���������� ������ ���
 *
 * ADCSRA - ������� �������� � ������� ��� 
 * ADEN - ��� ���������� ������ ��� 
 * ��������� ������� ���� � ��������� 1 ��������� ADC. 
 * ������� ���� ��������� ADC. 
 * ���������� ADC � �������� �������������� ���������� ��������������.
 */
void avr_driver_adc_disable(void)
{		
	ADCSRA &= ~(1 << ADEN);
}

/**
 * \fn void avr_driver_adc_prescaler_set(uint8_t prescaler)
 * \brief ������� ������ ������������ ������� ������ ���
 *
 * \param prescaler ��������� ������������ ������� ������ ���
 *
 * ADCSRA - ������� �������� � ������� ��� 
 * ADPS2..ADPS0 - ���� ������ ������������ ���������������� �������
 * ������ ���� ���������� ����������� ������� ������� XTAL ��� ��������� ����������� �������� ������� ���.
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
 * \brief ������� ������ �������� ���������� ���
 *
 * \param voltage_reference ��������� �������� �������� ����������
 *
 * ADMUX - ������� ����� ������� ������� ����� A ��� ����������� ���, �������������� ���������� � ����� ������� �������. 
 * REFS1:REFS0 - ���� ������ �������� ����������. 
 * ���� ������ ��� ���� �� ����� ��������������, �� ��������� ������� � ���� ������ ����� �������� ��������������. 
 * � �������� �������� ���������� ����� ���� ������ AVcc (���������� ��������� �������), AREF ��� ���������� 2.56� �������� �������� ����������.
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
 * \brief ������� ������ ����������� ����������� ������ ��� �����
 *
 * ADMUX - ������� ����� ������� ������� ����� A ��� ����������� ���, �������������� ���������� � ����� ������� �������. 
 * ADLAR - ��� ���������� ��� ��������� �������������� ��������� � �������� ADCL � ADCH. 
 * ��� ADLAR = 0 ������������ ������������ ������. ��� ���� � ������� ADCH ������������ ��� ������� ���� ����������, � � ������� ADCL - ������ �������.
 * ��� ADLAR = 1 ������������ ������������ �����. ��� ���� � ������� ADCH ������������ ������ ������� ����� ����������, � � ������� ADCL (� ������ � ��� ������� ����: 7 � 6) - ��� �������.
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
 * \brief ������� ������ ����������� ����������� ������ ��� ������
 *
 * ADMUX - ������� ����� ������� ������� ����� A ��� ����������� ���, �������������� ���������� � ����� ������� �������. 
 * ADLAR - ��� ���������� ��� ��������� �������������� ��������� � �������� ADCL � ADCH. 
 * ��� ADLAR = 0 ������������ ������������ ������. ��� ���� � ������� ADCH ������������ ��� ������� ���� ����������, � � ������� ADCL - ������ �������.
 * ��� ADLAR = 1 ������������ ������������ �����. ��� ���� � ������� ADCH ������������ ������ ������� ����� ����������, � � ������� ADCL (� ������ � ��� ������� ����: 7 � 6) - ��� �������.
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
 * \brief ������� ������ ����������� ����������� ������ ��� 
 *
 * \param adc_adjust ��������� ������������
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
 * \brief ������� ������ ������ � �������� ����� ��� ���
 *
 * \param adc_channel ��������� �����
 *
 * ADMUX - ������� ����� ������� ������� ����� A ��� ����������� ���, �������������� ���������� � ����� ������� �������. 
 * MUX3:MUX0 � ���� ������ ����������� ������.
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
 * \brief ������� ���������� ���������� �� ���������� ��������������
 *
 * ADCSRA - ������� �������� � ������� ��� 
 * ADIE - ��� ���������� ���������� �� ���������� ��������������. ���� � ���� ���� ����������� �������, � ���������� ��������� ���������, �� ��� ��������� �������������� ����� �������� ������� �� ������� ���������� �� ���..
 */
void avr_driver_adc_interrupt_enable(void)
{
	ADCSRA |= (1 << ADIE);
}

/**
 * \fn void avr_driver_adc_interrupt_disable(void)
 * \brief ������� ���������� ���������� �� ���������� ��������������
 *
 * ADCSRA - ������� �������� � ������� ��� 
 * ADIE - ��� ���������� ���������� �� ���������� ��������������. ���� � ���� ���� ����������� �������, � ���������� ��������� ���������, �� ��� ��������� �������������� ����� �������� ������� �� ������� ���������� �� ���..
 */
void avr_driver_adc_interrupt_disable(void)
{
	ADCSRA &= ~(1 << ADIE);
}

/**
 * \fn void avr_driver_adc_init(uint8_t prescaler, uint8_t voltage_reference, uint8_t adc_adjust)
 * \brief ������� ������������� ������ ���
 *
 * \param prescaler ��������� ������������ ������� ������ ���
 * \param voltage_reference ��������� �������� �������� ����������
 * \param adc_adjust ��������� ������������
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
 * \brief ������� ������� ��������������
 *
 * ADCSRA - ������� �������� � ������� ��� 
 * ADSC - ��� ������� ��������������. ��������� �������������� ����� ���� ������� ������� ���� ADSC � ������� ADCSRA. 
 * ���� ��� ������� ������������� �� �����, ���������� ���������������. ����� �������������� ���������, ��� ������������� ��������������� � 0. ����� ����� �������� �������������� �� �������� �� ������ ����������. 
 * ������ ��� ����� ����� �������� � ������ "���������� �����". � ����� ������ ��� ��������� ���������� �������������� � ��������� �������� ADCH � ADCL ������ ����������.
 */
void adc_driver_start_conversion(void)
{
	ADCSRA |= (1 << ADSC);
}

/**
 * \fn void adc_driver_wait_till_conversion_is_complete_interrrupt(void)
 * \brief ������� �������� ���������� �������������� (����� ����������)
 *
 * ADCSRA - ������� �������� � ������� ��� 
 * ADIF - ���� ���������� ���. ���� ��� ��������������� � 1 ����� ��� ��������� �������������� � � ��������� ADCL � ADCH ��������� ���������� ������. 
 * ���� ���� ��������������� ���� � ��� ������, ���� ���������� ���������. ��� ���������� ��� ������ ������������ ������ ���. 
 * ���� ������������ ����������, �� ���� ������������ �������������. ���� ������������ ����������� �����, �� ���� ����� ���� ������� ������� ���.1 � ���� ���.
 */
void adc_driver_wait_till_conversion_is_complete_interrrupt(void)
{
	while ((ADCSRA & (1 << ADIF)) != 0x10); 
}

/**
 * \fn void adc_driver_wait_till_conversion_is_complete(void)
 * \brief ������� �������� ���������� �������������� 
 *
 * ADCSRA - ������� �������� � ������� ��� 
 * ADSC - ��� ������� ��������������. ��������� �������������� ����� ���� ������� ������� ���� ADSC � ������� ADCSRA. 
 * ���� ��� ������� ������������� �� �����, ���������� ���������������. ����� �������������� ���������, ��� ������������� ��������������� � 0. ����� ����� �������� �������������� �� �������� �� ������ ����������. 
 * ������ ��� ����� ����� �������� � ������ "���������� �����". � ����� ������ ��� ��������� ���������� �������������� � ��������� �������� ADCH � ADCL ������ ����������.
 */
void adc_driver_wait_till_conversion_is_complete(void)
{
	while((ADCSRA & (1 << ADSC)));    
}

/**
 * \fn void adc_driver_clear_conversion_complete_interrupt_flag(void)
 * \brief ������� ������ ����� � ���������� ��������������
 *
 * ADCSRA - ������� �������� � ������� ��� 
 * ADIF - ���� ���������� ���. ���� ��� ��������������� � 1 ����� ��� ��������� �������������� � � ��������� ADCL � ADCH ��������� ���������� ������. 
 * ���� ���� ��������������� ���� � ��� ������, ���� ���������� ���������. ��� ���������� ��� ������ ������������ ������ ���. 
 * ���� ������������ ����������, �� ���� ������������ �������������. ���� ������������ ����������� �����, �� ���� ����� ���� ������� ������� ���.1 � ���� ���.
 */
void adc_driver_clear_conversion_complete_interrupt_flag(void)
{	
	ADCSRA |= (1 << ADIF);
}

/**
 * \fn uint16_t adc_driver_read_adc_result(void)
 * \brief ������� ������ �������� ���
 *
 */
uint16_t adc_driver_read_adc_result(void)
{
	return ADC;
}

/**
 * \fn uint16_t adc_driver_convert(void)
 * \brief ������� ������� ����� ������ ��� (��� ����������)
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