/* ==================================================================================
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

//File name:       CANOpenUDfuncs.c

//Description: � ���� �������� ������� �������� CANOpen ������������ ������������� (������ �������, ������� ������������� � �.�.)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 2017_02_08

//=====================================================================================*/
#include "main.h"

//! ������� � ����������� ��������� CAN ��� ����������������� ����� �����. ������������� ������.

// ������� ��������� � ������������� ���������� � ������� ���������!!!

//! ��������������� �1921��01�
/*
// kb/s:                                125     50     125     250     500     1000
TCANSpeedTableOptions canSpeedTable = { {1,     1,      1,      0,      0,      0 }, \
                                        {9,     24,     9,      39,     19,     9 }, \
                                        {6,     6,      6,      6,      6,      6 }, \
                                        {1,     1,      1,      1,      1,      1 }, \
                                        {1,     1,      1,      1,      1 ,     1 }, \
                                      };
//                                       ^- ��������� �� 125, �.�. 10 kb/s �� ����������
*/
//! ��������������� �1921��028
// kb/s:                                125     50     125     250     500     1000
TCANSpeedTableOptions canSpeedTable = { {1,      1,     1,      1,      0,      0 }, \
                                        {19,     49,    19,     9,      39,     19}, \
                                        {6,      6,     6,      6,      6,      6 }, \
                                        {1,      1,     1,      1,      1,      1 }, \
                                        {1,      1,     1,      1,      1 ,     1 }, \
                                      };
//                                       ^- ��������� �� 125, �.�. 10 kb/s �� ����������
//! ��������������� �1921��035
/*
// kb/s:                                125     50     125     250     500     1000
TCANSpeedTableOptions canSpeedTable = { {1,     1,      1,      0,      0,      0 }, \
                                        {9,     24,     9,      39,     19,     9 }, \
                                        {6,     6,      6,      6,      6,      6 }, \
                                        {1,     1,      1,      1,      1,      1 }, \
                                        {1,     1,      1,      1,      1 ,     1 }, \
                                      };
//                                       ^- ��������� �� 125, �.�. 10 kb/s �� ����������
*/

//**********************************************************************************************************************************************************************************************************
//������� ������������� Gpio CAN1
#ifdef CAN_1_ENABLE
void co_CAN1GpioInit()
{
    //������������� ����� � GpioPeripheralInit.c
}
#endif //CAN_1_ENABLE

//������� ������������� Gpio CAN2
#ifdef CAN_2_ENABLE
void co_CAN2GpioInit()
{
    //������������� ����� � GpioPeripheralInit.c
}
#endif //CAN_2_ENABLE
//**********************************************************************************************************************************************************************************************************
//������� ������ � ����������������� ������� (� �������� ������ ����� �������������� ��� ���������������� ���� �� ����� MCU,
// ��� � ������ ������������, �������� ����� SPI, eeprom).
//������� ������������ ��������� CANopen ��� ���������� � �������������� ���������� ������� ��������
//� ����� ������ �������� CANOpen ������� ��������� ���������� ������ � ������ ��/� �����
void co_UserMemoryRead (const T_UserMemoryContext *p)
{
	UserMem.MemStartAddr = p->MemStartAddr;
	UserMem.MCUStartAddr = p->MCUStartAddr;
	UserMem.data_length = p->data_length;
	UserMem.read(&UserMem);
}

void co_UserMemoryWrite (const T_UserMemoryContext *p)
{
	UserMem.MemStartAddr = p->MemStartAddr;
	UserMem.MCUStartAddr = p->MCUStartAddr;
	UserMem.data_length = p->data_length;
	UserMem.write(&UserMem);
}
//**********************************************************************************************************************************************************************************************************

//�������, ������� ���������� ��������� CANOpen ��� ������������� �������� CAN ��������� �� ������� ���������
//������ ������� ������������� ������ ���� �������� ����� ��������������� �������, �������������� �������� CAN ������
void co_CANToExtInterface_Send(TZCanMsg* MSG, Uint16 tag_CANnum)
{
	CANtoRS.write(MSG,&CANtoRS);
}



