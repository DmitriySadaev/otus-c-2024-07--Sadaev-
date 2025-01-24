#include "fsm_modbus_rtu_slave.h"

/***********************************************************************/
/******************************Переменные*******************************/
/***********************************************************************/

uint16_t modbus_rx_buffer[DUBNA_RX_MAX_SYMBOLS];
uint16_t modbus_tx_buffer[DUBNA_TX_MAX_SYMBOLS];
uint8_t modbus_rx_buffer_counter;
uint8_t modbus_tx_buffer_counter;
uint8_t prot_type;
uint8_t tx_data_length;
uint8_t fsm_du_status;
uint8_t modbus_errors;
uint16_t modbus_time_count;
uint16_t modbus_silent_delay;
uint16_t bu_sh_d_modbus_state_param[14];
uint8_t bu_sh_d_address;
uint8_t dubna_answer;
uint16_t crc;
uint8_t dubna_answer_status[10];
uint8_t dubna_answer_time[10];
uint8_t dubna_answer_bko_temp[41];
uint8_t dubna_answer_ku_temp[27];

extern struct adm2483brw_data adm2483brw1_d7;
extern struct bu_shd_r_m_data bu_shd_r_m;

/***********************************************************************/
/************************Вспомогательные функции************************/
/***********************************************************************/

void fsm_modbus_rtu_fill_tx_buffer(void)
{
	for (uint8_t i = 0; i < MODBUS_TX_MAX_SYMBOLS; i++)
	{
		modbus_tx_buffer[i] = 0;
	}
}

void fsm_modbus_rtu_slave_init_variables(struct bu_shd_r_m_data * bu_shd_r_m)
{
	fsm_du_status = MODBUS_STATUS_IDLE;
	bu_sh_d_address = bu_shd_r_m->du_address;
	modbus_rx_buffer_counter = 0;
	modbus_tx_buffer_counter = 0;
	modbus_time_count = 0;	
	modbus_errors = 0;
	tx_data_length = 0;
	dubna_answer = 0;
	crc = 0;
	fsm_modbus_rtu_fill_tx_buffer();
}

uint16_t fsm_modbus_calculate_silent_delay(uint32_t modbus_speed)
{
	switch (modbus_speed)
	{
		case 9600:
		{
			return 428;
			break;
		}
		case 19200:
		{
			return 214;
			break;
		}
		case 38400:
		{
			return 107;
			break;
		}
		case 57600:
		{
			return 71;
			break;
		}
		case 115200:
		{
			return 35;
			break;
		}
		default:
		{
			return 0;
			break;
		}
	}
}

void fsm_modbus_execute_orders_du_modbus(struct bu_shd_r_m_data * bu_shd_r_m)
{
	uint16_t buffer = 0;
	buffer = (modbus_rx_buffer[2] << 8) | modbus_rx_buffer[3];
	do 
	{ 
		if (bu_shd_r_m->du_prot	!= PROT_TYPE_MODBUS)							
		{
			modbus_errors |= (1 << MODBUS_ANSWER_DO_NOT_NEEDED);
			break;
		}
		if (bu_shd_r_m->du_address	!= modbus_rx_buffer[0])							
		{
			modbus_errors |= (1 << MODBUS_ANSWER_DO_NOT_NEEDED);
			break;
		}
		if (modbus_rx_buffer[1]	!= MODBUS_COMMAND_FORCE_SINGLE_COIL)			
		{
			if (modbus_rx_buffer[1]	!= MODBUS_COMMAND_READ_INPUT_REGISTERS)
			{
				modbus_errors |= (1 << MODBUS_ERROR_ILLEGAL_FUNCTION);
			}
			break;
		}
		if (buffer != MODBUS_COMMAND_FORCE_SINGLE_COIL_ADDRESS)	
		{
			modbus_errors |= (1 << MODBUS_ERROR_ILLEGAL_DATA_ADDRESS);
			break;
		}
		if (modbus_rx_buffer[4]	!= 0)											
		{
			modbus_errors |= (1 << MODBUS_ERROR_ILLEGAL_DATA_VALUE);
			break;
		}
		if ((modbus_rx_buffer[5] & (1 << MODBUS_ORDER_START_BKO1)) && (modbus_rx_buffer[1] == MODBUS_COMMAND_FORCE_SINGLE_COIL))
		{
			fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_BKO1_START);
		}
		if ((modbus_rx_buffer[5] & (1 << MODBUS_ORDER_START_REG1)) && (modbus_rx_buffer[1] == MODBUS_COMMAND_FORCE_SINGLE_COIL))
		{
			fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_REG1_START);
		}
		if ((modbus_rx_buffer[5] & (1 << MODBUS_ORDER_STOP_BKO1)) && (modbus_rx_buffer[1] == MODBUS_COMMAND_FORCE_SINGLE_COIL))
		{
			fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP);
		}
		if ((modbus_rx_buffer[5] & (1 << MODBUS_ORDER_STOP_REG1))  && (modbus_rx_buffer[1] == MODBUS_COMMAND_FORCE_SINGLE_COIL))
		{
			fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_REG1_STOP);
		}	
	} while (0);
}

void fsm_modbus_rtu_bu_state_32 (struct bu_shd_r_m_data * bu_shd_r_m)
{
	/*
	if (bu_shd_r_m->error_flags & (1 << ERROR_BKO_OVERLOAD))
	{
		bu_sh_d_modbus_state_param[4] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_OVERHEAT);
	}
	else 
	{
		bu_sh_d_modbus_state_param[4] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_OVERHEAT);
	}
	*/
	bu_sh_d_modbus_state_param[4] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_OVERHEAT); //заглушка пока отд. 122 не придумает что это, сам код выше
	if (bu_shd_r_m->error_flags & (1 << ERROR_T1_OVERHEAT))
	{
		bu_sh_d_modbus_state_param[4] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_T1_OVERHEAT);
	}
	else
	{
		bu_sh_d_modbus_state_param[4] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_T1_OVERHEAT);
	}	
	if (bu_shd_r_m->error_flags & (1 << ERROR_T2_OVERHEAT))
	{
		bu_sh_d_modbus_state_param[4] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_T2_OVERHEAT);
	}
	else
	{
		bu_sh_d_modbus_state_param[4] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_T2_OVERHEAT);
	}
	/*
	if (!(bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1)))
	{
		bu_sh_d_modbus_state_param[4] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_WILL_OFF);
	}
	else
	{
		bu_sh_d_modbus_state_param[4] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_WILL_OFF);
	}
	*/
	if (bu_shd_r_m->system_flags & (1 << SYSTEM_KU)) 
	{
		bu_sh_d_modbus_state_param[4] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_KU_ON);
	}
	else 
	{
		bu_sh_d_modbus_state_param[4] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_KU_ON);
	}
	if (bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1))
	{
		bu_sh_d_modbus_state_param[4] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_ON);
	}
	else
	{
		bu_sh_d_modbus_state_param[4] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_ON);
	}
	if (bu_shd_r_m->system_flags & (1 << SYSTEM_HEATER1))
	{
		bu_sh_d_modbus_state_param[4] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_REG1_ON);
	}
	else 
	{
		bu_sh_d_modbus_state_param[4] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_REG1_ON);
	}
}

