/******************************************************************************
 * @file		main.h
 * @brief		������������ ���� ��� �������� ����� �������
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

#ifndef VINCLUDE_MAIN_H_
#define VINCLUDE_MAIN_H_

#define __INT16_TYPE__  signed char
#define __UINT16_TYPE__ unsigned char
#define __INT32_TYPE__  signed int
#define __UINT32_TYPE__ unsigned int

#include <stdint-gcc.h>
#include "DSP.h"
#include "modbus_rtu.h"

#include "niietcm4.h" // ���� ���� �������� niietcm4_conf.h, ������� �������� ��������� ���������

static inline void Init_CLK(void);
static inline void Init_GPIO(void);
static inline void Init_MB(void);

int16 main(void);


#endif /* VINCLUDE_MAIN_H_ */
