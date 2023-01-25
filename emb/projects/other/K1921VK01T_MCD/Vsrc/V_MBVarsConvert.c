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

 \file		v_MBVarsConv.c
 \brief		������ �������������� ������ Modbus
 \author    ��� "��� ������". http://motorcontrol.ru
 \version	v.1.1. 02/03/2017

 \addtogroup v_ModBus */
/*@{*/

#include "main.h"
#include "mbod.h"
#include "math.h" //��� fabs
//! ������������� �� ���������
//! \memberof	TMBVarsConv
void MBVarsConv_init(TMBVarsConv *p) {

}

//! �������� ���������

//! ���� � .input, ����� � .output
//! ������ �������� �������� �� NumOfPoints ����� �� x � �� y.
//! \memberof	TMBVarsConv
void MBVarsConv_calc(TMBVarsConv *p) {
	float number, scale, scaled;
	long i, index;
	if (ModBus.Enabled == 1){ // ���� ������� MODBUS
		//��� ���������� �������������� �������� � ������ ������������� ����� ������ ���� for � ��������� �� ������ �������� �� ���� �����
		for (i = 0; i < ModBus.MBInternals.NumOfHRs; i++)// ��������� ��� �������� ������� HR (������������� ����������)
			if (mbodHR[i].type_or_acc == 1){// ���� �������� �������, �� �����������, ��� ��� �������������

				mbodHR[i].type_or_acc = 0;		// ���������� ���� ��������� ���������
				index = mbodHR[i].index;		//����� ������ ������

				if ((index != 2000) && (index != 2001))	//���� �� 2000 � �� 2001, �� ����� ��������� ���������
					p->NeedForSave = 1;//����� �� �������������� ���� ��������, ����� ��� ���������������� ������ �������� �� ���!

				//� ����������� �� ����, ����� ������ ������� ���������, ��������� ������ ��������������.
				//�� ������ �������� ������� �������� 3 �����. ���� �������� ����� ����� �����,
				//�� ������� ��������� ������� ��������� ��������� ������ ��� ��������� � ���������
				switch (index){
					case 2000://����� ����������
						//���� �������� ���� ������� ���������� �� ��������� � ����������
						if (p->Vars.Command!=p->Vars.CommandPrev){
							if (p->Vars.Command & (1<<0))//������� �� ������
								cmd.bit.start = 1;
							if (p->Vars.Command & (1<<1))//������� �� �������
								cmd.bit.stop = 1;
							if (p->Vars.Command & (1<<2))//������� �� ����� ������
								cmd.bit.trip_reset = 1;

						}
						p->Vars.CommandPrev=p->Vars.Command;
						break;

					case  2001:  // ������� ������� ��������
						number = (float) p->Vars.speed_ref;
						number = fabs(number);
						scale = (float) co2_vars.co_scaleNum14;	// ������� �������� (��/���) 16.0
						scaled = number / scale;
						refs.speed_ref = _IQ(scaled);
						break;

					case 43116: //���������� ������ � �������
						number = (float) MBVarsConv.Vars.Umax_protect;
						scale = (float) co2_vars.co_scaleNum7;	//���������� ��� �������
						scaled = number / scale;
						sm_prot.Umax_protect = _IQ(scaled);
						break;

					}


			}
	}

	// ��� ����������� �������������� ��������� ������
// 40002
	number = _IQtoF(cur_par.speed);
	scale = (float) co2_vars.co_scaleNum14;	// ������� �������� (��/���)
	scaled = scale * number;
	p->Vars.CurSpeed = scaled;

// 40007
	number = _IQtoF(cur_par.Is);
	scale = (float) co2_vars.co_scaleNum4;	//��� ������ �������
	scaled = scale * number;
	p->Vars.CurIs = scaled;

// 40054
	p->Vars.Main_ErrorCode = sm_prot.Main_ErrorCode; //��� ������� ������ (���������, ���� ���������)
}


void MBVarsConv_slow_calc(TMBVarsConv *p) {
	if (p->NeedForSave) {//������� �� ���������� ���������� ������� ����� ������
		p->NeedForSave = 0;

		//��������� ����������� �������� CANopen (��� ��� ���������)
		//������� ������� ���������� � ������� �����������, ��������� �� ���.
		co_ODexpositor_paramConservation(&co2_vars, 1, 1);
		co_ODexpositor_paramConservation(&co2_vars, 2, 1);
		co_ODexpositor_paramConservation(&co2_vars, 3, 1);
		co_ODexpositor_paramConservation(&co2_vars, 1, 2);
		co_ODexpositor_paramConservation(&co2_vars, 2, 2);
		co_ODexpositor_paramConservation(&co2_vars, 3, 2);

		co_ODexpositor_paramConservation(&co2_vars, 1, 3);
		co_ODexpositor_paramConservation(&co2_vars, 2, 3);
		co_ODexpositor_paramConservation(&co2_vars, 3, 3);
		co_ODexpositor_paramConservation(&co2_vars, 1, 4);
		co_ODexpositor_paramConservation(&co2_vars, 2, 4);
		co_ODexpositor_paramConservation(&co2_vars, 3, 4);
		co_ODexpositor_paramConservation(&co2_vars, 1, 5);
		co_ODexpositor_paramConservation(&co2_vars, 2, 5);
		co_ODexpositor_paramConservation(&co2_vars, 3, 5);
	}
}

/*@}*/

