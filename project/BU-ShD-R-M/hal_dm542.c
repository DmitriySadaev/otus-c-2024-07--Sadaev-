/*! 
  \file
  \defgroup		hal_dm542
  \brief		Файл исходного кода программы hal_dm542.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций драйвера шагового двигателя.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  DM542

*/

#include "hal_dm542.h"

void hal_dm542_init_struct(struct dm542_driver_data * dm542_driver, uint8_t dm542_control_pul_pin, uint8_t dm542_control_ena_pin, volatile uint8_t * dm542_control_port, uint8_t dm542_power_drv_pin, volatile uint8_t * dm542_power_drv_port, uint8_t dm542_connection_check_pin, volatile uint8_t * dm542_connection_check_port, uint32_t f_cpu)
{
	dm542_driver->dm542_control_ena_pin = dm542_control_ena_pin;
	dm542_driver->dm542_control_pul_pin = dm542_control_pul_pin;
	dm542_driver->dm542_control_port = dm542_control_port;
	dm542_driver->dm542_power_drv_pin = dm542_power_drv_pin;
	dm542_driver->dm542_power_drv_port = dm542_power_drv_port;
	dm542_driver->dm542_connection_check_pin = dm542_connection_check_pin;
	dm542_driver->dm542_connection_check_port = dm542_connection_check_port;
	dm542_driver->f_cpu = f_cpu;
}

void hal_dm542_power_drv_on(struct dm542_driver_data * dm542_driver)
{
	* dm542_driver->dm542_power_drv_port |= (1 << dm542_driver->dm542_power_drv_pin);
}

void hal_dm542_power_drv_off(struct dm542_driver_data * dm542_driver)
{
	* dm542_driver->dm542_power_drv_port &= ~(1 << dm542_driver->dm542_power_drv_pin);
}

void hal_dm542_control_ena_off(struct dm542_driver_data * dm542_driver)
{
	* dm542_driver->dm542_control_port |= (1 << dm542_driver->dm542_control_ena_pin);
}

void hal_dm542_control_ena_on(struct dm542_driver_data * dm542_driver)
{
	* dm542_driver->dm542_control_port &= ~(1 << dm542_driver->dm542_control_ena_pin);
}

void hal_dm542_control_pul_on(struct dm542_driver_data * dm542_driver)
{
	* dm542_driver->dm542_control_port |= (1 << dm542_driver->dm542_control_pul_pin);
}

void hal_dm542_control_pul_off(struct dm542_driver_data * dm542_driver)
{
	* dm542_driver->dm542_control_port &= ~(1 << dm542_driver->dm542_control_pul_pin);
}

void hal_dm542_connection_check_pin_pull_up(struct dm542_driver_data * dm542_driver)
{
	* dm542_driver->dm542_connection_check_port |= (1 << dm542_driver->dm542_connection_check_pin);
}

void hal_dm542_init_ports(struct dm542_driver_data * dm542_driver)
{
	hal_dm542_control_ena_off(dm542_driver);
	hal_dm542_control_pul_off(dm542_driver);
	hal_dm542_power_drv_off(dm542_driver);
	hal_dm542_connection_check_pin_pull_up(dm542_driver);
}

void hal_dm542_init_ddr(struct dm542_driver_data * dm542_driver) 
{
	* (dm542_driver->dm542_control_port  -1)		|= (1 << dm542_driver->dm542_control_pul_pin); //из адреса регистра PORT получаем адрес регистра DDR
	* (dm542_driver->dm542_control_port  -1)		|= (1 << dm542_driver->dm542_control_ena_pin);
	* (dm542_driver->dm542_power_drv_port-1)		|= (1 << dm542_driver->dm542_power_drv_pin);
	* (dm542_driver->dm542_connection_check_port-1)	&= ~(1 << dm542_driver->dm542_connection_check_pin);
}

void hal_dm542_init(struct dm542_driver_data * dm542_driver, uint8_t dm542_control_pul_pin, uint8_t dm542_control_ena_pin, volatile uint8_t * dm542_control_port, uint8_t dm542_power_drv_pin, volatile uint8_t * dm542_power_drv_port, uint8_t dm542_connection_check_pin, volatile uint8_t * dm542_connection_check_port, uint32_t f_cpu)
{
	uint8_t timer_n = 0;
	
	hal_dm542_init_struct(dm542_driver, dm542_control_pul_pin, dm542_control_ena_pin, dm542_control_port, dm542_power_drv_pin, dm542_power_drv_port, dm542_connection_check_pin, dm542_connection_check_port, f_cpu);
	hal_dm542_init_ddr(dm542_driver);
	hal_dm542_init_ports(dm542_driver);
	hal_dm542_power_drv_on(dm542_driver);
	hal_dm542_control_ena_on(dm542_driver);
	switch (dm542_control_pul_pin)
	{
		case PB4: {timer_n = 0; break;}
		case PB5: {timer_n = 1; break;}
		case PB6: {timer_n = 1; break;}
		case PB7: {timer_n = 2; break;}
	}
	timer_init(timer_n, 1, NORMAL_PORT_OPERATION, TOGGLE_OC0_ON_COMPARE_MATCH, FALSE, FALSE, 1);
}

