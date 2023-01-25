/*!
    Copyright 2017 	�� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_DPR_eCAP.c
 \brief     ������ ������� ����������� ��������� ������ � �������������� ������� CAP TDPReCAP (��. TDPReCAP)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.1 03/01/2013

 */

/** \addtogroup V_DPR_eCAP */
/*@{*/

#include "DSP.h"              // Device Headerfile and Examples Include File
#include "V_IQmath.h"          // ���������� IQmath
#include "V_DPR_eCAP.h"       // ������������ ���� ������
#include "main.h"

extern TDrvParams drv_params;
//! �������������

//!������ CAP_3, CAP_4, CAP_5 ����������������
//!��� ������� ������� ����� ��������� ������������ � ����������
//!�������, � ����� ��������� ���������� �� ���� ��������.

//! \memberof TDPReCAP
void DPReCAP_Init(TDPReCAP* p) {

	//������������� ECAP1
	ECAP0->ECEINT = 0x0000;             	// Disable all capture interrupts
	ECAP0->ECCLR = 0xFFFF;              	// Clear all CAP interrupt flags
	ECAP0->ECCTL0_bit.CAPLDEN = 0;         // Disable CAP1-CAP4 register loads
	ECAP0->ECCTL1_bit.TSCTRSTOP = 0;       // Make sure the counter is stopped
	ECAP0->ECCTL0_bit.PRESCALE = 0;			// DIV1

	// Configure peripheral registers
	ECAP0->ECCTL1_bit.CONTOST = 0;      	// continuous mode
	ECAP0->ECCTL0_bit.CAP0POL = 0;          	// rising edge
	ECAP0->ECCTL0_bit.CAP1POL = 1;          	// falling edge
	ECAP0->ECCTL0_bit.CTRRST0 = 0;          	// absolute time stamp
	ECAP0->ECCTL0_bit.CTRRST1 = 0;          	// absolute time stamp
	ECAP0->ECCTL1_bit.STOPWRAP = 1;			// Wrap after Capture Event 2
//	ECAP0->ECCTL1_bit.SYNCI_EN = 1;         	// Enable sync in
	ECAP0->ECCTL1_bit.SYNCOSEL = 0;        	// Pass through
	ECAP0->ECCTL0_bit.CAPLDEN = 1;          	// Enable capture units



	ECAP0->ECCTL1_bit.TSCTRSTOP = 1;        	// Start Counter
	ECAP0->ECCTL1_bit.REARM = 0; // Has no effect (�� ����� ������� ���� �������)
	ECAP0->ECCTL0_bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	ECAP0->ECEINT_bit.CEVT0 = 1;            	// 1 events = interrupt
	ECAP0->ECEINT_bit.CEVT1 = 1;            	// 2 events = interrupt

	//������������� ECAP2
	ECAP1->ECEINT = 0x0000;             // Disable all capture interrupts
	ECAP1->ECCLR = 0xFFFF;              	// Clear all CAP interrupt flags
	ECAP1->ECCTL0_bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
	ECAP1->ECCTL1_bit.TSCTRSTOP = 0;        // Make sure the counter is stopped
	ECAP1->ECCTL0_bit.PRESCALE = 0;			// DIV1

	// Configure peripheral registers
	ECAP1->ECCTL1_bit.CONTOST = 0;      	// continuous mode
	ECAP1->ECCTL0_bit.CAP0POL = 0;          	// rising edge
	ECAP1->ECCTL0_bit.CAP1POL = 1;          	// falling edge
	ECAP1->ECCTL0_bit.CTRRST0 = 0;          	// absolute time stamp
	ECAP1->ECCTL0_bit.CTRRST1 = 0;          	// absolute time stamp
	ECAP1->ECCTL1_bit.STOPWRAP = 1;			// Wrap after Capture Event 2
//	ECAP1->ECCTL1_bit.SYNCI_EN = 1;         	// Enable sync in
	ECAP1->ECCTL1_bit.SYNCOSEL = 0;        	// Pass through
	ECAP1->ECCTL0_bit.CAPLDEN = 1;          	// Enable capture units

	ECAP1->ECCTL1_bit.TSCTRSTOP = 1;        	// Start Counter
	ECAP1->ECCTL1_bit.REARM = 0; // Has no effect (�� ����� ������� ���� �������)
	ECAP1->ECCTL0_bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	ECAP1->ECEINT_bit.CEVT0 = 1;            	// 1 events = interrupt
	ECAP1->ECEINT_bit.CEVT1 = 1;            	// 2 events = interrupt

	//������������� ECap3
	ECAP2->ECEINT = 0x0000;             // Disable all capture interrupts
	ECAP2->ECCLR = 0xFFFF;              	// Clear all CAP interrupt flags
	ECAP2->ECCTL0_bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
	ECAP2->ECCTL1_bit.TSCTRSTOP = 0;        // Make sure the counter is stopped
	ECAP2->ECCTL0_bit.PRESCALE = 0;			// DIV1

	// Configure peripheral registers
	ECAP2->ECCTL1_bit.CONTOST = 0;      	// continuous mode
	ECAP2->ECCTL0_bit.CAP0POL = 0;          	// rising edge
	ECAP2->ECCTL0_bit.CAP1POL = 1;          	// falling edge
	ECAP2->ECCTL0_bit.CTRRST0 = 0;          	// absolute time stamp
	ECAP2->ECCTL0_bit.CTRRST1 = 0;          	// absolute time stamp
	ECAP2->ECCTL1_bit.STOPWRAP = 1;			// Wrap after Capture Event 2
//	ECAP2->ECCTL1_bit.SYNCI_EN = 1;         	// Enable sync in
	ECAP2->ECCTL1_bit.SYNCOSEL = 0;        	// Pass through
	ECAP2->ECCTL0_bit.CAPLDEN = 1;          	// Enable capture units

	ECAP2->ECCTL1_bit.TSCTRSTOP = 1;        	// Start Counter
	ECAP2->ECCTL1_bit.REARM = 0; // Has no effect (�� ����� ������� ���� �������)
	ECAP2->ECCTL0_bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	ECAP2->ECEINT_bit.CEVT0 = 1;            	// 1 events = interrupt
	ECAP2->ECEINT_bit.CEVT1 = 1;            	// 2 events = interrupt

	p->TsNom = ((APB0BusClock / (drv_params.speed_nom * drv_params.p)) * 15*2);
	//����������� ��� ��������� ������� ����� ������� � �� � �������� � ��/���
	//60 - ��/���, 1000 �� � �������, 6 ����� �� ��. ������
	p->TsNomMilsec = (60.0*1000 / (6*drv_params.speed_nom * drv_params.p));

	DPReCAP_Angle6Calc(p);
	p->CAP_WrongEdgeCnt = 0;
	p->SimulatorOmega2IQ_factor=_IQ(60.0/(2*MOTOR_MODEL_PI*drv_params.speed_nom));

}


