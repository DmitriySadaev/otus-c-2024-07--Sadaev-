/*!
\file
\defgroup hal_lcd
\brief Заголовочный файл hal_lcd.h

*/

#ifndef HAL_LCD_H_
#define HAL_LCD_H_

#include <avr/io.h>
#include <util/delay.h>

#ifndef LCD_DATA_PORT
#define LCD_DATA_PORT PORTC
#define LCD_DATA_DDR DDRC
#endif /* LCD_DATA_PORT */

#ifndef LCD_COMMAND_PORT
#define LCD_COMMAND_PORT PORTG
#define LCD_COMMAND_DDR DDRG
#endif /* LCD_COMMAND_PORT */

#ifndef LCD_RS
#define LCD_RS PG1
#endif /* LCD_RS */

#ifndef LCD_RW
#define LCD_RW PG2
#endif /* LCD_RW */

#ifndef LCD_EN
#define LCD_EN PG3
#endif /* LCD_EN */

#ifndef LCD_DB4
#define LCD_DB4 PC3
#endif /* LCD_DB4 */

#ifndef LCD_DB5
#define LCD_DB5 PC4
#endif /* LCD_DB5 */

#ifndef LCD_DB6
#define LCD_DB6 PC5
#endif /* LCD_DB6 */

#ifndef LCD_DB7
#define LCD_DB7 PC6
#endif /* LCD_DB7 */

#ifndef LCD_DB7
#define LCD_DB7 PC6
#endif /* LCD_DB7 */

#ifndef LCD_STROB_DELAY_US
#define LCD_STROB_DELAY_US 1U
#endif /* LCD_STROB_DELAY_US */

#ifndef LCD_COMMAND_DELAY_US
#define LCD_COMMAND_DELAY_US 100U
#endif /* LCD_COMMAND_DELAY_US */

#ifndef LCD_IDLE_DELAY_US
#define LCD_IDLE_DELAY_US 400U
#endif /* LCD_IDLE_DELAY_US */

#ifndef LCD_INIT_DELAY_MS
#define LCD_INIT_DELAY_MS 50U
#endif /* LCD_INIT_DELAY_MS */

#ifndef OLED_INIT_DELAY_MS
#define OLED_INIT_DELAY_MS 500U
#endif /* OLED_INIT_DELAY_MS */

#ifndef CLEAR_DISPLAY_DELAY_MS
#define CLEAR_DISPLAY_DELAY_MS 7U
#endif /* CLEAR_DISPLAY_DELAY_MS */

#ifndef LCD_TYPE
#define LCD_TYPE WEH002004ALPP5N00100
#endif /* LCD_TYPE */

	#ifndef WEH002004ALPP5N00100
	#define WEH002004ALPP5N00100 1U
	#endif /* WEH002004ALPP5N00100 */
	
	#ifndef MT_20S4M_3YLG
	#define MT_20S4M_3YLG 2U
	#endif /* MT-20S4M-3YLG */

#ifndef CHARACTER_ADDRESS_INITIAL_POSITION
#define CHARACTER_ADDRESS_INITIAL_POSITION 0x80
#endif /* CHARACTER_ADDRESS_INITIAL_POSITION */

#ifndef FIRST_LINE_ADDRESS_INCREMENT
#define FIRST_LINE_ADDRESS_INCREMENT 0x40
#endif /* FIRST_LINE_ADDRESS_INCREMENT */

#ifndef SECOND_LINE_ADDRESS_INCREMENT
#define SECOND_LINE_ADDRESS_INCREMENT 0x14
#endif /* SECOND_LINE_ADDRESS_INCREMENT */

#ifndef THIRD_LINE_ADDRESS_INCREMENT
#define THIRD_LINE_ADDRESS_INCREMENT 0x54
#endif /* THIRD_LINE_ADDRESS_INCREMENT */

void lcd_com(uint8_t byte);
void lcd_dat(uint8_t byte);
void lcd_string(unsigned char command, char *string);
void lcd_string_direct(char *string);
void lcd_string_direct_rus(char *string);
void lcd_num_to_str(unsigned int value, unsigned char nDigit);
void lcd_int10(uint16_t value, unsigned char nDigit);
void lcd_int100(uint16_t value, unsigned char nDigit);
void lcd_hex (unsigned int value, unsigned char nDigit);
void lcd_init(void);
uint8_t lcd_addr (uint8_t x, uint8_t y);

#endif /* HAL_LCD_H_ */