/**
  ******************************************************************************
  * @file    niietcm4_rcc.c
  *
  * @brief   ���� �������� ���������� ���� ������� ��� ������ � �������������
  *          � ������� ������������ ������ ����������������.
  *
  * @author  �����
  *             - ������ ������ (bkolbov), kolbov@niiet.ru
  * @date    06.11.2015
  *
  ******************************************************************************
  * @attention
  *
  * ������ ����������� ����������� ��������������� ���� ���ܻ, ��� �����-����
  * ��������, ���� ���������� ��� ���������������, ������� �������� ��������
  * �����������, ������������ �� ��� ����������� ���������� � ����������
  * ���������, �� �� ������������� ���. ������ ����������� �����������
  * ������������� ��� ��������������� ����� � ���������� ������ ��
  * �������������� �������������� ���������� � ��������, � ����� ��������� �����
  * �����������. �� � ����� ������ ������ ��� ��������������� �� �����
  * ��������������� �� �����-���� �����, �� ������ ��� ��������� �����, ���
  * �� ���� �����������, ��������� ��-�� ������������� ������������ �����������
  * ��� ���� �������� � ����������� ������������.
  *
  * <h2><center>&copy; 2015 ��� "�����"</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#ifdef RELPATH
    #include "main.h"
#else
    #include "../inc/main.h"
#endif
/** @addtogroup Peripheral
  * @{
  */

/** @defgroup RCC
  * @brief ������� ��� ������ � ������������� � ������� ������������ ������.
  * @{
  */ 

/** @defgroup RCC_Private ��������� ������
  * @{
  */

/** @defgroup RCC_Private_Defines ��������� ���������
  * @{
  */

/** @defgroup RCC_PLL_CONFIG_FREQ_DEFINE �������� ��������� ������, ������������ ��� ��������� PLL
  * @{
  */

#define RCC_PLL_REF_FREQ                ((uint32_t)1000000)     /*!< ������� F_REF, ������������ ��� ��������� PLL */
#define RCC_PLL_DIV_EN_FREQ             ((uint32_t)60000000)    /*!< ��������� �������� ��������� ������� - ��� ��������� ������� ������ ���, ������������� � ���������� ������� �������� PLL */

/**
  * @}
  */

/** @defgroup RCC_regs_reset_define ��������� �������� ���������
  * @{
  */

#define RCC_PLL_CTRL_Reset_Value        ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� PLL_CTRL */
#define RCC_PLL_OD_Reset_Value          ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� PLL_OD */
#define RCC_PLL_NR_Reset_Value          ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� PLL_NR */
#define RCC_PLL_NF_Reset_Value          ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� PLL_NF */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_Private_Functions ��������� �������
  * @{
  */

/**
  * @brief  ��������� �������� ����� ��������� ��������� �������
  *
  * @retval timeout �������� ������� ������� ����� ��������.
  */

uint32_t RCC_WaitClkChange(RCC_SysClk_TypeDef RCC_SysClk)
{
    uint32_t timeout = RCC_CLK_CHANGE_TIMEOUT;

    while(timeout)
    {
        if ((RCC_SysClk_TypeDef)(NT_COMMON_REG->SYS_CLK_bit.CURR_SRC) == RCC_SysClk)
        {
            break;
        }
        else
        {
            timeout--;
        }
    }

    return timeout;
}

/**
  * @brief  ��������� ��������� ��������� ������� � ������ ������ �������� ���������
  *   �� ������ H[0]. ������� ���������� ������� GPIO ��� ��������� ������.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState:
  *     - ENABLE - ��������� H[0] � �����  ���������� �������������� �������� 2.
  *     - DISABLE - ��������� H[0] � ��������� �� ���������.
  * @retval ���
  */

void RCC_SysClkDiv2Out(FunctionalState State)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(State));

    GPIO_Init_TypeDef GPIO_Init_Struct;

    GPIO_StructInit(&GPIO_Init_Struct);

    GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_0;
    if (State == ENABLE)
    {
        GPIO_Init_Struct.GPIO_Dir = GPIO_Dir_Out;
        GPIO_Init_Struct.GPIO_AltFunc = GPIO_AltFunc_2;
        GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_AltFunc;
        GPIO_Init_Struct.GPIO_Out = GPIO_Out_En;
    }

    GPIO_Init(NT_GPIOH, &GPIO_Init_Struct);
}

