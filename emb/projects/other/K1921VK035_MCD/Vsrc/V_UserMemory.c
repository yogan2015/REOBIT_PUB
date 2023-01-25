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

 \file      V_UserMemory.c
 \brief     ������ ��� I2C ������
 \author	�������� �.�., ���� �.�.
 \version   v 1.0 10/08/2019
*/

/** \addtogroup TUserMemory */
/*@{*/

#include "V_UserMemory.h"
#include "DSP.h"
#include "V_i2cMem.h"



//!�������������

//!������������� USERMEMORY
//! \memberof TUserMemory
void  USERMEMORY_Init(TUserMemory *p)
{
    i2cMem.init(&i2cMem);
}


//! ��������, �� ����� �� ������� ��������

//! ��������� ������� ����� �� ������, � ������� �������� ������������. ���� ����� ����� �� ������� ��������, �������� ������������ �� ���� � �������� � RAM �����
//! \memberof TUserMemory
void USERMEMORY_UpdateCurrentPage(TUserMemory *p, Uint16 spiaddr)
{

}


//! ������ � ������

//!��������� �������, ������������ �� flash �������� ������.
//!�������� � ��������������� � ���������� �������, � �������� ����� �� ���� ������ ���� ����� ����� �� ������� ������� ��������

//! ����� �� ����� spiaddr, ����� 16�� ��������� ������ ������������ startaddr, ������ data_length. ��� � ������
//! ��� ��������� �������� startaddr ����������������, � spiaddr ���
//! \memberof TUserMemory
void USERMEMORY_Write(TUserMemory *p)
{
    i2cMem.DSPstartaddr = p->MCUStartAddr;
    i2cMem.MEMstartaddr = p->MemStartAddr;
    i2cMem.data_length = p->data_length;
    i2cMem.write(&i2cMem);
    p->receivedCode = i2cMem.LastErr;
}


//! ������ �� ������

//!��������� �������, ����������� �� flash �������� ������. ����������� ��. TUserMemory.

//! ����� �� ����� spiaddr, ����� ����� 16�� ��������� ������ ������������ startaddr, ������ data_length. ��� � ������.
//! ��� ��������� �������� startaddr ����������������, � spiaddr ���
//! \memberof TUserMemory
void USERMEMORY_Read(TUserMemory *p)
{
    i2cMem.DSPstartaddr = p->MCUStartAddr;
    i2cMem.MEMstartaddr = p->MemStartAddr;
    i2cMem.data_length = p->data_length;
    i2cMem.read(&i2cMem);
    p->receivedCode = i2cMem.LastErr;
}


//! ���������� �������� ������ �� ������ �� ���� (�� ���������� ���� ��������)

//! \memberof TUserMemory
void USERMEMORY_WriteFromCache(TUserMemory *p, int16 pageNum)
{

}



//! ������ �������� ������ �� ����� � ��� (� ����������)

//! \memberof TUserMemory
void USERMEMORY_ReadToCache(TUserMemory *p, int16 pageNum)
{

}


//! ������� ��� ������ (����� FF)

//! \memberof TUserMemory
void USERMEMORY_Full_Erase(TUserMemory *p){
    i2cMem.clearMem(&i2cMem);
}


//! �������� ��� �� ���������� �� ������

//! \memberof TUserMemory
void USERMEMORY_Flush(TUserMemory *p){
}

//! ��������� ������� ���������� ������ - ����� ���� ��� ���������������� ������ ���� �� ������ �� �������

//! \memberof TUserMemory
void USERMEMORY_slow_calc(TUserMemory *p){
//	}
}

//! �������������� ������ - ����� ���� ��� ���������������� ������ ���� �� ������ �� �������

//! \memberof TUserMemory
void USERMEMORY_ms_calc(TUserMemory *p){


}



/*@}*/

