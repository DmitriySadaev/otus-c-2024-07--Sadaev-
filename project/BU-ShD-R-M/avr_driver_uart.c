/*! 
  \file
  \defgroup		avr_driver_uart
  \brief		���� ��������� ���� ��������� avr_driver_uart.c
  \author		������ �.�.
 
  ���� ��������� ���� �������� � ���� �������� �������, ������������ � �������� ���������.
  �������� ��� ������������ �� ���� ������� UART ����������������� ���� AVR.
 
  - Compiler:           GNU AVR toolchain
  - Supported devices:  AtMega64A
  - AppNote:            
*/
#include "avr_driver_uart.h"

/**
 * \fn void avr_driver_uart_set_error_flags_to_zero(uint8_t n_uart)
 * \brief ������� �������� ����� ������ ���������� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnA - ������� �������� � ������� UART �
 * FEn - ��� ������ �����
 * DORn - ��� ������ ������������
 * UPEn - ��� ������ ��������
 */
void avr_driver_uart_set_error_flags_to_zero(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0A &= ~(1 << FE0);
			UCSR0A &= ~(1 << DOR0);
			UCSR0A &= ~(1 << UPE0);
			break;			
		}
		case 1:
		{
			UCSR1A &= ~(1 << FE1);
			UCSR1A &= ~(1 << DOR1);
			UCSR1A &= ~(1 << UPE1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_set_double_speed(uint8_t n_uart)
 * \brief ������� ������������� ����� ������� �������� ���������� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnA - ������� �������� � ������� UART �
 * U2Xn - ��� �������� �������� �������� �� UART
 */
void avr_driver_uart_set_double_speed(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0A |= (1 << U2X0);
			break;	
		}
		case 1:
		{
			UCSR1A |= (1 << U2X1);
			break;
		}

	}
	avr_driver_uart_set_error_flags_to_zero(n_uart); //��������� ������ ������ ��� ������ � UCSRA (�. 25.11.2)
}

/**
 * \fn void avr_driver_uart_set_single_speed(uint8_t n_uart)
 * \brief ������� ������������� ����� ��������� �������� ���������� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnA - ������� �������� � ������� UART �
 * U2Xn - ��� �������� �������� �������� �� UART
 */
void avr_driver_uart_set_single_speed(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0A &= ~(1 << U2X0);
			break;
		}
		case 1:
		{
			UCSR1A &= ~(1 << U2X1);
			break;
		}

	}
	avr_driver_uart_set_error_flags_to_zero(n_uart); //��������� ������ ������ ��� ������ � UCSRA (�. 25.11.2)	
}

/**
 * \fn void avr_driver_uart_set_baudrate(uint8_t n_uart, uint32_t baudrate, uint32_t f_cpu)
 * \brief ������� ������������� ��������� �������� �������� �� ���������� UART
 *
 * \param n_uart ����� UART
 * \param baudrate ��������� �������� �������� ������
 * \param f_cpu ������� ������ �����������
 *
 * UCSRnA - ������� �������� � ������� UART �
 * U2Xn - ��� �������� �������� �������� �� UART
 * UBRRnH - ������� ������� �������� UART
 * UBRRnL - ������� ������� �������� UART
 */
