/*!
    Copyright 2017  �� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_TMU.c
 \brief     ������ ����� ������������������ �������������� (��. TTMU, TTMUPark, TTMUIPark)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 24/06/2019

 \addtogroup V_TMU
 @{*/


#include "main.h"

//������� �������������� �����. ��������� �� ���� ��������� � ������������� �������� � IQ24. �� �������� ��������� ���������� ������ ����� �������� IQ24.
void TMU_park_calc_IQ24PU (TTMUPark *p) {
    TMU->PHIN = _IQ24mpy(((p->ang & 0x00FFFFFF) << 4), _IQ24(2.0*_PI));     //������������ ���� �������� � IQ24, ����������� � IQ28, � ����� � ���������� ���� � ��������, ��� ������� ���� ���� TMU

    TMU->YIN = (p->ds >> 3);                //����������� �������������� ����� � ������� IQ24 � ������������ �������� � ������� IQ28
    TMU->XIN = (p->qs >> 3);                //�� ��

    TMU->CMD = (3 << TMU_CMD_FUNC_Pos) |    // ��������� ������
               (0 << TMU_CMD_ARGT_Pos) |    // ��������� � IQ28
               (1 << TMU_CMD_START_Pos);    // �������

    //����, ���� ���� TMU �������� ����������
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    p->de = ((int32)TMU->YOUT << 3);        //����������� �������� ������� �� ����������� ��������� ������� ��� ����� TMU � IQ28 �� ����������� ���������� ����� � IQ24
    p->qe = ((int32)TMU->XOUT << 3);        //�� ��
}


//������� ��������� �������������� �����. ��������� �� ���� ��������� � ������������� �������� � IQ24. �� �������� ��������� ���������� ������ ����� �������� IQ24.
void TMU_ipark_calc_IQ24PU (TTMUIPark *p) {
    TMU->PHIN = _IQ24mpy(((p->ang & 0x00FFFFFF) << 4), _IQ24(2.0*_PI));     //������������ ���� �������� � IQ24, ����������� � IQ28, � ����� � ���������� ���� � ��������, ��� ������� ���� ���� TMU

    TMU->YIN = (p->qe >> 3);                //����������� �������������� ����� � ������� IQ24 � ������������ �������� � ������� IQ28
    TMU->XIN = (p->de >> 3);                //�� ��

    TMU->CMD = (3 << TMU_CMD_FUNC_Pos) |    // ��������� ������
               (0 << TMU_CMD_ARGT_Pos) |    // ��������� � IQ28
               (1 << TMU_CMD_START_Pos);    // �������

    //����, ���� ���� TMU �������� ����������
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    p->qs = ((int32)TMU->YOUT << 3);        //����������� �������� ������� �� ����������� ��������� ������� ��� ����� TMU � IQ28 �� ����������� ���������� ����� � IQ24
    p->ds = ((int32)TMU->XOUT << 3);        //�� ��
}


//������� ������. ��������� �� ���� ���� � ������������� �������� � IQ24. �� �������� ���� ��������� ������ ����� �������� IQ24.
_iq TMU_sin_IQ24PU (_iq angle) {
    TMU->PHIN = _IQ24mpy(angle & 0x00FFFFFF, _IQ24(2.0*_PI));         //������������ ���� �������� � IQ24 � ����������� � ���������� ���� � ��������, ��� ������� ���� ���� TMU

    TMU->CMD =  (0 << TMU_CMD_FUNC_Pos) |   // ��������� �����/�������
                (4 << TMU_CMD_ARGT_Pos) |   // ��������� � IQ24
                (1 << TMU_CMD_START_Pos);   // �������

    //����, ���� ���� TMU �������� ����������
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    return (TMU->YOUT);
}


