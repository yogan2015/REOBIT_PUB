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
 
 \file      V_PWM_Module.c
 \brief     ������ ���������� ��������� ��� (��. TPWM_Module)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_PWM_Module 
 @{*/


#include "V_IQmath.h"
#include "V_PWM_Module.h"
#include "main.h"


#define GPIO_INV_ON
#define GPIO_INV_OFF



//! �������������

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *p) {
	SIU->PWMSYNC_bit.PRESCRST = 0; //������������� �������� - ����� ���������� ���������

// ------------------------------------------------------------------------
	// ����������� ������ ePWM1
	// ------------------------------------------------------------------------
	if (p->Frequency < PWM_FREQ_MIN)
		p->Frequency = PWM_FREQ_MIN;
	if (p->Frequency > PWM_FREQ_MAX)
		p->Frequency = PWM_FREQ_MAX;
	PWM0->TBPRD = _IQ10div(_IQ10(APB0BusClock/1000.0), p->Frequency << 1) >> 10; //������

	p->k_pwm = PWM0->TBPRD;
	p->FreqPrev = p->Frequency;                 //���������� �������
	PWM0->TBPHS_bit.TBPHS = 0x0000;            // Phase is 0
	PWM0->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	PWM0->TBCTL_bit.PRDLD = TB_SHADOW;        // �������� TBPRD ��� TBCTR = 0
	PWM0->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	PWM0->TBCTL_bit.PHSEN = TB_DISABLE;         // Disable phase loading
	PWM0->TBCTL_bit.PHSDIR = TB_UP;      // ������� ����� ����� �������� ����
	PWM0->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	PWM0->TBCTL_bit.CLKDIV = 0;                 // Time-base Clock Prescale
	PWM0->TBCTL_bit.SYNCOSEL = TB_CTR_ZERO; // ����� ������-������ ��� TBCTR = 0

	// Setup shadowing
	PWM0->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	PWM0->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   // Load on zero

	PWM0->CMPCTL_bit.SHDWBMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	PWM0->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   // Load on zero

	// Set Compare values
	PWM0->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Set actions
	PWM0->AQCTLA = AQ_EPWM_DISABLE; // ��� ������ ������� ��� PWM1A ���������
	PWM0->AQCTLA_bit.ZRO = 1; //�������� ��� ���� ��������
	PWM0->AQCTLA_bit.CAU = 2; //�������� ��� ��������� � ����������������
	PWM0->AQCTLA_bit.CAD = 1; //�������� ��� ��������� � ����������������

	//��� PWMB ���� �����, ��� ��� PWM�. ��� ��������. �������� ����� � ������ ��
	PWM0->AQCTLB = PWM0->AQCTLA; // ��� ������ ������� ��� PWM1B ���������
	PWM0->AQCTLB_bit.ZRO = PWM0->AQCTLA_bit.ZRO; //�������� ��� ���� ��������
	PWM0->AQCTLB_bit.CAU = PWM0->AQCTLA_bit.CAU; //�������� ��� ��������� � ����������������
	PWM0->AQCTLB_bit.CAD = PWM0->AQCTLA_bit.CAD; //�������� ��� ��������� � ����������������

	PWM0->AQSFRC_bit.RLDCSF = 0; //�� �� ���� ������ 0

	// Setup Deadband
	// DBRED = DBFED = 150 * T�_��� / 4
	PWM0->DBRED = _IQ4mpy(_IQ4(150 / 4), p->DeadBand >> 20) >> 4;
	PWM0->DBFED = PWM0->DBRED;
	PWM0->DBCTL_bit.INMODE = DBA_RED_DBB_FED;    //s4=0, s5=1 �� �������� DT
	PWM0->DBCTL_bit.OUTMODE = DB_FULL_ENABLE;    //S1=1, S2=2 �� �������� DT
	PWM0->DBCTL_bit.POLSEL = DB_ACTV_HIC;       // PWM1B = !PWM1A; S2=0, S3=1

	PWM0->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT (���������)
	PWM0->ETSEL_bit.INTEN = 0;                  // Disable INT


	//��������� TZ ���� ���������� ���������� ������ (one-shot)
	//   PWM0->TZSEL_bit.OSHT1 = TZ_ENABLE;
//    PWM0->TZSEL_bit.OSHT2 = TZ_ENABLE;
//    PWM0->TZSEL_bit.OSHT3 = TZ_ENABLE;

	// Trip-Zone
	PWM0->TZCTL_bit.TZA = TZ_STATE;   // �� ������� "One-Shot Trip" ���������
	PWM0->TZCTL_bit.TZB = TZ_STATE;          // ��� ������ � ������ ���������

	//��� VectorCARD �� ���� ����������� ADC
	//PWM0->ETSEL_bit.SOCAEN = 1;		// ��������� ������ ���
	//PWM0->ETSEL_bit.SOCASEL = 1;		// ��������� ��� CTR == 0 (Underflow)

	// ------------------------------------------------------------------------
	// ����������� ������ ePWM2
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM1->TBPRD = PWM0->TBPRD;              //������ ����� ��
	PWM1->TBPHS_bit.TBPHS = 0x0001;            // ���� ����� 1 ��-�� �������� � ���� ���� �� �������������
	PWM1->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	PWM1->TBCTL_bit.PRDLD = TB_SHADOW;        // �������� TBPRD ��� TBCTR = 0
	PWM1->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	PWM1->TBCTL_bit.PHSEN = TB_ENABLE;         // Enable phase loading
	PWM1->TBCTL_bit.PHSDIR = TB_UP;      // ������� ����� ����� �������� ����
	PWM1->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	PWM1->TBCTL_bit.CLKDIV = 0;           // Time-base Clock Prescale
	PWM1->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; // ���������� ������-������ "��������"

	// Setup shadowing
	PWM1->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	PWM1->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   // Load on zero

	PWM1->CMPCTL_bit.SHDWBMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	PWM1->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   // Load on zero

	// Set Compare values
	PWM1->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Set actions
	PWM1->AQCTLA = AQ_EPWM_DISABLE; // ��� ������ ������� ���������
	PWM1->AQCTLA_bit.ZRO = 1; //�������� ��� ���� ��������
	PWM1->AQCTLA_bit.CAU = 2; //�������� ��� ��������� � ����������������
	PWM1->AQCTLA_bit.CAD = 1; //�������� ��� ��������� � ����������������

	//��� PWMB ���� �����, ��� ��� PWM�. ��� ��������. �������� ����� � ������ ��
	PWM1->AQCTLB = PWM0->AQCTLA; // ��� ������ ������� ��� PWM1B ���������
	PWM1->AQCTLB_bit.ZRO = PWM0->AQCTLA_bit.ZRO; //�������� ��� ���� ��������
	PWM1->AQCTLB_bit.CAU = PWM0->AQCTLA_bit.CAU; //�������� ��� ��������� � ����������������
	PWM1->AQCTLB_bit.CAD = PWM0->AQCTLA_bit.CAD; //�������� ��� ��������� � ����������������

	PWM1->AQSFRC_bit.RLDCSF = 0; //�� �� ���� ������ 0

	// Active high complementary PWMs - Setup Deadband
	PWM1->DBRED = PWM0->DBRED;
	PWM1->DBFED = PWM1->DBRED;
	PWM1->DBCTL_bit.INMODE = PWM0->DBCTL_bit.INMODE;
	PWM1->DBCTL_bit.OUTMODE = PWM0->DBCTL_bit.OUTMODE;
	PWM1->DBCTL_bit.POLSEL = PWM0->DBCTL_bit.POLSEL;

	// Interrupt where we will change the Compare Values
	PWM1->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT
	PWM1->ETSEL_bit.INTEN = 0;                  // Disable INT

	//��������� TZ ���� ���������� ���������� ������ (one-shot)
	//   PWM1->TZSEL_bit.OSHT1 = TZ_ENABLE;
	//   PWM1->TZSEL_bit.OSHT2 = TZ_ENABLE;
	//   PWM1->TZSEL_bit.OSHT3 = TZ_ENABLE;

	// Trip-Zone
	PWM1->TZCTL_bit.TZA = TZ_STATE;   // �� ������� "One-Shot Trip" ���������
	PWM1->TZCTL_bit.TZB = TZ_STATE;          // ��� ������ � ������ ���������

	// ------------------------------------------------------------------------
	// ����������� ������ ePWM3
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM2->TBPRD = PWM0->TBPRD;
	PWM2->TBPHS_bit.TBPHS = 0x0001;            // ���� ����� 1 ��-�� �������� � ���� ���� �� �������������
	PWM2->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	PWM2->TBCTL_bit.PRDLD = TB_SHADOW;        // �������� TBPRD ��� TBCTR = 0
	PWM2->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	PWM2->TBCTL_bit.PHSEN = TB_ENABLE;         // Enable phase loading
	PWM2->TBCTL_bit.PHSDIR = TB_UP;      // ������� ����� ����� �������� ����
	PWM2->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	PWM2->TBCTL_bit.CLKDIV = 0;           // Time-base Clock Prescale
	PWM2->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; // ��������� ������ ������-�������

	// Setup shadowing
	PWM2->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	PWM2->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   // Load on zero

	PWM2->CMPCTL_bit.SHDWBMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	PWM2->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   // Load on zero

	// Set Compare values
	PWM2->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Set actions
	PWM2->AQCTLA = AQ_EPWM_DISABLE; // ��� ������ ������� ���������
	PWM2->AQCTLA_bit.ZRO = 1; //�������� ��� ���� ��������
	PWM2->AQCTLA_bit.CAU = 2; //�������� ��� ��������� � ����������������
	PWM2->AQCTLA_bit.CAD = 1; //�������� ��� ��������� � ����������������

	//��� PWMB ���� �����, ��� ��� PWM�. ��� ��������. �������� ����� � ������ ��
	PWM2->AQCTLB = PWM0->AQCTLA; // ��� ������ ������� ��� PWM1B ���������
	PWM2->AQCTLB_bit.ZRO = PWM0->AQCTLA_bit.ZRO; //�������� ��� ���� ��������
	PWM2->AQCTLB_bit.CAU = PWM0->AQCTLA_bit.CAU; //�������� ��� ��������� � ����������������
	PWM2->AQCTLB_bit.CAD = PWM0->AQCTLA_bit.CAD; //�������� ��� ��������� � ����������������

	PWM2->AQSFRC_bit.RLDCSF = 0; //�� �� ���� ������ 0

	// Active high complementary PWMs - Setup Deadband
	PWM2->DBRED = PWM0->DBRED;
	PWM2->DBFED = PWM2->DBRED;
	PWM2->DBCTL_bit.INMODE = PWM0->DBCTL_bit.INMODE;
	PWM2->DBCTL_bit.OUTMODE = PWM0->DBCTL_bit.OUTMODE;
	PWM2->DBCTL_bit.POLSEL = PWM0->DBCTL_bit.POLSEL;

	// Interrupt where we will change the Compare Values
	PWM2->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT
	PWM2->ETSEL_bit.INTEN = 0;                  // Disable INT

	//��������� TZ ���� ���������� ���������� ������ (one-shot)
	//  PWM2->TZSEL_bit.OSHT1 = TZ_ENABLE;
	//  PWM2->TZSEL_bit.OSHT2 = TZ_ENABLE;
	//  PWM2->TZSEL_bit.OSHT3 = TZ_ENABLE;


	// Trip-Zone
	PWM2->TZCTL_bit.TZA = TZ_STATE;   // �� ������� "One-Shot Trip" ���������
	PWM2->TZCTL_bit.TZB = TZ_STATE;          // ��� ������ � ������ ���������

	// ------------------------------------------------------------------------
	// ����������� ������ ePWM3 ��� ���
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM3->TBPRD = PWM0->TBPRD;
	PWM3->TBPHS_bit.TBPHS = 0x0001;      // ���� ����� 1 ��-�� �������� � ���� ���� �� �������������
	PWM3->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	PWM3->TBCTL_bit.PRDLD = TB_SHADOW;        // �������� TBPRD ��� TBCTR = 0
	PWM3->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	PWM3->TBCTL_bit.PHSEN = TB_ENABLE;         // Enable phase loading
	PWM3->TBCTL_bit.PHSDIR = TB_UP;      // ������� ����� ����� �������� ����
	PWM3->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	PWM3->TBCTL_bit.CLKDIV = 0;           // Time-base Clock Prescale
	PWM3->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; // ��������� ������ ������-�������

	// Interrupt where we will change the Compare Values
	PWM3->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT
	PWM3->ETSEL_bit.INTEN = 0;                  // Disable INT


	PWM3->ETSEL_bit.SOCAEN = 1;		// ��������� ������ ���
	PWM3->ETSEL_bit.SOCASEL = 1;		// ��������� ��� CTR == 0 (Underflow)

	//���������� ��� ����� ������
	PWM0->TZCLR = 0x7;
	PWM1->TZCLR = 0x7;
	PWM2->TZCLR = 0x7;

	//���������� ������ ���
	SIU->PWMSYNC_bit.PRESCRST= 0b111;
}



