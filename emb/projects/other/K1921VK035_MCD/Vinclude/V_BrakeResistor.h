/*
 * V_BrakeResistor.h
 *
 *  Created on: 11 sept. 2018 г.
 *      Author: Lashkevich
 */

#ifndef VINCLUDE_V_BRAKE_RESISTOR_H_
#define VINCLUDE_V_BRAKE_RESISTOR_H_

#define BRAKE_R_STATE_ON	1
#define BRAKE_R_STATE_OFF	0


struct SbrakeResistor;
typedef volatile struct SbrakeResistor TbrakeResistor;

struct SbrakeResistor {
    _iq upperLevel;               // Напряжение для включения резистора
    _iq bottomLevel;              // Напряжение для выключения резистора
    Uint16 state;
    Uint16 enabled;

	void (*init)(TbrakeResistor*);
	void (*fastCalc)(TbrakeResistor*);
};

void BrakeResistor_Init (TbrakeResistor*);
void BrakeResistor_fastCalc (TbrakeResistor*);

#define     BRAKE_RESISTOR_DEFAULTS {.init = BrakeResistor_Init,\
						   .fastCalc = BrakeResistor_fastCalc}

extern TbrakeResistor brakeResistor;
#endif /* VINCLUDE_V_BRAKE_RESISTOR_H_ */
