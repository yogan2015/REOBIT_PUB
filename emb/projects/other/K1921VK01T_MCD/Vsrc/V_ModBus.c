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

 \file      V_ModBus.c
 \brief     ������� ModBus (��. TModBus)
 24-03-2017		������� �������� �� �1921��01� �����. ������� �����������.

 13-08-2012		������ ���� type ��������� MB_Record ������������ ��� ������� ������/������
				��� �� ������� HR/IR-���������� (������ ��� ��� ������ ������� ������).

 24-01-2012     ������ ����� �������� ����� SciaRegs, ScibRegs � ScicRegs. ��� �������
				��������. ������������� ��������� RS � MODBUS_RS


 26-02-2011     ���������� �����-�� ����, ��������� ����������� ����������� ������ � �������
				���� "�������" �� ���� ��������� ������ ���� � �������, ��������� ��������
				���-�� �����������.


  27-11-2009    ������� ��������� �������� ��� ��������� broadcast (�����������������) ���������. ������������,
                ��� �������������� ������ ������� ������ (0x5 - write coils � 0x6 - write single register), �.�.
                broadcast ��������� �������� ����������������� �����������. ����� ������� ������ ����������, �.�.
                ������ �� ������... (�������)

  21-10-2008    ���������� ������ ������������ �������� �������� - ��� ������������ ������������ frame error (�� �������� SYS_VID800)
  29-01-2008    ��������� ������ ������� ���������
  28-01-2008    ��������� ������ � ������� ������ ������� �������� �������

  29-11-2007    ������� ��������� ��� ������ � ��17.1
                                1.���������� ������ ��� ��������� ������� ���������
                                2.��������� ������������ ������� ��������� � �������
                                3.��������� ����������� ��������������� ����������� �������� ��� ������� ���������� ������ �� �����

                                ���������. ����������� ���������� �������� �� ������������ ������� �������� � 0�0000 � �������
                                ��� ���������� ���������� ���������� � ������������� ���������� ����� ��������� ���������
                                �������� � ���� ������ �������� �� ���� ������ ���������� ��������.
  16-11-2006    Release Rev 1.0

 \author        Alecksey Anuchin
 \version   v 1.2 24/03/2017

*/

/** \addtogroup V_ModBus */
/*@{*/
#include "V_ModBus.h"
#include "main.h"

#if defined (HW_MOTORCONTROLBOARD)
//������� ��� ������������ RS485 ����� ������� � ���������
#define MODBUS_RX_RS485 NT_GPIOG->MASKHIGHBYTE_bit[1].MASKHB = 0	//G8
#define MODBUS_TX_RS485 NT_GPIOG->MASKHIGHBYTE_bit[1].MASKHB = 1	//G8
#else
#define MODBUS_RX_RS485 //NT_GPIOC->MASKHIGHBYTE_bit[4].MASKHB = 4
#define MODBUS_TX_RS485 //NT_GPIOC->MASKHIGHBYTE_bit[4].MASKHB = 0
#endif
//������ ��� ������������������� ����� UART (������ ��� �������, ����� ������ ������ �� ��������)
#define MODBUS_GPIO_VALUE  (NT_GPIOD->DATA>>1) & 3
//������� ������������ ����� UART (������������� � ������������� ����������������)
#define UART_CLOCK_FREQ 25000000


