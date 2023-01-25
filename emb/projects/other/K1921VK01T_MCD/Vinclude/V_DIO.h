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
#define D_IN1			((NT_GPIOB->DATA & (1 << 5)) == 0)			//B5	�����
#define D_IN2			((NT_GPIOA->DATA & (1 << 14)) == 0)			//A14	����
#define D_IN3			((NT_GPIOA->DATA & (1 << 15)) == 0)			//A15	����� ������
#else
#define D_IN1	0
#define D_IN2	0
#define D_IN3	0
#endif

// �������� ���������� ������
#ifdef HW_MOTORCONTROLBOARD
#define D_OUT1_ON		NT_GPIOB->MASKLOWBYTE_bit[64].MASKLB = 64			//NT_GPIOB->DATA |= (1 << 6)
#define D_OUT1_OFF		NT_GPIOB->MASKLOWBYTE_bit[64].MASKLB = 0			//NT_GPIOB->DATA &= ~(1 << 6)
#define D_OUT2_ON		NT_GPIOB->MASKHIGHBYTE_bit[128].MASKHB = 128		//NT_GPIOB->DATA |= (1 << 15)
#define D_OUT2_OFF		NT_GPIOB->MASKHIGHBYTE_bit[128].MASKHB = 0			//NT_GPIOB->DATA &= ~(1 << 15)
#define D_OUT3_ON		NT_GPIOB->MASKLOWBYTE_bit[16].MASKLB = 16			//NT_GPIOB->DATA |= (1 << 4)
#define D_OUT3_OFF		NT_GPIOB->MASKLOWBYTE_bit[16].MASKLB = 0			//NT_GPIOB->DATA &= ~(1 << 4)
#else
#define D_OUT1_ON
#define D_OUT1_OFF
#define D_OUT2_ON
#define D_OUT2_OFF
#define D_OUT3_ON
#define D_OUT3_OFF
#endif



// ������ ��������� ���������� �������
extern volatile Uint16 output_vect;
// ����� �������������� ������� ��������� ���������� �������
extern volatile Uint16 output_mask;

// ������ ��������� ���������� ������
extern volatile Uint16 input_vect;
// ����� �������������� ������� ��������� ���������� ������
extern volatile Uint16 input_mask;

// ����������� ���������� ���������� ������ Kf = 0.0001/T�
// (T� - ���������� ������� �������, ���)
extern volatile _iq inputKf;
#define in_Kf inputKf	// ��������� ��� ��� ��������� ���������� � ������� CANopen

// ����� �������� ����������� ����� � ��������� OFF (0)
extern volatile _iq inputOff;
// ����� �������� ����������� ����� � ��������� ON (1)
extern volatile _iq inputOn;


void DIO_Init();

void DIO_slow_calc();	// �������� � ������� ���������

void DIO_fast_calc();	// �������� � �������� 1��� ��� 10 ���


#ifdef __cplusplus
}
#endif

#endif

/*@}*/
