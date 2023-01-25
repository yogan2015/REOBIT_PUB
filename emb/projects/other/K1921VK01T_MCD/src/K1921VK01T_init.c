/******************************************************************************
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

 * @file		K1921VK01T_init.c
 * @brief		���� ��������������� ������������� ��������� ����������������
 * @version		v1.0
 * @date		11 ������� 2015
 *
 * @author	 	��� "��� ������" (http://motorcontrol.ru)
 *
 ******************************************************************************/
#include "DSP.h"
#include "main.h"


//System clock sources
#define SYSCLK_REFCLK       0
#define SYSCLK_PORCLK       1
#define SYSCLK_OSCCLK       2
#define SYSCLK_PLLCLK       3
#define SYSCLK_PLLDIVCLK    4
#define SYSCLK_USB60CLK     5
#define SYSCLK_USB12CLK     6
#define SYSCLK_ETH25CLK     7

//! ��������� ����������� ������ �����, �� ����������� ���������
void propReset(void) {
	int i;
	// ������ ����������
	DINT;

	//��������� �� ������������ �� ����������� ������
	do
	{
		NT_COMMON_REG->SYS_CLK = 0;
		for(i = 0; i < 50; i++);
	}
	while (NT_COMMON_REG->SYS_CLK_bit.CURR_SRC != SYSCLK_REFCLK);

	//��������������� PLL ���, ����� � ��������� 2 �������� ~100 ���
	NT_COMMON_REG->PLL_NR = 1;
	NT_COMMON_REG->PLL_NF = 24;
	NT_COMMON_REG->PLL_OD = 0;
	NT_COMMON_REG->PLL_CTRL_bit.PD = 0;

	// ��������� �� ������������ �� PLL/DIV
	do
	{
		NT_COMMON_REG->SYS_CLK = 0;
		NT_COMMON_REG->SYS_CLK = 4;
		for(i = 0; i < 50; i++);
	}
	while (NT_COMMON_REG->SYS_CLK_bit.CURR_SRC != SYSCLK_PLLDIVCLK);

	// ������ �����
	SCB->AIRCR=0x05FA0004;

}
//��������� ���������� ������������� �������������� ������� ���������� �����.
//���� � �� �� ������� ����� ���� ��������� ��� ���������� �����. � ����� ������ �� ����� �������� �� ���� �� ���, ����
//���� ��� ��������� � ������ ����������� �����-������, �.�. ����. ������� ���������.
//��� ���������� ������������� ������ ����� ����������� ����. �������, ������� � ���������� ������������ ����� �������������.
//������������ ����. ������� ��� ������ ����� ����� ������������� � ������������ � ����������� �������.
void K1921VK01T_GPIO_SafeInit()
{
    //������ �������������� ������� ����� �� ��������� ��� ����� ������
    //������� ��� �������, ����� ������
    NT_GPIOA->ALTFUNCCLR = 0xFFFFFFFF;
    NT_GPIOB->ALTFUNCCLR = 0xFFFFFFFF - 0x7;
    NT_GPIOC->ALTFUNCCLR = 0xFFFFFFFF;
    NT_GPIOD->ALTFUNCCLR = 0xFFFFFFFF - 0x800;
    NT_GPIOE->ALTFUNCCLR = 0xFFFFFFFF - 0x403;
    NT_GPIOF->ALTFUNCCLR = 0xFFFFFFFF;
    NT_GPIOG->ALTFUNCCLR = 0xFFFFFFFF;
    NT_GPIOH->ALTFUNCCLR = 0xFFFFFFFF;

	//��� ����� - �� ����
	NT_GPIOA->OUTENCLR = 0xFFFFFFFF;
	NT_GPIOB->OUTENCLR = 0xFFFFFFFF;
	NT_GPIOC->OUTENCLR = 0xFFFFFFFF;
	NT_GPIOD->OUTENCLR = 0xFFFFFFFF;
	NT_GPIOE->OUTENCLR = 0xFFFFFFFF;
	NT_GPIOF->OUTENCLR = 0xFFFFFFFF;
	NT_GPIOG->OUTENCLR = 0xFFFFFFFF;
	NT_GPIOH->OUTENCLR = 0xFFFFFFFF;

	//����� ����. ������� �� "������ ����� �����������������"
	NT_COMMON_REG->GPIOPCTLA_bit.PIN0 = 2;	//RAM_DATA[12]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN1 = 2;	//trace_dat[3]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN2 = 2;	//RAM_Oen[0]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN3 = 2;	//RAM_Oen[1]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN4 = 2;	//trace_dat[2]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN5 = 2;	//trace_dat[0]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN6 = 2;	//trace_dat[1]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN7 = 2;	//trace_clk
	NT_COMMON_REG->GPIOPCTLA_bit.PIN8 = 0;	//RAM_ADDR[0]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN9 = 0;	//RAM_ADDR[1]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN10 = 0;	//RAM_ADDR[2]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN11 = 0;	//RAM_ADDR[3]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN12 = 0;	//RAM_ADDR[4]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN13 = 0;	//RAM_ADDR[5]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN14 = 0;	//RAM_ADDR[6]
	NT_COMMON_REG->GPIOPCTLA_bit.PIN15 = 0;	//RAM_ADDR[7]

	//NT_COMMON_REG->GPIOPCTLB_bit.PIN0 = 2;	//RAM_Wen		������������ ��� TDI JTAG'�
	//NT_COMMON_REG->GPIOPCTLB_bit.PIN1 = 2;	//RAM_Cen[0]	������������ ��� TMS JTAG'�
	//NT_COMMON_REG->GPIOPCTLB_bit.PIN2 = 2;	//RAM_Cen[1]	������������ ��� TCK JTAG'�
	NT_COMMON_REG->GPIOPCTLB_bit.PIN3 = 2;	//RAM_ADDR[0]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN4 = 0;	//RAM_ADDR[8]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN5 = 0;	//RAM_ADDR[9]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN6 = 0;	//RAM_ADDR[10]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN7 = 0;	//RAM_ADDR[11]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN8 = 0;	//RAM_ADDR[12]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN9 = 0;	//RAM_ADDR[13]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN10 = 0;	//RAM_ADDR[14]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN11 = 0;	//RAM_ADDR[15]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN12 = 0;	//RAM_ADDR[16]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN13 = 0;	//RAM_ADDR[17]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN14 = 0;	//RAM_ADDR[18]
	NT_COMMON_REG->GPIOPCTLB_bit.PIN15 = 0;	//RAM_DATA[0]

	NT_COMMON_REG->GPIOPCTLC_bit.PIN0 = 2;	//RAM_ADDR[1]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN1 = 2;	//RAM_ADDR[2]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN2 = 2;	//RAM_ADDR[3]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN3 = 2;	//RAM_ADDR[4]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN4 = 2;	//RAM_ADDR[5]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN5 = 2;	//RAM_ADDR[6]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN6 = 0;	//RAM_DATA[1]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN7 = 0;	//RAM_DATA[2]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN8 = 0;	//RAM_DATA[3]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN9 = 0;	//RAM_DATA[4]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN10 = 0;	//RAM_DATA[5]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN11 = 0;	//RAM_DATA[6]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN12 = 0;	//RAM_DATA[7]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN13 = 0;	//RAM_DATA[8]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN14 = 0;	//RAM_DATA[9]
	NT_COMMON_REG->GPIOPCTLC_bit.PIN15 = 0;	//RAM_DATA[10]

	NT_COMMON_REG->GPIOPCTLD_bit.PIN0 = 2;	//RAM_ADDR[7]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN1 = 2;	//RAM_ADDR[8]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN2 = 2;	//RAM_ADDR[9]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN3 = 2;	//RAM_ADDR[10]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN4 = 2;	//RAM_ADDR[11]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN5 = 2;	//RAM_ADDR[12]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN6 = 2;	//RAM_DATA[0]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN7 = 2;	//RAM_DATA[1]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN8 = 2;	//RAM_DATA[2]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN9 = 2;	//RAM_DATA[3]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN10 = 2;	//RAM_DATA[4]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN11 = 2;	//eCMP_OUT[0]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN12 = 0;	//RAM_DATA[11]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN13 = 0;	//RAM_DATA[12]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN14 = 0;	//RAM_DATA[13]
	NT_COMMON_REG->GPIOPCTLD_bit.PIN15 = 0;	//RAM_DATA[14]

	NT_COMMON_REG->GPIOPCTLE_bit.PIN0 = 2;	//eCMP_OUT[1]
	//NT_COMMON_REG->GPIOPCTLE_bit.PIN1 = 2;	//UART_TxD[2]	������������ ��� TRST JTAG'�
	NT_COMMON_REG->GPIOPCTLE_bit.PIN2 = 2;	//RAM_DATA[6]
	NT_COMMON_REG->GPIOPCTLE_bit.PIN3 = 2;	//RAM_DATA[7]
	NT_COMMON_REG->GPIOPCTLE_bit.PIN4 = 2;	//Timer_IN[0]
	NT_COMMON_REG->GPIOPCTLE_bit.PIN5 = 2;	//RAM_LBn
	NT_COMMON_REG->GPIOPCTLE_bit.PIN6 = 2;	//RAM_DATA[8]
	NT_COMMON_REG->GPIOPCTLE_bit.PIN7 = 0;	//USB_DRVVBUS
	NT_COMMON_REG->GPIOPCTLE_bit.PIN8 = 2;	//SSP_FSS[1]
	NT_COMMON_REG->GPIOPCTLE_bit.PIN9 = 2;	//SSP_CLK[1]
	//NT_COMMON_REG->GPIOPCTLE_bit.PIN10 = 2;	//RAM_Ubn		������������ ��� TDO JTAG'�
	NT_COMMON_REG->GPIOPCTLE_bit.PIN11 = 2;	//RAM_DATA[10]
	NT_COMMON_REG->GPIOPCTLE_bit.PIN12 = 0;	//RAM_DATA[15]
	NT_COMMON_REG->GPIOPCTLE_bit.PIN13 = 0;	//RAM_Wen
	NT_COMMON_REG->GPIOPCTLE_bit.PIN14 = 0;	//RAM_Oen[0]
	NT_COMMON_REG->GPIOPCTLE_bit.PIN15 = 0;	//RAM_Oen[1]

	NT_COMMON_REG->GPIOPCTLF_bit.PIN0 = 2;	//SSP_TxD[1]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN1 = 2;	//RAM_DATA[11]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN2 = 1;	//SSP_CLK[3]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN3 = 2;	//RAM_DATA[14]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN4 = 2;	//UART_RxD[2]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN5 = 2;	//RAM_DATA[9]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN6 = 0;	//RAM_Cen[0]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN7 = 0;	//RAM_Cen[1]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN8 = 0;	//RAM_LBn
	NT_COMMON_REG->GPIOPCTLF_bit.PIN9 = 0;	//RAM_Ubn
	NT_COMMON_REG->GPIOPCTLF_bit.PIN10 = 1;	//---
	NT_COMMON_REG->GPIOPCTLF_bit.PIN11 = 1;	//---
	NT_COMMON_REG->GPIOPCTLF_bit.PIN12 = 1;	//UART_RI[2]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN13 = 1;	//UART_DTR[2]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN14 = 1;	//UART_RTS[2]
	NT_COMMON_REG->GPIOPCTLF_bit.PIN15 = 1;	//UART_DCD[2]

	NT_COMMON_REG->GPIOPCTLG_bit.PIN0 = 0;	//sda[0]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN1 = 0;	//eCMP_OUT[0]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN2 = 2;	//SSP_RxD[1]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN3 = 1;	//SSP_FSS[3]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN4 = 2;	//UART_TxD[2]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN5 = 2;	//RAM_DATA[13]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN6 = 2;	//RAM_DATA[15]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN7 = 2;	//RAM_DATA[5]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN8 = 1;	//UART_DSR[2]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN9 = 2;	//UART_RTS[3]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN10 = 2;	//---
	NT_COMMON_REG->GPIOPCTLG_bit.PIN11 = 2;	//Timer_IN[1]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN12 = 2;	//Timer_IN[2]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN13 = 0;	//trace_dat[0]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN14 = 0;	//trace_dat[1]
	NT_COMMON_REG->GPIOPCTLG_bit.PIN15 = 0;	//trace_dat[2]

	NT_COMMON_REG->GPIOPCTLH_bit.PIN0 = 0;	//trace_dat[3]
	NT_COMMON_REG->GPIOPCTLH_bit.PIN1 = 1;	//---
	NT_COMMON_REG->GPIOPCTLH_bit.PIN2 = 1;	//---
	NT_COMMON_REG->GPIOPCTLH_bit.PIN3 = 1;	//---
	NT_COMMON_REG->GPIOPCTLH_bit.PIN4 = 1;	//---
	NT_COMMON_REG->GPIOPCTLH_bit.PIN5 = 1;	//---
	NT_COMMON_REG->GPIOPCTLH_bit.PIN6 = 1;	//---
	NT_COMMON_REG->GPIOPCTLH_bit.PIN7 = 1;	//---
}