/**
  * @brief  �������������� ������������ PLL ��� ��������� �������� ��������� �������.
  *
  * � ������ ������ �� ��������� ������� ��� PLL, � ����� � �������� ��������
  * �������, ����������� ��� ����������� �������������.
  * @attention ���� Freq < 60 ���, �� � �������� ��������� ������� ����� �����������
  *   ����� �������� PLL DIV. � ��������� ������� ������������ ����� PLL ��������.
  *
  * @param  RCC_PLLRef ����� ��������� �������� ������� PLL.
  *   �������� ��������� ����� �������� �� @ref RCC_PLLRef_TypeDef.
  * @param  SysFreq �������� ��������� ������� � ��.
  *   �������� ��������� ����� �������� �� ��������� 1000000-100000000, ������� 1000000.
  * @retval ���
  */

OperationStatus RCC_PLLAutoConfig(RCC_PLLRef_TypeDef RCC_PLLRef, uint32_t SysFreq)
{
    uint32_t f_in = 0;
    uint32_t nf, nr;
    RCC_PLLNO_TypeDef no;
    uint32_t pll_div = 0;
    OperationStatus status;
    RCC_PLLInit_TypeDef RCC_PLLInit_Struct;
    FunctionalState pll_div_cmd = DISABLE;
    volatile uint32_t pll_stable_wait = RCC_CLK_PLL_STABLE_TIMEOUT;

    /* Check the parameters */
    assert_param(IS_RCC_PLL_REF(RCC_PLLRef));
    assert_param(IS_RCC_SYS_FREQ(SysFreq));

    if (RCC_PLLRef == RCC_PLLRef_XI_OSC)
    {
        f_in = EXT_OSC_VALUE;
    }
    else if (RCC_PLLRef == RCC_PLLRef_USB_CLK)
    {
        if (NT_COMMON_REG->USB_CTRL_bit.FSEL)
        {
            f_in = (uint32_t)(24000000);
        }
        else
        {
            f_in = (uint32_t)(12000000);
        }
    }
    else if (RCC_PLLRef == RCC_PLLRef_USB_60MHz)
    {
        f_in = (uint32_t)(60000000);
    }
    else if (RCC_PLLRef == RCC_PLLRef_ETH_25MHz)
    {
        f_in = (uint32_t)(25000000);
    }

    no = RCC_PLLNO_Div4;
    if ((SysFreq < RCC_PLL_DIV_EN_FREQ))
    {
        pll_div = (RCC_PLL_DIV_EN_FREQ/SysFreq + 1)/2 - 1;
        pll_div_cmd = ENABLE;
    }

    nr = f_in/(2*RCC_PLL_REF_FREQ);
    if (pll_div_cmd == DISABLE)
    {
        nf = ((SysFreq/RCC_PLL_REF_FREQ) * ((uint32_t)no + 1) * nr )/(f_in/RCC_PLL_REF_FREQ);
    }
    else /* (pll_div_cmd == ENABLE) */
    {
        nf = ((SysFreq/RCC_PLL_REF_FREQ) * ((uint32_t)no + 1) * nr * 2*(pll_div+1) )/(f_in/RCC_PLL_REF_FREQ);
    }


    RCC_PLLInit_Struct.RCC_PLLRef = RCC_PLLRef;
    RCC_PLLInit_Struct.RCC_PLLDiv = pll_div;
    RCC_PLLInit_Struct.RCC_PLLNO = no;
    RCC_PLLInit_Struct.RCC_PLLNF = nf;
    RCC_PLLInit_Struct.RCC_PLLNR = nr;

    RCC_PLLInit(&RCC_PLLInit_Struct);

    while(pll_stable_wait)
    {
        pll_stable_wait--;
    }

    if (pll_div_cmd == DISABLE)
    {
        status = RCC_SysClkSel(RCC_SysClk_PLL);
    }
    else /* (pll_div_cmd == ENABLE) */
    {
        status = RCC_SysClkSel(RCC_SysClk_PLLDIV);
    }

    return status;
}

