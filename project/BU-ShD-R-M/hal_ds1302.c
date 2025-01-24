/*! 
  \file
  \defgroup		hal_ds1302
  \brief		Файл исходного кода программы hal_ds1302.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций микросхем часов реального времени.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  DS1302ZN

*/

#include "hal_ds1302.h"

void ds1302_init_ddr(void)
{
	DS1302_DDR |= (1<<DS1302_SCLK);
	DS1302_DDR |= (1<<DS1302_IO);
	DS1302_DDR |= (1<<DS1302_RST);
}

void ds1302_set_mode_write(void)
{
	DS1302_DDR |= (1<<DS1302_IO);
}

void ds1302_set_mode_read(void)
{
	DS1302_DDR &= ~(1<<DS1302_IO);
}

void ds1302_chip_enable(void)
{
	DS1302_PORT |= (1<<DS1302_RST);
}

void ds1302_chip_disable(void)
{
	DS1302_PORT &= ~(1<<DS1302_RST);
}

void ds1302_init(void)
{
	ds1302_init_ddr();
	ds1302_set_mode_read();
	ds1302_chip_disable();
	_delay_us(DS1302_INIT_DELAY_US);
}

void ds1302_set_output(void)
{
	DS1302_PORT |= (1<<DS1302_IO);
}

void ds1302_reset_output(void)
{
	DS1302_PORT &= ~(1<<DS1302_IO);
}

void ds1302_strob(void)
{
	DS1302_PORT |= (1<<DS1302_SCLK);
	_delay_us(DS1302_STROB_DELAY_US);
	DS1302_PORT &= ~(1<<DS1302_SCLK);
	_delay_us(DS1302_STROB_DELAY_US);

}

void ds1302_write_byte(uint8_t byte_to_send)
{
	ds1302_set_mode_write();
	ds1302_chip_enable();
	ds1302_reset_output();
	for (uint8_t i = 0; i<=7; i++)
	{
		if (byte_to_send & 0x01)
		{
			ds1302_set_output();
		}
		else
		{
			ds1302_reset_output();
		}
		ds1302_strob();
		byte_to_send  = byte_to_send >> 1;
	}
	ds1302_chip_disable();
}

void ds1302_write_2_byte(uint8_t byte_to_send, uint8_t byte_to_send_2)
{
	ds1302_set_mode_write();
	ds1302_chip_enable();
	ds1302_reset_output();
	for (uint8_t i = 0; i<=7; i++)
	{
		if (byte_to_send & 0x01)
		{
			ds1302_set_output();
		}
		else
		{
			ds1302_reset_output();
		}
		ds1302_strob();	
		byte_to_send  = byte_to_send >> 1;
	}
	for (uint8_t i = 0; i<=7; i++)
	{
		if (byte_to_send_2 & 0x01)
		{
			ds1302_set_output();
		}
		else
		{
			ds1302_reset_output();
		}
		ds1302_strob();
		byte_to_send_2  = byte_to_send_2 >> 1;
	}
	ds1302_chip_disable();
}

uint8_t ds1302_read_byte(uint8_t command)
{
	uint8_t result = 0;
	uint8_t temp_byte = 0;
	
	ds1302_set_mode_write();
	ds1302_chip_enable();
	ds1302_reset_output();
	for (uint8_t i = 0; i<=7; i++)
	{
		if (command & 0x01)
		{
			ds1302_set_output();
		}
		else
		{
			ds1302_reset_output();
		}
		ds1302_strob();
		command  = command >> 1;
	}
	ds1302_reset_output();
	_delay_us(2);
	ds1302_set_mode_read();
	for (uint8_t i = 0; i<=7; i++)
	{
		if (DS1302_PORT_IN & (1<<DS1302_IO_PIN))
		{
			temp_byte = 1;	
		}
		else
		{
			temp_byte = 0;
		}
		ds1302_strob();
		temp_byte = temp_byte << 7;
		result = result >> 1;			
		result = result | temp_byte;
	}	
	ds1302_chip_disable();
	return result;
}

uint8_t normalize_ds1302_data_seconds_or_minutes(uint8_t byte_to_normalize)
{
	uint8_t result = 0;
	result = ((byte_to_normalize & 0x0F) + ((byte_to_normalize & 0x70)>>4)*10);
	return result;
}

uint8_t normalize_ds1302_data_hours(uint8_t byte_to_normalize)
{
	uint8_t result = 0;
	result = ((byte_to_normalize & 0x0F) + ((byte_to_normalize & 0x10)>>4)*10);
	return result;
}


