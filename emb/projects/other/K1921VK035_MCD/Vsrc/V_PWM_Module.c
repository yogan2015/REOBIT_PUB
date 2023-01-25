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

//! �������������

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *p) {
	SIU->PWMSYNC_bit.PRESCRST = 0; //������������� �������� - ����� ���������� ���������

	// ��������� �������
	if (p->Frequency < PWM_FREQ_MIN)
		p->Frequency = PWM_FREQ_MIN;
	if (p->Frequency > PWM_FREQ_MAX)
		p->Frequency = PWM_FREQ_MAX;
	PWM0->TBPRD = _IQ10div(_IQ10(SystemCoreClock/1000.0), p->Frequency << 1) >> 10; //������

	p->k_pwm = PWM0->TBPRD;
	p->FreqPrev = p->Frequency;                 //���������� �������

// ------------------------------------------------------------------------
	// ����������� ������ ePWM0
	// ------------------------------------------------------------------------
	PWM0->TBPHS_bit.TBPHS = 0x0000;            // Phase is 0
	PWM0->TBCTR = 0x0000;                       // Clear counter

	// ��������� ��������. � ����������� ��������� �� �����, �� ��� ��������� �� �������� �� ���� ���
	//PWM0->TBCTL_bit.PRDLD = TB_SHADOW;        	// �������� TBPRD ��� TBCTR = 0
	//PWM0->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  	// ���� �����-����
	//PWM0->TBCTL_bit.PHSEN = TB_DISABLE;         	// �� ���������������� ���� ������ �� � ���
	//PWM0->TBCTL_bit.HSPCLKDIV = 0;     			// ������ �������� ������� (��� �������)
	//PWM0->TBCTL_bit.CLKDIV = 0;                 	// ������ �������� ������� (��� �������)
	//PWM0->TBCTL_bit.SYNCOSEL = TB_CTR_ZERO; 		// ����� ������-������ ��� TBCTR = 0
	//PWM0->TBCTL_bit.FREESOFT = 2; 				// ���������� ���� ��� �������� �������� ����������
	//PWM0->TBCTL_bit.SHADOWGLOB = 1; 				// ��������� ���������� ������ ������� ���������

	PWM0->TBCTL = (TB_SHADOW << PWM_TBCTL_PRDLD_Pos) |
				  (TB_COUNT_UPDOWN << PWM_TBCTL_CTRMODE_Pos) |
				  (TB_DISABLE << PWM_TBCTL_PHSEN_Pos) |
				  (0 << PWM_TBCTL_HSPCLKDIV_Pos) |
				  (0 << PWM_TBCTL_CLKDIV_Pos) |
				  (TB_CTR_ZERO << PWM_TBCTL_SYNCOSEL_Pos) |
				  (2 << PWM_TBCTL_FREESOFT_Pos) |
				  (1 << PWM_TBCTL_SHDWGLOB_Pos);

	// ��������� ������� �������� ���������
	//PWM0->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   	// ������������ ������� ������� ��� CMPA
	//PWM0->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   	// ��������� � �������� �� �������� �� ���� ��������
	//PWM0->CMPCTL_bit.SHDWBMODE = CC_SHADOW;  		// ������������ ������� ������� ��� CMPB
	//PWM0->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   	// ��������� � �������� �� �������� �� ���� ��������
	PWM0->CMPCTL = (CC_SHADOW << PWM_CMPCTL_SHDWAMODE_Pos) |
				   (CC_CTR_ZERO << PWM_CMPCTL_LOADAMODE_Pos) |
				   (CC_SHADOW << PWM_CMPCTL_SHDWBMODE_Pos) |
				   (CC_CTR_ZERO << PWM_CMPCTL_LOADBMODE_Pos);

	// ��������� ������� ���������
	PWM0->CMPA_bit.CMPA = 0;                   // Set compare A value

	// ��������� �������� ��� ��������� �������� � ���������
	//PWM0->AQCTLA_bit.ZRO = AQ_CLEAR; //�������� ��� ���� ��������
	//PWM0->AQCTLA_bit.CAU = AQ_SET; //�������� ��� ��������� � ����������������
	//PWM0->AQCTLA_bit.CAD = AQ_CLEAR; //�������� ��� ��������� � ����������������
	PWM0->AQCTLA = (AQ_CLEAR << PWM_AQCTLA_ZRO_Pos) |
				   (AQ_SET << PWM_AQCTLA_CAU_Pos) |
				   (AQ_CLEAR << PWM_AQCTLA_CAD_Pos);

	//��� PWMB ��������� �� �����, ��� ��� �� ��� ������ ����� ������� ������� ����� ��������� �� ������ A

	PWM0->AQSFRC_bit.RLDCSF = 0; //�� �� ���� ������ 0

	// ��������� ����� ������� �������
	// DBRED = DBFED = 150 * T�_��� / 4
	PWM0->DBRED = _IQ4mpy(_IQ4(150 / 4), p->DeadBand >> 20) >> 4;
	PWM0->DBFED = PWM0->DBRED;

	// ��������� ������ ������� �������:
	// INMODE: S5=0 S4=0 - ������ � ����������� �������� ������� � ������ � ����������� ������ �������
	// 		   ����������� �� ������� PWMA
	// POLSEL: S3 = 1 S2 = 1 - ������ � ����������� �������� ������� ��� ��� ����, � ������
	//		   � ����������� ������ ������� �������������
	// OUTMODE:S0 = 1 S1 = 1 �� ����� PWMA ������� �������� ������ PWMA, �� � ����������� �������� �������
	//		   �� ����� PWMB ������� ������ PWMA � ����������� ������ ������� �� ��� � � ���������
	//PWM0->DBCTL_bit.INMODE = DBA_ALL;
	//PWM0->DBCTL_bit.POLSEL = DB_ACTV_HIC;
	//PWM0->DBCTL_bit.OUTMODE = DB_FULL_ENABLE;
	PWM0->DBCTL = (DBA_ALL << PWM_DBCTL_INMODE_Pos) |
				  (DB_ACTV_HIC << PWM_DBCTL_POLSEL_Pos) |
				  (DB_FULL_ENABLE << PWM_DBCTL_OUTMODE_Pos);

	// ��������� Trip-Zone
	//PWM0->TZCTL_bit.TZA = TZ_STATE;   	// �� ������� "One-Shot Trip" ���������
	//PWM0->TZCTL_bit.TZB = TZ_STATE;     // ��� ������ � ������ ��������� (������)
	PWM0->TZCTL = (TZ_STATE << PWM_TZCTL_TZA_Pos) |
				  (TZ_STATE << PWM_TZCTL_TZB_Pos);

	// ------------------------------------------------------------------------
	// ����������� ������ ePWM1
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM1->TBPRD = PWM0->TBPRD;              		//������ ����� ��
	PWM1->TBPHS_bit.TBPHS = 0x0001;            		// ���� ����� 1 ��-�� �������� � ���� ���� �� �������������
	PWM1->TBCTR = 0x0000;                       	// Clear counter

	// ��������� ��������
	//PWM1->TBCTL_bit.PRDLD = TB_SHADOW;        	// �������� TBPRD ��� TBCTR = 0
	//PWM1->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  	// ���� �����-����
	//PWM1->TBCTL_bit.PHSEN = TB_ENABLE;        	// ��������� �������������
	//PWM1->TBCTL_bit.PHSDIR = TB_UP;      			// ������� ����� ����� �������� ����
	//PWM1->TBCTL_bit.HSPCLKDIV = 0;     			// ������ �������� ������� (��� �������)
	//PWM1->TBCTL_bit.CLKDIV = 0;           		// ������ �������� ������� (��� �������)
	//PWM1->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; 		// ���������� ������-������ "��������"
	//PWM1->TBCTL_bit.FREESOFT = 2; 				// ���������� ���� ��� �������� �������� ����������
	//PWM1->TBCTL_bit.SHADOWGLOB = 1; 				// ��������� ���������� ������ ������� ���������
	PWM1->TBCTL = (TB_SHADOW << PWM_TBCTL_PRDLD_Pos) |
				  (TB_COUNT_UPDOWN << PWM_TBCTL_CTRMODE_Pos) |
				  (TB_ENABLE << PWM_TBCTL_PHSEN_Pos) |
				  (TB_UP << PWM_TBCTL_PHSDIR_Pos) |
				  (0 << PWM_TBCTL_HSPCLKDIV_Pos) |
				  (0 << PWM_TBCTL_CLKDIV_Pos) |
				  (TB_SYNC_IN << PWM_TBCTL_SYNCOSEL_Pos) |
	  	  	  	  (2 << PWM_TBCTL_FREESOFT_Pos) |
	  	  	  	  (1 << PWM_TBCTL_SHDWGLOB_Pos);

	// ������� ��������, ��������� �������� ��������, ������ �����
	// TZ � ���������� ������������� ��� ��, ��� � PWM0
	PWM1->CMPCTL = PWM0->CMPCTL;
	PWM1->AQCTLA = PWM0->AQCTLA;
	PWM1->DBRED = PWM0->DBRED;
	PWM1->DBFED = PWM0->DBFED;
	PWM1->DBCTL = PWM0->DBCTL;
	PWM1->TZCTL = PWM0->TZCTL;
	PWM1->ETSEL = PWM0->ETSEL;

	// ��������� �������
	PWM1->CMPA_bit.CMPA = 0;
	PWM1->AQSFRC_bit.RLDCSF = 0;

	// ------------------------------------------------------------------------
	// ����������� ������ ePWM2
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM2->TBPRD = PWM0->TBPRD;
	PWM2->TBPHS_bit.TBPHS = 0x0001;            // ���� ����� 1 ��-�� �������� � ���� ���� �� �������������
	PWM2->TBCTR = 0x0000;                       // Clear counter

	// ��������� �������� ����� ��, ��� � PWM1
	//PWM2->TBCTL_bit.PRDLD = TB_SHADOW;        		// �������� TBPRD ��� TBCTR = 0
	//PWM2->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  	// Count up-down
	//PWM2->TBCTL_bit.PHSEN = TB_ENABLE;         		// Enable phase loading
	//PWM2->TBCTL_bit.PHSDIR = TB_UP;      			// ������� ����� ����� �������� ����
	//PWM2->TBCTL_bit.HSPCLKDIV = 0;     				// High Speed Time-base Clock Prescale
	//PWM2->TBCTL_bit.CLKDIV = 0;          			// Time-base Clock Prescale
	//PWM2->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; 			// ��������� ������ ������-�������
	//PWM2->TBCTL_bit.FREESOFT = 2; 				// ���������� ���� ��� �������� �������� ����������
	//PWM2->TBCTL_bit.SHADOWGLOB = 1; 				// ��������� ���������� ������ ������� ���������
	PWM2->TBCTL = PWM1->TBCTL;

	// ������� ��������, ��������� �������� ��������, ������ �����
	// TZ � ���������� ������������� ��� ��, ��� � PWM0 � PWM1
	PWM2->CMPCTL = PWM0->CMPCTL;
	PWM2->AQCTLA = PWM0->AQCTLA;
	PWM2->DBRED = PWM0->DBRED;
	PWM2->DBFED = PWM0->DBFED;
	PWM2->DBCTL = PWM0->DBCTL;
	PWM2->TZCTL = PWM0->TZCTL;
	PWM2->ETSEL = PWM0->ETSEL;

	// ��������� �������
	PWM2->CMPA_bit.CMPA = 0;
	PWM2->AQSFRC_bit.RLDCSF = 0;


	// ��������� �����
	PWM0->TZFRC_bit.OST = 1;
	PWM1->TZFRC_bit.OST = 1;
	PWM2->TZFRC_bit.OST = 1;

	//��� 6 �������
	GPIOA->ALTFUNCSET = (1 << 8) + (1 << 9) + (1 << 10) + (1 << 11) + (1 << 12) + (1 << 13);

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
        PWM0->CMPA_bit.CMPA=(Uint16)p->GammaB;
        PWM1->CMPA_bit.CMPA=(Uint16)p->GammaC;
        PWM2->CMPA_bit.CMPA=(Uint16)p->GammaA;
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


	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaC;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaA;

}

