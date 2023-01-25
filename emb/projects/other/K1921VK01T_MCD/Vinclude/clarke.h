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
 
 \file        clarke.h
 \brief   ������ ������ �������������� (��. TClarke)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  clarke ������ ������ �������������� (��. Tclarke)

 @{
*/

#ifndef CLARKE_H
#define CLARKE_H

#ifdef __cplusplus
extern "C" {
#endif

    
/*! \class TClarke
      \brief ������ ��������������
      
      ����� \a TClarke, ���������� �� ��������� SClarke, ������������
      �������������� �������� �� ��������� ������� ��������� � ����������.
      ���, ��� �������������� ����� ��� ������� ���������� as � bs ����������
      ��������� �������� ����� ��� A � B, ������� ������� calc, ����� ���� � ��������
      ���������� ds, qs ����� �������� ������� ���� �� ������� ���������������� ����
      �����, ����� (� ������������ ���������� ��� d,q).*/

//! ��. TClarke
struct SClarke{  long  as;  //!< Input: phase-a stator variable
                long  bs;//!< Input: phase-b stator variable 
                long  ds;	//!< Output: stationary d-axis stator variable 
                long  qs;	//!< Output: stationary q-axis stator variable 
                void  (*calc)(struct SClarke*);	//!< Pointer to calculation function
               };	            

typedef struct SClarke TClarke;

  //! ������������� ��-���������
#define CLARKE_DEFAULTS { 0, \
                          0, \
                          0, \
                          0, \
              	          clarke_calc }

 //! \memberof TClarke
void clarke_calc(TClarke*);

#ifdef __cplusplus
}
#endif


#endif

/*@}*/