//! ������������ ������� �������.

//!��������� ����������� ���������� ��� ��������� Ud,
//!��������� ���������� ������� � ����������, ���� ���������, �
//!��������� ����� ������, ������������ �������� ���� ����������.
//! \memberof TPWM_Module
void PWM_Module_NormInput(TPWM_Module* p) {
    _iq knorm;

    p->UalphaNorm=p->UalphaRef;
    p->UbetaNorm=p->UbetaRef;

    //������� ��������� (��� ����� �����������)
    p->U_mag=_IQmag(p->UalphaNorm,p->UbetaNorm);


    p->UdCorTmp=_IQdiv(_IQ(1.0),(_IQ(1.0)+_IQmpy((adc.Udc_meas-_IQ(1.0)),p->UdCompK)));
    //���� ��������� ���������� �� Ud
    if (p->UdCompEnable&1) { //�� �������?
        p->UalphaNorm=_IQmpy(p->UalphaNorm, p->UdCorTmp);//������� ��������������� �����-�� ���������
        p->UbetaNorm=_IQmpy(p->UbetaNorm, p->UdCorTmp);//� ��� ����
    }

    //���������� �������� ��������� ���������� � ����������, ����������� � ������������� ������� ��������
    //����� U_lim=1.0, ��� � ���� ����� ����������. ������, ��� �� ����� ��������� � �������������. ����� ������ �������� ����� ������������ U_lim
    if (p->U_lim>_IQ(1.0/0.866)) //�� ��� ������ �������� ���� �����������-������. ���������� (������ �������� �������)
        p->U_lim=_IQ(1.0/0.866);
    /* ������������ ��������� �������, ������� ����� ����������*/
    knorm=_IQmag(p->UalphaNorm,p->UbetaNorm);//���� ��������� �� 540 � 311
    if (knorm>=p->U_lim) { //�� ������, ��� ���� �����������?
        knorm=_IQdiv(p->U_lim,knorm);//� ��� �� ����������, ��� ��������, ������������ ����������
        p->UalphaNorm=_IQmpy(knorm,p->UalphaNorm);//��������� ��������������� ����������
        p->UbetaNorm=_IQmpy(knorm,p->UbetaNorm);//� ���
        p->ULimitation=1;//���� � ���, ��� ���� ����������� ����������
    } else
        p->ULimitation=0;

    /* ������������ ����������� �������*/
    /* �� ����� ������� ���������� ������������� ������������
    ������ ������� ������������ ��������, ��������, 220*sqrt(2)
    ������ ������������ �������, ��� �� ������� ����������� �����������
    ����������� ���������� (����� �������� �������)
    */
    p->UalphaNorm=_IQmpy(p->UalphaNorm,_IQ(0.866));
    p->UbetaNorm=_IQmpy(p->UbetaNorm,_IQ(0.866));
}



