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

 \file      SMNet.c
 \brief     ������ ������ ���������� ��� ������ � �����.  (��. TSM_Net)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 */

/** \addtogroup SMNet */
/*@{*/

#include "DSP.h"
#include "V_IQmath.h"
#include "main.h"

//!�������������.

//!���������� �������������� �������������, ������������� ������ �������.
//! \memberof TSM_Net
void SM_Net_Init(TSM_Net *p) {

	p->state = 0;
	p->state_prev = 0xff;

#ifdef CAN_1_ENABLE
	//��������� �������� CANOpen_1
    co1_vars.settings.LoadParamsFromUserMemory_ena = 1;//��������� ��������� �������� ���������� �� �����
    co1_vars.CAN_REGS = (NT_CAN_TypeDef *)NT_CAN_BASE;//�������� �������� ����� ��������� ��������� CAN
    co1_vars.settings.CAN_ISR_priority = IRQ_PRIORITY_CAN;//���������� ���������� ��������� CAN (���������� ������ ����������)
    co1_vars.settings.CAN_IRQn = CAN1_IRQn;//�������� ����� ���������� CAN2 �� ������� ���������� � ������� CANOpen
    co1_vars.settings.MultiPDO_ena = 0;//���������� ��������� PDO ��� ����� ������ ���� (����. �������)
    co1_vars.settings.RX_PDO_Callback_ena = 0; //�� �������� ������� ��������� ������ ��� ������ PDO
    co1_vars.settings.AutoBusON_ena = 1; //������������� ������������� CAN ��� ������� �� �����
    co1_vars.settings.BlockTransfer_ena = 1;//��������� ������� �������� (����� ��� ������������)
    co1_vars.settings.speedCANTablePointer = &canSpeedTable;//�������� �������� ��������� ��� ��������� �������� CAN
    co1_vars.settings.resetCPU = propReset;//�������� �������� ����� ������� ������ ����������������
    co1_Init(&co1_vars); //������������� �������� CANOpen
#endif

#ifdef CAN_2_ENABLE
    //��������� �������� CANOpen_2
    co2_vars.settings.LoadParamsFromUserMemory_ena = 1;//��������� ��������� �������� ���������� �� �����
    co2_vars.CAN_REGS = (NT_CAN_TypeDef *)NT_CAN_BASE;//�������� �������� ����� ��������� ��������� CAN
    co2_vars.settings.CAN_ISR_priority = IRQ_PRIORITY_CAN;//���������� ���������� ��������� CAN (���������� ������ ����������)
    co2_vars.settings.CAN_IRQn = CAN2_IRQn;//�������� ����� ���������� CAN2 �� ������� ���������� � ������� CANOpen
    co2_vars.settings.MultiPDO_ena = 0;//���������� ��������� PDO ��� ����� ������ ���� (����. �������)
    co2_vars.settings.RX_PDO_Callback_ena = 0; //�� �������� ������� ��������� ������ ��� ������ PDO
    co2_vars.settings.AutoBusON_ena = 1; //������������� ������������� CAN ��� ������� �� �����
    co2_vars.settings.BlockTransfer_ena = 1;//��������� ������� �������� (����� ��� ������������)
    co2_vars.settings.speedCANTablePointer = &canSpeedTable;//�������� �������� ��������� ��� ��������� �������� CAN
    co2_vars.settings.resetCPU = propReset;//�������� �������� ����� ������� ������ ����������������
    co2_Init(&co2_vars); //������������� �������� CANOpen
#endif

	//������ �������:
	//	������ ������: 50
	//	��������� ����� � SPI: 3000
	FaultLog.init((TLogger*)&FaultLog, 50, 3000,(Uint32*) &RTCclock.packed_time);//���� ��������� �� ����� ����� ���� ������������� � ����������� �� ������ �����

#if (defined(CANTORS_ENA)) || (defined(CANTOUSB_ENA))
//������ � CANopen ����� UART (����������� � CAN, ��� ���������)
	CANtoRS.nodeID = (Uint16*)&co2_vars.co_nodeID; //����� ���� �� CANopen
    CANtoRS.callback = Z_co_receiveSDOrequest;//��������� �� ������� ��������� ������ �� �������� CANopen �� ������� SDO ���������
	CANtoRS.init(&CANtoRS);
#endif
#ifdef MODBUS_ENA
	// ����������� MODBUS
	ModBus.ExecutionFreq = 10000;//������� ������ ������� ������ ������ � ���
	ModBus.Init(&ModBus);
	MBVarsConv.init(&MBVarsConv);
#endif
}

