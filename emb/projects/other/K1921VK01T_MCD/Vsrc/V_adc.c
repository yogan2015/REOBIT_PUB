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
 
 \file      V_adc.c
 \brief     ������ ��������� ��� (��. TAdcDrv)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_adc 
 @{*/

#include "DSP.h"
#include "V_adc.h"
#include "main.h"

//!�������������.

//! ������������� ���������� � ��� ��������� ������. ������ ��� ���������, �������.
//! � ������ ������ ��������� ���������� �� ������� �������,������� ��������
//! ����� ������� ���, ����� �������� ����� ���������� ������� ��� (��������� ��� ��������
//! �������� ����)
//������ ��������� ������������ �� ������� NT_PWM3, ������� ��������������� � ������� ��������� ���.
//������������ ��������� ������������ � ����. ������ ����� ��� �������� �� ��������� ��������� � ���� ������ �� 16 ���������.
//� ���������� � �������� 10 ��� ������ ���������� �� ���� � ������������ � ��������� ������� (������ ���������� ������).
//� ��� �� ���������� �� ���������� ������� ������� N ��������� ����� � �� ��� ����������� ������� ��������������.
//����� ������� ��� ���������� N ������� �� ������� ��� � ����� F���/10���. ���� ������� ��� ������ 10 ���, �� ������� ���� �������, ���� ������ 40 ��� - 4 �������.
//� ������������ �������� �������� ����������� ������������� �����, � ��� ���������� �� ����������� ���������, � ���������� ���������� ������������� ��������� ���������.

//! \memberof TAdcDrv
void AdcDrv_init(TAdcDrv *p) {
	// ������ ���� �����������
	NT_ADC->ACTSS = 0;

	// ����� ��������� ���������� � ���������
	NT_ADC->SEQ[0].OP = 0;
	NT_ADC->SEQ[1].OP = 0;
	NT_ADC->SEQ[2].OP = 0;
	NT_ADC->SEQ[3].OP = 0;
	NT_ADC->SEQ[4].OP = 0;
	NT_ADC->SEQ[5].OP = 0;
	NT_ADC->SEQ[6].OP = 0;
	NT_ADC->SEQ[7].OP = 0;

	//�������� 2, 3, 4 � 5 ����������, �� ������ �� ���������� �������� (����� ���� ������� - 16 �����)
	//���������� � ������������� ������������ ������ ���� ���������, ���� ���������, �� ���������� ��������� (���������� ������� �������, ���������� �������� ����������� ���������).
	NT_ADC->ACTSS_bit.ASEN2 = 1;
	NT_ADC->ACTSS_bit.ASEN3 = 1;
	NT_ADC->ACTSS_bit.ASEN4 = 1;
	NT_ADC->ACTSS_bit.ASEN5 = 1;
	NT_ADC->ACTSS_bit.ASEN6 = 1;
	//������ ����� ���������� (��� 4 ����������, ��� �� ���� 4 ����������, ���������� ������)
	NT_ADC->IM_bit.MASK4 = 1;
	//����������� �������� �������
	NT_ADC->EMUX_bit.EM2 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
	NT_ADC->EMUX_bit.EM3 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
	NT_ADC->EMUX_bit.EM4 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
	NT_ADC->EMUX_bit.EM5 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
	NT_ADC->EMUX_bit.EM6 = 8; //������ ������������ �� ������� SocA  ����� ��� 3 ��� vector card
	NT_ADC->PSSI_bit.SS2 = 1; //��������� ����������� ������ ����������
	NT_ADC->PSSI_bit.SS3 = 1; //��������� ����������� ������ ����������
	NT_ADC->PSSI_bit.SS4 = 1; //��������� ����������� ������ ����������
	NT_ADC->PSSI_bit.SS5 = 1; //��������� ����������� ������ ����������
	NT_ADC->PSSI_bit.SS6 = 1; //��������� ����������� ������ ����������

	//����������� ���������� ������������ ����������
	NT_ADC->SEQ[2].CTL_bit.RCNT = 0; //���������� �� ���������
	NT_ADC->SEQ[3].CTL_bit.RCNT = 0; //���������� �� ���������
	NT_ADC->SEQ[4].CTL_bit.RCNT = 0; //���������� �� ���������
	NT_ADC->SEQ[5].CTL_bit.RCNT = 0; //���������� �� ���������
	NT_ADC->SEQ[6].CTL_bit.RCNT = 0; //���������� �� ���������
	//����������� ������� ����������
	NT_ADC->SEQ[2].CTL_bit.ICNT = 0; //���������� ����� ������� �������
	NT_ADC->SEQ[3].CTL_bit.ICNT = 0; //���������� ����� ������� �������
	NT_ADC->SEQ[4].CTL_bit.ICNT = 0; //���������� ����� ������� �������
	NT_ADC->SEQ[5].CTL_bit.ICNT = 0; //���������� ����� ������� �������
	NT_ADC->SEQ[6].CTL_bit.ICNT = 0; //���������� ����� ������� �������
	//NT_ADC->SEQUENCER.SEQ0.ADCSSTMR.bit.TMR

	NT_ADC->PP_bit[0].OM = 0x3; //OM2-OM0 = �011� All blocks active (ADC plus internal buffers plus internal bandgap).
	NT_ADC->PP_bit[1].OM = 0x3;
	NT_ADC->PP_bit[2].OM = 0x3;
	NT_ADC->PP_bit[3].OM = 0x3;
	NT_ADC->PP_bit[4].OM = 0x3;
	NT_ADC->PP_bit[5].OM = 0x3;
	NT_ADC->PP_bit[6].OM = 0x3;
	NT_ADC->PP_bit[7].OM = 0x3;
	NT_ADC->PP_bit[8].OM = 0x3;
	NT_ADC->PP_bit[9].OM = 0x3;
	NT_ADC->PP_bit[10].OM = 0x3;
	NT_ADC->PP_bit[11].OM = 0x3;

	//�������� ����������� ������ ���
	//����������� ����������� ����������� ������ ���
	NT_ADC->PP_bit[0].ENA = 1;	//�������� ������ ���
	NT_ADC->PP_bit[1].ENA = 1;
	NT_ADC->PP_bit[2].ENA = 1;
	NT_ADC->PP_bit[3].ENA = 1;
	NT_ADC->PP_bit[4].ENA = 1;
	NT_ADC->PP_bit[5].ENA = 1;
	NT_ADC->PP_bit[6].ENA = 1;
	NT_ADC->PP_bit[7].ENA = 1;
	NT_ADC->PP_bit[8].ENA = 1;
	NT_ADC->PP_bit[9].ENA = 1;
	NT_ADC->PP_bit[10].ENA = 1;
	NT_ADC->PP_bit[11].ENA = 1;

#ifdef HW_VECTORCARD_DRV8301_EVM
	// ����������� ����������� ������ �� ���� ����� ��� -
	// �� ������������ ����� �������� ������������ ������, ��� �� ADC result
	//���������� ���������� ������� ����� EXT_IA-FB � EXT_IB-FB (� ������� ��������������), ��� ��� ��-�� ��������� ��������
	//���� ������ �� ������ IA-FB ��� ����������������� ����� (��� � VectorCard) ���� ������� ������ �� DCDC, ������� �� ���� ������ 5�
	NT_ADC->DCCTL_bit[2].CHNL = 2;	//Udc
	NT_ADC->DCCTL_bit[6].CHNL = 6;	//��� ���� B
	NT_ADC->DCCTL_bit[14].CHNL = 14;	//��� ���� A

	//���������� ������ ������������
	NT_ADC->SEQ[2].DCP_bit.CMP2 = 1;	//Udc
	NT_ADC->SEQ[3].DCP_bit.CMP6 = 1;	//��� ���� B
	NT_ADC->SEQ[4].DCP_bit.CMP14 = 1;	//��� ���� A

	//����� ������� ��� ���������
	NT_ADC->SEQ[2].MUX_bit.CH2 = 1;	//Udc
	NT_ADC->SEQ[3].MUX_bit.CH6 = 1;	//��� ���� B
	NT_ADC->SEQ[4].MUX_bit.CH14 = 1;	//��� ���� A
#endif

#ifdef HW_VECTORCARD_DRV8312_EVM
	// ����������� ����������� ������ �� ���� ����� ��� -
	// �� ������������ ����� �������� ������������ ������, ��� �� ADC result
	//���������� ���������� ������� ����� EXT_IA-FB � EXT_IB-FB (� ������� ��������������), ��� ��� ��-�� ��������� ��������
	//���� ������ �� ������ IA-FB ��� ����������������� ����� (��� � VectorCard) ���� ������� ������ �� DCDC, ������� �� ���� ������ 5�
	NT_ADC->DCCTL_bit[2].CHNL = 2;	//Udc
	NT_ADC->DCCTL_bit[5].CHNL = 5;	//��� ���� B
	NT_ADC->DCCTL_bit[9].CHNL = 9;	//��� ���� A

	//���������� ������ ������������
	NT_ADC->SEQ[2].DCP_bit.CMP2 = 1;	//Udc
	NT_ADC->SEQ[3].DCP_bit.CMP5 = 1;	//��� ���� B
	NT_ADC->SEQ[4].DCP_bit.CMP9 = 1;	//��� ���� A

	//����� ������� ��� ���������
	NT_ADC->SEQ[2].MUX_bit.CH2 = 1;	//Udc
	NT_ADC->SEQ[3].MUX_bit.CH5 = 1;	//��� ���� B
	NT_ADC->SEQ[4].MUX_bit.CH9 = 1;	//��� ���� A
#endif

//��� ����������� ��40.4
#ifdef HW_VECTOR_MK_40_4
	NT_ADC->DCCTL_bit[1].CHNL = 1;	//Udc
	NT_ADC->DCCTL_bit[17].CHNL = 17;	//��� ���� B
	NT_ADC->DCCTL_bit[16].CHNL = 16;	//��� ���� A

	//���������� ������ ������������
	NT_ADC->SEQ[2].DCP_bit.CMP1 = 1;	//Udc
	NT_ADC->SEQ[3].DCP_bit.CMP17 = 1;	//��� ���� B
	NT_ADC->SEQ[4].DCP_bit.CMP16 = 1;	//��� ���� A

	//����� ������� ��� ���������
	NT_ADC->SEQ[2].MUX_bit.CH1 = 1;	//Udc
	NT_ADC->SEQ[3].MUX_bit.CH17 = 1;	//��� ���� B
	NT_ADC->SEQ[4].MUX_bit.CH16 = 1;	//��� ���� A
#endif

#ifdef HW_MOTORCONTROLBOARD
	// ����������� ����������� ������ �� ���� ����� ��� -
	// �� ������������ ����� �������� ������������ ������, ��� �� ADC result
	NT_ADC->DCCTL_bit[4].CHNL = 4;		//Udc
	NT_ADC->DCCTL_bit[0].CHNL = 0;		//��� ���� A
	NT_ADC->DCCTL_bit[2].CHNL = 2;		//��� ���� C
	NT_ADC->DCCTL_bit[16].CHNL = 16;	//�����������
	NT_ADC->DCCTL_bit[10].CHNL = 10;	//�������

	//���������� ������ ������������
	NT_ADC->SEQ[2].DCP_bit.CMP4 = 1;	//Udc
	NT_ADC->SEQ[3].DCP_bit.CMP0 = 1;	//��� ���� A
	NT_ADC->SEQ[4].DCP_bit.CMP2 = 1;	//��� ���� C
	NT_ADC->SEQ[5].DCP_bit.CMP16 = 1;	//�����������
	NT_ADC->SEQ[6].DCP_bit.CMP10 = 1;   //�������

	//����� ������� ��� ���������
	NT_ADC->SEQ[2].MUX_bit.CH4 = 1;		//Udc
	NT_ADC->SEQ[3].MUX_bit.CH0 = 1;		//��� ���� A
	NT_ADC->SEQ[4].MUX_bit.CH2 = 1;		//��� ���� C
	NT_ADC->SEQ[5].MUX_bit.CH16 = 1;	//�����������
	NT_ADC->SEQ[6].MUX_bit.CH10 = 1;   //�������
#endif

}


//!������ ��� � �������� ��������� ������� ���� ������� ���������� (������ 10���).

//! ���������� ���������� ���������� ��� �������� � ����������� � ������ IQ24.
//! ���� ��� ��� ��������� �������� ����������� �� ��������� ���������

//! \memberof TAdcDrv
#if (defined(HW_VECTORCARD_DRV8301_EVM)) || (defined(HW_VECTORCARD_DRV8312_EVM)) || (defined(HW_VECTORCARD_SIMULATOR)) || (defined(HW_NIIET_BOARD_SIMULATOR)) || (defined(HW_VECTOR_MK_40_4))
void AdcDrv_fast_calc(TAdcDrv *p) {

#if (!defined(HW_VECTORCARD_SIMULATOR)) && (!defined(HW_NIIET_BOARD_SIMULATOR))
	while (NT_ADC->SEQ[2].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		//��������� ����� �� ���� ��������� ������ � ���� ��
		p->UdcBuf[p->UdcPointer] = NT_ADC->SEQ[2].FIFO_bit.DATA;
		p->UdcPointer = (++p->UdcPointer) & 3;
	}
	while (NT_ADC->SEQ[3].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		p->IBBuf[p->IBPointer] =
				(int16) ((NT_ADC->SEQ[3].FIFO_bit.DATA) << 4) ^ 0x8000;
		p->IBPointer = (++p->IBPointer) & 3;
	}
	while (NT_ADC->SEQ[4].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		p->IABuf[p->IAPointer] =
				(int16) ((NT_ADC->SEQ[4].FIFO_bit.DATA) << 4) ^ 0x8000;
		p->IAPointer = (++p->IAPointer) & 3;
	}
	while (NT_ADC->SEQ[5].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		//��������� ����� �� ���� ��������� ������ � ���� ��
		//��� ��� ����������� �������� � ������� �������� �� �����,
		//�� ��� ��������� ���� �� ����� ������������ ������ ����� (��� ��� �����)
		p->T_temp = NT_ADC->SEQ[5].FIFO_bit.DATA;
	}
	while (NT_ADC->SEQ[6].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		//��������� ����� �� ���� ��������� ������ � ���� ��
		p->ref_temp = NT_ADC->SEQ[6].FIFO_bit.DATA;
	}

	p->Udc_temp = 0;
	p->IB_temp = 0;
	p->IA_temp = 0;


	//����������
	int i;
	for (i = 0; i < p->IASampleLength; i++) {//����� ������ ����� �����, ������� � ����� �����
		int j = p->IAPointer - i;
		if (j < 0)	//���� ������� ����� 0 - �������� � 3-� (������ �� 4 �����)
			j = 4 + j;
		p->IA_temp += p->IABuf[j];
	}
	//����� �� ����� ������� (1-4 �����)
	p->IA_temp = p->IA_temp / p->IASampleLength;

	for (i = 0; i < p->IBSampleLength; i++) {//����� ������ ����� �����, ������� � ����� �����
		int j = p->IBPointer - i;
		if (j < 0)	//���� ������� ����� 0 - �������� � 3-� (������ �� 4 �����)
			j = 4 + j;
		p->IB_temp += p->IBBuf[j];
	}
	//����� �� ����� ������� (1-4 �����)
	p->IB_temp = p->IB_temp / p->IBSampleLength;

	for (i = 0; i < p->UdcSampleLength; i++) {//����� ������ ����� �����, ������� � ����� �����
		int j = p->UdcPointer - i;
		if (j < 0)	//���� ������� ����� 0 - �������� � 3-� (������ �� 4 �����)
			j = 4 + j;
		p->Udc_temp += p->UdcBuf[j];
	}
	//����� �� ����� ������� (1-4 �����), ������� �������� �������� ����������� �������
	p->Udc_temp = p->Udc_temp / p->UdcSampleLength;

#endif
#ifdef HW_VECTORCARD_DRV8312_EVM
	//�������� HW_VECTORCARD_DRV8312_EVM ���������� �� HW_VECTORCARD_DRV8301_EVM � 5 ��� ������� ������������� �������� � ������ ������
	p->Imeas_a = p->IaGainNom * ((-(p->IA_temp/5) + p->Imeas_a_offset));
	p->Imeas_b = p->IbGainNom * ((-(p->IB_temp/5) + p->Imeas_b_offset));
	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);
	p->Imeas_c = -p->Imeas_a - p->Imeas_b;
#endif

#if defined(HW_VECTORCARD_DRV8301_EVM) || defined(HW_VECTOR_MK_40_4)
	p->Imeas_a = p->IaGainNom * ((p->IA_temp + p->Imeas_a_offset));
	p->Imeas_b = p->IbGainNom * ((p->IB_temp + p->Imeas_b_offset));
	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);
	p->Imeas_c = -p->Imeas_a - p->Imeas_b;
