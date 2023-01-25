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

 \file      v_CANtoRS.h
 \brief     ��������������� ������� CAN � RS/USB � �������. ��������
��������� � ��������� CANOpen

 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 3.0 08/08/2017

*/

#ifndef V_CAN_TO_RS_H
#define V_CAN_TO_RS_H

#ifdef __cplusplus
extern "C" {
#endif

#define CANTORS_BUFSIZE 20
#define CANTORS_TRANSM_TIME_OUT 10
#define CANTORS_READ_DATA_MAX_LEN 10
#define CANTORS_HEART_COUNTER_MAX 1000


#define CANTORS_ACTIVE		0x1
#define CANTOUSB_ACTIVE		0x2

#include "DSP.h"
#include "CANOpen_drv.h"

struct SCANtoRS {
                Uint16 APIpacketMode;
                int16 HeartBeatGo;//���������� ������������!
                Uint16 callback_go; //���� ��� ������ callback
                Uint16 PacketInWait; //���� ���� ���� ���-�� � ������ ��������
                Uint16 HeartCounter; //������� ��� �������� HeartBeat
                Uint16 ReadPackDataCounter; //������� ������ � ������
                Uint16 ReadCRCCounter; //������� ������ � ������
                Uint16 all_len; //transmit buf len
                Uint16 tr_counter; //transmit counter
				Uint16 MessDrop1;
				Uint16 MessDrop2;
				Uint16 MessDrop3;
				Uint16 CounterWrongCRC;
				Uint16 CounterRes;
				Uint16 CounterSended;
				void (*init)(volatile struct SCANtoRS *);     /* Pointer to the init function */
				void (*calc)(volatile struct SCANtoRS *);     /* Pointer to the calc function */
                void (*receive)(volatile struct SCANtoRS *);
                Uint16 (*write)(TZCanMsg* MSG,volatile struct SCANtoRS *);
                void (*callback)(TCo_OdVars* ppc, TZCanMsg* p);        
                unsigned char buf_out[CANTORS_BUFSIZE];
				TZCanMsg MSG;
				TZCanMsg bufMSG;
				Uint16 ReadPackData[CANTORS_BUFSIZE]; //����� ��� API �������
				Uint16 ReadCRC[2]; //����� ��� �RC
				Uint16 TempData[10];
				Uint16* nodeID;
				UART_TypeDef *UART;//!��������� �� ������������ ������ UART
				};

typedef volatile struct SCANtoRS TCANtoRS;


void CANtoRS_init(TCANtoRS*);
void CANtoRS_calc(TCANtoRS*);
void  CANtoRS_Receive(TCANtoRS*);
Uint16 CANtoRS_SendP(Uint16* Data, int16 len,TCANtoRS *p);
Uint16 CANtoRS_Write(TZCanMsg* MSG,TCANtoRS *p);
Uint16 CANtoRS_WriteHelper(TZCanMsg* MSG,TCANtoRS *p);
void CANtoRS_HeartBeat(TCANtoRS *p);
Uint16 CANtoRS_C_CRC(TCANtoRS *p,Uint16 *Data,Uint16 len);
void CANtoRS_Analysis(TCANtoRS*);


//���� ��������� � �������� ���������� �� ��������� �������� �� ���������
#define CAN_TO_RS_DEFAULTS { .init = CANtoRS_init,\
							 .calc = CANtoRS_calc,\
							 .receive = CANtoRS_Receive,\
							 .write = CANtoRS_WriteHelper}

#ifdef __cplusplus
}
#endif

#endif




