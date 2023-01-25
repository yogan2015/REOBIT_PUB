/*!
    Copyright 2018 	�� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      startup.c
 \brief     ��������� ����
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 04/09/2018

 */

#include "K1921BK01T.h"
#include "core_cm4.h"

#include "startup.h"
typedef unsigned char Uint8;
typedef unsigned short int Uint16;
typedef unsigned int Uint32;

// ������ �� 148 ���������� �� �������
//void (*g_pfnVectors[148])(void) __attribute__((section (".isr_vector"))) = ISR_VECTORS;
TisrVectors g_pfnVectors __attribute__((section (".isr_vector"))) = ISR_VECTORS;

// ���������� Reset_Handler
// �������� ��������� ��� ������������� ����������,
// ��������� ������ ��, ��� ������ ���� ������
extern int _estack;
extern int _sidata, _sdata, _edata, _sbss, _ebss;
void Reset_Handler (void) {
    // �������� ���������
    Uint32 i;
    Uint8   *from, *to;
    Uint32 size;

    // ������ ��������� ����������� ���� (���� ��������� ����������� �� RAM)
    __set_MSP((Uint32)&_estack);

    // ����������, ������-����-�������
    from = (Uint8*)&_sidata;
    to = (Uint8*)&_sdata;
    size = (Uint32)((Uint8*)&_edata - (Uint8*)&_sdata);

    // ��������
    for (i = 0; i < size; i++) {
        *to = *from;
        to++;
        from++;
    }

    // ������ ���� ����� ��� ZeroBss
    to = (Uint8*)&_sbss;
    size = (Uint32)((Uint8*)&_ebss - (Uint8*)&_sbss);

    // ��������
    for (i = 0; i < size; i++) {
        *to = 0;
        to++;
    }

    // ������ ����� �������� ��������� �����
    SCB->CPACR |= 0b11 << 20;
    SCB->CPACR |= 0b11 << 22;
    __DSB();
    __ISB();



    // � ������ ��������� � main()
    Uint16 mainRet = main();

    // � ���� ����� main ���������� - �������������
    while(1){};
}

/*@}*/
