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
 \brief     ������ ��������� ��� (��. TAdcDrv) MCB_028
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 22/03/2019

 \addtogroup V_adc 
 @{*/

/* ���������� �������
 * ADC13	Ia
 * ADC19		Ic
 * ADC1	Udc
 * ADC31	0.75V
 * ADC18	0.03V
 * ADC20	Pot
 * ADC15	AIN1
 * ADC27	AIN2
 * ADC29	TempSens
 */

#include "main.h"

//! \memberof TAdcDrv
//!
void AdcDrv_init(TAdcDrv *p) {

//! ������������� ��� ��� ����������� ������� ��� ������������� ���������� � ����

    Uint32 trash;
    // ������ ���� �����������
    ADC->SEQSYNC = 0;

    // ����� ��������� ��������� � ���������
    ADC->SEQ[0].SCVAL = 0;
    ADC->SEQ[1].SCVAL = 0;
    ADC->SEQ[2].SCVAL = 0;
    ADC->SEQ[3].SCVAL = 0;
    ADC->SEQ[4].SCVAL = 0;
    ADC->SEQ[5].SCVAL = 0;
    ADC->SEQ[6].SCVAL = 0;
    ADC->SEQ[7].SCVAL = 0;

    //�������� ���������
    ADC->SEQSYNC_bit.SYNC0 = 1;
    //������ ����� ����������
    ADC->IM_bit.SEQIM0 = 1;
    //����������� �������� ������� �����������
    ADC->EMUX_bit.EM0 = ADC_EMUX_EM0_SwReq;
    // ��������� �����������
    ADC->SEQEN_bit.SEQEN0 = 1;
    //����������� ���������� ������������ ���������� RCNT + 1
    ADC->SEQ[0].SCCTL_bit.RCNT = 3;
    ADC->SEQ[0].SCCTL_bit.RAVGEN = 1;   // ��������� ����������
    // ��� ����������
    ADC->SEQ[0].SCCTL_bit.ICNT = 0;
    ADC->SEQ[0].SRQCTL_bit.RQMAX = 0x6;


    ADC->ACTL[0].ACTL_bit.ADCEN = 0x1;                            // ��������� ������ ���
    ADC->ACTL[0].ACTL_bit.SELRES = ADC_ACTL_ACTL_SELRES_12bit;
    ADC->ACTL[1].ACTL_bit.ADCEN = 0x1;                          // ��������� ������ ���
    ADC->ACTL[1].ACTL_bit.SELRES = ADC_ACTL_ACTL_SELRES_12bit;
    ADC->ACTL[2].ACTL_bit.ADCEN = 0x1;                          // ��������� ������ ���
    ADC->ACTL[2].ACTL_bit.SELRES = ADC_ACTL_ACTL_SELRES_12bit;
    ADC->ACTL[3].ACTL_bit.ADCEN = 0x1;                          // ��������� ������ ���
    ADC->ACTL[3].ACTL_bit.SELRES = ADC_ACTL_ACTL_SELRES_12bit;


    ADC->SEQ[0].SRQSEL0_bit.RQ0 = 13;               // ����� ���� ��� ����� ������������
    ADC->SEQ[0].SRQSEL0_bit.RQ1 = 19;               //  --//--
    ADC->SEQ[0].SRQSEL0_bit.RQ2 = 1;                //  --//--
    ADC->SEQ[0].SRQSEL0_bit.RQ3 = 20;               //  --//--
    ADC->SEQ[0].SRQSEL1_bit.RQ4 = 15;               //  --//--
    ADC->SEQ[0].SRQSEL1_bit.RQ5 = 27;               //  --//--
    ADC->SEQ[0].SRQSEL1_bit.RQ6 = 29;               //  --//--


    // ���, ���� ��� �������� ���� "�����" (����� �������� ���� ���� ����� "ADCEN = 1")
    while (!ADC->ACTL[0].ACTL_bit.ADCRDY) {};
    while (!ADC->ACTL[1].ACTL_bit.ADCRDY) {};
    while (!ADC->ACTL[2].ACTL_bit.ADCRDY) {};
    while (!ADC->ACTL[3].ACTL_bit.ADCRDY) {};

}


//!������ ��� � �������� ��������� ������� ���� ������� ���������� (������ 10���).

//! ���������� ���������� ���������� ��� �������� � ����������� � ������ IQ24.
//! ���� ��� ��� ��������� �������� ����������� �� ��������� ���������

//! \memberof TAdcDrv

void AdcDrv_fast_calc(TAdcDrv *p) {
	Uint32 trash;
	Uint16 pot, ain1, ain2, temper;

	p->IA_temp = (int16) ADC->SEQ[0].SFIFO_bit.DATA;
	p->IC_temp = (int16) ADC->SEQ[0].SFIFO_bit.DATA;

	p->Udc_temp = (int16) ADC->SEQ[0].SFIFO_bit.DATA;

	pot = (int16) ADC->SEQ[0].SFIFO_bit.DATA;
	ain1 = (int16) ADC->SEQ[0].SFIFO_bit.DATA;
	ain2 = (int16) ADC->SEQ[0].SFIFO_bit.DATA;

	p->T_temp = (int16) ADC->SEQ[0].SFIFO_bit.DATA;

	// ��������������
	p->Imeas_a = p->IaGainNom * (((p->IA_temp<< 4) + p->Imeas_a_offset));
	p->Imeas_c = p->IcGainNom * (((p->IC_temp<< 4) + p->Imeas_c_offset));
	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);
	p->Imeas_b = -p->Imeas_a - p->Imeas_c;
	p->T_meas = p->TGainNom*(p->T_temp);

// ������� ����
    while (ADC->SEQ[0].SFLOAD)
        trash = ADC->SEQ[0].SFIFO;

}

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