uint8_t hal_dm542_calculate_prescaler(uint16_t pul_rev_selected, uint8_t rpm_selected)
{
	uint8_t result = 0;
	
	if (rpm_selected == 96)
	{
		switch (pul_rev_selected)
		{
			case 400:
			{
				result = 64;
				break;
			}
			case 800:
			case 1000:
			case 1600:
			case 2000:
			{
				result = 32;
				break;
			}
			case 3200:
			case 4000:
			case 5000:
			case 6400:
			case 8000:
			case 10000:
			case 12800:
			{
				result = 8;
				break;
			}	
			case 20000:
			case 25000:
			case 25600:	
			{
				result = 1;
				break;
			}	
		}
	}
	else
	{
		switch (pul_rev_selected)
		{
			case 400: 
			{
				result = 128;
				break;
			}
			case 800:
			{
				result = 64;
				break;
			}
			case 1000:
			case 1600:
			case 2000:
			case 3200:
			{
				result = 32;
				break;				
			}
			case 4000:
			case 5000:
			case 6400:
			case 8000:
			case 10000:
			case 12800:
			case 20000:
			case 25000:
			case 25600:
			{
				result = 8;
				break;
			}
		}
	}
	
	return result;
}

uint8_t hal_dm542_calculate_ocr(struct dm542_driver_data * dm542_driver_data, uint16_t pul_rev_selected, uint8_t rpm_selected)
{
	uint8_t result = 0;
	if (rpm_selected == 96)
	{
		switch (pul_rev_selected)
		{
			case 400:	{result = 179; break;}
			case 800:	{result = 179; break;}
			case 1000:	{result = 143; break;}
			case 1600:	{result = 89; break;}
			case 2000:	{result = 71; break;}
			case 3200:	{result = 179; break;}
			case 4000:	{result = 143; break;}
			case 5000:	{result = 114; break;}
			case 6400:	{result = 89; break;}
			case 8000:	{result = 71; break;}
			case 10000:	{result = 57; break;}
			case 12800:	{result = 44; break;}
			case 20000:	{result = 229; break;}
			case 25000:	{result = 183; break;}
			case 25600:	{result = 179; break;}

		}
	}
	else
	{
		result = (uint8_t)(((float)dm542_driver_data->f_cpu)/((float)pul_rev_selected*rpm_selected/60*2*hal_dm542_calculate_prescaler(pul_rev_selected, rpm_selected))-1);	
	}	
	return result;
}

void hal_dm542_start_rotation(struct dm542_driver_data * dm542_driver, uint16_t pul_rev_selected, uint8_t rpm_selected)
{
	uint8_t timer_n = 0;
	uint8_t prescaler = 0;
	uint8_t ocr = 0;
	switch (dm542_driver->dm542_control_pul_pin)
	{
		case PB4: {timer_n = 0; break;}
		case PB5: {timer_n = 1; break;}
		case PB6: {timer_n = 1; break;}
		case PB7: {timer_n = 2; break;}
	}
	prescaler = hal_dm542_calculate_prescaler(pul_rev_selected, rpm_selected);
	ocr = hal_dm542_calculate_ocr(dm542_driver, pul_rev_selected, rpm_selected);
	timer_init(timer_n, prescaler, CTC, TOGGLE_OC0_ON_COMPARE_MATCH, FALSE, FALSE, ocr);
}

void hal_dm542_stop_rotation(struct dm542_driver_data * dm542_driver)
{
	uint8_t timer_n = 0;
	switch (dm542_driver->dm542_control_pul_pin)
	{
		case PB4: {timer_n = 0; break;}
		case PB5: {timer_n = 1; break;}
		case PB6: {timer_n = 1; break;}
		case PB7: {timer_n = 2; break;}
	}
	timer_init(timer_n, 1, NORMAL_PORT_OPERATION, TOGGLE_OC0_ON_COMPARE_MATCH, FALSE, FALSE, 1);
}




