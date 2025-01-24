/*!
\file
\defgroup hal_ds1302
\brief Заголовочный файл hal_ds1302.h

*/

#ifndef HAL_DS1302_H_
#define HAL_DS1302_H_

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#ifndef DS1302_PORT
#define DS1302_PORT PORTA
#define DS1302_PORT_IN PINA
#define DS1302_DDR DDRA
#endif /* DS1302_PORT */

#ifndef DS1302_SCLK
#define DS1302_SCLK PA7
#endif /* DS1302_SCLK */

#ifndef DS1302_IO
#define DS1302_IO PA6
#define DS1302_IO_PIN PINA6
#endif /* DS1302_IO */

#ifndef DS1302_RST
#define DS1302_RST PA5
#endif /* DS1302_RST */

#ifndef DS1302_INIT_DELAY_US
#define DS1302_INIT_DELAY_US 4U
#endif /* DS1302_INIT_DELAY_US */

#ifndef DS1302_STROB_DELAY_US
#define DS1302_STROB_DELAY_US 30U
#endif /* DS1302_STROB_DELAY_US */

#ifndef DS1302_REG_SEC_W
#define DS1302_REG_SEC_W 0x80
#endif /* DS1302_REG_SEC_W */

#ifndef DS1302_REG_SEC_R
#define DS1302_REG_SEC_R 0x81
#endif /* DS1302_REG_SEC_R */

#ifndef DS1302_REG_MIN_W
#define DS1302_REG_MIN_W 0x82
#endif /* DS1302_REG_MIN_W */

#ifndef DS1302_REG_MIN_R
#define DS1302_REG_MIN_R 0x83
#endif /* DS1302_REG_MIN_R */

#ifndef DS1302_REG_HR_W
#define DS1302_REG_HR_W 0x84
#endif /* DS1302_REG_HR_W */

#ifndef DS1302_REG_HR_R
#define DS1302_REG_HR_R 0x85
#endif /* DS1302_REG_HR_R */

#ifndef DS1302_REG_DATE_W
#define DS1302_REG_DATE_W 0x86
#endif /* DS1302_REG_DATE_W */

#ifndef DS1302_REG_DATE_R
#define DS1302_REG_DATE_R 0x87
#endif /* DS1302_REG_DATE_R */

#ifndef DS1302_REG_MONTH_W
#define DS1302_REG_MONTH_W 0x88
#endif /* DS1302_REG_MONTH_W */

#ifndef DS1302_REG_MONTH_R
#define DS1302_REG_MONTH_R 0x89
#endif /* DS1302_REG_MONTH_R */

#ifndef DS1302_REG_DAY_W
#define DS1302_REG_DAY_W 0x8A
#endif /* DS1302_REG_DAY_W */

#ifndef DS1302_REG_DAY_R
#define DS1302_REG_DAY_R 0x8B
#endif /* DS1302_REG_DAY_R */

#ifndef DS1302_REG_YEAR_W
#define DS1302_REG_YEAR_W 0x8C
#endif /* DS1302_REG_YEAR_W */

#ifndef DS1302_REG_YEAR_R
#define DS1302_REG_YEAR_R 0x8D
#endif /* DS1302_REG_YEAR_R */

#ifndef DS1302_REG_CONTROL_W
#define DS1302_REG_CONTROL_W 0x8E
#endif /* DS1302_REG_CONTROL_W */

#ifndef DS1302_REG_CONTROL_R
#define DS1302_REG_CONTROL_R 0x8F
#endif /* DS1302_REG_CONTROL_R */

#ifndef DS1302_REG_TRICKLE_CHARGER_W
#define DS1302_REG_TRICKLE_CHARGER_W 0x90
#endif /* DS1302_REG_TRICKLE_CHARGER_W */

#ifndef DS1302_REG_TRICKLE_CHARGER_R
#define DS1302_REG_TRICKLE_CHARGER_R 0x91
#endif /* DS1302_REG_TRICKLE_CHARGER_R */

