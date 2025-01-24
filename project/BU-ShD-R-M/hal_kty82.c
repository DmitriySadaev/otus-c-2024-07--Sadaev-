<<<<<<< HEAD
/*! 
  \file
  \defgroup		hal_kty82
  \brief		Файл исходного кода программы hal_kty82.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций датчика температуры KTY82/110.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  KTY82/110
*/

/*Схема включения датчика температруы KTY
 *							
 *						  ^	Vref	
 *                        |
 *                       ---  R ~ 3 kOhm
 *                       | |
 *                       | |
 *          Output       ---
 *				----------|-----------
 *                       ---  KTY    |  C1 =  0.1 uF
 *                       | |      -------
 *                       | |      -------
 *                       ---         |
 *						  |			 |
 *						 ---        ---
 *						 GND	    GND
 */

#include "hal_kty82.h"

void hal_kty82_set_type(struct kty82_data * t_sensor, uint8_t sensor_type)
{
	t_sensor->type = sensor_type;
}

void hal_kty82_set_adc_pin(struct kty82_data * t_sensor, uint8_t sensor_adc_pin)
{
	t_sensor->adc_pin = sensor_adc_pin;
}

void hal_kty82_set_initial_kty82_resistance_ohm(struct kty82_data * t_sensor, uint16_t sensor_resistance_25)
{
	t_sensor->initial_kty82_resistance_ohm = sensor_resistance_25;
}

void hal_kty82_set_initial_kty82_temperature_grad10(struct kty82_data * t_sensor, uint16_t sensor_resistance_measurement_temperature)
{
	t_sensor->initial_kty82_temperature_grad10 = sensor_resistance_measurement_temperature;
}

void hal_kty82_set_initial_temperature_shift(struct kty82_data * t_sensor, int16_t temperature_shift)
{
	t_sensor->shift_grad10 = temperature_shift;
}

void hal_kty82_set_ballast_resistance(struct kty82_data * t_sensor, uint16_t ballast_resistance)
{
	t_sensor->ballast_resistance_ohm = ballast_resistance;
}

void hal_kty82_set_vref(struct kty82_data * t_sensor, uint16_t v_ref)
{
	t_sensor->v_ref = v_ref;
}

void hal_kty82_set_vref_kty(struct kty82_data * t_sensor, uint16_t v_ref_kty)
{
	t_sensor->v_ref_kty = v_ref_kty;
}

void hal_kty82_set_defaults(struct kty82_data * t_sensor, uint16_t sensor_resistance_25, uint16_t sensor_resistance_measurement_temperature, int8_t temperature_shift, uint16_t ballast_resistance, uint16_t v_ref, uint16_t v_ref_kty)
{
	hal_kty82_set_initial_kty82_resistance_ohm(t_sensor, sensor_resistance_25);
	hal_kty82_set_initial_kty82_temperature_grad10(t_sensor, sensor_resistance_measurement_temperature);
	hal_kty82_set_initial_temperature_shift(t_sensor, temperature_shift);
	hal_kty82_set_ballast_resistance(t_sensor, ballast_resistance);
	hal_kty82_set_vref(t_sensor, v_ref);
	hal_kty82_set_vref_kty(t_sensor, v_ref_kty);
}

void hal_kty82_init(struct kty82_data * t_sensor, uint8_t sensor_type, uint8_t sensor_adc_pin)
{
	hal_kty82_set_type(t_sensor, sensor_type);
	hal_kty82_set_adc_pin(t_sensor, sensor_adc_pin);
	avr_driver_adc_init(ADC_PRESCALER_DEFAULT, ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT, ADC_ADJUST_SELECTION_DEFAULT);
	switch (sensor_type)
	{
		case KTY82_110:
		{
			hal_kty82_set_defaults(t_sensor, KTY82_110_RESISTANCE_DEFAULT_OHM, KTY82_110_TEMPERATURE_DEFAULT_10GRAD, KTY82_110_TEMPERATURE_SHIFT_DEFAULT_10GRAD, KTY82_110_BALLAST_DEFAULT_OHM,V_REF_MV ,V_REF_KTY_MV);
			break;			
		}
	}
}   
                  
