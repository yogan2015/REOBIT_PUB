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

 \file      X_CANFlashProgStarter.c
 \brief     �������������� ������� ������� �� CAN�
 \author	������� �.
 \version   v 1.0 30/05/2017
*/

/** \addtogroup TCANFlashProgStarter */
/*@{*/


#include "DSP.h"
#include "main.h"
#include "X_CANFlashProgData.h"
#include "X_CANFlashProgStarter.h"
void GPIO_reset();
//� ������ ������� ����� ��������� ��� ������������� � ��� ��������������� ����� ��������� � ������������, 
//����� ����� ��������� ������ ���� �������������, ������������� � ��� (��� ��� ��� ����� ��������������� 
//���������� ���������� � ������ �������)
TFlashProgSettings FPsettings;
void StartFlashProgrammer() 							
{
	Uint16 i,j;
	volatile Uint8* sourcePtr;
	volatile Uint8* destPtr;
	volatile Uint16* sourcePtr16;
	volatile Uint16* destPtr16;
	void (*FlashProgProjectCall)(void);

	//��������� ��� ����������
	DINT;
	//��� ��������� ��� ���������� NVIC
	/*NVIC->ICER[0] = 0xFFFFFFFF;
	NVIC->ICER[1] = 0xFFFFFFFF;
	NVIC->ICER[2] = 0xFFFFFFFF;
	NVIC->ICER[3] = 0xFFFFFFFF;
	NVIC->ICER[4] = 0xFFFFFFFF;*/

	//��������� ��� GPIO � �������� ���������
	GPIO_reset();
	//�������������� GPIO CAN�� ���, ��� ��� ������������ �� ����� ����� ����� ����� ������� CAN � ������������
	#ifdef FP_DEVICE_M4F
		#ifdef CAN_1_ENABLE
			co_CAN1GpioInit();
		#endif
		#ifdef CAN_2_ENABLE
			co_CAN2GpioInit();
		#endif
	#endif
	//�������� ��������� �������������
	FPsettings.magic_number = 0x1234;
	
	#if defined(CAN_1_ENABLE) && defined(CAN_2_ENABLE)
		//���� ��������� ��� CAN-�, CANx_enable	���������� � call_back ��������
		FPsettings.CANa_bitRate = co1_vars.co_bitRate;
		FPsettings.CANa_nodeID = co1_vars.co_nodeID;
		FPsettings.CANb_bitRate = co2_vars.co_bitRate;
		FPsettings.CANb_nodeID = co2_vars.co_nodeID;
	#else
		#ifdef CAN_1_ENABLE
			FPsettings.CANa_enable = 1;
			FPsettings.CANb_enable = 0;
			FPsettings.CANa_bitRate = co1_vars.co_bitRate;
			FPsettings.CANa_nodeID = co1_vars.co_nodeID;
		#else
			FPsettings.CANa_enable = 0;
		#endif
		
		#ifdef CAN_2_ENABLE
			FPsettings.CANa_enable = 0;
			FPsettings.CANb_enable = 1;	
			FPsettings.CANb_bitRate = co2_vars.co_bitRate;
			FPsettings.CANb_nodeID = co2_vars.co_nodeID;
		#else
			FPsettings.CANb_enable = 0;
		#endif 
	#endif	
	
	//�������� ��������� �������������, �� ������� ������
	sourcePtr = (Uint8*)&FPsettings;
	destPtr = ((Uint8*)0x20000064);//��������� ������ �������� �� 2 ����� ���� ���������� ������
	for(i=0; i<sizeof(TFlashProgSettings); i++)
	{
		*destPtr++ = *sourcePtr++;
	}
	
	//�������� ��� ����� ������������� ���� ���� �����
	sourcePtr16 = (Uint16*)&FPData[0];
	for(i=0; i<FPNumOfAddrs; i++)
	{
		destPtr16 = (Uint16*)FPAddrs[i];
		for(j=0; j<(FPPartsLength[i]); j++)
		*destPtr16++ = *sourcePtr16++;
	}
 
	//���� � ������������
	((void (*)(void))(0x20000001))();
}

void GPIO_reset()
{
	K1921VK01T_GPIO_SafeInit();
	//����� ����� ������������������� ����� �� � ������ ���������
	//����� ���������, ���� ���� ������� ������.
}

long swu_vars = 0;



/*@}*/

