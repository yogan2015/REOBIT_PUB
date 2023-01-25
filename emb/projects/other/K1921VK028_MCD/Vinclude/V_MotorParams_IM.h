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
// V_motorParams_IM.h
//���� � ��������� ���������� ������ ��� ��������� ��������� ��

//��������� � ����������� ���������
struct SIm_param
{
	 float l_s; 		//!< ������������� ������� ��, ���
	 float l_r; 		//!<������������� ������ ��, ���
	 float l_m; 		//!< �������� ������������� ��, ���
	 float r_s; 		//!< ������������� ������� ��, ��
	 float r_r; 		//!< ������������� ������ ��, ��
	 float pp; 			//!< ����� ��� �������
	 float j;			//!< ������ �������
	 float qep; 		//!< ����� ����� ��������
	 float RatedPower;	//!< ����������� �������� (���������� ��������, �� ������������ � ��������)
	 float RatedSpeed;	//!< ����������� �������� (���������� ��������, �� ������������ � ��������)
	 float RatedCurrent;//!< ����������� ����������� ���
};
typedef volatile struct SIm_param TIm_param;

// !!! ��������! ��������� ����� ���������� � ������� ����������� ������ ���� �������!
TIm_param IMDATA[] = {\
//		|l_s		   |l_r			   |l_m			   |r_s			   |r_r			   |pp |j		   |qep	  |Power	|Speed	|Current
		{5590.601309,	5737.268318,	5392.169472,	101.64,			94.864,			1,	0.000025,	10000,	0.09,	2742,	0.33},\
		{396.0356208,	400.9617219,	389.5056727,	2.59129728,		1.69154128,		1,	0.0035,		10000,	3,		2871,	6.11},\
		{143.0596483,	145.1464178,	139.1179724,	0.6992832,		0.4807572,		2,	0.028,		7500,	7.5,	1456.5,	15.1},\
		{100.2417862,	101.3460409,	98.15597183,	0.362330144,	0.1927288,		2,	0.1,		7500,	15,		1465.5,	28.5},\
		{71.64092383,	72.15142923,	69.76907071,	0.2673,			0.128304,		3,	0.4,		7500,	22,		977,	41.2},\
		{38.44412805,	38.74763433,	37.43244047,	0.133489031,	0.060387895,	3,	0.74,		7500,	37,		982,	69.2},\
		{21.18984563,	21.74726654,	20.41259675,	0.091259168,	0.039463424,	4,	0.4,		5000,	45,		732.75,	89.2},\
		{17.01462802,	17.14451068,	16.23533208,	0.07140672,		0.044884224,	4,	3.2,		5000,	55,		733.5,	107.8},\
		{10.47720097,	10.65862436,	9.978286639,	0.041321984,	0.038472192,	5,	6.2,		5000,	75,		590.4,	154.4},\
		{6.858182237,	7.037715804,	6.463208391,	0.027073024,	0.022560853,	6,	10,			5000,	90,		493.5,	195},\
		{0,				0,				0,				0,				0,				0,	0,			0,		0,		0,		0},\
};
