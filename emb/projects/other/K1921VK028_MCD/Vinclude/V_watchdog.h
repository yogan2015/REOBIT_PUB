/*
 * V_watchdog.h
 *
 *  Created on: 12 èþë. 2018 ã.
 *      Author: Dmitry
 */

#ifndef V_WATCHDOG_H_
#define V_WATCHDOG_H_

struct Swdog;
typedef volatile struct Swdog Twdog;

struct Swdog {
	void (*enable)();
	void (*disable)();
	void (*feed)();
	void (*resetCPU)();
};

void WDog_Enable();
void WDog_Disable();
void WDog_Feed();
void WDog_ResetSystem();

#define WDOG_DEFAULTS {.enable = WDog_Enable,\
					   .disable = WDog_Disable,\
					   .feed = WDog_Feed,\
					   .resetCPU = WDog_ResetSystem}

extern Twdog Watchdog;
#endif /* V_WATCHDOG_H_ */
