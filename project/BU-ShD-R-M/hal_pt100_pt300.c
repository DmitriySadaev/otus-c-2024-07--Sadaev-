/*! 
  \file
  \defgroup		hal_pt100_pt300
  \brief		Файл исходного кода программы hal_pt100_pt300.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций датчика температуры с характеристикой Pt100 или Pt300
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
*/

#include "hal_pt100_pt300.h"

void hal_pt100_pt300_set_temperature_shift(struct pt100_pt300_data * t_sensor, int16_t temperature_shift)
{
	t_sensor->shift_grad10 = temperature_shift;
}

void hal_pt100_pt300_struct_init(struct pt100_pt300_data * t_sensor, uint8_t pt100_pt300_mode, uint8_t pt300_control_pin, volatile uint8_t * pt300_control_port, uint8_t adc_pin, uint16_t v_ref)
{
	t_sensor->pt100_pt300_mode = pt100_pt300_mode;
	t_sensor->pt300_control_pin = pt300_control_pin;
	t_sensor->pt300_control_port = pt300_control_port;	
	t_sensor->adc_pin = adc_pin;
	t_sensor->v_ref = v_ref;
}

void hal_pt100_pt300_init_ddr(struct pt100_pt300_data * t_sensor)
{
	* (t_sensor->pt300_control_port  -1)	|= (1 << t_sensor->pt300_control_pin); //из адреса регистра PORT получаем адрес регистра DDR

}

void hal_pt100_pt300_select_pt300(struct pt100_pt300_data * t_sensor)
{
	* t_sensor->pt300_control_port &= ~(1 << t_sensor->pt300_control_pin);
}

void hal_pt100_pt300_select_pt100(struct pt100_pt300_data * t_sensor)
{
	* t_sensor->pt300_control_port |= (1 << t_sensor->pt300_control_pin);
}

void hal_pt100_pt300_select_cu100(struct pt100_pt300_data * t_sensor)
{
	* t_sensor->pt300_control_port |= (1 << t_sensor->pt300_control_pin);
}

void hal_pt100_pt300_select_cu300(struct pt100_pt300_data * t_sensor)
{
	* t_sensor->pt300_control_port &= ~(1 << t_sensor->pt300_control_pin);
}

void hal_pt100_pt300_init(struct pt100_pt300_data * t_sensor, uint8_t pt100_pt300_mode, uint8_t pt300_control_pin, volatile uint8_t * pt300_control_port, uint8_t adc_pin, uint16_t v_ref)
{
	hal_pt100_pt300_struct_init(t_sensor, pt100_pt300_mode, pt300_control_pin, pt300_control_port, adc_pin, v_ref);
	hal_pt100_pt300_init_ddr(t_sensor);
	if (t_sensor->pt100_pt300_mode == PT100_MODE) 
	{
		hal_pt100_pt300_select_pt100(t_sensor);
	}
	if (t_sensor->pt100_pt300_mode == PT300_MODE) 
	{
		hal_pt100_pt300_select_pt300(t_sensor);
	}	
	if (t_sensor->pt100_pt300_mode == CU100_MODE)
	{
		hal_pt100_pt300_select_cu100(t_sensor);
	}
	if (t_sensor->pt100_pt300_mode == CU300_MODE)
	{
		hal_pt100_pt300_select_cu300(t_sensor);
	}
	avr_driver_adc_init(ADC_PRESCALER_DEFAULT, ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT, ADC_ADJUST_SELECTION_DEFAULT);
}
               
uint16_t hal_pt100_pt300_to_mv_conversion(struct pt100_pt300_data * t_sensor)
{
	float result = 0;
	result = (float)t_sensor->v_ref/(float)1023*(float)t_sensor->current_adc;
	return (uint16_t)result;
}			   
			   
