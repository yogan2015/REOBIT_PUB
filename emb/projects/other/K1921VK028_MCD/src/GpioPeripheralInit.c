/*
 * GpioPeripheralInit.c
 *
 * ��������� GPIO-��� ��� ���������, ������������ � �������
 *  Created on: 15 ���. 2019 �.
 *      Author: Dmitry
 */
#include "main.h"

void gpioPeripheralInit (void) {
	// ���������� ������ ���� ����� �� �����
	GPIOA->DENSET = 0xFFFF;
	GPIOB->DENSET = 0xFFFF;
	GPIOC->DENSET = 0xFFFF;
	GPIOD->DENSET = 0xFFFF;
	GPIOE->DENSET = 0xFFFF;
	GPIOF->DENSET = 0xFFFF;
	GPIOG->DENSET = 0xFFFF;
	GPIOH->DENSET = 0xFFFF;
	GPIOJ->DENSET = 0xFFFF;
	GPIOK->DENSET = 0xFFFF;
	GPIOL->DENSET = 0xFFFF;
	GPIOM->DENSET = 0xFFFF;

	// LEDs: K14 / K15
	GPIOK->DATAOUTCLR = GPIO_PIN_14 | GPIO_PIN_15;
	GPIOK->OUTENSET = GPIO_PIN_14 | GPIO_PIN_15;
	GPIOK->ALTFUNCCLR = GPIO_PIN_14 | GPIO_PIN_15;

	// Buttons: D10 / D11
	GPIOD->OUTENCLR = GPIO_PIN_10 | GPIO_PIN_11;
	GPIOD->ALTFUNCCLR = GPIO_PIN_10 | GPIO_PIN_11;

	// SPI: A0 / A1 / A2 / A3
	GPIOA->ALTFUNCNUM0_bit.PIN0 = 1;		// SPI0_CLK
	GPIOA->ALTFUNCNUM0_bit.PIN1 = 1;		// SPI0_RX
	GPIOA->ALTFUNCNUM0_bit.PIN2 = 1;		// SPI0_TX
	GPIOA->ALTFUNCNUM0_bit.PIN3 = 1;		// SPI0_FSS
	GPIOA->ALTFUNCSET = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;


	// QEP0: A12 / A13 / A14 / A15
	GPIOA->ALTFUNCNUM1_bit.PIN12 = 1;		// QEP_A
	GPIOA->ALTFUNCNUM1_bit.PIN13 = 1;		// QEP_B
	GPIOA->ALTFUNCNUM1_bit.PIN14 = 1;		// QEP_I
	GPIOA->ALTFUNCNUM1_bit.PIN15 = 1;		// QEP_S
	GPIOA->ALTFUNCSET = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;

	// PWM TZ0/1/2: B3 / B4 / B5
	GPIOB->ALTFUNCNUM0_bit.PIN3 = 1;		// TZ_0
	GPIOB->ALTFUNCNUM0_bit.PIN4 = 1;		// TZ_1
	GPIOB->ALTFUNCNUM0_bit.PIN5 = 1;		// TZ_2
	GPIOB->ALTFUNCSET = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;

	// PWM TZ3/4/5: D4 / D5 / D6
	GPIOD->ALTFUNCNUM0_bit.PIN4 = 2;		// TZ_3
	GPIOD->ALTFUNCNUM0_bit.PIN5 = 2;		// TZ_4
	GPIOD->ALTFUNCNUM0_bit.PIN6 = 2;		// TZ_5
	GPIOD->ALTFUNCSET = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;

	// PWM0/1/2/3: B6 / B7 / B8 / B9 / B10 / B11 / B12 / B13
	GPIOB->ALTFUNCNUM0_bit.PIN6 = 1;	// PWM0_A
	GPIOB->ALTFUNCNUM0_bit.PIN7 = 1;	// PWM0_B
	GPIOB->ALTFUNCNUM1_bit.PIN8 = 1;	// PWM1_A
	GPIOB->ALTFUNCNUM1_bit.PIN9 = 1;	// PWM1_B
	GPIOB->ALTFUNCNUM1_bit.PIN10 = 1;	// PWM2_A
	GPIOB->ALTFUNCNUM1_bit.PIN11 = 1;	// PWM2_B
	GPIOB->ALTFUNCNUM1_bit.PIN12 = 1;	// PWM3_A
	GPIOB->ALTFUNCNUM1_bit.PIN13 = 1;	// PWM3_B
	GPIOB->ALTFUNCSET = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
						GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;

#ifdef CAN_1_ENABLE
    // CAN0: C12 / C13
    GPIOC->ALTFUNCNUM1_bit.PIN12 = 1;   // CAN0_TX
    GPIOC->ALTFUNCNUM1_bit.PIN13 = 1;   // CAN0_RX
    GPIOC->ALTFUNCSET = GPIO_PIN_12 | GPIO_PIN_13;
#endif

#ifdef CAN_2_ENABLE
    // CAN1: C14 / C15
    GPIOC->ALTFUNCNUM1_bit.PIN14 = 1;   // CAN0_TX
    GPIOC->ALTFUNCNUM1_bit.PIN15 = 1;   // CAN0_RX
    GPIOC->ALTFUNCSET = GPIO_PIN_14 | GPIO_PIN_15;
#endif

#ifdef CANTORS_ENA
	// UART2: �8 / �9 (USB-UART)
	GPIOC->ALTFUNCNUM1_bit.PIN8 = 2;	// UART2_RX
	GPIOC->ALTFUNCNUM1_bit.PIN9 = 2;	// UART2_TX
	GPIOC->ALTFUNCSET = GPIO_PIN_8 | GPIO_PIN_9;
#endif

#ifdef MODBUS_ENA
	// UART3: E8 / E9 + M2  (modbus rx/tx)
	GPIOE->ALTFUNCNUM1_bit.PIN8 = 4;	// UART3_RX
	GPIOE->ALTFUNCNUM1_bit.PIN9 = 4;	// UART3_TX
	GPIOE->ALTFUNCSET = GPIO_PIN_8 | GPIO_PIN_9;

	GPIOM->ALTFUNCCLR = GPIO_PIN_2;
	GPIOM->OUTENSET = GPIO_PIN_2;
#endif


	// UdControl: B14
	GPIOB->ALTFUNCCLR = GPIO_PIN_14;
	GPIOB->DATAOUTCLR = GPIO_PIN_14;
	GPIOB->OUTENSET = GPIO_PIN_14;

	// DI: D1 / D2 / M14
	GPIOD->ALTFUNCCLR = GPIO_PIN_1 | GPIO_PIN_2;
	GPIOD->DATAOUTCLR = GPIO_PIN_1 | GPIO_PIN_2;
	GPIOD->OUTENSET = GPIO_PIN_1 | GPIO_PIN_2;

	GPIOM->ALTFUNCCLR = GPIO_PIN_14;
	GPIOM->DATAOUTCLR = GPIO_PIN_14;
	GPIOM->OUTENSET = GPIO_PIN_14;

	// DO: M10 / M11 / M13
	GPIOM->OUTENCLR = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_13;
	GPIOM->ALTFUNCCLR = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_13;

	// CAP: M5 / M6 / M7
	GPIOM->ALTFUNCNUM0_bit.PIN5 = 2;
	GPIOM->ALTFUNCNUM0_bit.PIN6 = 2;
	GPIOM->ALTFUNCNUM0_bit.PIN7 = 2;
	GPIOM->ALTFUNCSET = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;

	// Fan Control: B13
	GPIOB->ALTFUNCCLR = GPIO_PIN_13;
	GPIOB->DATAOUTCLR = GPIO_PIN_13;
	GPIOB->OUTENSET = GPIO_PIN_13;



}