/**
  * @brief  �������������� PLL �������� ���������� ��������� RCC_PLLInit_Struct.
  *
  * �������� �������� ������� PLL ����������� � �������������� ��������
  * �������� NR � ��������� NO ���������, � ����� �������� �������� ����� NF
  * �� �������:<br><br>
  *
  * <center>FOUT = (FIN ? NF) / (NO ? NR),</center>
  *
  * ��� FIN � ������� ������� PLL.<br>
  * @attention
  *
  * ��� ������� ������������� ������� PLL ������ ����������� ��������� �������:
  * - 3,2 ��� < FIN < 150 ���,
  * - 800 ��� < FREF < 8���,
  * - 200 ��� < FVCO < 500���,
  *
  * ��� ������� �������� ��������� FREF ����������� �� �������:<br><br>
  *
  * <center>FREF = FIN / (2 ? NR),</center>
  *
  * � ������� FVCO ����������� �� �������:<br><br>
  *
  * <center>FVCO = FIN ? (NF / NR)</center>
  * @param  RCC_PLLInit_Struct ��������� �� ��������� ���� @ref RCC_PLLInit_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval ���
  */

void RCC_PLLInit(RCC_PLLInit_TypeDef* RCC_PLLInit_Struct)
{
    assert_param(IS_RCC_PLLDIV(RCC_PLLInit_Struct->RCC_PLLDiv));
    assert_param(IS_RCC_PLL_NF(RCC_PLLInit_Struct->RCC_PLLNF));
    assert_param(IS_RCC_PLL_NO(RCC_PLLInit_Struct->RCC_PLLNO));
    assert_param(IS_RCC_PLL_NR(RCC_PLLInit_Struct->RCC_PLLNR));
    assert_param(IS_RCC_PLL_REF(RCC_PLLInit_Struct->RCC_PLLRef));

    NT_COMMON_REG->PLL_CTRL_bit.REFSEL = ((uint32_t)(RCC_PLLInit_Struct->RCC_PLLRef));
    NT_COMMON_REG->PLL_CTRL_bit.PLL_DIV = RCC_PLLInit_Struct->RCC_PLLDiv;
    NT_COMMON_REG->PLL_OD = ((uint32_t)(RCC_PLLInit_Struct->RCC_PLLNO));
    NT_COMMON_REG->PLL_NF = RCC_PLLInit_Struct->RCC_PLLNF - 2;
    NT_COMMON_REG->PLL_NR = RCC_PLLInit_Struct->RCC_PLLNR - 2;
}

/**
  * @brief  ���������� ������� ����� ��������� RCC_PLLInit_Struct ���������� �� ���������.
  * @param  RCC_PLLInit_Struct ��������� �� ��������� ���� @ref RCC_PLLInit_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void RCC_PLLStructInit(RCC_PLLInit_TypeDef* RCC_PLLInit_Struct)
{
    RCC_PLLInit_Struct->RCC_PLLRef = RCC_PLLRef_XI_OSC;
    RCC_PLLInit_Struct->RCC_PLLDiv = 0;
    RCC_PLLInit_Struct->RCC_PLLNO = RCC_PLLNO_Disable;
    RCC_PLLInit_Struct->RCC_PLLNF = 2;
    RCC_PLLInit_Struct->RCC_PLLNR = 2;
}

/**
  * @brief  ������������� ��� �������� PLL ���������� �� ���������.
  * @retval ���
  */

