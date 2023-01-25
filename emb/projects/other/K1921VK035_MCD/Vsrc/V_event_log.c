/*!
     Copyright 2017 	�� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_event_log.c
 \brief     ���������� ������� � ������� ������������� � �����
			������������ ������� ������ � ����������������� �������
			������� ����� init(); ������ ���� ����� ������������� �����
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 2009_01_20

*/

/** \addtogroup W_event_log */
/*@{*/
#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>


	//!<���������������� ������

//��������� ������ ������� � ����������������� ������ ����� ������ (������� � ���������� I2C-����������
//� ������� ������� ������, ������������ �� I2C � �������� ������).
//������� �������� ������ �����:
//���� ����� ��������� ������ [Logger_Event_Read] (������ ��������� ������ �� ����� �� ���������) -
//��� �������� � ������� ����� �������� �� �����.
//���� ����� �������� ������ � ���� [Logger_Event_Write] - � ���������� (��������, 1��) ������ ������ ������� � FIFO;
//����� � ������� ����� [Logger_Background_Calc] ������ �������� �� FIFO [Event_FIFO_Read]
//(�� ���� �� 1 ������� ����) � ������� � �����.


//��������� ������� �� FIFO (��� ���������� ������ � �����).
Uint16 Event_FIFO_Read(TEventFIFO* p,TEvent* ev)
{
	if (p->busy_flag > 0) return EVENT_FIFO_BUSY;
	//���������� ������ ������ � FIFO
	p->busy_flag = 1;
	if (p->number_of_msgs == 0)
	{
		//����������� ���� ������ � FIFO
		p->busy_flag = 0;
		return EVENT_FIFO_EMPTY;
	}
	//������ ������ �� FIFO
	ev->ev_code = p->msg_array[(p->read_ptr)].ev_code;
	ev->ev_time = p->msg_array[(p->read_ptr)].ev_time;
	ev->ev_num = p->msg_array[(p->read_ptr)].ev_num;
	//���������� FIFO � ���������� ������
	p->read_ptr++;
	if (p->read_ptr >= p->size) p->read_ptr = 0;
	p->number_of_msgs--;
	//����������� ���� ������ � FIFO
	p->busy_flag = 0;
	return EVENT_FIFO_SUCCESSFUL;
}



//�������� ������� � FIFO (���������� � Logger_Event_Write, � ����������)
Uint16 Event_FIFO_Write(TEventFIFO* p,TEvent* ev)
{
	if (p->busy_flag > 0) return EVENT_FIFO_BUSY;
	//���������� ������ ������ � FIFO
	p->busy_flag = 1;
	if (p->number_of_msgs == p->size)
	{
		//����������� ���� ������ � FIFO
		p->busy_flag = 0;
		return EVENT_FIFO_FULL;
	}
	//���������� ������ � FIFO
	p->msg_array[(p->write_ptr)].ev_code = ev->ev_code;
	p->msg_array[(p->write_ptr)].ev_time = ev->ev_time;
	p->msg_array[(p->write_ptr)].ev_num = ev->ev_num;
	//���������� FIFO � ���������� ������
	p->write_ptr++;
	if (p->write_ptr >= p->size)p->write_ptr = 0;
	p->number_of_msgs++;
	//����������� ���� ������ � FIFO
	p->busy_flag = 0;
	return EVENT_FIFO_SUCCESSFUL;
}

//������������� (���� ���� ����� ������� - ��� ������ FFFF, ������� ���)
void Logger_Init(TLogger* p,Uint16 BS,Uint16 SA,Uint32* tptr)
{
	TEvent tmp;
	Uint16 i;
	Uint16 last_log_num = 0;
	Uint16 last_log_index = 0;
	//�������������� ���������� ����������
	p->SPI_buf_size = BS;
	p->SPI_start_addr = SA;
	p->time_ptr = tptr;

	//����� ����� �������������� ����� � ����� - ����� ���������
	UserMem.MemStartAddr = p->SPI_start_addr;
	UserMem.data_length = 0;
	for (i=0;i<p->SPI_buf_size;i++)
	{
		//������ �����
		UserMem.MemStartAddr += UserMem.data_length;
		UserMem.MCUStartAddr = (Uint16*)(&tmp.ev_num);
		UserMem.data_length = LOG_NUM_LENGTH;
		UserMem.read(&UserMem);
		//������ �����
		UserMem.MemStartAddr += UserMem.data_length;
		UserMem.MCUStartAddr = (Uint16*)(&tmp.ev_time);
		UserMem.data_length = LOG_TIME_LENGTH;
		UserMem.read(&UserMem);
		//������ ���
		UserMem.MemStartAddr += UserMem.data_length;
		UserMem.MCUStartAddr = (Uint16*)(&tmp.ev_code);
		UserMem.data_length = LOG_CODE_LENGTH;
		UserMem.read(&UserMem);

		//������ ����������� ��������
		//���� ��� ���� 0xFFFF, �� ������ ��� ������
		if ((tmp.ev_num == 0xFFFF) && (tmp.ev_time == 0xFFFFFFFF) && (tmp.ev_code == 0xFFFF))
		{
			//������
			p->clear(p);
			//�������������� ����������
			p->INTERNAL_last_log_num = 0;
			p->INTERNAL_last_log_index = 0;
			return;
		}
		//���� ��������� ������
		if (last_log_num < tmp.ev_num)
		{
			last_log_num = tmp.ev_num;
			last_log_index = i;
		}
	}
	p->INTERNAL_last_log_num = last_log_num;
	p->INTERNAL_last_log_index = last_log_index;
}