// ��������� ������������ � �������������� �������� ����� PLL
// ������� Fvco ������������� �� 400 ���
// ����� �������� ��� �� ��������.
void Init_Clk_Pll_Div_Fvco400 (void) {
	// ��������� ������� ������������
	// �������� ������� ����� FOUT = (FIN * NF) / ( NR * NO) / N, ��� FIN - ������� ������
	// FIN = 12 MHz
	// �������������� ������� �� ��: 0.8 MHz < Fref < 8 MHz
	// Fref = FIN / (2 * NR)
	// �������������� ������� �� ��: 200 MHz < Fvco < 500 MHz
	// Fvco = FIN * (NF / NR)
	// �� ������ ������������� Fvco < 250 MHz, ������� �����
	// �������� 100 ��� �� �����, ����� ����� ������ Fvco = 200 MHz
	// ��������:
	// N = 2 * (PLL_DIV + 1)
	// NF = F_PLL + 2
	// NR = R_PLL + 2
	// NO = 1, 1/2, 1/2, 1/4 ��� PLL_OD = 0, 1, 2, 3 �����.
	volatile int i = 0;



	NT_COMMON_REG->PLL_OD = 0;		// �������� �������� NO = 1
	NT_COMMON_REG->PLL_NR = 1;		// ������� �������� NR = PLL_NR + 2 = 3
	NT_COMMON_REG->PLL_CTRL_bit.PLL_DIV = 1;	// N = 2 * (PLL_DIV + 1) = 4
#ifdef QUARTZ_10MHZ
	NT_COMMON_REG->PLL_NF = 118;		// �������� �������� ����� PLL NF=F_PLL+2=60
#endif
#ifdef QUARTZ_12MHZ
	NT_COMMON_REG->PLL_NF = 98;		// �������� �������� ����� PLL NF=F_PLL+2=100
#endif
	// ��� ������ 12 ���:
	// Fvco = 12 * (100 / 3) = 400 MHz
	// Fref = 12 / (2 * 3) = 4 MHz
	// FOUT = 12 * 100 / (3 * 1) / 4 = 100 ���, ����� ��������
	// ��� 10 ��� ���� ������ ������� � PLL_NF = 118
	NT_COMMON_REG->SYS_CLK = SYSCLK_PLLDIVCLK;		//���� PLL
	do
	{
		// ����� ��������� �������������
		for(i = 0; i < 250; i++);
	}
	while (NT_COMMON_REG->SYS_CLK_bit.CURR_SRC != SYSCLK_PLLDIVCLK);	// ������� �������� ������������ ������ ��������� � ���������

}