void fsm_modbus_rtu_bu_state_10 (struct bu_shd_r_m_data * bu_shd_r_m)
{
	if ((bu_shd_r_m->error_flags & (1 << ERROR_T1_BREAK)) || (bu_shd_r_m->error_flags & (1 << ERROR_T1_SHORT)) || (bu_shd_r_m->error_flags & (1 << ERROR_T2_BREAK)) || (bu_shd_r_m->error_flags & (1 << ERROR_T2_SHORT)))
	{
		bu_sh_d_modbus_state_param[5] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_KU_SENSORS_FAILURE);
	}
	else
	{
		bu_sh_d_modbus_state_param[5] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_KU_SENSORS_FAILURE);
	}
	if ((bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_SENSOR_BREAK)) || (bu_shd_r_m->error_flags & (1 << ERROR_BKO_SENSOR_SHORT)))
	{
		bu_sh_d_modbus_state_param[5] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO_SENSORS_FAILURE);
	}
	else
	{
		bu_sh_d_modbus_state_param[5] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO_SENSORS_FAILURE);
	}
	if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_BREAK))
	{
		bu_sh_d_modbus_state_param[5] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_HEATERS_BREAK);
	}
	else
	{
		bu_sh_d_modbus_state_param[5] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_HEATERS_BREAK);
	}	
	if ((bu_shd_r_m->error_flags & (1 << ERROR_BKO_OVERLOAD)) || (bu_shd_r_m->error_flags & (1 << ERROR_KU_OVERLOAD)))
	{
		bu_sh_d_modbus_state_param[5] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_OVERLOAD);
	}
	else
	{
		bu_sh_d_modbus_state_param[5] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_OVERLOAD);
	}
	if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_BREAK))
	{
		bu_sh_d_modbus_state_param[5] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_HEATER_BREAK);
	}
	else
	{
		bu_sh_d_modbus_state_param[5] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_HEATER_BREAK);	
	}
	if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED))
	{
		bu_sh_d_modbus_state_param[5] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_NOT_CONNECTED);
	}	
	else
	{
		bu_sh_d_modbus_state_param[5] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_BKO1_NOT_CONNECTED);	
	}
	if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED))
	{
		bu_sh_d_modbus_state_param[5] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_ALL_BKO_ARE_DISCONNECTED);
	}
	else 
	{
		bu_sh_d_modbus_state_param[5] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_ALL_BKO_ARE_DISCONNECTED);	
	}
	if (bu_shd_r_m->error_flags & ((1 << ERROR_KU_WRONG_PHASE_SEQUENCE) | (1 << ERROR_KU_PHASE_A) | (1 << ERROR_KU_PHASE_B) | (1 << ERROR_KU_PHASE_C)))
	{
		bu_sh_d_modbus_state_param[5] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_WRONG_PHASE_SEQUENCE);
	}
	else
	{
		bu_sh_d_modbus_state_param[5] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_10_WRONG_PHASE_SEQUENCE);
	}
}

void fsm_modbus_rtu_sensors_state(struct bu_shd_r_m_data * bu_shd_r_m)
{
	if (bu_shd_r_m->error_flags & (1 << ERROR_T1_SHORT))
	{
		bu_sh_d_modbus_state_param[6] |= (1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_SHORT);
	}
	else
	{
		bu_sh_d_modbus_state_param[6] &= ~(1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_SHORT);
	}
	if (bu_shd_r_m->error_flags & (1 << ERROR_T1_BREAK))
	{
		bu_sh_d_modbus_state_param[6] |= (1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_BREAK);
	}
	else
	{
		bu_sh_d_modbus_state_param[6] &= ~(1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_T1_BREAK);
	}	
	if (bu_shd_r_m->error_flags & (1 << ERROR_T2_SHORT))
	{
		bu_sh_d_modbus_state_param[6] |= (1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_SHORT);
	}
	else
	{
		bu_sh_d_modbus_state_param[6] &= ~(1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_SHORT);
	}
	if (bu_shd_r_m->error_flags & (1 << ERROR_T2_BREAK))
	{
		bu_sh_d_modbus_state_param[6] |= (1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_BREAK);
	}
	else
	{
		bu_sh_d_modbus_state_param[6] &= ~(1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_T2_BREAK);
	}
	if (bu_shd_r_m->error_flags & (1 << ERROR_BKO_SENSOR_SHORT))
	{
		bu_sh_d_modbus_state_param[6] |= (1 << MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_SHORT);
	}
	else
	{
		bu_sh_d_modbus_state_param[6] &= ~(1 << MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_SHORT);		
	}
	if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_SENSOR_BREAK))
	{
		bu_sh_d_modbus_state_param[6] |= (1 << MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_BREAK);
	}
	else
	{
		bu_sh_d_modbus_state_param[6] &= ~(1 << MODBUS_TRANS_PARAM_SENS_STATE_BKO1_SENS_BREAK);
	}	
	if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_IT3_NO_CONNECTION))
	{
		bu_sh_d_modbus_state_param[6] |= (1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_IT3_BKO1_NO_CONNECTION);
	}
	else
	{
		bu_sh_d_modbus_state_param[6] &= ~(1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_IT3_BKO1_NO_CONNECTION);
	}
}

void fsm_modbus_rtu_fill_bu_state_param(struct bu_shd_r_m_data * bu_shd_r_m)
{
	bu_sh_d_modbus_state_param[0] = bu_shd_r_m->t1_temperature_grad10;
	bu_sh_d_modbus_state_param[1] = bu_shd_r_m->t2_temperature_grad10;
	if (bu_shd_r_m->it3_temperature == 0)
	{
		bu_sh_d_modbus_state_param[2] = bu_shd_r_m->bko1_temperature_grad10;
	}
	else if (bu_shd_r_m->it3_dot_position)
	{
		bu_sh_d_modbus_state_param[2] = bu_shd_r_m->it3_temperature/10;
	}
	else
	{
		bu_sh_d_modbus_state_param[2] = bu_shd_r_m->it3_temperature;
	}
	bu_sh_d_modbus_state_param[3] = 0;									//bko2
	fsm_modbus_rtu_bu_state_32(bu_shd_r_m);								//bu_sh_d_modbus_state_param[4]
	fsm_modbus_rtu_bu_state_10(bu_shd_r_m);								//bu_sh_d_modbus_state_param[5]
	fsm_modbus_rtu_sensors_state(bu_shd_r_m);							//bu_sh_d_modbus_state_param[6]
	bu_sh_d_modbus_state_param[7] = bu_shd_r_m->operation_time_1000_h;
	bu_sh_d_modbus_state_param[8] = bu_shd_r_m->operation_time_h10;
	bu_sh_d_modbus_state_param[9] = (bu_shd_r_m->production_year << 8) | (bu_shd_r_m->production_month);
	bu_sh_d_modbus_state_param[10] = bu_shd_r_m->serial_number;
	bu_sh_d_modbus_state_param[11] = bu_shd_r_m->programm_version_00;
	bu_sh_d_modbus_state_param[12] = BU_SH_D_R_M;	
	if (!(bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1)))
	{
		bu_sh_d_modbus_state_param[13] = 0;
	}
	else if ((!(bu_shd_r_m->system_flags & (1 << SYSTEM_MO_II_ACTIVE))) || (bu_shd_r_m->bko1_temperature_grad10 < bu_shd_r_m->low_speed_bko_temperature_setting_grad10))
	{
		bu_sh_d_modbus_state_param[13] = bu_shd_r_m->rpm_low_s_selected;
	}
	else
	{
		bu_sh_d_modbus_state_param[13] = bu_shd_r_m->rpm_high_s_selected;
	}							 
}

void fsm_modbus_rtu_slave_disable_programming(void)
{
	DDRG |= (1 << PG4);
	PORTG |= (1 << PG4);
}

void fsm_modbus_rtu_enable_output(struct adm2483brw_data * adm2483brw)
{
	* adm2483brw->transmitter_enable_port |= (1 << adm2483brw->transmitter_enable_pin);
}

void fsm_modbus_rtu_disable_output(struct adm2483brw_data * adm2483brw)
{
	* adm2483brw->transmitter_enable_port &= ~(1 << adm2483brw->transmitter_enable_pin);
}

void fsm_modbus_rtu_rtu_enable_pin_ddr_init(struct adm2483brw_data * adm2483brw)
{
	* (adm2483brw->transmitter_enable_port - 1) |= (1 << adm2483brw->transmitter_enable_pin);
}

void fsm_modbus_rtu_switch_status_after_trancieving(struct adm2483brw_data * adm2483brw)
{
	if (fsm_du_status == MODBUS_STATUS_TRANCIEVING_FINISHED)
	{
		fsm_modbus_rtu_disable_output(adm2483brw);
		fsm_du_status = MODBUS_STATUS_IDLE;
	}
}

void fsm_modbus_rtu_prepare_answer_for_read_input_registers_command(void)
{
	uint8_t n_of_parametres = modbus_rx_buffer[5];
	
	modbus_tx_buffer[0] = modbus_rx_buffer[0];
	modbus_tx_buffer[1] = modbus_rx_buffer[1];
	modbus_tx_buffer[2] = n_of_parametres*2;
	
	for (uint8_t jj = 0; jj < n_of_parametres; jj++)
	{
		modbus_tx_buffer[3+jj*2] = (uint8_t)(bu_sh_d_modbus_state_param[modbus_rx_buffer[3]+jj] >> 8); 
		modbus_tx_buffer[4+jj*2] = (uint8_t)(bu_sh_d_modbus_state_param[modbus_rx_buffer[3]+jj]); 
	}
	crc = usMBCRC16(&modbus_tx_buffer[0], 3 + n_of_parametres * 2);
	modbus_tx_buffer[3 + n_of_parametres * 2] = (uint8_t)crc;
	modbus_tx_buffer[4 + n_of_parametres * 2] = (uint8_t)(crc >> 8);
}

