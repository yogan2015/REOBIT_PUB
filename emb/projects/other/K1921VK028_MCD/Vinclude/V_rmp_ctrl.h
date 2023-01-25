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
 
 \file        V_rmp_ctrl.h
 \brief   �������� ������������� (��. TRMPCtrl)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  V_rmp_ctrl �������� ������������� (��. TRMPCtrl)

 @{
*/

#ifndef V_RMP_CTRL_H
#define V_RMP_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

  /*! \class TRMPCtrl
      \brief �������� �������������
      
      ����� \a TRMPCtrl, ���������� �� ��������� SRMPCtrl, ������������
      ����� �������� ������������� - ������, ������� � �������� ������
      ���������� ���� �����, ���� �� �� ���������� �� ������. ���� ����� ������
      ��� �������� ������� ��������� ��� ��������� ������� �������.*/

//! ��. TRMPCtrl
struct SRMPCtrl{ long  input;//!< ����
                 long  output;//!< �����
                 long Ts;//!< ������� �������������
                 unsigned long  T;//!< ���� ������� (����� � �������� �� ��������� ������ �� ���� �� �������)
                 long step;//!<��������� ����������
                 void  (*calc)(struct SRMPCtrl*); //!< ������� �������, ������ ���������� � �������� � Ts �������������
                 void  (*slow_calc)(struct SRMPCtrl*); //!< ������� ��������� �������������
                 };	            

typedef struct SRMPCtrl TRMPCtrl;

//!������������� ��-���������
#define V_RMP_CTRL_DEFAULTS {0, \
                           	 0, \
                          	_IQ(0.0001), \
                          	_IQ(20), \
                          	0,\
                          	V_RMP_CTRL_calc,\
                          	V_RMP_CTRL_slow_calc,\
}

//! \memberof TRMPCtrl
void V_RMP_CTRL_calc(TRMPCtrl*);
//! \memberof TRMPCtrl
void V_RMP_CTRL_slow_calc(TRMPCtrl*);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/
