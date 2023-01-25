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

 \file      V_BrakeResistor.c
 \brief     ������ ���������� ������� ����������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/

#include <DSP.h>
#include "main.h"

#if defined (HW_MOTORCONTROLBOARD)
#define BR_CONTROL_OFF GPIOB->DATAOUTCLR = (1 << 7);
#define BR_CONTROL_ON GPIOB->DATAOUTSET = (1 << 7);
#else
#define BR_CONTROL_OFF	// �������� ��� ����������
#define BR_CONTROL_ON	// �������� ��� ���������
#endif

void BrakeResistor_Init (TbrakeResistor *p) {
	p->state = BRAKE_R_STATE_OFF;

	// ��������� �����
	BR_CONTROL_OFF;
	GPIOB->ALTFUNCCLR = (1 << 7);
	GPIOB->OUTENSET = (1 << 7);

}

void BrakeResistor_fastCalc (TbrakeResistor *p) {
	// ������ �� ���������� ������� (������ ���� ����������)
	if (p->bottomLevel >= p->upperLevel)
		p->bottomLevel = _IQmpy(p->upperLevel, _IQ(0.95));

	if (!p->enabled) {
		p->state = BRAKE_R_STATE_OFF;
		BR_CONTROL_OFF;
		return;
	}
	// ���� ��������� ���������� ��������� ����������, ��
	// ���� ���������� ������ ����� ������� - ��������, � ���� ������ ������ - ���������

	if (adc.Udc_meas > p->upperLevel){
		p->state = BRAKE_R_STATE_ON;
		BR_CONTROL_ON;

	} else if (adc.Udc_meas < p->bottomLevel) {
		p->state = BRAKE_R_STATE_OFF;
		BR_CONTROL_OFF;
	}





}

/*@}*/