void fsm_modbus_rtu_prepare_answer(void)
{
	if (modbus_errors & (1 << MODBUS_ANSWER_DO_NOT_NEEDED))
	{
		fsm_du_status = MODBUS_STATUS_TRANCIEVING_FINISHED;
	}
	if (modbus_errors && !(modbus_errors & (1 << MODBUS_ANSWER_DO_NOT_NEEDED)))
	{
		modbus_tx_buffer[0] = modbus_rx_buffer[0];
		modbus_tx_buffer[1] = modbus_rx_buffer[0] | (1 << 7);
		modbus_tx_buffer[2] = modbus_errors;
		
		crc = usMBCRC16(&modbus_tx_buffer[0], 3);
		
		modbus_tx_buffer[3] = crc >> 8;
		modbus_tx_buffer[4] = crc & 0xFF;		
	}
	if (!modbus_errors && (modbus_rx_buffer[1] == MODBUS_COMMAND_READ_INPUT_REGISTERS)) 
	{
		fsm_modbus_rtu_prepare_answer_for_read_input_registers_command();
	}
	if (!modbus_errors && (modbus_rx_buffer[1] == MODBUS_COMMAND_FORCE_SINGLE_COIL))
	{
		modbus_tx_buffer[0] = modbus_rx_buffer[0];
		modbus_tx_buffer[1] = modbus_rx_buffer[1];
		modbus_tx_buffer[2] = modbus_rx_buffer[2];
		modbus_tx_buffer[3] = modbus_rx_buffer[3];
		modbus_tx_buffer[4] = modbus_rx_buffer[4];
		modbus_tx_buffer[5] = modbus_rx_buffer[5];
		
		crc = usMBCRC16(&modbus_tx_buffer[0], 6);
		
		modbus_tx_buffer[6] = crc >> 8;
		modbus_tx_buffer[7] = crc & 0xFF;	
	}
}

void fsm_dubna_execute_order_start_bko1(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'S') {break;}
		if (modbus_rx_buffer[6]!= 'T') {break;}
		if (modbus_rx_buffer[7]!= 'A') {break;}
		if (modbus_rx_buffer[8]!= 'R') {break;}
		if (modbus_rx_buffer[9]!= 'T') {break;}
		if (modbus_rx_buffer[10]!= '1') {break;}
		if (dubna_answer != 0) {break;}

		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_BKO1_START);
		dubna_answer = DUBNA_COMMAND_BKO1_START;
	} while (0);
}

void fsm_dubna_execute_order_start_bko2(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'S') {break;}
		if (modbus_rx_buffer[6]!= 'T') {break;}
		if (modbus_rx_buffer[7]!= 'A') {break;}
		if (modbus_rx_buffer[8]!= 'R') {break;}
		if (modbus_rx_buffer[9]!= 'T') {break;}
		if (modbus_rx_buffer[10]!= '2') {break;}
		if (dubna_answer != 0) {break;}
			
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_BKO2_START);
		dubna_answer = DUBNA_COMMAND_BKO2_START;
	} while (0);
}

void fsm_dubna_execute_order_stop_bko1(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'S') {break;}
		if (modbus_rx_buffer[6]!= 'T') {break;}
		if (modbus_rx_buffer[7]!= 'O') {break;}
		if (modbus_rx_buffer[8]!= 'P') {break;}
		if (modbus_rx_buffer[10]!= '1') {break;}
		if (dubna_answer != 0) {break;}
			
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP);
		dubna_answer = DUBNA_COMMAND_BKO1_STOP;
	} while (0);
}

void fsm_dubna_execute_order_stop_bko2(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'S') {break;}
		if (modbus_rx_buffer[6]!= 'T') {break;}
		if (modbus_rx_buffer[7]!= 'O') {break;}
		if (modbus_rx_buffer[8]!= 'P') {break;}
		if (modbus_rx_buffer[10]!= '2') {break;}
		if (dubna_answer != 0) {break;}
			
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_BKO2_STOP);
		dubna_answer = DUBNA_COMMAND_BKO2_STOP;
	} while (0);
}

void fsm_dubna_execute_order_start_reg1(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'R') {break;}
		if (modbus_rx_buffer[6]!= 'E') {break;}
		if (modbus_rx_buffer[7]!= 'G') {break;}
		if (modbus_rx_buffer[8]!= 'O') {break;}
		if (modbus_rx_buffer[9]!= 'N') {break;}
		if (modbus_rx_buffer[10]!= '1') {break;}
		if (dubna_answer != 0) {break;}
			
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_REG1_START);
		dubna_answer = DUBNA_COMMAND_REG1_START;
	} while (0);
}

void fsm_dubna_execute_order_start_reg2(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'R') {break;}
		if (modbus_rx_buffer[6]!= 'E') {break;}
		if (modbus_rx_buffer[7]!= 'G') {break;}
		if (modbus_rx_buffer[8]!= 'O') {break;}
		if (modbus_rx_buffer[9]!= 'N') {break;}
		if (modbus_rx_buffer[10]!= '2') {break;}
		if (dubna_answer != 0) {break;}
			
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_REG2_START);
		dubna_answer = DUBNA_COMMAND_REG2_START;
	} while (0);
}

void fsm_dubna_execute_order_stop_reg1(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'R') {break;}
		if (modbus_rx_buffer[6]!= 'E') {break;}
		if (modbus_rx_buffer[7]!= 'G') {break;}
		if (modbus_rx_buffer[8]!= 'O') {break;}
		if (modbus_rx_buffer[9]!= 'F') {break;}
		if (modbus_rx_buffer[10]!= 'F') {break;}
		if (modbus_rx_buffer[11]!= '1') {break;}
		if (dubna_answer != 0) {break;}
			
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_REG1_STOP);
		dubna_answer = DUBNA_COMMAND_REG1_STOP;
	} while (0);
}

void fsm_dubna_execute_order_stop_reg2(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'R') {break;}
		if (modbus_rx_buffer[6]!= 'E') {break;}
		if (modbus_rx_buffer[7]!= 'G') {break;}
		if (modbus_rx_buffer[8]!= 'O') {break;}
		if (modbus_rx_buffer[9]!= 'F') {break;}
		if (modbus_rx_buffer[10]!= 'F') {break;}
		if (modbus_rx_buffer[11]!= '2') {break;}
		if (dubna_answer != 0) {break;}
			
		fsm_messages_send_broadcast_message(MSG_KEY_PRESSED_REG2_STOP);
		dubna_answer = DUBNA_COMMAND_REG2_STOP;
	} while (0);
}

void fsm_dubna_execute_order_status(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'S') {break;}
		if (modbus_rx_buffer[6]!= 'T') {break;}
		if (modbus_rx_buffer[7]!= 'A') {break;}
		if (modbus_rx_buffer[8]!= 'T') {break;}
		if (modbus_rx_buffer[9]!= 'U') {break;}
		if (modbus_rx_buffer[10]!= 'S') {break;}
		if (dubna_answer != 0) {break;}
		
		dubna_answer = DUBNA_COMMAND_STATUS;
	} while (0);
}

void fsm_dubna_execute_order_time(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'T') {break;}
		if (modbus_rx_buffer[6]!= 'I') {break;}
		if (modbus_rx_buffer[7]!= 'M') {break;}
		if (modbus_rx_buffer[8]!= 'E') {break;}
		if (dubna_answer != 0) {break;}
		
		dubna_answer = DUBNA_COMMAND_TIME;
	} while (0);
}

void fsm_dubna_execute_order_temp(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'T') {break;}
		if (modbus_rx_buffer[6]!= 'E') {break;}
		if (modbus_rx_buffer[7]!= 'M') {break;}
		if (modbus_rx_buffer[8]!= 'P') {break;}
		if (dubna_answer != 0) {break;}
		
		dubna_answer = DUBNA_COMMAND_BKO_TEMP;
	} while (0);
}

void fsm_dubna_execute_order_ctemp(void)
{
	do
	{
		if (modbus_rx_buffer[5]!= 'C') {break;}
		if (modbus_rx_buffer[6]!= 'T') {break;}
		if (modbus_rx_buffer[7]!= 'E') {break;}
		if (modbus_rx_buffer[8]!= 'M') {break;}
		if (modbus_rx_buffer[9]!= 'P') {break;}
		if (dubna_answer != 0) {break;}
		
		dubna_answer = DUBNA_COMMAND_KU_TEMP;
	} while (0);
}


void fsm_dubna_execute_orders(void)
{
	fsm_dubna_execute_order_start_bko1();
	fsm_dubna_execute_order_stop_bko1();
	fsm_dubna_execute_order_start_reg1();
	fsm_dubna_execute_order_stop_reg1();
	fsm_dubna_execute_order_status();
	fsm_dubna_execute_order_time();
	fsm_dubna_execute_order_temp();
	fsm_dubna_execute_order_ctemp();
}