#endif



#if (defined(HW_VECTORCARD_SIMULATOR)) || (defined(HW_NIIET_BOARD_SIMULATOR))
	//��������� ��������� �������� ��� � ��������� 0-4095
	p->IA_temp=(int16) ((model.adc_code_iA<<4) ^ 0x8000);
	p->IB_temp=(int16) ((model.adc_code_iB<<4) ^ 0x8000);
	p->IC_temp=(int16) ((model.adc_code_iC<<4) ^ 0x8000);
	p->ID_temp=(int16) ((model.adc_code_iD<<4) ^ 0x8000);
	p->Udc_temp=model.adc_code_Udc;

	p->Imeas_a = p->IaGainNom * ((p->IA_temp + p->Imeas_a_offset));
	p->Imeas_b = p->IbGainNom * ((p->IB_temp + p->Imeas_b_offset));
	if ((model.MotorType==MODEL_INDUCTION_MOTOR) || (model.MotorType==MODEL_SYNC_MOTOR)){//��� ��������� ���������� ���������� ��� �����������
		p->Imeas_c = -p->Imeas_a - p->Imeas_b;//��� ������� �� ������ ��������
	}
	else{
		p->Imeas_c = p->IcGainNom * ((p->IC_temp + p->Imeas_c_offset));
	}
	p->Imeas_d = p->IdGainNom * ((p->ID_temp + p->Imeas_d_offset));
	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);

