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
 
 \file      SMSys.c
 \brief     ������-������� ��� ������� ��������� �������. (��. TSM_Sys)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 */

/** \addtogroup SMSys */
/*@{*/
#include "main.h"

/* ���������� ������ ���������� ������� �������� ���������� */
#if   defined ( __CMCPPARM__ )
	extern const Uint32 __Vectors;
#elif defined (__GNUC__)
	// ������
#endif

#define LED_ON	GPIOA->MASKLB[8].MASKLB = 8
#define LED_OFF	GPIOA->MASKLB[8].MASKLB = 0
void setLedEnabled (Uint8 enabled) {

	// ���� ���� JTAG - ������� ����-������� � ������
	if (enabled) {
		GPIOA->ALTFUNCCLR = 1 << 3;
	} else {
		GPIOA->ALTFUNCSET = 1 << 3;
	}
}

//! ������������� ������� ���������� ����� ���������

//!������������� ��������� ������� � ��������� ���������� �������.
//!����� ������������� ����������� ����������
//! \memberof TSM_Sys
void SM_Sys_Init(TSM_Sys *p) {

	cmd.all = 0;
	drv_status.all = 0;
	UserMem.init(&UserMem);
	sm_net.init(&sm_net); //������� �����
	adc.init(&adc); //������������� ���
	sm_prot.init(&sm_prot); //������
	sm_cmd_logic.init(&sm_cmd_logic); //������ ���������/����������
	sm_ctrl.init(&sm_ctrl); //��������� ������� ����������
	pwm.init(&pwm); //������ ���
	cur_par.init(&cur_par); //������ ������� ����������� �������
	udControl.init(&udControl);
	//���������� ����� (������� ��� �����. ����)
	global_time.init(&global_time);
	fanControl.init(&fanControl);
	DIO_Init();
	brakeResistor.init(&brakeResistor);

	if (drv_params.sens_type == POS_SENSOR_TYPE_HALL){ //� ���� ������� ������ ��� �� ��������� �����
//		DPReCAP.Init(&DPReCAP); //��� ����.
	}
	if (drv_params.sens_type == POS_SENSOR_TYPE_ENCODER){ //� ���� ������� ������ �������
		//�������� ������������ �������
		posspeedEqep.speed_nom = drv_params.speed_nom;    //������� ��������
		posspeedEqep.pole_pairs = drv_params.p;    //���-�� ��� ������� ���������
		posspeedEqep.Posspeed_CTL.bit.dir = 1;    //����������� ��������
		posspeedEqep.RevolutionCounter=0;
		posspeedEqep.init(&posspeedEqep);//������������� ������ ��������
	}
	if (drv_params.sens_type == POS_SENSOR_TYPE_SSI){ //� ���� ������� ������ ������ � SSI �����������. ������� ������������ ������ ����� ��������������!
		//�������� ������ ������� ��������� SSI
		SSI_Encoder.speed_nom = drv_params.speed_nom;    //������� ��������
		SSI_Encoder.pole_pairs = drv_params.p;    //���-�� ��� ������� ���������
		SSI_Encoder.rotation_dir = 0;    //����������� ��������
		SSI_Encoder.RevolutionCounter=0;
		SSI_Encoder.init(&SSI_Encoder);//������ ��������� SSI
	}
	if (drv_params.sens_type == POS_SENSOR_TYPE_ENC_HALL){
		//�������� ������������ �������
//		DPReCAP.Init(&DPReCAP); //��� ����.
		posspeedEqep.speed_nom = drv_params.speed_nom;    //������� ��������
		posspeedEqep.pole_pairs = drv_params.p;    //���-�� ��� ������� ���������
		posspeedEqep.Posspeed_CTL.bit.dir = 1;    //����������� ��������
		posspeedEqep.RevolutionCounter=0;
		posspeedEqep.init(&posspeedEqep);//������������� ������ ��������
	}

	//�������� ������ ��� ����������� �� ������ ���������� (UniCON)
	pult_faults_lister.num_of_words = 2;
	pult_faults_lister.out_refresh_devisor = 1000; //��� ������ � �� ������� ������ ���������� ����� ����� 1���
	pult_faults_lister.w_ptrs[0] = (Uint16*) &sm_prot.masked_bit_fault1;//������������ ��� ����� ������ ������ �����
	pult_faults_lister.w_ptrs[1] = (Uint16*) &sm_prot.masked_bit_fault2;

	AutoOffset.FilterK = _IQ(0.00001);//���������� ������� ������� ��� ������������ ���
	AutoOffset.init(&AutoOffset); //���� �������� ��������� ������� ��� (����)

#if defined(HW_VECTORCARD_SIMULATOR) || defined(HW_NIIET_BOARD_SIMULATOR)
	//model.motorInternals.udc = 540; //�������� ����� ������� ��������
	model.tpr = _IQ10div(_IQ10(SystemCoreClock/1000.0), pwm.Frequency << 1) >> 10; //������ ������� ���
	model.dt = _IQ4mpy(_IQ4(150 / 4), pwm.DeadBand >> 20) >> 4; //�������� �������� �������
	model.Init(&model); //������ ���������
#endif

	// ��������� ������� 0 �� 10 ���
	TMR0->INTSTATUS_bit.INT = 1;
	TMR0->LOAD_bit.VAL = 10000 - 1; //9999 ���� ����� �� ����� ����������� ���������� ����, ����� � ���� ������� 10���
	TMR0->CTRL = ((1 << 0) | (1 << 3)); // ������ � ���������� ����������

	// ��������� ������� 1 �� 1 ���
	TMR1->INTSTATUS_bit.INT = 1;
	TMR1->LOAD_bit.VAL = 100000 - 1;
	TMR1->CTRL = ((1 << 0) | (1 << 3)); // ������ � ���������� ����������

	//��� �������� ������
	TMR2->LOAD_bit.VAL = 0xFFFFFFFF;
	TMR2->CTRL = (1 << 0); // ������


	/*
	� ���������������� �1921��035 �������������� �������� 3 ���� �� 8-�� ������� ���� PRI_n [7:0] ��� ��������� ����������� ���������� �
	�������� ��� � ����������� ��������� ������� __NVIC_PRIO_BITS. ����������, ��� ������� ���� [4:0] �� ������������ � ��� ���������
	������������� ������ ���� [7:5]. � ������������ �� ������� ��������� PRIGROUP �� ����� ������� ��� ������������ ��� 3 ����, ������� ��� �� 3-�
	������� ��� ������, � ������� ��� ���������, �.�. ��� �� ����� ����������� �����, ��� ����� ������ �� ����� �������� ���������, � ����� - ������.
	���� PRIGROUP = 0, �� ���� PRI_n ���������������� ��� 0bxxxxxxxx, ��� x - ���� ������� ���������� �����. ���� PRIGROUP = 4, �� ���� PRI_n
	���������������� ��� 0bxxx.yyyyy, ��� x - ���� ������� ���������� �����, y - ���� ������� ���������� ��������. � �.�.
	�������, ��� ������� PRIGROUP �� 0 �� 4 ����� ����� ���� � ��� �� ���������, �������� �� ���� ���� ������� 3 ���� ��� ������ � 0 ��� ���������
	(�� ��������, ��� � ��� ������������ ������ 3 ������� ����� ���� ���� PRI_n, �.�. ���� [7:5]), ����� ��� PRIGROUP �� 5 �� 7 ��� ����� ����� �������
	�� ����������� ����� ������������ ��������� ����������� ����� � ��������.
	*/
	NVIC_SetPriorityGrouping(4); // 3 ���� ��� ������, 0 ��� ���������. ����� ����� �� ����� ���������� �������� priority � ������� NVIC_SetPriority �� 0 �� 7 ��� ������� ������ ���������� ����������. 0 - ���������, 7 - ����� ������ ���������.

	NVIC_DisableIRQ(TMR0_IRQn);
	NVIC_DisableIRQ(TMR1_IRQn);
	NVIC_DisableIRQ(ECAP0_IRQn);
	NVIC_DisableIRQ(ECAP1_IRQn);
	NVIC_DisableIRQ(ECAP2_IRQn);
	NVIC_DisableIRQ(PWM0_TZ_IRQn);
	NVIC_DisableIRQ(QEP_IRQn);

	NVIC_ClearPendingIRQ(TMR0_IRQn);
	NVIC_ClearPendingIRQ(TMR1_IRQn);
	NVIC_ClearPendingIRQ(ECAP0_IRQn);
	NVIC_ClearPendingIRQ(ECAP1_IRQn);
	NVIC_ClearPendingIRQ(ECAP2_IRQn);
	NVIC_ClearPendingIRQ(PWM0_TZ_IRQn);
	NVIC_ClearPendingIRQ(QEP_IRQn);

	/* ���������� 10 ��� */
	NVIC_EnableIRQ(TMR0_IRQn);
	NVIC_SetPriority(TMR0_IRQn, IRQ_PRIORITY_10K);

	/* ���������� 1 ��� */
	NVIC_EnableIRQ(TMR1_IRQn);
	NVIC_SetPriority(TMR1_IRQn, IRQ_PRIORITY_1K);

	NVIC_EnableIRQ(ECAP0_IRQn); //CAP0
	NVIC_SetPriority(ECAP0_IRQn, IRQ_PRIORITY_CAP);

	NVIC_EnableIRQ(ECAP1_IRQn); //CAP1
	NVIC_SetPriority(ECAP1_IRQn, IRQ_PRIORITY_CAP);

	NVIC_EnableIRQ(ECAP2_IRQn); //CAP2
	NVIC_SetPriority(ECAP2_IRQn, IRQ_PRIORITY_CAP);

	NVIC_EnableIRQ(PWM0_TZ_IRQn); //PDP (� ��������� ������ ���� ������ ����)
	NVIC_SetPriority(PWM0_TZ_IRQn, IRQ_PRIORITY_TZ);

	NVIC_EnableIRQ(QEP_IRQn); //QEP
	NVIC_SetPriority(QEP_IRQn, IRQ_PRIORITY_EQEP);

	sm_sys.state = SYS_READY;

	// ����� ����� ���� �� ������� �������� ���������:
	// ���������� ��������� ��������� ��������� ����� �, ���������� ������ A3 �� �����
	// �� �� ���� ����� � ��� ��� �������� �������������� �������, ������� A3 ���� ��� JTAG-����
	GPIOA->LOCKKEY = 0xaDeadBee;
	__NOP();__NOP();
	GPIOA->LOCKCLR = 1 << 3;
	GPIOA->OUTENSET = 1 << 3;
	// �� ������ ������ ������������� �������� ������������� ����������
	sw.bit.use_led = FALSE;


#ifdef WATCHDOG_ON
	Watchdog.enable();	//���� ���������� ������ ������������, ��������������
#endif //WATCHDOG_ON
}


