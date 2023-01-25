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

 \file      V_DIO.h
 \brief     ������ ���������� ������/�������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/


#ifndef V_DIO_H
#define V_DIO_H

#ifdef __cplusplus
extern "C" {
#endif


// ������ ��������� � '1' ��������� ����
// var - ������� ����������
// index - ������ (��������) ���������������� ����
#define SET_BIT(var, index) var |= (1 << index);

// ������ ������ � '0' ��������� ����
// var - ������� ����������
// index - ������ (��������) ���������� ����
#define CLEAR_BIT(var, index) var &= (~(1 << index));

// ������ �������� ���������� ��������� ��������� ����
// var - ������� ����������
// index - ������ (��������) ������������ ����
#define BIT_IS_SET(var, index) ((var & (1 << index)) != 0)

// ������ �������� �������� ��������� ��������� ����
// var - ������� ����������
// index - ������ (��������) ������������ ����
#define BIT_IS_CLEAR(var, index) ((var & (1 << index)) == 0)


// �������� ���������� �����
#ifdef HW_MOTORCONTROLBOARD

#define D_IN1			((GPIOA->DATA & (1 << 14)) == 0)			// ���� 1

#else

#define D_IN1	0

#endif

// �������� ���������� ������
#ifdef HW_MOTORCONTROLBOARD
#define D_OUT1_ON		GPIOA->DATAOUTSET = (1 << 15)
#define D_OUT1_OFF		GPIOA->DATAOUTCLR = (1 << 15)
#else
#define D_OUT1_ON
#define D_OUT1_OFF
#endif



// ������ ��������� ���������� �������
extern volatile Uint8 output_vect;

// ������ ��������� ���������� ������
extern volatile Uint8 input_vect;


void DIO_Init();

void DIO_slow_calc();	// �������� � ������� ���������

void DIO_fast_calc();	// �������� � �������� 1��� ��� 10 ���


#ifdef __cplusplus
}
#endif

#endif

/*@}*/
