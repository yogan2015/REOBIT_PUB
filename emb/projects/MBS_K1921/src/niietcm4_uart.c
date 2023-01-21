/**
  ******************************************************************************
  * @file    niietcm4_uart.c
  *
  * @brief   ���� �������� ���������� ���� ������� ��� ������ � �������� UART.
  *
  * @author  �����
  *             - ������ ������ (bkolbov), kolbov@niiet.ru
  * @date    18.11.2015
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

/** @defgroup UART
  * @brief ������� ��� ������������������ UART.
  * @attention ������� ��������� ��������� ������ ����������� ����������� ������� UART.
  *            ���������������� ����� �����-������, � ����� ��������� ������������ � ����� ������ ���������� ����������� ��������.
  *            <br>@ref GPIO : @ref GPIO_Init_Deinit.
  *            <br>@ref RCC : @ref RCC_CLK_Config_UART, @ref RCC_RST_Config.
  * @{
  */ 

/** @defgroup UART_Private ��������� ������
  * @{
  */

/** @defgroup UART_Private_Defines ��������� ���������
  * @{
  */

/**
  * @}
  */

/** @defgroup UART_Private_Functions ��������� �������
  * @{
  */

/**
  * @brief  ���������� ������ ���������� UART.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void UART_Cmd(NT_UART_TypeDef* UARTx, FunctionalState State)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    UARTx->CR_bit.UARTEN =  (uint32_t)State;
}

/**
  * @brief  ������ ��������� �������� ��� ���������� ����������� �������� ��������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  IntDiv ����� ����� ��������.
  *   �������� ��������� ����� �������� �� ��������� 1-65535.
  * @param  FracDiv ������� ����� ��������.
  *   �������� ��������� ����� �������� �� ��������� 0-63. � ������, ���� IntDiv
  *   ����� 65535, �������� FracDiv ����� ���� ������ 0.
  * @retval ���
  */

void UART_BaudRateDivConfig(NT_UART_TypeDef* UARTx, uint32_t IntDiv, uint32_t FracDiv)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_INT_DIV(IntDiv));
    assert_param(IS_UART_FRAC_DIV(FracDiv));

    UARTx->IBRD = IntDiv;
    UARTx->FBRD = FracDiv;
}

/**
  * @brief  ��������� ������� �����.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void UART_Break(NT_UART_TypeDef* UARTx, FunctionalState State)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    UARTx->LCR_H_bit.BRK =  (uint32_t)State;
}

/**
  * @brief  ������������� ��� �������� UART ���������� �� ���������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3
  * @retval ���
  */

void UART_DeInit(NT_UART_TypeDef* UARTx)
{
    RCC_PeriphRst_TypeDef UartRst;
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    if (UARTx == NT_UART0)
    {
        UartRst = RCC_PeriphRst_UART0;

    }
    else if (UARTx == NT_UART1)
    {
        UartRst = RCC_PeriphRst_UART1;

    }
    else if (UARTx == NT_UART2)
    {
        UartRst = RCC_PeriphRst_UART2;

    }
    else /* (UARTx == NT_UART3) */
    {
        UartRst = RCC_PeriphRst_UART3;

    }

    RCC_PeriphRstCmd(UartRst, DISABLE);
    RCC_PeriphRstCmd(UartRst, ENABLE);
}

/**
  * @brief  �������������� UARTx �������� ���������� ��������� UART_InitStruct.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3
  * @param  UART_InitStruct ��������� �� ��������� ���� @ref UART_Init_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval Status ������ ���������� �������������.
  *   �������� ��������� ����� �������� �� @ref OperationStatus.
  */

