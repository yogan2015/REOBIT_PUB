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
 \brief     ������ � ���������������� ����������������� ������� 1921BK028 (��. TUserMemory)
 \author	�������� �.�., ���� �.�.
 \version   v 1.0 21/03/2019
*/

/** \addtogroup TUserMemory */
/*@{*/

#include "main.h"
#include "DSP.h"




//!�������������

//!������������� USERMEMORY
//! \memberof TUserMemory
void  USERMEMORY_Init(TUserMemory *p)
{
	USERMEMORY_ReadToCache(p,0);//������ � ���������� ������� �������� (����� ���� ������� �������� � ��� �������� ��������� ������)
}

//! ��������������� ������� �������� ��������, ��������� "0" ���� �� ��, � "1", ���� �� �� ��
Uint16 waitUserFlashBusy (TUserMemory *p) {
	p->waitClocks = 0;
	__NOP();		// � ������������ ������� ��������� ����� ��������� �������
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	while(NVRFLASH->STAT_bit.BUSY == 0x1){//����
		p->waitClocks++;
		if (p->waitClocks > USERMEMORY_MAX_WAITCLOCKS){//������ �����
			return 1;
		}
	}
	return 0;
}
//! ��������, �� ����� �� ������� ��������

//! ��������� ������� ����� �� ������, � ������� �������� ������������. ���� ����� ����� �� ������� ��������, �������� ������������ �� ���� � �������� � RAM �����
//! \memberof TUserMemory
void USERMEMORY_UpdateCurrentPage(TUserMemory *p, Uint16 spiaddr)
{
	Uint16 newPage=spiaddr>>PAGE_SIZE_LOG2;//����� �������� - ��� ������� �������� ������, ��� ��� �������� 256 ����
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
		Uint16 addrInPage=spiaddrTmp&0xFFFF;//����� ������ ��������
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
		Uint16 addrInPage=spiaddrTmp&0xFFFF;//����� ������ ��������
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
	int16 i = 0, readDataWord = 0;
	Uint32 *arrayPointer;
	Uint16 addrOffset=pageNum*USERMEMORY_PAGE_SIZE;//��������� ����� �� ������ (�� ������ ��������)
	NVRFLASH->STAT = 0x3;//����� �������
	NVRFLASH->ADDR = addrOffset;//����� ������ ��������
	NVRFLASH->CMD = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_PAGE_ERASE);//������� ��������

	if (waitUserFlashBusy(p) != 0){
		p->receivedCode = USERMEMORY_WRITE_TIMEOUT;
		return;
	}

	for(i = 0; i < USERMEMORY_PAGE_SIZE; i += NUMBER_OF_BYTE_ON_PAGE){//���� �� ������� ��������
		NVRFLASH->STAT = 0x3;					//����� �������
		NVRFLASH->ADDR = addrOffset + i;	//�����

		arrayPointer = (Uint32*)(&p->cacheArr[i]);
		for (readDataWord = 0; readDataWord < NUMBER_OF_32BIT_WORDS_AT_ONCE; readDataWord++){
			NVRFLASH->DATA[readDataWord].DATA = *arrayPointer;
			arrayPointer++;
		}

		NVRFLASH->CMD = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_WRITE);//������� �� ������ �����

		if (waitUserFlashBusy(p) != 0){
			p->receivedCode = USERMEMORY_WRITE_TIMEOUT;
			return;
		}
	}
	NVRFLASH->STAT = 0x3;//����� �������
	p->receivedCode = USERMEMORY_OP_OK;//��� ������
	p->PageRAM_and_FLASH_IdenticalFlag=1;//������ �������� � ���������� � �� ����� ������ ���������
}



//! ������ �������� ������ �� ����� � ��� (� ����������)

//! \memberof TUserMemory
void USERMEMORY_ReadToCache(TUserMemory *p, int16 pageNum)
{
	int16 i = 0, readDataWord = 0;
	Uint16 addrOffset = pageNum * USERMEMORY_PAGE_SIZE;//��������� ����� �� ������ (�� ������ ��������)
	Uint32 *arrayPointer;
	for(i = 0; i < USERMEMORY_PAGE_SIZE; i += NUMBER_OF_BYTE_ON_PAGE){//���� �� ������� ��������
		NVRFLASH->STAT = 0x3;//����� �������
		NVRFLASH->ADDR = addrOffset + i;//�����
		NVRFLASH->CMD = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_READ);//������� �� ������ �����


		if (waitUserFlashBusy(p) != 0){
			p->receivedCode = USERMEMORY_READ_TIMEOUT;
			return;
		}
		arrayPointer = (Uint32*)&(p->cacheArr[i]);

		// ����������� �� 16 ��� 4 32-��������� �����{
		for (readDataWord = 0; readDataWord < NUMBER_OF_32BIT_WORDS_AT_ONCE; readDataWord++){
			*arrayPointer = NVRFLASH->DATA[readDataWord].DATA;//������ (���� ����) � ����������
			arrayPointer++;
		}

	}
	NVRFLASH->STAT = 0x3;//����� �������
	p->receivedCode = USERMEMORY_OP_OK;
	p->PageInCache=pageNum;//����� �������� ������ � ����
	p->PageRAM_and_FLASH_IdenticalFlag=1;//������ � ���������� (� ����) ��������� � ������
}


//! ������� ��� ������ (����� FF)

//! \memberof TUserMemory
void USERMEMORY_Full_Erase(TUserMemory *p){
	// C���� �������, ������� �������� � �������� ����������
	NVRFLASH->STAT = 0x3;
	NVRFLASH->CMD = (USERMEMORY_USERFLASH_KEY | USERMEMORY_CMD_FULL_ERASE);//������� �� �������� ���� �����
	__NOP();		// � ������������ ������� ��������� ����� ��������� �������
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	while(NVRFLASH->STAT_bit.BUSY == 0x1){};

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

