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
 
 \file      V_SSI_Encoder.c
 \brief     ������ ������ �������� � ��������� ��� ������ ��������� ��������, ����������� �� ���������� SSI (��. TSSI_Encoder)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/04/2016

 \addtogroup V_QEP
 @{*/

#include "DSP.h"
#include "V_IQmath.h"
#include "V_SSI_Encoder.h"
#include "math.h"
#include "stdlib.h"
#include "main.h"

//! �������������

//! \memberof TSSI_Encoder
void SSI_Encoder_init(TSSI_Encoder *p) {
	volatile long delay;
	volatile Uint32 tempREG;


	// ��������� ��� SPI
#ifdef HW_MOTORCONTROLBOARD
#define SSI_NT_SPI NT_SPI0 //��������� ������ SPI
	NT_GPIOA->ALTFUNCSET = (1 << 6); //SPI_CLK0
	NT_GPIOA->ALTFUNCSET = (1 << 7); //SPI_RXD0
	NT_COMMON_REG->GPIOPCTLA_bit.PIN6 = 0;
	NT_COMMON_REG->GPIOPCTLA_bit.PIN7 = 0;
#else

#define SSI_NT_SPI NT_SPI2 //��������� ������ SPI
	//SPI-SOMI - �� VectorCard ���� 88, �� ����� B15, SPI_RXD2
	//SPI-SIMO - �� VectorCard ���� 38, �� ����� C6, SPI_TXD2
	//SPI-CLK - �� VectorCard ���� 39, �� �����  B14, SPI_CLK2
	//SPI-STE - �� VectorCard ���� 89, �� �����  B13, SPI_FSS2
	//����� texas DRV8301-HC-EVM ��������� ���, ��� ��������������� - ��� ������� ����������.
	//����� ������� ��� ��������. ��������� ������� ����������� � ������������ �����.

	NT_GPIOB->ALTFUNCSET = (1 << 13);//���-������
	NT_GPIOB->ALTFUNCSET = (1 << 14) | (1 << 15);
	NT_GPIOC->ALTFUNCSET = (1 << 6);//SIMO
	NT_COMMON_REG->GPIOPCTLB_bit.PIN13 = 2;//���-������
	NT_COMMON_REG->GPIOPCTLB_bit.PIN14 = 2;
	NT_COMMON_REG->GPIOPCTLB_bit.PIN15 = 2;
	NT_COMMON_REG->GPIOPCTLC_bit.PIN6 = 2;//SIMO
#endif

	// ��������� ������������ SSP ������
	// ����� 4 ������, �� ������ ������ �� 8 ��� �� �������� SSP_CLK_CTRL � �� ��� ���� �� UART_SSP_CLK_SEL

	// UART_SSP_CLK_SEL
	// �� ������ ����� ����� �� ������ �� 4-�� ������� SSP ��������� �� ��� ���� ��� ������ ��������� ������������ 0x0000XX00
	// "00" - � �������� �������� ������������ ������ SSP ���������� ��������� ������� 100 ���, ����� ������� f_SSP_IN = SysClk = 100 MHz

	// SSP_CLK_CTRL
	// ������� ��� ��������� ������������ (1 - ���������)
	// ������ ��� ��������� ������� ������� f_SSP_IN ��������� ��������� ������� (0 - �� ������, 1 - ������)
	// ������� ����� �������� �������� ������� ����� ���������:
	//  X - ������� �� ������� SSPclk = f_SSP_IN /( 2 * (X +1) )
	// �� ������������ �� ���� SSP - ����������� ������� ��� ������ ������ � ������� � ������ � �����,
	// f_SSP_IN > 22.12 MHz, ������� 25 ��� �������
#ifdef HW_MOTORCONTROLBOARD
	//��� DRV8301_SPI �� ������, �.�. ���� ����� �������� � ��� �����
	tempREG = NT_COMMON_REG->UART_SPI_CLK_SEL;// ����� tempREG, ����� �� ������ ������ ����, ���������� �� ������������ UART'a
	tempREG &= 0xFFFF00FF;
	NT_COMMON_REG->UART_SPI_CLK_SEL = tempREG;
	NT_COMMON_REG->SPI_CLK = 0x07070707;// ��������� ������������, ��������� ������� �������, ������ �� 4 - 25 ���
#endif

	// ��������� ������ ������ SPI
	// ����������� ��������� ������������.
	// ���������� ����� ������� f_SSP_IN �������� ��� ����� ��� ��������.
	// SSPCPSR - ������ ��������, � ��������� 2 ... 254, ����� ���� ������ ������ (������� ��� ������ ��������� ����� 0)
	// SSPCR0.bit.SCR - ������ �������� �� 0 �� 255.
	// ������� � ����� BitRate = f_SSP_IN / ( SSPCPSR * (SCR + 1) )

	SSI_NT_SPI->SPI_CR1 = 0;// ����� - ������, LoopBack ��������, ��� ������ SSP ���� ��������
	SSI_NT_SPI->SPI_IMSC = 0x0;		// ��������� ��� ����������
	SSI_NT_SPI->SPI_DMACR = 0;		// ��������� DMA
	SSI_NT_SPI->SPI_ICR = 0x3;	// ������� ���������� ("������������ FIFO �����" � "������������� FIFO �����")

	SSI_NT_SPI->SPI_CPSR = 4;			// ������� ������� ������� �� 4 -> 6,25 MHz
	SSI_NT_SPI->SPI_CR0_bit.DSS = 12;	// ������ ������ - 12 ���
	SSI_NT_SPI->SPI_CR0_bit.SCR = 0x3F;	// ������ ��������
	SSI_NT_SPI->SPI_CR0_bit.FRF = 0x0;	// �����-�� "����" ��� ��������� Motorola SPI
	SSI_NT_SPI->SPI_CR0_bit.SPH = 0x1;	// �����-�� "����������" ��� ��������� Motorola SPI
	SSI_NT_SPI->SPI_CR0_bit.SPO = 0x0;	// ����� ������� ����� Motorola/TI/Microwire. "0" - �� ��������� Motorola SPI
	SSI_NT_SPI->SPI_CR1_bit.SSE = 1;	// ��������� ������

	p->resol_inv = 1.0 / ((float) p->resol);

	p->read(p);
}


//! ������� ������� �������� � ���������, ���������� � ����������� �������������

//! \memberof TSSI_Encoder
void SSI_Encoder_Calc(TSSI_Encoder *p) {
	p->read(p);
}



void SSI_Encoder_Read(TSSI_Encoder*p) {
	_iq theta_elec_temp;
	Uint16 Data_read=0;
	_iq theta_mech_temp;

	if (SSI_NT_SPI->SPI_SR_bit.BSY == 0){//SPI ��������
		Data_read = SSI_NT_SPI->SPI_DR;//��� � ������� (����� �� 0 �� resol)
		SSI_NT_SPI->SPI_DR = 0xff;//���������� ��� ������, �������, ����� ������������ ���


		if (p->rotation_dir)//�������� ����������� ��������
			Data_read=(p->resol-1)-Data_read;//������ - �������
		p->Poscnt_res=Data_read;
	}

	//������� ���� � ������ �� ������� � ������������ ����
	//����� ������ �� float - ���������� ���������� � IQ
	p->theta_mech = _IQ((float )p->Poscnt_res * p->resol_inv); //������ ������������� ����
	p->theta_mech &= 0x00FFFFFF;
	//������ ����
	if (p->theta_mech_filterK!=0){
        p->theta_mech_filtered=p->theta_mech_filtered+_IQmpy(p->theta_mech_filterK,((p->theta_mech-p->theta_mech_filtered+_IQ(0.5))&0x00FFFFFF)-_IQ(0.5));
        p->theta_mech_filtered&=0x00FFFFFF;
	}else
		p->theta_mech_filtered=p->theta_mech;

    // ������� ���������� ������ ��������.
    if (p->prevThetaMech - p->theta_mech_filtered > _IQ(0.5))
		p->RevolutionCounter++;
	if (p->prevThetaMech - p->theta_mech_filtered < _IQ(-0.5))
		p->RevolutionCounter--;
	p->prevThetaMech=p->theta_mech_filtered;

	//���� � ������ ��� ��������� �� �������, ����������
	p->Poscnt_resContinouosLong=p->Poscnt_res+(p->resol*p->RevolutionCounter);
	p->Poscnt_resContinouosInt=p->Poscnt_resContinouosLong;//����� ���� ������� �������� � 16�� ��������� ������������
	p->Poscnt_resContinouosInt8=p->Poscnt_resContinouosLong&0xF;//����� ������ ����� � ������� ��������

	//������� ���� � ������ ���������� (�� ���������� ���������) � ������������ ����
	//�� 127 �������� �� ������������, �� ��� ���� ��������
	p->theta_mechContinouos = p->theta_mech_filtered + _IQ(p->RevolutionCounter); //������ ������������� ����
	p->theta_elecContinouos = p->theta_mechContinouos*p->pole_pairs+ p->AngleOffset;//������������� ���� ���������� (�� ����������)

	//������ �������������� ��������� ���������� �� ���������� 360 ��������
	p->theta_el_tmp = p->theta_mech_filtered*p->pole_pairs + p->AngleOffset;
	p->theta_elec = p->theta_el_tmp & 0x00FFFFFF;

}



/*@}*/