int16_t hal_pt100_to_grad10_conversion(struct pt100_pt300_data * t_sensor)
{
	int16_t result = 0;
	uint16_t pt100_mv = hal_pt100_pt300_to_mv_conversion(t_sensor);
	
	typedef struct {int16_t pt100_lookup_t; uint16_t pt100_lookup_mv;} table;
	
	table pt100_lookup[28]=
	{
		{-150, 1402},
		{-100, 1431},
		{-50, 1493},
		{0, 1488},
		{50, 1517},
		{100, 1546},
		{150, 1575},
		{200, 1603},
		{250, 1632},
		{300, 1660},
		{350, 1688},
		{400, 1771},
		{450, 1746},
		{500, 1774},
		{550, 1802},
		{600, 1830},
		{650, 1859},
		{700, 1887},
		{750, 1915},
		{800, 1943},
		{850, 1971},			
		{900, 1999},
		{950, 2027},
		{1000, 2055},
		{1050, 2083},
		{1100, 2110},
		{1150, 2138},
		{1200, 2166}		
	};

	for (uint8_t i = 0; i < 27; i++)
	{

		if (pt100_mv < pt100_lookup[0].pt100_lookup_mv)
		{
			result = PT100_PT300_SHORT;							//Показания ниже --15°С - КЗ
		}
		if (pt100_mv > pt100_lookup[27].pt100_lookup_mv)
		{
			result = PT100_PT300_BREAK;							//Показания выше +120°С - обрыв
		}
		if ((pt100_lookup[i].pt100_lookup_mv <= pt100_mv) && (pt100_lookup[i+1].pt100_lookup_mv > pt100_mv))
		{
			result =  (int16_t)(((float)pt100_lookup[i].pt100_lookup_t + ((float)pt100_lookup[i+1].pt100_lookup_t - (float)pt100_lookup[i].pt100_lookup_t)*((float)pt100_mv-(float)pt100_lookup[i].pt100_lookup_mv)/((float)pt100_lookup[i+1].pt100_lookup_mv-(float)pt100_lookup[i].pt100_lookup_mv)));
		}
	}
	return result;
}			   
	
int16_t hal_pt300_to_grad10_conversion(struct pt100_pt300_data * t_sensor)
{
	int16_t result = 0;
	uint16_t pt300_mv = hal_pt100_pt300_to_mv_conversion(t_sensor);
	
	typedef struct {int16_t pt300_lookup_t; uint16_t pt300_lookup_mv;} table; //табоица неверная 
	
	table pt300_lookup[28]=
	{
		{-150, 1320},
		{-100, 1348},
		{-50, 1375},
		{0, 1403},
		{50, 1427},
		{100, 1455},
		{150, 1483},
		{200, 1510},
		{250, 1538},
		{300, 1566},
		{350, 1589},
		{400, 1617},
		{450, 1645},
		{500, 1673},
		{550, 1696},
		{600, 1724},
		{650, 1752},
		{700, 1780},
		{750, 1803},
		{800, 1831},
		{850, 1859},
		{900, 1887},
		{950, 1910},
		{1000, 1938},
		{1050, 1965},
		{1100, 1988},
		{1150, 2016},
		{1200, 2044}
	};

	for (uint8_t i = 0; i < 27; i++)
	{

		if (pt300_mv < pt300_lookup[0].pt300_lookup_mv)
		{
			result = PT100_PT300_SHORT;							//Показания ниже --15°С - КЗ
		}
		if (pt300_mv > pt300_lookup[27].pt300_lookup_mv)
		{
			result = PT100_PT300_BREAK;							//Показания выше +120°С - обрыв
		}
		if ((pt300_lookup[i].pt300_lookup_mv <= pt300_mv) && (pt300_lookup[i+1].pt300_lookup_mv > pt300_mv))
		{
			result =  (int16_t)(((float)pt300_lookup[i].pt300_lookup_t + ((float)pt300_lookup[i+1].pt300_lookup_t - (float)pt300_lookup[i].pt300_lookup_t)*((float)pt300_mv-(float)pt300_lookup[i].pt300_lookup_mv)/((float)pt300_lookup[i+1].pt300_lookup_mv-(float)pt300_lookup[i].pt300_lookup_mv)));
		}
	}
	return result;
}	
	
int16_t hal_cu100_to_grad10_conversion(struct pt100_pt300_data * t_sensor)
{
	int16_t result = 0;
	uint16_t cu100_mv = hal_pt100_pt300_to_mv_conversion(t_sensor);
	
	typedef struct {int16_t cu100_lookup_t; uint16_t cu100_lookup_mv;} table; //табоица неверная
	
	table cu100_lookup[28]=
	{
		{-150, 1264},
		{-100, 1293},
		{-50, 1321},
		{0, 1349},
		{50, 1378},
		{100, 1406},
		{150, 1435},
		{200, 1463},
		{250, 1492},
		{300, 1520},
		{350, 1549},
		{400, 1577},
		{450, 1606},
		{500, 1634},
		{550, 1663},
		{600, 1691},
		{650, 1719},
		{700, 1748},
		{750, 1776},
		{800, 1805},
		{850, 1833},
		{900, 1862},
		{950, 1890},
		{1000, 1919},
		{1050, 1947},
		{1100, 1975},
		{1150, 2004},
		{1200, 2032}
	};

	for (uint8_t i = 0; i < 27; i++)
	{

		if (cu100_mv < cu100_lookup[0].cu100_lookup_mv)
		{
			result = PT100_PT300_SHORT;							//Показания ниже --15°С - КЗ
		}
		if (cu100_mv > cu100_lookup[27].cu100_lookup_mv)
		{
			result = PT100_PT300_BREAK;							//Показания выше +120°С - обрыв
		}
		if ((cu100_lookup[i].cu100_lookup_mv <= cu100_mv) && (cu100_lookup[i+1].cu100_lookup_mv > cu100_mv))
		{
			result =  (int16_t)(((float)cu100_lookup[i].cu100_lookup_t + ((float)cu100_lookup[i+1].cu100_lookup_t - (float)cu100_lookup[i].cu100_lookup_t)*((float)cu100_mv-(float)cu100_lookup[i].cu100_lookup_mv)/((float)cu100_lookup[i+1].cu100_lookup_mv-(float)cu100_lookup[i].cu100_lookup_mv)));
		}
	}
	return result;
}	
	