// ��������� ������������ � �������������� �������� ����� PLL
// ������� Fvco ������������� �� 200 ���
void Init_Clk_Pll_Div_Fvco200 (void) {
	// ��������� ������� ������������
	// �������� ������� ����� FOUT = (FIN * NF) / ( NR * NO) / N, ��� FIN - ������� ������
	// FIN = 12 MHz
	// �������������� ������� �� ��: 0.8 MHz < Fref < 8 MHz
	// Fref = FIN / (2 * NR)
	// �������������� ������� �� ��: 200 MHz < Fvco < 500 MHz
	// Fvco = FIN * (NF / NR)
	// �� ������ ������������� Fvco < 250 MHz, ������� �����
	// �������� 100 ��� �� �����, ����� ����� ������ Fvco = 200 MHz
	// ��������:
	// N = 2 * (PLL_DIV + 1)
	// NF = F_PLL + 2
	// NR = R_PLL + 2
	// NO = 1, 1/2, 1/2, 1/4 ��� PLL_OD = 0, 1, 2, 3 �����.
	volatile int i = 0;



	NT_COMMON_REG->PLL_OD = 0;		// �������� �������� NO = 1
	NT_COMMON_REG->PLL_NR = 1;		// ������� �������� NR = PLL_NR + 2 = 3
	NT_COMMON_REG->PLL_CTRL_bit.PLL_DIV = 0;	// N = 2 * (PLL_DIV + 1) = 2
#ifdef QUARTZ_10MHZ
	NT_COMMON_REG->PLL_NF = 58;		// �������� �������� ����� PLL NF=F_PLL+2=60
#endif
#ifdef QUARTZ_12MHZ
	NT_COMMON_REG->PLL_NF = 48;		// �������� �������� ����� PLL NF=F_PLL+2=50
#endif
	// ��� ������ 12 ���:
	// Fvco = 12 * (50 / 3) = 200 MHz
	// Fref = 12 / (2 * 3) = 2 MHz
	// FOUT = 12 * 50 / (3 * 1) / 2 = 100 ���, ����� ��������
	// ��� 10 ��� ���� ������ ������� � PLL_NF = 58
	NT_COMMON_REG->SYS_CLK = SYSCLK_PLLDIVCLK;		//���� PLL
	do
	{
		// ����� ��������� �������������
		for(i = 0; i < 250; i++);
	}
	while (NT_COMMON_REG->SYS_CLK_bit.CURR_SRC != SYSCLK_PLLDIVCLK);	// ������� �������� ������������ ������ ��������� � ���������

}