uint16_t hal_kty82_adc_to_mv_conversion(struct kty82_data * t_sensor, uint16_t adc)
{
	float result = 0;
	result = (float)t_sensor->v_ref/(float)1023*(float)adc;
	return (uint16_t)result;
}

uint16_t hal_kty82_mv_to_ohm_conversion(struct kty82_data * t_sensor, uint16_t v_kty)
{
	float result = 0;
	result = (float)t_sensor->ballast_resistance_ohm*(float)v_kty/((float)t_sensor->v_ref_kty-(float)v_kty);
	return (uint16_t)result;
}

int16_t hal_kty82_ohm_to_grad10_conversion(struct kty82_data * t_sensor, uint16_t r_kty)
{
	int16_t result = 0;
	
	if ((t_sensor->type) == KTY82_110)
	{
		typedef struct {int16_t kty_lookup_t; uint16_t kty_lookup_r;} table;
		
		table kty82_110_lookup[24]=
		{
			{-550, 490},
			{-500, 515},
			{-400, 567},
			{-300, 624},
			{-200, 684},
			{-100, 747},
			{   0, 815},
			{ 100, 886},
			{ 200, 961},
			{ 250, 1000},
			{ 300, 1040},
			{ 400, 1122},
			{ 500, 1209},
			{ 600, 1299},
			{ 700, 1392},
			{ 800, 1490},
			{ 900, 1591},
			{1000, 1696},
			{1100, 1805},
			{1200, 1915},
			{1250, 1970},
			{1300, 2023},
			{1400, 2124},
			{1500, 2211}
		};

		for (uint8_t i = 0; i < (23); i++)
		{
			if (r_kty < kty82_110_lookup[0].kty_lookup_r)
			{
				result = KTY82_SHORT;							//Показания ниже -55°С - КЗ
			}
			if (r_kty > kty82_110_lookup[23].kty_lookup_r)
			{
				result = KTY82_BREAK;							//Показания выше +150°С - обрыв
			}
			if ((kty82_110_lookup[i].kty_lookup_r <= r_kty) && (kty82_110_lookup[i+1].kty_lookup_r > r_kty))
			{
				result =  (int16_t)(((float)kty82_110_lookup[i].kty_lookup_t + ((float)kty82_110_lookup[i+1].kty_lookup_t - (float)kty82_110_lookup[i].kty_lookup_t)*((float)r_kty-(float)kty82_110_lookup[i].kty_lookup_r)/((float)kty82_110_lookup[i+1].kty_lookup_r-(float)kty82_110_lookup[i].kty_lookup_r)));
			}
		}
	}
	
	return result;
}

void hal_kty82_set_adc(struct kty82_data * t_sensor)
{
	avr_driver_adc_select_channel_single_ended_input(t_sensor->adc_pin);
	t_sensor->current_adc = adc_driver_convert();
}

void hal_kty82_update(struct kty82_data * t_sensor)
{
	uint16_t buffer = 0;
	int16_t buffer1 = 0;
	
	hal_kty82_set_adc(t_sensor);
	buffer = hal_kty82_adc_to_mv_conversion(t_sensor, t_sensor->current_adc);
	buffer = hal_kty82_mv_to_ohm_conversion(t_sensor, buffer);
	buffer1 = hal_kty82_ohm_to_grad10_conversion(t_sensor, buffer);
	
	t_sensor->temperature_grad10 = buffer1;
}

int16_t hal_kty_read_temperature(struct kty82_data * t_sensor)
{
	int16_t result = 0;
	
	if ((t_sensor->temperature_grad10 == KTY82_SHORT) || (t_sensor->temperature_grad10 == KTY82_BREAK))
	{
		result = t_sensor->temperature_grad10; 
	}
	else
	{
		result = t_sensor->temperature_grad10+t_sensor->shift_grad10;		
	}

	return result;
}


