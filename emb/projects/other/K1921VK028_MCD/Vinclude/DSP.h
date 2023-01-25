/******************************************************************************
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

 * @file		DSP.h
 * @brief		���� ����������� ������������ ������ ��������� � ���������� ��������� ��������
 * @author    	��� "��� ������". http://motorcontrol.ru
 * @version		v1.0
 * @date		11 ������� 2015

 ******************************************************************************/

#ifndef VINCLUDE_DSP_H_
#define VINCLUDE_DSP_H_
#ifdef __cplusplus
extern "C" {
#endif

// ����� ������� ������. ������ �� �������� ��� ��������� ������������
//#define QUARTZ_10MHZ
#define QUARTZ_12MHZ

//������� ������������ �����
#define CORE_CLK 200000000


#define GPIO_PIN_0		0x0001
#define GPIO_PIN_1		0x0002
#define GPIO_PIN_2		0x0004
#define GPIO_PIN_3		0x0008
#define GPIO_PIN_4		0x0010
#define GPIO_PIN_5		0x0020
#define GPIO_PIN_6		0x0040
#define GPIO_PIN_7		0x0080
#define GPIO_PIN_8		0x0100
#define GPIO_PIN_9		0x0200
#define GPIO_PIN_10		0x0400
#define GPIO_PIN_11		0x0800
#define GPIO_PIN_12		0x1000
#define GPIO_PIN_13		0x2000
#define GPIO_PIN_14		0x4000
#define GPIO_PIN_15		0x8000

#define __CM4_REV               0x0001	//� K1921VK01T.h ���� ���������� __CM4F_REV, �� � core_cm4.h ����������� ������ __CM4_REV. ���� �� ��������� ��� ����������� ����� � ������ �����, �����, �� ������������ ��� ���������
#define __CHECK_DEVICE_DEFINES


#include <stdint.h>

#include "K1921VK028.h"
#include "core_cm4.h"             /* Cortex-M4 processor and core peripherals */
#include "EPwm_defines.h"	//���� ���������� ��������� �������� ��� ������ � ��� ��������
void gpioPeripheralInit();

typedef char int8;
typedef unsigned char Uint8;
typedef unsigned short int Uint16;
typedef unsigned int Uint32;
typedef short int int16;
typedef int int32;
typedef unsigned long long Uint64;
typedef long long int64;

//��������� �� ������ ������ fastcode, ��� ����� ������� ��� ����������� �� ����� � ����������.
//���������� � ����� ���������� ������.
extern int __fastcode_ram_start;
extern int __fastcode_ram_end;
extern int __fastcode_flash_start;

extern int __isr_vector_flash_start;
extern int __isr_vector_ram_start;
extern int __isr_vector_ram_end;

//! ������ ����������
#define DINT __disable_irq()
//! ���������� ����������
#define EINT __enable_irq()

//! ��������� ����������� ������ �����, �� ����������� ���������
void propReset(void);

//! ��������� ���������� ������������� �������������� ������� ���������� �����
void K1921VK01T_GPIO_SafeInit();


//���������� ����������
#define IRQ_PRIORITY_TZ 1
#define IRQ_PRIORITY_ADC 2
#define IRQ_PRIORITY_CAP 3
#define IRQ_PRIORITY_EQEP 3
#define IRQ_PRIORITY_10K 4
#define IRQ_PRIORITY_CAN 5
#define IRQ_PRIORITY_1K 6



#ifdef __cplusplus
}
#endif

#endif /* VINCLUDE_DSP_H_ */
