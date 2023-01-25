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

 \file      V_DIO.c
 \brief     ������ ���������� ������/�������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/



#include "main.h"
#include "filter.h"



// ������ ��������� ���������� �������
volatile Uint16 output_vect = 0;
// ����� �������������� ������� ��������� ���������� �������
volatile Uint16 output_mask = 0;

// ������ ��������� ���������� ������
volatile Uint16 input_vect = 0;
// ����� �������������� ������� ��������� ���������� ������
volatile Uint16 input_mask = 0;
// ����������� ���������� ���������� ������ Kf = 0.001/T�
// (T� - ���������� ������� �������, ���)
volatile _iq inputKf = _IQ(0.03); //����� ������������ ������������ 60�� ��� inputKf=_IQ(0.03) � inputOn = _IQ(0.8) � 1��� ����������;
// ����� �������� ����������� ����� � ��������� OFF (0)
volatile _iq inputOff = _IQ(0.3);
// ����� �������� ����������� ����� � ��������� ON (1)
volatile _iq inputOn = _IQ(0.8);
// ������������� ������ ��������� ���������� ������ (��� ����� ����� ��������������)
Uint16 input = 0;

// ������� ���������� ������
TFilter fIn1 = FILTER_DEFAULTS;
TFilter fIn2 = FILTER_DEFAULTS;
TFilter fIn3 = FILTER_DEFAULTS;


void DIO_Init()
{
#if defined (HW_MOTORCONTROLBOARD)
	//��������� ���������� �����
	NT_GPIOB->ALTFUNCCLR = (1 << 5);							//��������� ����. �������
	NT_GPIOA->ALTFUNCCLR = (1 << 14) | (1 << 15);				//��������� ����. �������
	NT_GPIOB->OUTENCLR = (1 << 5);								//�� ����
	NT_GPIOA->OUTENCLR = (1 << 14) | (1 << 15);					//�� ����

	//��������� ���������� ������
	NT_GPIOB->ALTFUNCCLR = (1 << 6) | (1 << 15) | (1 << 4);		//��������� ����. �������
	NT_GPIOB->OUTENSET = (1 << 6) | (1 << 15) | (1 << 4);		//�� �����
#endif
}


void DIO_slow_calc()
{
	/*
	// �������� ������ ��������� ���������� ������� � ������ ����� ��������������
	Uint16 output = output_vect ^ output_mask;
	// ������� ����������� ����������� �� ������ 1
	if (BIT_IS_SET(output, 0))
		D_OUT1_OFF;
    else
    	D_OUT1_ON;
	// ������� ����������� ����������� �� ������ 2
	if (BIT_IS_SET(output, 1))
		D_OUT2_OFF;
    else
    	D_OUT2_ON;
	// ������� ����������� ����������� �� ������ 3
	if (BIT_IS_SET(output, 2))
		D_OUT3_OFF;
    else
    	D_OUT3_ON;
*/

	// ��������� ������������ ���������� ���������� ������
	fIn1.T = inputKf;
	fIn2.T = inputKf;
	fIn3.T = inputKf;
	// �������� ��������� ����� 1 � ������ ����������
	if (fIn1.output > inputOn) SET_BIT(input, 0);
	if (fIn1.output < inputOff) CLEAR_BIT(input, 0);
	// �������� ��������� ����� 2 � ������ ����������
	if (fIn2.output > inputOn) SET_BIT(input, 1);
	if (fIn2.output < inputOff) CLEAR_BIT(input, 1);
	// �������� ��������� ����� 3 � ������ ����������
	if (fIn3.output > inputOn) SET_BIT(input, 2);
	if (fIn3.output < inputOff) CLEAR_BIT(input, 2);

	input_vect = input ^ input_mask;
}


void DIO_fast_calc()
{
	// ����������� ������ ����������� ����� 1
    fIn1.input = (D_IN1 == 1) ? _IQ(1.0) : 0;
    fIn1.calc(&fIn1);
	// ����������� ������ ����������� ����� 2
    fIn2.input = (D_IN2 == 1) ? _IQ(1.0) : 0;
    fIn2.calc(&fIn2);
	// ����������� ������ ����������� ����� 3
    fIn3.input = (D_IN3 == 1) ? _IQ(1.0) : 0;
    fIn3.calc(&fIn3);
}

/*@}*/