//������� �� ������ PDO
void co_RPDO1_Callback(Uint16 nodeID, Uint16 tag_CANnum)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//������������ ���-������...
			break;
		}
		case 2:
		{
			PDO_cntr2++;
			//������������ ���-������...
			break;
		}
		default:
			break;
	}
	*/
}

void co_RPDO2_Callback(Uint16 nodeID, Uint16 tag_CANnum)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//������������ ���-������...
			break;
		}
		default:
			break;
	}
	*/
}

void co_RPDO3_Callback(Uint16 nodeID, Uint16 tag_CANnum)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//������������ ���-������...
			break;
		}
		default:
			break;
	}
	*/
}

void co_RPDO4_Callback(Uint16 nodeID, Uint16 tag_CANnum)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//������������ ���-������...
			break;
		}
		default:
			break;
	}
	*/
}

void co_RPDO5_Callback(Uint16 nodeID, Uint16 tag_CANnum)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//������������ ���-������...
			break;
		}
		default:
			break;
	}
	*/
}

void co_RPDO6_Callback(Uint16 nodeID, Uint16 tag_CANnum)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//������������ ���-������...
			break;
		}
		default:
			break;
	}
	*/
}

void co_RPDO7_Callback(Uint16 nodeID, Uint16 tag_CANnum)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//������������ ���-������...
			break;
		}
		default:
			break;
	}
	*/
}

void co_RPDO8_Callback(Uint16 nodeID, Uint16 tag_CANnum)
{
	/*
	switch(nodeID)
	{
		case 1:
		{
			//������������ ���-������...
			break;
		}
		default:
			break;
	}
	*/
}



//!��������� �� CANopen � ����� ��������� �������.

//!���� ���������� ������ � �������� [5139h.01h] �����. ����.���� ��������� �������,
//�� ���������� callback_RTC - ��� ��������������� ������ �� ��������� �����.

void callback_RTC(Uint16 par, Uint16 tag_CANnum) {
	if (par == 1) {
		RTCclock.setTimeFlag = 1; //��������� ������ � ����

	}
}

//!��������� � ���������� dlog.next_value_var � ������� ��������� ������������.

//!���������� ����������� ���������, ����������� ���������������� ���������� ������������������� ����������
//!������ TDataLog. ��� ������� ���������� ��� ��������� � ����������, ����� ������� �������� ������� ����������
//!�������������. ������ � ��� ���������� ������������� ��������� ����� ������ (���� � 4�) � ����� ����������� �����.
//!��� ������ �� � ��� ���������� ������������ ���� ����������������������� ������.

