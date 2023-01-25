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
 
 \file      V_relay_reg.h
 \brief     �������� ���������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 23/01/2016

\defgroup  V_realy_reg

@{*/



#ifndef V_RELAY_REG_H
#define V_RELAY_REG_H

#ifdef __cplusplus
extern "C" {
#endif

  /*! \class TRelayReg
    \brief ������ ��������� ����������

    ����� \a TRelayReg, ���������� �� ��������� SRelayReg, ������������
    ����� �������� ���������.
  
  */

//! ��. TRelayReg
typedef struct SRelayReg{  long  ref; //!< �������
				  long  fdb;//!< �������� �����
				  long  out;//!< �����
		 	 	  void  (*calc)(struct SRelayReg*);//!< Pointer to calculation function
				 }TRelayReg;


//! ������������� ��-���������
#define RELAY_REG_DEFAULTS { 0,0,0, \
		relay_reg_calc}



//! \memberof TRelayReg
void relay_reg_calc(TRelayReg*);



#ifdef __cplusplus
}
#endif

#endif

/*@}*/
