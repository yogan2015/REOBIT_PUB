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
 \version   v 2.0 25/09/2019

 \addtogroup
 @{*/



#include "main.h"
#include "filter.h"


// Дефайним дискретные входы
#ifdef HW_MCB3
#define D_IN0			((GPIOM->DATA & (1 << 13)) == 0)			//M13	Старт
#define D_IN1			((GPIOM->DATA & (1 << 11)) == 0)			//M11	Стоп
#define D_IN2			((GPIOM->DATA & (1 << 10)) == 0)			//M10	Сброс аварий
#else
#define D_IN0	0
#define D_IN1	0
#define D_IN2	0
#endif

// Дефайним дискретные выходы
#ifdef HW_MCB3
#define D_OUT0_ON		GPIOD->DATAOUTSET = GPIO_PIN_1
#define D_OUT0_OFF		GPIOD->DATAOUTCLR = GPIO_PIN_1
#define D_OUT1_ON		GPIOD->DATAOUTSET = GPIO_PIN_2
#define D_OUT1_OFF		GPIOD->DATAOUTCLR = GPIO_PIN_2
#define D_OUT2_ON		GPIOM->DATAOUTSET = GPIO_PIN_14
#define D_OUT2_OFF		GPIOM->DATAOUTCLR = GPIO_PIN_14
#else
#define D_OUT0_ON
#define D_OUT0_OFF
#define D_OUT1_ON
#define D_OUT1_OFF
#define D_OUT2_ON
#define D_OUT2_OFF
#endif



void DIO_init(TDIO* p)
{
	//Настройка коэффициентов фильтрации и порогов срабатывания для дискретных входов
	p->inputKf = _IQ(0.03);
	p->inputOff = _IQ(0.2);
	p->inputOn = _IQ(0.8);
	//Время включения/отключения при коэффициентах inputKf=_IQ(0.2), inputOn = _IQ(0.8), inputKf = _IQ(0.03) будет составлять примерно 60 мс (фильтры считаются в 1кГц прерывании)
}


void DIO_slow_calc(TDIO* p)
{
	// ОбновлЯем коэффициенты фильтрации дискретных входов
	p->fIn0.T = p->inputKf;
	p->fIn1.T = p->inputKf;
	p->fIn2.T = p->inputKf;
}


void DIO_ms_calc(TDIO* p)
{

	//------------------------Обработка входов------------------------------//

	// Инерционный фильтр дискретного Входа 0
    p->fIn0.input = (D_IN0 == 1) ? _IQ(1.0) : 0;
    p->fIn0.calc(&(p->fIn0));
	// Инерционный фильтр дискретного Входа 1
    p->fIn1.input = (D_IN1 == 1) ? _IQ(1.0) : 0;
    p->fIn1.calc(&(p->fIn1));
	// Инерционный фильтр дискретного Входа 2
    p->fIn2.input = (D_IN2 == 1) ? _IQ(1.0) : 0;
    p->fIn2.calc(&(p->fIn2));


	// Получаем состоЯние Входа 0 с учётом фильтрации
	if (p->fIn0.output > p->inputOn) p->in_bit.n0 = 1;
	if (p->fIn0.output < p->inputOff) p->in_bit.n0 = 0;
	// Получаем состоЯние Входа 1 с учётом фильтрации
	if (p->fIn1.output > p->inputOn) p->in_bit.n1 = 1;
	if (p->fIn1.output < p->inputOff) p->in_bit.n1 = 0;
	// Получаем состоЯние Входа 2 с учётом фильтрации
	if (p->fIn2.output > p->inputOn) p->in_bit.n2 = 1;
	if (p->fIn2.output < p->inputOff) p->in_bit.n2 = 0;

	//------------------------Обработка выходов------------------------------//

	// Выводим управлЯющее воздействие по Выходу 0
	if (p->out_bit.n0 == 1)
		D_OUT0_ON;
    else
    	D_OUT0_OFF;
	// Выводим управлЯющее воздействие по Выходу 1
	if (p->out_bit.n1 == 1)
		D_OUT1_ON;
    else
    	D_OUT1_OFF;
	// Выводим управлЯющее воздействие по Выходу 2
	if (p->out_bit.n2 == 1)
		D_OUT2_ON;
    else
    	D_OUT2_OFF;
}

/*@}*/

