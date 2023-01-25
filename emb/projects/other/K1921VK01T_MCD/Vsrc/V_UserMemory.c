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

 \file      V_UserMemory.c
 \brief     ������ � ���������������� ����������������� ������� 1921BK01 (��. TUserMemory)
 \author	�������� �.�., ���� �.�.
 \version   v 1.0 18/12/2014
*/

/** \addtogroup TUserMemory */
/*@{*/

#include <V_UserMemory.h>
#include "DSP.h"




//!�������������

//!������������� USERMEMORY
//! \memberof TUserMemory
void  USERMEMORY_Init(TUserMemory *p)
{
	USERMEMORY_ReadToCache(p,0);//������ � ���������� ������� �������� (����� ���� ������� �������� � ��� �������� ��������� ������)
}


//! ��������, �� ����� �� ������� ��������

//! ��������� ������� ����� �� ������, � ������� �������� ������������. ���� ����� ����� �� ������� ��������, �������� ������������ �� ���� � �������� � RAM �����
//! \memberof TUserMemory
void USERMEMORY_UpdateCurrentPage(TUserMemory *p, Uint16 spiaddr)
{
	Uint16 newPage=spiaddr>>8;//����� �������� - ��� ������� �������� ������, ��� ��� �������� 256 ����
	if (newPage!=p->PageInCache){//�������� ������?
		if (p->PageRAM_and_FLASH_IdenticalFlag==0)//� ���� ���������� ������ � ���� �������� � ���������� � ����?
			USERMEMORY_Flush(p);//�������� �������� �� ����
		if (p->receivedCode!=USERMEMORY_OP_OK)//�� �����?
			return;
		//������ � ���������� ����� ��������
		USERMEMORY_ReadToCache(p,newPage);
		if (p->receivedCode!=USERMEMORY_OP_OK)//�� �����?
			return;
	}
}


//! ������ � ������

//!��������� �������, ������������ �� flash �������� ������.
//!�������� � ��������������� � ���������� �������, � �������� ����� �� ���� ������ ���� ����� ����� �� ������� ������� ��������

//! ����� �� ����� spiaddr, ����� 16�� ��������� ������ ������������ startaddr, ������ data_length. ��� � ������
//! ��� ��������� �������� startaddr ����������������, � spiaddr ���
//! \memberof TUserMemory
void USERMEMORY_Write(TUserMemory *p)
{
	Uint16 i = 0;
	Uint16 spiaddrTmp=p->MemStartAddr;//����� �� ����� � ������
	p->MCUStartAddr8=(Uint8*)p->MCUStartAddr;//������ ��������� �� ������ - �� ��������� �� 16�� ��������� ������ �� ��������� �� ����� - ��� �������
	for(i = 0; i < p->data_length; i++){//�� ���� ������, ��� ����� ������������
		USERMEMORY_UpdateCurrentPage(p,spiaddrTmp);//������� � ���������� ��������, ���� ��� ������
		Uint16 addrInPage=spiaddrTmp&0xFF;//����� ������ ��������
		if (p->cacheArr[addrInPage] != (*(p->MCUStartAddr8))){//������ �� ��������� � ���, ��� ��� � ���������� � ���� �����?
			p->cacheArr[addrInPage]=(*(p->MCUStartAddr8));//������ ������ � ����������
			p->PageRAM_and_FLASH_IdenticalFlag=0;//����, ��� ������ � ���������� ���������� �� ���������� �� �����
		}
		spiaddrTmp++;
		p->MCUStartAddr8++;
	}
	//p->MCUStartAddr=(Uint16*)p->MCUStartAddr8;//����� ����� �� ������ ��������� (�� ����, ���� ��� ���� ��� ���)
	p->receivedCode = USERMEMORY_OP_OK;
}


//! ������ �� ������

//!��������� �������, ����������� �� flash �������� ������. ����������� ��. TUserMemory.

//! ����� �� ����� spiaddr, ����� ����� 16�� ��������� ������ ������������ startaddr, ������ data_length. ��� � ������.
//! ��� ��������� �������� startaddr ����������������, � spiaddr ���
//! \memberof TUserMemory
void USERMEMORY_Read(TUserMemory *p)
{
	Uint16 i = 0;
	Uint16 spiaddrTmp=p->MemStartAddr;
	p->MCUStartAddr8=(Uint8*)p->MCUStartAddr;
	for(i = 0; i < p->data_length; i++){//�� ���� ������, ��� ����� ������������
		USERMEMORY_UpdateCurrentPage(p,spiaddrTmp);//������� � ���������� ��������, ���� ��� ������
		Uint16 addrInPage=spiaddrTmp&0xFF;//����� ������ ��������
		*(p->MCUStartAddr8) = p->cacheArr[addrInPage];//������ ������ �� ����������, ��� ������ ���� ��� ���������� ����� USERMEMORY_UpdateCurrentPage
		spiaddrTmp++;
		p->MCUStartAddr8++;
	}
	p->MCUStartAddr=(Uint16*)p->MCUStartAddr8;//����� ����� �� ������ ��������� (�� ����, ���� ��� ���� ��� ���)
	p->receivedCode = USERMEMORY_OP_OK;
}


//! ���������� �������� ������ �� ������ �� ���� (�� ���������� ���� ��������)