//!��������� ������.

//! ���������� �������������� �������������, ������� ������ ��������� �������.

//! \memberof TSM_Net
void SM_Net_Slow_Calc(TSM_Net *p) {


#ifdef CAN_1_ENABLE
	co1_vars.co_scaleNum0 = 1; //��� ���������������
	co1_vars.co_scaleNum1 = 100;	// %
	co1_vars.co_scaleNum2 = drv_params.freq_nom;	//��
	co1_vars.co_scaleNum3 = drv_params.U_nom;//���������� ������ ����������� �����������
	co1_vars.co_scaleNum4 = drv_params.I_nom; //��� ������ �������
	co1_vars.co_scaleNum5 = 1;
	co1_vars.co_scaleNum6 = 1;
	co1_vars.co_scaleNum7 = drv_params.Udc_nom; //���������� ��� �������
	co1_vars.co_scaleNum8 = drv_params.power; //18 � ������� 9.6 //��������
	co1_vars.co_scaleNum9 = 1;
	co1_vars.co_scaleNumA = 20; //�����������
	co1_vars.co_scaleNumB = 1;
	co1_vars.co_scaleNumC = 1;
	co1_vars.co_scaleNumD = 1;
	co1_vars.co_scaleNumE = 1;
	co1_vars.co_scaleNumF = 1;
	co1_vars.co_scaleNum10 = 1; //
	co1_vars.co_scaleNum11 = 1; //
	co1_vars.co_scaleNum12 = drv_params.power; //18 � ������� 10.6 //��������
	co1_vars.co_scaleNum13 = 360; //
	co1_vars.co_scaleNum14 = drv_params.speed_nom; //����������� ������� ��������
	co1_vars.co_scaleNum15 = 1; //
	co1_vars.co_scaleNum16 = 1; //
	co1_vars.co_scaleNum17 = ((((long) drv_params.Udc_nom) << 6) / (long) drv_params.I_nom); //R��� 10.6
	co1_vars.co_scaleNum18 = 1000;
	co1_vars.co_scaleNum19 = 1;
	co1_vars.co_scaleNum1A = 1;
	co1_vars.co_scaleNum1B = 1;
	co1_vars.co_scaleNum1C = 1;
	co1_vars.co_scaleNum1D = 1;
	co1_vars.co_scaleNum1E = 1;
	co1_vars.co_scaleNum1F = 1;

	co_background_calc(&co1_vars); //������ �������� CANOpen_1 �������
#endif


#ifdef CAN_2_ENABLE
	co2_vars.co_scaleNum0 = 1; //��� ���������������
	co2_vars.co_scaleNum1 = 100;	// %
	co2_vars.co_scaleNum2 = drv_params.freq_nom;	//��
	co2_vars.co_scaleNum3 = drv_params.U_nom;//���������� ������ ����������� �����������
	co2_vars.co_scaleNum4 = drv_params.I_nom; //��� ������ �������
	co2_vars.co_scaleNum5 = 1;
	co2_vars.co_scaleNum6 = 1;
	co2_vars.co_scaleNum7 = drv_params.Udc_nom; //���������� ��� �������
	co2_vars.co_scaleNum8 = drv_params.power; //18 � ������� 9.6 //��������
	co2_vars.co_scaleNum9 = 1;
	co2_vars.co_scaleNumA = 20; //�����������
	co2_vars.co_scaleNumB = 1;
	co2_vars.co_scaleNumC = 1;
	co2_vars.co_scaleNumD = 1;
	co2_vars.co_scaleNumE = 1;
	co2_vars.co_scaleNumF = 1;
	co2_vars.co_scaleNum10 = 1; //
	co2_vars.co_scaleNum11 = 1; //
	co2_vars.co_scaleNum12 = drv_params.power; //18 � ������� 10.6 //��������
	co2_vars.co_scaleNum13 = 360; //
	co2_vars.co_scaleNum14 = drv_params.speed_nom; //����������� ������� ��������
	co2_vars.co_scaleNum15 = 1; //
	co2_vars.co_scaleNum16 = 1; //
	co2_vars.co_scaleNum17 = ((((long) drv_params.Udc_nom) << 6) / (long) drv_params.I_nom); //R��� 10.6
	co2_vars.co_scaleNum18 = 1000;
	co2_vars.co_scaleNum19 = 1;
	co2_vars.co_scaleNum1A = 1;
	co2_vars.co_scaleNum1B = 1;
	co2_vars.co_scaleNum1C = 1;
	co2_vars.co_scaleNum1D = 1;
	co2_vars.co_scaleNum1E = 1;
	co2_vars.co_scaleNum1F = 1;

	co_background_calc(&co2_vars); //������ �������� CANOpen_2 �������
#endif

	drv_params.U_nom = 0.5759 * drv_params.Udc_nom;//����������� ������ ����������
	drv_params.power = ((long) 300) << 6; //�������� � ������� 10.6
	drv_params.freq_nom = ((float) drv_params.speed_nom * drv_params.p) / 60 + 0.5; //����� �������
	drv_interface.calc(&drv_interface);
	FaultLog.background_calc(&FaultLog);

#ifdef MODBUS_ENA
	MBVarsConv.slow_calc(&MBVarsConv);
#endif

	if (RTCclock.ClockOk)//���� ��������?
		FaultLog.time_ptr = (Uint32*) &RTCclock.packed_time; //����� ��� ����� ������ �� �����
	else
		FaultLog.time_ptr = (Uint32*) &global_time.PowerOn_time;//���� �� ��������, �� �� ������ �������� ������� ���������
}