// ��������� ������������ ��� ������������� �������� ����� PLL
void Init_Clk_Pll (void) {
	volatile int i = 0;
	//��������� ������� ������������
	//�������� ������� ����� FOUT = (FIN * NF) / ( NR * NO), ��� FIN - ������� ������
	NT_COMMON_REG->PLL_OD = 2;		//�������� �������� PLL NO=2
	NT_COMMON_REG->PLL_NR = 1;		//������� �������� PLL NR=R_PLL+2=3
#ifdef QUARTZ_10MHZ
	NT_COMMON_REG->PLL_NF = 58;		//�������� �������� ����� PLL NF=F_PLL+2=60
#endif
#ifdef QUARTZ_12MHZ
	NT_COMMON_REG->PLL_NF = 48;		//�������� �������� ����� PLL NF=F_PLL+2=50
#endif
	//FOUT = 12*50/(3*2) = 100 ���, ����� ��������
	do
	{
		//����� ��������� �������������
		NT_COMMON_REG->SYS_CLK = SYSCLK_REFCLK;		//����� ��������� ������� �� ��������� ������� �� ����� ���������������� CPE_pad: 0 - ���� POR, 1 - ���� ���������������� XI_OSC
		NT_COMMON_REG->SYS_CLK = SYSCLK_PLLCLK;		//���� PLL
		for(i = 0; i < 50; i++);
	}
	while (NT_COMMON_REG->SYS_CLK_bit.CURR_SRC != SYSCLK_PLLCLK);	//������� �������� ������������ ������ ��������� � ���������

}