uint8_t fsm_dubna_get_rx_cr_position(void)
{
	uint8_t result = 0;
	for (uint8_t i = 0; i < DUBNA_RX_MAX_SYMBOLS; i++)
	{
		if (modbus_rx_buffer[i] == '>')
		{
			result = i;
		}
	}
	return result;
}

uint8_t fsm_dubna_check_rx_crc_is_ok(void)
{
	uint8_t calculated_cr = 0;
	uint8_t recieved_cr = 0;
	calculated_cr = protocol_dubna_cr(modbus_rx_buffer, (fsm_dubna_get_rx_cr_position()+1));
	switch (modbus_rx_buffer[fsm_dubna_get_rx_cr_position()+1])
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			recieved_cr = (modbus_rx_buffer[fsm_dubna_get_rx_cr_position()+1] - ASCII_TO_INT_DIFFERENTIAL)*16;
			break;
		}
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		{
			recieved_cr = (modbus_rx_buffer[fsm_dubna_get_rx_cr_position()+1] - ASCII_TO_INT_DIFFERENTIAL-7)*16;
			break;			
		}	
	}
	switch (modbus_rx_buffer[fsm_dubna_get_rx_cr_position()+2])
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			recieved_cr = recieved_cr + modbus_rx_buffer[fsm_dubna_get_rx_cr_position()+2] - ASCII_TO_INT_DIFFERENTIAL;
			break;
		}
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		{
			recieved_cr = recieved_cr + modbus_rx_buffer[fsm_dubna_get_rx_cr_position()+2] - ASCII_TO_INT_DIFFERENTIAL-7;
			break;
		}
	}
	if (calculated_cr == recieved_cr)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t fsm_dubna_check_parity_error(void)
{
	if (avr_driver_uart_check_parity_error(0/*номер UART*/))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t fsm_dubna_check_invalid_command_error(void)
{
	char dubna_rx[7];
	const char start2[] = "START2";
	const char stop2[] = "STOP2";
	const char regon2[] = "REGON2";
	const char regoff2[] = "REGOFF2";
	for (uint8_t i = 5; i < fsm_dubna_get_rx_cr_position(); i++)
	{
		dubna_rx[i] = modbus_rx_buffer[i];
	}
	do 
	{ 
		if (!strcmp(dubna_rx, start2)) { return TRUE;}
		if (!strcmp(dubna_rx, stop2)) { return TRUE;}
		if (!strcmp(dubna_rx, regon2)) { return TRUE;}
		if (!strcmp(dubna_rx, regoff2)) { return TRUE;}
	} while (0);
	
	return FALSE;
}

uint8_t fsm_dubna_check_unrecognizeable_command_error(void)
{
	char dubna_rx[7];
	const char start1[] = "START1";
	const char stop1[] = "STOP1";
	const char start2[] = "START2";
	const char stop2[] = "STOP2";
	const char regon1[] = "REGON1";
	const char regoff1[] = "REGOFF1";
	const char regon2[] = "REGON2";
	const char regoff2[] = "REGOFF2";	
	const char status[] = "STATUS";
	const char time[] = "TIME";
	const char temp[] = "TEMP";
	const char ctemp[] = "CTEMP";
	do 
	{
		if (modbus_rx_buffer[0] != '<') {return TRUE;}
		if (modbus_rx_buffer[4] != '/') {return TRUE;}	
		if (modbus_rx_buffer[fsm_dubna_get_rx_cr_position()] != '>') {return TRUE;}	
	} while (0);	
	for (uint8_t i = 5; i < fsm_dubna_get_rx_cr_position(); i++)
	{
		dubna_rx[i] = modbus_rx_buffer[i];
	}
	if (!strcmp(dubna_rx, start1)		|| 
		!strcmp(dubna_rx, stop1)		|| 
		!strcmp(dubna_rx, start2)		|| 
		!strcmp(dubna_rx, stop2)		|| 
		!strcmp(dubna_rx, regon1)		|| 
		!strcmp(dubna_rx, regoff1)		|| 
		!strcmp(dubna_rx, regon2)		||  
		!strcmp(dubna_rx, regoff2)		|| 
		!strcmp(dubna_rx, status)		|| 
		!strcmp(dubna_rx, time)			|| 
		!strcmp(dubna_rx, temp)			|| 
		!strcmp(dubna_rx, ctemp)) 
	{ 
		return TRUE;
	}
	return FALSE;
}

uint8_t fsm_dubna_check_manual_mode_error(void)
{
	//заглушка, ждем когда отд. 122 решит что делать по этому вопросу
	return FALSE;
}

uint8_t fsm_dubna_check_hardware_fault_error(void)
{
	/*
	if (bu_shd_r_m->error_flags)
	{
		return TRUE;
	}
	*/
	if (avr_driver_uart_check_data_overrun(0/*Номер UART*/))
	{
		return TRUE;
	}
	if (avr_driver_uart_check_frame_error(0/*Номер UART*/))
	{
		return TRUE;
	}
	return FALSE;
}

uint8_t fsm_dubna_check_checksum_error(void)
{
	if (fsm_dubna_check_rx_crc_is_ok())
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

uint8_t fsm_dubna_get_error(void)
{
	if (fsm_dubna_check_parity_error())						{dubna_answer = DUBNA_ERROR_PARITY;					return DUBNA_ERROR_PARITY;}
	if (fsm_dubna_check_invalid_command_error())			{dubna_answer = DUBNA_ERROR_INVALID_COMMAND;		return DUBNA_ERROR_INVALID_COMMAND;}
	if (fsm_dubna_check_unrecognizeable_command_error())	{dubna_answer = DUBNA_ERROR_UNRECOGNIZABLE_COMMAND; return DUBNA_ERROR_UNRECOGNIZABLE_COMMAND;}
	if (fsm_dubna_check_manual_mode_error())				{dubna_answer = DUBNA_ERROR_MANUAL_MODE;			return DUBNA_ERROR_MANUAL_MODE;}
	if (fsm_dubna_check_hardware_fault_error())				{dubna_answer = DUBNA_ERROR_HARDWARE_FAULT;			return DUBNA_ERROR_HARDWARE_FAULT;}
	if (fsm_dubna_check_checksum_error())					{dubna_answer = DUBNA_ERROR_CHECK_SUM_FAILURE;		return DUBNA_ERROR_CHECK_SUM_FAILURE;}
		
	return FALSE;
}

uint8_t fsm_dubna_check_order_address(void)
{
	uint8_t check_order_address = 0;
	
	check_order_address = (modbus_rx_buffer[1]- ASCII_TO_INT_DIFFERENTIAL)*100+(modbus_rx_buffer[2]- ASCII_TO_INT_DIFFERENTIAL)*10+(modbus_rx_buffer[3]- ASCII_TO_INT_DIFFERENTIAL);
	if (check_order_address == bu_sh_d_address)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t fsm_dubna_calculate_answer_length(void)
{
	switch (dubna_answer)
	{
		case DUBNA_COMMAND_TIME:
		{
			return 20;
			break;
		}
		case DUBNA_COMMAND_BKO_TEMP:
		{
			return 51;
			break;
		}
		case DUBNA_COMMAND_BKO1_STOP:
		case DUBNA_COMMAND_BKO2_STOP:
		{
			return 15;
			break;
		}
		case DUBNA_COMMAND_KU_TEMP:
		{
			return 37;
			break;
		}
		case DUBNA_COMMAND_BKO1_START:
		case DUBNA_COMMAND_BKO2_START:
		case DUBNA_COMMAND_REG1_START:
		case DUBNA_COMMAND_REG2_START:
		{
			return 16;
			break;
		}
		case DUBNA_COMMAND_STATUS:
		{
			return 20;
			break;
		}
		case DUBNA_COMMAND_REG1_STOP:
		case DUBNA_COMMAND_REG2_STOP:		
		{
			return 17;
			break;
		}
		case DUBNA_ERROR_PARITY:
		{
			return 21;
			break;
		}
		case DUBNA_ERROR_INVALID_COMMAND:
		{
			return 30;
			break;
		}		
		case DUBNA_ERROR_UNRECOGNIZABLE_COMMAND:
		{
			return 37;
			break;
		}
		case DUBNA_ERROR_MANUAL_MODE:
		{
			return 26;
			break;
		}
		case DUBNA_ERROR_HARDWARE_FAULT:
		{
			return 29;
			break;
		}
		case DUBNA_ERROR_CHECK_SUM_FAILURE:
		{
			return 32;
			break;
		}				
	}
	return 0;
}

void fsm_dubna_fill_starting_bytes(void)
{
	modbus_tx_buffer[0] = '{';
	modbus_tx_buffer[1] = modbus_rx_buffer[1];
	modbus_tx_buffer[2] = modbus_rx_buffer[2];
	modbus_tx_buffer[3] = modbus_rx_buffer[3];
	modbus_tx_buffer[4] = modbus_rx_buffer[4];
}

void fsm_dubna_prepare_answer(void)
{
	if (dubna_answer == 0)
	{
		fsm_du_status = MODBUS_STATUS_TRANCIEVING_FINISHED;
	}	
	if (dubna_answer != 0)
	{
		tx_data_length = fsm_dubna_calculate_answer_length();
		fsm_dubna_fill_starting_bytes();
		switch (dubna_answer)
		{
			case DUBNA_ERROR_PARITY:
			{
				modbus_tx_buffer[5] = '?';
				modbus_tx_buffer[6] = 'E';
				modbus_tx_buffer[7] = 'R';
				modbus_tx_buffer[8] = '1';
				modbus_tx_buffer[9] = '_';
				modbus_tx_buffer[10] = 'P';
				modbus_tx_buffer[11] = 'A';
				modbus_tx_buffer[12] = 'R';
				modbus_tx_buffer[13] = 'I';
				modbus_tx_buffer[14] = 'T';
				modbus_tx_buffer[15] = 'Y';
				modbus_tx_buffer[16] = '}';		
				modbus_tx_buffer[17] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 17);
				modbus_tx_buffer[18] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 17);
				modbus_tx_buffer[19] = 13;
				modbus_tx_buffer[20] = 10;
				break;
			}
			case DUBNA_ERROR_INVALID_COMMAND:
			{
				modbus_tx_buffer[5] = '?';
				modbus_tx_buffer[6] = 'E';
				modbus_tx_buffer[7] = 'R';
				modbus_tx_buffer[8] = '2';
				modbus_tx_buffer[9] = '_';
				modbus_tx_buffer[10] = 'I';
				modbus_tx_buffer[11] = 'N';
				modbus_tx_buffer[12] = 'V';
				modbus_tx_buffer[13] = 'A';
				modbus_tx_buffer[14] = 'L';
				modbus_tx_buffer[15] = 'I';
				modbus_tx_buffer[16] = 'D';
				modbus_tx_buffer[17] = '_';
				modbus_tx_buffer[18] = 'C';
				modbus_tx_buffer[19] = 'O';
				modbus_tx_buffer[20] = 'M';
				modbus_tx_buffer[21] = 'M';
				modbus_tx_buffer[22] = 'A';
				modbus_tx_buffer[23] = 'N';
				modbus_tx_buffer[24] = 'D';
				modbus_tx_buffer[25] = '}';
				modbus_tx_buffer[26] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 26);
				modbus_tx_buffer[27] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 26);
				modbus_tx_buffer[28] = 13;
				modbus_tx_buffer[29] = 10;
				break;
			}		
			case DUBNA_ERROR_UNRECOGNIZABLE_COMMAND:
			{
				modbus_tx_buffer[5] = '?';
				modbus_tx_buffer[6] = 'E';
				modbus_tx_buffer[7] = 'R';
				modbus_tx_buffer[8] = '3';
				modbus_tx_buffer[9] = '_';
				modbus_tx_buffer[10] = 'U';
				modbus_tx_buffer[11] = 'N';
				modbus_tx_buffer[12] = 'R';
				modbus_tx_buffer[13] = 'E';
				modbus_tx_buffer[14] = 'C';
				modbus_tx_buffer[15] = 'O';
				modbus_tx_buffer[16] = 'G';
				modbus_tx_buffer[17] = 'N';
				modbus_tx_buffer[18] = 'I';
				modbus_tx_buffer[19] = 'Z';
				modbus_tx_buffer[20] = 'A';
				modbus_tx_buffer[21] = 'B';
				modbus_tx_buffer[22] = 'L';
				modbus_tx_buffer[23] = 'E';
				modbus_tx_buffer[24] = '_';
				modbus_tx_buffer[25] = 'C';
				modbus_tx_buffer[26] = 'O';
				modbus_tx_buffer[27] = 'M';
				modbus_tx_buffer[28] = 'M';
				modbus_tx_buffer[29] = 'A';
				modbus_tx_buffer[30] = 'N';
				modbus_tx_buffer[31] = 'D';
				modbus_tx_buffer[32] = '}';
				modbus_tx_buffer[33] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 33);
				modbus_tx_buffer[34] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 33);
				modbus_tx_buffer[35] = 13;
				modbus_tx_buffer[36] = 10;
				break;
			}
			case DUBNA_ERROR_MANUAL_MODE:
			{
				modbus_tx_buffer[5] = '?';
				modbus_tx_buffer[6] = 'E';
				modbus_tx_buffer[7] = 'R';
				modbus_tx_buffer[8] = '4';
				modbus_tx_buffer[9] = '_';
				modbus_tx_buffer[10] = 'M';
				modbus_tx_buffer[11] = 'A';
				modbus_tx_buffer[12] = 'N';
				modbus_tx_buffer[13] = 'U';
				modbus_tx_buffer[14] = 'A';
				modbus_tx_buffer[15] = 'L';
				modbus_tx_buffer[16] = '_';
				modbus_tx_buffer[17] = 'M';
				modbus_tx_buffer[18] = 'O';
				modbus_tx_buffer[19] = 'D';
				modbus_tx_buffer[20] = 'E';
				modbus_tx_buffer[21] = '}';
				modbus_tx_buffer[22] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 22);
				modbus_tx_buffer[23] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 22);
				modbus_tx_buffer[24] = 13;
				modbus_tx_buffer[25] = 10;
				break;
			}	
			case DUBNA_ERROR_HARDWARE_FAULT:
			{
				modbus_tx_buffer[5] = '?';
				modbus_tx_buffer[6] = 'E';
				modbus_tx_buffer[7] = 'R';
				modbus_tx_buffer[8] = '5';
				modbus_tx_buffer[9] = '_';
				modbus_tx_buffer[10] = 'H';
				modbus_tx_buffer[11] = 'A';
				modbus_tx_buffer[12] = 'R';
				modbus_tx_buffer[13] = 'D';
				modbus_tx_buffer[14] = 'W';
				modbus_tx_buffer[15] = 'A';
				modbus_tx_buffer[16] = 'R';
				modbus_tx_buffer[17] = 'E';
				modbus_tx_buffer[18] = '_';
				modbus_tx_buffer[19] = 'F';
				modbus_tx_buffer[20] = 'A';
				modbus_tx_buffer[21] = 'U';
				modbus_tx_buffer[22] = 'L';
				modbus_tx_buffer[23] = 'T';
				modbus_tx_buffer[24] = '}';
				modbus_tx_buffer[25] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 25);
				modbus_tx_buffer[26] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 25);
				modbus_tx_buffer[27] = 13;
				modbus_tx_buffer[28] = 10;
				break;
			}		
			case DUBNA_ERROR_CHECK_SUM_FAILURE:
			{
				modbus_tx_buffer[5] = '?';
				modbus_tx_buffer[6] = 'E';
				modbus_tx_buffer[7] = 'R';
				modbus_tx_buffer[8] = '6';
				modbus_tx_buffer[9] = '_';
				modbus_tx_buffer[10] = 'C';
				modbus_tx_buffer[11] = 'H';
				modbus_tx_buffer[12] = 'E';
				modbus_tx_buffer[13] = 'C';
				modbus_tx_buffer[14] = 'K';
				modbus_tx_buffer[15] = '_';
				modbus_tx_buffer[16] = 'S';
				modbus_tx_buffer[17] = 'U';
				modbus_tx_buffer[18] = 'M';
				modbus_tx_buffer[19] = '_';
				modbus_tx_buffer[20] = 'F';
				modbus_tx_buffer[21] = 'A';
				modbus_tx_buffer[22] = 'I';
				modbus_tx_buffer[23] = 'L';
				modbus_tx_buffer[24] = 'U';
				modbus_tx_buffer[25] = 'R';
				modbus_tx_buffer[26] = 'E';
				modbus_tx_buffer[27] = '}';
				modbus_tx_buffer[28] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 28);
				modbus_tx_buffer[29] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 28);
				modbus_tx_buffer[30] = 13;
				modbus_tx_buffer[31] = 10;
				break;
			}
			case DUBNA_COMMAND_BKO1_STOP:
			case DUBNA_COMMAND_BKO2_STOP:
			{
				modbus_tx_buffer[5] = modbus_rx_buffer[5];
				modbus_tx_buffer[6] = modbus_rx_buffer[6];
				modbus_tx_buffer[7] = modbus_rx_buffer[7];
				modbus_tx_buffer[8] = modbus_rx_buffer[8];
				modbus_tx_buffer[9] = modbus_rx_buffer[9];
				modbus_tx_buffer[10] = '}';
				modbus_tx_buffer[11] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 11);
				modbus_tx_buffer[12] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 11);			
				modbus_tx_buffer[13] = 13;
				modbus_tx_buffer[14] = 10;
				break;
			}
			case DUBNA_COMMAND_BKO1_START:
			case DUBNA_COMMAND_BKO2_START:
			case DUBNA_COMMAND_REG1_START:
			case DUBNA_COMMAND_REG2_START:
			{
				modbus_tx_buffer[5] = modbus_rx_buffer[5];
				modbus_tx_buffer[6] = modbus_rx_buffer[6];
				modbus_tx_buffer[7] = modbus_rx_buffer[7];
				modbus_tx_buffer[8] = modbus_rx_buffer[8];
				modbus_tx_buffer[9] = modbus_rx_buffer[9];
				modbus_tx_buffer[10] = modbus_rx_buffer[10];
				modbus_tx_buffer[11] = '}';
				modbus_tx_buffer[12] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 12);
				modbus_tx_buffer[13] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 12);
				modbus_tx_buffer[14] = 13;
				modbus_tx_buffer[15] = 10;
				break;
			}
			case DUBNA_COMMAND_REG1_STOP:
			case DUBNA_COMMAND_REG2_STOP:
			{
				modbus_tx_buffer[5] = modbus_rx_buffer[5];
				modbus_tx_buffer[6] = modbus_rx_buffer[6];
				modbus_tx_buffer[7] = modbus_rx_buffer[7];
				modbus_tx_buffer[8] = modbus_rx_buffer[8];
				modbus_tx_buffer[9] = modbus_rx_buffer[9];
				modbus_tx_buffer[10] = modbus_rx_buffer[10];
				modbus_tx_buffer[11] = modbus_rx_buffer[11];
				modbus_tx_buffer[12] = '}';
				modbus_tx_buffer[13] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 13);
				modbus_tx_buffer[14] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 14);
				modbus_tx_buffer[15] = 13;
				modbus_tx_buffer[16] = 10;
				break;
			}
			case DUBNA_COMMAND_STATUS:
			{
				for (uint8_t i = 5; i <= 14; i++)
				{
					modbus_tx_buffer[i] = dubna_answer_status[i-5];
				}
				modbus_tx_buffer[15] = '}';
				modbus_tx_buffer[16] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 16);
				modbus_tx_buffer[17] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 16);
				modbus_tx_buffer[18] = 13;
				modbus_tx_buffer[19] = 10;				
				break;
			}
			case DUBNA_COMMAND_TIME:
			{
				for (uint8_t i = 5; i <= 14; i++)
				{
					modbus_tx_buffer[i] = dubna_answer_time[i-5];
				}
				modbus_tx_buffer[15] = '}';
				modbus_tx_buffer[16] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 16);
				modbus_tx_buffer[17] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 16);
				modbus_tx_buffer[18] = 13;
				modbus_tx_buffer[19] = 10;
				break;				
			}
			case DUBNA_COMMAND_BKO_TEMP:
			{
				for (uint8_t i = 5; i <= 45; i++)
				{
					modbus_tx_buffer[i] = dubna_answer_bko_temp[i-5];
				}
				modbus_tx_buffer[46] = '}';
				modbus_tx_buffer[47] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 47);
				modbus_tx_buffer[48] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 47);
				modbus_tx_buffer[49] = 13;
				modbus_tx_buffer[50] = 10;
				break;
			}
			case DUBNA_COMMAND_KU_TEMP:
			{
				for (uint8_t i = 5; i <= 31; i++)
				{
					modbus_tx_buffer[i] = dubna_answer_ku_temp[i-5];
				}
				modbus_tx_buffer[32] = '}';
				modbus_tx_buffer[33] = protocol_dubna_cr_ascii_high(&modbus_tx_buffer[0], 33);
				modbus_tx_buffer[34] = protocol_dubna_cr_ascii_low(&modbus_tx_buffer[0], 33);
				modbus_tx_buffer[35] = 13;
				modbus_tx_buffer[36] = 10;
				break;
			}			
		}
	}
}

