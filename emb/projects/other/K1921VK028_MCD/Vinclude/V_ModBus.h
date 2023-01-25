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

 \file      V_ModBus.h
 \brief     ������� ModBus (��. TModBus)
 \author	Alecksey Anuchin
 \version   v 1.1 24/03/2017
 \defgroup  V_ModBus ������� ModBus (��. TModBus)
 @{
*/

#ifndef V_MODBUS_H
#define V_MODBUS_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "mbod.h"


#define MODBUS_MAX_RX_COUNT 10

/*! \class TModBus
      \brief ������� ModBus

      ����� \a TModBus, ���������� �� ��������� SModBus, ������������
      �������� ������� �� RS-485 ��� ������� ModBus (RTU). */

//! ��. TModBus


 //! ��������� modbus ��� �������� ���������� ������
 typedef struct {volatile Uint16 In[MODBUS_MAX_RX_COUNT];//!<������ ��� �������� ������
 				volatile Uint16 InCount;//!<������� ��� ������� �������� ������
 				volatile MB_Record /*const*/ *Addr;//!<��������� �� �������
 				volatile Uint16 TimeOut;//!<������� �������, ������� ���� �����������
 				volatile Uint16 TimeOut1_5;//!<������������ ������� 1,5 ����� ����������� �����
 				volatile Uint16 TimeOut2_5;//!<������������ ������� 2,5 ����� ����������� �����
 				volatile Uint16 ToSend;//!<������ ��� ��������
 				volatile Uint16 NumOfHRs;//!<���������� Holding Registers
 				volatile Uint16 MiddleOfHRs;//!<�������� Holding Registers
 				volatile Uint16 InitialStepOfHRs;//!<��� Holding Registers
 				volatile Uint16 NumOfIRs;//!<���������� Input Registers
 				volatile Uint16 MiddleOfIRs;//!<�������� Input Registers
 				volatile Uint16 InitialStepOfIRs;//!<��� Input Registers
 				volatile Uint16 NumOfCs;//!<���������� Coils
 				volatile Uint16 MiddleOfCs;//!<�������� Coils
 				volatile Uint16 InitialStepOfCs;//!<��� Coils
 				volatile Uint16 NumOfDIs;//!<���������� Discrete Inputs
 				volatile Uint16 MiddleOfDIs;//!<�������� Discrete Inputs
 				volatile Uint16 InitialStepOfDIs;//!<��� Discrete Inputs
 				volatile Uint16 RxCRC;//!<����������� ����������� �����
 				volatile Uint16 TxCRC;//!<������������ ����������� �����
 				volatile Uint16 MagicNumber;//!<��...
 				volatile int16 TxState;//!<��������� ��������
 				volatile Uint16 temp;//!<
 				volatile int16 RecievedCounter;//!<������� ��� ����������� �������� �� ������
 				UART_TypeDef *NT_UART;//!��������� �� ������������ ������ UART
 				} MODBUS_INT;

 #define MODBUS_INT_DEFAULTS {{0},0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
 				0xFFFF,0xFFFF, 0xA001,-1, 0,0,  \
 				}

struct SModBus{Uint32 BaudRate;//!<�������� ������ �� RS
				Uint16 ExecutionFreq;//!< ������� ������������ ������
				Uint16 RSNodeID; //!< ����� ���� � ����
				Uint16 Enabled; //!< ���������� ��������� ���������� ������� ����� ModBus
				Uint16 Refresh;	//!< ���� ��������� ���������� �� Modbus
				int16 error;
				int16 errorCode;
				int16 AutoRestart;
				int16 clear_error;
				Uint16 received_data;
				Uint16 GPIOsValue;
				Uint16 isOnline;//!< � ���� �� ��� ��� (���� �� ������)
				Uint32 OfflineCounter;//!< ������� ���������������� � �������� ������ ��������� ModBus_Execute � ����������, ���� � ���� ���� ������
				Uint32 OfflineCounterMax;//!< ������� ���������� ������� � ���� (� �������� ����� OfflineCounter)
				Uint16 ReceiveByteCounter;//!< ������� �������� ����
                Uint16 ReceivePacketCounter;//!< ������� �������� �������
                MODBUS_INT MBInternals;//!< ��������� ���������� ��� ������ �������� (�� ��� ������������)
                void (*Init)(volatile struct SModBus*);
                void (*Execute)(volatile struct SModBus*);
                };


typedef volatile struct SModBus TModBus;


#define MODBUS_DEFAULTS {9600,10000, 0x01, 1, 0,\
				0,0,0,0,0,0,0,0,0,0,0,\
				MODBUS_INT_DEFAULTS,\
                ModBus_Init, \
                ModBus_Execute,\
                }


//! \memberof TModBus
void ModBus_Init(TModBus *p);
//! \memberof TModBus
void ModBus_Execute(TModBus *p);
//! \memberof TModBus
int16 ModBus_FindVocAddr(TModBus *p,volatile MB_Record Table[], Uint16 TableSize, int16 Type, Uint16 Index, int16 NumOfIndexs, int16 Mid, int16 Step);



#ifdef __cplusplus
}
#endif

#endif

/*@}*/