=======
/*! 
  \file
  \defgroup		hal_kty82
  \brief		Файл исходного кода программы hal_kty82.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя слой аппаратных абстракций датчика температуры KTY82/110.
  - Compiler:           GNU AVR toolchain    
  - Supported MCU:		AtMega64A
  - Supported devices:  KTY82/110
*/

/*Схема включения датчика температруы KTY
 *							
 *						  ^	Vref	
 *                        |
 *                       ---  R ~ 3 kOhm
 *                       | |
 *                       | |
 *          Output       ---
 *				----------|-----------
 *                       ---  KTY    |  C1 =  0.1 uF
 *                       | |      -------
 *                       | |      -------
 *                       ---         |
 *						  |			 |
 *						 ---        ---
 *						 GND	    GND
 */

#include "hal_kty82.h"

void hal_kty82_set_type(struct kty82_data * t_sensor, uint8_t sensor_type)
{
	t_sensor->type = sensor_type;
}

void hal_kty82_set_adc_pin(struct kty82_data * t_sensor, uint8_t sensor_adc_pin)
{
	t_sensor->adc_pin = sensor_adc_pin;
}

void hal_kty82_set_initial_kty82_resistance_ohm(struct kty82_data * t_sensor, uint16_t sensor_resistance_25)
{
	t_sensor->initial_kty82_resistance_ohm = sensor_resistance_25;
}

void hal_kty82_set_initial_kty82_temperature_grad10(struct kty82_data * t_sensor, uint16_t sensor_resistance_measurement_temperature)
{
	t_sensor->initial_kty82_temperature_grad10 = sensor_resistance_measurement_temperature;
}

void hal_kty82_set_initial_temperature_shift(struct kty82_data * t_sensor, int16_t temperature_shift)
{
	t_sensor->shift_grad10 = temperature_shift;
}

void hal_kty82_set_ballast_resistance(struct kty82_data * t_sensor, uint16_t ballast_resistance)
{
	t_sensor->ballast_resistance_ohm = ballast_resistance;
}

void hal_kty82_set_vref(struct kty82_data * t_sensor, uint16_t v_ref)
{
	t_sensor->v_ref = v_ref;
}

void hal_kty82_set_vref_kty(struct kty82_data * t_sensor, uint16_t v_ref_kty)
{
	t_sensor->v_ref_kty = v_ref_kty;
}

void hal_kty82_set_defaults(struct kty82_data * t_sensor, uint16_t sensor_resistance_25, uint16_t sensor_resistance_measurement_temperature, int8_t temperature_shift, uint16_t ballast_resistance, uint16_t v_ref, uint16_t v_ref_kty)
{
	hal_kty82_set_initial_kty82_resistance_ohm(t_sensor, sensor_resistance_25);
	hal_kty82_set_initial_kty82_temperature_grad10(t_sensor, sensor_resistance_measurement_temperature);
	hal_kty82_set_initial_temperature_shift(t_sensor, temperature_shift);
	hal_kty82_set_ballast_resistance(t_sensor, ballast_resistance);
	hal_kty82_set_vref(t_sensor, v_ref);
	hal_kty82_set_vref_kty(t_sensor, v_ref_kty);
}

void hal_kty82_init(struct kty82_data * t_sensor, uint8_t sensor_type, uint8_t sensor_adc_pin)
{
	hal_kty82_set_type(t_sensor, sensor_type);
	hal_kty82_set_adc_pin(t_sensor, sensor_adc_pin);
	avr_driver_adc_init(ADC_PRESCALER_DEFAULT, ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT, ADC_ADJUST_SELECTION_DEFAULT);
	switch (sensor_type)
	{
		case KTY82_110:
		{
			hal_kty82_set_defaults(t_sensor, KTY82_110_RESISTANCE_DEFAULT_OHM, KTY82_110_TEMPERATURE_DEFAULT_10GRAD, KTY82_110_TEMPERATURE_SHIFT_DEFAULT_10GRAD, KTY82_110_BALLAST_DEFAULT_OHM,V_REF_MV ,V_REF_KTY_MV);
			break;			
		}
	}
}   
                  
