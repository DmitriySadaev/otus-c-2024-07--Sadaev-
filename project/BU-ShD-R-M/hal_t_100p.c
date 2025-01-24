/*! 
  \file
  \defgroup		hal_t_100p
  \brief		Файл исходного кода программы hal_t_100p.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций датчика температуры типа 100П.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
*/

#include "hal_t_100p.h"

void hal_t_100p_set_temperature_shift(struct t_100p_data * t_sensor, int16_t temperature_shift)
{
	t_sensor->shift_grad10 = temperature_shift;
}

void hal_t_100p_struct_init(struct t_100p_data * t_sensor, uint8_t adc_pin, uint16_t v_ref, uint8_t control_pin, volatile  uint8_t * control_port)
{
	t_sensor->adc_pin = adc_pin;
	t_sensor->v_ref = v_ref;
	t_sensor->control_pin = control_pin;
	t_sensor->control_port = control_port;
}

void hal_t_100p_control_init_ddr(struct t_100p_data * t_sensor)
{
	* (t_sensor->control_port  -1)	|= (1 << t_sensor->control_pin); //из адреса регистра PORT получаем адрес регистра DDR
}

void hal_t_100p_control_pin_on(struct t_100p_data * t_sensor)
{
	* t_sensor->control_port |= (1 << t_sensor->control_pin);
}

void hal_t_100p_control_pin_off(struct t_100p_data * t_sensor)
{
	* t_sensor->control_port &= ~(1 << t_sensor->control_pin);
}

void hal_t_100p_init(struct t_100p_data * t_sensor, uint8_t adc_pin, uint16_t v_ref, uint8_t control_pin, volatile uint8_t * control_port)
{
	hal_t_100p_struct_init(t_sensor, adc_pin, v_ref, control_pin, control_port);
	hal_t_100p_control_init_ddr(t_sensor);
	hal_t_100p_control_pin_on(t_sensor);
	avr_driver_adc_init(ADC_PRESCALER_DEFAULT, ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT, ADC_ADJUST_SELECTION_DEFAULT);
}
                  
uint16_t hal_t_100p_to_mv_conversion(struct t_100p_data * t_sensor)
{
	float result = 0;
	result = (float)t_sensor->v_ref/(float)1023*(float)t_sensor->current_adc;
	return (uint16_t)result;
}

int16_t hal_t_100p_to_grad10_conversion(struct t_100p_data * t_sensor)
{
	int16_t result = 0;
	uint16_t t_100p_mv = hal_t_100p_to_mv_conversion(t_sensor);
	
	typedef struct {int16_t t_100p_lookup_t; uint16_t t_100p_lookup_mv;} table;
		
	table t_100p_lookup[64]=
	{
		{-2700, 0},
		{-2582, 12},					/*все что ниже 1 мВ считается коротким замыканием, от 1 до 12 мВ - 15 К*/
		{-2530, 20},
		{-2500, 24},			
		{-2450, 39},
		{-2400, 59},			
		{-2350, 85},
		{-2300, 115},
		{-2250, 150},
		{-2200, 187},
		{-2150, 227},
		{-2100, 268},
		{-2050, 311},
		{-2000, 354},
		{-1950, 397},
		{-1900, 441},
		{-1850, 485},
		{-1800, 528},			
		{-1750, 572},
		{-1700, 615},
		{-1650, 658},
		{-1600, 701},
		{-1550, 744},
		{-1500, 786},
		{-1450, 830},
		{-1400, 872},
		{-1350, 914},
		{-1300, 957},
		{-1250, 998},
		{-1200, 1040},
		{-1150, 1082},
		{-1100, 1124},
		{-1050, 1166},
		{-1000, 1207},
		{-950, 1248},
		{-900, 1230},
		{-850, 1331},
		{-800, 1372},
		{-750, 1413},
		{-700, 1454},
		{-650, 1495},
		{-600, 1536},
		{-550, 1577},
		{-500, 1617},
		{-450, 1658},
		{-400, 1698},
		{-350, 1739},
		{-300, 1779},
		{-250, 1819},
		{-200, 1860},
		{-150, 1900},
		{-100, 1940},
		{-50, 1980},
		{0, 2020},
		{50, 2060},
		{100, 2100},
		{150, 2140},
		{200, 2180},
		{250, 2219},
		{300, 2259},
		{350, 2298},
		{400, 2338},
		{450, 2377},
		{500, 2417}
	};

		for (uint8_t i = 0; i < 63; i++)
		{

			if (t_100p_mv == t_100p_lookup[0].t_100p_lookup_mv)
			{
				result = T_100P_SHORT;							//Показания ниже 1 мВ - КЗ
				return result;
			}
			if (t_100p_mv > t_100p_lookup[62].t_100p_lookup_mv)
			{
				result = T_100P_BREAK;							//Показания выше +50°С - обрыв
				return result;
			}
			if ((t_100p_mv > t_100p_lookup[0].t_100p_lookup_mv) && (t_100p_mv < t_100p_lookup[1].t_100p_lookup_mv))
			{
				result = t_100p_lookup[1].t_100p_lookup_t;
				return result;
			}
			if ((t_100p_lookup[i].t_100p_lookup_mv <= t_100p_mv) && (t_100p_lookup[i+1].t_100p_lookup_mv > t_100p_mv))
			{
				result =  (int16_t)(((float)t_100p_lookup[i].t_100p_lookup_t + ((float)t_100p_lookup[i+1].t_100p_lookup_t - (float)t_100p_lookup[i].t_100p_lookup_t)*((float)t_100p_mv-(float)t_100p_lookup[i].t_100p_lookup_mv)/((float)t_100p_lookup[i+1].t_100p_lookup_mv-(float)t_100p_lookup[i].t_100p_lookup_mv)));
				return result;
			}
		}
	return result;
}

void hal_t_100p_set_adc(struct t_100p_data * t_sensor)
{
	avr_driver_adc_select_channel_single_ended_input(t_sensor->adc_pin);
	t_sensor->current_adc = adc_driver_convert();
}

void hal_t_100p_update(struct t_100p_data * t_sensor)
{
	hal_t_100p_set_adc(t_sensor);
	t_sensor->temperature_grad10 = hal_t_100p_to_grad10_conversion(t_sensor);	
}

int16_t hal_t_100p_read_temperature(struct t_100p_data * t_sensor)
{
	int16_t result = 0;
	
	if ((t_sensor->temperature_grad10 == T_100P_SHORT) || (t_sensor->temperature_grad10 == T_100P_BREAK))
	{
		result = t_sensor->temperature_grad10; 
	}
	else
	{
		result = t_sensor->temperature_grad10+t_sensor->shift_grad10;		
	}
	if (t_sensor->temperature_grad10 == -2582)
	{
		result = t_sensor->temperature_grad10;
	}

	return result;
}