OperationStatus UART_Init(NT_UART_TypeDef* UARTx, UART_Init_TypeDef* UART_InitStruct)
{
    OperationStatus Status = ERROR;
    uint32_t IntDiv, FracDiv;

    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DATA_WIDTH(UART_InitStruct->UART_DataWidth));
    assert_param(IS_FUNCTIONAL_STATE(UART_InitStruct->UART_FIFOEn));
    assert_param(IS_UART_FIFO_LEVEL(UART_InitStruct->UART_FIFOLevelRx));
    assert_param(IS_UART_FIFO_LEVEL(UART_InitStruct->UART_FIFOLevelTx));
    assert_param(IS_UART_PARITY_BIT(UART_InitStruct->UART_ParityBit));
    assert_param(IS_FUNCTIONAL_STATE(UART_InitStruct->UART_RxEn));
    assert_param(IS_UART_STOP_BIT(UART_InitStruct->UART_StopBit));
    assert_param(IS_FUNCTIONAL_STATE(UART_InitStruct->UART_TxEn));

    if (((UART_InitStruct->UART_ClkFreq*5)/3) < (UART_InitStruct->UART_BaudRate*16))
    {
        return Status;
    }
    IntDiv = UART_InitStruct->UART_ClkFreq/(16*UART_InitStruct->UART_BaudRate);
    FracDiv = (uint32_t)((UART_InitStruct->UART_ClkFreq/(16.0*UART_InitStruct->UART_BaudRate)-IntDiv)*64.0+0.5);
    UART_BaudRateDivConfig(UARTx, IntDiv, FracDiv);
    UARTx->LCR_H_bit.WLEN = (uint32_t)UART_InitStruct->UART_DataWidth;
    UARTx->LCR_H_bit.STP2 = (uint32_t)UART_InitStruct->UART_StopBit;
    if (UART_InitStruct->UART_ParityBit == UART_ParityBit_Odd)
    {
        UARTx->LCR_H_bit.SPS = 0;
        UARTx->LCR_H_bit.EPS = 0;
        UARTx->LCR_H_bit.PEN = 1;
    }
    else if (UART_InitStruct->UART_ParityBit == UART_ParityBit_Even)
    {
        UARTx->LCR_H_bit.SPS = 0;
        UARTx->LCR_H_bit.EPS = 1;
        UARTx->LCR_H_bit.PEN = 1;
    }
    else if (UART_InitStruct->UART_ParityBit == UART_ParityBit_High)
    {
        UARTx->LCR_H_bit.SPS = 1;
        UARTx->LCR_H_bit.EPS = 0;
        UARTx->LCR_H_bit.PEN = 1;
    }
    else if (UART_InitStruct->UART_ParityBit == UART_ParityBit_Low)
    {
        UARTx->LCR_H_bit.SPS = 1;
        UARTx->LCR_H_bit.EPS = 1;
        UARTx->LCR_H_bit.PEN = 1;
    }
    else /* UART_InitStruct->UART_ParityBit == UART_ParityBit_Disable */
    {
        UARTx->LCR_H_bit.PEN = 0;
    }
    UARTx->LCR_H_bit.FEN = (uint32_t)UART_InitStruct->UART_FIFOEn;
    UARTx->IFLS_bit.RXIFLSEL = (uint32_t)UART_InitStruct->UART_FIFOLevelRx;
    UARTx->IFLS_bit.TXIFLSEL = (uint32_t)UART_InitStruct->UART_FIFOLevelTx;
    UARTx->CR_bit.TXE = (uint32_t)UART_InitStruct->UART_TxEn;
    UARTx->CR_bit.RXE = (uint32_t)UART_InitStruct->UART_RxEn;

    Status = OK;
    return Status;
}

/**
  * @brief  ���������� ������� ����� ��������� UART_InitStruct ���������� �� ���������.
  * @param  UART_InitStruct ��������� �� ��������� ���� @ref UART_Init_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void UART_StructInit(UART_Init_TypeDef* UART_InitStruct)
{
    UART_InitStruct->UART_BaudRate = 9600;
    UART_InitStruct->UART_ClkFreq = EXT_OSC_VALUE;
    UART_InitStruct->UART_DataWidth = UART_DataWidth_8;
    UART_InitStruct->UART_FIFOLevelRx = UART_FIFOLevel_1_2;
    UART_InitStruct->UART_FIFOLevelTx = UART_FIFOLevel_1_2;
    UART_InitStruct->UART_FIFOEn = DISABLE;
    UART_InitStruct->UART_ParityBit = UART_ParityBit_Disable;
    UART_InitStruct->UART_StopBit = UART_StopBit_1;
    UART_InitStruct->UART_RxEn = ENABLE;
    UART_InitStruct->UART_TxEn = ENABLE;
}

/**
  * @brief  �������� ����� ������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  Data   ����� ������.
  * @retval ���
  */

