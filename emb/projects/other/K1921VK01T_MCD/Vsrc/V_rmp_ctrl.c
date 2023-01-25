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
 
 \file      v_rmp_ctrl.c
 \brief     �������� ������������� (��. TRMPCtrl)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 */

/** \addtogroup V_rmp_ctrl */
/*@{*/

#ifdef __cplusplus 
extern "C" {
#endif

#include "v_rmp_ctrl.h"
#include "V_IQmath.h"
#include "stdlib.h"
#ifdef __cplusplus 
}
#endif

//! ������� ������� ��������� �������������

//!�������� output � �������� ������ T,
//!���� output �� ��������� input.

//! \memberof TRMPCtrl
void V_RMP_CTRL_calc(TRMPCtrl *p) {

	if ((labs(p->output - p->input) <= p->step) || (p->T==0))	//����� � ������� � �������� �� ���� ��� �� ������ ��������
	{
		p->output = p->input;									//����� ����� �����
	}
	else if (p->output < p->input)								//����� ����� ������ �����?
	{
		p->output += p->step;									//������������ � �������� ������ �����
	}
	else														//�����
	{
		p->output -= p->step;									//��������� � �������� ������ �����
	}

}

//! ��������������� ������� ��������� �������������

//!������������� ���� ������� T � ��� step c ������ ������� 
//!������ �������� ������� Ts (�������������, ������ 10���).

//! \memberof TRMPCtrl
void V_RMP_CTRL_slow_calc(TRMPCtrl *p) {
	p->step = _IQdiv(p->Ts, p->T);//��� ����������� ��
}

/*@}*/

