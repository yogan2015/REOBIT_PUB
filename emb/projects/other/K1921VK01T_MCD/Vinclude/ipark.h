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

 \file    ipark.h
 \brief   ������ ��������� ������������ �������������� ��������� (��. TIPark)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  IPark ��������� ������������ �������������� (��. TIPark)
 @{
*/

#ifndef IPARK_H
#define IPARK_H

#ifdef __cplusplus
extern "C" {
#endif

  /*! \class TIPark
      \brief ��������� ������������ ��������������
      
      ����� \a TIPark, ���������� �� ��������� SIPark, ������������
      ������� �������, ��������� � ������������� ����, �� ��������� ����
      �������� ang. �������� ����������� � �������� ���� �������� �� ���������
      � ������� TPark.*/

//! ��. TIPark
struct SIPark{  _iq  ds;//!< Output: stationary d-axis stator variable
                _iq  qs;//!< Output: stationary q-axis stator variable
                _iq  ang;//!< Input: rotating angle (pu)
                _iq  de;//!< Input: rotating d-axis stator variable
                _iq  qe;//!< Input: rotating q-axis stator variable
                void  (*calc)(struct SIPark*);	//!< Pointer to calculation function
               };	            

typedef struct SIPark TIPark;

  //! ������������� ��-���������
#define IPARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
              	          ipark_calc }

 //! \memberof TIPark
void ipark_calc(TIPark*);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/

