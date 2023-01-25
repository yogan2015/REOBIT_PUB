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

 \file        filter.h
 \brief  ����������� ����� � IQ ���������� (��. TFilter)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  filter ����������� ������ (��. TFilter)

 @{
*/


#ifndef FILTER_H
#define FILTER_H

#ifdef __cplusplus
extern "C"
{
#endif

  
/*! \class TFilter
      \brief ����������� ����� � IQ ����������

      ����� \a TFilter, ���������� �� ��������� SFilter, ������������ �� ����
      ����������� ����� � �������� ���, � ������ W(p)=1/(Tfiltra*p+1).
      ������ ��� ������������ � �������� ���������� �������, �� ���� ��������
      �������� ����������� ������, � �� ������ ����������� ���������������.*/

//! ��. TFilter
  struct SFilter
  {
    long input;//! ����
    long output;//! �����
    long T; //! T=Ts/Tfiltra ��� - Tfiltra ���������� ������� �������
    void (*calc)(volatile struct SFilter*);//��������� �� ������� �������
  };

  typedef volatile struct SFilter TFilter;

  //! ������������� ��-���������
#define FILTER_DEFAULTS {0,0,_IQ(0.01), \
	 TFilter_Calc}

 //! \memberof TFilter
void TFilter_Calc(TFilter*);

#ifdef __cplusplus
}
#endif


#endif

/*@}*/