uint8_t fsm_dubna_int_to_ascii(uint8_t number)
{
	if (number <= 9)
	{
		return number + 48;
	}
	else
	{
		return number + 48 + 7;
	}
}

void fsm_dubna_fill_status(struct bu_shd_r_m_data * bu_shd_r_m)
{
	uint8_t buffer = 0;
	
	dubna_answer_status[0] = '0';
	dubna_answer_status[1] = 'x';
	if (bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1))
	{
		buffer |= (1 << 3);
	}
	else
	{
		buffer &= ~(1 << 3);
	}
	if (bu_shd_r_m->system_flags & (1 << SYSTEM_HEATER1))
	{
		buffer |= (1 << 4);
	}
	else
	{
		buffer &= ~(1 << 4);
	}
	dubna_answer_status[2] = fsm_dubna_int_to_ascii(buffer >> 4);
	dubna_answer_status[3] = fsm_dubna_int_to_ascii(buffer & 0xF);
	buffer = 0;
	
	if (bu_sh_d_modbus_state_param[4] & (1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_WILL_OFF))
	{
		buffer |= (1 << 5);
	}
	else
	{
		buffer &= ~(1 << 5);
	}
	if (bu_shd_r_m->error_flags & (1 << ERROR_T2_OVERHEAT))	
	{
		buffer |= (1 << 4);
	}
	else
	{
		buffer &= ~(1 << 4);
	}
	if (bu_shd_r_m->error_flags & (1 << ERROR_T1_OVERHEAT))
	{
		buffer |= (1 << 3);
	}
	else
	{
		buffer &= ~(1 << 3);
	}	
	if (bu_shd_r_m->error_flags & (1 << ERROR_BKO_OVERLOAD))
	{
		buffer |= (1 << 0);
	}
	else
	{
		buffer &= ~(1 << 0);
	}	
	dubna_answer_status[4] = fsm_dubna_int_to_ascii(buffer >> 4);
	dubna_answer_status[5] = fsm_dubna_int_to_ascii(buffer & 0xF);
	buffer = 0;
	
	
	if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_BREAK))
	{
		buffer |= (1 << 0);
	}
	else
	{
		buffer &= ~(1 << 0);
	}
	if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED))
	{
		buffer |= (1 << 3);
	}	
	else
	{
		buffer &= ~(1 << 3);
	}
	if (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_NOT_CONNECTED))
	{
		buffer |= (1 << 6);
	}
	else 
	{
		buffer |= (1 << 6);	
	}
	if (bu_shd_r_m->error_flags & ((1 << ERROR_KU_WRONG_PHASE_SEQUENCE) | (1 << ERROR_KU_PHASE_A) | (1 << ERROR_KU_PHASE_B) | (1 << ERROR_KU_PHASE_C)))
	{
		buffer |= (1 << 7);	
	}
	else
	{
		buffer &= ~(1 << 7);	
	}
	dubna_answer_status[6] = fsm_dubna_int_to_ascii(buffer >> 4);
	dubna_answer_status[7] = fsm_dubna_int_to_ascii(buffer & 0xF);
	buffer = 0;	
	
	if ((bu_shd_r_m->error_flags & (1 << ERROR_T1_BREAK)) || (bu_shd_r_m->error_flags & (1 << ERROR_T1_SHORT)) || (bu_shd_r_m->error_flags & (1 << ERROR_T2_BREAK)) || (bu_shd_r_m->error_flags & (1 << ERROR_T2_SHORT)))
	{
		buffer |= (1 << 1);
	}
	else
	{
		buffer &= ~(1 << 1);
	}
	if ((bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_BKO_SENSOR_BREAK)) || (bu_shd_r_m->error_flags & (1 << ERROR_BKO_SENSOR_SHORT)))
	{
		buffer |= (1 << 2);
	}
	else
	{
		buffer &= ~(1 << 2);
	}
	if (bu_shd_r_m->error_flags & (1 << ERROR_HEATER_BREAK))
	{
		buffer |= (1 << 3);
	}
	else
	{
		buffer &= ~(1 << 3);
	}
	if ((bu_shd_r_m->error_flags & (1 << ERROR_BKO_OVERLOAD)) || (bu_shd_r_m->error_flags & (1 << ERROR_KU_OVERLOAD)))
	{
		buffer |= (1 << 4);
	}
	else
	{
		buffer &= ~(1 << 4);
	}
	dubna_answer_status[8] = fsm_dubna_int_to_ascii(buffer >> 4);
	dubna_answer_status[9] = fsm_dubna_int_to_ascii(buffer & 0xF);
}