void  ModBus_RS_Init(TModBus *p){

#if defined (HW_MOTORCONTROLBOARD)

	//��������� ����� G8 �������� �� �����
	NT_GPIOG->OUTENSET = (1 << 8);


    // ������� � ��������� ������������ �������
    NT_COMMON_REG->GPIOPCTLF_bit.PIN10 = 0;   //UART_TxD[2]
    NT_COMMON_REG->GPIOPCTLF_bit.PIN11 = 0;  //UART_RxD[2]
    NT_GPIOF->ALTFUNCSET = (1 << 10) + (1 << 11);

    // �������� ������������ ������� F4, ����� ��� �� ������������� UART2
    NT_COMMON_REG->GPIOPCTLF_bit.PIN4 = 1;

    p->MBInternals.NT_UART=NT_UART2;//������������ � �������� ����� UART (1,2,3)

	p->MBInternals.NT_UART->CR_bit.UARTEN = 1; 		// ��������� ������ UART
#else
	// ������� � ��������� ������������ �������
	NT_COMMON_REG->GPIOPCTLD_bit.PIN1 = 1;	 //UART_TxD[3]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN2 = 1;	//UART_RxD[3]
	NT_GPIOD->ALTFUNCSET = (1 << 1) + (1 << 2);

	// �������� ������������ ������� F12 � F13, ����� ��� �� ������������� UART3
	NT_COMMON_REG->GPIOPCTLF_bit.PIN12 = 1;
	NT_COMMON_REG->GPIOPCTLF_bit.PIN13 = 1;
	p->MBInternals.NT_UART=NT_UART3;//������������ � �������� ����� UART (1,2,3)

	p->MBInternals.NT_UART->CR_bit.UARTEN = 1; 		// ��������� ������ UART
#endif

	//������� ���������� �������� �� ���������� FIFO, ������������ ������ �� ������ �����
	//� ���������� � ���������� 10���. ������� ������� ������ ������ 57600 �� �������������� (����� ������ �����)
	if (p->BaudRate>57600)
		p->BaudRate=57600;

	// ��������� ������� � ���� ���������:
	// ������� �������� ������� ��� ��������� BaudRate
	// �.�. ���� UART ����������� � �������� 25 ��� (��� ��������� � ����� ����������������),
	// �� ��� ��������� �������, ��������, 57600 ���/� ���������
	// �������� 25000000 / (16 * 57600) = 27,126736111111111111111111111111
	// ����� ����� I = 27
	// ������� ����� F = (int)( 0.126736111*64 + 0.5 ) = 8
	// ������� ��. � ������������
	float DivResFloat=(float)UART_CLOCK_FREQ / (16 * p->BaudRate);
	long DivResInt=(long)DivResFloat;
	long DivResFrac=(int)((DivResFloat-DivResInt)*64 + 0.5);

	p->MBInternals.NT_UART->IBRD_bit.BAUD_DIVINT= DivResInt;
	p->MBInternals.NT_UART->FBRD_bit.BAUD_DIVFRAC = DivResFrac;

	// 8 ��� ������, 1 ���� ���, ��� �������� ��������
	p->MBInternals.NT_UART->LCR_H_bit.SPS = 0;		// ��� �������� ��������
	p->MBInternals.NT_UART->LCR_H_bit.WLEN = 3;		// ����� ������� 8 ���
	p->MBInternals.NT_UART->LCR_H_bit.FEN = 0;		// �� ������������ FIFO
	p->MBInternals.NT_UART->CR_bit.TXE = 1;			// ��������� ����
	p->MBInternals.NT_UART->CR_bit.RXE = 1;			// ��������� ��������
	p->MBInternals.NT_UART->LCR_H_bit.STP2 = 0;		// 1 ����-���

}



void  ModBus_ResetError(TModBus *p)
{
	// ���� 0-3 - ���� ������, ������������ ������� � ��� "1"
	p->MBInternals.NT_UART->RSR_ECR |= 0x000F;
}

int16 ModBus_CheckDataReady(TModBus *p)
{
	// return 1 - ���� ����� �������� �� ����
	return (!p->MBInternals.NT_UART->FR_bit.RXFE);
}

int16  ModBus_CheckTxEmpty(TModBus *p) //���� ��� ���������� (���� � �������� � ������� ��������)
{
	// return 1 - ���� ����� ����������� ����
	return (p->MBInternals.NT_UART->FR_bit.TXFE);
}

int16  ModBus_CheckTxReady(TModBus *p) //� ���������� ����� �������� ��������� ������ (����� ��������)
{
	// "1" - ���� ����� ����������� ����
	return (p->MBInternals.NT_UART->FR_bit.TXFE);
}

void  ModBus_Tx(TModBus *p, int16 data)  // �������� ������
{
	Uint8 tmp_data = data;
	p->MBInternals.NT_UART->DR_bit.DATA = tmp_data;
}

//!�������������.
//!��������� ���������,
//!��������� ������� �������� ��� ������������ �������� ������

