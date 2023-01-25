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


#ifdef HW_VECTORCARD_DRV8301_EVM
#define GPIO_INV_ON  NT_GPIOG->MASKHIGHBYTE_bit[(1<<(8-8))].MASKHB = (1<<(8-8))
//��� ������ ������������ ���������� ��������� ���������� �� ������������, ���������� ������ �������������� �������� ���������� �������
#define GPIO_INV_OFF NT_GPIOG->MASKHIGHBYTE_bit[(1<<(8-8))].MASKHB = (1<<(8-8))
#endif

#ifdef HW_VECTORCARD_DRV8312_EVM
//A[10], F[2], F[4]
#define GPIO_INV_ON  NT_GPIOA->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB = (1<<(10-8)); NT_GPIOF->MASKLOWBYTE_bit[(1<<2)].MASKLB = (1<<2);NT_GPIOF->MASKLOWBYTE_bit[(1<<4)].MASKLB = (1<<4)
#define GPIO_INV_OFF NT_GPIOA->MASKHIGHBYTE_bit[(1<<(10-8))].MASKHB = 0;NT_GPIOF->MASKLOWBYTE_bit[(1<<2)].MASKLB = 0;NT_GPIOF->MASKLOWBYTE_bit[(1<<4)].MASKLB = 0
#endif

#if defined(HW_VECTORCARD_SIMULATOR) || defined(HW_NIIET_BOARD_SIMULATOR)
#define GPIO_INV_ON
#define GPIO_INV_OFF
#endif

#if defined(HW_VECTOR_MK_40_4)
#define GPIO_INV_ON
#define GPIO_INV_OFF
#endif

#if defined(HW_MOTORCONTROLBOARD)
#define GPIO_INV_ON
#define GPIO_INV_OFF
#endif

//! ����������� �������� "������� �������"
#if defined(HW_MOTORCONTROLBOARD)
//! ��� ������������ ��������� ������ ������ 3���, ����� �� �����
#define DEAD_BAND_MIN	_IQ(3)
#define DEAD_BAND_MAX	_IQ(10)
#else
#define DEAD_BAND_MIN	_IQ(0)
#define DEAD_BAND_MAX	_IQ(10)
#endif