//! ����������� �������� ��������� � ������������� 60 ��������

//!����������� �������� ��������� ���������� ������ �� ������ ���� ������� �������
//!����� GPIO. ��������� �������� � ���������� Angle6.

//! \memberof TDPReCAP
void DPReCAP_Angle6Calc(TDPReCAP* p) {
	// �� ������ �������, ��������� ���������� �� ��������.
	//���� ����� �� �������, �� ��� ������� ����� ��������� � 10�,
	//�� ������� ���������� ����������� CAP, � ������� ��� ��������� ������ ���,
	//����� ���������� �������� � ���� ������� � 10� � � p->Angle6 ������� ������ ���������
	ECAP0->ECEINT = 0x0000;
	ECAP1->ECEINT = 0x0000;
	ECAP2->ECEINT = 0x0000;

	// ��������� ��� �� ��������� �����.
	p->HallCode = 0;

#if defined(HW_MCB3_SIMULATOR)
		p->HallCode = model.hallSensor;
#else
	if (p->UserDirection == 0) {
		if (GPIOM->DATA & (1 << 5))
			p->HallCode = p->HallCode + 1;
		if (GPIOM->DATA & (1 << 6))
			p->HallCode = p->HallCode + 2;
		if (GPIOM->DATA & (1 << 7))
			p->HallCode = p->HallCode + 4;
	} else {
		if (GPIOM->DATA & (1 << 5))
			p->HallCode = p->HallCode + 4;
		if (GPIOM->DATA & (1 << 6))
			p->HallCode = p->HallCode + 2;
		if (GPIOM->DATA & (1 << 7))
			p->HallCode = p->HallCode + 1;
	}
#endif




	switch (p->HallCode) {
	case 5: // 0
		p->Angle6 = 0;
		break;
	case 4: // 60
		p->Angle6 = _IQ(1.0 / 6.0);
		break;
	case 6: // 120
		p->Angle6 = _IQ(1.0 / 3.0);
		break;
	case 2: //180
		p->Angle6 = _IQ(1.0 / 2.0);
		break;
	case 3: // 240
		p->Angle6 = _IQ(2.0 / 3.0);
		break;
	case 1: // 300
		p->Angle6 = _IQ(5.0 / 6.0);
		break;
	}

	// ��������� ���������� �����.
	ECAP0->ECEINT = 6;
	ECAP1->ECEINT = 6;
	ECAP2->ECEINT = 6;
}