//!������� ������ (������ 10���).

//!����� ������� �������� ������� ������� ����������
//! \memberof TSM_Sys
void SM_Sys_Fast_Calc(TSM_Sys *p) {
	sm_net.fast_calc(&sm_net);//������ ���������������� ���������
	if (drv_params.sens_type == POS_SENSOR_TYPE_ENCODER) //� ���� ������� ������ �������
		posspeedEqep.calc(&posspeedEqep); //��� �������
	if (drv_params.sens_type == POS_SENSOR_TYPE_HALL){ //� ���� ������� ������ ��� �����
		DPReCAP.AngleCalc(&DPReCAP); 	//��� ����, ������������ ���� ��������� (��������� � DPReCAP.Angle)
		DPReCAP.Angle6Calc(&DPReCAP); 	//��� ����, ��������� ���� � ��������� 60 �������� (��������� � DPReCAP.Angle6)
		DPReCAP.SpeedCalc(&DPReCAP); 	//��� ����, ������ �������� �������� (DPReCAP.speed)
		DPReCAP.calc_10k(&DPReCAP); 	//��� ����, ��������� �������
	}
	if (drv_params.sens_type == POS_SENSOR_TYPE_SSI){ //������ � ����������� SSI. ����� ������������� ������� ������������ ����!
		SSI_Encoder.calc(&SSI_Encoder);				//������ ��������� SSI
	}

	DIO_fast_calc();				// ���������� ����� � ������
	udControl.calc(&udControl);		// �������� ������ ���
	sm_prot.fast_calc(&sm_prot); 	//������
	sm_ctrl.fast_calc(&sm_ctrl); 	//������� ���������� ������� ������� ����������

	global_time.calc(&global_time);

	cur_par.calc(&cur_par); //������ ������� ����������� �������
	drv_params.sens_type = drv_params.sens_type & 7; //�������� ������� ����� ����������, ��� �����

	brakeResistor.fastCalc(&brakeResistor);
#ifdef WATCHDOG_ON
//	Watchdog.feed();//���� ���������� ������ ������������, ���������� ��� �����
#endif //WATCHDOG_ON
}

