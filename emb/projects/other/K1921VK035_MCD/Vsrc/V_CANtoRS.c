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

 \file      v_CANtoRS.c
 \brief     ��������������� ������� CAN � RS � �������. �������� 
��������� � ��������� CANOpen
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup v_CANtoRS
@{
*/
#include "DSP.h"
#include "main.h"



//! \memberof TCANtoRS
void CANtoRS_init(TCANtoRS *p) {

	GPIOB->ALTFUNCSET = (1 << 8) + (1 << 9);

	p->UART=UART1;//������������ � �������� ����� UART (0, 1)


	// ��������� ������� � ���� ���������:
	// ������� �������� ������� ��� ��������� BaudRate
	// �.�. ���� UART ����������� � �������� 25 ��� (��� ��������� � ����� ����������������),
	// �� ��� ��������� ������� 57600 ���/� ���������
	// �������� 25000000 / (16 * 57600) = 27,126736111111111111111111111111
	// ����� ����� I = 27
	// ������� ����� F = (int)( 0.126736111*64 + 0.5 ) = 8
	// ������� ��. � ������������
	p->UART->IBRD_bit.DIVINT= 27;
	p->UART->FBRD_bit.DIVFRAC = 8;


	//p->UART->LCRH_bit.SPS = 0;		// ��� �������� ��������
	//p->UART->LCRH_bit.WLEN = 3;		// ����� ������� 8 ���
	//p->UART->LCRH_bit.FEN = 1;		// ������������ FIFO
	//p->UART->LCRH_bit.STP2 = 0;		// 1 ����-���
    //
	//p->UART->CR_bit.UARTEN = 1; // ��������� ������ UART
	//p->UART->CR_bit.TXE = 1;			// ��������� ����
	//p->UART->CR_bit.RXE = 1;			// ��������� ��������

	p->UART->LCRH = (0 << UART_LCRH_SPS_Pos) |
					(3 << UART_LCRH_WLEN_Pos) |
					(1 << UART_LCRH_FEN_Pos) |
					(0 << UART_LCRH_STP2_Pos);

	p->UART->CR = (1 << UART_CR_UARTEN_Pos) |
				  (1 << UART_CR_TXE_Pos) |
			      (1 << UART_CR_RXE_Pos);

	p->CounterWrongCRC=0;
    p->CounterRes=0;
    p->CounterSended=0;
    p->PacketInWait=0;

}



//! �� ��������� ��� �������� ������� ������� ���������
//!API �����, � ����� �������� �������
//!���������� ��������

 //! \memberof TCANtoRS
Uint16 CANtoRS_SendP(Uint16* Data, int16 len, TCANtoRS *p) {
    volatile int16 i;
    Uint16 MyCRC;
    p->buf_out[0] = 0x7E;
    for (i = 0; i < len; i++)
        p->buf_out[i+1]=Data[i];
    MyCRC=CANtoRS_C_CRC(p,Data,len);
    p->buf_out[len+1]=MyCRC & 0xFF;//������ ����
    p->buf_out[len+2]=(MyCRC>>8) & 0xFF;//������ ����
    p->all_len=1+len+2;//������ �����=���������+������ + ����������� �����

    i = 0;
    // ���� ����� TX �� ��������, �� ���������� ��� ����� �� ������
    while ((p->UART->FR_bit.TXFF != 1) && (i < p->all_len)){
    	p->UART->DR = p->buf_out[i];
    	i++;
    }

    return 1;
}



#define CRC_MAGIC_NUMBER 0xA001
//! ������� ������� ����������� ����� ������ 
//! � ���������� � ��������. ���� ��� �����, �� ���������� 1
 //! \memberof TCANtoRS

Uint16 CANtoRS_C_CRC(TCANtoRS *p,Uint16 *Data,Uint16 len) { //�������� ����������� ����� ��������� API ������
    int16 i,j;
    Uint16 MyCalcCRC=0xFFFF;

    for (j=0;j<len;j++) {
        MyCalcCRC=MyCalcCRC^(Data[j++]&0xFF);
        for (i=0; i<16; i++)
            if (MyCalcCRC&0x01) {
                MyCalcCRC=(MyCalcCRC>>1);
                MyCalcCRC=MyCalcCRC^CRC_MAGIC_NUMBER;
            } else
                MyCalcCRC=(MyCalcCRC>>1);
    }

    return MyCalcCRC;
}



/*! ������� ����������, ����� ������ �����-�� ������,
� ������������ �� ��� ���������� CAN �����. ��������
�������������, ����� � ������. ���-� �������� � ���������
p->MSG */
 //! \memberof TCANtoRS
void CANtoRS_Analysis(TCANtoRS *p) {
    int16 i,j;
    //������� ������ ���������� � 12�� �����,
    //�� ����� ��������� ���������� API ������
    p->MSG.id=0;
    p->MSG.id=(p->ReadPackData[0] & 7)<<8; //������ 3 ���� �������� ������;
    p->MSG.id|=p->ReadPackData[1];
    p->MSG.dlc=(p->ReadPackData[0]>>4) & 0xF; //������� 4 ���� �������� ����; ����� �������
    for (i=2,j=0;i<CANTORS_READ_DATA_MAX_LEN;i++,j++)
        p->MSG.data[j]=p->ReadPackData[i];
    p->callback_go=1;
}





/*! ���������� ���������� ���������� �� SCI ������.
�������� �� �������� ����������� �������� � ��������
����� � ������� API �����. ������� ���� �������� ���������,
����� ����� � �.�. � ����� ��������� ����������� ����� �
�������� ���������� ����������� */
 //! \memberof TCANtoRS

void CANtoRS_Receive(TCANtoRS *p) {
    Uint16 MyReadCRC_u16;
    Uint16 MyCalcCRC;
    Uint32 temp_byte;
    Uint16 repeat;
    for (repeat=0;repeat<7; repeat++) {//��������� �� ����� n ���� �� ���� ���� � �������

        switch (p->APIpacketMode) {

        case 0: { //�������� ���������


            if (p->UART->FR_bit.RXFE)
            	return;
            temp_byte = p->UART->DR_bit.DATA;
            if (temp_byte!=0x7e) {
                p->MessDrop3++;
                return;
            }
            p->ReadPackDataCounter=0;//������� ������
            p->APIpacketMode=1; //���������� �������, ����� ������ ������
            break;
        };
        case 1: { //�������� ������(�������� ��������) ������
            //��� ����������� ����� ���������� � API �����

            if (p->UART->FR_bit.RXFE)
            	return;
            temp_byte = p->UART->DR_bit.DATA;
            p->ReadPackData[p->ReadPackDataCounter++]=temp_byte;
            if (p->ReadPackDataCounter>=CANTORS_READ_DATA_MAX_LEN) {
                p->ReadPackDataCounter=0;//������� ������
                p->ReadCRCCounter=0;//������� ����������� �����
                p->APIpacketMode=2;  //������ �������, ����� ������ � �������� CRC
            }
            break;
        };

        case 2: { //��������  CRC
            //��� ����������� ����� ���������� � CRC �����

            if (p->UART->FR_bit.RXFE)
            	return;
            temp_byte = p->UART->DR_bit.DATA;
            p->ReadCRC[p->ReadCRCCounter++]=temp_byte;
            if (p->ReadCRCCounter>=2) {
                p->ReadCRCCounter=0;//������� ����������� �����
                MyReadCRC_u16=(p->ReadCRC[0]&0xFF)+((p->ReadCRC[1]<<8)&0xFF00);//������������ ������������ CRC � ���� ����������
                MyCalcCRC=CANtoRS_C_CRC(p,(Uint16 *)p->ReadPackData,CANTORS_READ_DATA_MAX_LEN);
                if (MyCalcCRC!=MyReadCRC_u16) {
                    //������!
                    p->CounterWrongCRC++;
                    p->APIpacketMode=0;
                    break;
                }//����������� ����� ������� � �����

                CANtoRS_Analysis(p);
                if (p->callback_go) { //���� ��������� ����, ����� callback
                    p->callback_go=0;
                    p->APIpacketMode=3;  //��������� callback
                }
                else
                    p->APIpacketMode=0;
                return;
            }
            break;
        };
        case 3: { //��������� callback
            p->CounterRes++;
            p->callback(&co1_vars, (TZCanMsg*)&(p->MSG));
            p->APIpacketMode=0;
            break;
        };
        default:
            return;
        }
    }
    return;
}



/*! ������ ���������� ������ ������� � ��������
CAN ������ HeartBeat. ���� �������� �� ������� (�������� ������),
�� ��������� ����������� ������� �, ������� �������, ��������
��������� ������ */
 //! \memberof TCANtoRS
void CANtoRS_HeartBeat(TCANtoRS *p) {
    TZCanMsg MSG;
    int16 i;
    MSG.id=0xE<<7;//heartbeat
    MSG.id|=*p->nodeID;//����� ����
    MSG.dlc=1;//�����
    for (i=0;i<8;MSG.data[i++]=0);//�������
    MSG.data[0]=5;//������ heartbeat
    if (!CANtoRS_Write(&MSG,p)) { //���� �� ���������� ���������
        p->HeartCounter=(CANTORS_HEART_COUNTER_MAX-3); //������ ������� ������� ��� ��� ���
        p->HeartBeatGo=1;//� ���� ����� ������� �� �������� SDO, �� ����� �����, ��� ���� ����������
    } else {
        p->HeartBeatGo=0;
    }
}


 //! \memberof TCANtoRS
Uint16 CANtoRS_WriteHelper(TZCanMsg* MSG,TCANtoRS *p) {
    if (p->HeartBeatGo) { //����� ����������� HeartBeat
        CANtoRS_HeartBeat(p);
        p->MessDrop1++;
        return 0;//��������� ������...
    }
    if (CANtoRS_Write(MSG,p))
        p->CounterSended++;
    else {
        p->MessDrop2++;

        return 0;
    }
    return 1;
}


/*! �� ��������� CAN ������ ��������� ������-�������,
��� ������� 4 ���� - �����, ����� 1 ��� ������� � 11 �������������.
����� ��������������� ������. ����� ��������������� ������� ������������*/
 //! \memberof TCANtoRS
Uint16 CANtoRS_Write(TZCanMsg* MSG,TCANtoRS *p) {
    if (!p->PacketInWait) { //��� ������ � ������
        //�������� �� ��������� �����
        p->bufMSG=*MSG;
        p->PacketInWait=1;//����, ��� � ������ ���-�� ����
        return 1;
        //���������, ��� ������ �� 1 ������� ������ �������
    } else
        return 0;
}

 //! \memberof TCANtoRS
Uint16 CANtoRS_Write_Real(TZCanMsg* MSG,TCANtoRS *p) {
    int16 i;

    p->TempData[0]=(MSG->dlc & 0xF)<<4;
    p->TempData[0]|=(MSG->id >> 8) & 7;
    p->TempData[1]=MSG->id & 0xFF;
    for (i=0;i<8;i++) p->TempData[i+2]=MSG->data[i];
    CANtoRS_SendP((Uint16*)p->TempData,10,p);
    return 1;
}

/*! ���������� �� ��������������� �������, ����������� 1 �������
� �������� ������� �������� HeartBeat. ������ ���������,
���� � SCI �������� �����-�� ������ � �� �����������, �������������.
 */

 //! \memberof TCANtoRS
void CANtoRS_calc(TCANtoRS *p) {

    //���� � ������ ���� �����, ��������� �������� � ���������� �������� � �� ���� heartbeat
    if (p->PacketInWait) {
        if (!CANtoRS_Write_Real((TZCanMsg*)&p->bufMSG,p))//��������� �� �������?
            p->MessDrop2++;
        p->PacketInWait=0;//������� �����
    }
    else{//���� ������ �� ������� ���, �������������� �� ���������. ����� �� � ������������ �����, �� �� ������� ��������
      CANtoRS_Receive(p);
      p->HeartCounter++; //������� ��� HeartBeat

      //�� ���� �� ��������� HeartBeat?
      if (p->HeartCounter>=(CANTORS_HEART_COUNTER_MAX-1)) {
          p->HeartCounter=0;
          CANtoRS_HeartBeat(p);
      }

    }
}



/*@}*/
