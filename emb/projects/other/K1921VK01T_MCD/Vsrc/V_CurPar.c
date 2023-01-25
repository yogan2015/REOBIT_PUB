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
 
 \file      V_CurPar.c
 \brief     ������ ����������� ������� ����������  (��. TCurPar)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 */

/** \addtogroup V_CurPar */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif
#include "DSP.h"     // Device Headerfile and Examples Include File
#include "V_IQmath.h"          // ���������� IQmath
#include "V_CurPar.h"    // ������������ ����
#include "main.h"
#ifdef __cplusplus
}
#endif

//! ������������� ������

//! ���, ����� ���������...
//! \memberof TCurPar
void CurPar_init(TCurPar* p) {
	//�������
	p->fPower.T = _IQ(0.001);  //������ �������� ��� ������ �� �����

}

//!������ �������� �� ������ ���

//!������ ���������� � ���������� ������� ���������, ����������� � �������
//!��� ������� ������������ ����������� ���������� ��� UalphaRef, UbetaRef,
//!���������� ���� ��� Ialpha, Ibeta. ��� ������ �� ���� ���������� ���������� �� ���,
//!���������� ���������� �������� ����������� � ����������� ��������� �� ������ ���,
//!� ����� ���������� ���������� ���������� �������� ����������� ����������� ������ ������� �������.
//! \memberof TCurPar
void CurPar_PowerCalcUf(TCurPar* p) {
	p->Ualpha = pwm.UalphaRef;  //���������� �������� ��� �����
	p->Ubeta = pwm.UbetaRef; //���������� �������� ��� ����

	//���������� �������� �� ���� ����� � ���� �������� �� ���� �������
	p->fPower.input = _IQmpy(p->PowerK,
			_IQmpy(p->Ualpha,p->Ialpha)+_IQmpy(p->Ubeta,p->Ibeta));

	//������ �������
	p->fPower.calc(&p->fPower);
	//��������� ������ ������� - ������� �������� ��������.
	p->power = p->fPower.output;
}

//!������ ������� ���������� �������

//! \memberof TCurPar
void CurPar_calc(TCurPar* p) {

	CurPar_PowerCalcUf(p); //������ ��������
}

//! \memberof TCurPar
//������ ����������� ��������������� ����������� ��������
//��� ���������� ��������� ����� �������� �������� � ������� �������� drv_params.power
void CurPar_slow_calc(TCurPar* p) {
	float PowerMaxReal;
	float PowerMaxScale;
	PowerMaxReal = (float) drv_params.I_nom * drv_params.U_nom;
	PowerMaxScale = _IQ6toF(drv_params.power);
	p->PowerK = _IQmpy(_IQ(PowerMaxReal / PowerMaxScale), _IQ(3.0/2));//����� 3/2 ����� ��� �������������� �������� �� 2� ������� ������������� � 3� �������
}

/*@}*/

