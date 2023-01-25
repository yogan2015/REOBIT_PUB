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

 \file      DRV_INTERFACE.c
 \brief     ����� ������ ������ �������������� ������ � ������ ������ (������, �������).
 //��������������, ��� ������ ����� ��������� ���������������� (��������� ����-�� ������ ������)...
 //���������� ��� ������������:
  	1.��� ������ ���������� �� ���� � ������������������� ��������� (������,, ������ � �.�.) ����� ���������� ������� ���� ans_data ������ ���� ����������� ��������� �������:
  	  	  p->ans_data = temp;
  	  ��� ������� ������� �������, ��� ������ ���������. � ���� ������ ���� p->ans_data ���������� ������� ������������������ �������� ����� ����� ���������� � �����
  	     p->data_Low
		  p->data_High
	2.��� ���������� ������� ���� p->ans_data ������� �� �����
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.1 2017_07_24

 */


#include "main.h"
void DRV_INTERFACE_Calc(TDrvInterface *p) {
	TEvent event;

	long temp = (p->req_data); //�������� �������

	p->INTERFACE_delta_time_sec = global_time.relative_time1.second_counter - p->INTERFACE_time_sec;
	// �������� "�����" ������
	if ((p->ans_data != 0) && (p->INTERFACE_delta_time_sec < DRV_INTERFACE_RESET_TIME))
		return;

	//��� ���� ������ ������ ���� ������� ��� ���� �����, ���� �� �������
	//� ����� ������ ��� ��������
	p->ans_data = 0;
	//������ �������� ������ ����� ����������, ����� ������� ���������� ����� ���������� ���������� �������
	switch ((temp) >> 16)
	{
		case DATA_REQUEST_READ_FAULT:  //������ �� ������ ������
		{
			FaultLog.read(&FaultLog, (temp & 0x0FFFF), &event);
			//��������� �����
			p->data_Low = (((Uint32) (event.ev_num)) << 16) + event.ev_code;
			p->data_High = event.ev_time;

			p->ans_data = temp; //������� �������, ��� ������� ����������
			//��������� ����� ������
			p->INTERFACE_time_sec = global_time.relative_time1.second_counter;
			break;
		}
		case DATA_REQUEST_WRITE_FAULT:  //������ �� ������ ������
		{
			//!!!
			//���� ����� ��������� ������ ������ ������
			break;
		}
		case DATA_REQUEST_WRITE_WORK_TIME:  //������ �� ������ work_time
		{
			global_time.relative_time1.relative_date.hour = 0;
			global_time.relative_time1.relative_date.minute = 0;
			global_time.WtiteSPI_flag = 1;

			break;
		}
		case DATA_REQUEST_READ_WORK_TIME:  //������ �� ������ work_time
		{
			//Ma][: ��!
			break;
		}
		case DATA_REQUEST_WRITE_OPER_TIME: {  //������ �� ������ oper_time
			global_time.relative_time2.relative_date.hour = 0;
			global_time.relative_time2.relative_date.minute = 0;
			global_time.WtiteSPI_flag = 1;

			break;
		}
		case DATA_REQUEST_READ_OPER_TIME:  //������ �� ������ ������
		{
			//Ma][: ��!
			break;
		}
		case DATA_REQUEST_CLEAR_ALL:  //������ �� ������� ����� ������
		{
			FaultLog.clear(&FaultLog);
			//��������� �����
			p->data_High = 0;
			p->data_Low = 0;

			p->ans_data = temp; //������� �������, ��� ������� ����������
			//��������� ����� ������
			p->INTERFACE_time_sec = global_time.relative_time1.second_counter;
			break;
		}
	}

	p->req_data = 0;//�������� ���� �������, ����� �� ��������� ��� ��������
}

