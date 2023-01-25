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

 \file      main.c
 \brief     ������� ���� �������. �������� main(), � ����� ����������� ����������.
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 */

/** \addtogroup MAIN */
/*@{*/
#include "main.h"
#include <string.h> //��� memcpy


TClarke clarke = CLARKE_DEFAULTS;  							//!<������ ��������������
TPark park = PARK_DEFAULTS;  								//!<������������ ��������������
TIPark ipark = IPARK_DEFAULTS;  							//!<�������� ������������ ��������������
TPidReg3 pid_id = PIDREG3_DEFAULTS;  						//!<���. ���� �� ��� d
TPidReg3 pid_iq = PIDREG3_DEFAULTS;  						//!<���. ���� �� ��� q
TPidReg3 pid_ia = PIDREG3_DEFAULTS;  						//!<���. ���� ����� ���
TPidReg3 pid_spd = PIDREG3_DEFAULTS; 						//!<���. ��������
TPidReg3 pid_pos = PIDREG3_DEFAULTS; 						//!<���. ���������
TVhzProf vhz = VHZPROF_DEFAULTS; 							//!< ����� U/f=const
TSM_Sys sm_sys = SM_Sys_DEFAULTS; 							//!< ������� �������� ��� ������ ���� �������
Uint16 disp_group_number = 0; 								//!< ���������� ��� �������� CANOpen � Unicon
TDataLog dlog = DATALOG_DEFAULTS; 							//!< ������ ������������������� ���������� CANOpen
TSM_Protect sm_prot = SM_PROTECT_DEFAULTS; 					//!< ������ �����
TSM_Ctrl sm_ctrl = SM_CTRL_DEFAULTS; 						//!< ������� ���������� �������, ��������� ��������� ����������
TSM_CmdLogic sm_cmd_logic = SM_CMD_LOGIC_DEFAULTS; 			//!< ��������� ���������������� ������ ����������
TSM_Net sm_net = SM_NET_DEFAULTS; 							//!< �������� ��� ������ ������� ���������
TRMPCtrl rmp = V_RMP_CTRL_DEFAULTS; 						//!< �������� �������������
TAdcDrv adc = ADC_DRV_DEFAULTS; 							//!< ������ ���
TPWM_Module pwm = PWM_Module_DEFAULTS; 						//!< ������ ���
TDPReCAP DPReCAP = DPRECAP_DEFAULTS; 						//!< ������ ��� �� ��������� �����
TposspeedEqep posspeedEqep = POSSPEED_DEFAULTS; 			//!< ������ ��� ���� �������
TCurPar cur_par = TCUR_PAR_DEFAULTS; 						//!< ������ ������� � �������� ������� ����������� ������� - ��������, ��������
TUserMemory UserMem = USERMEMORY_DEFAULTS; 					//!< ������ ������ � ����������������� �������.
TUdControl udControl = UD_CONTROL_DEFAULTS; 				//!<������� ������� ��� ����� ����������
TAutoOffset AutoOffset = AUTO_OFFSET_DEFAULTS;				//!<�������������� ���������� �������� ����� ���
TSSI_Encoder SSI_Encoder = SSI_ENCODER_DEFAULTS; 			//!<������� ��������� ������� ��������� � SSI �����������
TRotorObserver RotorObserver = ROTOR_OBSERVER_DEFAULTS; 	//!<���������� ����������� ��������������� ������ ������������ ���������
TCANtoRS CANtoRS = CAN_TO_RS_DEFAULTS; 						//!<������ ��� ������ � ��������� CANopen ����� UART (RS). ������� CAN �������������� � UART
TDrvInterface drv_interface = DRV_INTERFACE_DEFAULTS;		//!<��������� ��� ������ � ������� ������, ������� � �.�.
TLogger FaultLog = LOGGER_DEFAULTS;							//!<���������������� ������
TGlobalTime global_time = GLOBAL_TIME_DEFAULTS; 			//!<������ � ������
TFanControl fanControl = FAN_CONTROL_DEFAULTS;				//!< ���������� ������������
TbrakeResistor brakeResistor = BRAKE_RESISTOR_DEFAULTS;		//! ���������� ������� ����������
TBitsToEnumNums pult_faults_lister = BITS_TO_ENUM_NUMS_DEFAULTS; //!<�������� ������ ��� Unicon

TRefs refs; 						//!< ��������� � ��������� (����, ��������)
TCmd cmd = { 0 }; 					//!< ��������� � ��������� ����������
TDrvStatus drv_status = { 0 }; 		//!< ������� ������ �������
TDrvParams drv_params; 				//!< ��������� ���������
TSysSwitches sw; 					//!< ��������� ���������� ��������� ������� ����������

