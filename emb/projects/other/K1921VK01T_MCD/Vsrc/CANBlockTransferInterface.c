/* ==================================================================================
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

//File name:       CANBlockTransferInterface.c
//
//Originator:	Aliamkin Dmitry I
//
//Description:   ��� �������������� � ������� ��������� �� CAN ��������������
				 � �� ������� �����
//����������:    
//=====================================================================================
//-------------------------------------------------------------------------------------
		01.09.2016	Release	Rev 1.05
					����� CAN ����������� �������� ��������� � ��� ��� ����������� �������� � ������ ������ (��������� ��� M4F)
		20.09.2012	Release	Rev 1.04
					������� �������������� ������������ �������������� ��� ������� � CANBT_INTERFACE_BUSY ����� 5 ������
		20.09.2012	Release	Rev 1.03
					���������� ������ ����� �� ��������� CANBT_INTERFACE_DATALOG
		19.09.2012	Release	Rev 1.02
					��������� ��������� ������ ������� ����������� ����� ������� ��������
// 	26.12.2011	Release	Rev 1.01
//----------------------------------------------------------------------------------*/
#include "DSP.h"
#include "main.h"
#include "co_ODvars.h"
#include "CANOpen_drv.h"
#include "CANBlockTransferInterface.h"

void SMCanBTInterface_ms(volatile struct SCanBTInterface* p, Uint32 time, TCo_OdVars* co_ptr)
{
	//��������� ������� ��� ������������� �� ������, �.�. ����������, ��� ������������ ������ ������� 
	//���� CANOpen-� ��� ������� ������, ��� ������ ��������� �������� ��������������� ��-�� ����, ���
	//� SPI ����� ���� ���-�� ��������� (�������� ������ �� CAN :))
	if(p->alreadyInit == 0) 
	{
		co_ptr->co_blockTransferCommand = CANBT_INTERFACE_FREE;
		p->time_prev = time;
		p->alreadyInit = 1;
	}
	//������� ���������� �������
    p->state_shadow = co_ptr->co_blockTransferCommand; //�������� ���������� ���������, ��� ��� state ����� ���� ������� ����� ��������
    //����� �� ����������� �� state_shadow
    if (p->state_prev!=p->state_shadow)
    {
        p->E=1;//���� ������� ��������� (E - ENTRY)
        p->state_time = 0;
    }
    else
        p->E=0;
    p->state_prev=p->state_shadow;

    //����� ���������� � ������� ���������
    p->state_time += p->time_prev - time;
    p->time_prev = time;

    switch (p->state_shadow)//� ����������� �� ���������:
    {
		 case CANBT_INTERFACE_FREE:
		 {
			if (p->E)
			  {
					//ENTRY
			  }
			break;
		 }
		 case CANBT_INTERFACE_BUSY:
		 {
			if (p->E)
			  {
					//ENTRY
			  }
			//���� ��������� � ������� ��������� ������� �����, ������ ��� �� ������ ����� �������� �������������
			if(p->state_time > (150000*5000)) //5 ������
				co_ptr->co_blockTransferCommand = CANBT_INTERFACE_FREE;
			break;
		 }
		 case CANBT_INTERFACE_FLASH_PROG:
		 {//���� � �� ����� ����� �� �������� � ������ ����� � default:
			if (p->E)
			  {
					//ENTRY
			  }

			//������������� ���������� �������
			FP_BLOCK_PWM;
			//������� ���������� ���������� sm_ctrl � ���������� ������, ���� �� ��������� ��� ������
			FP_CTRL_STOP;
			FP_FAULT_SET;

			//������� � ������������ ����� �������� � ���� �����.

			break;
		 }
		 case CANBT_INTERFACE_DATALOG1:
		 {
			if (p->E)
			{
				// �������� ������ �� ������� ������������� � ������ ��� �������� �� ���������.
#if DLOG_DATA_SIZE == 16
				//DINT;
				//Uint32 t0 = CpuTimer2Regs.TIM.all;
				/*
				// 'memcpy' �������� 16-������� �������, ��� ��������� ������������ � �������� ��������
				// 'dlog.first_point_written', �� ��� �������� ���������, ��� ������� � ������ 'for'
				// (��. ����) ��� ���������� 32-������ �����.
				size_t n = 256 - dlog.first_point_written;
				memcpy((void*)&dlog.upload_buff[0],
					(void*)&dlog.buff[dlog.first_point_written + (dlog.buff_num << 8)], n);
				memcpy((void*)&dlog.upload_buff[n],
					(void*)&dlog.buff[dlog.buff_num << 8], dlog.first_point_written);
				//Uint32 t1 = t0 - CpuTimer2Regs.TIM.all;
				*/
				//t0 = CpuTimer2Regs.TIM.all;
				Uint32* CopyPtrFrom = (Uint32*)(&dlog.buff[dlog.first_point_written + (dlog.buff_num << 8)]);
				Uint32* CopyPtrTo = (Uint32*)(&dlog.upload_buff[0]);
				for (register int i = 128 - (dlog.first_point_written >> 1); i > 0; i--)
					*CopyPtrTo++ = *CopyPtrFrom++;
				CopyPtrFrom = (Uint32*)(&dlog.buff[dlog.buff_num << 8]);	//��������� �������-��������� ��������� �� ������, ��� �������-��������� �� � ���, ��� ����
				for (register int i = dlog.first_point_written >> 1; i > 0; i--)
					*CopyPtrTo++ = *CopyPtrFrom++;
				//Uint32 t2 = t0 - CpuTimer2Regs.TIM.all;
				//EINT;
#endif
#if DLOG_DATA_SIZE == 32
				//DINT;
				//Uint32 t0 = CpuTimer2Regs.TIM.all;
				Uint32* CopyPtrFrom = (Uint32*)(&dlog.buff[dlog.first_point_written + (dlog.buff_num << 8)]);
				Uint32* CopyPtrTo = (Uint32*)(&dlog.upload_buff[0]);
				for (register int i = 256 - dlog.first_point_written; i > 0; i--)
					*CopyPtrTo++ = *CopyPtrFrom++;
				CopyPtrFrom = (Uint32*)(&dlog.buff[dlog.buff_num << 8]);
				for (register int i = dlog.first_point_written; i > 0; i--)
					*CopyPtrTo++ = *CopyPtrFrom++;
				//Uint32 t1 = t0 - CpuTimer2Regs.TIM.all;
				//EINT;
#endif
				CANBlockTransferInitTX(co_ptr, 256, (Uint16*)&dlog.upload_buff[0]);
			}

			// ���� �� ������� �������� �����������, ����������� � ���������.
			if (co_ptr->BT->tx_status != CANBT_STATUS_BUSY)
			{
				co_ptr->co_blockTransferCommand = CANBT_INTERFACE_FREE;
			}
			break;
		 }
#if DLOG_DATA_SIZE == 32
		 case CANBT_INTERFACE_DATALOG2:
		 {
			if (p->E)
			{
				// ���������� �������� ������ �������� ������ �����������.
				CANBlockTransferInitTX(co_ptr, 256, (Uint16*)&dlog.upload_buff[128]);
			}
			// ���� �� ������� �������� �����������, ����������� � ���������.
			if (co_ptr->BT->tx_status != CANBT_STATUS_BUSY)
			{
				co_ptr->co_blockTransferCommand = CANBT_INTERFACE_FREE;
			}
			break;
		 }
#endif
		 default:
			co_ptr->co_blockTransferCommand = CANBT_INTERFACE_FREE;
    }	
}