//! ������� 6�� ��������� ��������� ���

//! \memberof TPWM_Module
void PWM_Module_No_SV_Update(TPWM_Module *p) {
    _iq lambda1;
    _iq lambda2;
    _iq lambda3;

    int16 gamma;
    int16 gamma1;
    long tmp_pwm;

    //���������� ���� ������� ��������� ������ ���� ������� ������� ����� �� ����, �����
    //������������� ��������� ���������� �����������, ��� � ��������� ��� ����� ���� �������� � ��������� ������ ���.
    DINT;
    if (PWM0->TBCTR>30) {
        PWM0->CMPA_bit.CMPA=(Uint16)p->GammaA;
        PWM1->CMPA_bit.CMPA=(Uint16)p->GammaB;
        PWM2->CMPA_bit.CMPA=(Uint16)p->GammaC;
    }
    EINT;

    PWM_Module_NormInput(p);

    //������ ����������� �� ������ ���������.
    //��������� ��. ����������� ����� �.�. http://motorcontrol.ru/wp-content/uploads/2015/11/Chuev_vector_control.pdf
    tmp_pwm = _IQmpy(_1_SQRT3,p->UbetaNorm);  /*����� �� ������ �� 3*/
    lambda1 = _IQmpy(p->k_pwm,(p->UalphaNorm - tmp_pwm));
    lambda2 = _IQmpy(p->k_pwm,2*tmp_pwm);
    lambda3 = _IQmpy(p->k_pwm,p->UalphaNorm + tmp_pwm);


    if (lambda1<=0)
        if (lambda3>0) {
            gamma=lambda3;
            gamma1=-lambda1;
            p->sector=1; /*110 ������ */
            p->GammaA=p->k_pwm-gamma;
            p->GammaB=p->k_pwm-(gamma+gamma1+1);
            p->GammaC=p->k_pwm-0;

        } else if (lambda2>0) {
            gamma=lambda2;
            gamma1=-lambda3;
            p->sector=2; /*011 ������ */
            p->GammaA=p->k_pwm-0;
            p->GammaB=p->k_pwm-(gamma+gamma1+1);
            p->GammaC=p->k_pwm-gamma1;
            /*011 ������ */
        } else if (lambda1!=0) {
            gamma=-lambda1;
            gamma1=-lambda2;
            p->sector=3; /*011 ������ */
            p->GammaA=p->k_pwm-0;
            p->GammaB=p->k_pwm-gamma;
            p->GammaC=p->k_pwm-(gamma+gamma1+1);
            /*011 ������ */
        } else {
            gamma=-lambda3;
            gamma1 = lambda1;
            p->sector= 4; /*101 ������ */
            p->GammaA=p->k_pwm-gamma1;
            p->GammaB=p->k_pwm-0;
            p->GammaC=p->k_pwm-(gamma+gamma1+1);
            /*101 ������ */

        }
    else if (lambda2>0) {
        gamma=lambda1;
        gamma1=lambda2;
        p->sector= 0; /*110 ������ */
        p->GammaA=p->k_pwm-(gamma+gamma1+1);
        p->GammaB=p->k_pwm-gamma1;
        p->GammaC=p->k_pwm-0;
        /*110 ������ */
    } else if (lambda3<0) {
        gamma=-lambda3;
        gamma1 = lambda1;
        p->sector= 4; /*101 ������ */
        p->GammaA=p->k_pwm-gamma1;
        p->GammaB=p->k_pwm-0;
        p->GammaC=p->k_pwm-(gamma+gamma1+1);
        /*101 ������ */
    } else {
        gamma=-lambda2;
        gamma1=lambda3;
        p->sector=5; /*101 ������ */
        p->GammaA=p->k_pwm-(gamma+gamma1+1);
        p->GammaB=p->k_pwm-0;
        p->GammaC=p->k_pwm-gamma;
        /*101 ������ */
    }


    /*��������� */

    if (p->GammaA<0) p->GammaA=0;
    if (p->GammaB<0) p->GammaB=0;
    if (p->GammaC<0) p->GammaC=0;

    if (p->GammaA>p->k_pwm) p->GammaA=p->k_pwm+1;
    if (p->GammaB>p->k_pwm) p->GammaB=p->k_pwm+1;
    if (p->GammaC>p->k_pwm) p->GammaC=p->k_pwm+1;

    //���������� ���� ������� ��������� ������ ���� ������� ������� ����� �� ����, �����
    //������������� ��������� ���������� �����������, ��� � ��������� ��� ����� ���� �������� � ��������� ������ ���.
    //������ ��� - ����� ������������� �������� � ���������� "�����������" ��� ��������� ������ ������� � ���
    DINT;
    if (PWM0->TBCTR>30) {
        PWM0->CMPA_bit.CMPA=(Uint16)p->GammaA;
        PWM1->CMPA_bit.CMPA=(Uint16)p->GammaB;
        PWM2->CMPA_bit.CMPA=(Uint16)p->GammaC;
    }
    EINT;
}

