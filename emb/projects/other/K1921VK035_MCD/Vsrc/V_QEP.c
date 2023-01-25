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
 
 \file      V_QEP.c
 \brief     ������ ������ �������� � ��������� ��� ������ eQEP (��. TposspeedEqep)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_QEP
 @{*/

#include "DSP.h"
#include "V_IQmath.h"
#include "V_QEP.h"
#include "math.h"
#include "stdlib.h"
#include "main.h"

#define FIRST_LAUNCH_UP		1//!< ������ ���� ��� �������� � ������ �������� �� ����� �������
#define NOT_FIRST_LAUNCH	0//!< �� ������ ����
#define SCALE_IQ_K 10
#define LOWEST_UPSS 0


//��� ������������ �������� -
//�������� QEP ����� ������� ���������
#define SPEED_CALC_TYPE_BY_QEP 0
//���������� �� ����������� ����
#define SPEED_CALC_TYPE_BY_SOFT 1


//! �������������

//! \memberof TposspeedEqep
void TposspeedEqep_init(TposspeedEqep *p) {

	QEP->QCAPCTL_bit.UPPS = LOWEST_UPSS;
	QEP->QCAPCTL_bit.CCPS = 4;
	QEP->QDECCTL_bit.QSRC = 0;			//���. ����� ������������� �����
	QEP->QEPCTL_bit.FREESOFT = 0;		//����� ���������
	QEP->QPOSINIT = 0;					//�������� �������� ��������� ����� ������������� ��� �������������� ������������
	QEP->QEPCTL_bit.SWI = 1;			//����� ��������
	QEP->QPOSMAX = (p->resol << 2) - 1;	//������������ �������� ��������, ����� ���� ���������
	if (p->Posspeed_CTL.bit.dir == 1) {	//�������� ����������� ��������
		QEP->QDECCTL_bit.QAP = 1;
	}

	QEP->QEPCTL_bit.QPEN = 1;	//���. ������������� ��������
	QEP->QCLR = 0xFFFF;	//�������� ���� ������
	QEP->QEPCTL_bit.QCLM = 0;	//����� ������� - �� ���������, �� ������� ��������� ��������� ����� ���������

	if (p->Posspeed_CTL.bit.index_en == 1) {	//���� ��������� ����� ����
		QEP->QEPCTL_bit.PCRM = 0;
		QEP->QEINT_bit.IEL = 1;
	} else {
		QEP->QEPCTL_bit.PCRM = 1;		//����� ��������� �������� - �� ������������� ��������
	}
	QEP->QWDPRD = 200000 / (1 << 2);	//���� ������� ����������� �������
	QEP->QEPCTL_bit.WDE = 1;	//���. ����������� �������

	/*������ ���������������� ������������ ��� ������� ��������,
	 ��� 15=60/4, 60 - ��� �������� � ��/���; 4 - ��� ��������� ������������ ���������� ������� (1 ������ ���� 4 ������);
	 SystemCoreClock - ������� ����������*/
	p->k_low = SystemCoreClock / ((float) p->resol * p->speed_nom) * 15.0;
	//� iq ������� ��������� ����� � 1<<(24-SCALE_IQ_K),  ��� 24 - ������� ����� iq, � SCALE_IQ_K - ��, ��������� ���������� ��������
	//� ������� speedK ������ ��������� � �������
	p->speedK = _IQ(p->k_low / (1 << (24 - 10)));

	p->resol_inv = 1.0 / ((float) p->resol);

	p->Index_eventCounter = 0;

    //������������� ������ ����� ������
	GPIOB->ALTFUNCSET = (1 << 11) + (1 << 12) + (1 << 13);
	SIU->REMAPAF_bit.QEPEN = 1;
}

//! ������� ������� �������� � ���������, ���������� � ����������� �������������

//! \memberof TposspeedEqep
void TposspeedEqep_Calc(TposspeedEqep *p) {
    long temp;
	//������� �������� GPIO ��� �������. ����� �������� � �����
	p->GPIOsValue = (GPIOB->DATA >> 12) & 3;

	//���� �������� �������, � ��������  UPEVNT �� �������
	if ((labs(p->speed_elec) > _IQ(2)) && (QEP->QCAPCTL_bit.UPPS != 5)) {
		QEP->QCAPCTL_bit.UPPS = 5;    //������ �������� UPEVNT �������
		p->skip_counter = 2;    //��� ����� ��������� ������ ��������
	}

	//���� �������� ������, � �������� �� ������
	if ((labs(p->speed_elec) < _IQ(1.5)) && (QEP->QCAPCTL_bit.UPPS != LOWEST_UPSS)) {
		QEP->QCAPCTL_bit.UPPS = LOWEST_UPSS;    //������ �������� UPEVNT ������
		p->skip_counter = 2;    //��� ����� ��������� ������ ��������
	}

	p->UPPS_forWatch = QEP->QCAPCTL_bit.UPPS;  //��� ����������� UPPS ������

	if (p->Posspeed_CTL.bit.CmdInit == 1) { //������� ����������������� - ��� ��������
		QEP->QEPCTL_bit.SWI = 1;
		p->Posspeed_FLG1.bit.first_theta = 1;
		p->Posspeed_FLG2.bit.pos_ident = 0;
		p->Posspeed_CTL.bit.CmdInit = 0;
		p->theta_elec = 0;
		p->Poscnt_res = 0;
	}
	p->Poscnt_resPrev=p->Poscnt_res;
	p->Poscnt_res = (unsigned long) QEP->QPOSCNT;    //������ ���������


	p->Poscnt_res16=p->Poscnt_res;//��� ���������� �� ������������
	p->Posspeed_FLG1.bit.PCO_tmp = QEP->QFLG_bit.PCO; //����� ����� �������������� ������������ ��������
	p->Posspeed_FLG1.bit.PCU_tmp = QEP->QFLG_bit.PCU; //����� ����� �������������� ������������ ��������
	QEP->QCLR_bit.PCO = 1; //�������� ����� �������������� ������������ ��������
	QEP->QCLR_bit.PCU = 1; //�������� ����� �������������� ������������ ��������

	//������� ���� � ������ �� ������� � ������������ ����
	//����� ������ �� float - ���������� ���������� � IQ
	p->theta_mech = _IQ((float )p->Poscnt_res * p->resol_inv * 0.25); //������ ������������� ����
	p->theta_mech &= 0x00FFFFFF;


    // ������� ���������� ������ ��������. ����� PCO � PCU ���������� ���-�� ������
    if (p->prevThetaMech - p->theta_mech > _IQ(0.5))
		p->RevolutionCounter++;
	if (p->prevThetaMech - p->theta_mech < _IQ(-0.5))
		p->RevolutionCounter--;
	p->prevThetaMech=p->theta_mech;

	//���� � ������ ��� ��������� �� �������, ����������
	p->Poscnt_resContinouosLong=p->Poscnt_res+((QEP->QPOSMAX+1)*p->RevolutionCounter);
	p->Poscnt_resContinouosInt=p->Poscnt_resContinouosLong;//����� ���� ������� �������� � 16�� ��������� ������������
	p->Poscnt_resContinouosInt8=p->Poscnt_resContinouosLong&0xF;//����� ������ ����� � ������� ��������


	//������� ���� � ������ ���������� (�� ���������� ���������) � ������������ ����
	//�� 127 �������� �� ������������, �� ��� ���� ��������
	p->theta_mechContinouos = _IQ((float )p->Poscnt_resContinouosLong * p->resol_inv * 0.25); //������ ������������� ����
	p->theta_elecContinouos = p->theta_mechContinouos*p->pole_pairs+ p->AngleOffset;//������������� ���� ���������� (�� ����������)

	//������ �������������� ��������� ���������� �� ���������� 360 ��������
	p->theta_el_tmp = p->theta_mech*p->pole_pairs + p->AngleOffset;
	p->theta_elec = p->theta_el_tmp & 0x00FFFFFF;

	//������������ �������� ���������, ������� ����� ����� ������� ���������� QEP
	if (p->SpeedCalcType==SPEED_CALC_TYPE_BY_QEP){

		/*�������� �� ������������ ����������� ������� - �� ������ �� ������� ��������*/
		if (QEP->QFLG_bit.WTO == 1) {
			p->Posspeed_FLG1.bit.first_launch = FIRST_LAUNCH_UP; //��������� ������� ������� ��������� ����� ������������ �������
			p->speed_elec = 0;    //��������� ��������
			QEP->QCLR_bit.WTO = 1;    //�������� �����
			QEP->QWDTMR = 0;    //��������� �������
		} else {
			/*������������ �� ������� ������� ��� �������������*/
			if (p->Posspeed_FLG1.bit.first_launch == FIRST_LAUNCH_UP) {
				//����. ����� �������
				QEP->QCAPCTL_bit.CEN = 0;
				QEP->QCAPCTL_bit.CEN = 1;
				p->Posspeed_FLG1.bit.first_launch = NOT_FIRST_LAUNCH;
			}

			p->QEPSTS=QEP->QEPSTS;//����� �������� �������

			if (p->QEPSTS_bit.UPEVNT == 1) { //���� ������� UPEVNT, ������ � ������� ��������� �����
				p->Qcprdlat_tmp = QEP->QCPRD;    //����� �������� �������
				p->speed_calc_skip = 0;   //������� ������� �������� - �� ����������

				if (p->QEPSTS_bit.COEF == 1) { //�������� ����� ������������ �������
					p->speed_elec = 0;
					p->speed_calc_skip = 1;      //���������� ������ ��������
					QEP->QEPSTS = 1 << 3;
				}

				if (p->QEPSTS_bit.CDEF == 1) { //�������� �� ��������� ����������� �������� �� ����� �������
					p->speed_elec = 0;
					p->speed_calc_skip = 1;      //���������� ������ ��������
					QEP->QEPSTS = 1 << 2;
				}

				if (p->Qcprdlat_tmp<7){//������ �����
					p->speed_calc_skip = 1;      //���������� ������ ��������
				}

				if (p->QEPSTS_bit.QDF!=p->DirPrev){//��������� ����������� ��������
					p->speed_elec = 0;
					p->speed_calc_skip = 1; //���������� ������ ��������
				}
				p->DirPrev=p->QEPSTS_bit.QDF;

				if (p->skip_counter != 0) { //�������� UPPS
					p->skip_counter--;
					p->speed_calc_skip = 1; //���������� ������ ��������
				}


				if (p->Qcprdlat_tmp > ((1<<(32-SCALE_IQ_K-1)))) { //������� 32 �������, � ������� ������������ ��� �������� �����, ������������� SCALE_IQ_K
					p->speed_elec = 0;
					p->speed_calc_skip = 1; //���������� ������ ��������
				}

				if (!p->speed_calc_skip) { //���� ������ �������� ���������� �� ����
					if (p->QEPSTS_bit.QDF == 1) //� ����������� �� ����������� ��������
						p->speed_tmpIQ = _IQdiv(p->speedK, p->Qcprdlat_tmp << SCALE_IQ_K); //���������� �������� ������� �� 16�� ��������� �����, ���������� ����� �� 15
					else
						p->speed_tmpIQ = -_IQdiv(p->speedK, p->Qcprdlat_tmp << SCALE_IQ_K);

					//�� ������� ����� ��������� ��������� � ����������� ��
					//��������� �� UPEVNT � ������������ �������� �������
					p->MoveK = QEP->QCAPCTL_bit.UPPS
							- QEP->QCAPCTL_bit.CCPS;

					if (p->MoveK >= 0) //���� ��������� �����
						p->speed_tmpIQ = p->speed_tmpIQ << p->MoveK;
					else
						//����
						p->speed_tmpIQ = p->speed_tmpIQ >> -p->MoveK;
					p->speed_elec = p->speed_tmpIQ; //������� �������� � ������� 8.24
				}

				QEP->QEPSTS = 1 << 7;
			}
			else if (QEP->QCTMR > QEP->QCPRD)
			{ //��� ������� UPEVNT, ������� �� ������� QCTMR, � �� �� ������� QCPRD
				p->Qcprdlat_tmp = QEP->QCTMR;    //����� ��������

				if (p->QEPSTS_bit.COEF == 1) { //�������� ����� ������������ �������
					p->speed_elec = 0;
					p->speed_calc_skip = 1;      //���������� ������ ��������
				}

				if (p->QEPSTS_bit.CDEF == 1) { //�������� �� ��������� ����������� �������� �� ����� �������
					p->speed_elec = 0;
					p->speed_calc_skip = 1;      //���������� ������ ��������
				}
				if (p->Qcprdlat_tmp<7){//������ �����
					p->speed_calc_skip = 1;      //���������� ������ ��������
				}

				if (p->Qcprdlat_tmp > ((1<<(32-SCALE_IQ_K-1)))) { //������� 32 �������, � ������� ������������ ��� �������� �����, ������������� SCALE_IQ_K
					p->speed_elec = 0;
					p->speed_calc_skip = 1; //���������� ������ ��������
				}

				if (!p->speed_calc_skip) { //���� ������ �������� ���������� �� ����
					if (p->QEPSTS_bit.QDF == 1) //� ����������� �� ����������� ��������
						p->speed_tmpIQ = _IQdiv(p->speedK, p->Qcprdlat_tmp << SCALE_IQ_K); //���������� �������� ������� �� 16�� ��������� �����, ���������� ����� �� 15
					else
						p->speed_tmpIQ = -_IQdiv(p->speedK, p->Qcprdlat_tmp << SCALE_IQ_K);

					//�� ������� ����� ��������� ��������� � ����������� ��
					//��������� �� UPEVNT � ������������ �������� �������
					p->MoveK = QEP->QCAPCTL_bit.UPPS
							- QEP->QCAPCTL_bit.CCPS;

					if (p->MoveK >= 0) //���� ��������� �����
						p->speed_tmpIQ = p->speed_tmpIQ << p->MoveK;
					else
						//����
						p->speed_tmpIQ = p->speed_tmpIQ >> -p->MoveK;
					p->speed_elec = p->speed_tmpIQ; //������� �������� � ������� 8.24
				}
			}
		}

	}

	//������������ �������� ���������� ����� ����������� ����
	if (p->SpeedCalcType==SPEED_CALC_TYPE_BY_SOFT){
		//������� ������ ������ �� ��� ����
		//0.5 � ����� - ��� ����� ������������������ ������� � ������� ����� ������ 360
		//����� ��� ��������� ���� ��� �������� ����� 360 �������� ���
		//��������� �� 5 �������� 355 ���������� 10 (� IQ �������)
		p->theta_finish=p->theta_finish+_IQmpy(_IQ(0.5),((p->theta_elec-p->theta_finish+_IQ(0.5))&0x00FFFFFF)-_IQ(0.5));
		p->theta_finish&=0x00FFFFFF;
		//����������� ���������� ����
		temp = (p->theta_finish << 8) - (p->theta_start << 8);
		p->d_fi = (temp >> 8);
		p->theta_start = p->theta_finish;

		//�������� ���������������, ������������ �� ����������� ���� �� ���� ������
		p->speed_elec_temp=_IQmpy(p->d_fi,p->KThetaToSpeed)<<3;

		//����������� ������ ��� ��������
		p->speed_filter.input = p->speed_elec_temp;
		p->speed_filter.calc(&p->speed_filter);
		p->speed_elec=p->speed_filter.output;
	}
}

//! ������� ��������� ������ (������� �������)

//! \memberof TposspeedEqep
void TposspeedEqep_IndexEvent(TposspeedEqep *p) {
	p->Posspeed_FLG2.bit.pos_ident = 1;
	p->Index_eventCounter++;
}

//! \memberof TposspeedEqep
void TposspeedEqep_SlowCalc(TposspeedEqep *p) {
	//����������� �������� ����������� �� ���� (����������� ���������� � ���) � ��������
	//����� �� 3 ����� ��������� ������� �� ���������� 127, ����� ��� ������������� �����
	//��������� ����� �� 3
	p->KThetaToSpeed=_IQdiv(_IQ(1.0),_IQmpyI32(drv_params.freq_nom,FAST_CALC_TS)<<3);
}
/*@}*/