//! \memberof TModBus
void ModBus_Init(TModBus *p)
{
  Uint16 x;

  ModBus_RS_Init(p);

  p->MBInternals.TimeOut1_5=(int16)(((int32)p->ExecutionFreq*(int32)17)/p->BaudRate +2);       // 17 ~ 11*1.5
  p->MBInternals.TimeOut2_5=(int16)(((int32)p->ExecutionFreq*(int32)28)/p->BaudRate);          // 28 ~ 11*2.5

  p->MBInternals.RecievedCounter=-1;


////// HR
  // ����� ������� ������� HR
  x=0;
  while (mbodHR[x].index!=0)
    x++;
  p->MBInternals.NumOfHRs=x;

  // ����� �������� �������� ������� HR
  p->MBInternals.MiddleOfHRs=x;
  x=0;
  while ((p->MBInternals.MiddleOfHRs>>1)!=0)
  {
    p->MBInternals.MiddleOfHRs>>=1;
    x=x+x+1;
  }
  p->MBInternals.MiddleOfHRs=x;

  // ����� ���������� ���������� ��� ������ �����������������
  // �����������
  p->MBInternals.InitialStepOfHRs=1;
  while (x!=0)
  {
    x>>=1;
    p->MBInternals.InitialStepOfHRs<<=1;
  }
  p->MBInternals.InitialStepOfHRs>>=1;

////// Coils
  // ����� ������� ������� C
  x=0;
  while (mbodC[x].index!=0)
    x++;
  p->MBInternals.NumOfCs=x;

  // ����� �������� �������� ������� C
  p->MBInternals.MiddleOfCs=x;
  x=0;
  while ((p->MBInternals.MiddleOfCs>>1)!=0)
  {
    p->MBInternals.MiddleOfCs>>=1;
    x=x+x+1;
  }
  p->MBInternals.MiddleOfCs=x;

  // ����� ���������� ���������� ��� ������ �����������������
  // �����������
  p->MBInternals.InitialStepOfCs=1;
  while (x!=0)
  {
    x>>=1;
    p->MBInternals.InitialStepOfCs<<=1;
  }
  p->MBInternals.InitialStepOfCs>>=1;

// Discrete Inputs
  // ����� ������� ������� DI
  x=0;
  while (mbodDI[x].index!=0)
    x++;
  p->MBInternals.NumOfDIs=x;

  // ����� �������� �������� ������� DI
  p->MBInternals.MiddleOfDIs=x;
  x=0;
  while ((p->MBInternals.MiddleOfDIs>>1)!=0)
  {
    p->MBInternals.MiddleOfDIs>>=1;
    x=x+x+1;
  }
  p->MBInternals.MiddleOfDIs=x;

  // ����� ���������� ���������� ��� ������ �����������������
  // �����������
  p->MBInternals.InitialStepOfDIs=1;
  while (x!=0)
  {
    x>>=1;
    p->MBInternals.InitialStepOfDIs<<=1;
  }
  p->MBInternals.InitialStepOfDIs>>=1;

////// IR
  // ����� ������� ������� HR
  x=0;
  while (mbodIR[x].index!=0)
    x++;
  p->MBInternals.NumOfIRs=x;

  // ����� �������� �������� ������� HR
  p->MBInternals.MiddleOfIRs=x;
  x=0;
  while ((p->MBInternals.MiddleOfIRs>>1)!=0)
  {
    p->MBInternals.MiddleOfIRs>>=1;
    x=x+x+1;
  }
  p->MBInternals.MiddleOfIRs=x;

  // ����� ���������� ���������� ��� ������ �����������������
  // �����������
  p->MBInternals.InitialStepOfIRs=1;
  while (x!=0)
  {
    x>>=1;
    p->MBInternals.InitialStepOfIRs<<=1;
  }
  p->MBInternals.InitialStepOfIRs>>=1;


  for (x=0; x<1000; x++)
    ;
}



//!������

//!������ ��������� ������� ModBus

