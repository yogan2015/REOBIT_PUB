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
	PWM0->ETSEL_bit.SOCAEN = 1;
	PWM0->ETSEL_bit.SOCASEL = ET_CTR_ZERO;
	PWM0->ETPS_bit.SOCAPRD = 2;

	Uint32 AdcClock, AdcDiv, trash;
	Uint32 pwmPrd = PWM0->TBPRD;	// �����������, ������� 10 ���

	if (pwmPrd < 1000) pwmPrd = 1000;
    //������������� ADC
    RCU->ADCCFG_bit.CLKSEL = RCU_ADCCFG_CLKSEL_PLLCLK;	// ������������ �� PLL
    RCU->ADCCFG_bit.DIVN = 0x1; 						// N = 2 * (DIVN + 1) = 4 -> ACLK = 25 MHz
    RCU->ADCCFG_bit.DIVEN = 0x1;						// ��������� ��������
    AdcDiv = 2 * (RCU->ADCCFG_bit.DIVN + 1);			// ����� ������� �������
    AdcClock = SystemCoreClock / AdcDiv;
    RCU->ADCCFG_bit.CLKEN = 0x1;						// ��������� ������������
    RCU->ADCCFG_bit.RSTDIS = 0x1;						// ������� �����
    ADC->ACTL_bit.ADCEN = 0x1;							// ��������� ������ ���

    //��������� ���������� 0
    // CH0, CH1, CH2, CH3.
    ADC->EMUX_bit.EM0 = ADC_EMUX_EM0_PWM012A;		// ������ �� �������
    ADC->SEQSYNC = ADC_SEQSYNC_SYNC0_Msk;			// ��������� ��������� SEQ0
    ADC->SEQ[0].SRQCTL_bit.RQMAX = 0x3;				// ���������� 4 ������ �� ��� = RQMAX + 1
    ADC->SEQ[0].SRQSEL_bit.RQ0 = 0x0;				// ����� ���� ��� ����� ������������
    ADC->SEQ[0].SRQSEL_bit.RQ1 = 0x1;				//	--//--
    ADC->SEQ[0].SRQSEL_bit.RQ2 = 0x2;				//  --//--
    ADC->SEQ[0].SRQSEL_bit.RQ3 = 0x3;				//  --//--
    ADC->SEQ[0].SCCTL_bit.RCNT = 3;					// ������ ��� ��� ����������� ����� ������� �������
    ADC->SEQ[0].SRTMR_bit.VAL = (pwmPrd / AdcDiv) / (ADC->SEQ[0].SCCTL_bit.RCNT + 1);	// ����� ����� ������	 ��� �� ������ ���
    ADC->SEQ[0].SCCTL_bit.ICNT = 3;					// ����� ���������� ����� ������ (ICNT + 1) ���������
    ADC->SEQ[0].SCCTL_bit.RAVGEN = 1;				// ��������� ��������� �� 4 ������
    ADC->SEQEN_bit.SEQEN0 = 1;						// ��������� ��������� 0


	// ������� FIFO
	while (ADC->SEQ[0].SFLOAD)
		trash = ADC->SEQ[0].SFIFO;

    // ��������� EPWM0 ��������� ��� �� ����


    // ���, ���� ��� �������� ���� "�����" (����� �������� ���� ���� ����� "ADCEN = 1")
    while (!ADC->ACTL_bit.ADCRDY) {};

    // ��������� ���������� �� ������� ����������
    ADC->IM_bit.SEQIM0 = 1;
    NVIC_EnableIRQ(ADC_SEQ0_IRQn);
    NVIC_SetPriority(ADC_SEQ0_IRQn, IRQ_PRIORITY_ADC);
}


//!������ ��� � �������� ��������� ������� ���� ������� ���������� (������ 10���).

//! ���������� ���������� ���������� ��� �������� � ����������� � ������ IQ24.
//! ���� ��� ��� ��������� �������� ����������� �� ��������� ���������

//! \memberof TAdcDrv

void AdcDrv_fast_calc(TAdcDrv *p) {
	Uint32 trash;
	// ���� �� ����� ������, �� � ���� ����� ��� ���������� ���������� - 4 �����.
	p->IA_temp = ADC->SEQ[0].SFIFO;
	p->IB_temp = ADC->SEQ[0].SFIFO;
	p->Udc_temp = ADC->SEQ[0].SFIFO;
	p->AI_temp = ADC->SEQ[0].SFIFO;

	// ������� FIFO �� ������, ���� ������-�� ��� ��������� ������ ��� ���� �������� (������ ����� ��������� �������)
	while (ADC->SEQ[0].SFLOAD)
		trash = ADC->SEQ[0].SFIFO;

	p->Imeas_a = p->IaGainNom * ((p->IA_temp<< 4) + p->Imeas_a_offset);
	p->Imeas_b = p->IbGainNom * ((p->IB_temp<< 4) + p->Imeas_b_offset);
	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);
	p->Imeas_c = -p->Imeas_a - p->Imeas_b;
	p->AI_meas = p->AI_temp *  p->AIGainNom;

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
	// �������� ���� ����� �������������
	volatile Uint16 pwmPrd = PWM0->TBPRD;

	// ���� ������� �����-����, �� ������ �� ���� � ��� ���� ������
	if (PWM0->TBCTL_bit.CTRMODE == TB_COUNT_UPDOWN)
		pwmPrd = pwmPrd << 1;

	// �������� ������� ���
	Uint16 AdcDiv = 2 * (RCU->ADCCFG_bit.DIVN + 1);
	if (pwmPrd < 1000) pwmPrd = 1000;

	ADC->SEQ[0].SRTMR_bit.VAL = (pwmPrd / AdcDiv) / (ADC->SEQ[0].SCCTL_bit.RCNT + 1);

	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain, drv_params._1_I_nom) << 1;
	p->IbGainNom = _IQ16mpy(p->Imeas_b_gain, drv_params._1_I_nom) << 1;
	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain, drv_params._1_Udc_nom) << 4;
	p->AIGainNom = _IQ16mpy(p->AI_meas_gain, _IQ(1)) << 4;
}

//! �������������� ������

//! \memberof TAdcDrv
void AdcDrv_ms_calc(TAdcDrv *p) {

}

/*@}*/