//!�������������� ������ 1���.

//!����� �������� ������� ������� ����������, ��������� �������������� �������������
//! \memberof TSM_Sys
void SM_Sys_ms_Calc(TSM_Sys* p) {
	// �����������
	if (sm_ctrl.state == CTRL_STOP) p->ledPeriod = 2000;
	else p->ledPeriod = 1000;

	p->ledTimer++;
	if (p->ledTimer < (p->ledPeriod >> 1))
		LED_ON;
	else if (p->ledTimer < p->ledPeriod)
		LED_OFF;
	else
		p->ledTimer = 0;



	sm_cmd_logic.ms_calc(&sm_cmd_logic); 	//��������� ������ ����������
	sm_net.ms_calc(&sm_net); 				//������� ��� ������ ���������������� ���������
	adc.ms_calc(&adc); 						//���
	sm_prot.ms_calc(&sm_prot); //������
	AutoOffset.ms_calc(&AutoOffset); //���� �������� ��������� ������� ���
	//������� �������� �������� CANopen. ����� ��, � ���������, �������� ������������� dlog
//	Can2BTInterface.ms_calc(&Can2BTInterface, TMR2->VALUE, &co2_vars);
	fanControl.slow_calc(&fanControl);

	UserMem.ms_calc(&UserMem);//���������������� ������ � ��
	if ((drv_params.sens_type == 2) || (drv_params.sens_type == 3)){ //� ���� ������� ������ ��� �����
		DPReCAP.ms_calc(&DPReCAP);
	}
	global_time.ms_calc(&global_time);
}