void ds1302_comms(struct ds1302_data * time, uint8_t field, uint8_t write_byte, uint8_t read_or_write)
{
	uint8_t temp_byte = 0;

	if(read_or_write == DS1302_READ)
	{
		if(field == DS1302_DATA_FIELD_SECOND)
		{
			temp_byte = ds1302_read_byte(DS1302_REG_SEC_R);
			temp_byte = normalize_ds1302_data_seconds_or_minutes(temp_byte);
			time->second = temp_byte;
		}
		else if(field == DS1302_DATA_FIELD_MINUTE)
		{
			temp_byte = ds1302_read_byte(DS1302_REG_MIN_R);
			temp_byte = normalize_ds1302_data_seconds_or_minutes(temp_byte);
			time->minute = temp_byte;
		}
		else if(field == DS1302_DATA_FIELD_HOUR)
		{
			temp_byte = ds1302_read_byte(DS1302_REG_HR_R);
		
			if((temp_byte & 0x80) == DS1302_DATA_HOUR_FORMAT_H12)						// 12 формат
			{
				if((temp_byte & 0x20) == 1)
				{																	// PM  
					time->hour_format = DS1302_DATA_HOUR_FORMAT_H12_PM;
				}
				else
				{																	// AM
					time->hour_format = DS1302_DATA_HOUR_FORMAT_H12_AM;
				}
					temp_byte = normalize_ds1302_data_hours(temp_byte);
					time->hour = temp_byte;
			}
			else																	// 24 формат
			{
				time->hour_format = DS1302_DATA_HOUR_FORMAT_H24;
				time->hour = ((temp_byte & 0x0F) + ((temp_byte & 0x30)>>4)*10);
			}
		}
		else if(field == DS1302_DATA_FIELD_DAY)
		{
			temp_byte = ds1302_read_byte(DS1302_REG_DAY_R);
			time->day = (temp_byte & 0x07);
		}
		else if(field == DS1302_DATA_FIELD_DATE)
		{
			temp_byte = ds1302_read_byte(DS1302_REG_DATE_R);
			time->date = ((temp_byte & 0x0F) + ((temp_byte & 0x30)>>4)*10);
		}
		else if(field == DS1302_DATA_FIELD_MONTH)
		{
			temp_byte = ds1302_read_byte(DS1302_REG_MONTH_R);
			time->month = ((temp_byte & 0x0F) + ((temp_byte & 0x10)>>4)*10);
		}
		else if(field == DS1302_DATA_FIELD_YEAR)
		{
			temp_byte = ds1302_read_byte(DS1302_REG_YEAR_R);
			time->year = ((temp_byte & 0x0F) + ((temp_byte & 0xF0)>>4)*10);
		}
	}
	else if(read_or_write == DS1302_WRITE)
	{
		if(field == DS1302_DATA_FIELD_SECOND)
		{
			ds1302_write_2_byte(DS1302_REG_SEC_W, ((((write_byte/10)<<4) & 0x70) | (write_byte%10)));
		}
		else if(field == DS1302_DATA_FIELD_MINUTE)
		{
			ds1302_write_2_byte(DS1302_REG_MIN_W, ((((write_byte/10)<<4) & 0x70)  | (write_byte%10)));
		}
		else if(field == DS1302_DATA_FIELD_HOUR)
		{
			if(time->hour_format == DS1302_DATA_HOUR_FORMAT_H24)
			ds1302_write_2_byte(DS1302_REG_HR_W, ((((write_byte/10)<<4) & 0x30) | (write_byte % 10)));
			else if(time->hour_format == DS1302_DATA_HOUR_FORMAT_H12_AM)
			ds1302_write_2_byte(DS1302_REG_HR_W, ((((write_byte/10)<<4) & 0x10)  | (write_byte%10)) | 0x80);
			else if(time->hour_format == DS1302_DATA_HOUR_FORMAT_H12_PM)
			ds1302_write_2_byte(DS1302_REG_HR_W, ((((write_byte/10)<<4) & 0x10)  | (write_byte%10)) | 0xA0);
		}
		else if(field == DS1302_DATA_FIELD_DAY)
		{
			ds1302_write_2_byte(DS1302_REG_DAY_W, write_byte & 0x03);
		}
		else if(field == DS1302_DATA_FIELD_DATE)
		{
			ds1302_write_2_byte(DS1302_REG_DATE_W, ((((write_byte/10)<<4) & 0x30)  | (write_byte%10)));
		}
		else if(field == DS1302_DATA_FIELD_MONTH)
		{
			ds1302_write_2_byte(DS1302_REG_MONTH_W, ((((write_byte/10)<<4) & 0x10) | (write_byte%10)));
		}
		else if(field == DS1302_DATA_FIELD_YEAR)
		{
			ds1302_write_2_byte(DS1302_REG_YEAR_W, ((((write_byte/10)<<4) & 0xF0) | (write_byte%10)));
		}
	}
}

void ds1302_update_time(struct ds1302_data * time, uint8_t field)	
{
	ds1302_comms(time, field, 0, DS1302_READ);
}

void ds1302_set_time(struct ds1302_data * time, uint8_t field, uint8_t write_byte)	
{																				
	ds1302_comms(time, field, write_byte, DS1302_WRITE);
}

void ds1302_update(struct ds1302_data * time)
{
	ds1302_update_time(time, DS1302_DATA_FIELD_SECOND);
	ds1302_update_time(time, DS1302_DATA_FIELD_MINUTE);
	ds1302_update_time(time, DS1302_DATA_FIELD_HOUR);
	ds1302_update_time(time, DS1302_DATA_FIELD_DAY);
	ds1302_update_time(time, DS1302_DATA_FIELD_DATE);
	ds1302_update_time(time, DS1302_DATA_FIELD_MONTH);
	ds1302_update_time(time, DS1302_DATA_FIELD_YEAR);
}