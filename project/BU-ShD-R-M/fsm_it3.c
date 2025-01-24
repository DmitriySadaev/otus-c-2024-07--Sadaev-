<<<<<<< HEAD
/*! 
  \file
  \defgroup		fsm_it3
  \brief		Файл исходного кода программы fsm_it3.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) измерителя температуры ИТ-3
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_it3.h"

uint8_t fsm_it3_status;
uint8_t fsm_it3_address;
uint8_t fsm_it3_reset_enabled;
uint8_t fsm_it3_tx_buffer[9];
uint8_t fsm_it3_rx_buffer[22]; 
volatile uint8_t fsm_it3_rx_counter;
volatile uint8_t fsm_it3_tx_counter;
uint8_t fsm_it3_is_initialized;
uint8_t it3_communication_error_count;

/***********************************************************************/
/************************Вспомогательные функции************************/
/***********************************************************************/

void fsm_it3_enable_output(void)
{
	PORTA |= (1 << PA3);
}

void fsm_it3_disable_output(void)
{
	PORTA &= ~(1 << PA3);
}

void fsm_it3_init_variables(struct bu_shd_r_m_data * bu_shd_r_m)
{
	fsm_it3_status = IT3_STATUS_INITIALIZING;
	fsm_it3_rx_counter = 0;
	fsm_it3_tx_counter = 0;
	it3_communication_error_count = 0;
	fsm_it3_is_initialized = 0;
	fsm_it3_address = bu_shd_r_m->it3_address;
	fsm_it3_reset_enabled = bu_shd_r_m->it3_reset_enabled;
}

uint16_t fsm_it3_calculate_crc(uint8_t * it3_frame, uint8_t it3_frame_length)
{
	uint16_t result = 0;
	for (uint8_t i = 0; i< it3_frame_length; i++)
	{
		result = result + (uint8_t)*(it3_frame+i);
	}
	result++;
	for (uint8_t i = 0; i<=15; i++)
	{
		if (result & (1 << i))
		{
			result &= ~(1 << i);
		}
		else
		{
			result |= (1 << i);
		}
	}
	return result;
}

uint8_t fsm_it3_get_crc_high(uint16_t crc)
{
	return (uint8_t)(crc >> 8); 
}

uint8_t fsm_it3_get_crc_low(uint16_t crc)
{
	return (uint8_t)(crc & 0xFF);
}

void fsm_it3_prepare_init_command(void)
{
	fsm_it3_tx_buffer[0] = IT3_SYNC;
	fsm_it3_tx_buffer[1] = IT3_LEN_ASK;
	fsm_it3_tx_buffer[2] = fsm_it3_address;
	fsm_it3_tx_buffer[3] = IT3_NUM;
	fsm_it3_tx_buffer[4] = fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[1],3));
	fsm_it3_tx_buffer[5] = fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[1],3));
	fsm_it3_tx_buffer[6] = IT3_COMMAND_TYPE_INIT;
	fsm_it3_tx_buffer[7] = 0xFE;
	fsm_it3_tx_buffer[8] = 0xFF;
}

void fsm_it3_prepare_transl_temp_command(void)
{
	fsm_it3_tx_buffer[0] = IT3_SYNC;
	fsm_it3_tx_buffer[1] = IT3_LEN_ASK;
	fsm_it3_tx_buffer[2] = fsm_it3_address;
	fsm_it3_tx_buffer[3] = IT3_NUM;
	fsm_it3_tx_buffer[4] = fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[1],3));
	fsm_it3_tx_buffer[5] = fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[1],3));
	fsm_it3_tx_buffer[6] = IT3_COMMAND_TYPE_READ_TEMP;
	fsm_it3_tx_buffer[7] = fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[6],1));
	fsm_it3_tx_buffer[8] = fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[6],1));			
}

void fsm_it3_fill_dot_position(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_it3_rx_buffer[19] & (1 << IT3_DOT_POSITION_BIT))
	{
		bu_shd_r_m->it3_dot_position = IT3_00_DOT_FORMAT;
	}
	else
	{
		bu_shd_r_m->it3_dot_position = IT3_0_DOT_FORMAT;
	}	
}

/***********************************************************************/
/************************Прерывания*************************************/
/***********************************************************************/