//! \memberof TModBus
void ModBus_Execute(TModBus *p)
{
  Uint16 x;
  volatile Uint16 RxReg;
  if (ModBus.Enabled == 1){ // ���� ������� MODBUS
	  p->OfflineCounter+=1;

	  //����� ��� �������� �� ����?
	  if (p->OfflineCounter>p->OfflineCounterMax)
	  {
		p->isOnline=0;//�� �� � ����
		p->OfflineCounter=p->OfflineCounterMax+1;//���� �� ������
	  }
	  else
		p->isOnline=1;//� ����

	  //�������� ������
	  if (p->errorCode)
	  {//���� ����� ������
		p->error += 1;
		if (p->AutoRestart == 1)//���� �������� ���� ����� ������
			ModBus_ResetError(p);
	  }
	  if (p->clear_error == 1)//���� ��������� ���� ������������ ������� ������ ������
	  {
		ModBus_ResetError(p);
		p->clear_error = 0;
		p->error = 0;
	  }
	  //������� �������� GPIO ��� �������
	  p->GPIOsValue=MODBUS_GPIO_VALUE;


	  if (p->MBInternals.TxState<1)//TxState==0 - �������� �� ����
		if (ModBus_CheckDataReady(p))//���� ���� ������� ��������� ������ (����)
		{
		  p->MBInternals.TimeOut=p->MBInternals.TimeOut1_5;//������� ������ ������� �������
		  RxReg = p->MBInternals.NT_UART->DR;//����� ���������� �������
		  p->errorCode=(RxReg & 0x0F00)>>8;
		  RxReg = RxReg & 0xFF;
		  p->received_data = RxReg;//�������������� �������� ������ ��� �������
		  p->ReceiveByteCounter++;
		  if (p->MBInternals.InCount==MODBUS_MAX_RX_COUNT)//�������� ������� ����� ����
			return;
		  p->MBInternals.In[p->MBInternals.InCount++]=RxReg;//�������� ������ � ������
		  p->MBInternals.RxCRC^=RxReg;//����� �� ������ ����������� �����
		  for (RxReg=0; RxReg<8; RxReg++)//��� ���� ����������� ������� ����������� �����
			if (p->MBInternals.RxCRC&0x01)
			{
			  p->MBInternals.RxCRC>>=1;
			  p->MBInternals.RxCRC^=p->MBInternals.MagicNumber;
			}
			else
			  p->MBInternals.RxCRC>>=1;
		  //������ ������, ���� ���� �������� ������, �� ��������
		  return;
		}
	  if (p->MBInternals.TimeOut==0)//����� ������� �����, ��� ������������ ������� p->MBInternals.TimeOut==1, � ����� ���� �� ���������� ����� ������
	  {
		p->MBInternals.InCount=0;//��������� �������� �������
		p->MBInternals.RxCRC=0xFFFF;//������������� ����������� ����� �� �����
		if (ModBus_CheckTxEmpty(p))//���� ����� �� �������� ����
		{
		  MODBUS_RX_RS485;//������������ RS485 �� �����
		  p->MBInternals.TxState=0;//TxState==0 - �������� �� ����
		  p->MBInternals.TxCRC=0xFFFF;//������������� ����������� ����� �� ��������
		}
		return;
	  }
	  if (p->MBInternals.TimeOut==1) //; ���� ��������, ����� ���� ��������� ���������� ����� � 1,5 �������
		if (p->MBInternals.InCount!=0) //; ���� ���������� ������� ������ �� ����� ����, �� ������������, ��� ������
		{
		  //��������� broadcast �������������� ��� (�� ������� � ������ ��� ���  - �������)
		  //����� ������� � �������� - ��� ���� �� �����, ������ ������������ �����
		  //������������ ����� ����� ������ ������� �� ������ (0x5 - write coils � 0x6 - write single register).
		  if (p->MBInternals.In[0] == 0)//������� ������, ���� ������ ����� 0 - �����������������
		  {
			//0x5 - write coils
			if (p->MBInternals.In[1] == 5)
			{
			  x=(p->MBInternals.In[4]<<8)+p->MBInternals.In[5];//������
			  //0 - ���� �����, 3 - ���� ������ �����������,  2 - ������ � ������
			  p->MBInternals.temp=ModBus_FindVocAddr(p, mbodC,\
										   p->MBInternals.NumOfCs, 1,\
										   (p->MBInternals.In[2]<<8)+p->MBInternals.In[3],\
										   1,\
										   p->MBInternals.MiddleOfCs, p->MBInternals.InitialStepOfCs);
			  if ((x!=0xFF00)&&(x!=0x0000))//������ �� �������, ��� ������� ���������� ������ ���� FF00 ��� 0000
				p->MBInternals.temp=3;//�������� ��� ����� ModBus_FindVocAddr ������� ������������ ������
			  if (p->MBInternals.temp==0)//���� ModBus_FindVocAddr ����� �����
			  {
				if (p->MBInternals.In[4]==0)   // reset bit
				  *(Uint16 *)(p->MBInternals.Addr->addr)&=(0xFFFF-(1<<p->MBInternals.Addr->type_or_acc));
				else                                                // set bit
				  *(Uint16 *)(p->MBInternals.Addr->addr)|=(1<<p->MBInternals.Addr->type_or_acc);
			  }
			}
			if (p->MBInternals.In[1] == 6)//0x6 - write HR
			{
			  p->MBInternals.temp=ModBus_FindVocAddr(p, mbodHR,\
										   p->MBInternals.NumOfHRs, 16,\
										   (p->MBInternals.In[2]<<8)+p->MBInternals.In[3],\
										   1,\
										   p->MBInternals.MiddleOfHRs, p->MBInternals.InitialStepOfHRs);
			  if (p->MBInternals.temp==0)//���� ModBus_FindVocAddr ����� �����
			  {
				*(Uint16 *)(p->MBInternals.Addr->addr)=(p->MBInternals.In[4]<<8)+p->MBInternals.In[5];
			  }
			}

			//������ �� �� �����, ��� � ���� ��� ���������� ���������� ��������� � �������
			p->MBInternals.InCount=0;//��������� ������� �������� ����
			p->MBInternals.TimeOut=0;//��������� ��������
			p->MBInternals.RxCRC=0xFFFF;//������������� ����������� �����
			return;
		  }

		  if (p->MBInternals.In[0]!=p->RSNodeID) //; ���� ����� ���� �� ������ � �����, �� ���������� �������.
		  {
			p->MBInternals.InCount=0;
			p->MBInternals.TimeOut=0;
			p->MBInternals.RxCRC=0xFFFF;
			return;
		  }
		  if (p->MBInternals.RxCRC!=0)    //; ���� �� ������� ����������� �����, �� ���������� �������.
		  {
			p->MBInternals.InCount=0;
			p->MBInternals.TimeOut=0;
			p->MBInternals.RxCRC=0xFFFF;
			return;
		  }
		  if (p->MBInternals.RecievedCounter<0)//!!!                                                             //; ���� ��� �� ������������������ ������� ����� ������� (-1), ��
		  {
			//; �������������� ������� � �������.
			p->MBInternals.RecievedCounter=p->MBInternals.TimeOut2_5;
			return;
		  }
		  if (p->MBInternals.RecievedCounter>0)//!!!                                                                        //; ���� ������� ����� ����� ������� ��� �������������, �� ��������� ���
		  {
			//; � �������
			p->MBInternals.RecievedCounter--;
			return;
		  }
		  //; ���� ������� RecievedCounter �������� �� ����, �� ����� ������������� �� ��������.
		  p->MBInternals.RecievedCounter=-1;
		  p->ReceivePacketCounter++;
		  MODBUS_TX_RS485;//RS485 �� ��������
		  p->MBInternals.TxState=1;//��������
		  p->MBInternals.RxCRC=0xFFFF;
		  p->MBInternals.TimeOut=p->MBInternals.TimeOut2_5;
		  ModBus_Tx(p,p->MBInternals.In[0]);//���������� ������ ���� - ����� ����������, ������-�� ���� �� ������...
		  p->MBInternals.TxCRC^=p->MBInternals.In[0];//����� ������ ����������� ����� �� ��������
		  //� ��� ���� ������ ����������� �����
		  for (RxReg=0; RxReg<8; RxReg++)
			if (p->MBInternals.TxCRC&0x01)
			{
			  p->MBInternals.TxCRC>>=1;
			  p->MBInternals.TxCRC^=p->MBInternals.MagicNumber;
			}
			else
			  p->MBInternals.TxCRC>>=1;
		  return;
		}
		else//���������� �������� ������ ����� ����.. ������-��
		{
		  p->MBInternals.TimeOut=0;
		  return;
		}
	  p->MBInternals.TimeOut--;//������������� �������
	  if (p->MBInternals.TxState<1)//���� TxState==0 - ��� ��������, � �����, �.�. ���� - ��������.
		return;

	  if (ModBus_CheckTxReady(p)==0)//���� ���������� �����
		return;

	  //������������� ��������
	  p->MBInternals.TimeOut=p->MBInternals.TimeOut2_5;

	  // � ����� ������� ���������� ���������� �������
	  // ���������
	  //p->TxState=0;

	  if (p->MBInternals.TxState==1)   //��������� �������� 1
	  {
		p->OfflineCounter=0;//������� ��� �������� ������������ ������� ModBus
		p->MBInternals.temp=p->MBInternals.In[1];//�������� ������, ��� ����� �������
		if (p->MBInternals.temp==1)    // ������� read Coils
		{
		  p->MBInternals.ToSend=p->MBInternals.temp;//��� �������� - ����� �������
		  p->MBInternals.temp=ModBus_FindVocAddr(p,mbodC,\
									   p->MBInternals.NumOfCs, 1,\
									   (p->MBInternals.In[2]<<8)+p->MBInternals.In[3],\
									   (p->MBInternals.In[4]<<8)+p->MBInternals.In[5],\
									   p->MBInternals.MiddleOfCs, p->MBInternals.InitialStepOfCs);
		  if (p->MBInternals.temp==0)//� ������� ������ �������
		  {
			p->MBInternals.TxState=10;
		  }
		  else//������, � ������� ������� �� ������
		  {
			p->MBInternals.ToSend|=0x80;//����������� ����� ������
			p->MBInternals.TxState=p->MBInternals.temp+3;
		  }
		}
		else if (p->MBInternals.temp==2)       // ��� ������� read DI
		{
		  p->MBInternals.ToSend=p->MBInternals.temp;//��� �������� - ����� �������
		  p->MBInternals.temp=ModBus_FindVocAddr(p,mbodDI,\
									   p->MBInternals.NumOfDIs, 1,\
									   (p->MBInternals.In[2]<<8)+p->MBInternals.In[3],\
									   (p->MBInternals.In[4]<<8)+p->MBInternals.In[5],\
									   p->MBInternals.MiddleOfDIs, p->MBInternals.InitialStepOfDIs);
		  if (p->MBInternals.temp==0)//� ������� ������ �������
		  {
			p->MBInternals.TxState=10;
		  }
		  else//������, � ������� ������� �� ������
		  {
			p->MBInternals.ToSend|=0x80;//����������� ����� ������
			p->MBInternals.TxState=p->MBInternals.temp+3;
		  }
		}
		else if (p->MBInternals.temp==3)       // ������� read HR
		{
		  p->MBInternals.ToSend=p->MBInternals.temp;
		  p->MBInternals.temp=ModBus_FindVocAddr(p,mbodHR,\
									   p->MBInternals.NumOfHRs, 16,\
									   (p->MBInternals.In[2]<<8)+p->MBInternals.In[3],\
									   (p->MBInternals.In[4]<<8)+p->MBInternals.In[5],\
									   p->MBInternals.MiddleOfHRs, p->MBInternals.InitialStepOfHRs);
		  if (p->MBInternals.temp==0)//� ������� ������ �������
		  {
			p->MBInternals.TxState=7;
		  }
		  else//������, � ������� ������� �� ������
		  {
			p->MBInternals.ToSend|=0x80;//����������� ����� ������
			p->MBInternals.TxState=p->MBInternals.temp+3;
		  }
		}
		else if (p->MBInternals.temp==4)       // ������� read IR
		{
		  p->MBInternals.ToSend=p->MBInternals.temp;
		  p->MBInternals.temp=ModBus_FindVocAddr(p,mbodIR,\
									   p->MBInternals.NumOfIRs, 16,\
									   (p->MBInternals.In[2]<<8)+p->MBInternals.In[3],\
									   (p->MBInternals.In[4]<<8)+p->MBInternals.In[5],\
									   p->MBInternals.MiddleOfIRs, p->MBInternals.InitialStepOfIRs);
		  if (p->MBInternals.temp==0)//� ������� ������ �������
		  {
			p->MBInternals.TxState=7;
		  }
		  else//������, � ������� ������� �� ������
		  {
			p->MBInternals.ToSend|=0x80;//����������� ����� ������
			p->MBInternals.TxState=p->MBInternals.temp+3;
		  }
		}
		else if (p->MBInternals.temp==5)       // ������� write Coil
		{
		  p->MBInternals.ToSend=p->MBInternals.temp;
		  x=(p->MBInternals.In[4]<<8)+p->MBInternals.In[5];//������
		  p->MBInternals.temp=ModBus_FindVocAddr(p,mbodC,\
									   p->MBInternals.NumOfCs, 1,\
									   (p->MBInternals.In[2]<<8)+p->MBInternals.In[3],\
									   1,\
									   p->MBInternals.MiddleOfCs, p->MBInternals.InitialStepOfCs);
		  if ((x!=0xFF00)&&(x!=0x0000))//������ �� ������� - ����� ������ 0xFF00 � 0x0000
			p->MBInternals.temp=3;//��� ����� �� ModBus_FindVocAddr ������� ������
		  if (p->MBInternals.temp==0)//� ������� ������ �������
		  {
			p->MBInternals.TxState=12;
			if (p->MBInternals.In[4]==0) // �������� ��� �������� - reset bit
			  *(Uint16 *)(p->MBInternals.Addr->addr)&=(0xFFFF-(1<<p->MBInternals.Addr->type_or_acc));
			else                                            // set bit
			  *(Uint16 *)(p->MBInternals.Addr->addr)|=(1<<p->MBInternals.Addr->type_or_acc);
			p->Refresh=1;
		  }
		  else//������, � ������� ������� �� ������
		  {
			p->MBInternals.ToSend|=0x80;//����������� ����� ������
			p->MBInternals.TxState=p->MBInternals.temp+3;
		  }
		}
		else if (p->MBInternals.temp==6)  // ������� write HR
		{
		  p->MBInternals.ToSend=p->MBInternals.temp;
		  p->MBInternals.temp=ModBus_FindVocAddr(p,mbodHR,\
									   p->MBInternals.NumOfHRs, 16,\
									   (p->MBInternals.In[2]<<8)+p->MBInternals.In[3],\
									   1,\
									   p->MBInternals.MiddleOfHRs, p->MBInternals.InitialStepOfHRs);
		  if (p->MBInternals.temp==0)//� ������� ������ �������
		  {
			p->MBInternals.TxState=12;
			//�������� ��� �������� - ������ ��������
			*(Uint16 *)(p->MBInternals.Addr->addr)=(p->MBInternals.In[4]<<8)+p->MBInternals.In[5];
			p->MBInternals.Addr->type_or_acc = MB_VAR_WRITE;
		  }
		  else//������, � ������� ������� �� ������
		  {
			p->MBInternals.ToSend|=0x80;//����������� ����� ������
			p->MBInternals.TxState=p->MBInternals.temp+3;
		  }
		}
		else//������� �� �������������� �������
		{
		  p->MBInternals.ToSend=p->MBInternals.temp|0x80;//����������� ����� ������
		  p->MBInternals.TxState=2;
		}
	  }
	  else if (p->MBInternals.TxState==12)     // send addr hi for write C
	  {
		p->MBInternals.TxState=13;
		p->MBInternals.ToSend=p->MBInternals.In[2];
	  }
	  else if (p->MBInternals.TxState==13)     // send addr low for write C
	  {
		p->MBInternals.TxState=14;
		p->MBInternals.ToSend=p->MBInternals.In[3];
	  }
	  else if (p->MBInternals.TxState==14)     // send data hi for write C
	  {
		p->MBInternals.TxState=15;
		p->MBInternals.ToSend=p->MBInternals.In[4];
	  }
	  else if (p->MBInternals.TxState==15)     // send data hi for write C
	  {
		p->MBInternals.TxState=3;
		p->MBInternals.ToSend=p->MBInternals.In[5];
	  }
	  else if (p->MBInternals.TxState==10)     // send length read Coils
	  {
		p->MBInternals.TxState=11;
		p->MBInternals.In[5]=p->MBInternals.In[5]+(p->MBInternals.In[4]<<8);
		p->MBInternals.ToSend=(p->MBInternals.In[5]+7)>>3;
	  }
	  else if (p->MBInternals.TxState==11)  // send data read Coils
	  {
		p->MBInternals.ToSend=0;
		for (x=0; x<8; x++)//����� ��������� 8 ������� ���������� �� ���
		{
		  if (p->MBInternals.In[5]!=0)//���������� ������������� ��������� �������
		  {
			//�������� �������� �������
			p->MBInternals.ToSend|=(((*(Uint16 *)(p->MBInternals.Addr->addr))>>(p->MBInternals.Addr->type_or_acc))&0x01)<<x;
			p->MBInternals.Addr++;
			p->MBInternals.In[5]--;
		  }
		  if (p->MBInternals.In[5]==0)//���� ��� ���������
			p->MBInternals.TxState=3;
		}
	  }
	  else if (p->MBInternals.TxState==7) // send length read HR
	  {
		p->MBInternals.TxState=8;
		p->MBInternals.ToSend=p->MBInternals.In[5]<<1;
	  }
	  else if (p->MBInternals.TxState==8) // send HR high word
	  {
		p->MBInternals.TxState=9;
		//x= *p->MBInternals.Addr->addr;
		p->MBInternals.temp=*(Uint16 *)(p->MBInternals.Addr->addr);

		p->MBInternals.ToSend=p->MBInternals.temp>>8;
	  }
	  else if (p->MBInternals.TxState==9) // send HR low word
	  {
		p->MBInternals.ToSend=p->MBInternals.temp&0xFF;
		p->MBInternals.Addr->type_or_acc = MB_VAR_READ;
		p->MBInternals.Addr+=1;
		p->MBInternals.In[5]--;//���������� ���-�� ����������� ���������� �� ������� �������
		if (p->MBInternals.In[5]==0)//���� ��� ���������� ����� ���� (��� ���������� ���������)
		  p->MBInternals.TxState=3;
		else
		  p->MBInternals.TxState=8;
	  }
	  else if (p->MBInternals.TxState==2)      // no such function
	  {
		p->MBInternals.ToSend=1;
		p->MBInternals.TxState=3;
	  }
	  else if (p->MBInternals.TxState==5)      // send error 2
	  {
		p->MBInternals.ToSend=2;
		p->MBInternals.TxState=3;
	  }
	  else if (p->MBInternals.TxState==6)      // send error 3
	  {
		p->MBInternals.ToSend=3;
		p->MBInternals.TxState=3;
	  }
	  else if (p->MBInternals.TxState==3)      // tx crc low
	  {
		p->MBInternals.ToSend=p->MBInternals.TxCRC&0x00FF;
		p->MBInternals.TxState=4;
	  }
	  else if (p->MBInternals.TxState==4)      // tx crc high
	  {
		p->MBInternals.ToSend=p->MBInternals.TxCRC&0x00FF;
		p->MBInternals.TxState=0;
	  }
	  else
		p->MBInternals.TxState=0;

	  p->MBInternals.TimeOut=p->MBInternals.TimeOut2_5;

	  ModBus_Tx(p,p->MBInternals.ToSend);

	  p->MBInternals.TxCRC^=p->MBInternals.ToSend;
	  for (RxReg=0; RxReg<8; RxReg++)
		if (p->MBInternals.TxCRC&0x01)
		{
		  p->MBInternals.TxCRC>>=1;
		  p->MBInternals.TxCRC^=p->MBInternals.MagicNumber;
		}
		else
		  p->MBInternals.TxCRC>>=1;
	  return;

  }
}

