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
 \brief     Работа с пользовательской энергонезависимой памятью 1921BK028 (см. TUserMemory)
 \author	Лашкевич М.М., Шпак Д.М.
 \version   v 1.0 21/03/2019
*/

/** \addtogroup TUserMemory */
/*@{*/

#include "main.h"
#include "DSP.h"




//!Инициализация

//!Инициализация USERMEMORY
//! \memberof TUserMemory
void  USERMEMORY_Init(TUserMemory *p)
{
	USERMEMORY_ReadToCache(p,0);//читаем в оперативку нулевой страницы (чтобы была текущая страница и все работало корректно дальше)
}

//! Вспомогательная функция ожидания операции, возвращет "0" если всё ОК, и "1", если не всё ОК
Uint16 waitUserFlashBusy (TUserMemory *p) {
	p->waitClocks = 0;
	__NOP();		// В документации сказали подождать перед проверкой статуса
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	while(NVRFLASH->STAT_bit.BUSY == 0x1){//ждем
		p->waitClocks++;
		if (p->waitClocks > USERMEMORY_MAX_WAITCLOCKS){//устали ждать
			return 1;
		}
	}
	return 0;
}
//! Проверка, не нужно ли сменить страницу

//! Проверяет текущий адрес на флешке, с которым работает пользователь. Если адрес вышел из текущей страницы, страница записывается на флеш и читается в RAM новый
//! \memberof TUserMemory
void USERMEMORY_UpdateCurrentPage(TUserMemory *p, Uint16 spiaddr)
{
	Uint16 newPage=spiaddr>>PAGE_SIZE_LOG2;//номер страницы - это верхнее значение адреса, так как страница 256 байт
	if (newPage!=p->PageInCache){//страница другая?
		if (p->PageRAM_and_FLASH_IdenticalFlag==0)//и есть измененные данные в этой странице в оперативке в кеше?
			USERMEMORY_Flush(p);//загоняем страницу на флеш
		if (p->receivedCode!=USERMEMORY_OP_OK)//не вышло?
			return;
		//читаем в оперативку новую страницу
		USERMEMORY_ReadToCache(p,newPage);
		if (p->receivedCode!=USERMEMORY_OP_OK)//не вышло?
			return;
	}
}


//! Запись в память

//!Медленная функция, записывающая на flash заданные данные.
//!Работает с закешированными в оперативке данными, а физическ пишет на флеш только если адрес вылез за границы текущей страницы

//! Адрес во флеше spiaddr, адрес 16ти разрядных данных пользователя startaddr, размер data_length. Все в байтах
//! При выполении операции startaddr инкрементируется, а spiaddr нет
//! \memberof TUserMemory
void USERMEMORY_Write(TUserMemory *p)
{
	Uint16 i = 0;
	Uint16 spiaddrTmp=p->MemStartAddr;//адрес на флеше в байтах
	p->MCUStartAddr8=(Uint8*)p->MCUStartAddr;//меняем указатель на данные - из указателя на 16ти разрядные данные на указатель на байты - так удобнее
	for(i = 0; i < p->data_length; i++){//по всем данным, что хочет пользователь
		USERMEMORY_UpdateCurrentPage(p,spiaddrTmp);//сменить и перечитать страницу, если она другая
		Uint16 addrInPage=spiaddrTmp&0xFFFF;//адрес внутри страницы
		if (p->cacheArr[addrInPage] != (*(p->MCUStartAddr8))){//данные на совпадают с тем, что уже в оперативке в этом месте?
			p->cacheArr[addrInPage]=(*(p->MCUStartAddr8));//кладем данные в оперативку
			p->PageRAM_and_FLASH_IdenticalFlag=0;//флаг, что данные в оперативке отличаются от записанных на флеше
		}
		spiaddrTmp++;
		p->MCUStartAddr8++;
	}
	//p->MCUStartAddr=(Uint16*)p->MCUStartAddr8;//чтобы адрес на данные поменялся (не знаю, надо это кому или нет)
	p->receivedCode = USERMEMORY_OP_OK;
}


//! Чтение из памяти

//!Медленная функция, считывающая из flash заданные данные. Подробности см. TUserMemory.

//! Адрес во флеше spiaddr, адрес адрес 16ти разрядных данных пользователя startaddr, размер data_length. Все в байтах.
//! При выполении операции startaddr инкрементируется, а spiaddr нет
//! \memberof TUserMemory
void USERMEMORY_Read(TUserMemory *p)
{
	Uint16 i = 0;
	Uint16 spiaddrTmp=p->MemStartAddr;
	p->MCUStartAddr8=(Uint8*)p->MCUStartAddr;
	for(i = 0; i < p->data_length; i++){//по всем данным, что хочет пользователь
		USERMEMORY_UpdateCurrentPage(p,spiaddrTmp);//сменить и перечитать страницу, если она другая
		Uint16 addrInPage=spiaddrTmp&0xFFFF;//адрес внутри страницы
		*(p->MCUStartAddr8) = p->cacheArr[addrInPage];//отдаем данные из оперативки, они должны быть там актуальные после USERMEMORY_UpdateCurrentPage
		spiaddrTmp++;
		p->MCUStartAddr8++;
	}
	p->MCUStartAddr=(Uint16*)p->MCUStartAddr8;//чтобы адрес на данные поменялся (не знаю, надо это кому или нет)
	p->receivedCode = USERMEMORY_OP_OK;
}