//! ������� �������������� ���

//! \memberof TPWM_Module
void PWM_Module_Sin_Update(TPWM_Module *p) {
	_iq PhasePtsA;
	_iq PhasePtsB;
	_iq PhasePtsC;
	_iq knorm;


	p->UalphaNorm = p->UalphaRef;
	p->UbetaNorm = p->UbetaRef;

	//������� ��������� (��� ����� �����������)
	p->U_mag = _IQmag(p->UalphaNorm, p->UbetaNorm);

	/* ������������ ��������� �������, ������� ����� ����������*/
	knorm = _IQmag(p->UalphaNorm, p->UbetaNorm);
	if (knorm >= p->U_lim) { //�� ������, ��� ���� �����������?
		knorm = _IQdiv(p->U_lim, knorm); //� ��� �� ����������, ��� ��������, ������������ ����������
		p->UalphaNorm = _IQmpy(knorm, p->UalphaNorm); //��������� ��������������� ����������
		p->UbetaNorm = _IQmpy(knorm, p->UbetaNorm); //� ���
		p->ULimitation = 1; //���� � ���, ��� ���� ����������� ����������
	} else
		p->ULimitation = 0;

	//������������ �������� ����������. ��� ��� �������������� ��� ��������� �� 0.866 ������� ����������,
	//��� ��������� ��� (270� ������������ ������� ���������� ������ 311�), �� ��� ����, ����� ��� ��� �� ������� � ����������
	//p->UalphaNorm, p->UbetaNorm ���������� �� �� ����� ���������� �� ������, ��� � � ��������� ���, ����� ������� ��������� � 1/0.866 ���.
	//������� �� ��� ����� ��� ����������� ������, ����� ��������� �������� � ���������� �� ������������� ���������.
	p->UalphaNorm = _IQmpy(p->UalphaNorm, _IQ(1/0.866/2));
	p->UbetaNorm = _IQmpy(p->UbetaNorm, _IQ(1/0.866/2));

	/*������ �������������� �� ������� �����, ����� � a,b,c */

	PhasePtsA = _IQ(0.5) - (p->UalphaNorm);
	PhasePtsB = _IQ(0.5) - (_IQmpy(p->UbetaNorm,_IQ(0.8660254)) - (p->UalphaNorm >> 1));
	PhasePtsC = _IQ(0.5) - (-_IQmpy(p->UbetaNorm, _IQ(0.8660254)) - (p->UalphaNorm >> 1));

	p->GammaA = _IQmpy(p->k_pwm, PhasePtsA);
	p->GammaB = _IQmpy(p->k_pwm, PhasePtsB);
	p->GammaC = _IQmpy(p->k_pwm, PhasePtsC);

	/*��������� */

	if (p->GammaA < 0)
		p->GammaA = 0;
	if (p->GammaB < 0)
		p->GammaB = 0;
	if (p->GammaC < 0)
		p->GammaC = 0;

	if (p->GammaA > p->k_pwm)
		p->GammaA = p->k_pwm + 1;
	if (p->GammaB > p->k_pwm)
		p->GammaB = p->k_pwm + 1;
	if (p->GammaC > p->k_pwm)
		p->GammaC = p->k_pwm + 1;


	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;

}

