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
 \brief     ������ � ����������������� ������� 1921BK01 (��. TUserMemory)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 10/08/2019

 \defgroup  V_UserMemory �������� ��� I2CMEM (��. TUserMemory)
 @{
*/



#ifndef V_USERMEMORY_H
#define V_USERMEMORY_H

#include "DSP.h"

#ifdef __cplusplus
extern "C" {
#endif


/*! \class TUserMemory
      \brief ������ � ���������������� ����������������� ������� I2c

      ����� \a TUserMemory, ���������� �� ��������� TUserMemory, ������������ ����� �������� ��� �������� ��� ������ �
       flash ������� �� ���������� I2C.\n
       �������� ����� ��� ������������� � ������� ���������, ��� ������������ UserMem \n

        ������ �������������:\n
        ��� �������������\n
        UserMem.init(&UserMem);\n

        ��� ������\n
        UserMem.spiaddr=0;\n
        UserMem.startaddr=buff;\n
        UserMem.data_length=1000;\n
        UserMem.write(&spimem);\n

       */

//! ��. TUserMemory

struct SUserMemory {Uint16 MemStartAddr;//!����� �� flash
				Uint16 *MCUStartAddr; //!����� �� ������ � �������
				Uint16 data_length;//!����� ������
				int16 receivedCode;//!������ ��������
                void (*init)(struct SUserMemory*);
                void (*write)(struct SUserMemory*);
                void (*read)(struct SUserMemory*);
                void (*ms_calc)(struct SUserMemory*);
                void (*slow_calc)(struct SUserMemory*);
                void (*full_erase)(struct SUserMemory*);
                };

typedef struct SUserMemory TUserMemory;

//!������������� �� ���������
#define USERMEMORY_DEFAULTS {.init = USERMEMORY_Init, \
				             .write = USERMEMORY_Write,\
				             .read = USERMEMORY_Read,\
				             .ms_calc = USERMEMORY_ms_calc,\
				             .slow_calc = USERMEMORY_slow_calc,\
				             .full_erase = USERMEMORY_Full_Erase,\
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
void USERMEMORY_ms_calc(TUserMemory *p);
//! \memberof TUserMemory
void USERMEMORY_slow_calc(TUserMemory *p);


#ifdef __cplusplus
}
#endif

#endif

/*@}*/




