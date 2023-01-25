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

 \file      V_MotorModel.h
 \brief     ������ ������� ����������������� (��. TMotorModel)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2017

 \defgroup  V_MotorModel.h ������ ������� ����������������� (��. TMotorModel)

 @{
*/


#ifndef V_MOTOR_MODEL_H
#define V_MOTOR_MODEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSP.h"
#include "V_IQmath.h"


// faults
#define MODEL_WRONG_PARAMETERS 1
#define MODEL_MAX_CURRENT_FAULT 2
#define MODEL_MAX_SPEED_FAULT 3

// motor types (for internal use)
#define MODEL_INDUCTION_MOTOR 0
#define MODEL_SYNC_MOTOR 1
#define MODEL_DC_MOTOR 2
#define MODEL_SRD_MOTOR 3

#define MOTOR_MODEL_PI 3.1415926f
#define MODEL_INV_2PI 0.15915494f

//��������� � ����������� ��������� � ���������������
struct Smotor
{
	int cmpr0, cmpr1, cmpr2, cmpr3; 							//!< ������� ��������� ���
	int tpr;													//!< ������ ���
	float inv_tpr; 												//!< 1/������ ���
	int dt;														//!< �������� �������� ������� � ������
	int dta, dtb, dtc, dtf;										//!< ������� �������� ������� �� ���������� ���
	float udc;													//!< ���������� ���
	float fia, fib, fic, fiav;									//!< ���������� ��� � ������� �����
	float ua, ub, uc;											//!< ������ ����������
	float isa, isb, isc, isd, isq;								//!< ������ ���� � ���� �����, �����
	float usa, usb, usd, usq, urd, urq;							//!< ���������� � ������������� ����
	float ird, irq, ira, irb;									//!< ���� � ������������� ����
	float omega,omega_rpm,torque;								//!< �������� (������� ��������), ������
	float torque_a, torque_b, torque_c;							//!< ������ �� ������ ���� (SRD)
	float j, inv_j;												//!< ������ ������� � �������� ��������
	float MechLoss;												//!< ������ �������
	float pp;													//!< ����� ��� �������
	float inv_pp;												//!<  1/pp
	float tetaR;												//!< ���� ��������� ������, �������������
	float tetaRM;												//!< ���� ��������� ������, ������������
	float cosTetaR, sinTetaR;									//!< cos � sin ���� ��������� ������
	float lm, lr, ls, lsd, lsq;									//!< ������������� - ��������, ������, �������
	float lmin, lmax, dls;										//!< ����������� ������������� (���-���), ������������ ������������� (���-���), ��������� ��������� �������������
	float inv_lmin;												//!<  1/lmin
	float l;													//!< ������� �������������
	float lp;													//!< ������������� � ����������� �������� ���������
	float ip, im;												//!< ���� � ����������� �������� ���������
	float wp, wm;												//!< ��������� ������� ������ ������� � ����������� �������� ���������
	float isat;													//!< ��� ���������
	float rr, rs;												//!< ������������� ����� � �������
	float ks, kr, km;											//!< ������������ ��������������
	float psa, psb, psc, psd, psq, prd, prq, pra, prb;			//!< ��������������� ������� � ������ � ������������� ���� ��� ������
	float ppsa, ppsb, ppsd, ppsq, pprd, pprq, ppra, pprb;		//!< ���������� ��������������� � ������������� ����
	float dpsa, dpsb, dpsd, dpsq, dprd, dprq;					//!< ����������� ��������������� � ������������� ����
	int type;													//!< ��� ���������
	float t, t2;												//!< ������ �������������, �������� ������� �������������
	float speedK;												//!< ����������� ������� ��������
	float iSenseK, ifSenseK, udSenseK, iSenseR, iSenseN;		//!< ����������� ������� ����, ������������� �������������� ��������� ��, ���������� ������ ������� ����� ��
	float RatedPower;											//!< ����������� �������� (���������� ��������, �� ������������ � ��������)
	float RatedSpeed;											//!< ����������� �������� (���������� ��������, �� ������������ � ��������)
	float RatedCurrent;											//!< ����������� ���
	float RatedFluxCurrent;										//!< ����������� ��� �����������
	int  iADCk, ifADCk;
	float QEPResolution;										//!< ����� ����� ���
	float m;													//!< ��������������� ������ ���������� ������
	float i_a, i_f, u_a, u_f, u_an;
	float r_a, r_f, r_ad, l_a, l_f;
	float _1_l_a, _1_l_f;
	float _1_lsd, _1_lsq;
	float dia, dif, dpa, dpf, pia, pif;
	float l_m,kf;												//!< ����������� ���� ��, ����� ��
	int dcm_pm;													//!< ����, ��� ��� � ��.
	int syncm_pm;												//!< ����, ��� �� � ��.
	float isPhaseA,isPhaseB,isPhaseC,isPhaseD;							//!< ��� ���� A,B,C
	float isPhaseA_prev,isPhaseB_prev,isPhaseC_prev;			//!< ��� ���� A,B,C ���������� ��������
	int CurrentInvertedFlag;									//!< ���� � ���, ��� ����� ���������� ��������� ���� ��� ���� ��� ������� ���� ����
	float cos30;												//!< cos 30 ��������
	float pisa,dprb,disa;										//!< ��������� ���� ������� �����, ���������� ��������������� ������ �� ��� ����, ���� ������� �� ��� �����
	float ThetaMax, PsiMax, IMax;								//!< ������������ ����, ����� � ��� SRM (��� ������������)
	float ThetaStep, PsiStep, IStep;							//!< ��� �� ����, ������ � ���� SRM (��� ������������)
	float ThetaStep_inv, PsiStep_inv, IStep_inv;				//!< �������� �������� ���� �� ����, ������ � ���� SRM (��� ������������)
	float power;												//!< �������� �� ����
	long iAtemp, iBtemp, iCtemp, iDtemp, Udc_temp, adcSpeedtemp;//!<��������� ���������� ��� ������� ������
	Uint16 hallSensor;											//!< ������ � ������� ��������� �����
	Uint16 hallSensorPrev;										//!< ������ � ������� ��������� ����� ����������
	float hallSensorOmegaPrev; 									//!< ��� �������� ��������� ������� �������� � ������� �����
};
typedef volatile struct Smotor Tmotor;


//��������� � ������� ������. �������� ����������� ����� �������� ���������� � ������� ���������.
//��������� ������� ���������, ������ ��� � �������� �������� �������, ������ ��������. ������ ��������� ��������.
struct SMotorModel
{
	Uint16 MotorType;		    //!< ��� ��������� � ������ (��� ����������)
	Uint16 MotorParametersNum;	//!< ����� ���������� ��������� �� �������
	Uint16 MotorParametersNumMax; // ������������ ��������� ����� ���������� �� �������
	Uint16 cmpr0;				//!< ������� ��������� ���
	Uint16 cmpr1;
	Uint16 cmpr2;
	Uint16 cmpr3;
	int16 InvertorEna;			//!< ���� ��������� ��������� (���� ���, �� ����� �� �����������)
	Uint16 tpr;					//!< ������ ���
	Uint16 dt;					//!< ������� ����� � ����� �������
	Uint16 adc_code_Speed;		//!< ���������� ��������
	Uint32 qepCounter;			//!< ��������� � ��������
	Uint16 hallSensor;			//!< ���������� ������ � ������� ��������� ����� (��� ������ ����)
	float hallSensorInterpAdd;  //!< ��� �������� ������������ ������� �����
	float hallSensorOmega; 		//!< ��� �������� ��������� ������� �������� � ������� �����
	Uint16 adc_code_iA;			//!< ���������� ����
	Uint16 adc_code_iB;
	Uint16 adc_code_iC;
	Uint16 adc_code_iD;
	Uint16 adc_code_Udc;		//!< ���������� �������� ���������� ����� ����������� ���� (���)
	int16 fault;				//!< ������ ������
	float load;					//!< ������ ��������
	float loadTmp;				//!< ������ �������� ��������� ����������
	void (*Init)(volatile struct SMotorModel*);        //!< Pointer to the init function
	void (*Execute)(volatile struct SMotorModel*);      //!<  Pointer to the update function
	Tmotor motorInternals;		//!< ���������� ���������� ��� ������� ������ ���������
};

typedef volatile struct SMotorModel TMotorModel;

#define MOTOR_MODEL_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,MotorModel_Init, MotorModel_Execute}

void MotorModel_Init(TMotorModel*);
void MotorModel_Execute(TMotorModel*);


#ifdef __cplusplus
}
#endif

#endif

/*@}*/