int16_t hal_cu300_to_grad10_conversion(struct pt100_pt300_data * t_sensor)
{
	int16_t result = 0;
	uint16_t cu300_mv = hal_pt100_pt300_to_mv_conversion(t_sensor);
	
	typedef struct {int16_t cu300_lookup_t; uint16_t cu300_lookup_mv;} table; //табоица неверная
	
	table cu300_lookup[28]=
	{
		{-150, 1224},
		{-100, 1252},
		{-50, 1280},
		{0, 1308},
		{50, 1336},
		{100, 1363},
		{150, 1391},
		{200, 1419},
		{250, 1447},
		{300, 1475},
		{350, 1503},
		{400, 1530},
		{450, 1558},
		{500, 1586},
		{550, 1614},
		{600, 1641},
		{650, 1669},
		{700, 1697},
		{750, 1724},
		{800, 1752},
		{850, 1780},
		{900, 1808},
		{950, 1835},
		{1000, 1863},
		{1050, 1891},
		{1100, 1918},
		{1150, 1946},
		{1200, 1974}
	};

	for (uint8_t i = 0; i < 27; i++)
	{

		if (cu300_mv < cu300_lookup[0].cu300_lookup_mv)
		{
			result = PT100_PT300_SHORT;							//Показания ниже --15°С - КЗ
		}
		if (cu300_mv > cu300_lookup[27].cu300_lookup_mv)
		{
			result = PT100_PT300_BREAK;							//Показания выше +120°С - обрыв
		}
		if ((cu300_lookup[i].cu300_lookup_mv <= cu300_mv) && (cu300_lookup[i+1].cu300_lookup_mv > cu300_mv))
		{
			result =  (int16_t)(((float)cu300_lookup[i].cu300_lookup_t + ((float)cu300_lookup[i+1].cu300_lookup_t - (float)cu300_lookup[i].cu300_lookup_t)*((float)cu300_mv-(float)cu300_lookup[i].cu300_lookup_mv)/((float)cu300_lookup[i+1].cu300_lookup_mv-(float)cu300_lookup[i].cu300_lookup_mv)));
		}
	}
	return result;
}

void hal_pt100_pt300_set_adc(struct pt100_pt300_data * t_sensor)
{
	avr_driver_adc_select_channel_single_ended_input(t_sensor->adc_pin);
	t_sensor->current_adc = adc_driver_convert();
}

void hal_pt100_pt300_update(struct pt100_pt300_data * t_sensor)
{
	hal_pt100_pt300_set_adc(t_sensor);
	if (t_sensor->pt100_pt300_mode == PT100_MODE)
	{
		t_sensor->temperature_grad10 = hal_pt100_to_grad10_conversion(t_sensor);	
	}
	if (t_sensor->pt100_pt300_mode == PT300_MODE)
	{
		t_sensor->temperature_grad10 = hal_pt300_to_grad10_conversion(t_sensor);	
	}
	if (t_sensor->pt100_pt300_mode == CU100_MODE)
	{
		t_sensor->temperature_grad10 = hal_cu100_to_grad10_conversion(t_sensor);
	}	
	if (t_sensor->pt100_pt300_mode == CU300_MODE)
	{
		t_sensor->temperature_grad10 = hal_cu300_to_grad10_conversion(t_sensor);
	}
}

int16_t hal_pt100_pt300_read_temperature(struct pt100_pt300_data * t_sensor)
{
	int16_t result = 0;
	
	if ((t_sensor->temperature_grad10 == PT100_PT300_SHORT) || (t_sensor->temperature_grad10 == PT100_PT300_BREAK))
	{
		result = t_sensor->temperature_grad10; 
	}
	else
	{
		result = t_sensor->temperature_grad10+t_sensor->shift_grad10;		
	}

	return result;
}


