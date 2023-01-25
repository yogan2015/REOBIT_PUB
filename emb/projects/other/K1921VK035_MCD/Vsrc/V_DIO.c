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

 \file      V_DIO.c
 \brief     Модуль дискретных входов/выходов
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 25/08/2017

 \addtogroup
 @{*/



#include "main.h"
#include "filter.h"



// Вектор состоЯниЯ дискретных выходов
volatile Uint8 output_vect = 0;

// Вектор состоЯниЯ дискретных входов
volatile Uint8 input_vect = 0;

// Фильтры дискретных входов
TFilter fIn1 = FILTER_DEFAULTS;



void DIO_Init()
{
#if defined (HW_MOTORCONTROLBOARD)
	// Инициализация дискретного входа
	GPIOA->ALTFUNCCLR = (1 << 14);
	GPIOA->OUTENCLR = (1 << 14);

	// Инициализация дискретного выхода
	GPIOA->ALTFUNCCLR = (1 << 15);
	GPIOA->OUTENSET = (1 << 15);

	// Коэффициент фильтрации дискретных входов
	fIn1.T = _IQ(0.03);

#endif

}


void DIO_slow_calc()
{
	// Выводим управлЯющее воздействие по Выходу 1
	if (BIT_IS_SET(output_vect, 0))
		D_OUT1_ON;
    else
    	D_OUT1_OFF;

	// Получаем состоЯние Входа 1 с учётом фильтрации
	if (fIn1.output > _IQ(0.8)) SET_BIT(input_vect, 0);
	if (fIn1.output < _IQ(0.3)) CLEAR_BIT(input_vect, 0);

}


void DIO_fast_calc()
{
	// Инерционный фильтр дискретного Входа 1
    fIn1.input = (D_IN1 == 1) ? _IQ(1.0) : 0;
    fIn1.calc(&fIn1);

}

/*@}*/

