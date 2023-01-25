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

 \file      SMProtect.c
 \brief     ������ �����.   (��. TSM_Protect)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup SMProtect
 @{ */

#include "DSP.h"
#include "main.h"
#include "stdlib.h"

int16 WriteCounter = 0;

//!�������������

//!������������ ������ ����������
//! \memberof TSM_Protect
void SM_Protect_Init(TSM_Protect *p) {
	p->state_prev = 0xff;
	p->state = 0x00;
}

//! ������� ������.

//!������������ ��� ������ � ��� �� ������������� ������������� ������.
//! \memberof TSM_Protect
void SM_Protect_Fast_Calc(TSM_Protect *p) {

	//���������� ������ �� ���������
	if (pwm.PDP_Fault) {
		if ((sm_ctrl.state != CTRL_STOP) && (sm_ctrl.state != CTRL_RUN))
			sm_prot.bit_fault1 |= F_PDPINT;
	}

	if (!DRV_FAULT) {
		//������� �����-�� ���������� ������
		sm_prot.bit_fault1 |= F_PDPINT;
	}

	/*������ �� ������������� ����*/
	if (labs(adc.Imeas_a) > sm_prot.Imax_protect) sm_prot.bit_fault2 |= F_CTRL_MAX_I_PH_A;
	if (labs(adc.Imeas_b) > sm_prot.Imax_protect) sm_prot.bit_fault2 |= F_CTRL_MAX_I_PH_B;
	if (labs(adc.Imeas_c) > sm_prot.Imax_protect) sm_prot.bit_fault2 |= F_CTRL_MAX_I_PH_C;

	// ������ �� ����� ��� ����������������� ���� �������� ������ ���
	if (udControl.Enabled == 1) {           //���� ���� ���� ������������ ���, �� ���������� ������ �� ���������� �������
	    if (udControl.fault_start == 1)
	        sm_prot.bit_fault1 |= F_RELAY_START;
	}

	//��� ���������� �������� ���� ��������� ����� 
	if (labs(cur_par.speed) > sm_prot.speed_max) {
		sm_prot.bit_fault2 |= F_CTRL_SPEED_MAX; // ������������� Ud
	}

	//��� ���������� ���������� ���� ��������� ����� 
	if (adc.Udc_meas > sm_prot.Umax_protect) {
		sm_prot.bit_fault1 |= F_CTRL_HI_UDC; // ������������� Ud
	}

	//�������� ����������
	if (adc.Udc_meas < sm_prot.Umin_protect) { //���� ������ ������� �� ����� ������
		if (sm_ctrl.state != CTRL_STOP) {
			sm_prot.bit_fault1 |= F_CTRL_LOW_UDC;
		}
	}

	DINT; //���������� ����������
		  //������, ��������� ������� ��������
	p->masked_bit_fault1 = p->bit_fault1 & p->mask_fault1;//������������ ������ ������
	p->masked_bit_fault2 = p->bit_fault2 & p->mask_fault2;
	EINT;      //���������� ����������


	//������� ���������� ������� �����
	if (p->state_prev != p->state) //����� ���������?
		p->E = 1;//�������� ���� ������� ��������� "entry"
	else
		p->E = 0;//����� ����������
	p->state_prev = p->state;

	switch (p->state) {//� ����������� �� �������� ���������
	case PROT_OFF: { //������ ���������
		if (p->E == 1) { //������ ���������
		}

		//�������� ��� ������
		p->bit_fault1 = 0;
		p->bit_fault2 = 0;

		//���������� ��������� ������� ����� ��������� �����������
		//����� �� ������ ������ ������������ ������ ���
		if (p->powered_okCounter++ > 5000) {
			p->state = PROT_ON_OK;
		}
		break;
	}

	case PROT_ON_OK: {  //�����
		if (p->E == 1) {        //������ ���������
			drv_status.bit.fault = 0;
		}
		//���� ������?
		if ((p->masked_bit_fault1 | p->masked_bit_fault2) != 0) {
			p->state = PROT_FAIL; //��������� � ��������� ������
		}
		break;
	}

	case PROT_FAIL: { //��������� ������ (��������� ������)
		if (p->E == 1) {
			cmd.all = 0;
		}
		drv_status.bit.fault = 1;
		//���������� ���. ���� ��� ��� ��������� ���������� �������� �����������, ����� �� �� �����
		pwm.Off(&pwm);
		//������ ������� ������
		if (cmd.bit.trip_reset == 1) {//������� �� ����� ������
			p->state = PROT_ON_OK;//���� � "�����"
			p->clearDrvFault = 1;	//��������� �������� ������ ������� ������

			if (udControl.Enabled == 1) {        //���� ���� ���� ������������ ���, �� ���������� ��������� ��������� ������
			    udControl.fault_start = 0;
            }

			//�������� ��� ����� ������
			p->bit_fault1 = 0;
			p->bit_fault2 = 0;
			cmd.all = 0;//��������� �����

		}
		break;
	}
	}
}

//! \memberof TSM_Protect
void SM_Protect_ms_Calc(TSM_Protect *p) {
	if (WriteCounter <= 15)   //���� ������ �����
	{
		if (((sm_prot.masked_bit_fault1 >> WriteCounter) & 0x1) != 0)  //����� ii-� ���� ������
		{
			if (((sm_prot.bit_fault_written1 >> WriteCounter) & 0x1) == 0)  //� ��� �� ��������
			{
				FaultLog.write(&FaultLog, WriteCounter + 1);
				sm_prot.bit_fault_written1 |= (1 << WriteCounter);
			}
		}
		else
			sm_prot.bit_fault_written1 &= ~(1 << WriteCounter);
	}
	else if (WriteCounter <= 31) //������ �����
	{
		if (((sm_prot.masked_bit_fault2 >> (WriteCounter - 16)) & 0x1) != 0)  //����� ii-� ���� ������
		{
			if (((sm_prot.bit_fault_written2 >> (WriteCounter - 16)) & 0x1) == 0)  //� ��� ������ ��� ���������
			{
				FaultLog.write(&FaultLog, WriteCounter + 1);
				sm_prot.bit_fault_written2 |= (1 << (WriteCounter - 16));
			}
		}
		else
			sm_prot.bit_fault_written2 &= ~(1 << (WriteCounter - 16));
	}
	WriteCounter++;
	if (WriteCounter >= (33 - 1))
		WriteCounter = 0;
}

//! ��������� ������.

//! \memberof TSM_Protect
void SM_Protect_Slow_Calc(TSM_Protect *p) {
	/* �������� ���������� ����� ��������. �� ������������� �������� ����� ��� �������,
	 * � �������� ������� /FAULT � /OCTW, �� ����� ������, ��� ������ ���������, ���� �� SPI ��������� �������.
	 * �������, ������, ����� � ����.
	 */
	if (p->readDrvSts == 1) {
		p->readDrvSts = 0;
	}

	/* ����� �������� ������, ���� ��������� ��� ����� GATE_RESET */
	if (p->clearDrvFault == 1) {
		p->clearDrvFault = 0;
	}
}

/*@}*/