//! \memberof TUserMemory
void USERMEMORY_WriteFromCache(TUserMemory *p, int16 pageNum)
{
	int16 i = 0;
	int16 addrOffset=pageNum*USERMEMORY_PAGE_SIZE;//��������� ����� �� ������ (�� ������ ��������)
	NT_USERFLASH->FCIC = 0x3;//����� �������
	NT_USERFLASH->FMA = addrOffset;//����� ������ ��������
	NT_USERFLASH->FMC = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_PAGE_ERASE);//������� ��������
	p->waitClocks = 0;
	while(NT_USERFLASH->FCIS != 0x1){//���� ��������
		if (NT_USERFLASH->FCIS == 0x2){//�� ������
			NT_USERFLASH->FCIC = 0x3;
			p->receivedCode = USERMEMORY_WRITE_HARDFAULT;
			return;
		}
		p->waitClocks++;//���-���
		if (p->waitClocks > (256*USERMEMORY_MAX_WAITCLOCKS)){//������ �����
			p->receivedCode = USERMEMORY_WRITE_TIMEOUT;
			return;
		}
	}

	for(i = 0; i < USERMEMORY_PAGE_SIZE; i++){//���� �� ������� ��������
		NT_USERFLASH->FCIC = 0x3;//����� �������
		NT_USERFLASH->FMA = addrOffset+i;//�����
		NT_USERFLASH->FMD = p->cacheArr[i];//������ �� ����������
		NT_USERFLASH->FMC = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_WRITE);//������� �� ������ �����

		p->waitClocks = 0;
		while(NT_USERFLASH->FCIS != 0x1){//����
			if (NT_USERFLASH->FCIS == 0x2){
				NT_USERFLASH->FCIC = 0x3;
				p->receivedCode = USERMEMORY_WRITE_HARDFAULT;//������
				return;
			}
			p->waitClocks++;//��� ����� ����?
			if (p->waitClocks > USERMEMORY_MAX_WAITCLOCKS){//������ �����
				p->receivedCode = USERMEMORY_WRITE_TIMEOUT;//������ �� ��������
				return;
			}
		}
	}
	NT_USERFLASH->FCIC = 0x3;//����� �������
	p->receivedCode = USERMEMORY_OP_OK;//��� ������
	p->PageRAM_and_FLASH_IdenticalFlag=1;//������ �������� � ���������� � �� ����� ������ ���������
}



//! ������ �������� ������ �� ����� � ��� (� ����������)

//! \memberof TUserMemory
void USERMEMORY_ReadToCache(TUserMemory *p, int16 pageNum)
{
	int16 i = 0;
	int16 addrOffset=pageNum*USERMEMORY_PAGE_SIZE;//��������� ����� �� ������ (�� ������ ��������)

	for(i = 0; i < USERMEMORY_PAGE_SIZE; i++){//���� �� ������� ��������
		NT_USERFLASH->FCIC = 0x3;//����� �������
		NT_USERFLASH->FMA = addrOffset+i;//�����
		NT_USERFLASH->FMC = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_READ);//������� �� ������ �����

		p->waitClocks = 0;
		while(NT_USERFLASH->FCIS != 0x1){//����
			if (NT_USERFLASH->FCIS == 0x2){
				NT_USERFLASH->FCIC = 0x3;
				p->receivedCode = USERMEMORY_READ_HARDFAULT;
				return;
			}
			p->waitClocks++;
			if (p->waitClocks > USERMEMORY_MAX_WAITCLOCKS){//������ �����
				p->receivedCode = USERMEMORY_READ_TIMEOUT;
				return;
			}
		}
		p->cacheArr[i]=NT_USERFLASH->FMD;//������ (���� ����) � ����������
	}
	NT_USERFLASH->FCIC = 0x3;//����� �������
	p->receivedCode = USERMEMORY_OP_OK;
	p->PageInCache=pageNum;//����� �������� ������ � ����
	p->PageRAM_and_FLASH_IdenticalFlag=1;//������ � ���������� (� ����) ��������� � ������
}


//! ������� ��� ������ (����� FF)

//! \memberof TUserMemory
void USERMEMORY_Full_Erase(TUserMemory *p){
	NT_USERFLASH->FCIC = 0x3;//����� �������
	NT_USERFLASH->FMC = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_FULL_ERASE);//������� �� �������� ���� �����
	while(NT_USERFLASH->FCIS != 0x1){};

}


//! �������� ��� �� ���������� �� ������

//! \memberof TUserMemory
void USERMEMORY_Flush(TUserMemory *p){
	USERMEMORY_WriteFromCache(p,p->PageInCache);
}

//! ��������� ������� ���������� ������ - ����� ���� ��� ���������������� ������ ���� �� ������ �� �������

//! \memberof TUserMemory
void USERMEMORY_slow_calc(TUserMemory *p){
	if (p->NeedFlushRequest){//���� �������?
		USERMEMORY_Flush(p);
		p->NeedFlushRequest=0;
	}
}

//! �������������� ������ - ����� ���� ��� ���������������� ������ ���� �� ������ �� �������

//! \memberof TUserMemory
void USERMEMORY_ms_calc(TUserMemory *p){

	if (!p->PageRAM_and_FLASH_IdenticalFlag)//������ �� ������ � � ���������� �� ���������
		p->autoFlushCounter++;

	if (p->autoFlushCounter>10000) //������ �� ������������
		p->autoFlushCounter=10000;

	if (p->autoFlushCounter>500){//����� �� ������������ �� ������
		p->NeedFlushRequest=1;//���� �������, �� ��� ��� ������ ������, ��� ����������, ������ ������� ����
		p->autoFlushCounter=0;
	}

}



/*@}*/