//! ������� ��� � ����������� ������ (��� ������ SRM)

//! \memberof TPWM_Module
void PWM_Module_Separate_Update(TPWM_Module *p) {
	_iq PhasePtsA;
	_iq PhasePtsB;
	_iq PhasePtsC;
	_iq knorm;

	p->UPhARef = _IQmpy(p->UPhARef, _IQ(0.5));
	p->UPhBRef = _IQmpy(p->UPhBRef, _IQ(0.5));
	p->UPhCRef = _IQmpy(p->UPhCRef, _IQ(0.5));

	PhasePtsA = _IQ(0.5) - p->UPhARef;
	PhasePtsB = _IQ(0.5) - p->UPhBRef;
	PhasePtsC = _IQ(0.5) - p->UPhCRef;

	p->GammaA = _IQmpy(p->k_pwm, PhasePtsA);
	p->GammaB = _IQmpy(p->k_pwm, PhasePtsB);
	p->GammaC = _IQmpy(p->k_pwm, PhasePtsC);

	/*��������� */

	if (p->GammaA < 0)
		p->GammaA = 0;
	if (p->GammaB < 0)
		p->GammaB = 0;
	if (p->GammaC < 0)
		p->GammaC = 0;

	if (p->GammaA > p->k_pwm)
		p->GammaA = p->k_pwm + 1;
	if (p->GammaB > p->k_pwm)
		p->GammaB = p->k_pwm + 1;
	if (p->GammaC > p->k_pwm)
		p->GammaC = p->k_pwm + 1;

	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;

}

