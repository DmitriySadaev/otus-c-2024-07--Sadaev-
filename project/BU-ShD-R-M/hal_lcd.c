/*! 
  \file
  \defgroup		hal_lcd
  \brief		���� ��������� ���� ��������� hal_lcd.c
  \author		������ �.�.
 
  ���� ��������� ���� �������� � ���� �������� �������, ������������ � �������� ���������.
  �������� ��� ������������ �� ���� ���� ���������� ���������� LCD ��� OLED �������.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  WEH002004ALPP5N00100, MT-20S4M-3YLG
  - Supported mode:	 4-bit
*/

#include "hal_lcd.h"

/*! \brief ������� ��������� �����, � �������� �������� LCD-�������.
*
*	� ��������(-��) ����������� ������ (DDR) �����(-��) ���������������� ����, ��������������
*	���� ������ (RS - instruction code), ����������� ������ ������/������ (R/W - Read/Write), 
*	������� ���������� ������ (EN - chip enable signal), �������������� ��� (DB4..DB7 - data bit 
*	4...7) 	��������������� ��� ������.
*
*	\param LCD_COMMAND_DDR		������� ����������� ������ �����, � �������� ���������� ����������� ������ LCD-�������
*	\param LCD_DATA_DDR			������� ����������� ������ �����, � �������� ���������� ������ �������������� ��� LCD-�������
*	\param LCD_EN				����� ����������������, � �������� ��������� ���� EN LCD-�������
*	\param LCD_RS				����� ����������������, � �������� ��������� ���� RS LCD-�������
*	\param LCD_RW				����� ����������������, � �������� ��������� ���� R/W LCD-�������
*	\param LCD_DB4				����� ����������������, � �������� ��������� ���� DB4 LCD-�������
*	\param LCD_DB5				����� ����������������, � �������� ��������� ���� DB5 LCD-�������
*	\param LCD_DB6				����� ����������������, � �������� ��������� ���� DB6 LCD-�������
*	\param LCD_DB7				����� ����������������, � �������� ��������� ���� DB7 LCD-�������
*/
void lcd_init_ddr (void)
{
	LCD_COMMAND_DDR |= (1 << LCD_EN);
	LCD_COMMAND_DDR |= (1 << LCD_RS);
	LCD_COMMAND_DDR |= (1 << LCD_RW);
	LCD_DATA_DDR	|= (1 << LCD_DB4);
	LCD_DATA_DDR	|= (1 << LCD_DB5);
	LCD_DATA_DDR	|= (1 << LCD_DB6);
	LCD_DATA_DDR	|= (1 << LCD_DB7);
}

/*! \brief ������� ������������ ������ EN LCD �������
*
*	������� ���������� ����� ����������������, � �������� ��������� ����� EN � ������� ��������� � ����� ���� ����������� ������� � ������
*	EN = 1 (������ ������ ������� � LCD), EN = 0 (����� ������ ������� � LCD). ���������������� ����������, ��� ��� ������ ���������� ��������� 
*	������ ���������������� � ������� ��������� 1 ���.
*
*	\param LCD_COMMAND_PORT		���� ����������������, � �������� ���������� ����������� ������ LCD-�������
*	\param LCD_EN				����� ����������������, � �������� ��������� ���� EN LCD-�������
*	\param LCD_STROB_DELAY_US	����� �������� ������ EN � ������� ���������
*	\param LCD_IDLE_DELAY_US	����� �������� ������ EN � ������ ���������
*/
void lcd_strob (void)
{
	LCD_COMMAND_PORT |= (1 << LCD_EN);
	_delay_us(LCD_STROB_DELAY_US);
	LCD_COMMAND_PORT &= ~(1 << LCD_EN);
	_delay_us(LCD_IDLE_DELAY_US);
}

/*! \brief ������� ��������� � ���� ������� ����������������, � ������� ���������� �������������� ������ LCD-�������
*
*	������� ���������� ������ ����������������, � �������� ��������� ������ DB4..DB7 � ������ ���������.
*
*	\param LCD_DATA_PORT		���� ����������������, � �������� ���������� ������ �������������� ��� LCD-�������
*	\param LCD_DB4				����� ����������������, � �������� ��������� ���� DB4 LCD-�������
*	\param LCD_DB5				����� ����������������, � �������� ��������� ���� DB5 LCD-�������
*	\param LCD_DB6				����� ����������������, � �������� ��������� ���� DB6 LCD-�������
*	\param LCD_DB7				����� ����������������, � �������� ��������� ���� DB7 LCD-�������
*/
void lcd_clear_data_pin (void)
{
	LCD_DATA_PORT &= ~(1 << LCD_DB4); 
	LCD_DATA_PORT &= ~(1 << LCD_DB5); 
	LCD_DATA_PORT &= ~(1 << LCD_DB6); 
	LCD_DATA_PORT &= ~(1 << LCD_DB7);
}