//������� ��������. ��������� �� ���� ���� � ������������� �������� � IQ24. �� �������� ���� ��������� ������ ����� �������� IQ24.
_iq TMU_cos_IQ24PU (_iq angle) {
    TMU->PHIN = _IQ24mpy(angle & 0x00FFFFFF, _IQ24(2.0*_PI));         //������������ ���� �������� � IQ24 � ����������� � ���������� ���� � ��������, ��� ������� ���� ���� TMU

    TMU->CMD =  (0 << TMU_CMD_FUNC_Pos) |   // ��������� �����/�������
                (4 << TMU_CMD_ARGT_Pos) |   // ��������� � IQ24
                (1 << TMU_CMD_START_Pos);   // �������

    //����, ���� ���� TMU �������� ����������
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    return (TMU->XOUT);
}


//������� �����������. ��������� �� ���� ��������� � ������������� �������� � IQ24. �� �������� ��������� ���������� ������ ����� �������� IQ24.
_iq TMU_atan2_IQ24PU (_iq inY, _iq inX) {
    TMU->XIN = (inX >> 3);                      //����������� �������������� ����� � ������� IQ24 � ������������ �������� � ������� IQ28
    TMU->YIN = (inY >> 3);                      //�� ��

    TMU->CMD =  (1 << TMU_CMD_FUNC_Pos) |       // ������� �� ������������� ������� ��������� � ��������
                (0 << TMU_CMD_ARGT_Pos) |       // ��������� � IQ28
                (1 << TMU_CMD_START_Pos);       // �������

    //����, ���� ���� TMU �������� ����������
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    return (_IQ24mpy((((int32)TMU->PHOUT) >> 4), _IQ24(0.15915494309189533576)));      //����������� ���� �� IQ28 � IQ24 � ����� ����� �� 2�� ��� �������������� � ������������� ����
}


//������� �������������� ��������� �� ������������� ������� � ��������. ��������� �� ���� ��������� � ������������� �������� � IQ24. �� �������� ��������� ���������� ������ ����� �������� IQ24.
void TMU_cartesianToPolar_calc_IQ24PU (TTMUCarToPol *p) {
    TMU->XIN = (p->x >> 3);                      //����������� �������������� ����� � ������� IQ24 � ������������ �������� � ������� IQ28
    TMU->YIN = (p->y >> 3);                      //�� ��

    TMU->CMD = (1 << TMU_CMD_FUNC_Pos) |    // ������� �� ������������� ������� ��������� � ��������
               (0 << TMU_CMD_ARGT_Pos) |    // ��������� � IQ28
               (1 << TMU_CMD_START_Pos);    // �������

    //����, ���� ���� TMU �������� ����������
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    p->r = ((int32) TMU->XOUT << 3);                                                  //����������� �������� ������� �� ����������� ��������� ������� ��� ����� TMU � IQ28 �� ����������� ���������� ����� � IQ24
    p->phi = _IQ24mpy((((int32)TMU->PHOUT) >> 4), _IQ24(0.15915494309189533576));     //����������� ���� �� IQ28 � IQ24 � ����� ����� �� 2�� ��� �������������� � ������������� ����
}


//������� �������������� ��������� �� �������� ������� � �������������. ��������� �� ���� ��������� � ������������� �������� � IQ24. �� �������� ��������� ���������� ������ ����� �������� IQ24.
void TMU_polarToCartesian_calc_IQ24PU (TTMUPolToCar *p) {
    TMU->XIN = (p->r >> 3);                                                     //����������� �������������� ����� � ������� IQ24 � ������������ �������� � ������� IQ28
    TMU->PHIN = _IQ24mpy(((p->phi & 0x00FFFFFF) << 4), _IQ24(2.0*_PI));         //������������ ���� �������� � IQ24, ����������� � IQ28, � ����� � ���������� ���� � ��������, ��� ������� ���� ���� TMU

    TMU->CMD = (2 << TMU_CMD_FUNC_Pos) |    // ������� �� �������� ������� ��������� � �������������
               (0 << TMU_CMD_ARGT_Pos) |    // ��������� � IQ28
               (1 << TMU_CMD_START_Pos);    // �������

    //����, ���� ���� TMU �������� ����������
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    p->x = ((int32) TMU->XOUT << 3) ;      //����������� �������� ������� �� ����������� ��������� ������� ��� ����� TMU � IQ28 �� ����������� ���������� ����� � IQ24
    p->y = ((int32) TMU->YOUT << 3);       //�� ��
}

/*@}*/
