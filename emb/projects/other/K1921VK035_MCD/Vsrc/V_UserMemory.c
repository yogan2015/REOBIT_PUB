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

 \file      V_UserMemory.c
 \brief     Обёртка для I2C памяти
 \author	Лашкевич М.М., Шпак Д.М.
 \version   v 1.0 10/08/2019
*/

/** \addtogroup TUserMemory */
/*@{*/

#include "V_UserMemory.h"
#include "DSP.h"
#include "V_i2cMem.h"



//!Инициализация

//!Инициализация USERMEMORY
//! \memberof TUserMemory
void  USERMEMORY_Init(TUserMemory *p)
{
    i2cMem.init(&i2cMem);
}


//! Проверка, не нужно ли сменить страницу

//! Проверяет текущий адрес на флешке, с которым работает пользователь. Если адрес вышел из текущей страницы, страница записывается на флеш и читается в RAM новый
//! \memberof TUserMemory
void USERMEMORY_UpdateCurrentPage(TUserMemory *p, Uint16 spiaddr)
{

}


//! Запись в память

//!Медленная функция, записывающая на flash заданные данные.
//!Работает с закешированными в оперативке данными, а физическ пишет на флеш только если адрес вылез за границы текущей страницы

//! Адрес во флеше spiaddr, адрес 16ти разрядных данных пользователя startaddr, размер data_length. Все в байтах
//! При выполении операции startaddr инкрементируется, а spiaddr нет
//! \memberof TUserMemory
void USERMEMORY_Write(TUserMemory *p)
{
    i2cMem.DSPstartaddr = p->MCUStartAddr;
    i2cMem.MEMstartaddr = p->MemStartAddr;
    i2cMem.data_length = p->data_length;
    i2cMem.write(&i2cMem);
    p->receivedCode = i2cMem.LastErr;
}


//! Чтение из памяти

//!Медленная функция, считывающая из flash заданные данные. Подробности см. TUserMemory.

//! Адрес во флеше spiaddr, адрес адрес 16ти разрядных данных пользователя startaddr, размер data_length. Все в байтах.
//! При выполении операции startaddr инкрементируется, а spiaddr нет
//! \memberof TUserMemory
void USERMEMORY_Read(TUserMemory *p)
{
    i2cMem.DSPstartaddr = p->MCUStartAddr;
    i2cMem.MEMstartaddr = p->MemStartAddr;
    i2cMem.data_length = p->data_length;
    i2cMem.read(&i2cMem);
    p->receivedCode = i2cMem.LastErr;
}


//! Записывает страницу данные на флешку из кеша (из оперативки одну страницу)

//! \memberof TUserMemory
void USERMEMORY_WriteFromCache(TUserMemory *p, int16 pageNum)
{

}



//! Читает страницу данных из флеша в кеш (в оперативку)

//! \memberof TUserMemory
void USERMEMORY_ReadToCache(TUserMemory *p, int16 pageNum)
{

}


//! Стереть всю флешку (будут FF)

//! \memberof TUserMemory
void USERMEMORY_Full_Erase(TUserMemory *p){
    i2cMem.clearMem(&i2cMem);
}


//! Сбросить кеш из оперативки на флешку

//! \memberof TUserMemory
void USERMEMORY_Flush(TUserMemory *p){
}

//! Медленный фоновый постоянный расчет - нужен пока для систематического сброса кеша на флешку по времени

//! \memberof TUserMemory
void USERMEMORY_slow_calc(TUserMemory *p){
//	}
}

//! Миллисекундный расчет - нужен пока для систематического сброса кеша на флешку по времени

//! \memberof TUserMemory
void USERMEMORY_ms_calc(TUserMemory *p){


}



/*@}*/