void DPReCAP_AngleErrorCalc(TDPReCAP* p) {
	long AngleDiff = 0;
	AngleDiff = (labs(
			((p->Angle6 - p->AnglePrev + _IQ(0.5)) & 0x00FFFFFF) - _IQ(0.5)))
			& 0x00FFFFFF;
	p->AnglePrev = p->Angle6;

	if (AngleDiff > _IQ(61.0 / 360)) { //���� ���� � �������� ���� ��������� ������, ��� �� 60 ��������, �� ������ �������
		p->WrongCodeCounter++;
		p->WrongCodeCounterPerSec++;

	}
}

//! ����������� �������� ��������� � ������ ������ ������������� �������� ���������

//!������������ �������� ��������� (� ������ ���� �������������)
//!���������� ���������� ������� ��������� Angle6, ���������� �������� DPReCAP_Angle6Calc.
//!������� "����������" ������� ��������� �� �������, ����� �� ����������� ����� ���� "��������"
//!����������� "����" (���������� Angle). ��� ����� ������������ ����������� ����� ����� ����� ������
//!����������� �������� � ������� ������� ��������� (PrevTs). ������, ��� �������� �������� ���������,
//!��������� ����� (� ������ ����� �������� ���������) ����� �������������� ����� �� �� ����� �����.
//!����� �������, � �������� ����������� �������� ��������� Angle6 ������������
//!�������, �������������� �� ������� 60*(������� �����/������).
//!���, � ������ ������� ������ � ������� ���������� Angle ����� Angle6. ����� ��������� ������ �������
//! Angle ������ ������ Angle6+60*(delta/Ts), ��� delta - ������� ����� � ������� ������� ���������� ������ � �������,
//! � Ts - ������, ����� ����� ����������� ����� ��������� ������� �������.
//! ������� ����� ��������� ����������� ��������, � ����� ��������� ���������������� ��������
//! AngleOffset � ��������������� �������� ���������.

//! \memberof TDPReCAP
void DPReCAP_AngleCalc(TDPReCAP* p) {
	Uint32 delta, Timer;
	Uint32 PrevTs;
	_iq Angle;
	_iq Angle6;

	// ��������� �������� ���������� �� ������ ������ �������
	Angle6 = p->Angle6;

#if (!defined(HW_MCB3_SIMULATOR))

	PrevTs = p->PrevTs;
	// �� ������ �������, ��������� ���������� �� ��������.
	ECAP0->ECEINT = 0x0000;
	ECAP1->ECEINT = 0x0000;
	ECAP2->ECEINT = 0x0000;



	// ��������� �������� ������ �� �������� �� ������ ������ ���������� ������.
	switch (p->DPReCAP_FLG1.bit.CAPnumber) {
	case 1:
		Timer = ECAP0->TSCTR;
		break;
	case 2:
		Timer = ECAP1->TSCTR;
		break;
	case 3:
		Timer = ECAP2->TSCTR;
		break;
	}

	// ���� �������� ����� ���� ��� ������ ��������������� �����, �� ���� �� ������������.
	if ((p->speed == 0) || (p->DPReCAP_FLG1.bit.AngleMode == 0)
			|| (p->Ts == 0)) {
		Angle = _IQ(1.0 / 12);
	} else {
		delta = Timer - PrevTs; // ������� ������� ������ � ������� �������� ���������� �������.
		Angle = _IQdiv(delta, p->Ts); // ������������ ����. ��������� �������� �������� � ������� "�����".
		if (Angle >= _IQ(1.0 / 6.0)) // ������������ ���� � �������� 1/6.
			Angle = _IQ(1.0 / 6.0);
	}
#else //���������
	Angle=_IQ(model.hallSensorInterpAdd * (1/(2*MOTOR_MODEL_PI)));//���������� ���� ��� ������������� ��� ������������� � ������ ��������� � ������ ������������
#endif

	if (p->DPReCAP_FLG1.bit.Dir == 1)
		Angle = _IQ(1.0/6.0) - Angle;

	if (p->UserDirection) //���������������� �������� �����������
		Angle = -Angle + _IQ(1.0/6);

	p->Angle = Angle6 + Angle + p->AngleOffset;

	p->Angle &= 0x00FFFFFF;


	// ��������� ���������� �����.
	ECAP0->ECEINT = 6;
	ECAP1->ECEINT = 6;
	ECAP2->ECEINT = 6;
}

