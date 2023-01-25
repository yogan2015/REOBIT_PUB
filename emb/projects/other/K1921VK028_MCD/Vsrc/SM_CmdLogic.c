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
 
 \file      SMCmdLogic.c
 \brief     ��������� ������ � �������, ����������� �� ��������� ����������. (��. TSM_CmdLogic)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup SMCmdLogic
 @{*/

#include "DSP.h"
#include "V_IQmath.h"
#include "main.h"

//!�������������

//!������ ���������...
//! \memberof TSM_CmdLogic
void SM_CmdLogicInit(TSM_CmdLogic *p) {
	p->state = 0;
	p->state_prev = 0xFF;
	cmd.all = 0;
}

//!��������� ������

//! \memberof TSM_CmdLogic
void SM_CmdLogicSlow_Calc(TSM_CmdLogic *p) {

}

//!1��� ������

//!��������� ��������� ���������� ������ � ������ ��,
//!������� ����������� ��������� ������ ������ � �������.
//! \memberof TSM_CmdLogic
void SM_CmdLogicms_Calc(TSM_CmdLogic *p) {
	p->StartButton = STARTBUTTON;   //��������� ����� ������
	p->StopButton = STOPBUTTON;     //��������� ����� �����
	p->ResetButton = RESETBUTTON;

	//����������� ��������� ����������� ��������
	if (p->state_prev != p->state)
		p->E = 1;
	else
		p->E = 0;
	p->state_prev = p->state;

#if defined (HW_MCB3)
	if ((p->StartButton==1) && (p->StartButtonPrev==0)){
		cmd.bit.start=1;//������� �� ������. ��� �� �������� ����� CAN
	}
	if ((p->StopButton==1) && (p->StopButtonPrev==0)){
		cmd.bit.stop=1;
	}
	p->StartButtonPrev=p->StartButton;
	p->StopButtonPrev=p->StopButton;
	p->ResetButtonPrev = p->ResetButton;
#endif

	//���������� ����� ������
	switch (p->state) {
	case CMD_LOGIC_TURNED_OFF: {	//��������� 0- ��������
		if (p->E == 1) {
			/*ENTRY*/
			sm_ctrl.state = CTRL_STOP;
			drv_status.bit.ready = 1;
			drv_status.bit.running = 0;
		}

		if (sm_prot.state == PROT_ON_OK) {//���� �� ����� ���������, ������������ ������� ���������
			if ((cmd.bit.start == 1) && (sm_sys.state == SYS_READY)) {//���� ������� ������� ������
				if (udControl.Enabled == 0) {	//���� ���� �������� ������ ��� ���������, �� ��������� � �����
					p->state = CMD_LOGIC_TURNED_ON;	//�������
				}
				else {
				    if (udControl.StateOn == 1) { //���� ���� �������� ������ ��� ��������, ���� ������������ ����, � ����� ���������
				        p->state = CMD_LOGIC_TURNED_ON;	//�������
				    }
				    else {
				        udControl.fault_start = 1;  //���� �������� �������� ��� ����������������� ����, �������� � ������
				    }
				}
			}
		}

		//���������� ������� �� ����������� ���������� � ����� ������ ���� ������������� ��������� � ����
		sm_ctrl.state = CTRL_STOP;
		//������ ���������� ������� ������� ����������
		cmd.bit.stop = 0;
		cmd.bit.start = 0;
		break;
	}

	case CMD_LOGIC_TURNED_ON: {	//��������� - ������
		if (p->E == 1) {
			/*ENTRY*/
			drv_status.bit.ready = 1;
			drv_status.bit.running = 1;
			sm_ctrl.state = CTRL_RUN;//�������
		}
		//���� ������ ��� ������� ���� �� ��������� ����
		if ((sm_prot.state == PROT_FAIL) || (cmd.bit.stop == 1)
				|| (sm_ctrl.state == CTRL_STOP)){
			p->state = CMD_LOGIC_TURNED_OFF;
		}

		//������ ���������� ������� ����������
		cmd.bit.stop = 0;
		cmd.bit.start = 0;
		break;
	}

    default: {      //�� ������ ������ ������ ����� ��-��������� "��������"
        p->state = CMD_LOGIC_TURNED_OFF;
        break;
    }

	} // ����� switch(p->state)
}

/*@}*/
