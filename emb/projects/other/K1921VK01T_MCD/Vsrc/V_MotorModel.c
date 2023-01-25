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

 \file      V_MotorModel.�
 \brief     ������ ������� ����������������� (��. TMotorModel)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2017

 \addtogroup V_MotorModel
 @{ */


#include "V_MotorModel.h"
#include "math.h"
#include "V_MotorParams.h"
#include <V_IQmath.h>
#include "main.h"

#define ADC_MAX_VALUE 4095
#define ADC_HALF_VALUE 2047

//������� ���������� "����" ��� ���
int MotorModel_fastrand() {
	static unsigned long g_seed;
	g_seed = (214013 * g_seed + 2531011);
	return ((g_seed >> 16) & 0x3) -2;
}

//������������� ���������� ������
void MotorModel_Init(TMotorModel *p) {
	Uint16 MotorParametersValid=0;
	int i=0;

	p->hallSensor = 1;		//������������� ������� ����� ��� ������� ����
	p->motorInternals.dt = p->dt;			//������������ �������� �������
	p->motorInternals.tpr = p->tpr;		//������ ���
	p->motorInternals.cmpr0 = p->motorInternals.tpr-p->cmpr0;	//������� ��������� ���. � ���������, ������ ��� ��� �������� ������ ���
	p->motorInternals.cmpr1 = p->motorInternals.tpr-p->cmpr1;
	p->motorInternals.cmpr2 = p->motorInternals.tpr-p->cmpr2;
	p->motorInternals.cmpr3 = p->motorInternals.tpr-p->cmpr3;
	//��� ������������� ������ (��������� � ���������� 10���)
	p->motorInternals.t = 1.0 / 10000;

	p->motorInternals.cos30 = cos(30.0/360*MOTOR_MODEL_PI*2);
	p->fault = 0;				//��� ������ ������
	p->motorInternals.udSenseK = ADC_HALF_VALUE/540.0;
	p->motorInternals.type=p->MotorType&0x7;//�������� ��� ��������� ���� � ��������� ���������� ���������

	// ����� ���c��������� ������ ������ ���������� ��������� �� �������
	// ����� ��� ������ �� �������� ������ ��������������� �������� �������
	// ������ //
	if (p->motorInternals.type==MODEL_INDUCTION_MOTOR){
			// ���� r_s, l_s, j ������������ ����� ����, ������ ���������� �� ������� ����� ����������.
			// ������ ���������� ����� - ��������� ������� � �������, � ����� ������, ��� � ���� �������� ������.
			while ((IMDATA[i].r_s != 0) && (IMDATA[i].l_s != 0) && (IMDATA[i].j != 0) && (i < 50)) i++;}
	else if (p->motorInternals.type==MODEL_SYNC_MOTOR){
			// ���� l_sd, l_sq, j ������������ ����� ����, ������ ���������� �� ������� ����� ����������.
			// ������ ���������� ����� - ��������� ������� � �������, � ����� ������, ��� � ���� �������� ������.
			while ((SMDATA[i].l_sd != 0) && (SMDATA[i].l_sq != 0) && (SMDATA[i].j != 0) && (i < 50)) i++;}
	else if (p->motorInternals.type==MODEL_DC_MOTOR){
			// ���� r_a, l_a, j ������������ ����� ����, ������ ���������� �� ������� ����� ����������.
			// ������ ���������� ����� - ��������� ������� � �������, � ����� ������, ��� � ���� �������� ������.
			while ((DCMDATA[i].r_a != 0) && (DCMDATA[i].l_a != 0) && (DCMDATA[i].j != 0) && (i < 50)) i++;}
	else if (p->motorInternals.type==MODEL_SRD_MOTOR){
			// ���� r_s, pp, j ������������ ����� ����, ������ ���������� �� ������� ����� ����������.
			// ������ ���������� ����� - ��������� ������� � �������, � ����� ������, ��� � ���� �������� ������.
			while ((SRMDATA[i].r_s != 0) && (SRMDATA[i].pp != 0) && (SRMDATA[i].j != 0) && (i < 50)) i++;}
	p->MotorParametersNumMax = i;
	// ����� //

	// �������� ���������� ���������� ������ ������ ����������
	// ������ //
	if ((p->MotorParametersNum > 0) && (p->MotorParametersNum <= p->MotorParametersNumMax)) MotorParametersValid = 1;
	else
	{
		if (p->MotorParametersNum > p->MotorParametersNumMax){
			p->MotorParametersNum = p->MotorParametersNumMax;
			MotorParametersValid = 1;}
		else if (p->MotorParametersNum == 0) MotorParametersValid = 0;
	}
	// ����� //

	// ������������� ���������� ����������
	if (p->motorInternals.type==MODEL_INDUCTION_MOTOR){//��� ��������� - �����������
		if (MotorParametersValid){
			p->motorInternals.ls = IMDATA[p->MotorParametersNum-1].l_s;		//������������� �������
			p->motorInternals.lr = IMDATA[p->MotorParametersNum-1].l_r;		//������������� ������
			p->motorInternals.lm = IMDATA[p->MotorParametersNum-1].l_m;		//�������� �������������
			//��������: � ���������� ls � lr ������ ���� ������ ������������� ������� � ������. ������ � ���������� ��������� ���������� ������������� ���������
			//������� � ������, ������� ������, ��� l_m. ����� �������� ������ ������������� ������� ��� ������, ����� ��������� l_m � l_s ��� l_r ��������������.
			//�������� ������������ ����� ��������������:
			if ((p->motorInternals.ls < p->motorInternals.lm) || (p->motorInternals.lr < p->motorInternals.lm))
				p->fault = MODEL_WRONG_PARAMETERS;
			p->motorInternals.rs = IMDATA[p->MotorParametersNum-1].r_s;				//������������� �������
			p->motorInternals.rr = IMDATA[p->MotorParametersNum-1].r_r;				//������������� ������
			p->motorInternals.pp = IMDATA[p->MotorParametersNum-1].pp;				//����� ��� �������
			p->motorInternals.j = IMDATA[p->MotorParametersNum-1].j;				//������ �������
			p->motorInternals.QEPResolution = IMDATA[p->MotorParametersNum-1].qep;	//���������� ��������
			p->motorInternals.RatedPower = IMDATA[p->MotorParametersNum-1].RatedPower; //����������� �������� (���������� ��������, �� ������������ � ��������)
			p->motorInternals.RatedSpeed = IMDATA[p->MotorParametersNum-1].RatedSpeed; //����������� �������� (���������� ��������, �� ������������ � ��������)
			p->motorInternals.RatedCurrent = IMDATA[p->MotorParametersNum-1].RatedCurrent; //����������� ����������� ���
			p->motorInternals.MechLoss = p->motorInternals.j * 10; 		//������������ ������
		}

		// ������������� ������������� � ��������� �������, ���������� �� ��������� ���������

		p->motorInternals.speedK = 60/(4*MOTOR_MODEL_PI); //����������� ������� ��������

		p->motorInternals.iADCk = p->motorInternals.RatedCurrent*1.414*3; 			// ��������� ����������� ��� ����� ����������� ��������� ������������ ����
		p->motorInternals.iSenseK = (ADC_HALF_VALUE*1.0)/p->motorInternals.iADCk;	//����������� ������� ���� ��� �������������� ���� � ������� � ��� ���

		p->motorInternals.ks = -(p->motorInternals.lr/1000.0) / (p->motorInternals.lm/1000.0 * p->motorInternals.lm/1000.0 - p->motorInternals.ls/1000.0 * p->motorInternals.lr/1000.0);	//������������ �������� ������� ��������������
		p->motorInternals.kr = -(p->motorInternals.ls/1000.0) / (p->motorInternals.lm/1000.0 * p->motorInternals.lm/1000.0 - p->motorInternals.ls/1000.0 * p->motorInternals.lr/1000.0);
		p->motorInternals.km = (p->motorInternals.lm/1000.0) / (p->motorInternals.lm/1000.0 * p->motorInternals.lm/1000.0 - p->motorInternals.ls/1000.0 * p->motorInternals.lr/1000.0);

		p->motorInternals.psa = 0;				//��������������� ������� � ���� �����,����
		p->motorInternals.psb = 0;
	}

	if (p->motorInternals.type==MODEL_SYNC_MOTOR){//��� ��������� - ����������
		if (MotorParametersValid){
			p->motorInternals.r_f = SMDATA[p->MotorParametersNum-1].r_f;			//������������� ��
			p->motorInternals.l_f = SMDATA[p->MotorParametersNum-1].l_f;			//������������� ��
			p->motorInternals.l_m = SMDATA[p->MotorParametersNum-1].l_m;			//����������� ���������� ������ (�������� �������������)
			p->motorInternals.rs = SMDATA[p->MotorParametersNum-1].r_s;				//������������� �������
			p->motorInternals.lsd = SMDATA[p->MotorParametersNum-1].l_sd;			//������������� �������
			p->motorInternals.lsq = SMDATA[p->MotorParametersNum-1].l_sq;			//������������� �������
			p->motorInternals.pp = SMDATA[p->MotorParametersNum-1].pp;				//����� ��� �������
			p->motorInternals.j = SMDATA[p->MotorParametersNum-1].j;				//������ �������
			p->motorInternals.QEPResolution = SMDATA[p->MotorParametersNum-1].qep;	//���������� ��������
			p->motorInternals.m = SMDATA[p->MotorParametersNum-1].psi_pm;			//��������������� ������ ����� ������ ���������� ��������
			p->motorInternals.RatedPower = SMDATA[p->MotorParametersNum-1].RatedPower; //����������� �������� (���������� ��������, �� ������������ � ��������)
			p->motorInternals.RatedSpeed = SMDATA[p->MotorParametersNum-1].RatedSpeed; //����������� �������� (���������� ��������, �� ������������ � ��������)
			p->motorInternals.RatedCurrent = SMDATA[p->MotorParametersNum-1].RatedCurrent; //����������� ����������� ���
			p->motorInternals.RatedFluxCurrent = SMDATA[p->MotorParametersNum-1].RatedFluxCurrent; //����������� ��� ��
			p->motorInternals.MechLoss = p->motorInternals.j * 10; 		//������������ ������
		}
		// ������������� ������������� � ��������� �������, ���������� �� ��������� ���������

		p->motorInternals.speedK = 60/(4*MOTOR_MODEL_PI); //����������� ������� ��������

		p->motorInternals.iADCk = p->motorInternals.RatedCurrent*1.414*3; 			// ��������� ����������� ��� ����� ����������� ��������� ������������ ����
		p->motorInternals.iSenseK = (ADC_HALF_VALUE*1.0)/p->motorInternals.iADCk;	//����������� ������� ���� ��� �������������� ���� � ������� � ��� ���

		p->motorInternals.ifADCk = p->motorInternals.RatedFluxCurrent*3; 			// ��������� ����������� ��� ����� ������������ ������������ ���� ��
		p->motorInternals.ifSenseK = (ADC_HALF_VALUE*1.0)/p->motorInternals.ifADCk;	//����������� ������� ���� ��� �������������� ���� � ������� � ��� ���

		p->motorInternals._1_lsd = 1.0/(p->motorInternals.lsd/1000);			//�������� ��������
		p->motorInternals._1_lsq = 1.0/(p->motorInternals.lsq/1000);			//�������� ��������

		if (p->motorInternals.l_f != 0)	//� �������� �����������
		{
			p->motorInternals._1_l_f = 1.0/(p->motorInternals.l_f/1000); // �������� �������� (������������ �� ��� � ��)
			p->motorInternals.syncm_pm = 0;
			p->motorInternals.m = 0;			//��������������� ������ ����� ����
		}
		else							//� ����������� ���������
		{
			p->motorInternals.syncm_pm = 1;
			p->motorInternals.ifADCk = 0; // ��������� ����������� ��� ���� ��
		}

		p->motorInternals.psd = p->motorInternals.m;//��������������� ������� � ���� d,q
		p->motorInternals.psq = 0;
		p->motorInternals.i_f = 0;
	}

	if (p->motorInternals.type==MODEL_DC_MOTOR){//��� ��������� - ������������ ��������� ����������� ����
		if (MotorParametersValid){
			p->motorInternals.pp = 2;				//����� ��� ������� (�������� �� �����, ������ ����� �� �����)
			p->motorInternals.r_f = DCMDATA[p->MotorParametersNum-1].r_f;			//������������� ��
			p->motorInternals.l_f = DCMDATA[p->MotorParametersNum-1].l_f;			//������������� ��
			p->motorInternals.l_m = DCMDATA[p->MotorParametersNum-1].l_m;			//����������� ���������� ������ (�������� �������������)
			p->motorInternals.r_a = DCMDATA[p->MotorParametersNum-1].r_a;			//������������� �����
			p->motorInternals.l_a = DCMDATA[p->MotorParametersNum-1].l_a;			//������������� �����
			p->motorInternals.RatedFluxCurrent = DCMDATA[p->MotorParametersNum-1].RatedFluxCurrent;			//����������� ��� ��
			p->motorInternals.RatedCurrent = DCMDATA[p->MotorParametersNum-1].RatedCurrent;			//����������� ��� �����
			p->motorInternals.j = DCMDATA[p->MotorParametersNum-1].j;				//������ �������
			p->motorInternals.QEPResolution = DCMDATA[p->MotorParametersNum-1].qep;	//���������� ��������
			p->motorInternals.RatedPower = DCMDATA[p->MotorParametersNum-1].RatedPower; //����������� �������� (���������� ��������, �� ������������ � ��������)
			p->motorInternals.RatedSpeed = DCMDATA[p->MotorParametersNum-1].RatedSpeed; //����������� �������� (���������� ��������, �� ������������ � ��������)
			p->motorInternals.MechLoss = p->motorInternals.j * 10; 					//������������ ������
		}
		// ������������� ������������� � ��������� �������, ���������� �� ��������� ���������

		p->motorInternals.speedK = 60/(4*MOTOR_MODEL_PI); //����������� ������� ��������
		p->motorInternals.iADCk = (ADC_HALF_VALUE*1.0)/p->motorInternals.iSenseK; // ��������� ����������� ��� ���� ��

		p->motorInternals.iADCk = p->motorInternals.RatedCurrent*1.414*3; 			// ��������� ����������� ��� ����� ����������� ��������� ������������ ����
		p->motorInternals.iSenseK = (ADC_HALF_VALUE*1.0)/p->motorInternals.iADCk;	//����������� ������� ���� ��� �������������� ���� � ������� � ��� ���

		p->motorInternals.ifADCk = p->motorInternals.RatedFluxCurrent*3; 			// ��������� ����������� ��� ����� ������������ ������������ ���� ��
		p->motorInternals.ifSenseK = (ADC_MAX_VALUE*1.0)/p->motorInternals.ifADCk;	//����������� ������� ���� ��� �������������� ���� � ������� � ��� ���

		p->motorInternals.r_ad = 0;

		p->motorInternals._1_l_a = 1.0/(p->motorInternals.l_a/1000); // �������� �������� (������������ �� ��� � ��)
		if (p->motorInternals.l_f != 0)	// ���� ��� � �������� �����������
		{
			// ����������� ����������� ������������ ��� ������ ��
			p->motorInternals._1_l_f = 1.0/(p->motorInternals.l_f/1000); // �������� �������� (������������ �� ��� � ��)
			p->motorInternals.ifADCk = (ADC_HALF_VALUE*1.0)/p->motorInternals.ifSenseK; // ��������� ����������� ��� ���� ��
			p->motorInternals.dcm_pm = 0;	// ���������� ���� ����������� �� ��
		}
		else	// ��� � ����������� ���������
		{
			// � ���� ������ ������� ����������� �� �������
			p->motorInternals.dcm_pm = 1; // ������������� ���� ����������� �� ��
			p->motorInternals.ifADCk = 0; // ��������� ����������� ��� ���� �� ������������� ����
		}
		p->motorInternals.i_a = 0;					//��� ��
		p->motorInternals.i_f = 0;					//����� �����
	}

	if (p->motorInternals.type==MODEL_SRD_MOTOR){//��� ��������� - ��� (Switched Reluctance Drive, SRD)
		if (MotorParametersValid){
			p->motorInternals.rs = SRMDATA[p->MotorParametersNum-1].r_s;				//������������� ������ �������
			p->motorInternals.pp = SRMDATA[p->MotorParametersNum-1].pp;				//����� ��� �������
			p->motorInternals.j = SRMDATA[p->MotorParametersNum-1].j;					//������ �������
			p->motorInternals.QEPResolution = SRMDATA[p->MotorParametersNum-1].qep;	//���������� ��������
			p->motorInternals.speedK = SRMDATA[p->MotorParametersNum-1].sk;			//����������� ������� ��������
			p->motorInternals.RatedPower = SRMDATA[p->MotorParametersNum-1].RatedPower; //����������� �������� (���������� ��������, �� ������������ � ��������)
			p->motorInternals.RatedSpeed = SRMDATA[p->MotorParametersNum-1].RatedSpeed; //����������� �������� (���������� ��������, �� ������������ � ��������)
			p->motorInternals.RatedCurrent = SRMDATA[p->MotorParametersNum-1].RatedCurrent; //����������� ����������� ��� (���������� ��������, �� ������������ � ��������)
			p->motorInternals.MechLoss = p->motorInternals.j * 10; 				//������������ ������
		}
		// ������������� ������������� � ��������� �������, ���������� �� ��������� ���������

		p->motorInternals.inv_pp=1.0/p->motorInternals.pp;

		p->motorInternals.iADCk = p->motorInternals.RatedCurrent*1.414*3; 			// ��������� ����������� ��� ����� ����������� ��������� ������������ ����
		p->motorInternals.iSenseK = (ADC_MAX_VALUE*1.0)/p->motorInternals.iADCk;	//����������� ������� ���� ��� �������������� ���� � ������� � ��� ���

		p->motorInternals.ifADCk = p->motorInternals.RatedFluxCurrent*3; 			// ��������� ����������� ��� ����� ������������ ������������ ���� ��
		p->motorInternals.ifSenseK = (ADC_MAX_VALUE*1.0)/p->motorInternals.ifADCk;	//����������� ������� ���� ��� �������������� ���� � ������� � ��� ���


		p->motorInternals.isPhaseA=0;	//������ ����
		p->motorInternals.isPhaseB=0;
		p->motorInternals.isPhaseC=0;
		p->motorInternals.psa=0;	//��������������� ���
		p->motorInternals.psb=0;
		p->motorInternals.psc=0;

		//��������� ���������� �������� (����� ��������� �����) ������ ��������������
		volatile int Psi_I_s_resolution = 0;
		volatile int Psi_I_r_resolution = 0;
		//� ��������� ����� ������ ���� ������������� ��������, ��� ������ ��������� �������
		while ((Psi_I_s[Psi_I_s_resolution].i >= 0) && (Psi_I_s_resolution < 50)) Psi_I_s_resolution++;
		while ((Psi_I_r[Psi_I_r_resolution].i >= 0) && (Psi_I_r_resolution < 50)) Psi_I_r_resolution++;
		Psi_I_s_resolution--;	//��������� �� 1, ����� �������� ���������� ��������
		Psi_I_r_resolution--;	//��������� �� 1, ����� �������� ���������� ��������

		//������ �������� ��������� ���������� (����, ���, ���������������) � ���� ������������� �� ���
		p->motorInternals.ThetaMax = 2*MOTOR_MODEL_PI;										//�������� ���� - 0..2��
		p->motorInternals.IMax = Psi_I_s[Psi_I_s_resolution].i;				//�������, ��� ������������ ��� ����� � ��������� ����� ������ ��� �������������� ���������
		p->motorInternals.PsiMax = Psi_I_s[Psi_I_s_resolution].psi;			//������������ ����� ����� � ��������� ����� ������ ��� �������������� ���������
		p->motorInternals.ThetaStep = p->motorInternals.ThetaMax/(SRD_SURFACE_RESOLUTION+1);	//���������� ����. �����, � ������� �� ���� � ������, ������� �� SRD_SURFACE_RESOLUTION+1,
																	//�.�. ������ ���������, � �� ������ ���� ���� ���������� �������� ����� ��� ����� 0 � 2��. �.�. ����� 2�� � ����� ��������
		p->motorInternals.ThetaStep_inv = 1.0/p->motorInternals.ThetaStep;
		p->motorInternals.IStep = p->motorInternals.IMax/SRD_SURFACE_RESOLUTION;				//���������� ����
		p->motorInternals.IStep_inv = 1.0/p->motorInternals.IStep;
		p->motorInternals.PsiStep = p->motorInternals.PsiMax/SRD_SURFACE_RESOLUTION;			//���������� ������
		p->motorInternals.PsiStep_inv = 1.0/p->motorInternals.PsiStep;
//		p->motorInternals.j = srm_j[p->MotorParametersNum-1];		//��� �������� ���� (������)
//		p->motorInternals.MechLoss = p->motorInternals.j * 10; 		//������������ ������

		//��������� ������ �������������� ��� ������ ���������� ������������, ������������� ����������� psi=f(i,theta)
		for (int i=0; i<SRD_SURFACE_RESOLUTION+1; i++)
		{
			float TmpI = i*p->motorInternals.IStep;
			Psi_I_s_acc[i] = MotorModel_FluxCubicInterpolation (TmpI, Psi_I_s, Psi_I_s_resolution);	//� ��������, ��� ��� ���������� ������ ����� ������, �.�. �� ��� ��� �� ��������� �����������, �
			Psi_I_r_acc[i] = MotorModel_FluxCubicInterpolation (TmpI, Psi_I_r, Psi_I_r_resolution);	//���� ������ ����� �� ������������. ����� ����� ������ �������� ��������� ���������� � ���������� ������
			for (int t=0; t<SRD_SURFACE_RESOLUTION+1; t++)
			{
				float TmpTheta = t*p->motorInternals.ThetaStep;
				Psi_ITheta[i][t] = (Psi_I_s_acc[i] + Psi_I_r_acc[i])*0.5 - (Psi_I_s_acc[i] - Psi_I_r_acc[i])*0.5*_IQtoF(_IQcos(_IQ(TmpTheta)));	//��� ����������� ���� ����� ������� ���������, ��� � ������� ������ �� ���������
			}
		}

		//��������� ����������� i=f(psi,theta) �� psi=f(i,theta)
		for (int t=0; t<SRD_SURFACE_RESOLUTION+1; t++)
		{
			//����� �� ���� ����� �� ��, �������������� ����������� ����� ��� �������� ����������� ���� psi=f(i) -> i=f(psi)
			for (int n=0; n<SRD_SURFACE_RESOLUTION+1; n++)
			{
				float TmpPsi = n*p->motorInternals.PsiStep;
				if (TmpPsi <= Psi_ITheta[0][t])	//������������ ������� (�� ������ ������)
				{
					I_PsiTheta[n][t] = 0;
				}
				else if (TmpPsi >= Psi_ITheta[SRD_SURFACE_RESOLUTION][t])	//������������ ��������
				{
					I_PsiTheta[n][t] = p->motorInternals.IMax;	//�� ������ �������������� ��� ������� ���� ����� ������ �� ���� ������������� ������ (����� �� ������ � ������������� ���������). �������, ����� ���������
				}
				else	//� ����������� �� ������, ������������� �������.
				{
					for (int i = 1; i < SRD_SURFACE_RESOLUTION+1; i++)	//���� ������� � �������� ������ psi=f(i), ���� ����� ���������� ����� p
					{
						if (Psi_ITheta[i][t] >= TmpPsi)	//����� � ��������� ����� ������ ���������, ������ ������ � ������ �������
						{
							I_PsiTheta[n][t] = p->motorInternals.IStep*i - (Psi_ITheta[i][t] - TmpPsi)*p->motorInternals.IStep/(Psi_ITheta[i][t] - Psi_ITheta[i-1][t]);
							break;
						}
					}
				}
			}
		}

		//��������� ����������� ������� M=f(i,theta)
		for (int t=0; t<SRD_SURFACE_RESOLUTION+1; t++)
		{
			float WcoPlus = 0;								//��������� ��� ���� Theta+
			float WcoMinus = 0;								//��������� ��� ���� Theta-
			M_ITheta[0][t] = 0;								//������ ��� ������� ���� � ����� ���� - �������
			float PsiPlus_prev = 0;
			float PsiMinus_prev = 0;

			//���� �������� ����� �� ���������, ��� ���� ����������� ��� ������������� �������� ������������ �� ���� � ������ theta=0 � theta=2Pi
			int tPlus = t+1;
			if (tPlus > SRD_SURFACE_RESOLUTION)
				tPlus -= (SRD_SURFACE_RESOLUTION+1);
			int tMinus = t-1;
			if (tMinus < 0)
				tMinus += (SRD_SURFACE_RESOLUTION+1);
			for (int i=1; i<SRD_SURFACE_RESOLUTION+1; i++)
			{
				//���� ��������������� ��� �������� ���� � ���� ���� ������ � ���� ������ (�� SRD_DELTA_THETA) ��������� ��� ������ �������� ������������
				float PsiPlus = Psi_ITheta[i][t] + (Psi_ITheta[i][tPlus] - Psi_ITheta[i][t])*SRD_DELTA_THETA*p->motorInternals.ThetaStep_inv;
				float PsiMinus = Psi_ITheta[i][t] - (Psi_ITheta[i][t] - Psi_ITheta[i][tMinus])*SRD_DELTA_THETA*p->motorInternals.ThetaStep_inv;
				//������� ��������� - �������� ��������������� �� ���� (������� ��������)
				WcoPlus += (PsiPlus + PsiPlus_prev)*0.5*p->motorInternals.IStep;
				WcoMinus += (PsiMinus + PsiMinus_prev)*0.5*p->motorInternals.IStep;
				PsiPlus_prev = PsiPlus;
				PsiMinus_prev = PsiMinus;
				//PhaseTorque = p->motorInternals.pp*(p->motorInternals.wm-p->motorInternals.wp)*50;	// 50 = inv_0.02 dTeta				��� ���� � �������� ��������
				M_ITheta[i][t] = p->motorInternals.pp*(WcoPlus - WcoMinus)*SRD_DELTA_THETA_INV*0.5;		//������� ������, ��� ����������� ���������
			}
		}
	}

	// ������ ������������� ������, ���������� �� �������
	p->motorInternals.inv_tpr=1.0/p->motorInternals.tpr;
	p->motorInternals.inv_j=1.0/p->motorInternals.j;

	p->motorInternals.t2 = p->motorInternals.t / 2;				//�������� ���� �������������

	// ��������� ���������� ���������
	p->motorInternals.tetaR = 0;			//���� ��������� ������ �������������
	p->motorInternals.tetaRM = 0;				//���� ��������� ������ ������������
	p->motorInternals.omega = 0;						//��������, ���/�
	p->motorInternals.prd = 0;					//��������������� ������ � ���� d,q
	p->motorInternals.prq = 0;
	p->motorInternals.isa = 0;						//���� ������� � ���� �����,����
	p->motorInternals.isb = 0;
	p->motorInternals.ira = 0;						//���� ������ � ���� �����,����
	p->motorInternals.irb = 0;
	p->motorInternals.ird = 0;						//���� ������ � ���� d,q
	p->motorInternals.irq = 0;


}

//������ ���������� ��� ����������� ���������
void MotorModel_calcU42Phase(TMotorModel *p) {
	if (p->InvertorEna) { //�������� �������
		// ������ ���������� �������
		// ���������� ������� �������� ������� �� ���������� ���� � ����������� �� ����� ����
		if (p->motorInternals.i_a > 0) {
			if (p->motorInternals.cmpr0 > p->motorInternals.dt)
				p->motorInternals.dta = -p->motorInternals.dt;
			else
				p->motorInternals.dta = -p->motorInternals.cmpr0;
		} else {
			if ((p->motorInternals.cmpr0 + p->motorInternals.dt) < p->motorInternals.tpr)
				p->motorInternals.dta = +p->motorInternals.dt;
			else
				p->motorInternals.dta = p->motorInternals.tpr - p->motorInternals.cmpr0;
		}
		if (p->motorInternals.i_a < 0) {
			if (p->motorInternals.cmpr1 > p->motorInternals.dt)
				p->motorInternals.dtb = -p->motorInternals.dt;
			else
				p->motorInternals.dtb = -p->motorInternals.cmpr1;
		} else {
			if ((p->motorInternals.cmpr1 + p->motorInternals.dt) < p->motorInternals.tpr)
				p->motorInternals.dtb = +p->motorInternals.dt;
			else
				p->motorInternals.dtb = p->motorInternals.tpr - p->motorInternals.cmpr1;
		}
		//������ ����������� � ������ ������� �������� �������
		p->motorInternals.fia = p->motorInternals.udc * (p->motorInternals.cmpr0 + (p->motorInternals.dta >> 1)) / p->motorInternals.tpr;
		p->motorInternals.fib = p->motorInternals.udc * (p->motorInternals.cmpr1 + (p->motorInternals.dtb >> 1)) / p->motorInternals.tpr;
		p->motorInternals.u_a = p->motorInternals.fia - p->motorInternals.fib;//���������� �� �����

		if (p->motorInternals.i_f > 0) {
			if (p->motorInternals.cmpr2 > p->motorInternals.dt)
				p->motorInternals.dtc = -p->motorInternals.dt;
			else
				p->motorInternals.dtc = -p->motorInternals.cmpr2;
		} else {
			if ((p->motorInternals.cmpr2 + p->motorInternals.dt) < p->motorInternals.tpr)
				p->motorInternals.dtc = +p->motorInternals.dt;
			else
				p->motorInternals.dtc = p->motorInternals.tpr - p->motorInternals.cmpr2;
		}
		//������ ����������� � ������ ������� �������� �������
		p->motorInternals.fic = p->motorInternals.udc * (p->motorInternals.cmpr2 + (p->motorInternals.dtc >> 1)) / p->motorInternals.tpr;
		p->motorInternals.u_f = p->motorInternals.fic;//���������� �� ��


		p->motorInternals.isPhaseA_prev = p->motorInternals.isPhaseA;
		p->motorInternals.CurrentInvertedFlag = 0;
	} else
	{//�������� ��������
/*
		if (p->motorInternals.isPhaseA > 0)
			p->motorInternals.u_a = -p->motorInternals.udc;
		else
			p->motorInternals.u_a = p->motorInternals.udc;
*/
		p->motorInternals.u_a = 0;

		p->motorInternals.fia = 0;
		p->motorInternals.fib = 0;
		p->motorInternals.fic = 0;

		if (p->motorInternals.isPhaseA * p->motorInternals.isPhaseA_prev < 0)		//��� ������ ���� ���� � ������� ���������� ���������
			p->motorInternals.CurrentInvertedFlag = 7;//����, ��� ��� ������������ ���� ��������� ����

		if (p->motorInternals.CurrentInvertedFlag == 7) {//������������ ������� ����������, � � ������ ��� ��������� ������� ����
			p->motorInternals.u_a=0;
		}
		p->motorInternals.u_f = 0;//���������� �� ����� ����
	}


}

//������ ���������� ��� ����������� ���������
void MotorModel_calcU43Phase(TMotorModel *p) {
	if (p->InvertorEna) { //�������� �������
		// ������ ���������� �������
		// ���������� ������� �������� ������� �� ���������� ���� � ����������� �� ����� ����
		if (p->motorInternals.isPhaseA > 0) {
			if (p->motorInternals.cmpr0 > p->motorInternals.dt)
				p->motorInternals.dta = -p->motorInternals.dt;
			else
				p->motorInternals.dta = -p->motorInternals.cmpr0;
		} else {
			if ((p->motorInternals.cmpr0 + p->motorInternals.dt) < p->motorInternals.tpr)
				p->motorInternals.dta = +p->motorInternals.dt;
			else
				p->motorInternals.dta = p->motorInternals.tpr - p->motorInternals.cmpr0;
		}
		if (p->motorInternals.isPhaseB > 0) {
			if (p->motorInternals.cmpr1 > p->motorInternals.dt)
				p->motorInternals.dtb = -p->motorInternals.dt;
			else
				p->motorInternals.dtb = -p->motorInternals.cmpr1;
		} else {
			if ((p->motorInternals.cmpr1 + p->motorInternals.dt) < p->motorInternals.tpr)
				p->motorInternals.dtb = +p->motorInternals.dt;
			else
				p->motorInternals.dtb = p->motorInternals.tpr - p->motorInternals.cmpr1;
		}
		if (p->motorInternals.isPhaseC > 0) {
			if (p->motorInternals.cmpr2 > p->motorInternals.dt)
				p->motorInternals.dtc = -p->motorInternals.dt;
			else
				p->motorInternals.dtc = -p->motorInternals.cmpr2;
		} else {
			if ((p->motorInternals.cmpr2 + p->motorInternals.dt) < p->motorInternals.tpr)
				p->motorInternals.dtc = +p->motorInternals.dt;
			else
				p->motorInternals.dtc = p->motorInternals.tpr - p->motorInternals.cmpr2;
		}

		//������ ����������� � ������ ������� �������� �������
		p->motorInternals.fia = p->motorInternals.udc * (p->motorInternals.cmpr0 + (p->motorInternals.dta >> 1)) / p->motorInternals.tpr;
		p->motorInternals.fib = p->motorInternals.udc * (p->motorInternals.cmpr1 + (p->motorInternals.dtb >> 1)) / p->motorInternals.tpr;
		p->motorInternals.fic = p->motorInternals.udc * (p->motorInternals.cmpr2 + (p->motorInternals.dtc >> 1)) / p->motorInternals.tpr;
		p->motorInternals.fiav = (p->motorInternals.fia + p->motorInternals.fib + p->motorInternals.fic) / 3;		//��������� ������� �����
		p->motorInternals.ua = p->motorInternals.fia - p->motorInternals.fiav;					//����������
		p->motorInternals.ub = p->motorInternals.fib - p->motorInternals.fiav;
		p->motorInternals.uc = p->motorInternals.fic - p->motorInternals.fiav;

		//���������� � ���� �����,����
		p->motorInternals.usa = p->motorInternals.ua;
		p->motorInternals.usb = 0.577350269 * p->motorInternals.ua + 1.154700538 * p->motorInternals.ub;

		p->motorInternals.isPhaseA_prev = p->motorInternals.isPhaseA;
		p->motorInternals.isPhaseB_prev = p->motorInternals.isPhaseB;
		p->motorInternals.isPhaseC_prev = p->motorInternals.isPhaseC;
		p->motorInternals.CurrentInvertedFlag = 0;

	} else { //�������� ��������
		//������ ���������� ����������, ������� ��������� � ���������, ����� �������� ��������.
		//������� ��� �������� ��� �� � �������� ������ ��������� ������������ ���� ��������, ���� �������� �� �������� �� ����,
		//� ����� "��������" ���� ���������. ��� ���������� �� ����������, �������, �� �����, ��� �� ������ ������.

		if (p->motorInternals.isPhaseA > 0)
			p->motorInternals.fia = 0;
		else
			p->motorInternals.fia = p->motorInternals.udc;

		if (p->motorInternals.isPhaseB > 0)
			p->motorInternals.fib = 0;
		else
			p->motorInternals.fib = p->motorInternals.udc;

		if (p->motorInternals.isPhaseC > 0)
			p->motorInternals.fic = 0;
		else
			p->motorInternals.fic = p->motorInternals.udc;

		if (p->motorInternals.isPhaseA * p->motorInternals.isPhaseA_prev < 0)		//��� ������ ���� ���� � ������� ���������� ���������
			p->motorInternals.CurrentInvertedFlag |= 1;

		if (p->motorInternals.isPhaseB * p->motorInternals.isPhaseB_prev < 0)		//��� ������ ���� ���� � ������� ���������� ���������
			p->motorInternals.CurrentInvertedFlag |= 2;

		if (p->motorInternals.isPhaseC * p->motorInternals.isPhaseC_prev < 0)		//��� ������ ���� ���� � ������� ���������� ���������
			p->motorInternals.CurrentInvertedFlag |= 4;

		if (p->motorInternals.CurrentInvertedFlag == 7) {
			p->motorInternals.fia = 0;
			p->motorInternals.fib = 0;
			p->motorInternals.fic = 0;
		}

		p->motorInternals.fiav = (p->motorInternals.fia + p->motorInternals.fib + p->motorInternals.fic) * (1.0/3);		//��������� ������� �����
		p->motorInternals.ua = p->motorInternals.fia - p->motorInternals.fiav;					//����������
		p->motorInternals.ub = p->motorInternals.fib - p->motorInternals.fiav;
		p->motorInternals.uc = p->motorInternals.fic - p->motorInternals.fiav;

		//���������� � ���� �����,����
		p->motorInternals.usa = p->motorInternals.ua;
		p->motorInternals.usb = 0.577350269 * p->motorInternals.ua + 1.154700538 * p->motorInternals.ub;
	}
}

//������ ���������� ��� �� ����������� ���������
void MotorModel_calcU4SyncMFieldWinding(TMotorModel *p) {
	if (p->InvertorEna) { //�������� �������
		// ������ ���������� �������
		// ���������� ������� �������� ������� �� ���������� ���� � ����������� �� ����� ����
		if (p->motorInternals.i_f > 0) {
			if (p->motorInternals.cmpr3 > p->motorInternals.dt)
				p->motorInternals.dtf = -p->motorInternals.dt;
			else
				p->motorInternals.dtf = -p->motorInternals.cmpr3;
		} else {
			if ((p->motorInternals.cmpr3 + p->motorInternals.dt) < p->motorInternals.tpr)
				p->motorInternals.dtf = +p->motorInternals.dt;
			else
				p->motorInternals.dtf = p->motorInternals.tpr - p->motorInternals.cmpr3;
		}
		//������ ����������� � ������ ������� �������� �������
		p->motorInternals.u_f = p->motorInternals.udc * (p->motorInternals.cmpr3 + (p->motorInternals.dtf >> 1)) / p->motorInternals.tpr;//���������� �� ��
	} else
	{//�������� ��������
		p->motorInternals.u_f = 0;//���������� �� ����� ����
	}


}

void MotorModel_MechModelExecute(TMotorModel *p) {
	float d_omega;
	p->loadTmp = 0;
	if (p->motorInternals.omega > 0)
		p->loadTmp = p->load + p->motorInternals.MechLoss;
	if (p->motorInternals.omega < 0)
		p->loadTmp = -p->load - p->motorInternals.MechLoss;

	d_omega = p->motorInternals.t / p->motorInternals.j * (p->motorInternals.torque - p->loadTmp);					//���������� ��������

	if ((fabs(d_omega) > fabs(p->motorInternals.omega)) && (fabs(p->motorInternals.torque) < p->load)) {
		p->motorInternals.omega = 0;
		d_omega = 0;
	}

	p->motorInternals.omega = p->motorInternals.omega + d_omega;	//��������


}

//���������� ������������ ��� ������ �������������� SRD
float MotorModel_FluxCubicInterpolation (volatile float Isource, volatile TFluxCurvePoint SourceArray[], volatile int SourceResolution)
{
	volatile float PsiResult=0;
	if (Isource <= SourceArray[0].i)	//��� ������ ��� ����� ��������
	{
		PsiResult = SourceArray[0].psi;
		return PsiResult;
	}
	if (Isource >= SourceArray[SourceResolution].i)	//��� ������ ��� ����� ���������
	{
		PsiResult = SourceArray[SourceResolution].psi;
		return PsiResult;
	}
	for (int count = 1; count < SourceResolution+1; count++)	//������ ������ ������, ���� ������ �������
	{
		if (SourceArray[count].i >= Isource)	//��� � ��������� ����� ������ ���������, ������ ������ � ������ �������
		{
			volatile float a, b, c, d;	//������������ ����������� ��������
			volatile float f_d0, f_d1;	//����������� � ����� � ������ ����� �������
			volatile float x_m;			//���������������� ���: �����, ����� ����� ����� ������� ��������� � ����, � ������ - � �������
			//������� ���������� ������������ f(x)=a*x^3 + b*x^2 + c*x + d, �����������: f(x)=3*a*x^2 + 2*b*x + c
			//����� ����� ������������ ����������� ��������, ����� ����� �������� �������� �� �������� ������� ������ � �����,
			//� ����� ����������� �������� � ���� ������. ��� ���������� ����������� ����� �������� �������� ���������� �������
			//� 2 �������� ������ (����� � ������ ������ �������). ������� ���=0 - ����� ������� �������, ���=1 - ������ �������
			//a = 2*f(0) - 2*f(1) + f'(0) + f'(1)
			//b = -3*f(0) + 3*f(1) - 2*f'(0) - f'(1)
			//c = f'(0)
			//d = f(0)
			//�.�. ��� �� ���� �������������, � x[1]-x[0]!=1, ����������� ������ �� ��������:
			//f'(0) = (f[1] - f[-1]) / {(x[1]-x[-1]) / (x[1]-x[0])}, �.�., �������� ������ ������������� �� ��� x, ����� ����������� x[1]-x[0]=1
			//f'(1) = (f[2] - f[0]) / {(x[2]-x[0]) / (x[1]-x[0])}
			//��������: f'(0) = (f[1] - f[-1]) *(x[1]-x[0]) / (x[1]-x[-1]), f'(1) = (f[2] - f[0]) *(x[1]-x[0]) / (x[2]-x[0])
			//��������, ������������, ����� ������ ��������� �� �������:
			//f(x)= a*xm^3 + b*xm^2 + c*xm + d,
			//��� xm=(x-x[0])/(x[1]-x[0]), �.�. x[0] �� ����� 0, � x[1] �� ����� 1. �.�., ���� �������� (�������� x[0]) � ����� ������� (����� �� x[1]-x[0])
			//����� -1: count-2
			//����� 0: count-1
			//����� 1: count
			//����� 2: count+1

			//������� ����������� � ������ 0 � 1 (�� ����� �������)
			if (count == 1)	//������� ����� �������
			{
				//����������� ����� ��-�������� ��������� ������, �.�. ������� �����, ��������� ����������� �� ������ �������
				f_d0 = SourceArray[count].psi - SourceArray[count-1].psi;	//�� �������� ����� �� ����� ������� �� �����, �.�. ������� �� �� �������
			}
			else	//������� ����� ����������� ��� ������
			{
				f_d0 = (SourceArray[count].psi - SourceArray[count-2].psi)*(SourceArray[count].i - SourceArray[count-1].i)/(SourceArray[count].i - SourceArray[count-2].i);
			}
			if (count == SourceResolution)	//������� ������ �������
			{
				//����������� ������ ��-�������� ��������� ������, �.�. ������� �����, ��������� ����������� �� ������ �������
				f_d1 = SourceArray[count].psi - SourceArray[count-1].psi;	//�� �������� ����� �� ����� ������� �� �����, �.�. ������� �� �� �������
			}
			else	//������� ������ ����������� ��� ������
			{
				f_d1 = (SourceArray[count+1].psi - SourceArray[count-1].psi)*(SourceArray[count].i - SourceArray[count-1].i)/(SourceArray[count+1].i - SourceArray[count-1].i);
			}

			//������� ������������ ��������
			a = 2*SourceArray[count-1].psi - 2*SourceArray[count].psi + f_d0 + f_d1;
			b = -3*SourceArray[count-1].psi + 3*SourceArray[count].psi - 2*f_d0 - f_d1;
			c = f_d0;
			d = SourceArray[count-1].psi;

			//������� ��� � ������ ����������� � ������������ ���������� �������� ������������ ��������� ������� �� ��� ���
			x_m = (Isource - SourceArray[count-1].i)/(SourceArray[count].i - SourceArray[count-1].i);

			PsiResult = a*x_m*x_m*x_m + b*x_m*x_m + c*x_m + d;	//������� ������� �����
			return PsiResult;
		}
	}
	return PsiResult;//���� �� ������ �� ����� ����, �� ����� ���������� �� �������
}

//���������� ������������ �� ����������� ��� ������ ���� � ������ SRD
float MotorModel_PhaseCurrentInterpolation (TMotorModel *p, volatile float Theta, volatile float PsiS)
{
	volatile float Current = 0;
	volatile float Current1, Current2;
	volatile int cntThetaMinus, cntThetaPlus, cntPsiMinus, cntPsiPlus;

	//������������ ������� ����������
	//�� ���� ���� ���������
	if (Theta < 0)
		Theta += p->motorInternals.ThetaMax;	//���������� 2��
	if (Theta > p->motorInternals.ThetaMax)
		Theta -= p->motorInternals.ThetaMax;	//�������� 2��
	cntThetaMinus = Theta*p->motorInternals.ThetaStep_inv;	//������ ������� �� ���� (������� �� ����)
	cntThetaPlus = cntThetaMinus + 1;			//������� �� ����
	if (cntThetaPlus > SRD_SURFACE_RESOLUTION)		//���� ����� �� ������� �������, �����������
	{
		cntThetaPlus -= (SRD_SURFACE_RESOLUTION+1);
	}
	//�� ������ ���� ������ ���������� ������ � �����
	if (PsiS < 0)
		PsiS = 0;
	if (PsiS > p->motorInternals.PsiMax)
		PsiS = p->motorInternals.PsiMax;
	cntPsiMinus = PsiS*p->motorInternals.PsiStep_inv;		//������ ������� �� ������ (������� �� ����)
	cntPsiPlus = cntPsiMinus + 1;				//������� �� ����

	//������ ������������ �� ����
	Current1 = I_PsiTheta[cntPsiMinus][cntThetaMinus] + (I_PsiTheta[cntPsiMinus][cntThetaPlus] - I_PsiTheta[cntPsiMinus][cntThetaMinus])*(Theta - (float)cntThetaMinus*p->motorInternals.ThetaStep)*p->motorInternals.ThetaStep_inv;
	//���� ������ �� ������� ������� �� ������, ���� ��������������� �� ����������� ��������, ����� �� ������� �� ������� �������
	if (cntPsiMinus >= SRD_SURFACE_RESOLUTION)	//�� ������ ��������� �� ������� �������
	{
		//������������ �� ������
		Current = Current1;	//��������������� �� ������� �� ������ �� ����, ������ ����� ����� ������� �� ������ ������������ �� ����
		return Current;
	}
	//������ ������������ �� ����
	Current2 = I_PsiTheta[cntPsiPlus][cntThetaMinus] + (I_PsiTheta[cntPsiPlus][cntThetaPlus] - I_PsiTheta[cntPsiPlus][cntThetaMinus])*(Theta - (float)cntThetaMinus*p->motorInternals.ThetaStep)*p->motorInternals.ThetaStep_inv;
	//������������ �� ������
	Current = Current1 + (Current2 - Current1)*(PsiS - (float)cntPsiMinus*p->motorInternals.PsiStep)*p->motorInternals.PsiStep_inv;
	return Current;
}

//���������� ������������ �� ����������� ��� ������ ������� � ������ SRD
float MotorModel_PhaseTorqueInterpolation (TMotorModel *p, volatile float Theta, volatile float IPh)
{

	volatile float Torque = 0;
	volatile float Torque1, Torque2;
	volatile int cntThetaMinus, cntThetaPlus, cntIMinus, cntIPlus;

	//������������ ������� ����������
	//�� ���� ���� ���������
	if (Theta < 0)
		Theta += p->motorInternals.ThetaMax;	//���������� 2��
	if (Theta > p->motorInternals.ThetaMax)
		Theta -= p->motorInternals.ThetaMax;	//�������� 2��
	cntThetaMinus = Theta*p->motorInternals.ThetaStep_inv;	//������ ������� �� ���� (������� �� ����)
	cntThetaPlus = cntThetaMinus + 1;			//������� �� ����
	if (cntThetaPlus > SRD_SURFACE_RESOLUTION)		//���� ����� �� ������� �������, �����������
	{
		cntThetaPlus -= (SRD_SURFACE_RESOLUTION+1);
	}
	//�� ���� ���� ������ ���������� ������ � �����
	if (IPh < 0)
		IPh = 0;
	if (IPh > p->motorInternals.IMax)
		IPh = p->motorInternals.IMax;
	cntIMinus = IPh*p->motorInternals.IStep_inv;		//������ ������� �� ���� (������� �� ����)
	cntIPlus = cntIMinus + 1;				//������� �� ����

	//������ ������������ �� ����
	Torque1 = M_ITheta[cntIMinus][cntThetaMinus] + (M_ITheta[cntIMinus][cntThetaPlus] - M_ITheta[cntIMinus][cntThetaMinus])*(Theta - (float)cntThetaMinus*p->motorInternals.ThetaStep)*p->motorInternals.ThetaStep_inv;
	//���� ������ �� ������� ������� �� ����, ���� ��������������� �� ����������� ��������, ����� �� ������� �� ������� �������
	if (cntIMinus >= SRD_SURFACE_RESOLUTION)	//�� ���� ��������� �� ������� �������
	{
		//������������ �� ����
		Torque = Torque1;	//��������������� �� ������� �� ���� �� ����, ������ ����� ����� ������� �� ������ ������������ �� ����
		return Torque;
	}
	//������ ������������ �� ����
	Torque2 = M_ITheta[cntIPlus][cntThetaMinus] + (M_ITheta[cntIPlus][cntThetaPlus] - M_ITheta[cntIPlus][cntThetaMinus])*(Theta - (float)cntThetaMinus*p->motorInternals.ThetaStep)*p->motorInternals.ThetaStep_inv;
	//������������ �� ����
	Torque = Torque1 + (Torque2 - Torque1)*(IPh - (float)cntIMinus*p->motorInternals.IStep)*p->motorInternals.IStep_inv;
	return Torque;
}

void Model_Execute_InductionMotor(TMotorModel *p) {
	MotorModel_calcU43Phase(p);	//������ ����������

	// ������ ������ � �������� ���� ������
	p->motorInternals.cosTetaR = _IQtoF(_IQcos(_IQ(p->motorInternals.tetaR)));//����� � ������� ��������� � ������������� ������, �.�. ����������� �������� ������ ������ (������, �����-�� ��������� ����������, �� ������������ ���������� ���������).
	p->motorInternals.sinTetaR = _IQtoF(_IQsin(_IQ(p->motorInternals.tetaR)));//���� ������� ����� ������� ��������� ����� � �������, �� �� ����� ������� �� ������

	// ������ ��������� ��������������� (����������)
	p->motorInternals.dpsa = (p->motorInternals.usa - p->motorInternals.isa * p->motorInternals.rs);
	p->motorInternals.dpsb = (p->motorInternals.usb - p->motorInternals.isb * p->motorInternals.rs);
	p->motorInternals.dprd = -(p->motorInternals.ird * p->motorInternals.rr);
	p->motorInternals.dprq = -(p->motorInternals.irq * p->motorInternals.rr);

	// ������ ����������� ���������������
	p->motorInternals.ppsa = p->motorInternals.psa + p->motorInternals.dpsa * p->motorInternals.t;
	p->motorInternals.ppsb = p->motorInternals.psb + p->motorInternals.dpsb * p->motorInternals.t;
	p->motorInternals.pprd = p->motorInternals.prd + p->motorInternals.dprd * p->motorInternals.t;
	p->motorInternals.pprq = p->motorInternals.prq + p->motorInternals.dprq * p->motorInternals.t;

	// ������� ��������������� ������ � ���������� alpha,beta
	p->motorInternals.ppra = p->motorInternals.pprd * p->motorInternals.cosTetaR - p->motorInternals.pprq * p->motorInternals.sinTetaR;
	p->motorInternals.pprb = +p->motorInternals.pprd * p->motorInternals.sinTetaR + p->motorInternals.pprq * p->motorInternals.cosTetaR;

	// ������ ����� ��� ������������� ���������
	p->motorInternals.isa = p->motorInternals.ks * p->motorInternals.ppsa + p->motorInternals.km * p->motorInternals.ppra;
	p->motorInternals.isb = p->motorInternals.ks * p->motorInternals.ppsb + p->motorInternals.km * p->motorInternals.pprb;
	p->motorInternals.ira = p->motorInternals.km * p->motorInternals.ppsa + p->motorInternals.kr * p->motorInternals.ppra;
	p->motorInternals.irb = p->motorInternals.km * p->motorInternals.ppsb + p->motorInternals.kr * p->motorInternals.pprb;

	// ������� �������� ����� � d,q ����������
	p->motorInternals.ird = p->motorInternals.ira * p->motorInternals.cosTetaR + p->motorInternals.irb * p->motorInternals.sinTetaR;
	p->motorInternals.irq = -p->motorInternals.ira * p->motorInternals.sinTetaR + p->motorInternals.irb * p->motorInternals.cosTetaR;

	// ������ ��������� ��������������� �� �����-����� ������� �������
	p->motorInternals.psa = p->motorInternals.psa + p->motorInternals.t2 * (p->motorInternals.dpsa + (p->motorInternals.usa - p->motorInternals.isa * p->motorInternals.rs));
	p->motorInternals.psb = p->motorInternals.psb + p->motorInternals.t2 * (p->motorInternals.dpsb + (p->motorInternals.usb - p->motorInternals.isb * p->motorInternals.rs));
	p->motorInternals.prd = p->motorInternals.prd + p->motorInternals.t2 * (p->motorInternals.dprd + (-p->motorInternals.ird * p->motorInternals.rr));
	p->motorInternals.prq = p->motorInternals.prq + p->motorInternals.t2 * (p->motorInternals.dprq + (-p->motorInternals.irq * p->motorInternals.rr));

	// ������� ��������������� ������ � ���������� alpha,beta
	p->motorInternals.pra = p->motorInternals.prd * p->motorInternals.cosTetaR - p->motorInternals.prq * p->motorInternals.sinTetaR;
	p->motorInternals.prb = p->motorInternals.prd * p->motorInternals.sinTetaR + p->motorInternals.prq * p->motorInternals.cosTetaR;

	//���� �������� �������� � ��� ���� ��������� ���� (���������� ����� ����, ������������� ������)
	//�� �������� ��� ������ � ��������� (���������, ����� ������� ������ �����)
	if ((p->InvertorEna == 0) && (p->motorInternals.CurrentInvertedFlag == 7)) {
		p->motorInternals.psa = 0;
		p->motorInternals.psb = 0;
		p->motorInternals.prd = 0;
		p->motorInternals.prq = 0;
		p->motorInternals.pra = 0;
		p->motorInternals.prb = 0;
	}

	// ������ ����� ����� ��������� ��������� ���������������
	p->motorInternals.isa = p->motorInternals.ks * p->motorInternals.psa + p->motorInternals.km * p->motorInternals.pra;
	p->motorInternals.isb = p->motorInternals.ks * p->motorInternals.psb + p->motorInternals.km * p->motorInternals.prb;
	p->motorInternals.ira = p->motorInternals.km * p->motorInternals.psa + p->motorInternals.kr * p->motorInternals.pra;
	p->motorInternals.irb = p->motorInternals.km * p->motorInternals.psb + p->motorInternals.kr * p->motorInternals.prb;

	// ������� �������� ����� � d,q ����������
	p->motorInternals.ird = p->motorInternals.ira * p->motorInternals.cosTetaR + p->motorInternals.irb * p->motorInternals.sinTetaR;
	p->motorInternals.irq = -p->motorInternals.ira * p->motorInternals.sinTetaR + p->motorInternals.irb * p->motorInternals.cosTetaR;

	// ������ �������
	p->motorInternals.torque = 3.0 / 2.0 * p->motorInternals.pp * (p->motorInternals.psa * p->motorInternals.isb - p->motorInternals.psb * p->motorInternals.isa);

	// ������ ��������
	MotorModel_MechModelExecute(p);

	//���� �� ���������� ������� � ����������
	p->motorInternals.isPhaseA = p->motorInternals.isa;
	p->motorInternals.isPhaseB = -0.5 * p->motorInternals.isa + p->motorInternals.cos30 * p->motorInternals.isb;
	p->motorInternals.isPhaseC = -p->motorInternals.isa - p->motorInternals.isPhaseB;

	//������ ���������� �������
	p->motorInternals.adcSpeedtemp = p->motorInternals.omega * p->motorInternals.speedK + ADC_HALF_VALUE;						//�������� (�������������)
	p->motorInternals.iAtemp = p->motorInternals.isa * p->motorInternals.iSenseK + ADC_HALF_VALUE;				//��� ���� A
	p->motorInternals.iBtemp = p->motorInternals.isPhaseB * p->motorInternals.iSenseK + ADC_HALF_VALUE;			//��� ���� B
	p->motorInternals.tetaRM = p->motorInternals.tetaRM + p->motorInternals.t * p->motorInternals.omega;	//������������ ��������� ������
	if (p->motorInternals.tetaRM > 2 * MOTOR_MODEL_PI)					//������������ 0..2��
		p->motorInternals.tetaRM -= 2 * MOTOR_MODEL_PI;
	if (p->motorInternals.tetaRM < 0)
		p->motorInternals.tetaRM += 2 * MOTOR_MODEL_PI;
	p->motorInternals.tetaR=p->motorInternals.tetaRM*p->motorInternals.pp;
}

void Model_Execute_SyncMotor(TMotorModel *p) {
	MotorModel_calcU43Phase(p);	//������ ����������

	// ������ ��������������� ������
	if (p->motorInternals.syncm_pm == 0) // ���� � ����������� ��
	{
		MotorModel_calcU4SyncMFieldWinding(p);	//������ ���������� ��
		p->motorInternals.dif = (p->motorInternals.u_f - p->motorInternals.i_f * p->motorInternals.r_f)*p->motorInternals._1_l_f;
		p->motorInternals.i_f = p->motorInternals.i_f + p->motorInternals.dif * p->motorInternals.t;
		if (p->motorInternals.i_f <= p->motorInternals.RatedFluxCurrent)		// ���� ���������
			p->motorInternals.m = p->motorInternals.i_f * p->motorInternals.l_m;
		else
			p->motorInternals.m = p->motorInternals.RatedFluxCurrent * p->motorInternals.l_m; // ��� ����� ���� ��������, ����� ��������� ��������.
	}	// ���� � ����������� ���������, �� ����� ������ ���������� ��� � ����� � �� ��������

	// ������ ������ � �������� ���� ������
	p->motorInternals.cosTetaR = _IQtoF(_IQcos(_IQ(p->motorInternals.tetaR)));//����� � ������� ��������� � ������������� ������, �.�. ����������� �������� ������ ������ (������, �����-�� ��������� ����������, �� ������������ ���������� ���������).
	p->motorInternals.sinTetaR = _IQtoF(_IQsin(_IQ(p->motorInternals.tetaR)));//���� ������� ����� ������� ��������� ����� � �������, �� �� ����� ������� �� ������

	// ������� ���������� �� ���� �����.���� � ��� d,q
	p->motorInternals.usd = p->motorInternals.usa * p->motorInternals.cosTetaR + p->motorInternals.usb * p->motorInternals.sinTetaR;
	p->motorInternals.usq = -p->motorInternals.usa * p->motorInternals.sinTetaR + p->motorInternals.usb * p->motorInternals.cosTetaR;

	// ������ ��������� ��������������� (����������)
	p->motorInternals.dpsd = (p->motorInternals.usd - p->motorInternals.isd * p->motorInternals.rs + p->motorInternals.psq * p->motorInternals.omega);
	p->motorInternals.dpsq = (p->motorInternals.usq - p->motorInternals.isq * p->motorInternals.rs - p->motorInternals.psd * p->motorInternals.omega);

	// ������ ����������� ���������������
	p->motorInternals.ppsd = p->motorInternals.psd + p->motorInternals.dpsd * p->motorInternals.t;
	p->motorInternals.ppsq = p->motorInternals.psq + p->motorInternals.dpsq * p->motorInternals.t;

	// ������ ����� ��� ������������� ���������
	p->motorInternals.isd = (p->motorInternals.ppsd - p->motorInternals.m) * p->motorInternals._1_lsd;
	p->motorInternals.isq = p->motorInternals.ppsq * p->motorInternals._1_lsq;

	// ������ ��������� ��������������� �� �����-����� ������� �������
	p->motorInternals.psd = p->motorInternals.psd + p->motorInternals.t2 * (p->motorInternals.dpsd + (p->motorInternals.usd - p->motorInternals.isd * p->motorInternals.rs + p->motorInternals.psq * p->motorInternals.omega));
	p->motorInternals.psq = p->motorInternals.psq + p->motorInternals.t2 * (p->motorInternals.dpsq + (p->motorInternals.usq - p->motorInternals.isq * p->motorInternals.rs - p->motorInternals.psd * p->motorInternals.omega));

	//���� �������� �������� � ��� ���� ��������� ���� (���������� ����� ����, ������������� ������)
	//�� ��������� ������ ����� �������, ����� �� ��������� (���������, ����� ������� ������ �����)
	if ((p->InvertorEna == 0) && (p->motorInternals.CurrentInvertedFlag == 7)) {
		p->motorInternals.psd = p->motorInternals.m;
		p->motorInternals.psq = 0;
	}

	// ������ ����� ����� ��������� ��������� ���������������
	p->motorInternals.isd = (p->motorInternals.psd - p->motorInternals.m) * p->motorInternals._1_lsd;
	p->motorInternals.isq = p->motorInternals.psq * p->motorInternals._1_lsq;

	//������� ����� � ��� �����,���� (��� ������ �� ���)
	p->motorInternals.isa = p->motorInternals.isd * p->motorInternals.cosTetaR - p->motorInternals.isq * p->motorInternals.sinTetaR;
	p->motorInternals.isb = +p->motorInternals.isd * p->motorInternals.sinTetaR + p->motorInternals.isq * p->motorInternals.cosTetaR;

	// ������ �������
	p->motorInternals.torque = 3.0 / 2.0 * p->motorInternals.pp * (p->motorInternals.psd * p->motorInternals.isq - p->motorInternals.psq * p->motorInternals.isd);

	// ������ ��������
	MotorModel_MechModelExecute(p);

	//���� �� ���������� ������� � ����������
	p->motorInternals.isPhaseA = p->motorInternals.isa;
	p->motorInternals.isPhaseB = -0.5 * p->motorInternals.isa + p->motorInternals.cos30 * p->motorInternals.isb;
	p->motorInternals.isPhaseC = -p->motorInternals.isa - p->motorInternals.isPhaseB;

	p->motorInternals.isPhaseD = p->motorInternals.i_f;

	//������ ���������� �������
	p->adc_code_Speed = p->motorInternals.omega * p->motorInternals.speedK + ADC_HALF_VALUE;						//�������� (�������������)
	p->motorInternals.iAtemp = p->motorInternals.isa * p->motorInternals.iSenseK + ADC_HALF_VALUE;				//��� ���� A
	p->motorInternals.iBtemp = p->motorInternals.isPhaseB * p->motorInternals.iSenseK + ADC_HALF_VALUE;			//��� ���� B
	p->motorInternals.iDtemp = p->motorInternals.i_f * p->motorInternals.ifSenseK + ADC_HALF_VALUE;					//��� ��
	p->motorInternals.tetaRM = p->motorInternals.tetaRM + p->motorInternals.t * p->motorInternals.omega;	//������������ ��������� ������
	if (p->motorInternals.tetaRM > 2 * MOTOR_MODEL_PI)					//������������ 0..2��
		p->motorInternals.tetaRM -= 2 * MOTOR_MODEL_PI;
	if (p->motorInternals.tetaRM < 0)
		p->motorInternals.tetaRM += 2 * MOTOR_MODEL_PI;

	p->motorInternals.tetaR=p->motorInternals.tetaRM*p->motorInternals.pp;
}

void Model_Execute_DCMotor(TMotorModel *p) {
	// �������������� ����������
	MotorModel_calcU42Phase(p);

	// !!! ��������! ��� ����������� ���������� �� � ����� ������������� � ������� �������������� ������ �� ����� ����������� �����������
	// !!! ����������� ����������� ���������� Lf=6.3 ��� � Rf=125 ��

	// ��������������� ������ ���������� �� ����
	if (p->motorInternals.dcm_pm == 0) // ���� � ����������� ��
	{
		p->motorInternals.dif = (p->motorInternals.u_f - p->motorInternals.i_f * p->motorInternals.r_f)*p->motorInternals._1_l_f;
		p->motorInternals.i_f = p->motorInternals.i_f + p->motorInternals.dif * p->motorInternals.t;
		if (p->motorInternals.i_f <= p->motorInternals.RatedFluxCurrent)		// ���� ���������
			p->motorInternals.kf = p->motorInternals.i_f * p->motorInternals.l_m;
		else
			p->motorInternals.kf = p->motorInternals.RatedFluxCurrent * p->motorInternals.l_m; // ��� ����� ���� ��������, ����� ��������� ��������.
	}
	else // ���� � ����������� ���������
		p->motorInternals.kf = p->motorInternals.l_m * 1.0;

	p->motorInternals.dia = (p->motorInternals.u_a - p->motorInternals.kf*p->motorInternals.omega - p->motorInternals.i_a*(p->motorInternals.r_a + p->motorInternals.r_ad))*p->motorInternals._1_l_a;
	p->motorInternals.i_a = p->motorInternals.i_a + p->motorInternals.dia * p->motorInternals.t;

	//���� �������� �������� � ��� ���� ��������� ���� (���������� ����� ����, ������������� ������)
	//�� ��������� ������ ����� �������, ����� �� ��������� (���������, ����� ������� ������ �����)
	if ((p->InvertorEna == 0) && (p->motorInternals.CurrentInvertedFlag == 7)) {
		p->motorInternals.i_a=0;
	}

	// ������
	p->motorInternals.torque = p->motorInternals.kf * p->motorInternals.i_a;

	// ���������� ������������ �������
	MotorModel_MechModelExecute(p);

	//omega+=0.5;
	p->motorInternals.tetaRM = p->motorInternals.tetaRM + p->motorInternals.t * p->motorInternals.omega;		//���������
	if (p->motorInternals.tetaRM > 2 * MOTOR_MODEL_PI)						//����������� 0..2��
		p->motorInternals.tetaRM -= 2 * MOTOR_MODEL_PI;
	if (p->motorInternals.tetaRM < 0)
		p->motorInternals.tetaRM += 2 * MOTOR_MODEL_PI;

	p->motorInternals.isPhaseA = p->motorInternals.i_a;
	p->motorInternals.isPhaseB = p->motorInternals.isPhaseA;
	p->motorInternals.isPhaseC = p->motorInternals.i_f;

	//������ ���������� �������
	p->motorInternals.adcSpeedtemp = p->motorInternals.omega * p->motorInternals.speedK + ADC_HALF_VALUE;			//�������� (�������������)
	p->motorInternals.iAtemp = p->motorInternals.i_a * p->motorInternals.iSenseK + ADC_HALF_VALUE;					//��� �����
	p->motorInternals.iCtemp = p->motorInternals.i_f * p->motorInternals.ifSenseK + ADC_HALF_VALUE;					//��� ��
}


void Model_Execute_SRDMotor(TMotorModel *p) {
	p->motorInternals.ua=p->motorInternals.udc*(p->motorInternals.cmpr0*p->motorInternals.inv_tpr*2-1);	//������ ����������
	p->motorInternals.psa+=(p->motorInternals.ua - p->motorInternals.isPhaseA*p->motorInternals.rs)*p->motorInternals.t;					//����������� ���������������
	if (p->motorInternals.psa<0)
		p->motorInternals.psa=0;
	p->motorInternals.isPhaseA=MotorModel_PhaseCurrentInterpolation(p,p->motorInternals.tetaR, p->motorInternals.psa);			//���� ��� ����
	p->motorInternals.torque_a = MotorModel_PhaseTorqueInterpolation(p,p->motorInternals.tetaR, p->motorInternals.isPhaseA);		//���� ������ ����
	//DebugW2 = _IQ(p->motorInternals.torque_a);

	p->motorInternals.ub=p->motorInternals.udc*(p->motorInternals.cmpr1*p->motorInternals.inv_tpr*2-1);	//������ ����������
	p->motorInternals.psb+=(p->motorInternals.ub - p->motorInternals.isPhaseB*p->motorInternals.rs)*p->motorInternals.t;					//����������� ���������������
	if (p->motorInternals.psb<0)
		p->motorInternals.psb=0;
	float TetaB = p->motorInternals.tetaR+MOTOR_MODEL_PI*1.33333;				//������� �����
	if (TetaB > 2*MOTOR_MODEL_PI)
		TetaB -= 2*MOTOR_MODEL_PI;
	p->motorInternals.isPhaseB=MotorModel_PhaseCurrentInterpolation(p,TetaB, p->motorInternals.psb);					//���� ��� ����
	p->motorInternals.torque_b = MotorModel_PhaseTorqueInterpolation(p,TetaB, p->motorInternals.isPhaseB);			//���� ������ ����
	//DebugW3 = _IQ(p->motorInternals.torque_b);

	p->motorInternals.uc=p->motorInternals.udc*(p->motorInternals.cmpr2*p->motorInternals.inv_tpr*2-1);	//������ ����������
	p->motorInternals.psc+=(p->motorInternals.uc - p->motorInternals.isPhaseC*p->motorInternals.rs)*p->motorInternals.t;					//����������� ���������������
	if (p->motorInternals.psc<0)
		p->motorInternals.psc=0;
	float TetaC = p->motorInternals.tetaR+MOTOR_MODEL_PI*0.66667;				//������� �����
	if (TetaC > 2*MOTOR_MODEL_PI)
		TetaC -= 2*MOTOR_MODEL_PI;
	p->motorInternals.isPhaseC=MotorModel_PhaseCurrentInterpolation(p,TetaC, p->motorInternals.psc);					//���� ��� ����
	p->motorInternals.torque_c = MotorModel_PhaseTorqueInterpolation(p,TetaC, p->motorInternals.isPhaseC);			//���� ������ ����
	//DebugW4 = _IQ(p->motorInternals.torque_c);

	//��������� ������ ���� ��� (���� - �����������)
	p->motorInternals.torque = p->motorInternals.torque_a + p->motorInternals.torque_b + p->motorInternals.torque_c;

	// ������ ��������
	MotorModel_MechModelExecute(p);

	p->motorInternals.tetaRM+=p->motorInternals.t*p->motorInternals.omega;
	//p->motorInternals.tetaRM = 0.393;	//���� � ������������ �������� ��� ���� A, ��� �����
	if (p->motorInternals.tetaRM>2*MOTOR_MODEL_PI)
		p->motorInternals.tetaRM-=2*MOTOR_MODEL_PI;
	if (p->motorInternals.tetaRM<0)
		p->motorInternals.tetaRM+=2*MOTOR_MODEL_PI;

	p->motorInternals.tetaR=p->motorInternals.tetaRM*p->motorInternals.pp;
	while (p->motorInternals.tetaR>2*MOTOR_MODEL_PI)
		p->motorInternals.tetaR-=2*MOTOR_MODEL_PI;

	p->adc_code_Speed=p->motorInternals.omega*p->motorInternals.speedK+ADC_HALF_VALUE;
	p->motorInternals.iAtemp=p->motorInternals.isPhaseA*p->motorInternals.iSenseK;
	p->motorInternals.iBtemp=p->motorInternals.isPhaseB*p->motorInternals.iSenseK;
	p->motorInternals.iCtemp=p->motorInternals.isPhaseC*p->motorInternals.iSenseK;


}

//�������� ������� ������� ������, ���������� � ���������� 10 ���
void MotorModel_Execute(TMotorModel *p) {

	p->motorInternals.cmpr0 = p->motorInternals.tpr-p->cmpr0;	//������� ��������� ���. � ���������, ������ ��� ��� �������� ������ ���
	p->motorInternals.cmpr1 = p->motorInternals.tpr-p->cmpr1;
	p->motorInternals.cmpr2 = p->motorInternals.tpr-p->cmpr2;
	p->motorInternals.cmpr3 = p->motorInternals.tpr-p->cmpr3;

	if (p->fault == 0)		//���� ��� ������ ������, �������
	{
		if (p->motorInternals.type == MODEL_INDUCTION_MOTOR) {
			Model_Execute_InductionMotor(p);

		} else if (p->motorInternals.type == MODEL_SYNC_MOTOR) {
			Model_Execute_SyncMotor(p);

		} else if (p->motorInternals.type == MODEL_DC_MOTOR) {
			Model_Execute_DCMotor(p);

		}
		else if (p->motorInternals.type==MODEL_SRD_MOTOR){
			Model_Execute_SRDMotor(p);
		}
	} else {//������ � ������
		p->motorInternals.iAtemp=ADC_HALF_VALUE;
		p->motorInternals.iBtemp=ADC_HALF_VALUE;
		p->motorInternals.iCtemp=ADC_HALF_VALUE;
		p->motorInternals.iDtemp=ADC_HALF_VALUE;

	}

	//�������� ������� � ������� ����� (3 ��������) � ����������� �� �������� �������������� ���������
	//������������ ����� �������������� �������, ��� ������ ����� �� �������������� ����
	Uint16 TempSector=p->motorInternals.tetaR * (1/(2 * MOTOR_MODEL_PI)*6);
	TempSector=TempSector%6;//���� �� ���������, ������� ���������� ������� �� ��������� �� ���-�� ��������

	switch (TempSector){//� ����������� �� ������ ������� ��������� ��������� ��� �� ��������� �����
		case 0:{
			p->motorInternals.hallSensor=5;//101
			break;
		}
		case 1:{
			p->motorInternals.hallSensor=4;//100
			break;
		}
		case 2:{
			p->motorInternals.hallSensor=6;//110
			break;
		}
		case 3:{
			p->motorInternals.hallSensor=2;//010
			break;
		}
		case 4:{
			p->motorInternals.hallSensor=3;//011
			break;
		}
		case 5:{
			p->motorInternals.hallSensor=1;//001
			break;
		}

	}

	if (p->motorInternals.hallSensor!=p->motorInternals.hallSensorPrev){//������ ����� ����� ��� �����
		p->hallSensorOmega=p->motorInternals.hallSensorOmegaPrev;//�� ����� ������ - ��������, ������� ���� ����� ����������� ������� ��� �����
		p->motorInternals.hallSensorOmegaPrev=p->motorInternals.omega;//���������� ������� ��������, ����� ������ � �����
		p->hallSensorInterpAdd=0;
		p->motorInternals.hallSensorPrev=p->motorInternals.hallSensor;
		p->hallSensor=p->motorInternals.hallSensor;
	}

	if (fabs(p->motorInternals.omega)<1){//���� ��������� ����� �����
		p->hallSensorOmega=0;
		p->motorInternals.hallSensorOmegaPrev=0;
		p->hallSensorInterpAdd=0;
	}
	if (p->hallSensorInterpAdd < (MOTOR_MODEL_PI/3))	//������������ ������ ������ ����
	p->hallSensorInterpAdd = p->hallSensorInterpAdd + p->motorInternals.t * p->hallSensorOmega *p->motorInternals.pp;	//������������ ��������� ������

	p->motorInternals.power=p->motorInternals.omega*p->motorInternals.torque*0.001;//�������� �� ���� � ���
	p->qepCounter=p->motorInternals.tetaRM*MODEL_INV_2PI*p->motorInternals.QEPResolution*4;//�������� �������� ���������������� �������� �� �������� ���� ���������
	p->motorInternals.omega_rpm = p->motorInternals.omega*MODEL_INV_2PI*60;//������� �������� ���� �� ���/� � ��/���
	p->motorInternals.Udc_temp=p->motorInternals.udc*p->motorInternals.udSenseK;//�������� ��������� ���������� ���


	//��������� ���� ���
	p->motorInternals.iAtemp += MotorModel_fastrand();
	p->motorInternals.iBtemp += MotorModel_fastrand();
	p->motorInternals.iCtemp += MotorModel_fastrand();
	p->motorInternals.iDtemp += MotorModel_fastrand();
	p->motorInternals.adcSpeedtemp += MotorModel_fastrand();
	p->motorInternals.Udc_temp += MotorModel_fastrand();

	//��������� ������� ���
	if (p->motorInternals.iAtemp > ADC_MAX_VALUE)
		p->motorInternals.iAtemp = ADC_MAX_VALUE;
	if (p->motorInternals.iAtemp < 0)
		p->motorInternals.iAtemp = 0;
	if (p->motorInternals.iBtemp > ADC_MAX_VALUE)
		p->motorInternals.iBtemp = ADC_MAX_VALUE;
	if (p->motorInternals.iBtemp < 0)
		p->motorInternals.iBtemp = 0;
	if (p->motorInternals.iCtemp > ADC_MAX_VALUE)
		p->motorInternals.iCtemp = ADC_MAX_VALUE;
	if (p->motorInternals.iCtemp < 0)
		p->motorInternals.iCtemp = 0;
	if (p->motorInternals.iDtemp > ADC_MAX_VALUE)
		p->motorInternals.iDtemp = ADC_MAX_VALUE;
	if (p->motorInternals.iDtemp < 0)
		p->motorInternals.iDtemp = 0;
	if (p->motorInternals.adcSpeedtemp > ADC_MAX_VALUE)
		p->motorInternals.adcSpeedtemp = ADC_MAX_VALUE;
	if (p->motorInternals.adcSpeedtemp < 0)
		p->motorInternals.adcSpeedtemp = 0;
	if (p->motorInternals.Udc_temp > ADC_MAX_VALUE)
		p->motorInternals.Udc_temp = ADC_MAX_VALUE;
	if (p->motorInternals.Udc_temp < 0)
		p->motorInternals.Udc_temp = 0;

	p->adc_code_iA = p->motorInternals.iAtemp;
	p->adc_code_iB = p->motorInternals.iBtemp;
	p->adc_code_iC = p->motorInternals.iCtemp;
	p->adc_code_iD = p->motorInternals.iDtemp;
	p->adc_code_Speed = p->motorInternals.adcSpeedtemp;
	p->adc_code_Udc =  p->motorInternals.Udc_temp;

}


/*@}*/
