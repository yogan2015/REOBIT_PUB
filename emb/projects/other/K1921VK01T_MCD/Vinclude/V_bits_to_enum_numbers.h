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
 
 \file      V_bits_to_enum_numbers.h
 \brief     ������ "��������" ������� ���������� (��. TBitsToEnumNums)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  V_bits_to_enum_numbers ������ "��������" ������� ���������� (��. TBitsToEnumNums)
 @{
*/

#ifndef V_BITS_TO_ENUM_NUMS_H
#define V_BITS_TO_ENUM_NUMS_H

#ifdef __cplusplus
extern "C"
{
#endif

//!���������� ����������������� ���� ��� ������� ����������
#define NUM_OF_W_PTRS 2

  /*! \class TBitsToEnumNums
        \brief ������ "��������" ������� ����������

        ����� \a TBitsToEnumNums, ���������� �� ��������� SBitsToEnumNums, �����������
        ������� ���������� � ����� (��������������� �������  ����� ������� ���������),
        ���������� � �������� ����������. �������� � ����� ������� ���� ������������� 1.
        ������ 0 ���� ������� ���� � ����������� ������ �� �����������. �������������� ���
        "�������������" ����� ���� ������ � �������������� � ����� ������ �� ��. */

//! ��. TBitsToEnumNums
  struct SBitsToEnumNums
  {
    Uint16 out_refresh_devisor;//!< ��������, �������� ���� ��������
    Uint16 counter;//!<������� �������� ��������
    Uint16 num_of_words;//!<���-�� ������� ����������
    Uint16 last_word;//!<������� �����
    Uint16 last_bit;//!<������� ���
    Uint16 *w_ptrs[NUM_OF_W_PTRS]; //!<��������� �� ������� ���������� (���������)
    Uint16 output;//!<����� ������ (����������� �����)
    void (*calc)(volatile struct SBitsToEnumNums*);
  };

  typedef volatile struct SBitsToEnumNums TBitsToEnumNums;


//!������������� �� ���������
#define BITS_TO_ENUM_NUMS_DEFAULTS {1000,0,4,0,0,{0},0,\
    BitsToEnumNums,\
  }
//! \memberof TBitsToEnumNums
  void BitsToEnumNums(TBitsToEnumNums*);


#ifdef __cplusplus
}
#endif

#endif


/*@}*/