//! ������� ������� ��������

//!��� ������� �������� ������������ ���������� Tspeed,
//!������� ������������ ����� ����� ����� ��������� ������� ������� ���������
//!������������ �� ������ � ���� �� ������. ���, ��������, �������� ����� ����������� � ��������� �������
//!������ CAP3, ����� ����� ��������� � ����������� ������� CAP4 � �.�.
//!�� ������ ����� �������, ����������� �������� � ��������������� ���������� TsNom
//!�������������� �������� ��������.

//! \memberof TDPReCAP
void DPReCAP_SpeedCalc(TDPReCAP* p) {
#if (!defined(HW_MCB3_SIMULATOR))

	_iq speed;

	// ������� �������� � ������������� �������� ������������ �����������.
	if ((p->Tspeed != 0) && (p->DPReCAP_FLG1.bit.ZeroFLG == 0)) {

		// ���� �������� ����������� � ����������� �� �����������.
		if (p->DPReCAP_FLG1.bit.Dir == 0)
			speed = _IQdiv(p->TsNom, p->Tspeed);
		else
			speed = -_IQdiv(p->TsNom, p->Tspeed);
		if (p->UserDirection) { //�������� �������������
			speed = -speed;
		}
	} else {
		speed = 0;
	}

	p->speed = speed;


	DINT;//����� ��� ����������������� ��������� � ���������� DPReCAP_FLG1 (����� �� ���������� ������������ � ���������� �������)
	// ��������� ��������, ���� ��������� �������� ����� ����� ����� ��������� ���������.
	if (p->milsec > p->milsecFIX) {
		p->speed = 0;
		p->DPReCAP_FLG1.bit.ZeroFLG = 1;
//		p->cnt1 = 0; // ���� �������� ��� ����� � hold'�. ����� �� ����, ������ ��� �����.
	}
	EINT;

	DINT;//����� ��� ����������������� ��������� � ���������� DPReCAP_FLG1 (����� �� ���������� ������������ � ���������� �������)

	// ��� �������� ������ ��������, ��������� ������������ ����.
	if ((labs(p->speed)) <= (p->speedMIN))
		p->DPReCAP_FLG1.bit.SpeedMinFLG = 0;
	else
		p->DPReCAP_FLG1.bit.SpeedMinFLG = 1;
	EINT;

#else //���������
	p->speed=p->SimulatorOmega2IQ_factor*model.hallSensorOmega;//������� �������� ��� ������������� � ������ ��������� � ������ ������������
#endif
}

//! �������, ���������� � ���������� �� ������������ � ���������� ������ ������ ������� 1

//! � ������� ������������ ����� ������� ������ CAP � ���������� Timer1.
//! ������ �� ����� ��������� ��� ���������� - p->Ts, ����� ����� ����� ���������� ��������,
//!����������� ��� ������������� �������� ���������, � ����������  p->Tspeed,
//!����� ����� ����� �������� ������ � ���� �� ������, ���������� ��� ������� ��������.
//! \memberof TDPReCAP
void DPReCAP_CAP1Calc(TDPReCAP* p) {
	Uint32 Timer=0;
	if (p->cnt >= 2) {
		p->cnt=2;
		p->HelpCalc(p);

		// � ����������� �� ������ ����������� CAP ���������� ����������� ��������.
		if (p->DPReCAP_FLG1.bit.CAPnumber == 3)
			p->DPReCAP_FLG1.bit.Dir = 0;
		if (p->DPReCAP_FLG1.bit.CAPnumber == 2)
			p->DPReCAP_FLG1.bit.Dir = 1;
		if (p->DPReCAP_FLG1.bit.CAPnumber == 1) {
			if (p->DPReCAP_FLG1.bit.PrevDir == 0)
				p->DPReCAP_FLG1.bit.Dir = 1;
			else
				p->DPReCAP_FLG1.bit.Dir = 0;
		}
		if (p->DPReCAP_FLG1.bit.Dir != p->DPReCAP_FLG1.bit.PrevDir) {
			p->DPReCAP_FLG1.bit.PrevDir = p->DPReCAP_FLG1.bit.Dir;
			p->cnt2 = 1;
		}

	    if (ECAP0->ECFLG_bit.CEVT0==1)//����� �����
	    {
	            Timer = ECAP0->CAP0;
	    }
	    if (ECAP0->ECFLG_bit.CEVT1==1)//����� ����
	    {
	            Timer = ECAP0->CAP1;
	    }

		// ������� ������� ��� ������� ���� � ��������.
		p->Ts = (Timer - p->PrevTs) * 6;
		p->PrevTs = Timer;

		p->Tspeed = Timer - p->PrevTspeed1;
		p->PrevTspeed1 = Timer;

	} else {
		p->Ts = 0;
		p->Tspeed = 0;
	}


	p->cnt++;
	p->milsec = 0;
	p->DPReCAP_FLG1.bit.CAPnumber = 1;

}

