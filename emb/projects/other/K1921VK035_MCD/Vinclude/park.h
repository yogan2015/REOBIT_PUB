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
 
 \file    park.h
 \brief   ������ ������������ �������������� ��������� (��. TPark)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  Park ������������ �������������� (��. TPark)
 @{
*/
#ifndef PARK_H
#define PARK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "V_IQmath.h"
  
  /*! \class TPark
      \brief ������������ ��������������
      
      ����� \a TPark, ���������� �� ��������� SPark, ������������
      ������� ������� (ds,qs), ��������� � ������������� ����, �� ��������� ����
      �������� ang. �������� ���������� ������ ����������� � ���������� de,qe. */

//! ��. TPark
struct SPark{  _iq  ds;  //!<  Input: stationary d-axis stator variable
              _iq  qs;	//!<  Input: stationary q-axis stator variable
              _iq  ang;	//!<  Input: rotating angle (pu)
              _iq  de;	//!<  Output: rotating d-axis stator variable
              _iq  qe;	//!<  Output: rotating q-axis stator variable
              void  (*calc)(struct SPark*);//!<  Pointer to calculation function
             };	            

typedef struct SPark TPark;

//! ������������� ��-���������
#define PARK_DEFAULTS {  0, \
                          0, \
                          0, \
                          0, \
                          0, \
              			  park_calc }

 //! \memberof TPark
void park_calc(TPark*);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/