//!��������������� ������� ������


//!������� ���� ������� � ������� � ���������� ������ �� ���� � p->MBInternals.Addr
//!����������:
//!       0 - ���� �����
//!       3 - ���� ������ �����������
//!       2 - ������ � ������

//! \memberof TModBus
int16 ModBus_FindVocAddr(TModBus *p,volatile MB_Record /*const*/ Table[], Uint16 TableSize, int16 Type, Uint16 Index, int16 NumOfIndexs, int16 Mid, int16 Step)
{
  int16 x=0;
  if (Type==16)
  {
    if (NumOfIndexs==0)
      return(3);
    if (NumOfIndexs>0x7D)
      return(3);
  }
  else
  {
    if (NumOfIndexs==0)
      return(3);
    if (NumOfIndexs>0x7D0)
      return(3);
  }
  x+=Mid;
  Step<<=1;
  do
  {
    Step>>=1;
    if (Index==Table[x].index)
    {
      if ((x+NumOfIndexs)>TableSize)
        return(2);
      p->MBInternals.Addr=&Table[x];
      return(0);
    }
    else if (Index<Table[x].index)
      x-=Step;
    else
    {
      x+=Step;
      if (x>=TableSize)
        x=(TableSize-1);
    }
  }
  while (Step!=0);
  return (2);
  ;
}

/*@}*/


