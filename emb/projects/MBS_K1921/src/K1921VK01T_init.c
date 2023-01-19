/******************************************************************************
 * @file		K1921VK01T_init.c
 * @brief		���� ��������������� ������������� ��������� ����������������
 * @version		v1.0
 * @date		11 ������� 2015
 *
 * @note
 * ��� "��� ������" (http://motorcontrol.ru), ��� ����� ��������.
 *
 * @par
 *
 * 
 *
 * @par
 * ������ ����������� ����������� ���������������� "��� ����", � ��,
 * ��� ������������, ���������� �� ���� ��� �����, ��������� � ��� ��������������.
 * ��� "��� ������" �� ����� ������� ��������������� �� ��������� ������,
 * ��������� � ��� ��������������.
 *
 ******************************************************************************/

#ifdef RELPATH
    #include "main.h"
#else
    #include "../inc/main.h"
#endif


//System clock sources
#define SYSCLK_REFCLK       0
#define SYSCLK_PORCLK       1
#define SYSCLK_OSCCLK       2
#define SYSCLK_PLLCLK       3
#define SYSCLK_PLLDIVCLK    4
#define SYSCLK_USB60CLK     5
#define SYSCLK_USB12CLK     6
#define SYSCLK_ETH25CLK     7


//��������� ���������� ������������� �������������� ������� ���������� �����.
//���� � �� �� ������� ����� ���� ��������� ��� ���������� �����. � ����� ������ �� ����� �������� �� ���� �� ���, ����
//���� ��� ��������� � ������ ����������� �����-������, �.�. ����. ������� ���������.
//��� ���������� ������������� ������ ����� ����������� ����. �������, ������� � ���������� ������������ ����� �������������.
//������������ ����. ������� ��� ������ ����� ����� ������������� � ������������ � ����������� �������.
void K1921VK01T_GPIO_SafeInit()
{
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

void InitCLK(void)
{
	volatile int i;


	NT_BOOTFLASH->T_ACC = 6;		//�������� �� ��������� ������, �� ���������� ������ �� ����-������ (� ����������� ������)

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