Uint32 VendorToken=0x11111111;		//!< ���������� ���� �������������, ������ ��� ��������� UniCON � COODEdit ��� ��������� ������� ������� ������ ���������������
int drv_status_code; 				//!<������ ������� ���������� � ���� ��������� (�����, ������ � �.�.)

//���������� ��� ������� - �������� � ������� CANOpen, 
//� ��� ����� ����������� ����� ������ ���������� � ��������� �
//� UniCon, � ����� ������������ �� �������� � �� ��� ������� � ������ �� ����.
volatile long Debug1 = 0;
volatile long Debug2 = 0;
volatile Uint16 Debug3 = 0;
volatile Uint16 Debug4 = 0;
volatile long DebugW1 = 0;
volatile long DebugW2 = 0;
volatile long DebugW3 = 0;
volatile long DebugW4 = 0;
volatile float DebugF1 = 0;
volatile float DebugF2 = 0;
volatile float DebugF3 = 0;
volatile float DebugF4 = 0;

//�������� ���������� ������ �������
Uint16 CounterCAP_isr = 0;
Uint16 cap0_counter = 0;
Uint16 cap1_counter = 0;
Uint16 cap2_counter = 0;

Uint16 LoopCounter = 0; //!< ������� �������� �������� �����

//!� ���� ������� ���������� ������ ���������
//! \memberof MAIN_C
int main(void) {

 	co1_vars.co_productCode = 51;
	co1_vars.co_revisionNumber = 1;

	/* ��������� ������������, ��������� ��������� */
	SystemInit();				// ��������� ������
	SystemCoreClockUpdate();	// ������� ��������� ���������� ������������ ������� (�� �����, �������������)

	pwm.Off(&pwm); //��������� ��� (�� ������ ������)
	DINT;
	//�������������, ����������, �����.
	sm_sys.init(&sm_sys);
	EINT;//���������� ����������

	//��� � ������ ���������� ��� �������� CANOpen

	while (1) { //������� ����
		LoopCounter++;
		sm_sys.slow_calc(&sm_sys); //������� ������
	}
}

unsigned long CpuTimerIsr1 = 0;
Uint16 TIsr1 = 0;
Uint16 msCounter = 0;

//! ���������, ���������� �� ������� � �������� 1���
//! \memberof MAIN_C
void TMR1_IRQHandler(void) {
	CpuTimerIsr1 = TMR2->VALUE; //���������� ����� ���������� �������
	sm_sys.ms_calc(&sm_sys); //�������������� ������ �����

	msCounter++;

	TIsr1 = (CpuTimerIsr1 - TMR2->VALUE) & 0xFFFFFF; //����� ���������� �������
	if (TIsr1 > 97000) {
		sm_prot.bit_fault1 |= F_PROGRAM_1K; //���� ������ ������� ������, ������
	}

	TMR1->INTSTATUS_bit.INT = 1;	//����� ����������
}

Uint16 FastCounter = 0;
unsigned long CpuTimerIsr10 = 0;
Uint16 TIsr10 = 0;

//! ���������, ���������� �� ������� � �������� 10���
//! \memberof MAIN_C
void TMR0_IRQHandler(void) {
	CpuTimerIsr10 = TMR2->VALUE; //���������� ����� ���������� �������
	sm_sys.fast_calc(&sm_sys); //������ 10��� �����

	FastCounter++;
	TIsr10 = (CpuTimerIsr10 - TMR2->VALUE) & 0xFFFFFF; //����� ���������� �������
	if (TIsr10 > 9700) {
		sm_prot.bit_fault1 |= F_PROGRAM_10K; //���� ������ ������� ������, ������
	}
	TMR0->INTSTATUS_bit.INT = 1;	//����� ����������
}

Uint16 ePWM0_TZ_isr_counter = 0;
//!����������, ����������� ��� ���������� ������
//! \memberof MAIN_C
#if defined (__GNUC__)
void PWM0_TZ_IRQHandler(void)
#elif defined (__CMCPPARM__)
void PWM0_TZ_IRQHandler(void)
#endif
{
	//��� ��� ���������� ������ ��������� ��� ��������� ���
	//� ������������ ���� ���������� ����������� ������������,
	//� ���������� �� ��� �� ���������
	//���� � "���������" ��������� �� ������� ���������� ���, �������, ���� ������
	//����� ���������� ��������� ������� �� ����, ������ ������ � �� ���
	ePWM0_TZ_isr_counter++;
	/*
	 pwm12.Off(&pwm12);

	 if (sm_ctrl.state!=CTRL_STOP)
	 {
	 sm_prot.bit_fault1|= F_PDPINT;
	 }
	 sm_ctrl.state=CTRL_STOP;
	 //���������� ����� ���������� �� ���� �����
	 */
}


