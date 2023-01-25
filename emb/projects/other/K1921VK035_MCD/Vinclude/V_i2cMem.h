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

 \file      v_i2cMem.h
 \brief     Драйвер для работы с микросхемой флеш памяти 24LC256 по
 интерфейсу I2C
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 10/08/2019

 \addtogroup v_i2cMem
@{
*/
#ifndef INCLUDE_V_I2CMEM_H_
#define INCLUDE_V_I2CMEM_H_

#define EEPROM_MEM_LENGTH 32768 // Размер памяти в байтах (256 кбит)

struct SI2cMem;
typedef volatile struct SI2cMem TI2cMem;

struct SI2cMem {
    Uint16 MEMstartaddr;    //! Адрес на flash
    Uint16 data_length;     //! Длина данных в байтах
    Uint16 *DSPstartaddr;   //! Адрес на массив с данными в контроллере
    Uint16 LastErr;         //! Код ошибки (если возникла)
    void (*init)(TI2cMem*);
    void (*write)(TI2cMem*);
    void (*read)(TI2cMem*);
    void (*clearMem)(TI2cMem*);
    };


void I2CMEM_Init(TI2cMem*);
void I2CMEM_Write(TI2cMem*);
void I2CMEM_Read(TI2cMem*);
void I2CMEM_Clear(TI2cMem*);

//!Инициализатор по умолчанию
#define I2CMEM_DEFAULTS { .init = I2CMEM_Init, \
                          .write = I2CMEM_Write,\
                          .read = I2CMEM_Read,\
                          .clearMem = I2CMEM_Clear,\
                        }

extern TI2cMem i2cMem;

#endif /* INCLUDE_V_I2CMEM_H_ */