ISR(USART1_RX_vect)
{
	if (fsm_it3_status == IT3_STATUS_TRANCIEVING_FINISHED)
	{
		fsm_it3_status = IT3_STATUS_RECIEVING;
	}
	if (fsm_it3_status == IT3_STATUS_RECIEVING)
	{
		fsm_it3_rx_buffer[fsm_it3_rx_counter++] = avr_driver_uart_receive(1);
	}
	if (fsm_it3_is_initialized && (fsm_it3_rx_counter == IT3_RX_TEMP_MAX_LENGTH))
	{
		avr_driver_uart_rx_complete_interrupt_disable(1);
		fsm_it3_status = IT3_STATUS_IDLE;
		fsm_it3_rx_counter = 0;
	}
	if (!fsm_it3_is_initialized && (fsm_it3_rx_counter == IT3_RX_INIT_MAX_LENGTH))
	{
		avr_driver_uart_rx_complete_interrupt_disable(1);
		fsm_it3_status = IT3_STATUS_IDLE;
		fsm_it3_rx_counter = 0;
	}
}

ISR(USART1_UDRE_vect)
{
	if ((fsm_it3_status == IT3_STATUS_IDLE) || (fsm_it3_status == IT3_STATUS_INITIALIZING))
	{
		fsm_it3_status = IT3_STATUS_TRANCIEVING;
		fsm_it3_enable_output();
	}
	if (fsm_it3_status == IT3_STATUS_TRANCIEVING)
	{
		avr_driver_uart_transmitt(1,fsm_it3_tx_buffer[fsm_it3_tx_counter++]);
		if (fsm_it3_tx_counter == IT3_TX_MAX_LENGTH)
		{
			avr_driver_uart_data_register_empty_interrupt_disable(1);
			fsm_it3_status = IT3_STATUS_TRANCIEVING_FINISHED;
			avr_driver_uart_rx_complete_interrupt_enable(1);
			fsm_it3_tx_counter = 0;
		}
	}	
}

ISR(USART1_TX_vect)
{
	fsm_it3_status = IT3_STATUS_TRANCIEVING_FINISHED;
	fsm_it3_disable_output();
}
/***********************************************************************/
/********************Основное функции***********************************/
/***********************************************************************/

void fsm_it3_init(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m, uint8_t transmitter_enable_pin, volatile uint8_t * transmitter_enable_port, uint32_t f_cpu)
{
	fsm_it3_init_variables(bu_shd_r_m);
	hal_adm2483brw_init(adm2483brw, 1/*номер UART*/, IT3_BAUD_SPEED, AVR_DRIVER_UART_SINGLE_SPEED, AVR_DRIVER_UART_ASYNC_OPERATION_MODE, 2 /*количиество стоп бит*/, 8/*число бит в байте*/, AVR_DRIVER_UART_PARITY_DISABLED, transmitter_enable_pin, transmitter_enable_port, f_cpu);	
	avr_driver_uart_rx_complete_interrupt_disable(1);
	avr_driver_uart_data_register_empty_interrupt_disable(1);
	fsm_it3_prepare_init_command();
	virtual_timers_timer_reset(IT3_TIMER);
}