void fsm_dubna_fill_time(struct bu_shd_r_m_data * bu_shd_r_m)
{
	uint32_t buffer = (bu_shd_r_m->operation_time_h10+bu_shd_r_m->operation_time_1000_h*1000)*100;

	dubna_answer_time[0] = '0';
	dubna_answer_time[1] = 'x';
	for (uint8_t i = 9; i > 1; i--)
	{
		dubna_answer_time[i] = fsm_dubna_int_to_ascii(buffer%16);
		buffer = buffer/16;	
	}	
}

void fsm_dubna_fill_temp(struct bu_shd_r_m_data * bu_shd_r_m)
{
	int32_t buffer = 0;

	if ((bu_shd_r_m->bko1_temperature_grad10 < 600) && (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_IT3_NO_CONNECTION)))
	{
		buffer = (int32_t)8000*1000;
	}
	if ((bu_shd_r_m->bko1_temperature_grad10 >= 600) && (bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_IT3_NO_CONNECTION)))
	{
		buffer = (int32_t)(bu_shd_r_m->bko1_temperature_grad10);
		buffer = buffer*100;
	}
	if (!(bu_shd_r_m->error_flags & ((uint32_t)1 << ERROR_IT3_NO_CONNECTION)) && (bu_shd_r_m->it3_temperature != 0))
	{
		if (bu_shd_r_m->it3_dot_position)
		{
			buffer = 10*bu_shd_r_m->it3_temperature;
		}
		else
		{
			buffer = 100*bu_shd_r_m->it3_temperature;
		}
	}
	dubna_answer_bko_temp[0] = 'T';
	dubna_answer_bko_temp[1] = '1';
	dubna_answer_bko_temp[2] = '=';
	dubna_answer_bko_temp[3] = '0';
	dubna_answer_bko_temp[4] = 'x';
	if (buffer >= 0)
	{
		for (uint8_t i = 12; i > 4; i--)
		{

			dubna_answer_bko_temp[i] = fsm_dubna_int_to_ascii(abs(buffer)%16);
			buffer = buffer/16;
		}
	}
	else
	{
		for (uint8_t i = 12; i > 4; i--)
		{
			dubna_answer_bko_temp[i] = fsm_dubna_int_to_ascii(abs(buffer)%16);
			
			if ((dubna_answer_ku_temp[i] >=54) && (dubna_answer_ku_temp[i] <=57))
			{
				dubna_answer_bko_temp[i] = 111 - dubna_answer_ku_temp[i];
			}
			else
			{
				dubna_answer_bko_temp[i] = 118 - dubna_answer_ku_temp[i];
			}
			buffer = buffer/16;
		}
	}	
	dubna_answer_bko_temp[13] = '_';
	dubna_answer_bko_temp[14] = 'T';
	dubna_answer_bko_temp[15] = '2';
	dubna_answer_bko_temp[16] = '=';
	dubna_answer_bko_temp[17] = '0';
	dubna_answer_bko_temp[18] = 'x';
	dubna_answer_bko_temp[27] = '_';
	dubna_answer_bko_temp[28] = 'T';
	dubna_answer_bko_temp[29] = '3';
	dubna_answer_bko_temp[30] = '=';
	dubna_answer_bko_temp[31] = '0';
	dubna_answer_bko_temp[32] = 'x';
	for (uint8_t i = 19; i < 27; i++)
	{
		dubna_answer_bko_temp[i] = '0';
	}
	for (uint8_t i = 33; i < 41; i++)
	{
		dubna_answer_bko_temp[i] = '0';
	}
}

