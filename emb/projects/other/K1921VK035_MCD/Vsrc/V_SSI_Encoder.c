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

	// ��������� ����� ��� SPI
	GPIOB->ALTFUNCSET = (1 << 5) | (1 << 6); // ������������ (SPI_SCK)

	// ��������� ������ SPI
	// ������������ ������ SPI � ����� "src/system_K1921VK035.c" ��������� �� fIN = 25 ���
	// ��� ������� �������� ��� ����� ��� ��������.
	// SSPCPSR - ������ ��������, � ��������� 2 ... 254, ����� ���� ������ ������ (������� ��� ������ ��������� ����� 0)
	// SSPCR0.bit.SCR - ������ �������� �� 0 �� 255.
	// ������� � ����� BitRate = fIN / ( CPSR * (SCR + 1) )

	SPI->IMSC = 0x0;	// ��������� ��� ����������
	SPI->DMACR = 0;		// ��������� DMA
	SPI->ICR = 0x3;		// ����� ���������� �� ������ ������ ("������������ FIFO �����" � "������������� FIFO �����")

	SPI->CPSR = 4;				// ������� ������� ������� �� 4



	// � CR0 ������������� ������ �������� �������, ���������� � ����� ������ ��������.
	//
	// ������ �������� = 62, ����� f_ssp = 25 ��� / (4 * (62 + 1)) = 99,2 ���
	//
	// ��������� ���� � ���������� ��� ������ � ������ SPI
	// �� �������� �� ������ ���� �����: �� ������� ��������� ������ �� ��������� � ����
	// ���������� ������� ����� ������, � � ������ �������� ������� ������� �� �� �����.
	// ����� ���� ������ �� ����� �������� �� �������� ������, � ������ ��������� �� ����
	// �� ��������. �� ��� ���� �� ������ ������� ������ ������ ���������� �� ����, � ������
	// ������� ��� �������� ������ ���� ��������.
	// ����� ���� �� �� ���� �������������, � ��� ���� ��������� � ���������.
	//
	// ������ ����� �� 1 ������, ��� ����� � ��������, ����� ���� (12 + 1) = 13 ���, �� ������� ������ �������
	//
	// � ����� �������� �����, ������ ����� �������
	//SPI->CR0_bit.FRF = 0x0;		// SSI �������� � ������ SPI, ��� ��������� ������, �� ������ ������ ������ ������
	//SPI->CR0_bit.SPO = 0x0;		// � ������ �������� CLK � ���� (����� �������� ��������� � �������)
	//SPI->CR0_bit.SPH = 0x0;		// ������� ������ �� ��������� ������ ������������� (����� �������� ��������� �� ���������)
	//SPI->CR0_bit.SCR = 62;		// ������ �������� = 62 + 1 = 63
	//SPI->CR0_bit.DSS = SSI_ENC_RESOLUTION; // ������ ����� 12 + 1 = 13 ���
	SPI->CR0 = (SSI_ENC_RESOLUTION << SPI_CR0_DSS_Pos) | (62 << SPI_CR0_SCR_Pos);

	// � ���� ������������ ��������� �� ������� ����, ��� ��� �������������, ��
	// ��� �������� �� ����������� ������������ ����� ���������
	//SPI->CR1_bit.MS = 0;		// ����� - ������
	//SPI->CR1_bit.RXIFLSEL = 0;	// ������� FIFO �� ���� = 0 (FIFO �� ������������)
	//SPI->CR1_bit.TXIFLSEL = 0;	// ������� FIFO �� �������� = 0 (FIFO �� ������������)
	//SPI->CR1_bit.SSE = 1;		// ��������� ������ SPI
	SPI->CR1 = (1 << SPI_CR1_SSE_Pos);
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

	if (SPI->SR_bit.BSY == 0){//SPI ��������
		Data_read = SPI->DR & SSI_ENC_DATA_MASK;//��� � ������� (����� �� 0 �� resol) � ��������� ������� ��������
		SPI->DR = 0xff;//���������� ��� ������, �������, ����� ������������ ���


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