void fsm_it3_process(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (virtual_timers_timer_get(IT3_TIMER) >= IT3_TIMER_SURVEY_PERIOD)
	{
		if (fsm_it3_status == IT3_STATUS_INITIALIZING)
		{
			avr_driver_uart_data_register_empty_interrupt_enable(1);
			virtual_timers_timer_reset(IT3_TIMER);
		}
		if (fsm_it3_status == IT3_STATUS_IDLE)
		{
			do 
			{
				if (fsm_it3_rx_buffer[0] != IT3_SYNC)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[1] != IT3_LEN_RESP_INIT)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[2] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[3] != IT3_NUM)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[4] != 0xFA)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[5] != 0xFF)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[6] != IT3_RESP_TYPE_ERRORS)													{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[7] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[8] != fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[6],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[9] != fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[6],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[10] != IT3_SYNC)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[11] != IT3_LEN_RESP_INIT)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[12] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[13] != IT3_NUM)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[14] != 0xFA)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[15] != 0xFF)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[16] != IT3_RESP_TYPE_INIT)													{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[17] != fsm_it3_address)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[18] != fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[16],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[19] != fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[16],2)))	{it3_communication_error_count++; break;}

				fsm_it3_is_initialized = 1;	
				bu_shd_r_m->error_flags &=  ~((uint32_t)1 << ERROR_IT3_NO_CONNECTION);
				for (uint8_t i =0 ; i < IT3_RX_INIT_MAX_LENGTH; i++)
				{
					fsm_it3_rx_buffer[i] = 0;
				}
				fsm_it3_prepare_transl_temp_command();
			} while (0);
			do 
			{
				if (fsm_it3_rx_buffer[0] != IT3_SYNC)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[1] != IT3_LEN_RESP_INIT)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[2] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[3] != IT3_NUM)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[4] != 0xFA)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[5] != 0xFF)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[6] != IT3_RESP_TYPE_ERRORS)													{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[7] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[8] != fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[6],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[9] != fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[6],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[10] != IT3_SYNC)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[11] != IT3_LEN_RESP_TEMP)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[12] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[13] != IT3_NUM)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[14] != 0xF8)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[15] != 0xFF)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[16] != IT3_RESP_TYPE_INIT)													{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[20] != fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[16],4)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[21] != fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[16],4)))	{it3_communication_error_count++; break;}
				
				bu_shd_r_m->it3_temperature = (fsm_it3_rx_buffer[18]<<8) | fsm_it3_rx_buffer[17];
				fsm_it3_fill_dot_position(bu_shd_r_m);			
				it3_communication_error_count = 0;
				for (uint8_t i =0 ; i < IT3_RX_TEMP_MAX_LENGTH; i++)
				{
					fsm_it3_rx_buffer[i] = 0;
				}
			} while (0);
			if ((it3_communication_error_count >= IT3_COMMUNICATION_ERROR_MAX_COUNT) && !(bu_shd_r_m->error_flags & ((uint32_t)1 <<ERROR_IT3_NO_CONNECTION)))
			{
				fsm_messages_send_broadcast_message(MSG_IT3_NO_CONNECTION);
				bu_shd_r_m->error_flags |=  ((uint32_t)1 << ERROR_IT3_NO_CONNECTION);
				fsm_it3_prepare_init_command();
				fsm_it3_is_initialized = 0;
				it3_communication_error_count = 0;
				bu_shd_r_m->it3_temperature = 0;
			} 
			fsm_it3_rx_counter = 0;
			fsm_it3_tx_counter = 0;
			fsm_it3_enable_output();
			virtual_timers_timer_reset(IT3_TIMER);
			avr_driver_uart_data_register_empty_interrupt_enable(1);
		}
		if ((fsm_it3_status != IT3_STATUS_IDLE) || (fsm_it3_status != IT3_STATUS_INITIALIZING))
		{
			fsm_it3_status = IT3_STATUS_IDLE;
		}
	}
=======
/*! 
  \file
  \defgroup		fsm_it3
  \brief		Файл исходного кода программы fsm_it3.c
  \author		Садаев Д.С.
 
  Файл исходного кода содержит в себе описание функций, используемых в основной программе.
  Исходный код представляет из себя машину состояний (конечный автомат) измерителя температуры ИТ-3
 
  - Compiler:           GNU AVR toolchain         
*/

#include "fsm_it3.h"

uint8_t fsm_it3_status;
uint8_t fsm_it3_address;
uint8_t fsm_it3_reset_enabled;
uint8_t fsm_it3_tx_buffer[9];
uint8_t fsm_it3_rx_buffer[22]; 
volatile uint8_t fsm_it3_rx_counter;
volatile uint8_t fsm_it3_tx_counter;
uint8_t fsm_it3_is_initialized;
uint8_t it3_communication_error_count;

/***********************************************************************/
/************************Вспомогательные функции************************/
/***********************************************************************/

void fsm_it3_enable_output(void)
{
	PORTA |= (1 << PA3);
}

void fsm_it3_disable_output(void)
{
	PORTA &= ~(1 << PA3);
}

void fsm_it3_init_variables(struct bu_shd_r_m_data * bu_shd_r_m)
{
	fsm_it3_status = IT3_STATUS_INITIALIZING;
	fsm_it3_rx_counter = 0;
	fsm_it3_tx_counter = 0;
	it3_communication_error_count = 0;
	fsm_it3_is_initialized = 0;
	fsm_it3_address = bu_shd_r_m->it3_address;
	fsm_it3_reset_enabled = bu_shd_r_m->it3_reset_enabled;
}

uint16_t fsm_it3_calculate_crc(uint8_t * it3_frame, uint8_t it3_frame_length)
{
	uint16_t result = 0;
	for (uint8_t i = 0; i< it3_frame_length; i++)
	{
		result = result + (uint8_t)*(it3_frame+i);
	}
	result++;
	for (uint8_t i = 0; i<=15; i++)
	{
		if (result & (1 << i))
		{
			result &= ~(1 << i);
		}
		else
		{
			result |= (1 << i);
		}
	}
	return result;
}

uint8_t fsm_it3_get_crc_high(uint16_t crc)
{
	return (uint8_t)(crc >> 8); 
}

uint8_t fsm_it3_get_crc_low(uint16_t crc)
{
	return (uint8_t)(crc & 0xFF);
}

