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

 \file      V_UdControl.h
 \brief     ������ �������� ������ ���
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/


#ifndef V_UD_CONTROL_H
#define V_UD_CONTROL_H


#include "build.h"


#ifdef __cplusplus
extern "C" {
#endif

//! ��������� ���������
#define UD_CONTROL_STATE_OFF 0
//! ��������� �������� ���������
#define UD_CONTROL_STATE_WAIT 1
//! ��������� ��������
#define UD_CONTROL_STATE_ON 2

#define UD_CONTROL_OFF  GPIOB->DATAOUTCLR = GPIO_PIN_14;
#define UD_CONTROL_ON   GPIOB->DATAOUTSET = GPIO_PIN_14;



/*! \class TUdControl
  \brief ���������� ����� ������ ����� ����������� ����

  ����� \a TUdControl, ���������� �� ��������� SUdControl, ������
  ��� ���������� ���������� �������, ������� �������� ���� ������
  ����� ����������� ����. ����� ���������� ������� ��� ��������:
  �������� ��������, ���������� ���������� ���� �������� ������� �
  ������������� ������ ���������� (����������� ��������� � ����).
*/

//!��. TUdControl
struct SUdControl{
	Uint16 Enabled;
    int fault_start; //!<������� ����� ��� ����������������� ����
	int state; //!<���������
	int state_shadow;//!< ��������� �������
	int state_prev;//!<��������� ����������
	int E;//!<���� ������� ���������
	int StateCounter;//!<������� ������� ���������� � ���������
	long fUdc_output_prev;//!<�������� ���������� ����������
	long U_on;//!<���������� ���������
	long U_off;//!<���������� ����������
	long Timeout_on;//!<������� ��������� � ��.
	long deriv_time_ZPT; //!<����������� �� ���������� �� ������������
	long deriv_const; //!<��������� ������� ��������� �����������
	int StateOn;//!<�������� ���������: �������/�� �������
	TFilter fUdc;//!<������ ���������� �� ���
	Uint16 ExternCheckKey;//!<���� ����-��������
	Uint16 ExternCheckKeyEnabled;//!<���� �� ������������� ����-��������
	void   (*init)(volatile struct SUdControl*);
	void   (*calc)(volatile struct SUdControl*);
};

typedef volatile struct SUdControl TUdControl;



//! \memberof TUdControl
void UdControl_init(TUdControl*);
//! \memberof TUdControl
void UdControl_calc(TUdControl*);


#define UD_CONTROL_DEFAULTS {0,0,UD_CONTROL_STATE_OFF,UD_CONTROL_STATE_OFF,UD_CONTROL_STATE_OFF,\
						0,0,0,\
						_IQ(0.8),_IQ(0.5),3000,0,\
						0,0, FILTER_DEFAULTS,\
						0,0,\
						UdControl_init,\
						UdControl_calc}


#ifdef __cplusplus
}
#endif

#endif


/*@}*/

