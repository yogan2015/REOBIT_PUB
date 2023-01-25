/*!
    Copyright 2019  АО "НИИЭТ" и ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      v_i2cMem.c
 \brief     Драйвер для работы с микросхемой флеш памяти 24LC256 по
 интерфейсу I2C
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 10/08/2019

 \addtogroup v_i2cMem
@{
*/

#include "main.h"
#include "V_i2cmem.h"
#define I2C_MEM_ERROR_OK                0
#define I2C_MEM_ERROR_WRITE_HW_ERR      1
#define I2C_MEM_ERROR_READ_HW_ERR       2
#define I2C_MEM_ERROR_TIMEOUT           3

TI2cMem i2cMem = I2CMEM_DEFAULTS;

// Желаемая частота шины I2C в килогерцах
#define I2CMEM_FREQUENCY_KHZ    400

// Функция ожидания выполнения команды модулем I2C
// Просто ждёт, пока модуль выйдет из состояния "IDLE"
Uint16 i2c_waitIdle() {
    Uint32 idle = 0;

    while ((I2C->ST & I2C_ST_MODE_Msk) == I2C_ST_MODE_IDLE){
        idle++;
        // Если ожидание слишком долгое - выдать ошибку
        if (idle > 10000000)
            return 1;
    };

    return 0;
}


// Функция ждёт, пока закончится внутренний цикл записи в микросхеме памяти.
// Пока цикл идёт, микросхема не квитирует отправленный ей байт с собственным адресом и командой "Write"
// Если должались, пока микросхема освободится, то на выходе из функции она будет в состоянии
// ожидания приёма внутреннего адреса (то есть её послан старт и адрес устройства с битом "Write")
Uint16 i2c_waitMemBusyAndSendAddWr () {
    volatile Uint32 waitCycles = 0;
    // Посылаем старт и ждём, пока он сделается
    I2C->CTL0 = I2C_CTL0_START_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_STDONE)
        return I2C_MEM_ERROR_TIMEOUT;


    do {
        // Послать адрес устройства + Write, подождать, пока передастся
        I2C->SDA = 0b10100000;
        I2C->CTL0 = I2C_CTL0_CLRST_Msk;
        if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

        // Смотрим, что прислало устройство. Если прислало "4" - значит внутренний цикл записи
        // окончен и можно ехать дальше. Возвращаем 0
        if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTADPA){
            // Иначе смотрим, который раз уже пытаемся дождаться ответа. Если слишком долго - уходим отсюда
            waitCycles++;
            if (waitCycles > 10000000) {
                I2C->CTL0 = I2C_CTL0_STOP_Msk | I2C_CTL0_CLRST_Msk;
                return I2C_MEM_ERROR_TIMEOUT;
            }

            // Если не слишком долго - высылаем повторный старт
            I2C->CTL0 = I2C_CTL0_START_Msk;
            I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
            if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

            if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_RSDONE)
                return I2C_MEM_ERROR_TIMEOUT;
        }
    } while ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTADPA);

    // Дошли до сюда - всё хорошо
    return I2C_MEM_ERROR_OK;
}

// Вспомогательная функция для блочной записи данных в памяти.
// Осуществляет инит/переинит записи массива, который надо вызывать
// при достижении границы страницы (64 байта) внутри памяти.
Uint16 i2c_initWriteArray (Uint16 address) {
    Uint16 retVal;
    // Ждём, пока память память закончин внутреннее сохранение
    retVal = i2c_waitMemBusyAndSendAddWr();
    if (retVal != I2C_MEM_ERROR_OK)
        return retVal;

    // Страший байт адреса 0x0000____
    I2C->SDA = (address >> 8) & 0xFF;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // Если не квитирован - ошибка
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
        return I2C_MEM_ERROR_WRITE_HW_ERR;

    // Младший байт адреса 0x____0000
    I2C->SDA = (address >> 0) & 0xFF;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // Если не квитирован - ошибка
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
        return I2C_MEM_ERROR_WRITE_HW_ERR;

    // Всё хорошо
    return I2C_MEM_ERROR_OK;
}

// Запись массива байт в память.
Uint16 i2c_writeArray(Uint16 address, Uint16 *dataPtr_u16, Uint16 length_u8) {
    // Тут внутри проще работать с байтами
    Uint8* dataPtr_u8 = (Uint8*)dataPtr_u16;

    // Отправляем адрес, с котрого начнём запись
    i2c_initWriteArray(address);

    // Отправляем данные
    while (length_u8 > 0) {
        I2C->SDA = *dataPtr_u8;
        I2C->CTL0 = I2C_CTL0_CLRST_Msk;
        if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

        // Если не квитирован - ошибка
        if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
            return I2C_MEM_ERROR_WRITE_HW_ERR;

        length_u8--;
        dataPtr_u8++;
        address++;

        // Смотрим, не дошли ли до конца страницы внутри памяти/
        // Если дошли - надо отправить стоп и подождать, пока данные пропишутся
        if ((address & 0x3F) == 0) {
            // Формируем стоп и перезапускаем записывалку на новый адрес
            I2C->CTL0 = I2C_CTL0_STOP_Msk;
            I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
            i2c_initWriteArray(address);
        }
    }

    // Закончили - формируем стоп
    I2C->CTL0 = I2C_CTL0_STOP_Msk;
    I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
    return I2C_MEM_ERROR_OK;
}