void fsm_dubna_fill_ctemp(struct bu_shd_r_m_data * bu_shd_r_m)
{
	int32_t buffer = 0;
	if (bu_shd_r_m->t1_temperature_grad10 == 0x8000 /*PT100_PT300_SHORT*/)
	{
		buffer = (int32_t)-10001*1000;
	}
	else if (bu_shd_r_m->t1_temperature_grad10 == 0x8FFF /*PT100_PT300_BREAK*/)
	{
		buffer = (int32_t)10001*1000;
	}	
	else
	{
		buffer = (int32_t)bu_shd_r_m->t1_temperature_grad10;
		buffer = buffer*100;
	}
	dubna_answer_ku_temp[0] = 'T';
	dubna_answer_ku_temp[1] = '1';
	dubna_answer_ku_temp[2] = '=';
	dubna_answer_ku_temp[3] = '0';
	dubna_answer_ku_temp[4] = 'x';	
	if (buffer >= 0)
	{
		for (uint8_t i = 12; i > 4; i--)
		{

			dubna_answer_ku_temp[i] = fsm_dubna_int_to_ascii(abs(buffer)%16);
			buffer = buffer/16;
		}
	}
	else
	{
		for (uint8_t i = 12; i > 4; i--)
		{
			dubna_answer_ku_temp[i] = fsm_dubna_int_to_ascii(abs(buffer)%16);
			
			if ((dubna_answer_ku_temp[i] >=54) && (dubna_answer_ku_temp[i] <=57))
			{
				dubna_answer_ku_temp[i] = 111 - dubna_answer_ku_temp[i];
			}
			else
			{
				dubna_answer_ku_temp[i] = 118 - dubna_answer_ku_temp[i];
			}
			buffer = buffer/16;
		}
	}		
	dubna_answer_ku_temp[13] = '_';
	if (bu_shd_r_m->t2_temperature_grad10 == 0x8000 /*PT100_PT300_SHORT*/)
	{
		buffer = (int32_t)-10001*1000;
	}
	else if (bu_shd_r_m->t2_temperature_grad10 == 0x8FFF /*PT100_PT300_BREAK*/)
	{
		buffer = (int32_t)10001*1000;
	}
	else
	{
		buffer = (int32_t)bu_shd_r_m->t2_temperature_grad10;
		buffer = buffer*100;
	}	
	dubna_answer_ku_temp[14] = 'T';
	dubna_answer_ku_temp[15] = '2';
	dubna_answer_ku_temp[16] = '=';
	dubna_answer_ku_temp[17] = '0';
	dubna_answer_ku_temp[18] = 'x';
	if (buffer >= 0)
	{
		for (uint8_t i = 26; i > 18; i--)
		{

			dubna_answer_ku_temp[i] = fsm_dubna_int_to_ascii(abs(buffer)%16);
			buffer = buffer/16;
		}	
	}
	else
	{
		for (uint8_t i = 26; i > 18; i--)
		{
			dubna_answer_ku_temp[i] = fsm_dubna_int_to_ascii(abs(buffer)%16);
			
			if ((dubna_answer_ku_temp[i] >=54) && (dubna_answer_ku_temp[i] <=57))
			{
				dubna_answer_ku_temp[i] = 111 - dubna_answer_ku_temp[i];
			}
			else 
			{
				dubna_answer_ku_temp[i] = 118 - dubna_answer_ku_temp[i];
			}
			buffer = buffer/16;
		}	
	}
}

void fsm_dubna_fill_parametres(struct bu_shd_r_m_data * bu_shd_r_m)
{
	fsm_dubna_fill_status(bu_shd_r_m);
	fsm_dubna_fill_time(bu_shd_r_m);
	fsm_dubna_fill_temp(bu_shd_r_m);
	fsm_dubna_fill_ctemp(bu_shd_r_m);
}

/***********************************************************************/
/************************Прерывания*************************************/
/***********************************************************************/