/*! \brief ������� ������������� ������
*
*	������� ������������� ������ ����������������, � �������� ��������� ������ DB4..DB7 � ���������,
*	�������������� � �������� ������.
*
*	\param nible				����� (��������, ������� ��� ����������), ������� ��������� ������������ �� ������� �������������� ��� LCD-�������
*	\param LCD_DATA_PORT		���� ����������������, � �������� ���������� ������ �������������� ��� LCD-�������
*	\param LCD_DB4				����� ����������������, � �������� ��������� ���� DB4 LCD-�������
*	\param LCD_DB5				����� ����������������, � �������� ��������� ���� DB5 LCD-�������
*	\param LCD_DB6				����� ����������������, � �������� ��������� ���� DB6 LCD-�������
*	\param LCD_DB7				����� ����������������, � �������� ��������� ���� DB7 LCD-�������
*/
void distribute_nible(uint8_t nible)
{
	if ((nible & 1) == 1)
	{
		LCD_DATA_PORT |=(1<<LCD_DB4);
	}
	nible = nible >> 1;
	if ((nible & 1) == 1)
	{
		LCD_DATA_PORT |=(1<<LCD_DB5);
	}
	nible = nible >> 1;
	if ((nible & 1) == 1)
	{
		LCD_DATA_PORT |=(1<<LCD_DB6);
	}
	nible = nible >> 1;
	if ((nible & 1 ) == 1)
	{
		LCD_DATA_PORT |=(1<<LCD_DB7);
	}
}

/*! \brief ������� ��������� ������ LCD-������� �� ����� ������
*
*	������� ����������� ����� ����������������, � �������� ��������� ����� RS LCD-������� � ������� ���������
*	(RS = 1 ������ ������).
*
*	\param LCD_COMMAND_PORT	���� ����������������, � �������� ���������� ����������� ������ LCD-������� 
*	\param LCD_RS			����� ����������������, � �������� ��������� ���� RS LCD-�������
*/

void lcd_config_port_to_send_data(void)
{
	LCD_COMMAND_PORT|= (1 << LCD_RS); 
}

/*! \brief ������� ��������� ������ LCD-������� �� ����� ������
*
*	������� ����������� ����� ����������������, � �������� ��������� ����� RS LCD-������� � ������ ���������
*	(RS = 0 ������ ������).
*
*	\param LCD_COMMAND_PORT	���� ����������������, � �������� ���������� ����������� ������ LCD-�������
*	\param LCD_RS			����� ����������������, � �������� ��������� ���� RS LCD-�������
*/
void lcd_config_port_to_send_command(void)
{
	LCD_COMMAND_PORT &= ~(1 << LCD_RS);	
}

/*! \brief ������� ������ ������� � LCD-�������
*
*	������� ���������� � LCD-������� �������� ���� ������ �  �������� �������.
*
*	\param byte				����, ������, ������� ����� ��������� � LCD-������� � �������� �������
*/
void lcd_com(uint8_t byte)
{
	uint8_t nible=0;
	
	lcd_clear_data_pin();
	lcd_config_port_to_send_command();
	nible=((byte & 0xF0) >> 4); // ������� ��������
	distribute_nible(nible);
	lcd_strob();
	lcd_clear_data_pin();
	nible=(byte & 0x0F); // ������� ��������
	distribute_nible(nible);
	lcd_strob();
}

/*! \brief ������� ������ ������� "������� �������"
*
*	������� ���������� ������ ������� �������.
*
*	\param CLEAR_DISPLAY_DELAY_MS		����� �������� ����� ���������� ������� (� ������������ � ��������� ����� ���������� - �� ����� 6,2 ��).
*/
void lcd_clear_display(void)
{
	lcd_com(0x01);
	_delay_ms(CLEAR_DISPLAY_DELAY_MS);
}

/*! \brief ������� ������ ������� "������� �  �������� ���������"
*
*	������� ���������� ������ ���������� ������� � �������� ���������
*/
void lcd_return_home(void)
{
	lcd_com(0x02);
}

/*! \brief ������� ������ ������� "������������ ����� �������"
*
*	������������ ����� ������������, ��� ������ ��������� ���������� ������ � ������� ����� ������� ������ �� 1 ������� �� ����������� 
*/
void lcd_increment_mode_on(void)
{
	lcd_com(0x06);
}

/*! \brief ������� ������ ������� "�������� �������"
*
*	������� �������� LCD-�������.
*/
void lcd_display_on(void)
{
	lcd_com(0x0C);
}

/*! \brief ������� ������ ������� "����� ������-����������� ������"
*
*	������� �������� ����� ������ ��� ������ �������������� ������-����������� ������.
*/
void lcd_english_russian_character_font_table_select(void)
{
	lcd_com(0x2A);
}