void UART_SendData(NT_UART_TypeDef* UARTx, uint32_t Data)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DATA(Data));

    /*
     * � ������� ����� Data ��������� ������ ��� �������� � �����.
     * ��� ��������� ���� ��� ������ � ������� ������ �������� ������������.
     * ������ � ������� DR ���� ��������, � �� ����� ���� DR_bit.DATA,
     * �.�. ������ � ���� ����������� � ��������� ������-�����������-������,
     * ������� ����� �������� � �������, ����� ���������� ������������� ����� ������ � ��������.
     */
    UARTx->DR = Data;
}

/**
  * @brief  ����� ����� ������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @retval  Data  ����� ������.
  */

uint32_t UART_RecieveData(NT_UART_TypeDef* UARTx)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));

    return(UARTx->DR_bit.DATA);
}

/**
  * @brief  ������ ��������� ���������� �����.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  UART_Flag  ����� ������.
  *   �������� ��������� ����� ������������ �������� �� @ref UART_Exported_Constants_Flag.
  * @retval Status  ��������� �����. ���� ������� ��������� ������,
  *   �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus UART_FlagStatus(NT_UART_TypeDef* UARTx, uint32_t UART_Flag)
{
    FlagStatus Status;
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_FLAG(UART_Flag));

    if (UARTx->FR & UART_Flag)
    {
        Status = Flag_SET;
    }
    else
    {
        Status = Flag_CLEAR;
    }

    return Status;
}

/**
  * @brief  ������ ��������� ���������� ����� ������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  UART_Error  ����� ������ ������.
  *   �������� ��������� ����� ������������ �������� �� @ref UART_Exported_Constants_Error.
  * @retval Status  ��������� �����. ���� ������� ��������� ������,
  *   �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus UART_ErrorStatus(NT_UART_TypeDef* UARTx, uint32_t UART_Error)
{
    FlagStatus Status;
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_ERROR(UART_Error));

    if (UARTx->RSR_ECR & UART_Error)
    {
        Status = Flag_SET;
    }
    else
    {
        Status = Flag_CLEAR;
    }

    return Status;
}

/**
  * @brief  ������� ������ ������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  UART_Error  ����� ������ ������.
  *   �������� ��������� ����� ������������ �������� �� @ref UART_Exported_Constants_Error.
  * @retval ���
  */

void UART_ErrorStatusClear(NT_UART_TypeDef* UARTx, uint32_t UART_Error)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_ERROR(UART_Error));

    UARTx->RSR_ECR = UART_Error;
}


/**
  * @brief  �������������� �������� ����� UART �������� ���������� ��������� UART_ModemInitStruct.
  * @param  UART_ModemInitStruct ��������� �� ��������� ���� @ref UART_ModemInit_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval ���
  */

void UART_ModemConfig(NT_UART_TypeDef* UARTx, UART_ModemInit_TypeDef* UART_ModemInitStruct)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(UART_ModemInitStruct->UART_InvDTR));
    assert_param(IS_FUNCTIONAL_STATE(UART_ModemInitStruct->UART_InvRTS));
    assert_param(IS_FUNCTIONAL_STATE(UART_ModemInitStruct->UART_CTSEn));
    assert_param(IS_FUNCTIONAL_STATE(UART_ModemInitStruct->UART_RTSEn));

    UARTx->CR_bit.DTR = (uint32_t)UART_ModemInitStruct->UART_InvDTR;
    UARTx->CR_bit.RTS = (uint32_t)UART_ModemInitStruct->UART_InvRTS;
    UARTx->CR_bit.CTSEN = (uint32_t)UART_ModemInitStruct->UART_CTSEn;
    UARTx->CR_bit.RTSEN = (uint32_t)UART_ModemInitStruct->UART_RTSEn;
}

/**
  * @brief  ���������� ������� ����� ��������� UART_ModemInitStruct ���������� �� ���������.
  * @param  UART_ModemInitStruct ��������� �� ��������� ���� @ref UART_ModemInit_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void UART_ModemStructInit(UART_ModemInit_TypeDef* UART_ModemInitStruct)
{
    UART_ModemInitStruct->UART_InvDTR = DISABLE;
    UART_ModemInitStruct->UART_InvRTS = DISABLE;
    UART_ModemInitStruct->UART_CTSEn = DISABLE;
    UART_ModemInitStruct->UART_RTSEn = DISABLE;
}

/**
  * @brief  ����� ����� ���������� ������ ���������/�����������, �� ���������� ��������
  *   ����� �������������� ����������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  UART_Dir  ����� ����� �������� ��������� � �����������.
  *   �������� ��������� ����� �� �������� @ref UART_Dir_Typedef.
  * @param  UART_FIFOLevel  ����� ������.
  *   �������� ��������� ����� �������� �� @ref UART_FIFOLevel_TypeDef.
  * @retval ���
  */

