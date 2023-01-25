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
 
 \file      V_pid_reg3.c
 \brief     ���-��������� (��. TPidReg3)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_pid_reg3
 @{*/

#include "V_IQmath.h"         // Include header for IQmath library
#include "V_pid_reg3.h"
#include "stdlib.h"
#include "main.h"
//! ������� ������� ��� ����������
//! ������ ��� ���� ������������ ������ ������������� ����������
//! ������������ ���� ����� ����� ����� ����������, �������� pid_reg3.pdf

//! �� ����� pid_ref_reg3 - �������, pid_fdb_reg3 - �������� �����
//! �� ������ pid_out_reg3.

//! \memberof TPidReg3
void pid_reg3_calc(TPidReg3 *v) {
	v->e_reg3 = v->pid_ref_reg3 - v->pid_fdb_reg3;//������ - ������� ����� �������� �����
	v->e_reg3Dz=v->e_reg3;//������ ����� ��������� ����� ������� ����

	if (v->DeadZone!=0){//���� ���� ������� ���� ������������������
		if (v->e_reg3Dz>0){//������ � ����
			v->e_reg3Dz=v->e_reg3Dz-v->DeadZone;//�������� ������� ����
			if (v->e_reg3Dz<0)//�� ���, ����� ������ �� ����� �������������
				v->e_reg3Dz=0;
		}
		if (v->e_reg3Dz<0){
			v->e_reg3Dz=v->e_reg3Dz+v->DeadZone;
			if (v->e_reg3Dz>0)
				v->e_reg3Dz=0;
		}
	}

	v->up_reg3 = _IQmpy(v->Kp_reg3, v->e_reg3Dz);

	v->uprsat_reg3 = v->up_reg3 + v->ui_reg3 + v->ud_reg3;

	if (v->uprsat_reg3 > v->pid_out_max)
		v->pid_out_reg3 = v->pid_out_max;
	else if (v->uprsat_reg3 < v->pid_out_min)
		v->pid_out_reg3 = v->pid_out_min;
	else
		v->pid_out_reg3 = v->uprsat_reg3;

	v->saterr_reg3 = v->pid_out_reg3 - v->uprsat_reg3 + v->saterr_reg3Add;

	//������������ �� ������ ��� ����. �����. ���� �������� ����, �� ���.
	if (v->Kf_d == 0){
		v->e_reg3_filterOut = v->e_reg3;//����� �������
	}
	else{//����� ������� ������
		v->e_reg3_filterOut = v->e_reg3_filterOut
				+ _IQmpy(v->Kf_d, (v->e_reg3 - v->e_reg3_filterOut));
	}

	if ((v->DiffCounter++ + 1) >= v->DiffDelim) {//������ ������� ������� ������� ����. �����
		if (v->KdFilterInitFlag==1){//��� ������ ���� ������� ����������
			v->e_reg3_filterOut = v->e_reg3;//����� ������� ������ �������������� �������
			v->up1_reg3 = v->e_reg3_filterOut;//����������� ����
			v->KdFilterInitFlag=0;//������������� ���������
		}
		v->ud_reg3 = _IQmpy(v->Kd_reg3, (v->e_reg3_filterOut - v->up1_reg3)<<6);//���������������� �����
		v->up1_reg3 = v->e_reg3_filterOut;
		v->DiffCounter = 0;
	}

	if (v->Ki_reg3 != 0)//���� ������������ ������������
		v->ui_reg3 = v->ui_reg3
				+ _IQmpy(v->Ki_reg3,
						v->up_reg3) + _IQmpy(v->Kc_reg3,v->saterr_reg3);
	else
		v->ui_reg3 = 0;

	if (v->Kc_reg3 == 0) {
		if (v->ui_reg3 > v->pid_out_max)
			v->ui_reg3 = v->pid_out_max;
		else if (v->ui_reg3 < v->pid_out_min)
			v->ui_reg3 = v->pid_out_min;
	}

}


//! \memberof TPidReg3
void pid_reg3_reset(TPidReg3 *v) {
	v->pid_fdb_reg3=0;
	v->pid_ref_reg3=0;
	v->ui_reg3=0;
	v->KdFilterInitFlag=1;
}

/*@}*/