void fsm_it3_prepare_init_command(void)
{
	fsm_it3_tx_buffer[0] = IT3_SYNC;
	fsm_it3_tx_buffer[1] = IT3_LEN_ASK;
	fsm_it3_tx_buffer[2] = fsm_it3_address;
	fsm_it3_tx_buffer[3] = IT3_NUM;
	fsm_it3_tx_buffer[4] = fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[1],3));
	fsm_it3_tx_buffer[5] = fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[1],3));
	fsm_it3_tx_buffer[6] = IT3_COMMAND_TYPE_INIT;
	fsm_it3_tx_buffer[7] = 0xFE;
	fsm_it3_tx_buffer[8] = 0xFF;
}

void fsm_it3_prepare_transl_temp_command(void)
{
	fsm_it3_tx_buffer[0] = IT3_SYNC;
	fsm_it3_tx_buffer[1] = IT3_LEN_ASK;
	fsm_it3_tx_buffer[2] = fsm_it3_address;
	fsm_it3_tx_buffer[3] = IT3_NUM;
	fsm_it3_tx_buffer[4] = fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[1],3));
	fsm_it3_tx_buffer[5] = fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[1],3));
	fsm_it3_tx_buffer[6] = IT3_COMMAND_TYPE_READ_TEMP;
	fsm_it3_tx_buffer[7] = fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[6],1));
	fsm_it3_tx_buffer[8] = fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_tx_buffer[6],1));			
}

void fsm_it3_fill_dot_position(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (fsm_it3_rx_buffer[19] & (1 << IT3_DOT_POSITION_BIT))
	{
		bu_shd_r_m->it3_dot_position = IT3_00_DOT_FORMAT;
	}
	else
	{
		bu_shd_r_m->it3_dot_position = IT3_0_DOT_FORMAT;
	}	
}

/***********************************************************************/
/************************Прерывания*************************************/
/***********************************************************************/

ISR(USART1_RX_vect)
{
	if (fsm_it3_status == IT3_STATUS_TRANCIEVING_FINISHED)
	{
		fsm_it3_status = IT3_STATUS_RECIEVING;
	}
	if (fsm_it3_status == IT3_STATUS_RECIEVING)
	{
		fsm_it3_rx_buffer[fsm_it3_rx_counter++] = avr_driver_uart_receive(1);
	}
	if (fsm_it3_is_initialized && (fsm_it3_rx_counter == IT3_RX_TEMP_MAX_LENGTH))
	{
		avr_driver_uart_rx_complete_interrupt_disable(1);
		fsm_it3_status = IT3_STATUS_IDLE;
		fsm_it3_rx_counter = 0;
	}
	if (!fsm_it3_is_initialized && (fsm_it3_rx_counter == IT3_RX_INIT_MAX_LENGTH))
	{
		avr_driver_uart_rx_complete_interrupt_disable(1);
		fsm_it3_status = IT3_STATUS_IDLE;
		fsm_it3_rx_counter = 0;
	}
}

ISR(USART1_UDRE_vect)
{
	if ((fsm_it3_status == IT3_STATUS_IDLE) || (fsm_it3_status == IT3_STATUS_INITIALIZING))
	{
		fsm_it3_status = IT3_STATUS_TRANCIEVING;
		fsm_it3_enable_output();
	}
	if (fsm_it3_status == IT3_STATUS_TRANCIEVING)
	{
		avr_driver_uart_transmitt(1,fsm_it3_tx_buffer[fsm_it3_tx_counter++]);
		if (fsm_it3_tx_counter == IT3_TX_MAX_LENGTH)
		{
			avr_driver_uart_data_register_empty_interrupt_disable(1);
			fsm_it3_status = IT3_STATUS_TRANCIEVING_FINISHED;
			avr_driver_uart_rx_complete_interrupt_enable(1);
			fsm_it3_tx_counter = 0;
		}
	}	
}

ISR(USART1_TX_vect)
{
	fsm_it3_status = IT3_STATUS_TRANCIEVING_FINISHED;
	fsm_it3_disable_output();
}
/***********************************************************************/
/********************Основное функции***********************************/
/***********************************************************************/

void fsm_it3_init(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m, uint8_t transmitter_enable_pin, volatile uint8_t * transmitter_enable_port, uint32_t f_cpu)
{
	fsm_it3_init_variables(bu_shd_r_m);
	hal_adm2483brw_init(adm2483brw, 1/*номер UART*/, IT3_BAUD_SPEED, AVR_DRIVER_UART_SINGLE_SPEED, AVR_DRIVER_UART_ASYNC_OPERATION_MODE, 2 /*количиество стоп бит*/, 8/*число бит в байте*/, AVR_DRIVER_UART_PARITY_DISABLED, transmitter_enable_pin, transmitter_enable_port, f_cpu);	
	avr_driver_uart_rx_complete_interrupt_disable(1);
	avr_driver_uart_data_register_empty_interrupt_disable(1);
	fsm_it3_prepare_init_command();
	virtual_timers_timer_reset(IT3_TIMER);
}