//! Записывает страницу данные на флешку из кеша (из оперативки одну страницу)

//! \memberof TUserMemory
void USERMEMORY_WriteFromCache(TUserMemory *p, int16 pageNum)
{
	int16 i = 0, readDataWord = 0;
	Uint32 *arrayPointer;
	Uint16 addrOffset=pageNum*USERMEMORY_PAGE_SIZE;//начальный адрес на флешке (от начала страницы)
	NVRFLASH->STAT = 0x3;//сброс статуса
	NVRFLASH->ADDR = addrOffset;//адрес начала страницы
	NVRFLASH->CMD = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_PAGE_ERASE);//стираем страницу

	if (waitUserFlashBusy(p) != 0){
		p->receivedCode = USERMEMORY_WRITE_TIMEOUT;
		return;
	}

	for(i = 0; i < USERMEMORY_PAGE_SIZE; i += NUMBER_OF_BYTE_ON_PAGE){//цикл по размеру страницы
		NVRFLASH->STAT = 0x3;					//сброс статуса
		NVRFLASH->ADDR = addrOffset + i;	//адрес

		arrayPointer = (Uint32*)(&p->cacheArr[i]);
		for (readDataWord = 0; readDataWord < NUMBER_OF_32BIT_WORDS_AT_ONCE; readDataWord++){
			NVRFLASH->DATA[readDataWord].DATA = *arrayPointer;
			arrayPointer++;
		}

		NVRFLASH->CMD = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_WRITE);//команда на запись байта

		if (waitUserFlashBusy(p) != 0){
			p->receivedCode = USERMEMORY_WRITE_TIMEOUT;
			return;
		}
	}
	NVRFLASH->STAT = 0x3;//сброс статуса
	p->receivedCode = USERMEMORY_OP_OK;//все хорошо
	p->PageRAM_and_FLASH_IdenticalFlag=1;//данные страницы в оперативке и во флеше теперь идентичны
}



//! Читает страницу данных из флеша в кеш (в оперативку)

//! \memberof TUserMemory
void USERMEMORY_ReadToCache(TUserMemory *p, int16 pageNum)
{
	int16 i = 0, readDataWord = 0;
	Uint16 addrOffset = pageNum * USERMEMORY_PAGE_SIZE;//начальный адрес на флешке (от начала страницы)
	Uint32 *arrayPointer;
	for(i = 0; i < USERMEMORY_PAGE_SIZE; i += NUMBER_OF_BYTE_ON_PAGE){//цикл по размеру страницы
		NVRFLASH->STAT = 0x3;//сброс статуса
		NVRFLASH->ADDR = addrOffset + i;//адрес
		NVRFLASH->CMD = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_READ);//команда на чтение байта


		if (waitUserFlashBusy(p) != 0){
			p->receivedCode = USERMEMORY_READ_TIMEOUT;
			return;
		}
		arrayPointer = (Uint32*)&(p->cacheArr[i]);

		// Считывается по 16 или 4 32-разрядных слова{
		for (readDataWord = 0; readDataWord < NUMBER_OF_32BIT_WORDS_AT_ONCE; readDataWord++){
			*arrayPointer = NVRFLASH->DATA[readDataWord].DATA;//данные (один байт) в оперативку
			arrayPointer++;
		}

	}
	NVRFLASH->STAT = 0x3;//сброс статуса
	p->receivedCode = USERMEMORY_OP_OK;
	p->PageInCache=pageNum;//какая страница теперь в кеше
	p->PageRAM_and_FLASH_IdenticalFlag=1;//данные в оперативке (в кеше) идентичны с флешем
}


//! Стереть всю флешку (будут FF)

//! \memberof TUserMemory
void USERMEMORY_Full_Erase(TUserMemory *p){
	// Cброс статуса, команда стирания и ожидание завершения
	NVRFLASH->STAT = 0x3;
	NVRFLASH->CMD = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_FULL_ERASE);//команда на стирание фсей флеши
	__NOP();		// В документации сказали подождать перед проверкой статуса
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	while(NVRFLASH->STAT_bit.BUSY == 0x1){};

}


//! Сбросить кеш из оперативки на флешку

//! \memberof TUserMemory
void USERMEMORY_Flush(TUserMemory *p){
	USERMEMORY_WriteFromCache(p,p->PageInCache);
}

//! Медленный фоновый постоянный расчет - нужен пока для систематического сброса кеша на флешку по времени

//! \memberof TUserMemory
void USERMEMORY_slow_calc(TUserMemory *p){
	if (p->NeedFlushRequest){//надо флушить?
		USERMEMORY_Flush(p);
		p->NeedFlushRequest=0;
	}
}

//! Миллисекундный расчет - нужен пока для систематического сброса кеша на флешку по времени

//! \memberof TUserMemory
void USERMEMORY_ms_calc(TUserMemory *p){

	if (!p->PageRAM_and_FLASH_IdenticalFlag)//данные на флешке и в оперативке не идентичны
		p->autoFlushCounter++;

	if (p->autoFlushCounter>10000) //зищита от переполнения
		p->autoFlushCounter=10000;

	if (p->autoFlushCounter>500){//долго не сбрасывается на флешку
		p->NeedFlushRequest=1;//надо флушить, но тут это делать нельзя, ибо прерывание, ставим реквест фону
		p->autoFlushCounter=0;
	}

}



/*@}*/

