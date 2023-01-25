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

*/

#ifndef V_FIFO_C_
#define V_FIFO_C_

#define BUFFER_SIZE 64

#define FIFO_BUSY				-1		// ���� �����
#define FIFO_NOT_ENOUGH_SPACE	2		// �� ������� ����� ��� ������
#define FIFO_NOT_ENOUGH_DATA	3		// ��� ������� ������, ������� ����� ��������
#define FIFO_OK					0		// �� ��


struct Sfifo;
typedef volatile struct Sfifo Tfifo;
struct Sfifo {
	Uint16 busy;
	Uint16 size;		// ������ ������ (����)
    Uint16 wp;		// Write pointer
	Uint16 rp; 		// Read pointer
	Uint8 wrapFlag;	// ��������� � 1, ���� wp ������� �� ������� ������;
						// ������������, ���� rp  �������
						// �������� ��������� ��������, ����� ������ �������� �� 100%: rp == wp && wrap == 1
						// ���� ���� ����� ��������� ����: rp == wp && wrap == 0
    Uint8 buff[BUFFER_SIZE];
    int16 (*put)(Tfifo*, Uint16, Uint8*);
    int16 (*get)(Tfifo*, Uint16, Uint8*);
    int16 (*availSpace)(Tfifo*);
    int16 (*filledSpace)(Tfifo*);
    void (*clear)(Tfifo*);
};

int16 Fifo_Put (volatile struct Sfifo*, Uint16, Uint8*);
int16 Fifo_Get (volatile struct Sfifo*, Uint16, Uint8*);
int16 getFill (Tfifo*);
int16 getFreeSpace (Tfifo*);
void Fifo_Clear (Tfifo*);

#define FIFO_DEFAULTS {.size = BUFFER_SIZE,\
					   .put = Fifo_Put,\
					   .get = Fifo_Get,\
					   .availSpace = getFreeSpace,\
					   .filledSpace = getFill,\
					   .clear = Fifo_Clear}

extern Tfifo fifosha;

extern Tfifo usbRxBuf;
extern Tfifo usbTxBuf;
#endif /* V_FIFO_C_ */