void avr_driver_uart_set_baudrate(uint8_t n_uart, uint32_t baudrate, uint32_t f_cpu)
{
	switch (n_uart)
	{
		case 0:
		{
			if (UCSR0A & (1 << U2X0))
			{
				UBRR0H = (uint8_t)((f_cpu/8/baudrate-1) >> 8);
				UBRR0L = (uint8_t)(f_cpu/8/baudrate-1);
			}
			if (!(UCSR0A & (1 << U2X0)))
			{
				UBRR0H = (uint8_t)((f_cpu/16/baudrate-1) >> 8);
				UBRR0L = (uint8_t)(f_cpu/16/baudrate-1);
			}
			break;			
		}
		case 1:
		{
			if (UCSR1A & (1 << U2X1))
			{
				UBRR1H = (uint8_t)((f_cpu/8/baudrate-1) >> 8);
				UBRR1L = (uint8_t)(f_cpu/8/baudrate-1);
			}
			if (!(UCSR1A & (1 << U2X1)))
			{
				UBRR1H = (uint8_t)((f_cpu/16/baudrate-1) >> 8);
				UBRR1L = (uint8_t)(f_cpu/16/baudrate-1);
			}
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_transmitter_enable(uint8_t n_uart)
 * \brief ������� ��������� �������� �� ���������� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * TXENn - ��� ���������� �������� �� UART
 */
void avr_driver_uart_transmitter_enable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B |= (1 << TXEN0);
			break;
		}
		case 1:
		{
			UCSR1B |= (1 << TXEN1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_transmitter_disable(uint8_t n_uart)
 * \brief ������� ��������� �������� �� ���������� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * TXENn - ��� ���������� �������� �� UART
 */
void avr_driver_uart_transmitter_disable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B &= ~(1 << TXEN0);
			break;
		}
		case 1:
		{
			UCSR1B &= ~(1 << TXEN1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_receiver_enable(uint8_t n_uart)
 * \brief ������� ��������� ����� �� ���������� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * RXENn - ��� ���������� ������ �� UART
 */
void avr_driver_uart_receiver_enable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B |= (1 << RXEN0);
			break;
		}
		case 1:
		{
			UCSR1B |= (1 << RXEN1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_receiver_disable(uint8_t n_uart)
 * \brief ������� ��������� ����� �� ���������� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * RXENn - ��� ���������� ������ �� UART
 */
void avr_driver_uart_receiver_disable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B &= ~(1 << RXEN0);
			break;
		}
		case 1:
		{
			UCSR1B &= ~(1 << RXEN1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_operation_mode_select(uint8_t n_uart, uint8_t op_mode)
 * \brief ������� ������������� ���������� ��� ������������ ����� ������ ���������� UART
 *
 * \param n_uart ����� UART
 * \param op_mode ����� ������
 *
 * UCSRnC - ������� �������� � ������� UART C
 * UMSELn - ��� ������� �����������/������������ ������ ������
 */
void avr_driver_uart_operation_mode_select(uint8_t n_uart, uint8_t op_mode)
{
	switch (n_uart)
	{
		case 0:
		{
			if (op_mode == AVR_DRIVER_UART_ASYNC_OPERATION_MODE)
			{
				UCSR0C &= ~(1 << UMSEL0); 
			}
			if (op_mode == AVR_DRIVER_UART_SYNC_OPERATION_MODE)
			{
				UCSR0C |= (1 << UMSEL0);
			}
			break;
		}
		case 1:
		{
			if (op_mode == AVR_DRIVER_UART_ASYNC_OPERATION_MODE)
			{
				UCSR1C &= ~(1 << UMSEL1);
			}
			if (op_mode == AVR_DRIVER_UART_SYNC_OPERATION_MODE)
			{
				UCSR1C |= (1 << UMSEL1);
			}
			break;
		}
	}	
}

/**
 * \fn void avr_driver_uart_stop_bit_select(uint8_t n_uart, uint8_t n_stop_bits)
 * \brief ������� ������������� �������� ����� ����-���
 *
 * \param n_uart ����� UART
 * \param n_stop_bits ����� ����-���
 *
 * UCSRnC - ������� �������� � ������� UART C
 * USBSn - ��� ��������� ������� ����-���� (���� ������  ����� ������)
 */
void avr_driver_uart_stop_bit_select(uint8_t n_uart, uint8_t n_stop_bits)
{
	switch (n_uart)
	{
		case 0:
		{
			if (n_stop_bits == 1)
			{
				UCSR0C &= ~(1 << USBS0);
			}
			if (n_stop_bits == 2)
			{
				UCSR0C |= (1 << USBS0);
			}
			break;
		}
		case 1:
		{
			if (n_stop_bits == 1)
			{
				UCSR1C &= ~(1 << USBS1);
			}
			if (n_stop_bits == 2)
			{
				UCSR1C |= (1 << USBS1);
			}
			break;
		}
	}	
}

/**
 * \fn void avr_driver_uart_character_size_select(uint8_t n_uart, uint8_t n_characters)
 * \brief ������� ������������� ������ ������������� �����
 *
 * \param n_uart ����� UART
 * \param n_characters ����� ��� � �����
 *
 * UCSRnC - ������� �������� � ������� UART C
 * UCSZn0:2 - ���� ������� ������� ����� (�� 5 �� 9)
 */
void avr_driver_uart_character_size_select(uint8_t n_uart, uint8_t n_characters)
{
	switch (n_characters)
	{
		case 5:
		{
			if (n_uart == 0)
			{
				UCSR0C &= ~(1 << UCSZ00);
				UCSR0C &= ~(1 << UCSZ01);
				UCSR0B &= ~(1 << UCSZ02);
			}
			if (n_uart == 1)
			{
				UCSR1C &= ~(1 << UCSZ10);
				UCSR1C &= ~(1 << UCSZ11);
				UCSR1B &= ~(1 << UCSZ12);
			}
			break;
		}
		case 6:
		{
			if (n_uart == 0)
			{
				UCSR0C |=  (1 << UCSZ00);
				UCSR0C &= ~(1 << UCSZ01);
				UCSR0B &= ~(1 << UCSZ02);
			}
			if (n_uart == 1)
			{
				UCSR1C |=  (1 << UCSZ10);
				UCSR1C &= ~(1 << UCSZ11);
				UCSR1B &= ~(1 << UCSZ12);
			}
			break;
		}
		case 7:
		{
			if (n_uart == 0)
			{
				UCSR0C &= ~(1 << UCSZ00);
				UCSR0C |=  (1 << UCSZ01);
				UCSR0B &= ~(1 << UCSZ02);
			}
			if (n_uart == 1)
			{
				UCSR1C &= ~(1 << UCSZ10);
				UCSR1C |=  (1 << UCSZ11);
				UCSR1B &= ~(1 << UCSZ12);
			}
			break;
		}
		case 8:
		{
			if (n_uart == 0)
			{
				UCSR0C |=  (1 << UCSZ00);
				UCSR0C |=  (1 << UCSZ01);
				UCSR0B &= ~(1 << UCSZ02);
			}
			if (n_uart == 1)
			{
				UCSR1C |=  (1 << UCSZ10);
				UCSR1C |=  (1 << UCSZ11);
				UCSR1B &= ~(1 << UCSZ12);
			}
			break;
		}
		case 9:
		{
			if (n_uart == 0)
			{
				UCSR0C |=  (1 << UCSZ00);
				UCSR0C |=  (1 << UCSZ01);
				UCSR0B |=  (1 << UCSZ02);
			}
			if (n_uart == 1)
			{
				UCSR1C |=  (1 << UCSZ10);
				UCSR1C |=  (1 << UCSZ11);
				UCSR1B |=  (1 << UCSZ12);
			}
			break;
		}
	}	
}

/**
 * \fn void avr_driver_uart_clock_polarity_select(uint8_t n_uart, uint8_t clock_polarity)
 * \brief ������� ������������� ��������� ����� ������� � ��������� � ���������� ������
 *
 * \param n_uart ����� UART
 * \param clock_polarity ��������� ��������� ����� ������� � ��������� � ���������� ������
 *
 * UCSRnC - ������� �������� � ������� UART C
 * UCPOLn - ��� ������� ��������� ����� ������� � ��������� � ���������� ������
 *
 *   UCPOLn | Transmitted Data Changed | Receiver Data Changed
 * -------------------------------------------------------------------------------------
 * 0		| Rising XCKn Edge		   | Falling XCKn Edge
 * 1		| Falling XCKn Edge		   | Rising XCKn Edge
 */
void avr_driver_uart_clock_polarity_select(uint8_t n_uart, uint8_t clock_polarity)
{
	switch (n_uart)
	{
		case 0:
		{
			if (clock_polarity == 0)
			{
				UCSR0C &= ~(1 << UCPOL0);
			}
			if (clock_polarity == 1)
			{
				UCSR0C |= (1 << UCPOL0);
			}
			break;
		}
		case 1:
		{
			if (clock_polarity == 0)
			{
				UCSR1C &= ~(1 << UCPOL1);
			}
			if (clock_polarity == 1)
			{
				UCSR1C |= (1 << UCPOL1);
			}
			break;
		}
	}	
}

/**
 * \fn void avr_driver_uart_clock_polarity_select(uint8_t n_uart, uint8_t clock_polarity)
 * \brief ������� ������������� ��������� ��������
 *
 * \param n_uart ����� UART
 * \param parity ��������
 *
 * UCSRnC - ������� �������� � ������� UART C
 * UPMn0:2 - ���� ������� ��������
 */
void avr_driver_uart_parity_mode_select(uint8_t n_uart, uint8_t parity)
{
	switch(parity)
	{
		case AVR_DRIVER_UART_PARITY_DISABLED:
		{
			if (n_uart == 0)
			{
				UCSR0C &= ~(1 << UPM00);
				UCSR0C &= ~(1 << UPM01);
			}
			if (n_uart == 1)
			{
				UCSR1C &= ~(1 << UPM10);
				UCSR1C &= ~(1 << UPM11);
			}
			break;
		}
		case AVR_DRIVER_UART_PARITY_EVEN:
		{
			if (n_uart == 0)
			{
				UCSR0C &= ~(1 << UPM00);
				UCSR0C |=  (1 << UPM01);
			}
			if (n_uart == 1)
			{
				UCSR1C &= ~(1 << UPM10);
				UCSR1C |=  (1 << UPM11);
			}
			break;
		}
		case AVR_DRIVER_UART_PARITY_ODD:
		{
			if (n_uart == 0)
			{
				UCSR0C |=  (1 << UPM00);
				UCSR0C |=  (1 << UPM01);
			}
			if (n_uart == 1)
			{
				UCSR1C |=  (1 << UPM10);
				UCSR1C |=  (1 << UPM11);
			}
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_rx_complete_interrupt_enable(uint8_t n_uart)
 * \brief ������� ��������� ���������� �� ��������� ������ ���� �� ����� ��������� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * RXCIEn - ��� ��������� ���������� �� ��������� ������ ���� �� ����� ��������� UART
 */
void avr_driver_uart_rx_complete_interrupt_enable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B |= (1 << RXCIE0);
			break;
		}
		case 1:
		{
			UCSR1B |= (1 << RXCIE1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_rx_complete_interrupt_disable(uint8_t n_uart)
 * \brief ������� ��������� ���������� �� ��������� ������ ���� �� ����� ��������� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * RXCIEn - ��� ��������� ���������� �� ��������� ������ ���� �� ����� ��������� UART
 */
void avr_driver_uart_rx_complete_interrupt_disable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B &= ~(1 << RXCIE0);
			break;
		}
		case 1:
		{
			UCSR1B &= ~(1 << RXCIE1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_tx_complete_interrupt_enable(uint8_t n_uart)
 * \brief ������� ��������� ���������� �� ���������� �������� ����������� �� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * TXCIEn - ��� ��������� ���������� �� ���������� �������� ����������� �� UART
 */
void avr_driver_uart_tx_complete_interrupt_enable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B |= (1 << TXCIE0);
			break;
		}
		case 1:
		{
			UCSR1B |= (1 << TXCIE1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_tx_complete_interrupt_disable(uint8_t n_uart)
 * \brief ������� ��������� ���������� �� ���������� �������� ����������� �� UART
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * TXCIEn - ��� ��������� ���������� �� ���������� �������� ����������� �� UART
 */
void avr_driver_uart_tx_complete_interrupt_disable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B &= ~(1 << TXCIE0);
			break;
		}
		case 1:
		{
			UCSR1B &= ~(1 << TXCIE1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_tx_complete_interrupt_enable(uint8_t n_uart)
 * \brief ������� ��������� ���������� �� ����������� ������
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * UDRIEn - ��� ��������� ���������� �� ����������� ������
 */
void avr_driver_uart_data_register_empty_interrupt_enable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B |= (1 << UDRIE0);
			break;
		}
		case 1:
		{
			UCSR1B |= (1 << UDRIE1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_data_register_empty_interrupt_disable(uint8_t n_uart)
 * \brief ������� ��������� ���������� �� ����������� ������
 *
 * \param n_uart ����� UART
 *
 * UCSRnB - ������� �������� � ������� UART B
 * UDRIEn - ��� ��������� ���������� �� ����������� ������
 */
void avr_driver_uart_data_register_empty_interrupt_disable(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0B &= ~(1 << UDRIE0);
			break;
		}
		case 1:
		{
			UCSR1B &= ~(1 << UDRIE1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_multiprocessor_mode_off(uint8_t n_uart)
 * \brief ������� ��������� ������������������ ����� UART
 *
 * \param n_uart ����� UART
 *
 * � ������������������ ������ ���������� �������������� �������, ������� ��������� �������� ������ �� ���������� �������� ���������� � ������������� �� ������������
 * UCSRnA - ������� �������� � ������� UART A
 * MPCMn - ��� ��������� ������������������� ������ UART
 */
void avr_driver_uart_multiprocessor_mode_off(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0A &= ~(1 << MPCM0);
			break;
		}
		case 1:
		{
			UCSR1A &= ~(1 << MPCM1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_multiprocessor_mode_on(uint8_t n_uart)
 * \brief ������� �������� ������������������ ����� UART
 *
 * \param n_uart ����� UART
 *
 * � ������������������ ������ ���������� �������������� �������, ������� ��������� �������� ������ �� ���������� �������� ���������� � ������������� �� ������������
 * UCSRnA - ������� �������� � ������� UART A
 * MPCMn - ��� ��������� ������������������� ������ UART
 */
void avr_driver_uart_multiprocessor_mode_on(uint8_t n_uart)
{
	switch (n_uart)
	{
		case 0:
		{
			UCSR0A |= (1 << MPCM0);
			break;
		}
		case 1:
		{
			UCSR1A |= (1 << MPCM1);
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_init(uint8_t n_uart, uint32_t f_cpu, uint8_t speed_mode, uint32_t baudrate, uint8_t op_mode, uint8_t n_stop_bits, uint8_t n_characters, uint8_t clock_polarity, uint8_t parity, uint8_t interrupts_mode)
 * \brief ������� ������������� ���������� UART
 *
 * \param n_uart ����� UART
 * \param f_cpu ������� ������ �����������
 * \param speed_mode ���������/������� ��������
 * \param baudrate ��������� �������� �������� ������
 * \param op_mode ����� ������ (����������/�����������)
 * \param n_stop_bits ����� ����-���
 * \param n_characters ����� ��� � �����
 * \param clock_polarity ��������� ��������� ����� ������� � ��������� � ���������� ������
 * \param parity ��������
 * \param interrupts_mode ���������/���������� ���� ���������� �� UART
 */
void avr_driver_uart_init(uint8_t n_uart, uint32_t f_cpu, uint8_t speed_mode, uint32_t baudrate, uint8_t op_mode, uint8_t n_stop_bits, uint8_t n_characters, uint8_t clock_polarity, uint8_t parity, uint8_t interrupts_mode)
{
	if (speed_mode == AVR_DRIVER_UART_SINGLE_SPEED)
	{
		avr_driver_uart_set_single_speed(n_uart);
	}
	if (speed_mode == AVR_DRIVER_UART_DOUBLE_SPEED)
	{
		avr_driver_uart_set_double_speed(n_uart);
	}
	if (op_mode == AVR_DRIVER_UART_SYNC_OPERATION_MODE) //� ���������� ������ ��� �� ������������ � ��� ����� �������� (�. 25.11.2)
	{
		avr_driver_uart_set_single_speed(n_uart);
	}
	avr_driver_uart_multiprocessor_mode_off(n_uart);
	avr_driver_uart_set_baudrate(n_uart, baudrate, f_cpu);
	avr_driver_uart_transmitter_enable(n_uart);
	avr_driver_uart_receiver_enable(n_uart);
	avr_driver_uart_operation_mode_select(n_uart, op_mode);
	avr_driver_uart_stop_bit_select(n_uart, n_stop_bits);
	avr_driver_uart_character_size_select(n_uart, n_characters);
	avr_driver_uart_parity_mode_select(n_uart, parity);
	avr_driver_uart_clock_polarity_select(n_uart, clock_polarity);
	if (interrupts_mode == AVR_DRIVER_UART_INTERRUPTS_ON)
	{
		avr_driver_uart_rx_complete_interrupt_enable(n_uart);
		avr_driver_uart_tx_complete_interrupt_enable(n_uart);
		avr_driver_uart_data_register_empty_interrupt_enable(n_uart);

	}
	if (interrupts_mode == AVR_DRIVER_UART_INTERRUPTS_OFF)
	{
		avr_driver_uart_rx_complete_interrupt_disable(n_uart);
		avr_driver_uart_tx_complete_interrupt_disable(n_uart);
		avr_driver_uart_data_register_empty_interrupt_disable(n_uart);		
	}
}

/**
 * \fn void avr_driver_uart_transmitt(uint8_t n_uart, uint8_t data_to_trasmitt)
 * \brief ������� �������� ��������� ������ �� UART
 *
 * \param n_uart ����� UART
 * \param data_to_trasmitt ������ ��� ��������
 */
void avr_driver_uart_transmitt(uint8_t n_uart, uint8_t data_to_trasmitt)
{
	switch (n_uart)
	{
		case 0:
		{
			while (!(UCSR0A & (1 << UDRE0)));
			UDR0 = data_to_trasmitt;
			break;
		}
		case 1:
		{
			while (!(UCSR1A & (1 << UDRE1)));
			UDR1 = data_to_trasmitt;
			break;
		}
	}
}

/**
 * \fn void avr_driver_uart_transmitt_9bits(uint8_t n_uart, uint16_t data_to_trasmitt)
 * \brief ������� �������� ��������� ������ �� UART ��� ������� ����� � 9 ���
 *
 * \param n_uart ����� UART
 * \param data_to_trasmitt ������ ��� ��������
 */
void avr_driver_uart_transmitt_9bits(uint8_t n_uart, uint16_t data_to_trasmitt)
{
	switch (n_uart)
	{
		case 0:
		{
			while (!(UCSR0A & (1 << UDRE0)));
			UCSR0B &= ~(1 << TXB80);
			if (data_to_trasmitt & 0x0100)
			{
				UCSR0B |= (1 << TXB80);
			}
			UDR0 = (uint8_t)(data_to_trasmitt & 0x00FF);
			break;
		}
		case 1:
		{
			while (!(UCSR1A & (1 << UDRE1)));
			UCSR1B &= ~(1 << TXB81);
			if (data_to_trasmitt & 0x0100)
			{
				UCSR1B |= (1 << TXB81);
			}
			UDR1 = (uint8_t)(data_to_trasmitt & 0x00FF);
			break;
		}
	}	
}

/**
 * \fn uint8_t avr_driver_uart_receive(uint8_t n_uart)
 * \brief ������� ������ ��������� ������ �� UART
 *
 * \param n_uart ����� UART
 */
uint8_t avr_driver_uart_receive(uint8_t n_uart)
{
	uint8_t result = 0;
	switch (n_uart)
	{
		case 0:
		{
			while (!(UCSR0A & (1 << RXC0)));
			result = UDR0; 
			break;
		}
		case 1:
		{
			while (!(UCSR1A & (1 << RXC1)));
			result = UDR1;
			break;
		}
	}
	return result;
}

/**
 * \fn uint8_t avr_driver_uart_receive(uint8_t n_uart)
 * \brief ������� ������ ��������� ������ �� UART ��� ������� ����� � 9 ���
 *
 * \param n_uart ����� UART
 */
uint16_t avr_driver_uart_receive_9bit(uint8_t n_uart)
{
	uint8_t result_low = 0;
	uint8_t result_high = 0;
	uint16_t result = 0;
	switch (n_uart)
	{
		case 0:
		{
			while (!(UCSR0A & (1 << RXC0)));
			result_high = UCSR0B;
			result_low = UDR0;
			result_high = (result_high >> 1) & 0x01;
			result = ((result_high << 8) | result_low);
			break;
		}
		case 1:
		{
			while (!(UCSR1A & (1 << RXC1)));
			result_high = UCSR1B;
			result_low = UDR1;
			result_high = (result_high >> 1) & 0x01;
			result = ((result_high << 8) | result_low);
			break;
		}
	}
	return result;
}

/**
 * \fn uint8_t avr_driver_uart_check_frame_error(uint8_t n_uart)
 * \brief ������� �������� ������� ������ �����
 *
 * \param n_uart ����� UART
 */
uint8_t avr_driver_uart_check_frame_error(uint8_t n_uart)
{
	uint8_t result = 0;
	switch (n_uart)
	{
		case 0:
		{
			if (UCSR0A & (1 << FE0))
			{
				result = 1;
			}
			break;
		}
		case 1:
		{
			if (UCSR1A & (1 << FE1))
			{
				result = 1;
			}
			break;
		}
	}
	return result;	
}

/**
 * \fn uint8_t avr_driver_uart_check_data_overrun(uint8_t n_uart)
 * \brief ������� �������� ������� ������ ������������ ������
 *
 * \param n_uart ����� UART
 */
uint8_t avr_driver_uart_check_data_overrun(uint8_t n_uart)
{
	uint8_t result = 0;
	switch (n_uart)
	{
		case 0:
		{
			if (UCSR0A & (1 << DOR0))
			{
				result = 1;
			}
			break;
		}
		case 1:
		{
			if (UCSR1A & (1 << DOR1))
			{
				result = 1;
			}
			break;
		}
	}
	return result;
}

/**
 * \fn uint8_t avr_driver_uart_check_parity_error(uint8_t n_uart)
 * \brief ������� �������� ������� ������ ��������
 *
 * \param n_uart ����� UART
 */
uint8_t avr_driver_uart_check_parity_error(uint8_t n_uart)
{
	uint8_t result = 0;
	switch (n_uart)
	{
		case 0:
		{
			if (UCSR0A & (1 << UPE0))
			{
				result = 1;
			}
			break;
		}
		case 1:
		{
			if (UCSR1A & (1 << UPE1))
			{
				result = 1;
			}
			break;
		}
	}
	return result;
}