// Чтение массива 16-разрядных слов
Uint16 i2c_readArray(Uint16 address, Uint16* readDataPtr_u16, Uint16 length_u8){
    // Тут внутри проще работать с байтами
    Uint8* readDataPtr_u8 = (Uint8*)readDataPtr_u16;

    Uint16 retVal;

    // Ждём, пока память память закончит внутреннее сохранение
    retVal = i2c_waitMemBusyAndSendAddWr();
    if (retVal != I2C_MEM_ERROR_OK)
        return retVal;

    // Страший байт адреса 0x0000____
    I2C->SDA = (address >> 8) & 0xFF;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // Если не квитирован - ошибка
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
        return I2C_MEM_ERROR_READ_HW_ERR;

    // Младший байт адреса 0x____0000
    I2C->SDA = (address >> 0) & 0xFF;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // Если не квитирован - ошибка
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MTDAPA)
        return I2C_MEM_ERROR_READ_HW_ERR;

    // Повторный старт, чтобы перейти в режим мастера-приёмника
    I2C->CTL0 = I2C_CTL0_START_Msk;
    I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // Если режим неправильный - ошибка
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_RSDONE)
        return I2C_MEM_ERROR_READ_HW_ERR;

    // Адрес устройства + Read
    I2C->SDA = 0b10100001;
    I2C->CTL0 = I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // Если передача адреса устройства не квитирована - ошибка
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MRADPA)
        return I2C_MEM_ERROR_READ_HW_ERR;

    // До последнего байта принимаем и квитируем
    while (length_u8 > 1) {
        I2C->CTL0 = I2C_CTL0_CLRST_Msk;
        if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

        // Если режим не стал правильным - ошибка
        if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MRDAPA)
            return I2C_MEM_ERROR_READ_HW_ERR;

        *readDataPtr_u8 = I2C->SDA;
        readDataPtr_u8++;
        length_u8--;
    }

    // Последний байт принимаем, но не квитируем
    I2C->CTL0 = I2C_CTL0_ACK_Msk;  // Reset + NACK
    I2C->CTL0 |= I2C_CTL0_CLRST_Msk;
    if (i2c_waitIdle() != 0) return I2C_MEM_ERROR_TIMEOUT;

    // Если режим не стал правильным - ошибка
    if ((I2C->ST & I2C_ST_MODE_Msk) != I2C_ST_MODE_MRDANA)
        return I2C_MEM_ERROR_READ_HW_ERR;

    *readDataPtr_u8 = I2C->SDA;

    // Формируем стоп
    I2C->CTL0 = I2C_CTL0_STOP_Msk | I2C_CTL0_CLRST_Msk;
    return I2C_MEM_ERROR_OK;
}



// Инит модуля I2C и GPIO, к которым подключена память
void I2CMEM_Init(TI2cMem*p){
    // Разрешаем работу 0 и 1 ножек порта А и переводим их в периферийный режим
    GPIOA->ALTFUNCSET = 0x3;

    // Разрешаем работу I2C модуля и ставим ему скорость
    // Fi2c = Fcpu / (4 * SCLFRQ), а Fcpu для 035 = 100 МГц
    I2C->CTL1 |= I2C_CTL1_ENABLE_Msk;
    I2C->CTL1 |= (25000 / I2CMEM_FREQUENCY_KHZ) << I2C_CTL1_SCLFRQ_Pos;
}

// Запись массива байтов
void I2CMEM_Write(TI2cMem*p){
    p->LastErr = i2c_writeArray(p->MEMstartaddr, p->DSPstartaddr, p->data_length);
}

// Чтение массива байтов
void I2CMEM_Read(TI2cMem*p){
    p->LastErr = i2c_readArray(p->MEMstartaddr, p->DSPstartaddr, p->data_length);
}

// Полная очистка памяти
void I2CMEM_Clear(TI2cMem*p){
    Uint32 i = 0;
    Uint16 ffArr[32];
    for (i = 0; i < 32; i++) {
        ffArr[i] = 0xFFFF;
    }

    // Забиваем каждую страницу 0xFF
    for (i = 0; i < EEPROM_MEM_LENGTH; i += 0x40){
        p->MEMstartaddr = i;
        p->DSPstartaddr = ffArr;
        p->data_length = 0x40;

        p->LastErr = i2c_writeArray(p->MEMstartaddr, p->DSPstartaddr, p->data_length);
        if (p->LastErr != I2C_MEM_ERROR_OK)
            return;
    }
}
/*@}*/
