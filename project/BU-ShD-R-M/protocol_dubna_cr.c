#include "protocol_dubna_cr.h"

uint8_t protocol_dubna_cr(uint16_t * dubna_frame, uint8_t dubna_frame_length)
{
	uint16_t result = 0;
	
	for(volatile uint8_t i = 0; i < dubna_frame_length; i++)
	{
		result = result + *(dubna_frame+i);
	}
	
	result = result % DUBNA_CR_MOD;
	
	return (uint8_t)result;
}

uint8_t protocol_dubna_cr_ascii_high(uint16_t * dubna_frame, uint8_t dubna_frame_length)
{
	uint8_t result = 0;
	result = protocol_dubna_cr(dubna_frame, dubna_frame_length);
	result = result/16;
	if (result <= 9)
	{
		result = result + 48;
	} 
	else
	{
		result = result + 48+7;
	}
	return result;
}

uint8_t protocol_dubna_cr_ascii_low(uint16_t * dubna_frame, uint8_t dubna_frame_length)
{
	uint8_t result = 0;
	result = protocol_dubna_cr(dubna_frame, dubna_frame_length);
	result = result%16;
	if (result <= 9)
	{
		result = result + 48;
	}
	else
	{
		result = result + 48+7;
	}
	return result;
}