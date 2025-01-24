<<<<<<< HEAD
/*! 
  \file
  \defgroup		hal_sn74als165d
  \brief		Файл исходного кода программы hal_sn74als165d.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций сдвигового регистра с параллельной  загрузкой и последовательным выходом.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  SN74ALS165D
*/

#include "hal_sn74als165d.h"

void sn74als165d_init_ddr(void)
{
	SN74ALS165D_DDR |= (1<<SN74ALS165D_CLK);
	SN74ALS165D_DDR |= (1<<SN74ALS165D_SH_LD);
	SN74ALS165D_DDR &= ~(1<<SN74ALS165D_SER);
}

void sn74als165d_input_to_hi_z(void)
{
	SN74ALS165D_PORT &= ~(1<<SN74ALS165D_SER);
}

void sn74als165d_set_mode_parallel_load(void)
{
	SN74ALS165D_PORT &= ~(1<<SN74ALS165D_SH_LD);
}

void sn74als165d_set_mode_shift_load(void)
{
	SN74ALS165D_PORT |= (1<<SN74ALS165D_SH_LD);
}

void sn74als165d_init(void)
{
	sn74als165d_init_ddr();
	sn74als165d_input_to_hi_z();
	sn74als165d_set_mode_parallel_load();
}

void sn74als165d_strob_high(void)
{
	SN74ALS165D_PORT |= (1<<SN74ALS165D_CLK);
}

void sn74als165d_strob_low(void)
{
	_delay_us(SN74ALS165D_STROB_DELAY_US);
	SN74ALS165D_PORT &= ~(1<<SN74ALS165D_CLK);
	_delay_us(SN74ALS165D_STROB_DELAY_US);
}

void sn74als165d_read_serial_input(uint8_t * sn74als165d_read_array)
{
	if (!(SN74ALS165D_PORT_IN & (1<<SN74ALS165D_SER)))
	{
		*(uint8_t*)(sn74als165d_read_array+(8*SN74ALS165D_IN_SERIES_CONNECTED)) = 1;
	}
	else
	{
		*(uint8_t*)(sn74als165d_read_array+(8*SN74ALS165D_IN_SERIES_CONNECTED)) = 0;
	}
}

void sn74als165d_read_parallel_input(uint8_t * sn74als165d_read_array)
{
	for (uint8_t i = 0; i <= (8*SN74ALS165D_IN_SERIES_CONNECTED-1); i++)
	{
		sn74als165d_strob_high();
		if (SN74ALS165D_PORT_IN & (1<<SN74ALS165D_SER))
		{
			*(uint8_t*)(sn74als165d_read_array+i) = 0;
		}
		else
		{
			*(uint8_t*)(sn74als165d_read_array+i) = 1;
		}
		sn74als165d_strob_low();
	}
}

void sn74als165d_read(uint8_t * sn74als165d_read_array)
{
	sn74als165d_set_mode_shift_load();
	sn74als165d_read_serial_input(sn74als165d_read_array);
	sn74als165d_read_parallel_input(sn74als165d_read_array);
	sn74als165d_set_mode_parallel_load();
}
=======
/*! 
  \file
  \defgroup		hal_sn74als165d
  \brief		Файл исходного кода программы hal_sn74als165d.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций сдвигового регистра с параллельной  загрузкой и последовательным выходом.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  SN74ALS165D
*/

#include "hal_sn74als165d.h"

void sn74als165d_init_ddr(void)
{
	SN74ALS165D_DDR |= (1<<SN74ALS165D_CLK);
	SN74ALS165D_DDR |= (1<<SN74ALS165D_SH_LD);
	SN74ALS165D_DDR &= ~(1<<SN74ALS165D_SER);
}

void sn74als165d_input_to_hi_z(void)
{
	SN74ALS165D_PORT &= ~(1<<SN74ALS165D_SER);
}

void sn74als165d_set_mode_parallel_load(void)
{
	SN74ALS165D_PORT &= ~(1<<SN74ALS165D_SH_LD);
}

void sn74als165d_set_mode_shift_load(void)
{
	SN74ALS165D_PORT |= (1<<SN74ALS165D_SH_LD);
}

void sn74als165d_init(void)
{
	sn74als165d_init_ddr();
	sn74als165d_input_to_hi_z();
	sn74als165d_set_mode_parallel_load();
}

void sn74als165d_strob_high(void)
{
	SN74ALS165D_PORT |= (1<<SN74ALS165D_CLK);
}

void sn74als165d_strob_low(void)
{
	_delay_us(SN74ALS165D_STROB_DELAY_US);
	SN74ALS165D_PORT &= ~(1<<SN74ALS165D_CLK);
	_delay_us(SN74ALS165D_STROB_DELAY_US);
}

void sn74als165d_read_serial_input(uint8_t * sn74als165d_read_array)
{
	if (!(SN74ALS165D_PORT_IN & (1<<SN74ALS165D_SER)))
	{
		*(uint8_t*)(sn74als165d_read_array+(8*SN74ALS165D_IN_SERIES_CONNECTED)) = 1;
	}
	else
	{
		*(uint8_t*)(sn74als165d_read_array+(8*SN74ALS165D_IN_SERIES_CONNECTED)) = 0;
	}
}

void sn74als165d_read_parallel_input(uint8_t * sn74als165d_read_array)
{
	for (uint8_t i = 0; i <= (8*SN74ALS165D_IN_SERIES_CONNECTED-1); i++)
	{
		sn74als165d_strob_high();
		if (SN74ALS165D_PORT_IN & (1<<SN74ALS165D_SER))
		{
			*(uint8_t*)(sn74als165d_read_array+i) = 0;
		}
		else
		{
			*(uint8_t*)(sn74als165d_read_array+i) = 1;
		}
		sn74als165d_strob_low();
	}
}

void sn74als165d_read(uint8_t * sn74als165d_read_array)
{
	sn74als165d_set_mode_shift_load();
	sn74als165d_read_serial_input(sn74als165d_read_array);
	sn74als165d_read_parallel_input(sn74als165d_read_array);
	sn74als165d_set_mode_parallel_load();
}
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