//! ������� ��� � ����������� ������ (��� ������ SRM)

//! \memberof TPWM_Module
void PWM_Module_Separate_Update(TPWM_Module *p) {
	// ���������������� ��� �������� �����
/*	_iq PhasePtsA;
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

	//���������

	if (p->GammaA < 0)
		p->GammaA = 0;
	if (p->GammaB < 0)
		p->GammaB = 0;
	if (p->GammaC < 0)
		p->GammaC = 0;

	if  (p->GammaA > p->k_pwm)
		p->GammaA = p->k_pwm + 1;
	if (p->GammaB > p->k_pwm)
		p->GammaB = p->k_pwm + 1;
	if (p->GammaC > p->k_pwm)
		p->GammaC = p->k_pwm + 1;

	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaC;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaA;
*/
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
		default: {
			// ������ �� ������������ ����� ���
			p->PWM_type = PWM_TYPE_6SECT_NO_SV;
			PWM_Module_No_SV_Update(p);
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
		p->k_pwm = _IQ10div(_IQ10(SystemCoreClock/1000.0), p->Frequency << 1) >> 10; //������
		PWM0->TBPRD = p->k_pwm;
		//��� ���� ����� �� �� �����
		PWM1->TBPRD = p->k_pwm;
		PWM2->TBPRD = p->k_pwm;



		p->FreqPrev = p->Frequency; //���������� �������
		EINT;
	}
}

//! ������� ��������� ��� (��������� ���������)

//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *p) {
	p->Enabled = 1;	//���� "��������"

	// ������� �������������� ��������� �������
	PWM0->TZCLR_bit.OST = 1;
	PWM1->TZCLR_bit.OST = 1;
	PWM2->TZCLR_bit.OST = 1;
}

//! ������� ���������� ��� (���������� ���������)

//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *p) {

	p->Enabled = 0;	//���� "���������"
	// ������������� ������� ��� �����
	PWM0->TZFRC_bit.OST = 1;
	PWM1->TZFRC_bit.OST = 1;
	PWM2->TZFRC_bit.OST = 1;
}

/*@}*/
