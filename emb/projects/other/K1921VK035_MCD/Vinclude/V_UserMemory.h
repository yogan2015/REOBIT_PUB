/*!
    Copyright 2017 	АО "НИИЭТ" и ООО "НПФ ВЕКТОР"

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
 \brief     Работа с энергонезависимой памятью 1921BK01 (см. TUserMemory)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 10/08/2019

 \defgroup  V_UserMemory Оболочка для I2CMEM (см. TUserMemory)
 @{
*/



#ifndef V_USERMEMORY_H
#define V_USERMEMORY_H

#include "DSP.h"

#ifdef __cplusplus
extern "C" {
#endif


/*! \class TUserMemory
      \brief Работа с пользовательской энергонезависимой памятью I2c

      Класс \a TUserMemory, основанный на структуре TUserMemory, представляет собой оболочку для драйвера для работы с
       flash памятью по интерфейсу I2C.\n
       Оболочка нужна для совместимости с другими проектами, где используется UserMem \n

        пример использования:\n
        для инициализации\n
        UserMem.init(&UserMem);\n

        для записи\n
        UserMem.spiaddr=0;\n
        UserMem.startaddr=buff;\n
        UserMem.data_length=1000;\n
        UserMem.write(&spimem);\n

       */

//! см. TUserMemory

struct SUserMemory {Uint16 MemStartAddr;//!Адрес на flash
				Uint16 *MCUStartAddr; //!адрес на массив с данными
				Uint16 data_length;//!длина данных
				int16 receivedCode;//!Статус операции
                void (*init)(struct SUserMemory*);
                void (*write)(struct SUserMemory*);
                void (*read)(struct SUserMemory*);
                void (*ms_calc)(struct SUserMemory*);
                void (*slow_calc)(struct SUserMemory*);
                void (*full_erase)(struct SUserMemory*);
                };

typedef struct SUserMemory TUserMemory;

//!Инициализатор по умолчанию
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




