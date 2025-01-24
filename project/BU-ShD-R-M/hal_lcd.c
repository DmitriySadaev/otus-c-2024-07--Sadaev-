/*! 
  \file
  \defgroup		hal_lcd
  \brief		Файл исходного кода программы hal_lcd.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций LCD или OLED дисплея.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  WEH002004ALPP5N00100, MT-20S4M-3YLG
  - Supported mode:	 4-bit
*/

#include "hal_lcd.h"

/*! \brief Функция установки порта, к которому подлючен LCD-дисплей.
*
*	В регистре(-ах) направления данных (DDR) порта(-ов) микроконтроллера биты, соответсвующие
*	типу данных (RS - instruction code), направлению данных чтение/запись (R/W - Read/Write), 
*	сигналу разрешения работы (EN - chip enable signal), информационных бит (DB4..DB7 - data bit 
*	4...7) 	устанавливаются как выходы.
*
*	\param LCD_COMMAND_DDR		Регистр направления данных порта, к которому подключены управляющие выводы LCD-дисплея
*	\param LCD_DATA_DDR			Регистр направления данных порта, к которому подключены выводы информационных бит LCD-дисплея
*	\param LCD_EN				Выход микроконтроллера, к которому подключен вход EN LCD-дисплея
*	\param LCD_RS				Выход микроконтроллера, к которому подключен вход RS LCD-дисплея
*	\param LCD_RW				Выход микроконтроллера, к которому подключен вход R/W LCD-дисплея
*	\param LCD_DB4				Выход микроконтроллера, к которому подключен вход DB4 LCD-дисплея
*	\param LCD_DB5				Выход микроконтроллера, к которому подключен вход DB5 LCD-дисплея
*	\param LCD_DB6				Выход микроконтроллера, к которому подключен вход DB6 LCD-дисплея
*	\param LCD_DB7				Выход микроконтроллера, к которому подключен вход DB7 LCD-дисплея
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

/*! \brief Функция переключения выхода EN LCD дисплея
*
*	Функция переключет вывод микроконтроллера, к которому подключен вывод EN в высокое положение и после чего переключает обратно в низкое
*	EN = 1 (начало записи команды в LCD), EN = 0 (конец записи команды в LCD). Экспериментально определено, что для записи достаточно удержание 
*	вывода микроконтроллера в высоком состоянии 1 мкс.
*
*	\param LCD_COMMAND_PORT		Порт микроконтроллера, к которому подключены управляющие выводы LCD-дисплея
*	\param LCD_EN				Выход микроконтроллера, к которому подключен вход EN LCD-дисплея
*	\param LCD_STROB_DELAY_US	Время выдержки вывода EN в высоком состоянии
*	\param LCD_IDLE_DELAY_US	Время выдержки вывода EN в низком состоянии
*/
void lcd_strob (void)
{
	LCD_COMMAND_PORT |= (1 << LCD_EN);
	_delay_us(LCD_STROB_DELAY_US);
	LCD_COMMAND_PORT &= ~(1 << LCD_EN);
	_delay_us(LCD_IDLE_DELAY_US);
}

/*! \brief Функция установки в ноль выводов микроконтроллера, к которым подключены информационные выводы LCD-дисплея
*
*	Фнукция переключет выводы микроконтроллера, к которому подключен выводы DB4..DB7 в низкое состояние.
*
*	\param LCD_DATA_PORT		Порт микроконтроллера, к которому подключены выводы информационных бит LCD-дисплея
*	\param LCD_DB4				Выход микроконтроллера, к которому подключен вход DB4 LCD-дисплея
*	\param LCD_DB5				Выход микроконтроллера, к которому подключен вход DB5 LCD-дисплея
*	\param LCD_DB6				Выход микроконтроллера, к которому подключен вход DB6 LCD-дисплея
*	\param LCD_DB7				Выход микроконтроллера, к которому подключен вход DB7 LCD-дисплея
*/
void lcd_clear_data_pin (void)
{
	LCD_DATA_PORT &= ~(1 << LCD_DB4); 
	LCD_DATA_PORT &= ~(1 << LCD_DB5); 
	LCD_DATA_PORT &= ~(1 << LCD_DB6); 
	LCD_DATA_PORT &= ~(1 << LCD_DB7);
}

