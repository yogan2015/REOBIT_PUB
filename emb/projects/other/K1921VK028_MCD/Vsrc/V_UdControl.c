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

 \file      V_UdControl.c
 \brief     ������ �������� ������ ���
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/


#include "main.h"


//!�������������.

//!������������� ����� �����������, ����������� ����� ������ �� �����.

//! \memberof TUdControl
void UdControl_init(TUdControl *p) {
    p->Enabled = 1; //�������� ���� ������ ���
	UD_CONTROL_OFF; //������� ��������
	p->state = UD_CONTROL_STATE_OFF; //� ��� � ��������� "���������"
	p->StateOn = 0;
}

//!������.

//!���������� �������, ����������� ����� ������. �������� ���� � �����-������
//!������� ���������� (�������� 10���). �����, ����� �������� � � 1���, ��
//!�� �����������. ����� ��� ���������: ���������, �������� ������ � ��������.
//!��� ������������ ���������� �� ������ ����������� ���������� �� ���.

//! \memberof TUdControl
void UdControl_calc(TUdControl *p) {
	if (p->Enabled){//���� ���� ���� ���������� ������� ���
		p->fUdc.input = adc.Udc_meas; //�� ���� ������� - ���������� � ���
		p->fUdc.calc(&(p->fUdc));
		//������� ���������� �������
		p->state_shadow = p->state;
		if (p->state_prev != p->state_shadow)
			p->E = 1; //������ ���������
		else
			p->E = 0;
		p->state_prev = p->state_shadow;

		switch (p->state_shadow) {
		case UD_CONTROL_STATE_OFF: //���� ��������
		{
			UD_CONTROL_OFF; //��������� ����
			p->StateOn = 0; //��������� ���������
			if (adc.Udc_meas > p->U_on) //���������� ����� ������
				p->state = UD_CONTROL_STATE_WAIT; //��������� � ��������
			break;
		}

		case UD_CONTROL_STATE_WAIT: //���� ��������, ��������� ��������
		{
			if (p->E == 1) //������ ���������
					{
				p->StateCounter = 0;
			}
			p->StateCounter += global_time.relative_time1.delta_millisecond;
			UD_CONTROL_OFF; //��������� ����
			p->StateOn = 0; //��������� ���������
			if (adc.Udc_meas < p->U_off) //������ ����� ��������, �� ���������� ���������...
				p->state = UD_CONTROL_STATE_OFF;

			if (global_time.relative_time1.delta_millisecond) { //���� ����� ��� ������������
				//����������� �� ������������
				p->deriv_time_ZPT = (labs(p->fUdc.output - p->fUdc_output_prev))<<11; //�������� �������� ����������� ��� ��������� ������ ����� 1
				p->fUdc_output_prev = p->fUdc.output;
			}
			//������� ��������� � �����������
			if ((p->StateCounter >= p->Timeout_on) && (p->deriv_time_ZPT < p->deriv_const) && (adc.Udc_meas > p->U_off)) { //� ����������� ������ ��������� ������
				p->state = UD_CONTROL_STATE_ON;
				p->StateCounter = 0;
			}
			break;
		}

		case UD_CONTROL_STATE_ON: {
			if ((adc.Udc_meas < p->U_off) && (drv_status.bit.running == 0)) //��������-��������, � ��� ���������� ���������... ���� ����� ���������� ��������� �� ����� ������, �� ��������� �� ����
				p->state = UD_CONTROL_STATE_OFF;
			UD_CONTROL_ON; //������� ����
			p->StateOn = 1; //��������� ��������
			break;

		}

		}
	}


}

/*@}*/

