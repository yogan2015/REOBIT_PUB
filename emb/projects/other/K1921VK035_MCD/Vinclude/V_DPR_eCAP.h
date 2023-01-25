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
 
 \file      V_DPR_eCAP.h
 \brief     ������ ������� �������� � ��������� �� ��� �������� �� ��������� �����.
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

*/

#ifndef V_DPR_ECAP_H
#define V_DPR_ECAP_H

#ifdef __cplusplus
extern "C"
{
#endif

struct SDPReCAPFLG1_BITS  							// bits
  {
Uint16 AngleMode:
    1;			// 0		����� ������� ����: 0 - 6 ��������, 1 - ������������
Uint16 SpeedMode:
    1;			// 1		����� ������� ��������: 0 - �� ������� �������, 1 - �� ������ �����
Uint16 Dir:
    1;				// 2       	����������� ��������: 0 - �� �������, 1 -  ������.
Uint16 PrevDir:
    1;			// 3       	����������� ��������: 0 - �� �������, 1 -  ������.
Uint16 CAPnumber:
    2;			// 4-5 		����� eCAP, �� �������� ���� ���������� ����������.
Uint16 ZeroFLG:
    1;			// 6		���� ��������� ��������
Uint16 SpeedMinFLG:
    1;		// 7

Uint16 firstlaunch1:1;  //!< 1		FLAG: ������ ��������� � ���������� eCAP1.
Uint16 firstlaunch2:1;	//!< 2		FLAG: ������ ��������� � ���������� eCAP2.
Uint16 firstlaunch3:1;	//!< 3       	FLAG: ������ ��������� � ���������� eCAP3.
Uint16 rsvd:
	5;				// 8-15		reserved;
  };

  union SDPReCAP_FLG1
  {
    Uint16              all;
    struct SDPReCAPFLG1_BITS  bit;
  };

  struct SDPReCAP
  {
	int16 enabled;
	int16 initialized;
	int16 HallCode;			//������� ��� ��������� �� �������� �����
    Uint32 Ts;				// ������ ��� ������� ������������������ ����
    Uint32 Tspeed;			// ������ ��� ������ ��������
    Uint32 TsNom;			// ������, �������������� ����������� ��������
    Uint32 TsNomMilsec;		// ������, �������������� ����������� �������� ��� ������������ 1 ��
    Uint32 PrevTs;			// ���������� �������� ������� ��� ������� ����.
    _iq speed;				// ����������� ��������

    _iq speedMIN;			// ������� ����������� ��������
    _iq speedMinREF;		// ��������, ��������������� ������� ��� ��������� ��������
    _iq Angle;				// ����������� ����������������� ����
    _iq Angle6;				// ����������� �������������� ����
    _iq AnglePrev;			// ����������� �������������� ���� ����������

    Uint32 cnt;				// ������� ����� ���������� � ������� ����� (������ 2 �� �������).
    Uint32 cnt2;			// ������� ���������� �������� �������.
    Uint32 milsec;			// ����� � �� � ������� ������� ������� �����
    Uint32 milsecFIX;		// ������������� ������� ��� ��������� ��������
    Uint32 milsecREF;		// ������� ��� ��������� ��������
    Uint32 milsecPrevREF;	// ���������� �������� ������� ��� ��������� ��������

    Uint32 PrevTspeed;		// ���������� �������� ������� ��� ������� ��������
    Uint32 PrevTspeed1;		// ���������� �������� ������� ��� ������� �������� �� ������� �.
    Uint32 PrevTspeed2;		// ���������� �������� ������� ��� ������� �������� �� ������� B.
    Uint32 PrevTspeed3;		// ���������� �������� ������� ��� ������� �������� �� ������� C.


	int16 CAPCalcEna1;
	int16 CAPCalcEna2;
	int16 CAPCalcEna3;

	int16 CAP_WrongEdgeCnt;
	int16 CAP_WrongEdgeCnt1;
	int16 CAP_WrongEdgeCnt2;
	int16 CAP_WrongEdgeCnt3;
	int16 CAP_WrongEdgeCntPrev;

	Uint16 WrongCodeCounter;
	Uint16 WrongCodeCounterPerSec;
	Uint16 WrongCodeCounterLimitPerSec;
	int32 AngleOffset;


	int16 ErrorLevel;
	int16 ErrorLevelCounter;
	int16 ErrorLevelTimeCounterBig;
	int16 ErrorLevelTimeCounter;
	int16 SensorFault;
	Uint16 UserDirection;//���������������� �������� �����������

	float SimulatorOmega2IQ_factor;

	union SDPReCAP_FLG1	DPReCAP_FLG1;

    void (*Init)(volatile struct SDPReCAP*);
    void (*AngleCalc)(volatile struct SDPReCAP*);
    void (*Angle6Calc)(volatile struct SDPReCAP*);
    void (*AngleErrorCalc)(volatile struct SDPReCAP*);
    void (*SpeedCalc)(volatile struct SDPReCAP*);
    void (*CAP1Calc)(volatile struct SDPReCAP*);
    void (*CAP2Calc)(volatile struct SDPReCAP*);
    void (*CAP3Calc)(volatile struct SDPReCAP*);
    void (*HelpCalc)(volatile struct SDPReCAP*);
    void (*slow_calc)(volatile struct SDPReCAP*);
    void (*ms_calc)(volatile struct SDPReCAP*);
    void (*calc_10k)(volatile struct SDPReCAP*);
  };
  typedef volatile struct SDPReCAP TDPReCAP;

  /******************************************************************************
   ������������� ���������  �� ���������
  ******************************************************************************/
#define DPRECAP_DEFAULTS  {\
    .Init = DPReCAP_Init, \
    .AngleCalc = DPReCAP_AngleCalc, \
    .Angle6Calc = DPReCAP_Angle6Calc, \
    .AngleErrorCalc = DPReCAP_AngleErrorCalc, \
    .SpeedCalc = DPReCAP_SpeedCalc, \
    .CAP1Calc = DPReCAP_CAP1Calc, \
    .CAP2Calc = DPReCAP_CAP2Calc, \
    .CAP3Calc = DPReCAP_CAP3Calc, \
    .HelpCalc = DPReCAP_HelpCalc, \
    .slow_calc = DPReCAP_SlowCalc, \
    .ms_calc = DPReCAP_msCalc, \
	.calc_10k = DPReCAP_calc_10k\
  }

  /******************************************************************************
  ��������� �������������.
  ******************************************************************************/
  void DPReCAP_Init(TDPReCAP*);

  /******************************************************************************
   ��������� ������� ����.
  ******************************************************************************/
  void DPReCAP_Angle6Calc(TDPReCAP*);

  /******************************************************************************
   ��������� ���������� ����� ���������� ��������� ����.
  ******************************************************************************/
  void DPReCAP_AngleErrorCalc(TDPReCAP*);

  /******************************************************************************
   ��������� ������� ������������������ ����.
  ******************************************************************************/
  void DPReCAP_AngleCalc(TDPReCAP*);

  /******************************************************************************
   ��������� ������� ��������.
  ******************************************************************************/
  void DPReCAP_SpeedCalc(TDPReCAP*);

  /******************************************************************************
  ������ ���������� 1
  ******************************************************************************/
  void DPReCAP_CAP1Calc(TDPReCAP*);

  /******************************************************************************
  ������ ���������� 2
  ******************************************************************************/
  void DPReCAP_CAP2Calc(TDPReCAP*);

  /******************************************************************************
  ������ ���������� 3
  ******************************************************************************/
  void DPReCAP_CAP3Calc(TDPReCAP*);

  /******************************************************************************
  ��������������� ������, ����� ��� ���� ����������
  ******************************************************************************/
  void DPReCAP_HelpCalc(TDPReCAP*);


  /******************************************************************************
  ��������������� ������ � ����
  ******************************************************************************/
  void DPReCAP_SlowCalc(TDPReCAP*);

  /******************************************************************************
  �������������� ������
  ******************************************************************************/
  void DPReCAP_msCalc(TDPReCAP*);


  void DPReCAP_calc_10k(TDPReCAP* p);
#ifdef __cplusplus
}
#endif	// extern "C"

#endif	// V_DPR_ECAP_H