//������� ������� ������ � �����
void Logger_Clear(TLogger* p)
{
	Uint16 zero = 0;
	UserMem.MemStartAddr = p->SPI_start_addr;
	UserMem.MCUStartAddr = (Uint16*)(&zero);
	UserMem.data_length = 1;
	for (int i=0;i<(p->SPI_buf_size * (LOG_LENGTH));i++)
	{
		UserMem.write(&UserMem);
		UserMem.MemStartAddr++;
	}
	p->INTERNAL_last_log_index = 0;
	p->INTERNAL_last_log_num = 0;
}


//������� ������� ������ ������� � FIFO
Uint16 Logger_Event_Write(TLogger* p,Uint16 code)
{
	TEvent event;
	//��������� ������
	__disable_irq();
	event.ev_time = *(p->time_ptr);
	event.ev_code = code;
	event.ev_num = ++p->INTERNAL_last_log_num;
	p->INTERNAL_last_log_code = code;
	__enable_irq();
	//����� � FIFO
	return p->FIFO.write((struct SEventFIFO*)&(p->FIFO),(TEvent*)&event);
}

//��������� ������ �� �����, ������� ������ � TEvent* event
void Logger_Event_Read(TLogger* p,Uint16 shift_index,TEvent* event)
{
	Uint16 correction = 0;
	//��������� ������������ �������
	if (shift_index > (p->SPI_buf_size - 1)) return;

	//���� ��������� ��� ����������� ������
	if (((int16)p->INTERNAL_last_log_index - (int16)shift_index) < 0) correction = p->SPI_buf_size;
	//������ ������
	UserMem.MemStartAddr = p->SPI_start_addr + ((p->INTERNAL_last_log_index - shift_index + correction)*(LOG_LENGTH));
	UserMem.MCUStartAddr = (Uint16*)(&(event->ev_num));
	UserMem.data_length = LOG_NUM_LENGTH;
	UserMem.read(&UserMem);
	//������ �������
	UserMem.MemStartAddr += UserMem.data_length;
	UserMem.MCUStartAddr = (Uint16*)(&(event->ev_time));
	UserMem.data_length = LOG_TIME_LENGTH;
	UserMem.read(&UserMem);
	//������ ����
	UserMem.MemStartAddr += UserMem.data_length;
	UserMem.MCUStartAddr = (Uint16*)(&(event->ev_code));
	UserMem.data_length = LOG_CODE_LENGTH;
	UserMem.read(&UserMem);
}

//������� ��������� FIFO � ������ ������ � �����. ���� � FIFO ���-�� ����� - ������� �� ������.
//���� FIFO ������ ��� ������ - ��������.
void Logger_Background_Calc(TLogger* p)
{
	Uint16 ret;
	TEvent event;
	//����� �� ������ ������������� ������� ���� ����� ���������� �� 1 ������ �� ���
	ret = p->FIFO.read((struct SEventFIFO*)&(p->FIFO),(TEvent*)&event);
	if (ret == EVENT_FIFO_SUCCESSFUL)
	{
		//����� � �����
		if (p->INTERNAL_last_log_index >= (p->SPI_buf_size - 1)) p->INTERNAL_last_log_index = 0;
		else p->INTERNAL_last_log_index++;

		//������ ������
		UserMem.MemStartAddr = p->SPI_start_addr + (p->INTERNAL_last_log_index)*(LOG_LENGTH);
		UserMem.MCUStartAddr = (Uint16*)(&(event.ev_num));
		UserMem.data_length = LOG_NUM_LENGTH;
		UserMem.write(&UserMem);
		//������ �������
		UserMem.MemStartAddr += UserMem.data_length;
		UserMem.MCUStartAddr = (Uint16*)(&(event.ev_time));
		UserMem.data_length = LOG_TIME_LENGTH;
		UserMem.write(&UserMem);
		//������ ����
		UserMem.MemStartAddr += UserMem.data_length;
		UserMem.MCUStartAddr = (Uint16*)(&(event.ev_code));
		UserMem.data_length = LOG_CODE_LENGTH;
		UserMem.write(&UserMem);
	}
}

//������� �������� � ������ ������� � ������ ������ ������ ������
//��������������� ��������� ������ ��� ���� ������ �, ���� �� �������, �� ��� �� �������, ������������ ������.
void Logger_ms_Calc(TLogger* p){

}

#ifdef __cplusplus
} // Extern "C"
#endif
/*@}*/
