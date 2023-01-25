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

 \file      V_fifo.c
 \brief     ��������� ����� ���� FIFO. ��������� ���������� ������ ���� "Uint8"
 �������� ������������ �����.

 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 08/08/2017

 \addtogroup V_fifo
@{
*/

#include "DSP.h"
#include "V_fifo.h"

Tfifo fifosha = FIFO_DEFAULTS;

//! ������� ���������� ����� ��������
//! ����� ����, ���� rp==wp � ��� ���� wp �� ��������� ������ ������ (����
//! ���������, �� rp ���� ���������)
//!  \memberof Tfifo
//!
//!  \param *p ��������� �� ������ FIFO
//!  \return ���������� ��������� (��������� ��� ������) ��������� � ������
int16 getFreeSpace (Tfifo *p){
    if ((p->rp == p->wp) && (p->wrapFlag == 0)) return p->size;
    else return ((p->size - p->wp + p->rp) & (p->size - 1));
}

//! ������� ������ ���� � ������
//! ������ - ���� rp==wp ��� ������ ������� wp ������ ������
//!  \memberof Tfifo
//!
//! \param *p ��������� �� ������ FIFO
//! \return ���������� ���������� (��������� ��� ������) ��������� � ������
int16 getFill (Tfifo *p){
    if ((p->rp == p->wp) && (p->wrapFlag == 1)) return p->size;
    else return ((p->wp - p->rp) & (p->size - 1));
}


//! �������� � ����� fifo len ���� �� ������ data
//!  \memberof Tfifo
//!
//! \param *p ��������� �� ������ FIFO
//! \param len ���������� ������ ��� ������
//! \param *data ��������� �� ������ ������, ������� ����� ��������
//! \return stat ������ ���������� �������� (��/����� �����/��� �����)
int16 Fifo_Put (Tfifo*p, Uint16 len, Uint8* data){
    int i;

    // ���������, ��� ���� �� ����� ������� ������
    if (p->busy == 1) return FIFO_BUSY;
    else p->busy = 1;

    // ��������, ��� ���������� ����� ��� len elemento�
    if (p->availSpace(p) >= len){
    	// ����� � ����� ��������. ���� ����� ������� �� ������� ������ - ������ ���� wrapFlag
        for (i = 0; i < len; i++){
            p->buff[p->wp] = *(data + i);
            p->wp++;
            if (p->wp == p->size) {
                p->wp = 0;
                p->wrapFlag = 1;
            }
        }
        p->busy = 0;
        return FIFO_OK;
    } else {
    	p->busy = 0;
        return FIFO_NOT_ENOUGH_SPACE;
    }
}

//! ����� �� ������ len ����
//!  \memberof Tfifo
//!
//! \param *p ��������� �� ������ FIFO
//! \param len ���������� ������ ��� ������
//! \param *data ��������� �� ������, � ������� ����� ������� ������
//! \return stat ������ ���������� �������� (��/����� �����/��� ������)
int16 Fifo_Get (Tfifo*p, Uint16 len, Uint8* data){
    int i;

    // ���������, ��� ���� �� ����� ������� ������
    if (p->busy == 1) return FIFO_BUSY;
    else p->busy = 1;

    if (p->filledSpace(p) >= len){
        for (i = 0; i < len; i++){
            *(data + i) = p->buff[p->rp];
            p->rp++;
            if (p->rp == p->size) {
                p->rp = 0;
                p->wrapFlag = 0;
            }
        }
        p->busy = 0;
        return FIFO_OK;
    } else {
    	p->busy = 0;
        return FIFO_NOT_ENOUGH_DATA;
    }
}

//! ����� ����. ���������� ������ ������ FIFO �� ���������, �� ���������
//! ������ � ������ ������������
//!  \memberof Tfifo
//!
//! \param *p ��������� �� ������ FIFO
//! \return ���
void Fifo_Clear (Tfifo*p){
	p->wp = 0;
	p->rp = 0;
	p->wrapFlag = 0;
}
/*@}*/