//!������� ������

//!������� ������ ��������� ������� �������, ����� ������� "�������������" ����� ������ � ��������������
//! \memberof TSM_Net
void SM_Net_ms_Calc(TSM_Net *p) {
	//������� �������� ��������� ������� ���������� � ���������.
	//�� drv_status_code ������������ ������ ������� � UniCON
	if (drv_status.bit.ready == 1)
		drv_status_code = DRV_STATUS_READY;
	if (drv_status.bit.running == 1)
		drv_status_code = DRV_STATUS_RUNNING;
	if (drv_status.bit.testing == 1)
		drv_status_code = DRV_STATUS_TESTING;
	if (drv_status.bit.fault == 1)
		drv_status_code = DRV_STATUS_FAULT;
	if (drv_status.bit.alarm == 1)
		drv_status_code |= DRV_STATUS_ALARM;
	else
		drv_status_code &= ~DRV_STATUS_ALARM;
	if (drv_status.bit.overheat == 1)
		drv_status_code = DRV_STATUS_OVERHEAT;
	else
		drv_status_code &= ~DRV_STATUS_OVERHEAT;
	//������� �������� ������ ��� ������ (UniCON)
	pult_faults_lister.calc(&pult_faults_lister);
	sm_prot.Main_ErrorCode = 0xFF & pult_faults_lister.output;


#ifdef CAN_1_ENABLE
	co_1ms_calc(&co1_vars);    //������ �������� CANOpen_1
#endif

#ifdef CAN_2_ENABLE
	co_1ms_calc(&co2_vars);    //������ �������� CANOpen_2
#endif

#if (defined(CANTORS_ENA)) || (defined(CANTOUSB_ENA))
	CANtoRS.calc(&CANtoRS);
#endif
#ifdef MODBUS_ENA
	MBVarsConv.calc(&MBVarsConv);
#endif

}

void SM_Net_fast_Calc(TSM_Net *p) {

#ifdef MODBUS_ENA
	ModBus.Execute(&ModBus);
#endif
}

/*@}*/
