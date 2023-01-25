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

 \file      V_Fan.c
 \brief     ������ ������ �����������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/


#include "main.h"


//! \memberof TFanControl
void FanControl_init(TFanControl *p)
{
#if defined (HW_MOTORCONTROLBOARD)
	p->Enabled = 1; //�������� ���� �����������

	//��������� ����� ��� ���������� ������������
	FAN_OFF;
	GPIOB->ALTFUNCCLR = (1 << 4);		//��������� ����. �������
	GPIOB->OUTENSET = (1 << 4);			//�� �����
#endif
}

//! \memberof TFanControl
void FanControl_slow_calc(TFanControl *p) {
	if (p->Enabled){//���� ���� ����������
		//������� ���������� �������
		p->state_shadow = p->state;
		p->state_prev = p->state_shadow;

		switch (p->state_shadow) {


		case FAN_CONTROL_STATE_OFF: //���������� �� ��������, ����������� ��������� ������ T_on
		{
			FAN_OFF;
			p->StateOn = 0;
			if ((p->temperature > p->T_on) || (p->manualOn))
				p->state = FAN_CONTROL_STATE_ON;
			break;
		}

		case FAN_CONTROL_STATE_ON: //��������� �����������, ����������� ������ T_on � ������ T_alarm
		{
			FAN_ON; //�������� ����������
			p->StateOn = 1; //��������� ������

			if (p->temperature > p->T_alarm) //���� ����������� ��������� ��� ������, ��������� � ����� ���������
				p->state = FAN_CONTROL_STATE_OVERHEAT;
			if ((p->temperature < p->T_off) && (!p->manualOn)) //���� ����������� ���������� ���� ��������� ������, ��������� � ������� �����
				p->state = FAN_CONTROL_STATE_OFF;
			break;
		}

		case FAN_CONTROL_STATE_OVERHEAT: //����������� ������ T_alarm, ���������� ��������, ��������� �������������� � ���������
		{
			FAN_ON; //�������� ����������
			p->StateOn = 1; //��������� ������
			drv_status.bit.overheat = 1; //����� �������������� � ���������
			if (p->temperature < p->T_alarm) { //���� ����������� ���������� ���� ��������� ������, ��������� � ������� �����
				drv_status.bit.overheat = 0; //����� �������������� � ���������
				p->state = FAN_CONTROL_STATE_ON;
			}
			break;

		}

		}
	}


}

/*@}*/