void RCC_PLLDeInit()
{
    NT_COMMON_REG->PLL_CTRL = RCC_PLL_CTRL_Reset_Value;
    NT_COMMON_REG->PLL_OD = RCC_PLL_OD_Reset_Value;
    NT_COMMON_REG->PLL_NF = RCC_PLL_NF_Reset_Value;
    NT_COMMON_REG->PLL_NR = RCC_PLL_NR_Reset_Value;
}

/**
  * @brief  ���������� ������� PowerDown PLL.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_PLLPowerDownCmd(FunctionalState State)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == DISABLE)
    {
        NT_COMMON_REG->PLL_CTRL_bit.PD = 0;
    }
    else if (State == ENABLE)
    {
        NT_COMMON_REG->PLL_CTRL_bit.PD = 1;
    }
}

/**
  * @brief  ��������� ������������ ���������� ����� ���������.
  * @attention ����� UART , SPI, ADC, USB ����������� ��������.
  *   - @ref RCC_CLK_Config_UART
  *   - @ref RCC_CLK_Config_SPI
  *   - @ref RCC_CLK_Config_ADC
  *   - @ref RCC_CLK_Config_USB
  * @param  RCC_PeriphClk  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref RCC_PeriphClk_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_PeriphClkCmd(RCC_PeriphClk_TypeDef RCC_PeriphClk, FunctionalState State)
{
    /* Check the parameters */
    assert_param(IS_RCC_PERIPH_CLK(RCC_PeriphClk));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_COMMON_REG->APB_CLK |= RCC_PeriphClk;
    }
    else if (State == DISABLE)
    {
        NT_COMMON_REG->APB_CLK &= ~RCC_PeriphClk;
    }
}

/**
  * @brief  ����� ��������� ��� ���������� ��������� �������.
  * @param  RCC_SysClk  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref RCC_SysClk_TypeDef.
  * @retval ���
  */

OperationStatus RCC_SysClkSel(RCC_SysClk_TypeDef RCC_SysClk)
{
    uint32_t timeout;
    OperationStatus status;

    /* Check the parameters */
    assert_param(IS_RCC_SYS_CLK(RCC_SysClk));

    NT_COMMON_REG->SYS_CLK = ((uint32_t)RCC_SysClk);

   timeout = RCC_WaitClkChange(RCC_SysClk);

    if (timeout)
    {
        status = OK;
    }
    else
    {
        status = ERROR;
    }

    return status;
}

/**
  * @brief  ������� �������� ���������� ��������� �������.
  * @retval �������� �� @ref RCC_SysClk_TypeDef
  */

RCC_SysClk_TypeDef RCC_SysClkStatus()
{
    return((RCC_SysClk_TypeDef)((NT_COMMON_REG->SYS_CLK)>>COMMON_REG_SYS_CLK_CURR_SRC_Pos));
}

/**
  * @brief  ��������� ��������� ��������� ������� ��� USB.
  * @param  RCC_USBClk  ����� ��������� ������������.
  *   �������� ��������� ����� �������� �� @ref RCC_USBClk_TypeDef.
  * @param  RCC_USBFreq  ����� ������������� ������� �� ����� CLK_USB.
  *   �������� ��������� ����� �������� �� @ref RCC_USBFreq_TypeDef.
  * @retval ���
  */

void RCC_USBClkConfig(RCC_USBClk_TypeDef RCC_USBClk, RCC_USBFreq_TypeDef RCC_USBFreq)
{
    /* Check the parameters */
    assert_param(IS_RCC_USB_CLK(RCC_USBClk));
    assert_param(IS_RCC_USB_FREQ(RCC_USBFreq));

    NT_COMMON_REG->USB_CTRL &= ~((1<<COMMON_REG_USB_CTRL_FSEL_Pos) | (1<<COMMON_REG_USB_CTRL_CLKSEL_Pos));
    NT_COMMON_REG->USB_CTRL |= (RCC_USBFreq<<COMMON_REG_USB_CTRL_FSEL_Pos) | (RCC_USBClk<<COMMON_REG_USB_CTRL_CLKSEL_Pos);
}

