<<<<<<< HEAD
/*!
\file
\defgroup avr_driver_adc
\brief Заголовочный файл avr_driver_adc.h

*/

#ifndef AVR_DRIVER_ADC_H_
#define AVR_DRIVER_ADC_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef ADC_PRESCALER_DEFAULT
#define ADC_PRESCALER_DEFAULT 32U
#endif /* ADC_PRESCALER_DEFAULT */

#ifndef ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT
#define ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT ADC_VOLTAGE_REFERENCE_AREF
#endif /* ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT */

	#ifndef ADC_VOLTAGE_REFERENCE_AREF
	#define ADC_VOLTAGE_REFERENCE_AREF 1U
	#endif /* ADC_VOLTAGE_REFERENCE_AREF */
	
	#ifndef ADC_VOLTAGE_REFERENCE_AVCC
	#define ADC_VOLTAGE_REFERENCE_AVCC 2U
	#endif /* ADC_VOLTAGE_REFERENCE_AVCC */	
	
	#ifndef ADC_VOLTAGE_REFERENCE_INTERNAL_2_56V
	#define ADC_VOLTAGE_REFERENCE_INTERNAL_2_56V 3U
	#endif /* ADC_VOLTAGE_REFERENCE_INTERNAL_2_56V */

#ifndef ADC_ADJUST_SELECTION_DEFAULT
#define ADC_ADJUST_SELECTION_DEFAULT ADC_ADJUST_RIGHT
#endif /* ADC_ADJUST_SELECTION_DEFAULT */

	#ifndef ADC_ADJUST_RIGHT
	#define ADC_ADJUST_RIGHT 0U
	#endif /* ADC_ADJUST_RIGHT */
	
	#ifndef ADC_ADJUST_LEFT
	#define ADC_ADJUST_LEFT 1U
	#endif /* ADC_ADJUST_LEFT */

// основные функции
void avr_driver_adc_init(uint8_t prescaler, uint8_t voltage_reference, uint8_t adc_adjust); //Для инициализации по умолчанию avr_driver_adc_init(ADC_PRESCALER_DEFAULT, ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT, ADC_ADJUST_SELECTION_DEFAULT);
void avr_driver_adc_select_channel_single_ended_input(uint8_t adc_channel);
uint16_t adc_driver_convert(void);

//функции для работы в прерываниях (вместо uint16_t adc_driver_convert(void) )
void adc_driver_start_conversion(void);
void adc_driver_wait_till_conversion_is_complete_interrrupt(void);
void adc_driver_clear_conversion_complete_interrupt_flag(void);
uint16_t adc_driver_read_adc_result(void);

=======
/*!
\file
\defgroup avr_driver_adc
\brief Заголовочный файл avr_driver_adc.h

*/

#ifndef AVR_DRIVER_ADC_H_
#define AVR_DRIVER_ADC_H_

#include <stdint.h>
#include <avr/io.h>

#ifndef TRUE
#define TRUE 1U
#endif /* TRUE */

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#ifndef ADC_PRESCALER_DEFAULT
#define ADC_PRESCALER_DEFAULT 32U
#endif /* ADC_PRESCALER_DEFAULT */

#ifndef ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT
#define ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT ADC_VOLTAGE_REFERENCE_AREF
#endif /* ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT */

	#ifndef ADC_VOLTAGE_REFERENCE_AREF
	#define ADC_VOLTAGE_REFERENCE_AREF 1U
	#endif /* ADC_VOLTAGE_REFERENCE_AREF */
	
	#ifndef ADC_VOLTAGE_REFERENCE_AVCC
	#define ADC_VOLTAGE_REFERENCE_AVCC 2U
	#endif /* ADC_VOLTAGE_REFERENCE_AVCC */	
	
	#ifndef ADC_VOLTAGE_REFERENCE_INTERNAL_2_56V
	#define ADC_VOLTAGE_REFERENCE_INTERNAL_2_56V 3U
	#endif /* ADC_VOLTAGE_REFERENCE_INTERNAL_2_56V */

#ifndef ADC_ADJUST_SELECTION_DEFAULT
#define ADC_ADJUST_SELECTION_DEFAULT ADC_ADJUST_RIGHT
#endif /* ADC_ADJUST_SELECTION_DEFAULT */

	#ifndef ADC_ADJUST_RIGHT
	#define ADC_ADJUST_RIGHT 0U
	#endif /* ADC_ADJUST_RIGHT */
	
	#ifndef ADC_ADJUST_LEFT
	#define ADC_ADJUST_LEFT 1U
	#endif /* ADC_ADJUST_LEFT */

// основные функции
void avr_driver_adc_init(uint8_t prescaler, uint8_t voltage_reference, uint8_t adc_adjust); //Для инициализации по умолчанию avr_driver_adc_init(ADC_PRESCALER_DEFAULT, ADC_VOLTAGE_REFERENCE_SELECTION_DEFAULT, ADC_ADJUST_SELECTION_DEFAULT);
void avr_driver_adc_select_channel_single_ended_input(uint8_t adc_channel);
uint16_t adc_driver_convert(void);

//функции для работы в прерываниях (вместо uint16_t adc_driver_convert(void) )
void adc_driver_start_conversion(void);
void adc_driver_wait_till_conversion_is_complete_interrrupt(void);
void adc_driver_clear_conversion_complete_interrupt_flag(void);
uint16_t adc_driver_read_adc_result(void);

>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
#endif /* AVR_DRIVER_ADC_H_ */