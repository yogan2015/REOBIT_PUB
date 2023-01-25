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

 \file      V_AutoOffset.c
 \brief     ������������ ��� (��. TAutoOffset)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 @{
 */

/** \addtogroup TAutoOffset */
/*@{*/

#include "DSP.h"
#include "v_IQmath.h"
#include "V_adc.h"
#include "V_AutoOffset.h"
#include "V_common.h"

extern TAdcDrv adc;
extern TDrvParams drv_params;

void AutoOffset_init(TAutoOffset *p) {
	p->FilterK = _IQ(0.001);
}

void AutoOffset_calc(TAutoOffset *p) {
	//����������� ��� ����� ���. ����� ������ ����������, ���� ������ ���� ��������.
	//���� ��� �� ���, �� ����������� ������ �������
	p->IA_int = p->IA_int + _IQmpy(p->FilterK, adc.Imeas_a);
	p->IB_int = p->IB_int + _IQmpy(p->FilterK, adc.Imeas_b);
}

void AutoOffset_slow_calc(TAutoOffset *p) {

	long IA_pu;
	long IB_pu;

	if (p->Enabled){//���� ������ ����������� �������� ����� �������
		//������������� �� �.�. ������� � �������� ���
		IA_pu = -p->IA_int / (_IQ16mpy(adc.Imeas_a_gain, drv_params._1_I_nom));
		adc.Imeas_a_offset  = IA_pu >> 1;

		IB_pu = -p->IB_int / (_IQ16mpy(adc.Imeas_b_gain, drv_params._1_I_nom));
		adc.Imeas_b_offset = IB_pu >> 1;

	} else {//������ ��������, �������������� ����������� �������� ��������� ��������
		p->IA_int=-(((long)adc.Imeas_a_offset)<<1)*_IQ16mpy(adc.Imeas_a_gain, drv_params._1_I_nom);
		p->IB_int=-(((long)adc.Imeas_b_offset)<<1)*_IQ16mpy(adc.Imeas_b_gain, drv_params._1_I_nom);
	}

}

/*@}*/