/**
  * @brief  ��������� ������������ USB.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_USBClkCmd(FunctionalState State)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_COMMON_REG->USB_CTRL_bit.CLKEN = 1;
    }
    else if (State == DISABLE)
    {
        NT_COMMON_REG->USB_CTRL_bit.CLKEN = 0;
    }
}

/**
  * @brief  ��������� ��������� ��������� ������� ��� ���������� UART.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  RCC_UARTClk  ����� ��������� ������������ ��� UART.
  *   �������� ��������� ����� �������� �� @ref RCC_UARTClk_TypeDef.
  * @retval ���
  */

void RCC_UARTClkSel(NT_UART_TypeDef* UARTx, RCC_UARTClk_TypeDef RCC_UARTClk)
{
    uint32_t offset;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_RCC_UART_CLK(RCC_UARTClk));

    if (UARTx == NT_UART0)
    {
        offset = COMMON_REG_UART_SPI_CLK_SEL_SEL_UART0_Pos;
    }
    else if (UARTx == NT_UART1)
    {
        offset = COMMON_REG_UART_SPI_CLK_SEL_SEL_UART1_Pos;
    }
    else if (UARTx == NT_UART2)
    {
        offset = COMMON_REG_UART_SPI_CLK_SEL_SEL_UART2_Pos;
    }
    else /* (UARTx == NT_UART3) */
    {
        offset = COMMON_REG_UART_SPI_CLK_SEL_SEL_UART3_Pos;
    }

    NT_COMMON_REG->UART_SPI_CLK_SEL &= ~(3<<offset);
    NT_COMMON_REG->UART_SPI_CLK_SEL |= (RCC_UARTClk<<offset);
}

/**
  * @brief  ��������� �������� ��������� ������� ��� ���������� UART.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  DivVal  �������� ��������. �������������� ����������� ������� �����������
  *   �� ������� (2?(DivVal+1)).
  *   �������� ��������� ����� �������� �� ��������� 0-63.
  * @param  DivState  ����� ��������� ��������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_UARTClkDivConfig(NT_UART_TypeDef* UARTx, uint32_t DivVal, FunctionalState DivState)
{
    uint32_t offset;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_RCC_CLK_DIV(DivVal));
    assert_param(IS_FUNCTIONAL_STATE(DivState));

    if (UARTx == NT_UART0)
    {
        offset = COMMON_REG_UART_CLK_DIVEN_UART0_Pos;
    }
    else if (UARTx == NT_UART1)
    {
        offset = COMMON_REG_UART_CLK_DIVEN_UART1_Pos;
    }
    else if (UARTx == NT_UART2)
    {
        offset = COMMON_REG_UART_CLK_DIVEN_UART2_Pos;
    }
    else /* (UARTx == NT_UART3) */
    {
        offset = COMMON_REG_UART_CLK_DIVEN_UART3_Pos;
    }

    NT_COMMON_REG->UART_CLK &= ~(0x7F << offset);
    NT_COMMON_REG->UART_CLK |=  (DivVal << (offset+1)) | (DivState << offset);
}

/**
  * @brief  ��������� ������������ UART.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_UARTClkCmd(NT_UART_TypeDef* UARTx, FunctionalState State)
{
    uint32_t offset;

    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (UARTx == NT_UART0)
    {
        offset = COMMON_REG_UART_CLK_CLKEN_UART0_Pos;
    }
    else if (UARTx == NT_UART1)
    {
        offset = COMMON_REG_UART_CLK_CLKEN_UART1_Pos;
    }
    else if (UARTx == NT_UART2)
    {
        offset = COMMON_REG_UART_CLK_CLKEN_UART2_Pos;
    }
    else /* (UARTx == NT_UART3) */
    {
        offset = COMMON_REG_UART_CLK_CLKEN_UART3_Pos;
    }

    if (State == ENABLE)
    {
        NT_COMMON_REG->UART_CLK |=  (1 << offset);
    }
    else if (State == DISABLE)
    {
        NT_COMMON_REG->UART_CLK &= ~(1 << offset);
    }
}