void SMCanBTInterface_slow(volatile struct SCanBTInterface* p)
{
	//������� ���������� �������
    switch (p->state_shadow)//� ����������� �� ���������:
    {
		 case CANBT_INTERFACE_FLASH_PROG:
		 {
			if (p->E)
			  {
					//ENTRY
			  }

			//������������� ���������� �������
			FP_BLOCK_PWM;
			//������� ���������� ���������� sm_ctrl � ���������� ������, ���� �� ��������� ��� ������
			FP_CTRL_STOP;
			FP_FAULT_SET;

			//���� �������� (100��), ���� ��� �� ���������� � ���� � ������
			if(p->state_time > (150000*100))
				StartFlashProgrammer();

			break;
		 }
    }
}

//������ ��� ������� �������� ������ ���, ����� �������� ������������ �� ���
void callback_BTcmd(Uint16 par, Uint16 tag_CANnum)
{
	#ifdef CAN_1_ENABLE
		if(tag_CANnum == 1)
		{
			if(par==0)
			{
				if(co1_vars.co_blockTransferCommand == 0)
					co1_vars.co_blockTransferCommand = 0x8000;
			}
			if(par==1)
			{
				if(co1_vars.co_blockTransferCommand == 1)
				{	//�� 1-�� CAN� ����� �����������, ������� ��� � ���������� �������������
					FPsettings.CANa_enable = 1;
					FPsettings.CANb_enable = 0;

				}
			}
		}
	#endif

	#ifdef CAN_2_ENABLE
		if(tag_CANnum == 2)
		{
			if(par==0)
			{
				if(co2_vars.co_blockTransferCommand == 0)
					co2_vars.co_blockTransferCommand = 0x8000;
			}
			if(par==1)
			{
				if(co2_vars.co_blockTransferCommand == 1)
				{	//�� 2-�� CAN� ����� �����������, ������� ��� � ���������� �������������
					FPsettings.CANb_enable = 1;
					FPsettings.CANa_enable = 0;
				}
			}
		}
	#endif
}