void callback_dlog(Uint16 par, Uint16 tag_CANnum) {
	//���� ������, �� ��������� ����� �� ������ �����
	if (par == 1) {
		//� ���������� next_value_var ������������ �������� ��������, ����� ������, �� �������� ����� ������,
		//� ��� �� ������������
		dlog.buff_num = (long)((dlog.next_value_var >> 24) & 3); //����������� ����� ������
#if DLOG_DATA_SIZE == 32
		dlog.highPartOfValue = (int)((dlog.next_value_var >> 26) & 1); // �������� ������� ����� 32-������� ��������?
#endif
		dlog.Rcounter = (dlog.next_value_var >> 16) & 0xFF; //����� ����� ���� ��������

		//��������� ����� �� ������������ ������� ��������
		if ((dlog.next_value_var & 0xffff) == 1) {
			//�����, ������� �� ���� ���������� ������� ��������
#ifdef CAN_1_ENABLE
			if (co1_vars.co_blockTransferCommand == CANBT_INTERFACE_FREE)
				co1_vars.co_blockTransferCommand = CANBT_INTERFACE_DATALOG1;
#endif
#ifdef CAN_2_ENABLE
			if (co2_vars.co_blockTransferCommand == CANBT_INTERFACE_FREE)
				co2_vars.co_blockTransferCommand = CANBT_INTERFACE_DATALOG1;
#endif
		}
#if DLOG_DATA_SIZE == 32
		if ((dlog.next_value_var & 0xffff) == 2) {
#ifdef CAN_1_ENABLE
			if (co1_vars.co_blockTransferCommand == CANBT_INTERFACE_FREE)
				co1_vars.co_blockTransferCommand = CANBT_INTERFACE_DATALOG2;
#endif
#ifdef CAN_2_ENABLE
			if (co2_vars.co_blockTransferCommand == CANBT_INTERFACE_FREE)
				co2_vars.co_blockTransferCommand = CANBT_INTERFACE_DATALOG2;
#endif
		}
#endif	// DLOG_DATA_SIZE == 32

	}

	//��������� ������:
#if DLOG_DATA_SIZE == 16
	switch (dlog.buff_num) { //������� ����� ������
	case 0: {
		dlog.next_value_var = dlog.dl_buffer1_adr[(dlog.Rcounter + dlog.first_point_written) & 0xFF];
		break;
	}
	case 1: {
		dlog.next_value_var = dlog.dl_buffer2_adr[(dlog.Rcounter + dlog.first_point_written) & 0xFF];
		break;
	}
	case 2: {
		dlog.next_value_var = dlog.dl_buffer3_adr[(dlog.Rcounter + dlog.first_point_written) & 0xFF];
		break;
	}
	case 3: {
		dlog.next_value_var = dlog.dl_buffer4_adr[(dlog.Rcounter + dlog.first_point_written) & 0xFF];
		break;
	}
	default: { //���� � buff_num ���-�� �� ��, ��-������� ����� ������ �����
		dlog.next_value_var = dlog.dl_buffer1_adr[(dlog.Rcounter + dlog.first_point_written) & 0xFF];
		break;
	}
	}
	//������ ������ � ������ �����
	dlog.next_value_var &= 0xFFFF;
	dlog.next_value_var |= (((unsigned long) dlog.Rcounter) << 16); //� ������� ����� ����� Rcounter ��� ��������
	dlog.next_value_var |= (((unsigned long) dlog.buff_num) << 24); //� ������� ����� ����� (��� ����) buff_num ��� ��������

	dlog.Rcounter++; //����� ����� ������. ���������������� ���� ����� ������ ������� �����.
	dlog.Rcounter &= 0xFF; //�� �����. ������ ���������, ����� ������� �������. ��. ������
#endif
#if DLOG_DATA_SIZE == 32
	int32 val32;
	int varSizeIs16;
	switch (dlog.buff_num) { //������� ����� ������
	default:
	case 0: {
		val32 = dlog.dl_buffer1_adr[(dlog.Rcounter + dlog.first_point_written) & 0xFF];
		varSizeIs16 = (int)(dlog.object1Info.varSize == 16);
		break;
	}
	case 1: {
		val32 = dlog.dl_buffer2_adr[(dlog.Rcounter + dlog.first_point_written) & 0xFF];
		varSizeIs16 = (int)(dlog.object2Info.varSize == 16);
		break;
	}
	case 2: {
		val32 = dlog.dl_buffer3_adr[(dlog.Rcounter + dlog.first_point_written) & 0xFF];
		varSizeIs16 = (int)(dlog.object3Info.varSize == 16);
		break;
	}
	case 3: {
		val32 = dlog.dl_buffer4_adr[(dlog.Rcounter + dlog.first_point_written) & 0xFF];
		varSizeIs16 = (int)(dlog.object4Info.varSize == 16);
		break;
	}
	}
	dlog.next_value_var = (dlog.highPartOfValue != 0 ? val32 >> 16 : val32) & 0x0000FFFF;
	dlog.next_value_var |= ((Uint32)dlog.Rcounter) << 16;
	dlog.next_value_var |= ((Uint32)dlog.buff_num) << 24;
	dlog.next_value_var |= ((Uint32)dlog.highPartOfValue) << 26;
	dlog.next_value_var |= ((Uint32)varSizeIs16) << 27;

	if ((dlog.highPartOfValue != 0) || varSizeIs16)
	{
		// ��� ��������� ������� ������� ������� ����� ��������� �����.
		dlog.Rcounter++;
		dlog.Rcounter &= 0xFF;
		dlog.highPartOfValue = 0;
	}
	else
	{
		// ��� ��������� ������� ������� ������� ����� ���� �� �����.
		dlog.highPartOfValue = 1;
	}
#endif
}