void InitCLK(void)
{
	volatile int i = 0;
	NT_BOOTFLASH->T_ACC = 6;		//�������� �� ��������� ������, �� ���������� ������ �� ����-������ (� ����������� ������)
	NT_COMMON_REG->USB_CTRL = 0x00000006; //clk_en, 12MHz, xtal

	//��������� �� ������������ �� ����������� ������
	do
	{
		NT_COMMON_REG->SYS_CLK = 0;
		for(i = 0; i < 50; i++);
	}
	while (NT_COMMON_REG->SYS_CLK_bit.CURR_SRC != SYSCLK_REFCLK);

	// ������� ������������ ��� ������������� ����������� ��������.
	Init_Clk_Pll_Div_Fvco200();



	// ���������� ������ ���������
	NT_COMMON_REG->APB_CLK = 0x7FFFF | 0x1000000 | 0x80000;

	for (int i = 0; i < 100; i++){//����� ���� ������ �����... ������ ��� �����������
		NT_COMMON_REG->PER_RST0=0;
		NT_COMMON_REG->PER_RST1=0;
	}

	NT_COMMON_REG->PER_RST0 = 0xFFFFFFFF;
	NT_COMMON_REG->PER_RST1 = 0xFFFFFFFF;
	NT_COMMON_REG->GPIODEN0=0xFFFFFFFF;
	NT_COMMON_REG->GPIODEN1=0xFFFFFFFF;
	NT_COMMON_REG->GPIODEN2=0xFFFFFFFF;
	NT_COMMON_REG->GPIODEN3=0xFFFFFFFF;

	// ��������� ������������ ��� (12 ���)
	NT_COMMON_REG->ADC_CTRL0 = 0x0F0F0F0F;
	NT_COMMON_REG->ADC_CTRL1 = 0x0F0F0F0F;
	NT_COMMON_REG->ADC_CTRL2 = 0x0F0F0F0F;

	// ��������� ������������ UART (25 ���)
	NT_COMMON_REG->UART_CLK = 0x07070707;
	NT_COMMON_REG->SPI_CLK  = 0x70000;

	K1921VK01T_GPIO_SafeInit();
}



