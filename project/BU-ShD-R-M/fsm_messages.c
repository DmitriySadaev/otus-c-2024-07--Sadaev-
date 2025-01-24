/*! 
  \file
  \defgroup		fsm_messages
  \brief		���� ��������� ���� ��������� fsm_messages.c
  \author		������ �.�.
 
  ���� ��������� ���� �������� � ���� �������� �������, ������������ � �������� ���������.
  �������� ��� ������������ �� ���� ����������� ������ ��������� ���������, ������������ ��� ���������� ��������� �� ������ �������� ���������
 
  - Compiler:           GNU AVR toolchain
  - Reference:			������������ �.�. ���������� SWITCH-���������� ��� ����������
  					    ����������� ������������ ����������� ��� �����������������. ����� 2. / �.�.
  						������������ / ���������� � ����������. - 2006. - �12.         
*/


#include "fsm_messages.h"

uint8_t messages[MAX_MESSAGES];
uint8_t broadcast_messages[MAX_BROADCAST_MESSAGES];

void fsm_messages_init(void)
{
	for (uint8_t i = 0; i < MAX_MESSAGES; i++)
	{
		messages[i] = MESSAGE_NOT_ACTIVE;
	}
}

void fsm_messages_send_message(uint8_t message)
{
	messages[message] = MESSAGE_SET;
}

void fsm_messages_send_broadcast_message(uint8_t message)
{	if (broadcast_messages[message] != MESSAGE_ACTIVE)
	{
		broadcast_messages[message] = MESSAGE_SET;	
	} 
}

void fsm_messages_process(void)
{
	for (uint8_t i = 0; i < MAX_MESSAGES; i++)
	{
		if (messages[i] == MESSAGE_ACTIVE)
		{
			messages[i] = MESSAGE_NOT_ACTIVE;			
		}
		if (messages[i] == MESSAGE_SET)
		{
			messages[i] = MESSAGE_ACTIVE;
		}
	}	
	for (uint8_t i = 0; i < MAX_BROADCAST_MESSAGES; i++)
	{
		if (broadcast_messages[i] == MESSAGE_ACTIVE)
		{
			broadcast_messages[i] = MESSAGE_NOT_ACTIVE;
		}
		if (broadcast_messages[i] == MESSAGE_SET)
		{
			broadcast_messages[i] = MESSAGE_ACTIVE;
		}
	}
}

uint8_t fsm_messages_get_message(uint8_t message)
{
	if (messages[message] == MESSAGE_ACTIVE)
	{
		messages[message] = MESSAGE_NOT_ACTIVE;
		return MESSAGE_RECIEVED;
	}
	else
	{
		return MESSAGE_NOT_RECIEVED;
	}
}

uint8_t fsm_messages_get_broadcast_message(uint8_t message)
{
	if (broadcast_messages[message] == MESSAGE_ACTIVE)
	{
		return MESSAGE_RECIEVED;
	}
	else
	{
		return MESSAGE_NOT_RECIEVED;
	}
}