//!����������, ����������� �� �������� ������� ������ CAP0
//! \memberof MAIN_C
#if defined (__GNUC__)
void ECAP0_IRQHandler(void)
#elif defined (__CMCPPARM__)
void CAP0_IRQHandler(void)
#endif
{
	//������������ ��� ���������� ��� NVIC - ����� ��� ������ �� ������� ��� ��������� �����
	ECAP0->PEINT = 1;

	if (DPReCAP.CAPCalcEna1 == 0) { //���� ������� ��������� ��������
		DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
		DPReCAP.CAP_WrongEdgeCnt1++;
		return;
	}
	DPReCAP.CAPCalcEna1 = 0;//������ ����� ��������, ����� ������ ���������� 10���. ���� ������� ��� ������, ��� ������

	CounterCAP_isr++;//����� ������� ���� ���������� ������ �������
	CounterCAP_isr = CounterCAP_isr & 0xF;
	cap0_counter++;//������� ���������� ������ ����� ������
	//������ �� ��������� ��� ���� �������� ����� ����������� ������� ���� � ��������� 60 ��������.
	//������� ������� ��������  DPReCAP.Angle6 - ���� � ��������� 60 ��������.
	DPReCAP.Angle6Calc(&DPReCAP);
	//���������� ������ ������� ������1 (0, ���� ������� � ����, �� �� ��������������� �� ������� ��� �������, � ����������� �� ������ ������������ ������...).
	//�������� ����� ����� ���� ��������� � ����������� ��� ������� ������������� ���� � ������� �������� (��������)
	DPReCAP.CAP1Calc(&DPReCAP);

	//������������� ���������� ������������ � 10 ��� ����������
}

//!����������, ����������� �� �������� ������� ������ CAP1
//! \memberof MAIN_C
#if defined (__GNUC__)
void ECAP1_IRQHandler(void)
#elif defined (__CMCPPARM__)
void CAP1_IRQHandler(void)
#endif
{
	//������������ ��� ���������� ��� NVIC - ����� ��� ������ �� ������� ��� ��������� �����
	ECAP1->PEINT = 1;

	if (DPReCAP.CAPCalcEna2 == 0) { //���� ������� ��������� ��������
		DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
		DPReCAP.CAP_WrongEdgeCnt2++;
		return;
	}
	DPReCAP.CAPCalcEna2 = 0;

	CounterCAP_isr++;
	CounterCAP_isr = CounterCAP_isr & 0xF;
	cap1_counter++;
	DPReCAP.Angle6Calc(&DPReCAP);
	DPReCAP.CAP2Calc(&DPReCAP);

	//������������� ���������� ������������ � 10 ��� ����������
}


//!����������, ����������� �� �������� ������� ������ CAP2
//! \memberof MAIN_C
#if defined (__GNUC__)
void ECAP2_IRQHandler(void)
#elif defined (__CMCPPARM__)
void CAP2_IRQHandler(void)
#endif
{
	//������������ ��� ���������� ��� NVIC - ����� ��� ������ �� ������� ��� ��������� �����
	ECAP2->PEINT = 1;

	if (DPReCAP.CAPCalcEna3 == 0) { //���� ������� ��������� ��������
		DPReCAP.CAP_WrongEdgeCnt = (++DPReCAP.CAP_WrongEdgeCnt) & 0xFF;
		DPReCAP.CAP_WrongEdgeCnt3++;
		return;
	}
	DPReCAP.CAPCalcEna3 = 0;

	CounterCAP_isr++;
	CounterCAP_isr = CounterCAP_isr & 0xF;
	cap2_counter++;
	DPReCAP.Angle6Calc(&DPReCAP); //���� ������, �� � ������ ������� ����� �� ���� ������ ��� �����, ��� ��� ���������� �����������, � Angle6Calc ���
	DPReCAP.CAP3Calc(&DPReCAP);

	//������������� ���������� ������������ � 10 ��� ����������
}

//!����������, ����������� �� ������� �������� �����(�������) ������ QEP
//! \memberof MAIN_C
//! �� - �� ��������� ACM601V36-1000 ��� ��������� �����.
//��� ��� ����� ���������� c ����� ���������� �� ����� (��� ����� �� �����, ��� �������)
#if defined (__GNUC__)
void QEP_IRQHandler(void)
#elif defined (__CMCPPARM__)
void QEP1_IRQHandler(void)
#endif
{
	//��������� ������
	posspeedEqep.index(&posspeedEqep);
	//������������ ��� ���������� ��� NVIC
	QEP->INTCLR = 1;
	QEP->QCLR_bit.IEL = 1;
	QEP->QCLR_bit.INT = 1;
}

//���������� ���������� ���� ��� �� ������� ��� � �������� 4 ���������� �� ������
void ADC_SEQ0_IRQHandler (void) {
	adc.fast_calc(&adc);

	dlog.update(&dlog); //������������������� ������
	ADC->IC_bit.SEQIC0 = 1;
}
/*@}*/