void PWM_Module_DC_Update(TPWM_Module *p)
{
	int32 UalphaRef = 0, UbetaRef = 0;
	int32 gamma1_DC = 0, gamma2_DC = 0;
	int32 temp32;

	UalphaRef = p->UalphaRef;
	UbetaRef = p->UbetaRef;

	if (UalphaRef > _IQ(1))
		UalphaRef = _IQ(1);
	else if (UalphaRef < _IQ(-1))
		UalphaRef = _IQ(-1);

	if (UbetaRef > _IQ(1))
		UbetaRef = _IQ(1);
	else if (UbetaRef < _IQ(0))
		UbetaRef = _IQ(0);

	//������ �������������� ��� ����������� ������������ ���������� � ��������� -1 - 0 - +1 (� ������������� ��������)
	//���������� 1 - ���������� (1/2 + 0.5) = 1, ���������� 0 - ���������� 0,5 � �.�.
	gamma1_DC = -(UalphaRef >> 1) + _IQ(0.5); // (IQ), �������� �������� ���������� � ��������������� ����������.

	//�� ������ �������� �������� p->k_pwm �������, ������ ������� ����� ���� � temp32.
	//��-����� ��� �������� ������������� ������������ ������ iq16.
	gamma1_DC = gamma1_DC >> 8; // (IQ16) ��������� ��, ��� ����, � iq16.
	temp32 = _IQ16mpy(gamma1_DC, _IQ16(p->k_pwm)); // (IQ16) ��������� ���������� � �������� ��� �������� � ������� ���������.
	p->GammaA = temp32 >> 16; // (IQ0) �������� ����� ����� � ������� ���������.
	p->GammaB = p->k_pwm - p->GammaA; // � �������� ��������� EPwm2 �� ��, ��� � � EPwm1.

	//�� ������ �������� �������� p->k_pwm �������, ������ ������� ����� ���� � temp32.
	//��-����� ��� �������� ������������� ������������ ������ iq16.
	gamma2_DC = UbetaRef >> 8; // (IQ16) ��������� ��, ��� ����, � iq16.
	temp32 = _IQ16mpy(gamma2_DC, _IQ16(p->k_pwm)); // (IQ16) ��������� ���������� � �������� ��� �������� � ������� ���������.
	p->GammaC = p->k_pwm - (temp32 >> 16); // (IQ0) �������� ����� ����� � ������� ���������.

	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;
}