//! �������������

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *p) {
	NT_COMMON_REG->PWM_SYNC_bit.TBCLKSYNC = 0; //������������� �������� - ����� ���������� ���������
	/* ���������������� ���� */
	NT_COMMON_REG->PWM_CTRL = 0x8;

// ------------------------------------------------------------------------
	// ����������� ������ ePWM1
	// ------------------------------------------------------------------------
	if (p->Frequency < PWM_FREQ_MIN)
		p->Frequency = PWM_FREQ_MIN;
	if (p->Frequency > PWM_FREQ_MAX)
		p->Frequency = PWM_FREQ_MAX;
	NT_PWM0->TBPRD = _IQ10div(_IQ10(CORE_CLK/1000.0), p->Frequency << 1) >> 10; //������

	p->k_pwm = NT_PWM0->TBPRD;
	p->FreqPrev = p->Frequency;                 //���������� �������
	NT_PWM0->TBPHS_bit.TBPHS = 0x0000;            // Phase is 0
	NT_PWM0->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	NT_PWM0->TBCTL_bit.PRDLD = TB_SHADOW;        // �������� TBPRD ��� TBCTR = 0
	NT_PWM0->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	NT_PWM0->TBCTL_bit.PHSEN = TB_DISABLE;         // Disable phase loading
	NT_PWM0->TBCTL_bit.PHSDIR = TB_UP;      // ������� ����� ����� �������� ����
	NT_PWM0->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	NT_PWM0->TBCTL_bit.CLKDIV = 0;                 // Time-base Clock Prescale
	NT_PWM0->TBCTL_bit.SYNCOSEL = TB_CTR_ZERO; // ����� ������-������ ��� TBCTR = 0

	// Setup shadowing
	NT_PWM0->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	NT_PWM0->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   // Load on zero

	NT_PWM0->CMPCTL_bit.SHDWBMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	NT_PWM0->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   // Load on zero

	// Set Compare values
	NT_PWM0->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Set actions
	NT_PWM0->AQCTLA = AQ_EPWM_DISABLE; // ��� ������ ������� ��� PWM1A ���������
	NT_PWM0->AQCTLA_bit.ZRO = 1; //�������� ��� ���� ��������
	NT_PWM0->AQCTLA_bit.CAU = 2; //�������� ��� ��������� � ����������������
	NT_PWM0->AQCTLA_bit.CAD = 1; //�������� ��� ��������� � ����������������

	//��� PWMB ���� �����, ��� ��� PWM�. ��� ��������. �������� ����� � ������ ��
	NT_PWM0->AQCTLB = NT_PWM0->AQCTLA; // ��� ������ ������� ��� PWM1B ���������
	NT_PWM0->AQCTLB_bit.ZRO = NT_PWM0->AQCTLA_bit.ZRO; //�������� ��� ���� ��������
	NT_PWM0->AQCTLB_bit.CAU = NT_PWM0->AQCTLA_bit.CAU; //�������� ��� ��������� � ����������������
	NT_PWM0->AQCTLB_bit.CAD = NT_PWM0->AQCTLA_bit.CAD; //�������� ��� ��������� � ����������������

	NT_PWM0->AQSFRC_bit.RLDCSF = 0; //�� �� ���� ������ 0

	// Setup Deadband
	// DBRED = DBFED = 150 * T�_��� / 4
	NT_PWM0->DBRED = _IQ4mpy(_IQ4(150 / 4), p->DeadBand >> 20) >> 4;
	NT_PWM0->DBFED = NT_PWM0->DBRED;
	NT_PWM0->DBCTL_bit.IN_MODE = DBA_RED_DBB_FED;    //s4=0, s5=1 �� �������� DT
	NT_PWM0->DBCTL_bit.OUT_MODE = DB_FULL_ENABLE;    //S1=1, S2=2 �� �������� DT
	NT_PWM0->DBCTL_bit.POLSEL = DB_ACTV_HIC;       // PWM1B = !PWM1A; S2=0, S3=1

	NT_PWM0->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT (���������)
	NT_PWM0->ETSEL_bit.INTEN = 0;                  // Disable INT


	//��������� TZ ���� ���������� ���������� ������ (one-shot)
	//   NT_PWM0->TZSEL_bit.OSHT1 = TZ_ENABLE;
//    NT_PWM0->TZSEL_bit.OSHT2 = TZ_ENABLE;
//    NT_PWM0->TZSEL_bit.OSHT3 = TZ_ENABLE;

	// Trip-Zone
	NT_PWM0->TZCTL_bit.TZA = TZ_STATE;   // �� ������� "One-Shot Trip" ���������
	NT_PWM0->TZCTL_bit.TZB = TZ_STATE;          // ��� ������ � ������ ���������

	//��� VectorCARD �� ���� ����������� ADC
	//NT_PWM0->ETSEL_bit.SOCAEN = 1;		// ��������� ������ ���
	//NT_PWM0->ETSEL_bit.SOCASEL = 1;		// ��������� ��� CTR == 0 (Underflow)

	// ------------------------------------------------------------------------
	// ����������� ������ ePWM2
	// ------------------------------------------------------------------------
	// Setup TBCLK
	NT_PWM1->TBPRD = NT_PWM0->TBPRD;              //������ ����� ��
	NT_PWM1->TBPHS_bit.TBPHS = 0x0001;            // ���� ����� 1 ��-�� �������� � ���� ���� �� �������������
	NT_PWM1->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	NT_PWM1->TBCTL_bit.PRDLD = TB_SHADOW;        // �������� TBPRD ��� TBCTR = 0
	NT_PWM1->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	NT_PWM1->TBCTL_bit.PHSEN = TB_ENABLE;         // Enable phase loading
	NT_PWM1->TBCTL_bit.PHSDIR = TB_UP;      // ������� ����� ����� �������� ����
	NT_PWM1->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	NT_PWM1->TBCTL_bit.CLKDIV = 0;           // Time-base Clock Prescale
	NT_PWM1->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; // ���������� ������-������ "��������"

	// Setup shadowing
	NT_PWM1->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	NT_PWM1->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   // Load on zero

	NT_PWM1->CMPCTL_bit.SHDWBMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	NT_PWM1->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   // Load on zero

	// Set Compare values
	NT_PWM1->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Set actions
	NT_PWM1->AQCTLA = AQ_EPWM_DISABLE; // ��� ������ ������� ���������
	NT_PWM1->AQCTLA_bit.ZRO = 1; //�������� ��� ���� ��������
	NT_PWM1->AQCTLA_bit.CAU = 2; //�������� ��� ��������� � ����������������
	NT_PWM1->AQCTLA_bit.CAD = 1; //�������� ��� ��������� � ����������������

	//��� PWMB ���� �����, ��� ��� PWM�. ��� ��������. �������� ����� � ������ ��
	NT_PWM1->AQCTLB = NT_PWM0->AQCTLA; // ��� ������ ������� ��� PWM1B ���������
	NT_PWM1->AQCTLB_bit.ZRO = NT_PWM0->AQCTLA_bit.ZRO; //�������� ��� ���� ��������
	NT_PWM1->AQCTLB_bit.CAU = NT_PWM0->AQCTLA_bit.CAU; //�������� ��� ��������� � ����������������
	NT_PWM1->AQCTLB_bit.CAD = NT_PWM0->AQCTLA_bit.CAD; //�������� ��� ��������� � ����������������

	NT_PWM1->AQSFRC_bit.RLDCSF = 0; //�� �� ���� ������ 0

	// Active high complementary PWMs - Setup Deadband
	NT_PWM1->DBRED = NT_PWM0->DBRED;
	NT_PWM1->DBFED = NT_PWM1->DBRED;
	NT_PWM1->DBCTL_bit.IN_MODE = NT_PWM0->DBCTL_bit.IN_MODE;
	NT_PWM1->DBCTL_bit.OUT_MODE = NT_PWM0->DBCTL_bit.OUT_MODE;
	NT_PWM1->DBCTL_bit.POLSEL = NT_PWM0->DBCTL_bit.POLSEL;

	// Interrupt where we will change the Compare Values
	NT_PWM1->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT
	NT_PWM1->ETSEL_bit.INTEN = 0;                  // Disable INT

	//��������� TZ ���� ���������� ���������� ������ (one-shot)
	//   NT_PWM1->TZSEL_bit.OSHT1 = TZ_ENABLE;
	//   NT_PWM1->TZSEL_bit.OSHT2 = TZ_ENABLE;
	//   NT_PWM1->TZSEL_bit.OSHT3 = TZ_ENABLE;

	// Trip-Zone
	NT_PWM1->TZCTL_bit.TZA = TZ_STATE;   // �� ������� "One-Shot Trip" ���������
	NT_PWM1->TZCTL_bit.TZB = TZ_STATE;          // ��� ������ � ������ ���������

	// ------------------------------------------------------------------------
	// ����������� ������ ePWM3
	// ------------------------------------------------------------------------
	// Setup TBCLK
	NT_PWM2->TBPRD = NT_PWM0->TBPRD;
	NT_PWM2->TBPHS_bit.TBPHS = 0x0001;            // ���� ����� 1 ��-�� �������� � ���� ���� �� �������������
	NT_PWM2->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	NT_PWM2->TBCTL_bit.PRDLD = TB_SHADOW;        // �������� TBPRD ��� TBCTR = 0
	NT_PWM2->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	NT_PWM2->TBCTL_bit.PHSEN = TB_ENABLE;         // Enable phase loading
	NT_PWM2->TBCTL_bit.PHSDIR = TB_UP;      // ������� ����� ����� �������� ����
	NT_PWM2->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	NT_PWM2->TBCTL_bit.CLKDIV = 0;           // Time-base Clock Prescale
	NT_PWM2->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; // ��������� ������ ������-�������

	// Setup shadowing
	NT_PWM2->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	NT_PWM2->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   // Load on zero

	NT_PWM2->CMPCTL_bit.SHDWBMODE = CC_SHADOW;   //�������� SHADOW ��� ���������
	NT_PWM2->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   // Load on zero

	// Set Compare values
	NT_PWM2->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Set actions
	NT_PWM2->AQCTLA = AQ_EPWM_DISABLE; // ��� ������ ������� ���������
	NT_PWM2->AQCTLA_bit.ZRO = 1; //�������� ��� ���� ��������
	NT_PWM2->AQCTLA_bit.CAU = 2; //�������� ��� ��������� � ����������������
	NT_PWM2->AQCTLA_bit.CAD = 1; //�������� ��� ��������� � ����������������

	//��� PWMB ���� �����, ��� ��� PWM�. ��� ��������. �������� ����� � ������ ��
	NT_PWM2->AQCTLB = NT_PWM0->AQCTLA; // ��� ������ ������� ��� PWM1B ���������
	NT_PWM2->AQCTLB_bit.ZRO = NT_PWM0->AQCTLA_bit.ZRO; //�������� ��� ���� ��������
	NT_PWM2->AQCTLB_bit.CAU = NT_PWM0->AQCTLA_bit.CAU; //�������� ��� ��������� � ����������������
	NT_PWM2->AQCTLB_bit.CAD = NT_PWM0->AQCTLA_bit.CAD; //�������� ��� ��������� � ����������������

	NT_PWM2->AQSFRC_bit.RLDCSF = 0; //�� �� ���� ������ 0

	// Active high complementary PWMs - Setup Deadband
	NT_PWM2->DBRED = NT_PWM0->DBRED;
	NT_PWM2->DBFED = NT_PWM2->DBRED;
	NT_PWM2->DBCTL_bit.IN_MODE = NT_PWM0->DBCTL_bit.IN_MODE;
	NT_PWM2->DBCTL_bit.OUT_MODE = NT_PWM0->DBCTL_bit.OUT_MODE;
	NT_PWM2->DBCTL_bit.POLSEL = NT_PWM0->DBCTL_bit.POLSEL;

	// Interrupt where we will change the Compare Values
	NT_PWM2->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT
	NT_PWM2->ETSEL_bit.INTEN = 0;                  // Disable INT

	//��������� TZ ���� ���������� ���������� ������ (one-shot)
	//  NT_PWM2->TZSEL_bit.OSHT1 = TZ_ENABLE;
	//  NT_PWM2->TZSEL_bit.OSHT2 = TZ_ENABLE;
	//  NT_PWM2->TZSEL_bit.OSHT3 = TZ_ENABLE;


	// Trip-Zone
	NT_PWM2->TZCTL_bit.TZA = TZ_STATE;   // �� ������� "One-Shot Trip" ���������
	NT_PWM2->TZCTL_bit.TZB = TZ_STATE;          // ��� ������ � ������ ���������

	// ------------------------------------------------------------------------
	// ����������� ������ ePWM3 ��� ���
	// ------------------------------------------------------------------------
	// Setup TBCLK
	NT_PWM3->TBPRD = NT_PWM0->TBPRD;
	NT_PWM3->TBPHS_bit.TBPHS = 0x0001;      // ���� ����� 1 ��-�� �������� � ���� ���� �� �������������
	NT_PWM3->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	NT_PWM3->TBCTL_bit.PRDLD = TB_SHADOW;        // �������� TBPRD ��� TBCTR = 0
	NT_PWM3->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	NT_PWM3->TBCTL_bit.PHSEN = TB_ENABLE;         // Enable phase loading
	NT_PWM3->TBCTL_bit.PHSDIR = TB_UP;      // ������� ����� ����� �������� ����
	NT_PWM3->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	NT_PWM3->TBCTL_bit.CLKDIV = 0;           // Time-base Clock Prescale
	NT_PWM3->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; // ��������� ������ ������-�������

	// Interrupt where we will change the Compare Values
	NT_PWM3->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT
	NT_PWM3->ETSEL_bit.INTEN = 0;                  // Disable INT


	NT_PWM3->ETSEL_bit.SOCAEN = 1;		// ��������� ������ ���
	NT_PWM3->ETSEL_bit.SOCASEL = 1;		// ��������� ��� CTR == 0 (Underflow)

	//���������� ��� ����� ������
	NT_PWM0->TZCLR = 0x7;
	NT_PWM1->TZCLR = 0x7;
	NT_PWM2->TZCLR = 0x7;

	//��������� �����
#ifdef HW_VECTORCARD_DRV8301_EVM
	//��� 6 �������
	NT_GPIOG->ALTFUNCSET = (1 << 2) + (1 << 3) + (1 << 4);		//ePWMxA(0), (1), (2)
	NT_GPIOA->ALTFUNCSET = (1 << 10);		//ePWMxB(0)
	NT_GPIOF->ALTFUNCSET = (1 << 2) + (1 << 4);		//ePWMxB(1), (2)

	// ������������ ������� - PWM
	NT_COMMON_REG->GPIOPCTLA_bit.PIN10 = 2;//ePWMxB(0)
	NT_COMMON_REG->GPIOPCTLF_bit.PIN2 = 0;//ePWMxB(1)
	NT_COMMON_REG->GPIOPCTLF_bit.PIN4 = 0;//ePWMxB(2)

	NT_COMMON_REG->GPIOPCTLG_bit.PIN2 = 0;//ePWMxA(0)
	NT_COMMON_REG->GPIOPCTLG_bit.PIN3 = 0;//ePWMxA(1)
	NT_COMMON_REG->GPIOPCTLG_bit.PIN4 = 0;//ePWMxA(2)

	//NT_GPIOG->DATAOUT |= (1 << 6);
	NT_GPIOG->OUTENSET = (1 << 6); //InvEnable
#endif

#if defined(HW_VECTORCARD_DRV8312_EVM)
	//��� 3 ������ ���������� �������� ������� (������ ����� ����� ���� ���������)
	NT_GPIOG->ALTFUNCSET = (1 << 2) + (1 << 3) + (1 << 4);	 //ePWMxA(0), (1), (2)

	// ������������ ������� - PWM
	NT_COMMON_REG->GPIOPCTLG_bit.PIN2 = 0;//ePWMxA(0)
	NT_COMMON_REG->GPIOPCTLG_bit.PIN3 = 0;//ePWMxA(1)
	NT_COMMON_REG->GPIOPCTLG_bit.PIN4 = 0;//ePWMxA(2)

	//��������� �������������� ������� (�� ������)
	NT_GPIOA->ALTFUNCCLR = (1 << 10);		//A[10]
	NT_GPIOF->ALTFUNCCLR = (1 << 2) + (1 << 4);		//F[2], F[4]

	//A[10], F[2], F[4]  ����� ������
	NT_GPIOA->OUTENSET = (1 << 10);
	NT_GPIOF->OUTENSET = (1 << 2);
	NT_GPIOF->OUTENSET = (1 << 4);
#endif


#ifdef HW_VECTOR_MK_40_4
	NT_GPIOG->ALTFUNCSET_bit.ALTFUNCSET = (1 << 2) + (1 << 3) + (1 << 4); //ePWMxA(0), (1), (2)
	NT_GPIOF->ALTFUNCSET_bit.ALTFUNCSET = (1 << 0) + (1 << 2) + (1 << 4); //ePWMxB(0), (1), (2)

	// ������������ ������� - PWM
	NT_COMMON_REG->GPIOPCTLF_bit.PIN0 = 0;//ePWMxB(0)
	NT_COMMON_REG->GPIOPCTLF_bit.PIN2 = 0;//ePWMxB(1)
	NT_COMMON_REG->GPIOPCTLF_bit.PIN4 = 0;//ePWMxB(2)

	NT_COMMON_REG->GPIOPCTLG_bit.PIN2 = 0;//ePWMxA(0)
	NT_COMMON_REG->GPIOPCTLG_bit.PIN3 = 0;//ePWMxA(1)
	NT_COMMON_REG->GPIOPCTLG_bit.PIN4 = 0;//ePWMxA(2)

	//���� ���������� ������
	NT_GPIOA->ALTFUNCCLR = (1<<8); //A[8]

#endif

#ifdef HW_MOTORCONTROLBOARD
	//��� 6 �������
	NT_GPIOG->ALTFUNCSET = (1 << 2) + (1 << 3) + (1 << 4);		//ePWMxA(0), (1), (2)
	NT_GPIOF->ALTFUNCSET = (1 << 0);							//ePWMxB(0)
	NT_GPIOA->ALTFUNCSET = (1 << 11) + (1 << 12);				//ePWMxB(1), (2)

	// ������������ ������� - PWM
	NT_COMMON_REG->GPIOPCTLF_bit.PIN0 = 0;		//ePWMxB(0)
	NT_COMMON_REG->GPIOPCTLA_bit.PIN11 = 2;		//ePWMxB(1)
	NT_COMMON_REG->GPIOPCTLA_bit.PIN12 = 2;		//ePWMxB(2)


	NT_COMMON_REG->GPIOPCTLG_bit.PIN2 = 0;//ePWMxA(0)
	NT_COMMON_REG->GPIOPCTLG_bit.PIN3 = 0;//ePWMxA(1)
	NT_COMMON_REG->GPIOPCTLG_bit.PIN4 = 0;//ePWMxA(2)
#endif

	//���������� ������ ���
	NT_COMMON_REG->PWM_SYNC_bit.TBCLKSYNC = 0x1FF;

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
    if (NT_PWM0->TBCTR>30) {
        NT_PWM0->CMPA_bit.CMPA=(Uint16)p->GammaA;
        NT_PWM1->CMPA_bit.CMPA=(Uint16)p->GammaB;
        NT_PWM2->CMPA_bit.CMPA=(Uint16)p->GammaC;
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
    if (NT_PWM0->TBCTR>30) {
        NT_PWM0->CMPA_bit.CMPA=(Uint16)p->GammaA;
        NT_PWM1->CMPA_bit.CMPA=(Uint16)p->GammaB;
        NT_PWM2->CMPA_bit.CMPA=(Uint16)p->GammaC;
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


	NT_PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
	NT_PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
	NT_PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;

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

	NT_PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
	NT_PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
	NT_PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;

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

	NT_PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
	NT_PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
	NT_PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;
}

//! ������� ��� ��� ��������� ������� ����������� ������������� ���������

//! \memberof TPWM_Module
void PWM_Module_ChargingMode(TPWM_Module *p) {
	p->GammaA = p->k_pwm;
	p->GammaB = p->k_pwm;
	p->GammaC = p->k_pwm;

	DINT;
	if (NT_PWM0->TBCTR > 30) {
		NT_PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
		NT_PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
		NT_PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;
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
	NT_PWM0->DBRED = _IQ4mpy(_IQ4(100), p->DeadBand >> 20) >> 4;
	//�� ��� ����� �� �� �����
	NT_PWM0->DBFED = NT_PWM0->DBRED;

	NT_PWM1->DBFED = NT_PWM0->DBRED;
	NT_PWM1->DBRED = NT_PWM0->DBRED;
	NT_PWM2->DBFED = NT_PWM0->DBRED;
	NT_PWM2->DBRED = NT_PWM0->DBRED;

	if (p->MinGammaLimit < DEAD_BAND_MIN)
		p->MinGammaLimit = GAMMA_LIMIT_MIN;
	if (p->MinGammaLimit > DEAD_BAND_MAX)
		p->MinGammaLimit = GAMMA_LIMIT_MAX;
	NT_PWM0->FWDTH = _IQ4mpy(_IQ4(100), p->MinGammaLimit >> 20) >> 4;
	NT_PWM1->FWDTH = NT_PWM0->FWDTH;
	NT_PWM2->FWDTH = NT_PWM0->FWDTH;
	//������� ���. ����� "�� ����".
	if (p->FreqPrev != p->Frequency) { //������� �������
		DINT; //���������� ����������
		//�������� ���������/��������
		if (p->Frequency < PWM_FREQ_MIN)
			p->Frequency = PWM_FREQ_MIN;
		if (p->Frequency > PWM_FREQ_MAX)
			p->Frequency = PWM_FREQ_MAX;
		//�������� ������
		p->k_pwm = _IQ10div(_IQ10(CORE_CLK/1000.0), p->Frequency << 1) >> 10; //������
		NT_PWM0->TBPRD = p->k_pwm;
		//��� ���� ����� �� �� �����
		NT_PWM1->TBPRD = p->k_pwm;
		NT_PWM2->TBPRD = p->k_pwm;
		NT_PWM3->TBPRD = p->k_pwm;        //������ ���

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

	NT_PWM3->TBPHS_bit.TBPHS = 1;//������ ������ ��� ������� ���: 1 - ����� �� ���� �������

}

//! ������� ��������� ��� (��������� ���������)

//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *p) {
	p->Enabled = 1;	//���� "��������"

	// ������� �������������� ��������� �������
    NT_PWM0->AQCSFRC = 0;
    NT_PWM1->AQCSFRC = 0;
    NT_PWM2->AQCSFRC = 0;
	GPIO_INV_ON;

}

//! ������� ���������� ��� (���������� ���������)

//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *p) {

	p->Enabled = 0;	//���� "���������"
	// ������������� ������� ��� �����

	NT_PWM0->AQCSFRC = 9;  // 0x1 - 0 �� ������ PWMxA, 0x8 - 1 �� ������ PWMxB
    NT_PWM1->AQCSFRC = 9;  // 0x1 - 0 �� ������ PWMxA, 0x8 - 1 �� ������ PWMxB
    NT_PWM2->AQCSFRC = 9;  // 0x1 - 0 �� ������ PWMxA, 0x8 - 1 �� ������ PWMxB
	GPIO_INV_OFF;

}

/*@}*/