/**
  * @brief  ��������� ��������� ��������� ������� ��� ���������� SPI.
  * @param  SPIx  ����� ������ SPI, ��� x ����� � ��������� 0-3.
  * @param  RCC_SPIClk  ����� ��������� ������������ ��� SPI.
  *   �������� ��������� ����� �������� �� @ref RCC_SPIClk_TypeDef.
  * @retval ���
  */

void RCC_SPIClkSel(NT_SPI_TypeDef* SPIx, RCC_SPIClk_TypeDef RCC_SPIClk)
{
    uint32_t offset;

    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_RCC_SPI_CLK(RCC_SPIClk));

    if (SPIx == NT_SPI0)
    {
        offset = COMMON_REG_UART_SPI_CLK_SEL_SEL_SPI0_Pos;
    }
    else if (SPIx == NT_SPI1)
    {
        offset = COMMON_REG_UART_SPI_CLK_SEL_SEL_SPI1_Pos;
    }
    else if (SPIx == NT_SPI2)
    {
        offset = COMMON_REG_UART_SPI_CLK_SEL_SEL_SPI2_Pos;
    }
    else /* (SPIx == NT_SPI3) */
    {
        offset = COMMON_REG_UART_SPI_CLK_SEL_SEL_SPI3_Pos;
    }

    NT_COMMON_REG->UART_SPI_CLK_SEL &= ~(3<<offset);
    NT_COMMON_REG->UART_SPI_CLK_SEL |= (RCC_SPIClk<<offset);
}


/**
  * @brief  ��������� �������� ��������� ������� ��� ���������� SPI.
  * @param  SPIx  ����� ������ SPI, ��� x ����� � ��������� 0-3.
  * @param  DivVal  �������� ��������.  �������������� ����������� ������� �����������
  *   �� ������� (2?(DivVal+1)).
  *   �������� ��������� ����� �������� �� ��������� 0-63.
  * @param  DivState  ����� ��������� ��������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_SPIClkDivConfig(NT_SPI_TypeDef* SPIx, uint32_t DivVal, FunctionalState DivState)
{
    uint32_t offset;

    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_RCC_CLK_DIV(DivVal));
    assert_param(IS_FUNCTIONAL_STATE(DivState));

    if (SPIx == NT_SPI0)
    {
        offset = COMMON_REG_SPI_CLK_DIVEN_SPI0_Pos;
    }
    else if (SPIx == NT_SPI1)
    {
        offset = COMMON_REG_SPI_CLK_DIVEN_SPI1_Pos;
    }
    else if (SPIx == NT_SPI2)
    {
        offset = COMMON_REG_SPI_CLK_DIVEN_SPI2_Pos;
    }
    else /* (SPIx == NT_SPI3) */
    {
        offset = COMMON_REG_SPI_CLK_DIVEN_SPI3_Pos;
    }

    NT_COMMON_REG->SPI_CLK &= ~(0x7F << offset);
    NT_COMMON_REG->SPI_CLK |=  (DivVal << (offset+1)) | (DivState << offset);
}

/**
  * @brief  ��������� ������������ SPI.
  * @param  SPIx  ����� ������ SPI, ��� x ����� � ��������� 0-3.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_SPIClkCmd(NT_SPI_TypeDef* SPIx, FunctionalState State)
{
    uint32_t offset;

    /* Check the parameters */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (SPIx == NT_SPI0)
    {
        offset = COMMON_REG_SPI_CLK_CLKEN_SPI0_Pos;
    }
    else if (SPIx == NT_SPI1)
    {
        offset = COMMON_REG_SPI_CLK_CLKEN_SPI1_Pos;
    }
    else if (SPIx == NT_SPI2)
    {
        offset = COMMON_REG_SPI_CLK_CLKEN_SPI2_Pos;
    }
    else /* (SPIx == NT_SPI3) */
    {
        offset = COMMON_REG_SPI_CLK_CLKEN_SPI3_Pos;
    }

    if (State == ENABLE)
    {
        NT_COMMON_REG->SPI_CLK |=  (1 << offset);
    }
    else if (State == DISABLE)
    {
        NT_COMMON_REG->SPI_CLK &= ~(1 << offset);
    }
}