/*! \brief ������� ������ ������ � LCD-�������
*
*	������� ���������� � LCD-������� �������� ���� ������ �  �������� ������.
*
*	\param byte				����, ������, ������� ����� ��������� � LCD-������� � �������� ������
*/
void lcd_dat(uint8_t byte)
{
	uint8_t nible=0;
	lcd_clear_data_pin();
	lcd_config_port_to_send_data();
	nible=((byte & 0xF0) >> 4); // ������� ��������
	distribute_nible(nible);
	lcd_strob();
	lcd_clear_data_pin();
	nible=(byte & 0x0F); // ������� ��������
	distribute_nible(nible);
	lcd_strob();
}

/*! \brief ������� ������ ��������� ������ �� LCD-�������.
*
*	\param command			������� ��� ���������� �������� �� �������� ������
*	\param string			��������� �� ������, ������� ���������� ������� �� LCD-�������
*/
void lcd_string(unsigned char command, char* string)
{
	//lcd_com(0x0C);
	_delay_us(LCD_COMMAND_DELAY_US);
	lcd_com(command);
	while(*string != '\0')
	{
		lcd_dat(*string);
		string++;
	}
}

/*! \brief ������� ������ ��������� ������ �� LCD-������� ��� �������� �����.
*
*	\param string			��������� �� ������, ������� ���������� ������� �� LCD-�������
*/
void lcd_string_direct(char *string)
{
	while(*string != '\0')
	{
		lcd_dat(*string);
		string++;
	}
}

/*! \brief ������� ������ ����� ���������� �� LCD-�������.
*
*	\param value			����������, ������� ��������� �������
*	\param nDigit			���������� �������� � ����������
*/
void lcd_num_to_str(unsigned int value, unsigned char nDigit)
{
	switch(nDigit)
	{
		case 6: lcd_dat(((value/100000)%10)+'0');
		case 5: lcd_dat(((value/10000)%10)+'0');
		case 4: lcd_dat(((value/1000)%10)+'0');
		case 3: lcd_dat(((value/100)%10)+'0');
		case 2: lcd_dat(((value/10)%10)+'0');
		case 1: lcd_dat((value%10)+'0');
	}
}

/*! \brief ������� ������ ����� ���������� � ����� ������ ����� ������� �� LCD-�������.
*
*	\param value			����������, ������� ��������� �������
*	\param nDigit			���������� �������� � ����������
*/
void lcd_int10(uint16_t value, unsigned char nDigit)
{	
	switch(nDigit)
	{
		case 7: lcd_dat(((value/100000)%10)+'0');
		case 6: lcd_dat(((value/10000)%10)+'0');
		case 5: lcd_dat(((value/1000)%10)+'0');
		case 4: lcd_dat(((value/100)%10)+'0');
		case 3: lcd_dat(((value/10)%10)+'0');
		case 2:	lcd_dat('.');
		case 1: lcd_dat((value%10)+'0');
	}
}

/*! \brief ������� ������ ����� ���������� � ����� ������� ����� ������� �� LCD-�������.
*
*	\param value			����������, ������� ��������� �������
*	\param nDigit			���������� �������� � ����������
*/
void lcd_int100(uint16_t value, unsigned char nDigit)
{	
	switch(nDigit)
	{
		case 7: lcd_dat(((value/100000)%10)+'0');
		case 6: lcd_dat(((value/10000)%10)+'0');
		case 5: lcd_dat(((value/1000)%10)+'0');
		case 4: lcd_dat(((value/100)%10)+'0');
		case 3:	lcd_dat('.');
		case 2: lcd_dat(((value/10)%10)+'0');
		case 1: lcd_dat((value%10)+'0');
	}
}

/*! \brief ������� ������ ���������� � 16-�������� ������� ���������� �� LCD-�������.
*
*	\param value			����������, ������� ��������� �������
*	\param nDigit			���������� �������� � ����������
*/
void lcd_hex (unsigned int value, unsigned char nDigit)
{
	switch(nDigit)
	{
		case 6: lcd_dat(((value/0x100000)%0x10)+'0');
		case 5: lcd_dat(((value/0x10000)%0x10)+'0');
		case 4: lcd_dat(((value/0x1000)%0x10)+'0');
		case 3: lcd_dat(((value/0x100)%0x10)+'0');
		case 2: lcd_dat(((value/0x10)%0x10)+'0');
		case 1: lcd_dat((value%0x10)+'0');
	}
}