//!��������� ������ (�������).

//!����� ��������� �������� ��������� �������
//! \memberof TSM_Sys
void SM_Sys_Slow_Calc(TSM_Sys *p) {
	//�������� ������������� ��� ��������������� ����� � ����������
	drv_params._1_Udc_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.Udc_nom));
	drv_params._1_I_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.I_nom));
	drv_params._1_U_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.U_nom));

	UserMem.slow_calc(&UserMem);//���������������� ������ � ��

	sm_prot.slow_calc(&sm_prot);//������ �����
	sm_net.slow_calc(&sm_net); //������� ��� ������ ���������������� ���������
	dlog.background_analizer(&dlog); //������� ���������� ������ �������������������
	global_time.slow_calc(&global_time);
	rmp.slow_calc(&rmp); //�������� ������������� ������� �� ��������������� �� ���������� �������������
	pwm.slow_calc(&pwm); //������� ���������� ������ ��� (�������� ���������������� �������)
	adc.slow_calc(&adc); //������� ���������� ���
	cur_par.slow_calc(&cur_par); //������ ������� ����������� �������
	AutoOffset.slow_calc(&AutoOffset);
	posspeedEqep.slow_calc(&posspeedEqep);//������������� ������ ��������
	RotorObserver.slow_calc(&RotorObserver);//����������� ������ ������ ��
	DPReCAP.slow_calc(&DPReCAP);//��� �����
	DIO_slow_calc();				// ���������� ����� � ������


	if (sw.bit.Reboot & 1) { //������� ������������
		sw.bit.Reboot = 0; //���������� �
		if (sm_ctrl.state == CTRL_STOP) { //��������������� ������ � ��������
			//��������� ����� �����
			//������������� �� ����!
			Watchdog.resetCPU();
		}
	}

	//����� ������� �������� ��� ��� ����� ���
	//������ ������ ������ � �������� � ���������� ������
	if ((sw.bit.AutoOffset) && (sm_ctrl.state == CTRL_STOP)) AutoOffset.Enabled=1;
	else AutoOffset.Enabled=0;

	// ���� ��������� ���������
	if (sw.bit.use_led && !sw.bit.use_led_prev)
		setLedEnabled(TRUE);
	else if (!sw.bit.use_led && sw.bit.use_led_prev)
		setLedEnabled(FALSE);

	sw.bit.use_led_prev = sw.bit.use_led;
}
/*@}*/

