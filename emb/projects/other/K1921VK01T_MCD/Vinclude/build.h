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

 \file      build.h
 \brief     ���������������� ������������ ����
 �������� ���������� ����������������, ������������ �� ���� �������.
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 3.0 30/05/2017

 @{
*/


//����� ���� ���������� �����

//VectorCARD � ���������� ���������� DRV8301
//#define HW_VECTORCARD_DRV8301_EVM

//VectorCARD � ���������� ���������� DRV8312
//#define HW_VECTORCARD_DRV8312_EVM

//VectorCARD � ������������� �������� ����������
#define HW_VECTORCARD_SIMULATOR

//���������� ����� ����� � ������������� �������� ����������
//#define HW_NIIET_BOARD_SIMULATOR

//���������� ��40.4 ��� ������
//#define HW_VECTOR_MK_40_4

//���������� Motor Control Board
//#define HW_MOTORCONTROLBOARD

//��� UART, ���������� ��� ��� ������ - MODBUS ��� CANtoRS ���������
//#define MODBUS_ENA
#define CANTORS_ENA

// ����� ����� ������������� USB ��� CANopen
//#define CANTOUSB_ENA

//!������ ������ (��������� �� sm_ctrl)
//! ����� �������
#define CTRL_STOP 							0
//! ����� ������� (��������� ���, ������� � ������ �������� ����� ������)
#define CTRL_RUN 							1
//! ����� �������������� (���������� ���), �������� ������ ����
#define CTRL_FLUXING 				        2
//! ����� ���������� ���������� �� ������ U(f) ��� �������� ����
#define CTRL_RUN_U2F				        3
//! ����� �������� ������� ����
#define CTRL_RUN_I2F				        4
//! ��������� ��������� ���������� ������������� � �������� ��� ���������� ������
#define CTRL_RUN_VECTOR_SM    				5
//! ��������� ��������� ���������� � ��������� � � �������� ��������� ��� ���������� ������
#define CTRL_RUN_VECTOR_SM_ENCODER_POS		10

//! ��������� ���������� ��� ������������ ��������� � ��������� � �������� ��������
#define CTRL_RUN_VECTOR_IM_ENCODER			55

//! ��������� ���������� ��� ������������ ��������� � ��������� � �������� �������� � ���������
#define CTRL_RUN_VECTOR_IM_ENCODER_POS		60

//! ����� ���������� ������� ���������
#define CTRL_AUTO_SENSOR_TUNING		        29

//! ��������� ���������� ���������� ����������� ���� ��� ��������: ������� ���������� �� �������
#define CTRL_DC_DRIVE						35
//! ��������� ���������� ���������� ����������� ���� � �������� ���� � ��������
#define CTRL_DC_DRIVE_FB					36

//! ����� �������������� ��� SRM
#define CTRL_RUN_SRM_AUTOCOMMUTATION		101




//����� ������ ��� ������ �����

//bit_fault1
#define F_CTRL_LOW_UDC          	0x1
#define F_CTRL_HI_UDC       	 	0x2
#define F_ENCODER_FAULT             0x4
#define F_MODEL_FAULT 	        	0x8
#define F_FLASH_PROGRAM         	0x10
#define F_CTRL_HI_TEMP  		    0x20
#define F_CAN_RESTORATION_ERROR		0x40
//#define F_RESERVED       		    0x80
#define F_PROGRAM_1K	          	0x100
#define F_PROGRAM_10K        		0x200
#define F_PROGRAM_40K	        	0x400
//#define F_RESERVED	        	0x800
#define F_PDPINT		       		0x1000
#define F_RELAY_START			    0x2000
//#define F_RESERVED	       		0x4000
//#define F_RESERVED				0x8000

//bit_fault2
//#define F_RESERVED				0x1
//#define F_RESERVED				0x2
//#define F_RESERVED				0x4
//#define F_RESERVED				0x8
#define F_CTRL_MAX_I_PH_A			0x10                  
#define F_CTRL_MAX_I_PH_B			0x20                  
#define F_CTRL_MAX_I_PH_C		    0x40
//#define F_RESERVED				0x80
//#define F_RESERVED				0x100
#define F_CTRL_SPEED_MAX			0x200  
//#define F_RESERVED				0x400
//#define F_RESERVED				0x800
#define F_PDP_SWITCH_A0				0x1000
#define F_PDP_SWITCH_A1				0x2000
#define F_PDP_SWITCH_A2				0x4000
#define F_PDP_SWITCH_LOWER			0x8000


#define POS_SENSOR_TYPE_NO_SENSOR 0
#define POS_SENSOR_TYPE_ENCODER 1
#define POS_SENSOR_TYPE_HALL 2
#define POS_SENSOR_TYPE_ENC_HALL 3
#define POS_SENSOR_TYPE_SSI 4
#define POS_SENSOR_TYPE_SENSORLESS 5

//!����� ������������� �������� ������� (����������, ������� ������ 10���)
#define FAST_CALC_FREQ 10000
#define FAST_CALC_TS _IQ(0.0001)



#if (!defined(HW_VECTORCARD_DRV8301_EVM)) && (!defined(HW_VECTORCARD_DRV8312_EVM)) && (!defined(HW_VECTORCARD_SIMULATOR))\
	&& (!defined(HW_NIIET_BOARD_SIMULATOR)) 	&& (!defined(HW_VECTOR_MK_40_4)) && (!defined(HW_MOTORCONTROLBOARD))
#error ���������� ���������� ���� �� ���� ������ ���������� �����
#endif


/*@}*/