/*! \brief Функция распределения ниббла
*
*	Фнукция устанавливает выводы микроконтроллера, к которому подключен выводы DB4..DB7 в состояние,
*	закодированное в заданном ниббле.
*
*	\param nible				Ниббл (полубайт, тетрада или гексадецит), который требуется распределить по выводам информационных бит LCD-дисплея
*	\param LCD_DATA_PORT		Порт микроконтроллера, к которому подключены выводы информационных бит LCD-дисплея
*	\param LCD_DB4				Выход микроконтроллера, к которому подключен вход DB4 LCD-дисплея
*	\param LCD_DB5				Выход микроконтроллера, к которому подключен вход DB5 LCD-дисплея
*	\param LCD_DB6				Выход микроконтроллера, к которому подключен вход DB6 LCD-дисплея
*	\param LCD_DB7				Выход микроконтроллера, к которому подключен вход DB7 LCD-дисплея
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

/*! \brief Функция настройки вывода LCD-дисплея на прием данных
*
*	Функция переключает вывод микроконтроллера, к которому подключен вывод RS LCD-дисплея в высокое состояние
*	(RS = 1 запись данных).
*
*	\param LCD_COMMAND_PORT	Порт микроконтроллера, к которому подключены управляющие выводы LCD-дисплея 
*	\param LCD_RS			Выход микроконтроллера, к которому подключен вход RS LCD-дисплея
*/

void lcd_config_port_to_send_data(void)
{
	LCD_COMMAND_PORT|= (1 << LCD_RS); 
}

/*! \brief Функция настройки вывода LCD-дисплея на прием команд
*
*	Функция переключает вывод микроконтроллера, к которому подключен вывод RS LCD-дисплея в низкое состояние
*	(RS = 0 запись команд).
*
*	\param LCD_COMMAND_PORT	Порт микроконтроллера, к которому подключены управляющие выводы LCD-дисплея
*	\param LCD_RS			Выход микроконтроллера, к которому подключен вход RS LCD-дисплея
*/
void lcd_config_port_to_send_command(void)
{
	LCD_COMMAND_PORT &= ~(1 << LCD_RS);	
}

/*! \brief Функция записи команды в LCD-дисплей
*
*	Функция отправляет в LCD-дисплей заданный байт данных в  качестве команды.
*
*	\param byte				Байт, данных, который будет отправлен в LCD-дисплей в качестве команды
*/
void lcd_com(uint8_t byte)
{
	uint8_t nible=0;
	
	lcd_clear_data_pin();
	lcd_config_port_to_send_command();
	nible=((byte & 0xF0) >> 4); // старший полубайт
	distribute_nible(nible);
	lcd_strob();
	lcd_clear_data_pin();
	nible=(byte & 0x0F); // младший полубайт
	distribute_nible(nible);
	lcd_strob();
}

/*! \brief Функция записи команды "Очистка дисплея"
*
*	Функция производит полную очистку дисплея.
*
*	\param CLEAR_DISPLAY_DELAY_MS		Время ожидания после выполнения команды (в соответствии с даташитом время выполнения - не более 6,2 мс).
*/
void lcd_clear_display(void)
{
	lcd_com(0x01);
	_delay_ms(CLEAR_DISPLAY_DELAY_MS);
}

/*! \brief Функция записи команды "Возврат в  исходное положение"
*
*	Функция производит возрат сдвинутого дисплея в исходное положение
*/
void lcd_return_home(void)
{
	lcd_com(0x02);
}

/*! \brief Функция записи команды "Инкрементный режим включен"
*
*	Инкрементный режим предполагает, что каждая следующий записанный символ в дисплей будет записан правее на 1 позицию от предыдущего 
*/
void lcd_increment_mode_on(void)
{
	lcd_com(0x06);
}

/*! \brief Функция записи команды "Включить дисплей"
*
*	Функция включает LCD-дисплей.
*/
void lcd_display_on(void)
{
	lcd_com(0x0C);
}

/*! \brief Функция записи команды "Выбор русско-английского шрифта"
*
*	Функция включает режим вывода при помощи кодогенератора русско-ангдийского шрифта.
*/
void lcd_english_russian_character_font_table_select(void)
{
	lcd_com(0x2A);
}

/*! \brief Функция записи данных в LCD-дисплей
*
*	Функция отправляет в LCD-дисплей заданный байт данных в  качестве данных.
*
*	\param byte				Байт, данных, который будет отправлен в LCD-дисплей в качестве данных
*/
void lcd_dat(uint8_t byte)
{
	uint8_t nible=0;
	lcd_clear_data_pin();
	lcd_config_port_to_send_data();
	nible=((byte & 0xF0) >> 4); // старший полубайт
	distribute_nible(nible);
	lcd_strob();
	lcd_clear_data_pin();
	nible=(byte & 0x0F); // младший полубайт
	distribute_nible(nible);
	lcd_strob();
}

/*! \brief Функция вывода строковых данных на LCD-дисплей.
*
*	\param command			Команда для выполнения дисплеем до отправки данных
*	\param string			Указатель на строку, которую необходимо вывести на LCD-дисплей
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

/*! \brief Функция вывода строковых данных на LCD-дисплей без указания места.
*
*	\param string			Указатель на строку, которую необходимо вывести на LCD-дисплей
*/
void lcd_string_direct(char *string)
{
	while(*string != '\0')
	{
		lcd_dat(*string);
		string++;
	}
}