void fsm_it3_process(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (virtual_timers_timer_get(IT3_TIMER) >= IT3_TIMER_SURVEY_PERIOD)
	{
		if (fsm_it3_status == IT3_STATUS_INITIALIZING)
		{
			avr_driver_uart_data_register_empty_interrupt_enable(1);
			virtual_timers_timer_reset(IT3_TIMER);
		}
		if (fsm_it3_status == IT3_STATUS_IDLE)
		{
			do 
			{
				if (fsm_it3_rx_buffer[0] != IT3_SYNC)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[1] != IT3_LEN_RESP_INIT)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[2] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[3] != IT3_NUM)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[4] != 0xFA)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[5] != 0xFF)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[6] != IT3_RESP_TYPE_ERRORS)													{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[7] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[8] != fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[6],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[9] != fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[6],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[10] != IT3_SYNC)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[11] != IT3_LEN_RESP_INIT)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[12] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[13] != IT3_NUM)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[14] != 0xFA)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[15] != 0xFF)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[16] != IT3_RESP_TYPE_INIT)													{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[17] != fsm_it3_address)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[18] != fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[16],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[19] != fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[16],2)))	{it3_communication_error_count++; break;}

				fsm_it3_is_initialized = 1;	
				bu_shd_r_m->error_flags &=  ~((uint32_t)1 << ERROR_IT3_NO_CONNECTION);
				for (uint8_t i =0 ; i < IT3_RX_INIT_MAX_LENGTH; i++)
				{
					fsm_it3_rx_buffer[i] = 0;
				}
				fsm_it3_prepare_transl_temp_command();
			} while (0);
			do 
			{
				if (fsm_it3_rx_buffer[0] != IT3_SYNC)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[1] != IT3_LEN_RESP_INIT)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[2] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[3] != IT3_NUM)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[4] != 0xFA)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[5] != 0xFF)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[6] != IT3_RESP_TYPE_ERRORS)													{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[7] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[8] != fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[6],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[9] != fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[6],2)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[10] != IT3_SYNC)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[11] != IT3_LEN_RESP_TEMP)														{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[12] != 0x00)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[13] != IT3_NUM)																{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[14] != 0xF8)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[15] != 0xFF)																	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[16] != IT3_RESP_TYPE_INIT)													{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[20] != fsm_it3_get_crc_low(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[16],4)))	{it3_communication_error_count++; break;}
				if (fsm_it3_rx_buffer[21] != fsm_it3_get_crc_high(fsm_it3_calculate_crc(&fsm_it3_rx_buffer[16],4)))	{it3_communication_error_count++; break;}
				
				bu_shd_r_m->it3_temperature = (fsm_it3_rx_buffer[18]<<8) | fsm_it3_rx_buffer[17];
				fsm_it3_fill_dot_position(bu_shd_r_m);			
				it3_communication_error_count = 0;
				for (uint8_t i =0 ; i < IT3_RX_TEMP_MAX_LENGTH; i++)
				{
					fsm_it3_rx_buffer[i] = 0;
				}
			} while (0);
			if ((it3_communication_error_count >= IT3_COMMUNICATION_ERROR_MAX_COUNT) && !(bu_shd_r_m->error_flags & ((uint32_t)1 <<ERROR_IT3_NO_CONNECTION)))
			{
				fsm_messages_send_broadcast_message(MSG_IT3_NO_CONNECTION);
				bu_shd_r_m->error_flags |=  ((uint32_t)1 << ERROR_IT3_NO_CONNECTION);
				fsm_it3_prepare_init_command();
				fsm_it3_is_initialized = 0;
				it3_communication_error_count = 0;
				bu_shd_r_m->it3_temperature = 0;
			} 
			fsm_it3_rx_counter = 0;
			fsm_it3_tx_counter = 0;
			fsm_it3_enable_output();
			virtual_timers_timer_reset(IT3_TIMER);
			avr_driver_uart_data_register_empty_interrupt_enable(1);
		}
		if ((fsm_it3_status != IT3_STATUS_IDLE) || (fsm_it3_status != IT3_STATUS_INITIALIZING))
		{
			fsm_it3_status = IT3_STATUS_IDLE;
		}
	}
>>>>>>> f2f8c77ab68784997ceace777433729a63acd840
}