uint16_t hal_kty82_adc_to_mv_conversion(struct kty82_data * t_sensor, uint16_t adc)
{
	float result = 0;
	result = (float)t_sensor->v_ref/(float)1023*(float)adc;
	return (uint16_t)result;
}

uint16_t hal_kty82_mv_to_ohm_conversion(struct kty82_data * t_sensor, uint16_t v_kty)
{
	float result = 0;
	result = (float)t_sensor->ballast_resistance_ohm*(float)v_kty/((float)t_sensor->v_ref_kty-(float)v_kty);
	return (uint16_t)result;
}

int16_t hal_kty82_ohm_to_grad10_conversion(struct kty82_data * t_sensor, uint16_t r_kty)
{
	int16_t result = 0;
	
	if ((t_sensor->type) == KTY82_110)
	{
		typedef struct {int16_t kty_lookup_t; uint16_t kty_lookup_r;} table;
		
		table kty82_110_lookup[24]=
		{
			{-550, 490},
			{-500, 515},
			{-400, 567},
			{-300, 624},
			{-200, 684},
			{-100, 747},
			{   0, 815},
			{ 100, 886},
			{ 200, 961},
			{ 250, 1000},
			{ 300, 1040},
			{ 400, 1122},
			{ 500, 1209},
			{ 600, 1299},
			{ 700, 1392},
			{ 800, 1490},
			{ 900, 1591},
			{1000, 1696},
			{1100, 1805},
			{1200, 1915},
			{1250, 1970},
			{1300, 2023},
			{1400, 2124},
			{1500, 2211}
		};

		for (uint8_t i = 0; i < (23); i++)
		{
			if (r_kty < kty82_110_lookup[0].kty_lookup_r)
			{
				result = KTY82_SHORT;							//Показания ниже -55°С - КЗ
			}
			if (r_kty > kty82_110_lookup[23].kty_lookup_r)
			{
				result = KTY82_BREAK;							//Показания выше +150°С - обрыв
			}
			if ((kty82_110_lookup[i].kty_lookup_r <= r_kty) && (kty82_110_lookup[i+1].kty_lookup_r > r_kty))
			{
				result =  (int16_t)(((float)kty82_110_lookup[i].kty_lookup_t + ((float)kty82_110_lookup[i+1].kty_lookup_t - (float)kty82_110_lookup[i].kty_lookup_t)*((float)r_kty-(float)kty82_110_lookup[i].kty_lookup_r)/((float)kty82_110_lookup[i+1].kty_lookup_r-(float)kty82_110_lookup[i].kty_lookup_r)));
			}
		}
	}
	
	return result;
}

void hal_kty82_set_adc(struct kty82_data * t_sensor)
{
	avr_driver_adc_select_channel_single_ended_input(t_sensor->adc_pin);
	t_sensor->current_adc = adc_driver_convert();
}

void hal_kty82_update(struct kty82_data * t_sensor)
{
	uint16_t buffer = 0;
	int16_t buffer1 = 0;
	
	hal_kty82_set_adc(t_sensor);
	buffer = hal_kty82_adc_to_mv_conversion(t_sensor, t_sensor->current_adc);
	buffer = hal_kty82_mv_to_ohm_conversion(t_sensor, buffer);
	buffer1 = hal_kty82_ohm_to_grad10_conversion(t_sensor, buffer);
	
	t_sensor->temperature_grad10 = buffer1;
}

int16_t hal_kty_read_temperature(struct kty82_data * t_sensor)
{
	int16_t result = 0;
	
	if ((t_sensor->temperature_grad10 == KTY82_SHORT) || (t_sensor->temperature_grad10 == KTY82_BREAK))
	{
		result = t_sensor->temperature_grad10; 
	}
	else
	{
		result = t_sensor->temperature_grad10+t_sensor->shift_grad10;		
	}

	return result;
}


>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