//! ������� ��� ��� ��������� ������� ����������� ������������� ���������

//! \memberof TPWM_Module
void PWM_Module_ChargingMode(TPWM_Module *p) {
	p->GammaA = p->k_pwm;
	p->GammaB = p->k_pwm;
	p->GammaC = p->k_pwm;

	DINT;
	if (PWM0->TBCTR > 30) {
		PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
		PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
		PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;
	}
	EINT;
}

//! ����� �������-������� ��� ������� ���

//����������� �� ������ ��� (�� �������), ��� ������� � ����������.

//! \memberof TPWM_Module
void PWM_Module_Update(TPWM_Module *p) {

	if (p->ChargingMode)
		PWM_Module_ChargingMode(p);
	else {
		switch (p->PWM_type) {
		case PWM_TYPE_6SECT_NO_SV: {
			PWM_Module_No_SV_Update(p);
			break;
		}
		case PWM_TYPE_SIN_PWM: {
			PWM_Module_Sin_Update(p);
			break;
		}
		case PWM_TYPE_DC_DRIVE: {
			PWM_Module_DC_Update(p);
			break;
		}
		case PWM_TYPE_SRD: {
			PWM_Module_Separate_Update(p);
			break;
		}
		}
	}

}

//! ��������� ������

//! ��������������� ��������� ������������� ��������
//! �������� �������� �������, ������� ��� � �.�.