#endif

}
#endif

#if defined(HW_MOTORCONTROLBOARD)
void AdcDrv_fast_calc(TAdcDrv *p) {

	while (NT_ADC->SEQ[2].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		//��������� ����� �� ���� ��������� ������ � ���� ��
		p->UdcBuf[p->UdcPointer] = NT_ADC->SEQ[2].FIFO_bit.DATA;
		p->UdcPointer = (++p->UdcPointer) & 3;
	}
	while (NT_ADC->SEQ[3].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		p->IABuf[p->IAPointer] =
				(int16) ((NT_ADC->SEQ[3].FIFO_bit.DATA) << 4) ^ 0x8000;
		p->IAPointer = (++p->IAPointer) & 3;
	}
	while (NT_ADC->SEQ[4].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		p->ICBuf[p->ICPointer] =
				(int16) ((NT_ADC->SEQ[4].FIFO_bit.DATA) << 4) ^ 0x8000;
		p->ICPointer = (++p->ICPointer) & 3;
	}
	while (NT_ADC->SEQ[5].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		//��������� ����� �� ���� ��������� ������ � ���� ��
		//��� ��� ����������� �������� � ������� �������� �� �����,
		//�� ��� ��������� ���� �� ����� ������������ ������ ����� (��� ��� �����)
		p->T_temp = NT_ADC->SEQ[5].FIFO_bit.DATA;
	}
	while (NT_ADC->SEQ[6].FSTAT_bit.FLOAD > 0)	//���� ���� �� ��������
	{
		//��������� ����� �� ���� ��������� ������ � ���� ��
		p->ref_temp = NT_ADC->SEQ[6].FIFO_bit.DATA;
	}

	p->Udc_temp = 0;
	p->IA_temp = 0;
	p->IC_temp = 0;


	//����������
	int i;
	for (i = 0; i < p->IASampleLength; i++) {//����� ������ ����� �����, ������� � ����� �����
		int j = p->IAPointer - i;
		if (j < 0)	//���� ������� ����� 0 - �������� � 3-� (������ �� 4 �����)
			j = 4 + j;
		p->IA_temp += p->IABuf[j];
	}
	//����� �� ����� ������� (1-4 �����)
	p->IA_temp = p->IA_temp / p->IASampleLength;

	for (i = 0; i < p->ICSampleLength; i++) {//����� ������ ����� �����, ������� � ����� �����
		int j = p->ICPointer - i;
		if (j < 0)	//���� ������� ����� 0 - �������� � 3-� (������ �� 4 �����)
			j = 4 + j;
		p->IC_temp += p->ICBuf[j];
	}
	//����� �� ����� ������� (1-4 �����)
	p->IC_temp = p->IC_temp / p->ICSampleLength;

	for (i = 0; i < p->UdcSampleLength; i++) {//����� ������ ����� �����, ������� � ����� �����
		int j = p->UdcPointer - i;
		if (j < 0)	//���� ������� ����� 0 - �������� � 3-� (������ �� 4 �����)
			j = 4 + j;
		p->Udc_temp += p->UdcBuf[j];
	}
	//����� �� ����� ������� (1-4 �����), ������� �������� �������� ����������� �������
	p->Udc_temp = p->Udc_temp / p->UdcSampleLength;


	p->Imeas_a = p->IaGainNom * ((p->IA_temp + p->Imeas_a_offset));
	p->Imeas_c = p->IcGainNom * ((p->IC_temp + p->Imeas_c_offset));
	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);
	p->Imeas_b = -p->Imeas_a - p->Imeas_c;
	p->T_meas = p->TGainNom * (p->T_temp);		//������ ����������� ��� ��������
	p->ref_meas = p->refGainNom * ((p->ref_temp + p->ref_meas_offset));

}
#endif


