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

\file      v_common.h
\brief     ���������� �������� ������ ���������� ����������, ������� ��� ������� ���� ��� ����, �����
�������������� �� � ��������� ������
\author    ��� "��� ������". ��� ����� ��������. http://motorcontrol.ru
\version   v 2.0 25/03/2016

\defgroup  v_common ���������� �������� ������ ���������� ����������

@{*/

#ifndef V_COMMON_H
#define V_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif


//!������� ���� ��� �������� ������� ������� ����������
typedef struct
{
	unsigned int ready	:1;
	unsigned int running	:1;
	unsigned int fault		:1;
	unsigned int alarm		:1;
	unsigned int testing	:1;
	unsigned int overheat	:1;
} DRV_STATUS_BIT;

//!��������� ��� ������� ������� ���������� (�������� DRV_STATUS_BIT)
typedef union
{
	int all;
	DRV_STATUS_BIT bit;
}TDrvStatus;


//!������� ���� ����� ����������
typedef struct
{
	unsigned int start		:1;
	unsigned int stop		:1;
	unsigned int trip_reset	:1;
	unsigned int reserved	:5;
} CMD_BIT;

//!��������� ����� ���������� (�������� DRV_STATUS_BIT)
typedef union
{
	unsigned int all;
	CMD_BIT bit;
}TCmd;


//! ���������, ���������� �������� ������� ��� �������
typedef volatile struct
{
	long speed_ref;//!< ������� ��������
	long Iq_ref;//!< ������� ��������������� ��� ��������� ������� ����������
	long i_flux_ref;//!< ������� ���� ��� ��������� �� ���� ������� ���������� (�� ���������)
	long theta_elec;//!< ������� �������� ��������� ������� ����/����������
	long ua_ref, uf_ref; // ������� ���� ����� � ���� �� ��� ���
	long DCMspeed_ref;//!< ������� ��������
} TRefs;

//! ��������� ��� �������� ���������� �������, ���������, ������� ������� ������� ����������
typedef struct
{
	long Rs;//!< ������������� ���� �������
	long Ls;//!< ������������� ���� �������
	int p;//!< ���������� ��� �������
	int I_nom;//!< ����������� (�������) ������ ��� � ������� 16.0
	long _1_I_nom;//!< 1/I_nom
	int U_nom;//!< ����������� (�������) ������ ���������� � ������� 16.0
	long _1_U_nom;//!< 1/U_nom
	int Udc_nom;//!< ����������� (�������) ���������� ��� � ������� 16.0
	long _1_Udc_nom;//!< 1/Udc_nom
	int speed_nom;//!< ����������� (�������) �������� � ������� 16.0
	int freq_nom;//!< ����������� (�������) ������� � ������� 16.0
	int power;//!< ����������� (�������) �������� � ������� 16.0
	int sens_type;//!< ��� ������� ���������
} TDrvParams;


struct SsysSwitches {
	Uint16  recuperation_ena 	:1;	//!< 0 ���������� ����������� ������� ��� ����������
	Uint16  Reboot			 	:1;	//!< 1 ����������� ������������
	Uint16 	AutoOffset		 	:1;	//!< 2 ������������ ���
	Uint16 	use_led				:1;	//!< 3 ������������ ��������� ������ JTAG
	Uint16 	use_led_prev		:1;	//!< 4 ������������ ��������� ������ JTAG
	Uint16					    :11;
};


typedef union {
	struct SsysSwitches bit;
	Uint16 all;
} TSysSwitches;

#ifdef __cplusplus
}
#endif

#endif

/*@}*/