/*! \brief ������� ������� �� ������������ �������
*
*	������� ������������ �������� ���������� ��������� ����� ��������� ������� ��� ������������ ������� LCD ��� OLED �������.
*	�������� �������� ������� �� ���� �������.
*
*	\param LCD_TYPE					��� ������������� �������
*	\param OLED_INIT_DELAY_MS		�������� ��������� ��� OLED ��������
*	\param LCD_INIT_DELAY_MS		�������� ��������� ��� LCD ��������
*/
void lcd_wait_for_initialization (void)
{
	switch (LCD_TYPE)
	{
		case WEH002004ALPP5N00100:
		{
			_delay_ms(OLED_INIT_DELAY_MS);
			break;
		}
		case MT_20S4M_3YLG:
		{
			_delay_ms(LCD_INIT_DELAY_MS);
			break;
		}
	}	
}

/*! \brief ������� ������������� ��� ��������� �������
*
*	������� ������������ ������� ��������� "0000" ���� ���. ��� ��������� ��� ���������� ���� ����� ������� � ������� ������ ��� ����������� ��������.
*
*/
void lcd_synchronize(void)
{
	for (uint8_t i=0;i<5;i++) 
	{
		lcd_strob();
	}
}

/*! \brief ������� ������������� �������
*
*/
void lcd_init(void)
{
	lcd_init_ddr();
	lcd_clear_data_pin();
	lcd_wait_for_initialization();
	LCD_DATA_PORT |=(1<<LCD_DB4)|(1<<LCD_DB5);  // 8 ���
	lcd_synchronize();
	LCD_DATA_PORT &=~(1<<LCD_DB4);         // 4 ���
	lcd_strob();
	lcd_strob();
	LCD_DATA_PORT &=~(1<<LCD_DB5); 
	LCD_COMMAND_PORT|=(1<<LCD_DB7);
	lcd_strob();
	lcd_clear_data_pin();
	lcd_strob();
	LCD_DATA_PORT |=(1<<LCD_DB7);
	lcd_strob();
	lcd_clear_data_pin();
	lcd_strob();
	LCD_DATA_PORT |=(1<<LCD_DB4);
	lcd_strob();
	lcd_clear_data_pin();
	lcd_strob();
	LCD_DATA_PORT |=(1<<LCD_DB5)|(1<<LCD_DB6);
	lcd_strob();
	lcd_clear_data_pin();
	lcd_display_on();
	lcd_english_russian_character_font_table_select();
	lcd_increment_mode_on();
	lcd_return_home();
	lcd_clear_display();
}

/*! \brief ������� ��������� ������ ������ �������� ������ ������ ������� 
*
*	������� ����� ����� ������ � ������ ������� �� � �����������
*
*	\param x	����� ������� � ������, 0...19.
*	\param y	����� �������, 0...3.
*/
uint8_t lcd_addr (uint8_t x, uint8_t y)
{
	uint8_t result = CHARACTER_ADDRESS_INITIAL_POSITION;
	
	if (x>19) return CHARACTER_ADDRESS_INITIAL_POSITION;
	if (y>3)  return CHARACTER_ADDRESS_INITIAL_POSITION;
	
	switch(y)
	{
		case 0: 
		{
			result += x;		
			break;
		}
		case 1: 
		{
			result += FIRST_LINE_ADDRESS_INCREMENT  + x;	
			break;
		}
		case 2: 
		{
			result += SECOND_LINE_ADDRESS_INCREMENT + x;	
			break;
		}
		case 3: 
		{
			result += THIRD_LINE_ADDRESS_INCREMENT  + x;	
			break;
		}
	}
	return result;
}

/*! \brief ������� ������ ��������� ������ �� LCD-������� � ���������� �������� ����� ��� �������� �����.
*
*	\param string			��������� �� ������, ������� ���������� ������� �� LCD-�������
*/
void lcd_string_direct_rus(char *string)
{
	char *text_pointer;
	text_pointer = string;
	while (*text_pointer != '\0')
	{
		switch (*text_pointer)
		{
			case '�':
			{
				lcd_dat(0b01000001);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10100000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01000010);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10100001);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11100000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01000101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10110101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10100011);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10100100);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10100101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10100110);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01001011);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10100111);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01001101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01001000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01001111);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10101000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01010000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01000011);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01010100);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10101001);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10101010);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01011000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11100001);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10101011);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10101100);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11100010);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10101101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10101110);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01100010);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10101111);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10110000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10110001);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01100001);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10110010);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10110011);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10110100);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11100011);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01100101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10110101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10110110);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10110111);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10111000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10111001);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10111010);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10111011);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10111100);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10111101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01101111);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10111110);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01110000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01100011);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b10111111);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01111001);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11100100);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b01111000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11100101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11000000);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11000001);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11100110);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11000010);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11000011);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11000100);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11000101);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11000110);
				text_pointer++;
				break;
			}
			case '�':
			{
				lcd_dat(0b11000111);
				text_pointer++;
				break;
			}
			default:
			{
				lcd_dat(*text_pointer);
				text_pointer++;
			}
		}
	}
}