#ifndef DS1302_REG_CLOCK_BURST_W
#define DS1302_REG_CLOCK_BURST_W 0xBE
#endif /* DS1302_REG_CLOCK_BURST_W */

#ifndef DS1302_REG_CLOCK_BURST_R
#define DS1302_REG_CLOCK_BURST_R 0xBF
#endif /* DS1302_REG_CLOCK_BURST_R */

#ifndef DS1302_READ
#define DS1302_READ 0U
#endif /* DS1302_READ */

#ifndef DS1302_WRITE
#define DS1302_WRITE 1U
#endif /* DS1302_WRITE */

#ifndef DS1302_DATA_FIELD_SECOND
#define DS1302_DATA_FIELD_SECOND 0U
#endif /* DS1302_DATA_FIELD_SECOND */

#ifndef DS1302_DATA_FIELD_MINUTE
#define DS1302_DATA_FIELD_MINUTE 1U
#endif /* DS1302_DATA_FIELD_MINUTE */

#ifndef DS1302_DATA_FIELD_HOUR
#define DS1302_DATA_FIELD_HOUR 2U
#endif /* DS1302_DATA_FIELD_HOUR */

#ifndef DS1302_DATA_FIELD_DATE
#define DS1302_DATA_FIELD_DATE 3U
#endif /* DS1302_DATA_FIELD_DATE */

#ifndef DS1302_DATA_FIELD_MONTH
#define DS1302_DATA_FIELD_MONTH 4U
#endif /* DS1302_DATA_FIELD_MONTH */

#ifndef DS1302_DATA_FIELD_DAY
#define DS1302_DATA_FIELD_DAY 5U
#endif /* DS1302_DATA_FIELD_DAY */

#ifndef DS1302_DATA_FIELD_YEAR
#define DS1302_DATA_FIELD_YEAR 6U
#endif /* DS1302_DATA_FIELD_YEAR */

#ifndef DS1302_DATA_FIELD_CONTROL
#define DS1302_DATA_FIELD_CONTROL 7U
#endif /* DS1302_DATA_FIELD_CONTROL */

#ifndef DS1302_DATA_FIELD_TRICKLE_CHARGER
#define DS1302_DATA_FIELD_TRICKLE_CHARGER 8U
#endif /* DS1302_DATA_FIELD_TRICKLE_CHARGER */

#ifndef DS1302_DATA_FIELD_CLOCK_BURST
#define DS1302_DATA_FIELD_CLOCK_BURST 9U
#endif /* DS1302_DATA_FIELD_CLOCK_BURST */

#ifndef DS1302_DATA_HOUR_FORMAT_H12
#define DS1302_DATA_HOUR_FORMAT_H12 1U
#endif /* DS1302_DATA_HOUR_FORMAT_H12 */

#ifndef DS1302_DATA_HOUR_FORMAT_H24
#define DS1302_DATA_HOUR_FORMAT_H24 0U
#endif /* DS1302_DATA_HOUR_FORMAT_H24 */

#ifndef DS1302_DATA_HOUR_FORMAT_H12_AM
#define DS1302_DATA_HOUR_FORMAT_H12_AM 2U
#endif /* DS1302_DATA_HOUR_FORMAT_H12_AM */

#ifndef DS1302_DATA_HOUR_FORMAT_H12_PM
#define DS1302_DATA_HOUR_FORMAT_H12_PM 3U
#endif /* DS1302_DATA_HOUR_FORMAT_H12_PM */

struct ds1302_data
{
uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t date;
uint8_t month;
uint8_t day;
uint8_t year;
uint8_t control;
uint8_t trickle_charger;
uint8_t clock_burst;
uint8_t hour_format;
};

void ds1302_init(void);
void ds1302_update(struct ds1302_data * time);
void ds1302_set_time(struct ds1302_data * time, uint8_t field, uint8_t write_byte);

#endif /* HAL_DS1302_H_ */