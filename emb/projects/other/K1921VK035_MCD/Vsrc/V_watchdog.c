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

 \file      V_PWM_Module.c
 \brief     Модуль реализации векторной ШИМ (см. TPWM_Module)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup Twdog
 @{*/
#include "main.h"

Twdog Watchdog = WDOG_DEFAULTS;
// Разрешение вочдога
void WDog_Enable (){
	RCU->WDTCFG_bit.CLKSEL = 2;		// PLL
	RCU->WDTCFG_bit.DIVN = 1;		// PLL / 4
	RCU->WDTCFG_bit.DIVEN = 1;
	RCU->WDTCFG_bit.RSTDIS = 1;
	RCU->WDTCFG_bit.CLKEN = 1;

	WDT->LOCK = 0x1ACCE551;
	WDT->LOAD_bit.VAL = 100000;
	WDT->CTRL_bit.INTEN = 1;
	WDT->CTRL_bit.RESEN = 1;
	WDT->LOCK = 0x1ACCE551;

}

// Отключение вочдога
void WDog_Disable (){
	WDT->LOCK = 0x1ACCE551;
	WDT->CTRL_bit.INTEN = 0;
	WDT->CTRL_bit.RESEN = 0;
	WDT->LOCK = 0x1ACCE551;
}

// Сброс таймера вочдога
void WDog_Feed (){
	WDT->LOCK = 0x1ACCE551;
	WDT->LOAD_bit.VAL = 2500 * 3;		// 3 * 10 кГц прерывания
	WDT->LOCK = 0x1ACCE551;
}

// Перезагрузка проца вочдогом
void WDog_ResetSystem (){
	DINT;
	WDog_Enable();
	WDT->LOCK = 0x1ACCE551;
	WDT->LOAD_bit.VAL = 2;		// 2 такта
	WDT->LOCK = 0x1ACCE551;

	while(1);
}


/*@}*/
