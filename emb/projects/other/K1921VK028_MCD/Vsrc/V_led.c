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

 \file      Vled.c
 \brief     Управление светодиодами
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup led
 */

#include "DSP.h"
#include "main.h"

#define RUN_LED_TOGGLE	GPIOK->DATAOUTTGL = 1 << 15
#define RUN_LED_OFF		GPIOK->DATAOUTSET = 1 << 15
#define RUN_LED_ON		GPIOK->DATAOUTCLR = 1 << 15

#define FAULT_LED_TOGGLE	GPIOK->DATAOUTTGL = 1 << 14
#define FAULT_LED_OFF		GPIOK->DATAOUTSET = 1 << 14
#define FAULT_LED_ON		GPIOK->DATAOUTCLR = 1 << 14

void LED_init(Tled *p) {
	// В src/GpioPeripheralInit()
}


// Один диод мигает медленно в стопе и быстро в ране
// Другой мигает если авария и не мигает если не аварий
void LED_msCalc(Tled *p) {
	// Таймера считают себе и считают
	p->timerRunLed++;
	p->timerFaultLed++;

	// В зависимости от статуса привода выставляем периоды миганий
	if (drv_status.bit.running == 0) p->prdRunLed = 1000;
	else p->prdRunLed = 200;

	if (drv_status.bit.fault == 0) p->prdFaultLed = 0;
	else p->prdFaultLed = 200;

	// Если период ноль - не мигать вообще, иначе - переключать по периоду
	if (p->prdFaultLed == 0) FAULT_LED_OFF;
	else if (p->timerFaultLed >= p->prdFaultLed) {
		p->timerFaultLed = 0;
		FAULT_LED_TOGGLE;
	}

	if (p->prdRunLed == 0) RUN_LED_OFF;
	else if (p->timerRunLed >= p->prdRunLed) {
		p->timerRunLed = 0;
		RUN_LED_TOGGLE;
	}

}












