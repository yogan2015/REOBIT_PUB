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
 
 \file      V_excitation.c
 \brief     ������ �����������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 28/03/2017

 \addtogroup V_excitation
 @{*/

#include "V_IQmath.h"         // Include header for IQmath library
#include "V_excitation.h"
#include "main.h"
//! ������� ������� ��������� ����������

//! \memberof TRelayReg
void excitation_calc(Texcitation *v)
{
	//������� ����������� ��
	//� ������ ��� ������ 3 ������. ������� ��� ������ �� � �������� ����������� ��������� ���������� ���.
	volatile int32 GammaF;
	if (v->ref < _IQ(0))
		v->ref = _IQ(0);

	if (v->ref > _IQ(1))
		v->ref = _IQ(1);

	GammaF = v->ref >> 8; // (IQ16) ��������� ��, ��� ����, � iq16.
	GammaF = _IQ16mpy(GammaF, _IQ16(pwm.k_pwm)); // (IQ16) ��������� ���������� � �������� ��� �������� � ������� ���������.
	GammaF = pwm.k_pwm - (GammaF >> 16); // (IQ0) �������� ����� ����� � ������� ���������.

#if defined(HW_MCB3_SIMULATOR)
	model.cmpr3 = (Uint16) GammaF;
#endif
}

/*@}*/
