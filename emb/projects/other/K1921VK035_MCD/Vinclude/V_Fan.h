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

 \file      V_Fan.h
 \brief     ������ ������ �����������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/


#ifndef V_FAN_H
#define V_FAN_H


//! ���������� ��������
#define FAN_CONTROL_STATE_OFF 		0
//! ���������� �������
#define FAN_CONTROL_STATE_ON 		1
//! ��������� ���������
#define FAN_CONTROL_STATE_OVERHEAT 	2

/* ��������� � ���������� ����������� */
#if defined (HW_MOTORCONTROLBOARD)
#define FAN_ON			GPIOB->MASKLB[16].MASKLB = 16			//NT_GPIOA->DATA |= (1 << 13)
#define FAN_OFF			GPIOB->MASKLB[16].MASKLB = 0			//NT_GPIOA->DATA &= ~(1 << 13)
#endif

#if !defined (HW_MOTORCONTROLBOARD)
/* ������� ��� ������ ������������ */
#define FAN_ON
#define FAN_OFF
#endif


struct SFanControl{
	Uint16 Enabled;
	Uint16 manualOn;	// �������������� ���������

	int state; //!<���������
	int state_shadow;//!< ��������� �������
	int state_prev;//!<��������� ����������
	int StateOn;//!<�������� ���������: �������/�� �������

	long T_on;//!<����������� ���������
	long T_off;//!<����������� ����������
	long T_alarm;//!����������� ������ ��������������
	long temperature;	//! �����������, �� ������� �������������� ��������

	void   (*init)(volatile struct SFanControl*);
	void   (*slow_calc)(volatile struct SFanControl*);
};

typedef volatile struct SFanControl TFanControl;



//! \memberof TFanControl
void FanControl_init(TFanControl*);
//! \memberof TFanControl
void FanControl_slow_calc(TFanControl*);	//������ � ������� ������


#define FAN_CONTROL_DEFAULTS {0,0,\
						FAN_CONTROL_STATE_OFF,FAN_CONTROL_STATE_OFF,FAN_CONTROL_STATE_OFF,0,\
						_IQ(2.5),_IQ(2), _IQ(4), _IQ(0),\
						FanControl_init,\
						FanControl_slow_calc}



#endif

/*@}*/
