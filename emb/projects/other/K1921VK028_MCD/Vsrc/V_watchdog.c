/*
 * V_watchdog.c
 *
 *  Created on: 12 июл. 2018 г.
 *      Author: Dmitry
 */

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
