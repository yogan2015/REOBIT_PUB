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

 \file      mbod.c
 \brief     ������� �������� MODBUS
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2017

*/

/** \addtogroup MODBUS */
/*@{*/

#include "mbod.h"
#include "main.h"


/* �������� �������
 * ������ ���� � �������:
 * ����� ���� 1 ����, ������� 1 ����, ����� 2 �����, ������/���-�� ���������� 2 �����, ����������� ����� CRC16(LH)
 * ������ �����������, ��������, ���������� COMpump
 *
01 06 07 D0 00 01 48 87  - ��������� ������ (������ � 2000 �������� 1)
01 06 07 D1 00 64 D9 6C - ������ ������� �������� (2001) ������ 100 ��/���
01 06 A8 6C 00 64 68 5C - ������ ������ �� ���������� Udc ������ 100�

01 03 9C 42 00 01 0A 4E - ������ ������� ������� ��������
01 03 9C 76 00 01 4B 80	- ������ ����� ������


� ��������:
mbodHR - ���������� Holding Registers (�� ������ � ������). ��� �������	0x03(�� ������) 0x06(�� ������)
mbodIR - ���������� Input Registers (�� ������). ��� �������	0x04
mbodC - ������� ���������� Coil (��� ������). ��� ������� 0x05(�� ������)
mbodDI - ������� ���������� Discrete Inputs (��� ������). ��� ������� 0x02(�� ������)

������ ����� ������� - ����� ���������� � �������  ModBus.
������ - ����� ���� ��� ������� ���������� � ���������� �����������.
������ - ����� ����������.


*/

volatile MB_Record mbodHR[] = {\
		2000,  0,(long)(&MBVarsConv.Vars.Command),/*����� ����������. 0� ��� - ����, 1� ��� - ����, 2� ��� - ����� ������ */\
		2001,  0,(long)(&MBVarsConv.Vars.speed_ref), /*������� ������� �������� � ��/���*/\
		40002, 0,(long)(&MBVarsConv.Vars.CurSpeed),/* ������� ������� �������� (��/���) */\
		40007, 0,(long)(&MBVarsConv.Vars.CurIs),/*��� ������� ����������� (�)*/\
		40054, 0,(long)(&MBVarsConv.Vars.Main_ErrorCode),/*��� ������ (���������, ���� ������ ���������)*/\
		43116,  0,(long)(&MBVarsConv.Vars.Umax_protect),/*������� ����. ������ ���*/\
        0,0,0	// ����� �������, �� ������� - �� ����� ������������ ������ �������.
};

volatile MB_Record mbodIR[] = {\
                           	0,0,0	// ����� �������, �� ������� - �� ����� ������������ ������ �������.
                           	};

volatile MB_Record mbodC[] =  {\
                           	0,0,0	// ����� �������, �� ������� - �� ����� ������������ ������ �������.
                            };



volatile MB_Record mbodDI[] =  {0,0,0	// ����� �������, �� ������� - �� ����� ������������ ������ �������.
                          	};

/*@}*/