//!��������� ������.

//!���������� ���������� �������������, ������������ � ���������� ������� �������,
//!����� �� �������� ������������ ����� ���. ������� ������������,
//!�� ������� ���� �������� ���������� � ��� ��������, ����� ��������
//!������������� ������� � �������� �����.

//! ������   p->PvalveGainNom=_IQ16mpy(p->Pvalve_gain,_IQ(1.0/100));
//! Pvalve_gain - �������� � ������� int. �������� ������������� � UniCON.
//!����������, �������� ��������� ������������� ������ �������� ���. � ���������� ������
//!����� 100. �.�. ����� �� ��� ������������ ������, ��� ������������� 100%.

//!_IQ(1.0/100) �������� �������� ��� ��������������� ������������. ��� ��� �������� ���������
//!������������ ����� ��������� � ������������� ������� ���, ��� 100% ������������ 1.0,
//!�� �������������� ����������� (����) ����� 100. �.�. UniCON, �������� �� ������� ����������
//! ����� 1.0 � ������� 8.24 ������ �������� ��� �� 100, ����� ������������ ��������.
//! ����� ����������� ����� ���� ��� 1.0/100, �� ��� ���� ������� ������� �������� ����� ������.
//!���, ��� ����� ��� ������������ �������� _1_I_nom, � ������� 8.24, ��������������� ������� �������� ��
//������� �������� ����, ��������, 200 �. ��� ��� � ����������� �� �������� ��������������� ������� ��� ����� ��������,
//�� ��� ��������, � ������� �� ���������, ������� �������������. ������ _1_I_nom ���� � ������ �����, ��� ���
//�������� ����� ������ �������.