//! �������, ���������� � ���������� �� ������������ � ���������� ������ ������ ������� 2

//! � ������� ������������ ����� ������� ������ CAP � ���������� Timer1.
//! ������ �� ����� ��������� ��� ���������� - p->Ts, ����� ����� ����� ���������� ��������,
//!����������� ��� ������������� �������� ���������, � ����������  p->Tspeed,
//!����� ����� ����� �������� ������ � ���� �� ������, ���������� ��� ������� ��������.
//! \memberof TDPReCAP
void DPReCAP_CAP2Calc(TDPReCAP* p) {
	Uint32 Timer=0;
	if (p->cnt >= 2) {
		p->cnt=2;
		p->HelpCalc(p);

		// � ����������� �� ������ ����������� CAP ���������� ����������� ��������.
		if (p->DPReCAP_FLG1.bit.CAPnumber == 1)
			p->DPReCAP_FLG1.bit.Dir = 0;
		if (p->DPReCAP_FLG1.bit.CAPnumber == 3)
			p->DPReCAP_FLG1.bit.Dir = 1;
		if (p->DPReCAP_FLG1.bit.CAPnumber == 2) {
			if (p->DPReCAP_FLG1.bit.PrevDir == 0)
				p->DPReCAP_FLG1.bit.Dir = 1;
			else
				p->DPReCAP_FLG1.bit.Dir = 0;
		}

		if (p->DPReCAP_FLG1.bit.Dir != p->DPReCAP_FLG1.bit.PrevDir) {
			p->DPReCAP_FLG1.bit.PrevDir = p->DPReCAP_FLG1.bit.Dir;
			p->cnt2 = 1;
		}

	    if (ECAP1->ECFLG_bit.CEVT0==1)
	    {
	            Timer = ECAP1->CAP0;
	    }
	    if (ECAP1->ECFLG_bit.CEVT1==1)
	    {
	            Timer = ECAP1->CAP1;
	    }

		// ������� ������� ��� ������� ���� � ��������.
		p->Ts = (Timer - p->PrevTs) * 6;
		p->PrevTs = Timer;

		p->Tspeed = Timer - p->PrevTspeed2;
		p->PrevTspeed2 = Timer;

	} else {
		p->Ts = 0;
		p->Tspeed = 0;
	}


	p->cnt++;
	p->milsec = 0;
	p->DPReCAP_FLG1.bit.CAPnumber = 2;

}

//! �������, ���������� � ���������� �� ������������ � ���������� ������ ������ ������� 3

