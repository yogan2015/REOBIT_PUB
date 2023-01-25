/******************************************************************************
 * @file		DSP.h
 * @brief		���� ����������� ������������ ������ ��������� � ���������� ��������� ��������
 * @version		v1.0
 * @date		11 ������� 2015
 *
 * @note
 * ��� "��� ������", ��� ����� ��������. ��� ����: http://motorcontrol.ru
 *
 * @par
 * ��� "��� ������" �������������� ��� ����������� ����������� � ����������������
 * �����, � ��� ����� ���������������� ��������.
 *
 * @par
 * ������ ����������� ����������� ���������������� "��� ����", � ��,
 * ��� ������������, ���������� �� ���� ��� �����, ��������� � ��� ��������������.
 * ��� "��� ������" �� ����� ������� ��������������� �� ��������� ������,
 * ��������� � ��� ��������������.
 *
 ******************************************************************************/

#ifndef VINCLUDE_DSP_H_
#define VINCLUDE_DSP_H_

#define __CM4_REV               0x0001	//� K1921VK01T.h ���� ���������� __CM4F_REV, �� � core_cm4.h ����������� ������ __CM4_REV. ���� �� ��������� ��� ����������� ����� � ������ �����, �����, �� ������������ ��� ���������
#define __CHECK_DEVICE_DEFINES


#include <stdint.h>

#include "K1921VK035.h"
#include "core_cm4.h"             /* Cortex-M4 processor and core peripherals */
#include <string.h>	 				//��� memcpy
#include "EPwm_defines.h"

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

#define IRQ_PRIORITY_TZ 1
#define IRQ_PRIORITY_ADC 2
#define IRQ_PRIORITY_CAP 3
#define IRQ_PRIORITY_10K 4
#define IRQ_PRIORITY_CAN 5
#define IRQ_PRIORITY_1K 6
#define IRQ_PRIORITY_EQEP 6

#endif /* VINCLUDE_DSP_H_ */