//! \memberof TPWM_Module
void PWM_Module_SlowCalc(TPWM_Module *p) {
	Uint16 tmp;
	//�������� ����������� �������� �������� �������
	if (p->DeadBand < DEAD_BAND_MIN)
		p->DeadBand = DEAD_BAND_MIN;
	if (p->DeadBand > DEAD_BAND_MAX)
		p->DeadBand = DEAD_BAND_MAX;
	//�������� �� �� ������� IQ � ��� � ����� ������� �� 100���
	PWM0->DBRED = _IQ4mpy(_IQ4(100), p->DeadBand >> 20) >> 4;
	//�� ��� ����� �� �� �����
	PWM0->DBFED = PWM0->DBRED;

	PWM1->DBFED = PWM0->DBRED;
	PWM1->DBRED = PWM0->DBRED;
	PWM2->DBFED = PWM0->DBRED;
	PWM2->DBRED = PWM0->DBRED;

	if (p->MinGammaLimit < DEAD_BAND_MIN)
		p->MinGammaLimit = GAMMA_LIMIT_MIN;
	if (p->MinGammaLimit > DEAD_BAND_MAX)
		p->MinGammaLimit = GAMMA_LIMIT_MAX;
	PWM0->FWDTH = _IQ4mpy(_IQ4(100), p->MinGammaLimit >> 20) >> 4;
	PWM1->FWDTH = PWM0->FWDTH;
	PWM2->FWDTH = PWM0->FWDTH;
	//������� ���. ����� "�� ����".
	if (p->FreqPrev != p->Frequency) { //������� �������
		DINT; //���������� ����������
		//�������� ���������/��������
		if (p->Frequency < PWM_FREQ_MIN)
			p->Frequency = PWM_FREQ_MIN;
		if (p->Frequency > PWM_FREQ_MAX)
			p->Frequency = PWM_FREQ_MAX;
		//�������� ������
		p->k_pwm = _IQ10div(_IQ10(APB0BusClock/1000.0), p->Frequency << 1) >> 10; //������
		PWM0->TBPRD = p->k_pwm;
		//��� ���� ����� �� �� �����
		PWM1->TBPRD = p->k_pwm;
		PWM2->TBPRD = p->k_pwm;
		PWM3->TBPRD = p->k_pwm;        //������ ���

		//��������� ����� ������� ��� ���������� �����, ������ �� ������� ���
		adc.IASampleLength = (p->Frequency >> 10) / 10;	//������� ��� � ������� 22.10, �������� � ���� � ����� �� 10 - ������� ������� ������� ����������
		if (adc.IASampleLength > 4)	//�� ����� 4 �����
			adc.IASampleLength = 4;
		if (adc.IASampleLength < 1)	//�� ����� 1 �����
			adc.IASampleLength = 1;
		adc.IBSampleLength = adc.IASampleLength;
		adc.ICSampleLength = adc.IASampleLength;
		adc.UdcSampleLength = adc.IASampleLength;

		p->FreqPrev = p->Frequency; //���������� �������
		EINT;
	}

	PWM3->TBPHS_bit.TBPHS = 1;//������ ������ ��� ������� ���: 1 - ����� �� ���� �������

}

//! ������� ��������� ��� (��������� ���������)

//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *p) {
	p->Enabled = 1;	//���� "��������"

	// ������� �������������� ��������� �������
	PWM0->AQCSFRC = 0;
	PWM1->AQCSFRC = 0;
	PWM2->AQCSFRC = 0;
	GPIO_INV_ON;

}

//! ������� ���������� ��� (���������� ���������)

//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *p) {

	p->Enabled = 0;	//���� "���������"
	// ������������� ������� ��� �����

	PWM0->AQCSFRC = 9;  // 0x1 - 0 �� ������ PWMxA, 0x8 - 1 �� ������ PWMxB
	PWM1->AQCSFRC = 9;  // 0x1 - 0 �� ������ PWMxA, 0x8 - 1 �� ������ PWMxB
	PWM2->AQCSFRC = 9;  // 0x1 - 0 �� ������ PWMxA, 0x8 - 1 �� ������ PWMxB
	GPIO_INV_OFF;

}

/*@}*/