//��� ������������ �������� ��� �������� ����� �� 0 �� 4096.
//��� ������� � ���������� ���������� ������� ���, ����� ���������� �������������� �������� � ������� 8.24,
//��� 1.0 ��� 4096. ����� �������, ����� �������� ����� 4096 �� 4 �������.

//����� �������, PvalveGainNom - ��� ����������� � ������� 24.8. �� ���������� � ���������� ������������� �������
//_IQ16mpy, �������� ������� Pvalve_gain (int) � 1.0/100 � ������� 8.24. ������� IQ ��������
//�� ���� ������������ ����� ������� ��������� � 64 �������� �� ������� ���������� ������ �� Q ��������.
//�.�. _IQ16mpy �������� ����� � ������� IQ24 9������ ��������) �� ������������� ����������� (������ ��������),
//� ����� �������� ��������� �� 16 �������� ������.
//���, � ���������� _IQ16mpy(p->Pvalve_gain,_IQ(1.0/100)); ���������� ������������� ����� 255, ����������
//1.0 � ������� 24.8 ��-�� ������ �� 16 �������� ������.

//�� ��������������� ������ ������� � ����� ����� - ��������� ����������������� ��������� ���.

//! \memberof TAdcDrv
void AdcDrv_slow_calc(TAdcDrv *p) {
	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain, drv_params._1_I_nom) << 1;
	p->IbGainNom = _IQ16mpy(p->Imeas_b_gain, drv_params._1_I_nom) << 1;
	p->IcGainNom = _IQ16mpy(p->Imeas_c_gain, drv_params._1_I_nom) << 1;
	p->IdGainNom = _IQ16mpy(p->Imeas_d_gain, drv_params._1_I_nom) << 1;
	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain, drv_params._1_Udc_nom) << 4;
	p->TGainNom = _IQ16mpy(p->T_meas_gain, _IQ(0.05)) << 4;	//0.05 = 1/20, ��� 20 �������� �� ������� - ����������� (�������) �����������
	p->refGainNom = _IQ16mpy(p->ref_meas_gain, _IQ(1.0/100)) << 4;
}

//! �������������� ������

//! \memberof TAdcDrv
void AdcDrv_ms_calc(TAdcDrv *p) {

}

/*@}*/