/**
  * @brief  ��������� �������� ��������� ������� ��� ���������� ADC.
  * @param  RCC_ADCClk  ����� ������ ADC.
  *   �������� ��������� ����� �������� �� @ref RCC_ADCClk_TypeDef.
  * @param  DivVal  �������� ��������. �������������� ����������� ������� �����������
  *   �� ������� (2?(DivVal+1)).
  *   �������� ��������� ����� �������� �� ��������� 0-63.
  * @param  DivState  ����� ��������� ��������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_ADCClkDivConfig(RCC_ADCClk_TypeDef RCC_ADCClk, uint32_t DivVal, FunctionalState DivState)
{
    uint32_t offset;
    volatile uint32_t* ctrl_reg;

    /* Check the parameters */
    assert_param(IS_RCC_ADC_CLK(RCC_ADCClk));
    assert_param(IS_RCC_CLK_DIV(DivVal));
    assert_param(IS_FUNCTIONAL_STATE(DivState));

    if (RCC_ADCClk == RCC_ADCClk_0)
    {
        offset = COMMON_REG_ADC_CTRL0_DIVEN_ADC0_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL0);
    }
    else if (RCC_ADCClk == RCC_ADCClk_1)
    {
        offset = COMMON_REG_ADC_CTRL0_DIVEN_ADC1_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL0);
    }
    else if (RCC_ADCClk == RCC_ADCClk_2)
    {
        offset = COMMON_REG_ADC_CTRL0_DIVEN_ADC2_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL0);
    }
    else if (RCC_ADCClk == RCC_ADCClk_3)
    {
        offset = COMMON_REG_ADC_CTRL0_DIVEN_ADC3_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL0);
    }
    else if (RCC_ADCClk == RCC_ADCClk_4)
    {
        offset = COMMON_REG_ADC_CTRL1_DIVEN_ADC4_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL1);
    }
    else if (RCC_ADCClk == RCC_ADCClk_5)
    {
        offset = COMMON_REG_ADC_CTRL1_DIVEN_ADC5_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL1);
    }
    else if (RCC_ADCClk == RCC_ADCClk_6)
    {
        offset = COMMON_REG_ADC_CTRL1_DIVEN_ADC6_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL1);
    }
    else if (RCC_ADCClk == RCC_ADCClk_7)
    {
        offset = COMMON_REG_ADC_CTRL1_DIVEN_ADC7_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL1);
    }
    else if (RCC_ADCClk == RCC_ADCClk_8)
    {
        offset = COMMON_REG_ADC_CTRL2_DIVEN_ADC8_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL2);
    }
    else if (RCC_ADCClk == RCC_ADCClk_9)
    {
        offset = COMMON_REG_ADC_CTRL2_DIVEN_ADC9_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL2);
    }
    else if (RCC_ADCClk == RCC_ADCClk_10)
    {
        offset = COMMON_REG_ADC_CTRL2_DIVEN_ADC10_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL2);
    }
    else /* (RCC_ADCClk == RCC_ADCClk_11) */
    {
        offset = COMMON_REG_ADC_CTRL2_DIVEN_ADC11_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL2);
    }

    *ctrl_reg &= ~(0x7F << offset);
    *ctrl_reg |=  (DivVal << (offset+1)) | (DivState << offset);
}

