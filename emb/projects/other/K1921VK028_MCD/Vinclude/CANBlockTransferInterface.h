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

 \file      CANBlockTransferInterface.h
 \brief     ������� �������� ������ ��� CANopen
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  CANOpen_drv ������� CANOpen
 @{
*/
#ifndef CANBLOCKTRANS_INTERFACE_H
#define CANBLOCKTRANS_INTERFACE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "DSP.h"

#define CANBT_INTERFACE_FREE 0
#define CANBT_INTERFACE_BUSY 0x8000
#define CANBT_INTERFACE_FLASH_PROG  1
#define CANBT_INTERFACE_DATALOG1  	2
#define CANBT_INTERFACE_DATALOG2  	3	// ������������ ��� 32-������� �����������

struct SCanBTInterface{
		Uint16 alreadyInit;	//������� ������� ������ ���������� ��������.
	    Uint16 state_shadow;//������� ���������.
	    Uint16 state_prev;	//���������� ������� (�� ���� ����)
	    Uint16 E;			//���� ������� ���������.
	    Uint32 time_prev;
	    Uint64 state_time;	//����� ���������� � ������� ���������, � ����� �����. ��� 150��� ������������ ����� ����� 4���. ��� :)
		Uint16 BlockTransferCommand;
		void (*ms_calc)(volatile struct SCanBTInterface* p, Uint32 time, TCo_OdVars* co_ptr);
		void (*slow_calc)(volatile struct SCanBTInterface* p);
		};

typedef volatile struct SCanBTInterface TCanBTInterface;

#define T_CANBT_INTERFACE_DEFAULTS {0,CANBT_INTERFACE_FREE,0xFF,1,\
									 0,0,0,\
									 SMCanBTInterface_ms,\
									SMCanBTInterface_slow}

void SMCanBTInterface_ms(volatile struct SCanBTInterface* p, Uint32 time, TCo_OdVars* co_ptr);
void SMCanBTInterface_slow(volatile struct SCanBTInterface* p);

//������� ��� 2700.00
void callback_BTcmd(Uint16 par, Uint16 tag_CANnum);

#ifdef __cplusplus
}
#endif

#endif