//��� ������������ �������� ��� �������� ����� �� 0 �� 65535. (16 ��������, ��� ��������� �������).
//��� ������� � ���������� ���������� ������� ���, ����� ���������� �������������� �������� � ������� 8.24,
//��� 1.0 ��� 65535. ����� �������, ����� �������� ����� 65535 �� 24-16=8 ��������.
//����� �� 8 �������� - ��� ��������� �� ����� 255. ����� 255 - ��� 1.0 � ������� 24.8.

//����� �������, PvalveGainNom - ��� ����������� � ������� 24.8. �� ���������� � ���������� ������������� �������
//_IQ16mpy, �������� ������� Pvalve_gain (int) � 1.0/100 � ������� 8.24. ������� IQ ��������
//�� ���� ������������ ����� ������� ��������� � 64 �������� �� ������� ���������� ������ �� Q ��������.
//�.�. _IQ16mpy �������� ����� � ������� IQ24 9������ ��������) �� ������������� ����������� (������ ��������),
//� ����� �������� ��������� �� 16 �������� ������.
//���, � ���������� _IQ16mpy(p->Pvalve_gain,_IQ(1.0/100)); ���������� ������������� ����� 255, ����������
//1.0 � ������� 24.8 ��-�� ������ �� 16 �������� ������.

//�� ��������������� ������ ������� � ����� ����� - ��������� ������������������ ��������� ���.

//! \memberof TAdcDrv
void AdcDrv_slow_calc(TAdcDrv *p) {

	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain, drv_params._1_I_nom) << 1;
	p->IbGainNom = _IQ16mpy(p->Imeas_b_gain, drv_params._1_I_nom) << 1;
	p->IcGainNom = _IQ16mpy(p->Imeas_c_gain, drv_params._1_I_nom) << 1;
	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain, drv_params._1_Udc_nom) << 4;
	p->TGainNom = _IQ16mpy(p->T_meas_gain, _IQ(0.05)) << 4; //0.05 = 1/20
}

//! �������������� ������

//! \memberof TAdcDrv
void AdcDrv_ms_calc(TAdcDrv *p) {

}

/*@}*/

