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
 
 \file      V_bits_to_enum_numbers.c
 \brief     ������ "��������" ������� ���������� (��. TBitsToEnumNums)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 */

/** \addtogroup V_bits_to_enum_numbers */
/*@{*/

#include "DSP.h"
#include "V_bits_to_enum_numbers.h"

//! ����������� ������� ���������� � �����

//!��������� � �������� ��� ������ ����� ��� ��������������,
//!��� �������������� ������������ ��� ������ � ������ ������ �
//!���������� ����� ���� ��� � "��������" ���� ������� � ������������
//!��������, ���� ���������� ��������� ���. ����� �������������� ����� ��� 
//!�������� ���������� ������/�������������� �������������.
//!�������� ���������� � ������������ �������������� (��������, 10���).
//! \memberof TBitsToEnumNums
void BitsToEnumNums(TBitsToEnumNums* p) {
	Uint16 i;

	p->counter++;
	if (p->counter < p->out_refresh_devisor)
		return;
	p->counter = 0;

	//�������� ������������ ������
	if ((p->num_of_words > NUM_OF_W_PTRS) || (p->num_of_words == 0))
		return;

	//���������� ���� � ������� �����������
	for (i = 0; i < (16 * p->num_of_words); i++) {
		p->last_bit++;
		if (p->last_bit > 15) {
			p->last_bit = 0;
			p->last_word++;
			if (p->last_word > (p->num_of_words - 1))
				p->last_word = 0;
		}
		//������ �������� ����
		if ((*(p->w_ptrs[p->last_word])) & (0x1 << p->last_bit)) {
			//����� ������� ������� ���������
			p->output = p->last_word * 16 + p->last_bit + 1;
			return;
		}
	}

	//���� ����� �� ���� ������ ��� �������, ������ ������ 0
	p->output = 0;
}

/*@}*/

