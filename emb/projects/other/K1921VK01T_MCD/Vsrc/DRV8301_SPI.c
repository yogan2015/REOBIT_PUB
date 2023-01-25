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

 \file    DRV8301_SPI.c
 \brief   ������� ��� �������� ������ ��������� DRV8301
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016
 \addtogroup drv8301interface
 @{
 */

#include "DSP.h"
#include "main.h"

void DRV8301_Interface_Init(Tdrv8301interface*p) {
#ifdef HW_VECTORCARD_DRV8301_EVM
	volatile long delay;
	volatile Uint32 tempREG;

	// ��������� ��� SPI
	NT_GPIOC->ALTFUNCSET = (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11);
	NT_COMMON_REG->GPIOPCTLC_bit.PIN8 = 1;
	NT_COMMON_REG->GPIOPCTLC_bit.PIN9 = 1;
	NT_COMMON_REG->GPIOPCTLC_bit.PIN10 = 1;
	NT_COMMON_REG->GPIOPCTLC_bit.PIN11 = 1;

	// ��������� ������������ SSP ������
	// ����� 4 ������, �� ������ ������ �� 8 ��� �� �������� SSP_CLK_CTRL � �� ��� ���� �� UART_SSP_CLK_SEL

	// UART_SSP_CLK_SEL
	// �� ������ ����� ����� �� ������ �� 4-�� ������� SSP ��������� �� ��� ���� ��� ������ ��������� ������������ 0x0000XX00
	// "00" - � �������� �������� ������������ ������ SSP ���������� ��������� ������� 100 ���, ����� ������� f_SSP_IN = SysClk = 100 MHz

	// SSP_CLK_CTRL
	// ������� ��� ��������� ������������ (1 - ���������)
	// ������ ��� ��������� ������� ������� f_SSP_IN ��������� ��������� ������� (0 - �� ������, 1 - ������)
	// ������� ����� �������� �������� ������� ����� ���������:
	//  X - ������� �� ������� SSPclk = f_SSP_IN /( 2 * (X +1) )
	// �� ������������ �� ���� SSP - ����������� ������� ��� ������ ������ � ������� � ������ � �����,
	// f_SSP_IN > 22.12 MHz, ������� 25 ��� �������
	tempREG = NT_COMMON_REG->UART_SPI_CLK_SEL;// ����� tempREG, ����� �� ������ ������ ����, ���������� �� ������������ UART'a
	tempREG &= 0xFFFF00FF;
	NT_COMMON_REG->UART_SPI_CLK_SEL = tempREG;
	NT_COMMON_REG->SPI_CLK = 0x07070707;// ��������� ������������, ��������� ������� �������, ������ �� 4 - 25 ���

	// ��������� ������ ������ SPI
	// ����������� ��������� ������������.
	// ���������� ����� ������� f_SSP_IN �������� ��� ����� ��� ��������.
	// SSPCPSR - ������ ��������, � ��������� 2 ... 254, ����� ���� ������ ������ (������� ��� ������ ��������� ����� 0)
	// SSPCR0.bit.SCR - ������ �������� �� 0 �� 255.
	// ������� � ����� BitRate = f_SSP_IN / ( SSPCPSR * (SCR + 1) )

	NT_SPI0->SPI_CR1 = 0;// ����� - ������, LoopBack ��������, ��� ������ SSP ���� ��������
	NT_SPI0->SPI_IMSC = 0x0;		// ��������� ��� ����������
	NT_SPI0->SPI_DMACR = 0;		// ��������� DMA
	NT_SPI0->SPI_ICR = 0x3;	// ������� ���������� ("������������ FIFO �����" � "������������� FIFO �����")

	NT_SPI0->SPI_CPSR = 4;			// ������� ������� ������� �� 4 -> 6,25 MHz
	NT_SPI0->SPI_CR0_bit.DSS = 0xF;	// ������ ������ - 16 ���
	NT_SPI0->SPI_CR0_bit.SCR = 0x3F;	// ������ �������� = 15 -> f_SPI = 416 kHz
	NT_SPI0->SPI_CR0_bit.FRF = 0x0;	// �����-�� "����" ��� ��������� Motorola SPI
	NT_SPI0->SPI_CR0_bit.SPH = 0x1;	// �����-�� "����������" ��� ��������� Motorola SPI
	NT_SPI0->SPI_CR0_bit.SPO = 0x0;	// ����� ������� ����� Motorola/TI/Microwire. "0" - �� ��������� Motorola SPI
	NT_SPI0->SPI_CR1_bit.SSE = 1;	// ��������� ������

	// ��������� ��� ��� ����� ������ �� DRV8301: �4 - Fault, C5 - OCTW
	NT_GPIOC->ALTFUNCCLR = (1 << 4) | (1 << 5);
	NT_GPIOC->OUTENCLR = (1 << 4) | (1 << 5);

	// ��������� ���� ��� ��������� DRV8301: G8 - EN_GATE
	NT_GPIOG->ALTFUNCCLR = (1 << 8);
	NT_GPIOG->OUTENSET |= (1 << 8);	//����� ���, ����� �� ��������� ��������� ��� ����� G
	NT_GPIOG->DATA |= (1 << 8);	//DATA.bit.GPIO8 = 1

	// ������� 10 �� ����� ����������
	delay = 10000000;
	while (delay > 0)
		delay--;

	// ��������� ������ DRV8301
	p->CTRL1.bit.GATE_CURRENT = 0;		// full current 1.7A
//			p->CTRL1.bit.GATE_CURRENT = 1;		// med current 0.7A
//			p->CTRL1.bit.GATE_CURRENT = 2;		// min current 0.25A
	p->CTRL1.bit.GATE_RESET = 0;			// Normal Mode
	p->CTRL1.bit.PWM_MODE = 0;			// six independant PWMs
//			p->CTRL1.bit.OC_MODE = 0;				// current limiting when OC detected
	p->CTRL1.bit.OC_MODE = 1;				// latched OC shutdown
//			p->CTRL1.bit.OC_MODE = 2;				// Report on OCTWn pin and SPI reg only, no shut-down
//			p->CTRL1.bit.OC_MODE = 3;				// OC protection disabled
//			p->CTRL1.bit.OC_ADJ_SET = 0;			// OC @ Vds=0.060V
//			p->CTRL1.bit.OC_ADJ_SET = 4;			// OC @ Vds=0.097V
//			p->CTRL1.bit.OC_ADJ_SET = 6;			// OC @ Vds=0.123V
//			p->CTRL1.bit.OC_ADJ_SET = 9;			// OC @ Vds=0.175V
	p->CTRL1.bit.OC_ADJ_SET = 15;			// OC @ Vds=0.358V
//			p->CTRL1.bit.OC_ADJ_SET = 16;			// OC @ Vds=0.403V
//			p->CTRL1.bit.OC_ADJ_SET = 17;			// OC @ Vds=0.454V
//			p->CTRL1.bit.OC_ADJ_SET = 18;			// OC @ Vds=0.511V
	p->CTRL1.bit.Reserved = 0;

//			p->CTRL2.bit.OCTW_SET = 0;			// report OT and OC
	p->CTRL2.bit.OCTW_SET = 1;			// report OT only

//			p->CTRL2.bit.GAIN = 0;				// CS amplifier gain = 10
	p->CTRL2.bit.GAIN = 1;				// CS amplifier gain = 20
//			p->CTRL2.bit.GAIN = 2;				// CS amplifier gain = 40
//			p->CTRL2.bit.GAIN = 3;				// CS amplifier gain = 80

	p->CTRL2.bit.DC_CAL_CH1 = 0;			// not in CS calibrate mode
	p->CTRL2.bit.DC_CAL_CH2 = 0;			// not in CS calibrate mode
	p->CTRL2.bit.OC_TOFF = 0;				// normal mode
	p->CTRL2.bit.Reserved = 0;

	// �������

	p->write(p, CNTRL_REG_1_ADDR);
	p->write(p, CNTRL_REG_2_ADDR);
	p->read(p);
#endif
}

void DRV8301_Interface_Write(Tdrv8301interface*p, Uint16 reg) {
#ifdef HW_VECTORCARD_DRV8301_EVM
	Uint16 trash;

	p->writeWord.bit.R_W = 0;						//we are initiating a write
	p->writeWord.bit.ADDRESS = reg;				//load the address

	if (reg == CNTRL_REG_1_ADDR)
		p->writeWord.bit.DATA = p->CTRL1.all;			//data to be written;
	else
		p->writeWord.bit.DATA = p->CTRL2.all;
	NT_SPI0->SPI_DR = p->writeWord.all;					//send out the data

	while (NT_SPI0->SPI_SR_bit.BSY == 1)
		;		//wait for the packet to complete

	trash = NT_SPI0->SPI_DR;//read returned value of Status Register 1 and clear the INT_FLAG bit
#endif
}

void DRV8301_Interface_Read(Tdrv8301interface*p) {
#ifdef HW_VECTORCARD_DRV8301_EVM
	Uint16 trash;
	// ������� �������, ��� ����� ������ ������ �������
	p->writeWord.bit.R_W = 1;						//we are initiating a read
	p->writeWord.bit.ADDRESS = STAT_REG_1_ADDR;		//load the address
	p->writeWord.bit.DATA = 0;						//dummy data;

	NT_SPI0->SPI_DR = p->writeWord.all;					//send out the data

	while (NT_SPI0->SPI_SR_bit.BSY == 1)
		;		//wait for the packet to complete

	// � ��� ����� DRV ��� ������� ����� (���� ��� �� ������ ���)
	trash = NT_SPI0->SPI_DR;			//dummy read to clear the INT_FLAG bit

	// ������ �������, ��� �������� ������ �������
	p->writeWord.bit.R_W = 1;						//we are initiating a read
	p->writeWord.bit.ADDRESS = STAT_REG_2_ADDR;				//load the address
	p->writeWord.bit.DATA = 0;							//dummy data;

	NT_SPI0->SPI_DR = p->writeWord.all;					//send out the data

	while (NT_SPI0->SPI_SR_bit.BSY == 1)
		;		//wait for the packet to complete

	// � ��� ����� DRV ��� ������� ����� �� ������� ������ - �� ���� ���������� ������� ��������
	p->STS1.all = NT_SPI0->SPI_DR;		//dummy read to clear the INT_FLAG bit

	// ������ �������, ��� ������
	p->writeWord.bit.R_W = 1;						//we are initiating a read
	p->writeWord.bit.ADDRESS = STAT_REG_2_ADDR;				//load the address
	p->writeWord.bit.DATA = 0;							//dummy data;

	NT_SPI0->SPI_DR = p->writeWord.all;					//send out the data

	while (NT_SPI0->SPI_SR_bit.BSY == 1)
		;		//wait for the packet to complete

	// � ��� ����� DRV ��� ������� ����� �� ������� ������ - �� ���� ���������� ������� ��������
	p->STS2.all = NT_SPI0->SPI_DR;
#endif
}