void UART_ITFIFOLevelConfig(NT_UART_TypeDef* UARTx, UART_Dir_Typedef UART_Dir, UART_FIFOLevel_TypeDef UART_FIFOLevel)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DIR(UART_Dir));
    assert_param(IS_UART_FIFO_LEVEL(UART_FIFOLevel));

    if (UART_Dir == UART_Dir_Rx)
    {
        UARTx->IFLS_bit.RXIFLSEL = (uint32_t)UART_FIFOLevel;
    }
    else /* if (UART_Dir == UART_Dir_Tx) */
    {
        UARTx->IFLS_bit.TXIFLSEL = (uint32_t)UART_FIFOLevel;
    }
}

/**
  * @brief  ������������ ��������� ����������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  UART_ITSource  ����� ����������.
  *   �������� ��������� ����� ������������ �������� �� @ref UART_Exported_Constants_ITSource.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void UART_ITCmd(NT_UART_TypeDef* UARTx, uint32_t UART_ITSource,  FunctionalState State)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_IT_SOURCE(UART_ITSource));

    if (State == ENABLE)
    {
        UARTx->IMSC |= (uint32_t)UART_ITSource;
    }
    else
    {
        UARTx->IMSC &= ~(uint32_t)UART_ITSource;
    }
}

/**
  * @brief  ������ ���������������� ��������� ����������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  UART_ITSource  ����� ����������.
  *   �������� ��������� ����� ������������ �������� �� @ref UART_Exported_Constants_ITSource.
  * @retval Status  ��������� �����. ���� ������� ��������� ����������,
  *   �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus UART_ITRawStatus(NT_UART_TypeDef* UARTx, uint32_t UART_ITSource)
{
    FlagStatus Status;
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_IT_SOURCE(UART_ITSource));

    if (UARTx->RIS & UART_ITSource)
    {
        Status = Flag_SET;
    }
    else
    {
        Status = Flag_CLEAR;
    }

    return Status;
}

/**
  * @brief  ������ �������������� ��������� ����������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  UART_ITSource  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref UART_Exported_Constants_ITSource.
  * @retval Status  ��������� �����. ���� ������� ��������� ����������,
  *   �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus UART_ITMaskedStatus(NT_UART_TypeDef* UARTx, uint32_t UART_ITSource)
{
    FlagStatus Status;
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_IT_SOURCE(UART_ITSource));

    if (UARTx->MIS & UART_ITSource)
    {
        Status = Flag_SET;
    }
    else
    {
        Status = Flag_CLEAR;
    }

    return Status;
}

/**
  * @brief  ����� ������ ��������� ��������� ����������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  UART_ITSource  ����� ����������.
  *   �������� ��������� ����� ������������ �������� �� @ref UART_Exported_Constants_ITSource.
  * @retval ���
  */

void UART_ITStatusClear(NT_UART_TypeDef* UARTx, uint32_t UART_ITSource)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_IT_SOURCE(UART_ITSource));

    UARTx->ICR = (uint32_t)UART_ITSource;
}

/**
  * @brief  ���������� ������������� �������� DMA �� ��������� � ������ �������������
  *   ���������� �� ������.
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void UART_DMABlkOnErrCmd(NT_UART_TypeDef* UARTx,  FunctionalState State)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    UARTx->DMACR_bit.DMAONERR = (uint32_t)State;
}

/**
  * @brief  ���������� ������������ �������� DMA ��� ������������ ������ �����������/���������
  * @param  UARTx  ����� ������ UART, ��� x ����� � ��������� 0-3.
  * @param  UART_Dir  ����� ����������� (����� ��� ��������) ��� ������������.
  *   �������� ��������� ����� �������� �� @ref UART_Dir_Typedef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void UART_DMACmd(NT_UART_TypeDef* UARTx, UART_Dir_Typedef UART_Dir,  FunctionalState State)
{
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DIR(UART_Dir));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (UART_Dir == UART_Dir_Rx)
    {
        UARTx->DMACR_bit.RXDMAE = (uint32_t)State;
    }
    else /* if (UART_Dir == UART_Dir_Tx) */
    {
        UARTx->DMACR_bit.TXDMAE = (uint32_t)State;
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