/*! \brief Функция вывода целой переменной на LCD-дисплей.
*
*	\param value			Переменная, которую требуется вывести
*	\param nDigit			Количество разрядов у переменной
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

/*! \brief Функция вывода целой переменной с одним знаком после запятой на LCD-дисплей.
*
*	\param value			Переменная, которую требуется вывести
*	\param nDigit			Количество разрядов у переменной
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

/*! \brief Функция вывода целой переменной с двумя знаками после запятой на LCD-дисплей.
*
*	\param value			Переменная, которую требуется вывести
*	\param nDigit			Количество разрядов у переменной
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

/*! \brief Функция вывода переменной в 16-тиричной системе исчисления на LCD-дисплей.
*
*	\param value			Переменная, которую требуется вывести
*	\param nDigit			Количество разрядов у переменной
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

/*! \brief Функция задежки на стабилизацию питания
*
*	Функция осуществляет задержку выполнения программы после включения питания для стабилизации питания LCD или OLED дисплея.
*	Величина задержки зависит от типа дисплея.
*
*	\param LCD_TYPE					Тип подключенного дисплея
*	\param OLED_INIT_DELAY_MS		Задержка включения для OLED дисплеев
*	\param LCD_INIT_DELAY_MS		Задержка включения для LCD дисплеев
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

/*! \brief Функция синхронизации при включении питания
*
*	Функция осуществляет оправку сообщения "0000" пять раз. Это требуется для устранения шума между старшим и младшим байтом при последующей отправки.
*
*/
void lcd_synchronize(void)
{
	for (uint8_t i=0;i<5;i++) 
	{
		lcd_strob();
	}
}

