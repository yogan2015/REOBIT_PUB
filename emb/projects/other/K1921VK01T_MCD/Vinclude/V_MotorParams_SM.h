/*    Copyright 2017 	�� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// V_motorParams.h
//���� � ��������� ���������� ������ ��� ��������� ��������� ����

//��������� � ����������� ���������
struct Ssm_param
{
	 float r_f; 			//!< ������������� ��
	 float l_f; 			//!< ������������� ��, ���
	 float l_m; 			//!< ����������� ���������� ������ (�������� �������������)
	 float RatedFluxCurrent;//!< ����������� ��� ��
	 float psi_pm; 			//!< ��������������� ���������� �������� ����
	 float r_s; 			//!< ������������� ������� ����, ��
	 float l_sd; 			//!< ������������� ������� �� ��� "d" ����, ���
	 float l_sq; 			//!< ������������� ������� �� ��� "q" ����, ���
	 float pp; 				//!< ����� ��� �������
	 float j;				//!< ������ �������
	 float qep; 			//!< ����� ����� ��������
	 float RatedPower;		//!< ����������� �������� (���������� ��������, �� ������������ � ��������)
	 float RatedSpeed;		//!< ����������� �������� (���������� ��������, �� ������������ � ��������)
	 float RatedCurrent;	//!< ����������� ����������� ���  (���������� ��������, �� ������������ � ��������)
};
typedef volatile struct Ssm_param Tsm_param;

// !!! ��������! ��������� ����� ���������� � ������� ����������� ������ ���� �������!
Tsm_param SMDATA[] = {\
//		|r_f   |l_f	   |l_m	   |If	   |psi_pm         |r_s    |l_sd   |l_sq   |pp |j          |qep	   |Power	|Speed	|Current
		{0,		0,		0,		0,		0.162056937,	0.38,   0.91,   0.91,	4,  0.00001032, 2500,	0.1,	3000,	4},\
		{0,		0,		0,		0, 		1.035363764, 	21.62, 	45.6,  	53.7,	1,  0.000014,	1000,	0.145,	3000,	0.81},\
		{0,		0,		0,		0,		1.035363764, 	10.2,	27.8,	29.3,	1,	0.000028,	2500,	0.298,	3000,	1.3},\
		{0,		0,		0,		0,		1.035363764, 	5.66,	16.26,	19.42,	1,	0.000042,	3000,	0.425,	3000,	2.3},\
		{0,		0,		0,		0,		0.241876025, 	1.03,	0.82,	0.82,	1,	0.0000831,	5000,	0.4,	2680,	5.9},\
		{0,		0,		0,		0,		0.130691078, 	0.345,	0.273,	0.273,	1,	0.0000831,	10000,	0.4,	4960,	9.56},\
		{0,		0,		0,		0,		0.118074271, 	1.01,  	0.448,	0.448,	1,	0.0000209,	5000,	0.25,	5490,	4.86},\
		{0,		0,		0,		0,		0.064822775, 	0.336, 	0.149, 	0.149,	1,	0.0000209,	2500,	0.25,	10000,	7.94},\
		{0,		0,		0,		0,		1.035363764, 	0.59,  	6.85,  	6.85,	3,	0.00678,	2000,	2.83,	3000,	6.3},\
		{0,		0,		0,		0, 		1.035363764, 	6.5,   	18,    	20,  	3,  0.00417,	3000,	1.7,	3000,	3.8},\
		{0,		0,		0,		0,		0.051993267, 	0.002, 	0.125,	0.125,	1,	0.01,		9000,	93,		60000,	141},\
		{0,		0,		0,		0,		0.414145505, 	1.144, 	5.3,	5.3,	2,	0.000153,	10000,	1.5,	6000,	4.5},\
		{0,		0,		0,		0,		0.865211934, 	0.129, 	4.541,	7.424,	2,	0.1,		10000,	29.864,	3100,	60},\
		{65,	10.21,	1.25,	2.4,	0, 				0.129, 	4.541,	7.424,	2,	0.1,		10000,	29.864,	3100,	60},\
		{0,		0,		0,		0,		0,			    0,		0,		0,		0,	0,			0,		0,		0,		0},\
};
