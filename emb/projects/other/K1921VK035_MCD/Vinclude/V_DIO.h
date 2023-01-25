/*!
     Copyright 2017 	јќ "Ќ»»Ё“" и ќќќ "Ќѕ‘ ¬≈ “ќ–"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_DIO.h
 \brief     ћодуль дискретных входов/выходов
 \author    ќќќ "Ќѕ‘ ¬ектор". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/


#ifndef V_DIO_H
#define V_DIO_H

#ifdef __cplusplus
extern "C" {
#endif


// ћакрос установки в '1' заданного бита
// var - целевая переменная
// index - индекс (смещение) устанавливаемого бита
#define SET_BIT(var, index) var |= (1 << index);

// ћакрос сброса в '0' заданного бита
// var - целевая переменная
// index - индекс (смещение) очищаемого бита
#define CLEAR_BIT(var, index) var &= (~(1 << index));

// ћакрос проверки ненулевого состояни€ заданного бита
// var - целевая переменная
// index - индекс (смещение) проверяемого бита
#define BIT_IS_SET(var, index) ((var & (1 << index)) != 0)

// ћакрос проверки нулевого состояни€ заданного бита
// var - целевая переменная
// index - индекс (смещение) проверяемого бита
#define BIT_IS_CLEAR(var, index) ((var & (1 << index)) == 0)


// ƒефайним дискретные входы
#ifdef HW_MOTORCONTROLBOARD

#define D_IN1			((GPIOA->DATA & (1 << 14)) == 0)			// ¬ход 1

#else

#define D_IN1	0

#endif

// ƒефайним дискретные выходы
#ifdef HW_MOTORCONTROLBOARD
#define D_OUT1_ON		GPIOA->DATAOUTSET = (1 << 15)
#define D_OUT1_OFF		GPIOA->DATAOUTCLR = (1 << 15)
#else
#define D_OUT1_ON
#define D_OUT1_OFF
#endif



// ¬ектор состояния дискретных выходов
extern volatile Uint8 output_vect;

// ¬ектор состояния дискретных входов
extern volatile Uint8 input_vect;


void DIO_Init();

void DIO_slow_calc();	// вызывать в фоновой программе

void DIO_fast_calc();	// вызывать с частотой 1к√ц или 10 к√ц


#ifdef __cplusplus
}
#endif

#endif

/*@}*/