/*! \brief Функция инициализации дисплея
*
*/
void lcd_init(void)
{
	lcd_init_ddr();
	lcd_clear_data_pin();
	lcd_wait_for_initialization();
	LCD_DATA_PORT |=(1<<LCD_DB4)|(1<<LCD_DB5);  // 8 бит
	lcd_synchronize();
	LCD_DATA_PORT &=~(1<<LCD_DB4);         // 4 бит
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

/*! \brief Функция считвания адреса памяти заданной ячейки памяти дисплея 
*
*	Функция выдаёт адрес ячейки в памяти дисплея по её координатам
*
*	\param x	Номер символа в строке, 0...19.
*	\param y	Номер столбца, 0...3.
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

/*! \brief Функция вывода строковых данных на LCD-дисплей с поддержкой русского языка без указания места.
*
*	\param string			Указатель на строку, которую необходимо вывести на LCD-дисплей
*/
void lcd_string_direct_rus(char *string)
{
	char *text_pointer;
	text_pointer = string;
	while (*text_pointer != '\0')
	{
		switch (*text_pointer)
		{
			case 'А':
			{
				lcd_dat(0b01000001);
				text_pointer++;
				break;
			}
			case 'Б':
			{
				lcd_dat(0b10100000);
				text_pointer++;
				break;
			}
			case 'В':
			{
				lcd_dat(0b01000010);
				text_pointer++;
				break;
			}
			case 'Г':
			{
				lcd_dat(0b10100001);
				text_pointer++;
				break;
			}
			case 'Д':
			{
				lcd_dat(0b11100000);
				text_pointer++;
				break;
			}
			case 'Е':
			{
				lcd_dat(0b01000101);
				text_pointer++;
				break;
			}
			case 'Ё':
			{
				lcd_dat(0b10110101);
				text_pointer++;
				break;
			}
			case 'Ж':
			{
				lcd_dat(0b10100011);
				text_pointer++;
				break;
			}
			case 'З':
			{
				lcd_dat(0b10100100);
				text_pointer++;
				break;
			}
			case 'И':
			{
				lcd_dat(0b10100101);
				text_pointer++;
				break;
			}
			case 'Й':
			{
				lcd_dat(0b10100110);
				text_pointer++;
				break;
			}
			case 'К':
			{
				lcd_dat(0b01001011);
				text_pointer++;
				break;
			}
			case 'Л':
			{
				lcd_dat(0b10100111);
				text_pointer++;
				break;
			}
			case 'М':
			{
				lcd_dat(0b01001101);
				text_pointer++;
				break;
			}
			case 'Н':
			{
				lcd_dat(0b01001000);
				text_pointer++;
				break;
			}
			case 'О':
			{
				lcd_dat(0b01001111);
				text_pointer++;
				break;
			}
			case 'П':
			{
				lcd_dat(0b10101000);
				text_pointer++;
				break;
			}
			case 'Р':
			{
				lcd_dat(0b01010000);
				text_pointer++;
				break;
			}
			case 'С':
			{
				lcd_dat(0b01000011);
				text_pointer++;
				break;
			}
			case 'Т':
			{
				lcd_dat(0b01010100);
				text_pointer++;
				break;
			}
			case 'У':
			{
				lcd_dat(0b10101001);
				text_pointer++;
				break;
			}
			case 'Ф':
			{
				lcd_dat(0b10101010);
				text_pointer++;
				break;
			}
			case 'Х':
			{
				lcd_dat(0b01011000);
				text_pointer++;
				break;
			}
			case 'Ц':
			{
				lcd_dat(0b11100001);
				text_pointer++;
				break;
			}
			case 'Ч':
			{
				lcd_dat(0b10101011);
				text_pointer++;
				break;
			}
			case 'Ш':
			{
				lcd_dat(0b10101100);
				text_pointer++;
				break;
			}
			case 'Щ':
			{
				lcd_dat(0b11100010);
				text_pointer++;
				break;
			}
			case 'Ъ':
			{
				lcd_dat(0b10101101);
				text_pointer++;
				break;
			}
			case 'Ы':
			{
				lcd_dat(0b10101110);
				text_pointer++;
				break;
			}
			case 'Ь':
			{
				lcd_dat(0b01100010);
				text_pointer++;
				break;
			}
			case 'Э':
			{
				lcd_dat(0b10101111);
				text_pointer++;
				break;
			}
			case 'Ю':
			{
				lcd_dat(0b10110000);
				text_pointer++;
				break;
			}
			case 'Я':
			{
				lcd_dat(0b10110001);
				text_pointer++;
				break;
			}
			case 'а':
			{
				lcd_dat(0b01100001);
				text_pointer++;
				break;
			}
			case 'б':
			{
				lcd_dat(0b10110010);
				text_pointer++;
				break;
			}
			case 'в':
			{
				lcd_dat(0b10110011);
				text_pointer++;
				break;
			}
			case 'г':
			{
				lcd_dat(0b10110100);
				text_pointer++;
				break;
			}
			case 'д':
			{
				lcd_dat(0b11100011);
				text_pointer++;
				break;
			}
			case 'е':
			{
				lcd_dat(0b01100101);
				text_pointer++;
				break;
			}
			case 'ё':
			{
				lcd_dat(0b10110101);
				text_pointer++;
				break;
			}
			case 'ж':
			{
				lcd_dat(0b10110110);
				text_pointer++;
				break;
			}
			case 'з':
			{
				lcd_dat(0b10110111);
				text_pointer++;
				break;
			}
			case 'и':
			{
				lcd_dat(0b10111000);
				text_pointer++;
				break;
			}
			case 'й':
			{
				lcd_dat(0b10111001);
				text_pointer++;
				break;
			}
			case 'к':
			{
				lcd_dat(0b10111010);
				text_pointer++;
				break;
			}
			case 'л':
			{
				lcd_dat(0b10111011);
				text_pointer++;
				break;
			}
			case 'м':
			{
				lcd_dat(0b10111100);
				text_pointer++;
				break;
			}
			case 'н':
			{
				lcd_dat(0b10111101);
				text_pointer++;
				break;
			}
			case 'о':
			{
				lcd_dat(0b01101111);
				text_pointer++;
				break;
			}
			case 'п':
			{
				lcd_dat(0b10111110);
				text_pointer++;
				break;
			}
			case 'р':
			{
				lcd_dat(0b01110000);
				text_pointer++;
				break;
			}
			case 'с':
			{
				lcd_dat(0b01100011);
				text_pointer++;
				break;
			}
			case 'т':
			{
				lcd_dat(0b10111111);
				text_pointer++;
				break;
			}
			case 'у':
			{
				lcd_dat(0b01111001);
				text_pointer++;
				break;
			}
			case 'ф':
			{
				lcd_dat(0b11100100);
				text_pointer++;
				break;
			}
			case 'х':
			{
				lcd_dat(0b01111000);
				text_pointer++;
				break;
			}
			case 'ц':
			{
				lcd_dat(0b11100101);
				text_pointer++;
				break;
			}
			case 'ч':
			{
				lcd_dat(0b11000000);
				text_pointer++;
				break;
			}
			case 'ш':
			{
				lcd_dat(0b11000001);
				text_pointer++;
				break;
			}
			case 'щ':
			{
				lcd_dat(0b11100110);
				text_pointer++;
				break;
			}
			case 'ъ':
			{
				lcd_dat(0b11000010);
				text_pointer++;
				break;
			}
			case 'ы':
			{
				lcd_dat(0b11000011);
				text_pointer++;
				break;
			}
			case 'ь':
			{
				lcd_dat(0b11000100);
				text_pointer++;
				break;
			}
			case 'э':
			{
				lcd_dat(0b11000101);
				text_pointer++;
				break;
			}
			case 'ю':
			{
				lcd_dat(0b11000110);
				text_pointer++;
				break;
			}
			case 'я':
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