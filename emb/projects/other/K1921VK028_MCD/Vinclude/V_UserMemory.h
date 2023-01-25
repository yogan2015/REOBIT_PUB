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

 \file      V_UserMemory.h
 \brief     ������ � ����������������� ������� 1921BK028 (��. TUserMemory)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 20/03/2019

 \defgroup  V_UserMemory ������ � ����������������� ������� (��. TUserMemory)
 @{
*/



#ifndef V_USERMEMORY_H
#define V_USERMEMORY_H

#include "DSP.h"

#ifdef __cplusplus
extern "C" {
#endif


/*! \class TUserMemory
      \brief ������ � ���������������� ����������������� ������� ��01

      ����� \a TUserMemory, ���������� �� ��������� TUserMemory, ������������ ����� ������� ��� ������ �
       flash �������.\n
        ������ �������������:\n
        ��� �������������\n
        spimem.init.(&spimem);\n

        ��� ������\n
        UserMem.spiaddr=0;\n
        UserMem.startaddr=buff;\n
        UserMem.data_length=1000;\n
        UserMem.write(&spimem);\n

       */

//! ��. TUserMemory

//���������������� ������ �� ������������� ��������� � ��� �� �������, ��� ��������� �������� ���������.
//��� ���, ���� ����������� �� BFlash � ������ ������� ������/�������� NVR ������ ��� �� BFlash, �� ���������� ������������
//������ ���� �� ����� ������/��������. ������ ��� ��� ���� ���������� ����, � �� ����� �������� ������ ���� � ��������
//�������� flash ��� � �������� NVR flash

//#define NVR_MAIN_FLASH      //��������� ���������������� ������ � NVR �������� ������
#define NVR_BOOT_FLASH      //��������� ���������������� ������ � NVR ����������� ������


#define USERMEMORY_USERFLASH_KEY 0xC0DE0100		// ���� 0xC0DE0000 + ��� NVRON
#define USERMEMORY_MAX_WAITCLOCKS 2000000L
#define USERMEMORY_WRITE_HARDFAULT 0x1
#define USERMEMORY_WRITE_TIMEOUT 0x2
#define USERMEMORY_READ_HARDFAULT 0x3
#define USERMEMORY_READ_TIMEOUT 0x4
#define USERMEMORY_OP_OK 0x0

#ifdef NVR_MAIN_FLASH
#define USERMEMORY_PAGE_SIZE MEM_MFLASH_PAGE_SIZE
#define NVRFLASH MFLASH
#define NUMBER_OF_BYTE_ON_PAGE 64
#define NUMBER_OF_32BIT_WORDS_AT_ONCE 16
#define PAGE_SIZE_LOG2 MEM_MFLASH_PAGE_SIZE_LOG2
#endif

#ifdef NVR_BOOT_FLASH
#define USERMEMORY_PAGE_SIZE MEM_BFLASH_PAGE_SIZE
#define NVRFLASH BFLASH
#define NUMBER_OF_BYTE_ON_PAGE 16
#define NUMBER_OF_32BIT_WORDS_AT_ONCE 4
#define PAGE_SIZE_LOG2 MEM_BFLASH_PAGE_SIZE_LOG2
#endif

#define USERMEMORY_CMD_READ (1<<0)
#define USERMEMORY_CMD_WRITE (1<<1)
#define USERMEMORY_CMD_PAGE_ERASE (1<<2)
#define USERMEMORY_CMD_FULL_ERASE (3<<2)	// ��� ERASESEC + ��� ALLSEC
#define USERMEMORY_NVRON_BIT	(1 << 8)


struct SUserMemory {
	Uint16 MemStartAddr; 					//!����� �� flash
	Uint8 *MCUStartAddr8; 					//!����� �� ������ � ������� ��� �������� ���������
	Uint16 *MCUStartAddr; 					//!����� �� ������ � �������
	Uint16 data_length; 					//!����� ������
	int16 receivedCode; 					//!������ ��������
	Uint32 waitClocks; 						//!������� ��� �������� �������� ��������
	Uint16 PageInCache; 					//!����� ������� �������������� ��������
	Uint16 autoFlushCounter; 				//!������� ��� ���������� ���� �� ���� �� ��������
	Uint8 PageRAM_and_FLASH_IdenticalFlag; 	//!���� � ���, ��� ������ � ���� � �� ����� ���������
	Uint8 NeedFlushRequest; 				//���� ������� �� ������ ������ �� ���� �� ����
	Uint8 cacheArr[USERMEMORY_PAGE_SIZE]; 	//��� ������ - ���� �������� ������
	void (*init)(struct SUserMemory*);
	void (*write)(struct SUserMemory*);
	void (*read)(struct SUserMemory*);
	void (*full_erase)(struct SUserMemory*);
	void (*flush)(struct SUserMemory*);
	void (*ms_calc)(struct SUserMemory*);
	void (*slow_calc)(struct SUserMemory*);
};

typedef struct SUserMemory TUserMemory;

//!������������� �� ���������
#define USERMEMORY_DEFAULTS {\
				.init = USERMEMORY_Init, \
				.write = USERMEMORY_Write,\
				.read = USERMEMORY_Read,\
				.full_erase = USERMEMORY_Full_Erase,\
				.flush = USERMEMORY_Flush,\
				.ms_calc = USERMEMORY_ms_calc,\
				.slow_calc = USERMEMORY_slow_calc,\
                }


//! \memberof TUserMemory
void USERMEMORY_Init(TUserMemory*);
//! \memberof TUserMemory
void USERMEMORY_Write(TUserMemory*);
//! \memberof TUserMemory
void USERMEMORY_Read(TUserMemory*);
//! \memberof TUserMemory
void USERMEMORY_Full_Erase(TUserMemory*);
//! \memberof TUserMemory
void USERMEMORY_ReadToCache(TUserMemory *p, int16 pageNum);
//! \memberof TUserMemory
void USERMEMORY_WriteFromCache(TUserMemory *p, int16 pageNum);
//! \memberof TUserMemory
void USERMEMORY_Flush(TUserMemory *p);
//! \memberof TUserMemory
void USERMEMORY_ms_calc(TUserMemory *p);
//! \memberof TUserMemory
void USERMEMORY_slow_calc(TUserMemory *p);
//! \memberof TUserMemory
void USERMEMORY_UpdateCurrentPage(TUserMemory *p, Uint16 spiaddr);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/




