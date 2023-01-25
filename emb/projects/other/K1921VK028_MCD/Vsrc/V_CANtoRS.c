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
 \brief     ��������������� ������� CAN � RS/USB � �������. ��������
��������� � ��������� CANOpen
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 3.0 08/08/2017

 \addtogroup v_CANtoRS
@{
*/
#include "DSP.h"
#include "main.h"


void usb_irq_en(void);
void usb_irq_dis(void);
//! \memberof TCANtoRS
void CANtoRS_init(TCANtoRS *p) {
#ifdef CANTORS_ENA
    p->NT_UART=UART2;                   //������������ � �������� ����� UART (1,2,3)
    p->NT_UART->CR_bit.UARTEN = 1;      // ��������� ������ UART

	// ��������� ������� � ���� ���������:
	// ������� �������� ������� ��� ��������� BaudRate
	// �.�. ���� UART ����������� � �������� 25 ��� (��� ��������� � ����� ����������������),
	// �� ��� ��������� ������� 57600 ���/� ���������
	// �������� 25000000 / (16 * 57600) = 27,126736111111111111111111111111
	// ����� ����� I = 27
	// ������� ����� F = (int)( 0.126736111*64 + 0.5 ) = 8
	// ������� ��. � ������������
	p->NT_UART->IBRD_bit.DIVINT= 27;
	p->NT_UART->FBRD_bit.DIVFRAC = 8;



	p->NT_UART->LCRH_bit.SPS = 0;		// ��� �������� ��������
	p->NT_UART->LCRH_bit.WLEN = 3;		// ����� ������� 8 ���
	p->NT_UART->LCRH_bit.FEN = 1;		// ������������ FIFO
	p->NT_UART->CR_bit.TXE = 1;			// ��������� ����
	p->NT_UART->CR_bit.RXE = 1;			// ��������� ��������
	p->NT_UART->LCRH_bit.STP2 = 0;		// 1 ����-���
#endif

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
    p->buf_out[0]=0x7E;
    for (i=0;i<len;i++)
        p->buf_out[i+1]=Data[i];
    MyCRC=CANtoRS_C_CRC(p,Data,len);
    p->buf_out[len+1]=MyCRC & 0xFF;//������ ����
    p->buf_out[len+2]=(MyCRC>>8) & 0xFF;//������ ����
    p->all_len=1+len+2;//������ �����=���������+������ + ����������� �����

    i = 0;

#ifdef CANTORS_ENA
    // ���� ����� TX �� ��������, �� ���������� ��� ����� �� ������
    while ((p->NT_UART->FR_bit.TXFF != 1) && (i < p->all_len)){
    	p->NT_UART->DR = p->buf_out[i];
    	i++;
    }
#endif

    return 1;
}



#define CRC_MAGIC_NUMBER 0xA001
//! ������� ������� ����������� ����� ������ 
//! � ���������� � ��������. ���� ��� �����, �� ���������� 1
 //! \memberof TCANtoRS
#if defined (__GNUC__)
__attribute__((section(".fastcode")))
#endif
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

/*! ������� ����������, ����� ������ �����-�� ������,
 * � ���������, ��� ��� ������ ��������� � ����� ���� ����������
 * ��������� CANopen. ���� ��� ��� - ������ ������������ ��
 * ���������
 */
 //! \memberof TCANtoRS
#if defined (__GNUC__)
__attribute__((section(".fastcode")))
#endif
void CANtoRS_CheckPacketValid(TCANtoRS *p) {
	Uint8 i;
    Uint16 readCRC, calcCRC;	// ��������� � ��������� ����������� �����

    // ������� ��������, �� ����� �� ���������� �������� ����� ��������� ������
    // ���� ����� - �� ��������, � ��� ��� ��������� ������ ��������, ������ �� ������, ����� �� ������ ��������� ���������
    if (p->callback_go) {
    	p->callback_go = 0;
    	p->CounterRes++;
    	p->callback(&co1_vars, (TZCanMsg*)&(p->MSG));
    	return;
    }
    // ���������, ������� ���� �������� � �����. ���� ������, ��� ����� (13) - ������� � ��� ���������� ����.
    // ���� ��������� - ���������� ������� �������� ���� � ��� ��������� �������
    if (p->ReadPackDataCounter < 13)
    	return;

    p->ReadPackDataCounter = 0;

    // ������� ��������� ���������, ������ ���� ������� (������ ���� 0x7E)
    // ���� ��������� �� ������� - ���������� ������� ���������� ������, � ����������� ����� ���������� �������
    if (p->tempBuf[0] != 0x7E){
    	p->MessDrop3++;
    	return;
    }

    // ���� ��������� ������� - ��������� 10 ���� ����� � DATA
    for (i = 0; i < CANTORS_READ_DATA_MAX_LEN; i++){
    	p->ReadPackData[i] = p->tempBuf[i + 1];
    }

    // ������ �������� ��������� ��� ���� ������� - CRC. ��������� ��������� CRC � ���������.
    // ���� �� ������� - ������� ��������.
    readCRC = ((Uint16)(p->tempBuf[12]) << 8) | ((Uint16)(p->tempBuf[11]));
    calcCRC = CANtoRS_C_CRC(p, (Uint16*)p->ReadPackData, CANTORS_READ_DATA_MAX_LEN);
    if (readCRC != calcCRC) {
        p->CounterWrongCRC++;
        return;
    }

    // ����������� ����� ������� - ����������� �����
    CANtoRS_Analysis(p);

    // ����� ���������, ��� � ���������� ��������� ������ �� ������� ������������� ������� �������.
    // � ����� ������ ����� ������ ���� "callback_go". ���� ��� ��� - �� ��� ���������� ��� ���������
    // ������ �������, ����� �� ������� ������� ����� �������. � ���� �������.
    return;

}

//! ������� ��� ����� ������ �� ��������� RS
//! \memberof TCANtoRS
#if defined (__GNUC__)
__attribute__((section(".fastcode")))
#endif
void CANtoRS_ReceiveRS(TCANtoRS *p) {
    // ������ �� ���� ������, ���� ��� ��� ����, ���� ���� ���� �� ��������
    while ((p->NT_UART->FR_bit.RXFE != 1) && (p->ReadPackDataCounter < 13)) {
    	// ���� ���-�� ������ �� RS, � � ������� ��� ��������� �� USB - ���� �������� ReadDataCounter
    	if (p->lastActiveConnection == CANTOUSB_ACTIVE)
    		p->ReadPackDataCounter = 0;

    	p->tempBuf[p->ReadPackDataCounter] = p->NT_UART->DR_bit.DATA;
    	p->ReadPackDataCounter++;

    	// ���������, ��� ������ ������� RS
    	p->lastActiveConnection = CANTORS_ACTIVE;
    }
}

//! ������� ��� ����� ������ �� ��������� USB
//! \memberof TCANtoRS
#if defined (__GNUC__)
__attribute__((section(".fastcode")))
#endif
void CANtoRS_ReceiveUSB(TCANtoRS *p) {
//    Uint16 neededBytes;
//    Uint16 tempLen;
//    // ���������, ������� ���� ������ � ������.
//    // ���� ������, ��� ��� ���� - ������ ������� ����.
//    // ���� ������, ��� ���� - ������ ��.
//    usb_irq_dis();
//    tempLen = usbRxBuf.filledSpace(&usbRxBuf);
//    if (tempLen > 0){
//    	// ���� ���-�� ������ �� USB, � � ������� ��� ��������� �� RS - ���� �������� ReadDataCounter
//    	if (p->lastActiveConnection == CANTORS_ACTIVE)
//    		p->ReadPackDataCounter = 0;
//
//    	neededBytes = 13 - p->ReadPackDataCounter;
//
//    	if (tempLen >= neededBytes) {
//    		usbRxBuf.get(&usbRxBuf, neededBytes, (Uint8*)(p->tempBuf + p->ReadPackDataCounter));
//    		p->ReadPackDataCounter += neededBytes;
//    	} else {
//    		usbRxBuf.get(&usbRxBuf, tempLen, (Uint8*)(p->tempBuf + p->ReadPackDataCounter));
//    		p->ReadPackDataCounter += tempLen;
//    	}
//
//    	// ���������, ��� � ��� ��� ������� USB
//    	p->lastActiveConnection = CANTOUSB_ACTIVE;
//    }
//    usb_irq_en();
}

//! ������� ��� ����� � ��������� ������ �� ���������/
//! �������� ����� � � USB, � � RS
//! \memberof TCANtoRS
#if defined (__GNUC__)
__attribute__((section(".fastcode")))
#endif
void CANtoRS_Receive(TCANtoRS *p) {

#ifdef CANTORS_ENA
	// ���� RS-������ ������������ - ������������ UART
	CANtoRS_ReceiveRS(p);
#endif

	// ��������� ��������� ������
	CANtoRS_CheckPacketValid(p);
}


/*! ������ ���������� ������ ������� � ��������
CAN ������ HeartBeat. ���� �������� �� ������� (�������� ������),
�� ��������� ����������� ������� �, ������� �������, ��������
��������� ������ */
 //! \memberof TCANtoRS
void CANtoRS_HeartBeat(TCANtoRS *p) {
	TZCanMsg MSG;
	int16 i;
	MSG.id = 0xE << 7;				//heartbeat
	MSG.id |= *p->nodeID;			//����� ����
	MSG.dlc = 1;					//�����
	for (i = 0; i < 8; MSG.data[i++] = 0);					//�������
	MSG.data[0] = 5;				//������ heartbeat
	if (!CANtoRS_Write(&MSG, p)) { 	//���� �� ���������� ���������
		p->HeartCounter = (CANTORS_HEART_COUNTER_MAX - 3); //������ ������� ������� ��� ��� ���
		p->HeartBeatGo = 1; 		//� ���� ����� ������� �� �������� SDO, �� ����� �����, ��� ���� ����������
	} else {
		p->HeartBeatGo = 0;
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
#if defined (__GNUC__)
__attribute__((section(".fastcode")))
#endif
void CANtoRS_calc(TCANtoRS *p) {

    //���� � ������ ���� �����, ��������� �������� � ���������� �������� � �� ���� heartbeat
    if (p->PacketInWait) {
        if (!CANtoRS_Write_Real((TZCanMsg*)&p->bufMSG, p))//��������� �� �������?
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
