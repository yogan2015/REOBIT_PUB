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

 \file      DRV_INTERFACE.h
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
// ������ ������������� � ������ main
#ifndef DRV_INTERFACE_H
#define DRV_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif

#define DRV_INTERFACE_RESET_TIME 10	//�������� � ��� ����� ���������� ��������� Ans_Data

//!������ �� ������ ������
#define DATA_REQUEST_READ_FAULT 1
//!������ �� ������ ������
#define DATA_REQUEST_WRITE_FAULT 2
//!������ �� ������ �������� �������
#define DATA_REQUEST_WRITE_WORK_TIME 3
//!������ �� ������ �������� �������
#define DATA_REQUEST_READ_WORK_TIME 4
#define DATA_REQUEST_WRITE_OPER_TIME 5
//!������ �� ������ ������� �� ���������� ���������
#define DATA_REQUEST_READ_OPER_TIME 6
//!������� �����
#define DATA_REQUEST_CLEAR_ALL 10


  struct SDrvInterface
  {
    long req_data;
    long ans_data;
    long data_High;
    long data_Low;

    long INTERFACE_time_sec;//!<
    long INTERFACE_delta_time_sec;//!<
    void (*calc)(struct SDrvInterface*);
  };

  typedef struct SDrvInterface TDrvInterface;

#define DRV_INTERFACE_DEFAULTS {0,0,0,0,\
    0,0,\
    DRV_INTERFACE_Calc,\
  }

  void DRV_INTERFACE_Calc(TDrvInterface*);

#ifdef __cplusplus
}
#endif

#endif