//! � ������� ������������ ����� ������� ������ CAP � ���������� Timer1.
//! ������ �� ����� ��������� ��� ���������� - p->Ts, ����� ����� ����� ���������� ��������,
//!����������� ��� ������������� �������� ���������, � ����������  p->Tspeed,
//!����� ����� ����� �������� ������ � ���� �� ������, ���������� ��� ������� ��������.
//! \memberof TDPReCAP
void DPReCAP_CAP3Calc(TDPReCAP* p) {
	Uint32 Timer;
	if (p->cnt >= 2) {
		p->cnt=2;
		p->HelpCalc(p);

		// � ����������� �� ������ ����������� CAP ���������� ����������� ��������.
		if (p->DPReCAP_FLG1.bit.CAPnumber == 2)
			p->DPReCAP_FLG1.bit.Dir = 0;
		if (p->DPReCAP_FLG1.bit.CAPnumber == 1)
			p->DPReCAP_FLG1.bit.Dir = 1;
		if (p->DPReCAP_FLG1.bit.CAPnumber == 3) {
			if (p->DPReCAP_FLG1.bit.PrevDir == 0)
				p->DPReCAP_FLG1.bit.Dir = 1;
			else
				p->DPReCAP_FLG1.bit.Dir = 0;
		}

		if (p->DPReCAP_FLG1.bit.Dir != p->DPReCAP_FLG1.bit.PrevDir) {
			p->DPReCAP_FLG1.bit.PrevDir = p->DPReCAP_FLG1.bit.Dir;
			p->cnt2 = 1;
		}

	    if (ECAP2->ECFLG_bit.CEVT0==1)
	    {
	            Timer = ECAP2->CAP0;
	    }
	    if (ECAP2->ECFLG_bit.CEVT1==1)
	    {
	            Timer = ECAP2->CAP1;
	    }


		// ������� ������� ��� ������� ���� � ��������.
		p->Ts = (Timer - p->PrevTs) * 6;
		p->PrevTs = Timer;

		p->Tspeed = Timer - p->PrevTspeed3;
		p->PrevTspeed3 = Timer;

	} else {
		p->Ts = 0;
		p->Tspeed = 0;
	}


	p->cnt++;
	p->milsec = 0;
	p->DPReCAP_FLG1.bit.CAPnumber = 3;
}

void DPReCAP_calc_10k(TDPReCAP* p) {

	DINT;
	if (p->CAPCalcEna1==0){
		p->CAPCalcEna1=1;
		ECAP0->ECCLR_bit.CEVT0 = 1;
		ECAP0->ECCLR_bit.CEVT1 = 1;
		ECAP0->ECCLR_bit.INT = 1;
	}
	if (p->CAPCalcEna2==0){
		p->CAPCalcEna2=1;
		ECAP1->ECCLR_bit.CEVT0 = 1;
		ECAP1->ECCLR_bit.CEVT1 = 1;
		ECAP1->ECCLR_bit.INT = 1;
	}
	if (p->CAPCalcEna3==0){
		p->CAPCalcEna3=1;
		ECAP2->ECCLR_bit.CEVT0 = 1;
		ECAP2->ECCLR_bit.CEVT1 = 1;
		ECAP2->ECCLR_bit.INT = 1;
	}
	EINT;

}


void DPReCAP_HelpCalc(TDPReCAP* p) {
	// �������� �������� � ���������� ����,
	// ���� ����� ����� ����� ��������� ������ ���������.
	if (p->milsec > p->milsecFIX) {
		p->speed = 0;
		p->DPReCAP_FLG1.bit.ZeroFLG = 1;
	} else {
		p->DPReCAP_FLG1.bit.ZeroFLG = 0;
	}
}

void DPReCAP_SlowCalc(TDPReCAP* p) {
//������� ��� ������� T=Ts/Tfiltra ��� - Tfiltra ���������� ������� �������
//	p->AngleFilter_1_T=_IQdiv(FAST_CALC_TS,AngleFilterT);
}


void DPReCAP_msCalc(TDPReCAP* p) {
	p->milsec++;//������� ������� ���������� �����
	if (p->milsecREF != p->milsecPrevREF) {
		p->milsecFIX=p->milsecREF;
		p->speedMinREF = _IQdiv(p->TsNomMilsec, p->milsecFIX);
		p->milsecPrevREF = p->milsecREF;
	}

	p->ErrorLevelTimeCounterBig++;
	if (p->ErrorLevelTimeCounterBig > 10000) {
		p->ErrorLevel = p->ErrorLevelCounter;
		p->ErrorLevelCounter = 0;
		p->ErrorLevelTimeCounterBig = 0;
	}

	p->ErrorLevelTimeCounter++;
	if (p->ErrorLevelTimeCounter > 1000) {
		if (p->WrongCodeCounterPerSec > p->WrongCodeCounterLimitPerSec){
			p->SensorFault = 1;
		} else
			p->SensorFault = 0;
		p->WrongCodeCounterPerSec=0;
		p->ErrorLevelTimeCounter = 0;
	}


	if (p->CAP_WrongEdgeCntPrev != p->CAP_WrongEdgeCnt)
		p->ErrorLevelCounter++;
	p->CAP_WrongEdgeCntPrev = p->CAP_WrongEdgeCnt;

}

/*@}*/