/**
  * @brief  ��������� ������������ ADC.
  * @param  RCC_ADCClk  ����� ������ ADC.
  *   �������� ��������� ����� �������� �� @ref RCC_ADCClk_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_ADCClkCmd(RCC_ADCClk_TypeDef RCC_ADCClk, FunctionalState State)
{
    uint32_t offset;
    volatile uint32_t* ctrl_reg;

    /* Check the parameters */
    assert_param(IS_RCC_ADC_CLK(RCC_ADCClk));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (RCC_ADCClk == RCC_ADCClk_0)
    {
        offset = COMMON_REG_ADC_CTRL0_CLKEN_ADC0_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL0);
    }
    else if (RCC_ADCClk == RCC_ADCClk_1)
    {
        offset = COMMON_REG_ADC_CTRL0_CLKEN_ADC1_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL0);
    }
    else if (RCC_ADCClk == RCC_ADCClk_2)
    {
        offset = COMMON_REG_ADC_CTRL0_CLKEN_ADC2_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL0);
    }
    else if (RCC_ADCClk == RCC_ADCClk_3)
    {
        offset = COMMON_REG_ADC_CTRL0_CLKEN_ADC3_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL0);
    }
    else if (RCC_ADCClk == RCC_ADCClk_4)
    {
        offset = COMMON_REG_ADC_CTRL1_CLKEN_ADC4_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL1);
    }
    else if (RCC_ADCClk == RCC_ADCClk_5)
    {
        offset = COMMON_REG_ADC_CTRL1_CLKEN_ADC5_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL1);
    }
    else if (RCC_ADCClk == RCC_ADCClk_6)
    {
        offset = COMMON_REG_ADC_CTRL1_CLKEN_ADC6_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL1);
    }
    else if (RCC_ADCClk == RCC_ADCClk_7)
    {
        offset = COMMON_REG_ADC_CTRL1_CLKEN_ADC7_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL1);
    }
    else if (RCC_ADCClk == RCC_ADCClk_8)
    {
        offset = COMMON_REG_ADC_CTRL2_CLKEN_ADC8_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL2);
    }
    else if (RCC_ADCClk == RCC_ADCClk_9)
    {
        offset = COMMON_REG_ADC_CTRL2_CLKEN_ADC9_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL2);
    }
    else if (RCC_ADCClk == RCC_ADCClk_10)
    {
        offset = COMMON_REG_ADC_CTRL2_CLKEN_ADC10_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL2);
    }
    else /* (RCC_ADCClk == RCC_ADCClk_11) */
    {
        offset = COMMON_REG_ADC_CTRL2_CLKEN_ADC11_Pos;
        ctrl_reg = &(NT_COMMON_REG->ADC_CTRL2);
    }

    if (State == ENABLE)
    {
        *ctrl_reg |=  (1 << offset);
    }
    else if (State == DISABLE)
    {
        *ctrl_reg &= ~(1 << offset);
    }

}

/**
  * @brief  ����� �� ��������� ������ ������������ ������.
  * @param  RCC_PeriphRst  ����� ������������� ������.
  *   �������� ��������� ����� �������� �� @ref RCC_PeriphRst_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void RCC_PeriphRstCmd(RCC_PeriphRst_TypeDef RCC_PeriphRst, FunctionalState State)
{
    volatile uint32_t* ctrl_reg;
    uint32_t offset = 0;

    /* Check the parameters */
    assert_param(IS_RCC_PERIPH_RST(RCC_PeriphRst));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (RCC_PeriphRst <= RCC_PeriphRst_ETH)
    {
        ctrl_reg = &(NT_COMMON_REG->PER_RST0);
    }
    else
    {
        ctrl_reg = &(NT_COMMON_REG->PER_RST1);
        offset = (uint32_t)RCC_PeriphRst_ETH + 1; //��������� ��������� � rst1
    }

    if (State == ENABLE)
    {
        *ctrl_reg |= (1<<(RCC_PeriphRst-offset));
    }
    else if (State == DISABLE)
    {
        *ctrl_reg &= ~(1<<(RCC_PeriphRst-offset));
    }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2015 NIIET *****END OF FILE****/