ISR(USART0_RX_vect)
{
	//Обработка приема для Модбас
	if (prot_type == PROT_TYPE_MODBUS)
	{
		if (fsm_du_status == MODBUS_STATUS_IDLE)
		{
			fsm_du_status = MODBUS_STATUS_RECIEVING_DATA;
		}
		if (fsm_du_status == MODBUS_STATUS_RECIEVING_DATA)
		{
			modbus_rx_buffer[modbus_rx_buffer_counter] = avr_driver_uart_receive(0);
			modbus_rx_buffer_counter++;
			if (modbus_rx_buffer_counter == MODBUS_RX_MAX_SYMBOLS)
			{
				fsm_du_status = MODBUS_STATUS_AWAITING_TO_TRANCIEVE_DATA;
				modbus_tx_buffer_counter = 0;
				avr_driver_uart_rx_complete_interrupt_disable(0);
				avr_driver_uart_data_register_empty_interrupt_enable(0);
				fsm_modbus_execute_orders_du_modbus(&bu_shd_r_m);
				if (modbus_rx_buffer[1] == 0x04)
				{
					fsm_modbus_rtu_prepare_answer_for_read_input_registers_command();
				}
				else
				{
					fsm_modbus_rtu_prepare_answer();
				}
			}
		}
	}
	

	//Обработаа приема для Дубны 
	if (prot_type == PROT_TYPE_DUBNA)
	{
		if (fsm_du_status == MODBUS_STATUS_IDLE)
		{
			fsm_du_status = MODBUS_STATUS_RECIEVING_DATA;
		}
		if (fsm_du_status == MODBUS_STATUS_RECIEVING_DATA)
		{
			modbus_rx_buffer[modbus_rx_buffer_counter] = avr_driver_uart_receive(0);
			modbus_rx_buffer_counter++;	
			if ((modbus_rx_buffer_counter >= DUBNA_RX_MAX_SYMBOLS) || (modbus_rx_buffer[modbus_rx_buffer_counter - 4 /*номер символа с конца*/] == '>'))
			{
				fsm_du_status = MODBUS_STATUS_AWAITING_TO_TRANCIEVE_DATA;
				modbus_tx_buffer_counter = 0;
				avr_driver_uart_rx_complete_interrupt_disable(0);
				avr_driver_uart_data_register_empty_interrupt_enable(0);
				do 
				{
					if (!fsm_dubna_check_order_address())	{break;}
					fsm_dubna_get_error();
					fsm_dubna_execute_orders();
					fsm_dubna_prepare_answer();
				} while (0);
			}			
		}
	}
}

ISR(USART0_UDRE_vect)
{
	if (prot_type == PROT_TYPE_MODBUS)
	{
		if (fsm_du_status == MODBUS_STATUS_AWAITING_TO_TRANCIEVE_DATA)
		{
			modbus_time_count++;
			if (modbus_rx_buffer[1] == 0x05)
			{
				tx_data_length = 8;
			}
			if (modbus_rx_buffer[1] == 0x04)
			{
				tx_data_length = 5 + modbus_rx_buffer[5]*2;
			}
		}
		if ((modbus_time_count >= modbus_silent_delay)&& (fsm_du_status == MODBUS_STATUS_AWAITING_TO_TRANCIEVE_DATA))
		{
			fsm_du_status = MODBUS_STATUS_TRANCIEVING_DATA;
			modbus_time_count = 0;
		}
		if (fsm_du_status == MODBUS_STATUS_TRANCIEVING_DATA)
		{
			fsm_modbus_rtu_enable_output(&adm2483brw1_d7);
			avr_driver_uart_transmitt(0, (uint8_t)modbus_tx_buffer[modbus_tx_buffer_counter]);
			modbus_time_count = 0;
			modbus_tx_buffer_counter++;
		}
		if (modbus_tx_buffer_counter > tx_data_length-1)
		{
			avr_driver_uart_rx_complete_interrupt_enable(0);
			avr_driver_uart_data_register_empty_interrupt_disable(0);
			modbus_rx_buffer_counter = 0;
			modbus_time_count = 0;
		}	
	}	
	if (prot_type == PROT_TYPE_DUBNA)
	{
		if (fsm_du_status == MODBUS_STATUS_AWAITING_TO_TRANCIEVE_DATA)
		{
			modbus_time_count++;
		}
		if ((modbus_time_count >= modbus_silent_delay) && (fsm_du_status == MODBUS_STATUS_AWAITING_TO_TRANCIEVE_DATA))
		{
			fsm_du_status = MODBUS_STATUS_TRANCIEVING_DATA;
			modbus_time_count = 0;
			modbus_rx_buffer_counter = 0;
		}
		if (fsm_du_status == MODBUS_STATUS_TRANCIEVING_DATA)
		{
			fsm_modbus_rtu_enable_output(&adm2483brw1_d7);
			avr_driver_uart_transmitt(0,(uint8_t)modbus_tx_buffer[modbus_tx_buffer_counter]);
			modbus_time_count = 0;
			modbus_tx_buffer_counter++;
		}
		if (modbus_tx_buffer_counter > tx_data_length-1)
		{
			avr_driver_uart_rx_complete_interrupt_enable(0);
			avr_driver_uart_data_register_empty_interrupt_disable(0);
			modbus_rx_buffer_counter = 0;
			modbus_time_count = 0;
			dubna_answer = 0;
		}
	}	
}

ISR(USART0_TX_vect)
{
	fsm_du_status = MODBUS_STATUS_TRANCIEVING_FINISHED;
	PORTE &= ~(1 << PE2);									//некрасиво, сдалать потом нормально
}

/***********************************************************************/
/********************Основное функции***********************************/
/***********************************************************************/

void fsm_modbus_rtu_init(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m, uint16_t baudrate, uint8_t transmitter_enable_pin, volatile uint8_t * transmitter_enable_port, uint32_t f_cpu)
{
	prot_type = bu_shd_r_m->du_prot;
	fsm_modbus_rtu_slave_init_variables(bu_shd_r_m);
	if (prot_type == PROT_TYPE_MODBUS)
	{
		hal_adm2483brw_init(adm2483brw, 0, baudrate, AVR_DRIVER_UART_SINGLE_SPEED, AVR_DRIVER_UART_ASYNC_OPERATION_MODE, 2 /*количиество стоп бит*/, 8/*число бит в байте*/, AVR_DRIVER_UART_PARITY_DISABLED, transmitter_enable_pin, transmitter_enable_port, f_cpu);
		modbus_silent_delay = fsm_modbus_calculate_silent_delay(baudrate);		
	}
	if (prot_type == PROT_TYPE_DUBNA)
	{
		hal_adm2483brw_init(adm2483brw, 0, baudrate, AVR_DRIVER_UART_SINGLE_SPEED, AVR_DRIVER_UART_ASYNC_OPERATION_MODE, 1 /*количиество стоп бит*/, 8/*число бит в байте*/, AVR_DRIVER_UART_PARITY_DISABLED, transmitter_enable_pin, transmitter_enable_port, f_cpu);	
		modbus_silent_delay = fsm_modbus_calculate_silent_delay(baudrate);
	}
	fsm_modbus_rtu_slave_disable_programming();
	fsm_modbus_rtu_rtu_enable_pin_ddr_init(adm2483brw);
	avr_driver_uart_rx_complete_interrupt_enable(0);
	avr_driver_uart_data_register_empty_interrupt_disable(0);
	virtual_timers_timer_reset(DU_TIMER);
	
}

void fsm_modbus_rtu_process(struct adm2483brw_data * adm2483brw, struct bu_shd_r_m_data * bu_shd_r_m)
{
	fsm_modbus_rtu_switch_status_after_trancieving(adm2483brw);
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_FINISHED))
	{
		bu_sh_d_modbus_state_param[6] |= (1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_REG1_FINISHED);
	}
	if (fsm_messages_get_broadcast_message(MSG_REGEN1_STARTED))
	{
		bu_sh_d_modbus_state_param[6] &= ~(1 << MODBUS_TRANS_PARAMETR_SENSORS_STATE_REG1_FINISHED);		
	}
	if ((bu_shd_r_m->system_flags & (1 << SYSTEM_BKO1)) && (fsm_messages_get_broadcast_message(MSG_KEY_PRESSED_BKO1_STOP) || fsm_messages_get_broadcast_message(MSG_NEW_ERROR)))
	{
		bu_sh_d_modbus_state_param[4] |= (1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_WILL_OFF);
	}
	else
	{
		bu_sh_d_modbus_state_param[4] &= ~(1 << MODBUS_TRANS_PARAMETR_BU_STATE_32_BKO1_WILL_OFF);
	}
	if (virtual_timers_timer_get(DU_TIMER) >= MODBUS_SURVEY_PERIOD_MS)
	{
		fsm_modbus_rtu_fill_bu_state_param(bu_shd_r_m);
		fsm_dubna_fill_parametres(bu_shd_r_m);
		virtual_timers_timer_reset(DU_TIMER);
	}
}

uint32_t fsm_modbus_rtu_calculate_baud(uint8_t baud)
{
	switch (baud)
	{
		case MODBUS_BAUDRATE_9600:
		{
			return 9600;
			break;
		}
		case MODBUS_BAUDRATE_19200:
		{
			return 19200;
			break;
		}
		case MODBUS_BAUDRATE_38400:
		{
			return 38400;
			break;
		}
		case MODBUS_BAUDRATE_57600:
		{
			return 57600;
			break;
		}
		case MODBUS_BAUDRATE_115200:
		{
			return 115200;
			break;
		}
		default:
		{
			return 0;
			break;
		}
	}
}