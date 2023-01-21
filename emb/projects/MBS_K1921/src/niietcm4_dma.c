/**
  ******************************************************************************
  * @file    niietcm4_dma.c
  *
  * @brief   ���� �������� ���������� ���� ������� ��� ������ � DMA.
  *
  * @author  �����
  *             - ������ ������ (bkolbov), kolbov@niiet.ru
  * @date    10.11.2015
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

/** @defgroup DMA
  * @brief ������� ��� ������ � ������������ ������� ������� ������.
  *
  * @attention ��� ������ ������� ������� ������� ����������� �� ���������� ���
  *   ��������� ���� @ref DMA_ConfigData_TypeDef - ��������� ��������� � ��������������
  *   ����������� ������ �������. ������ ���� ��������� ���������� 1�� � ��� ������ ����
  *   ����������� ��������� �� 1024 ������ � �������� ������������.
  *
  *   ����� ��� �������� �������������:
  *   - ������� ��������� ���� @ref DMA_ConfigData_TypeDef;
  *   - �������� ����� ���� ��������� ����������� DMA - @ref DMA_BasePtrConfig;
  *   - �������������� ����������� ������ (@ref DMA_Exported_Functions_Init_Channel);
  *   - �������������� ���������� DMA (@ref DMA_Exported_Functions_Init ��� �����
  *     ��������� ������� @ref DMA_Exported_Functions_Config;
  *   - DMA ����� � ������.
  *
  *   ����� �������� ������������� � ������������� DMA �������� � ����������� � �������� ��������.
  * @{
  */ 

/** @defgroup DMA_Private ��������� ������
  * @{
  */

/** @defgroup DMA_Private_Defines ��������� ���������
  * @{
  */

/** @defgroup DMA_regs_reset_define ��������� �������� ���������
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup DMA_Private_Functions ��������� �������
  * @{
  */

/**
  * @brief  ��������������� ������ DMA.
  * @param  DMA_Channel ��������� �� ��������� ���� @ref DMA_Channel_TypeDef,
  *         ������� �������� ���������������� ���������� ������.
  * @retval ���
  */

void DMA_ChannelDeInit(DMA_Channel_TypeDef* DMA_Channel)
{
    DMA_Channel->SRC_DATA_END = 0;
    DMA_Channel->DST_DATA_END = 0;
    DMA_Channel->CHANNEL_CFG = 0;
}

/**
  * @brief  ������������� ������ DMA.
  * @param  DMA_Channel ��������������� ���� ��������� ������.
  * @param  DMA_ChannelInitStruct ��������� �� ��������� ���� @ref DMA_ChannelInit_TypeDef,
  *         ������� �������� ���������������� ���������� ������.
  * @retval ���
  */

void DMA_ChannelInit(DMA_Channel_TypeDef* DMA_Channel, DMA_ChannelInit_TypeDef* DMA_ChannelInitStruct)
{
    assert_param(IS_DMA_MODE(DMA_ChannelInitStruct->DMA_Mode));
    assert_param(IS_DMA_ARBITRATION_RATE(DMA_ChannelInitStruct->DMA_ArbitrationRate));
    assert_param(IS_DMA_DATA_INC(DMA_ChannelInitStruct->DMA_DstDataInc));
    assert_param(IS_DMA_DATA_INC(DMA_ChannelInitStruct->DMA_SrcDataInc));
    assert_param(IS_DMA_DATA_SIZE(DMA_ChannelInitStruct->DMA_DstDataSize));
    assert_param(IS_DMA_DATA_SIZE(DMA_ChannelInitStruct->DMA_SrcDataSize));
    assert_param(IS_DMA_TRANSFERS_TOTAL(DMA_ChannelInitStruct->DMA_TransfersTotal));
    assert_param(IS_FUNCTIONAL_STATE(DMA_ChannelInitStruct->DMA_DstProtect.BUFFERABLE));
    assert_param(IS_FUNCTIONAL_STATE(DMA_ChannelInitStruct->DMA_DstProtect.CACHEABLE));
    assert_param(IS_FUNCTIONAL_STATE(DMA_ChannelInitStruct->DMA_DstProtect.PRIVELGED));
    assert_param(IS_FUNCTIONAL_STATE(DMA_ChannelInitStruct->DMA_SrcProtect.BUFFERABLE));
    assert_param(IS_FUNCTIONAL_STATE(DMA_ChannelInitStruct->DMA_SrcProtect.CACHEABLE));
    assert_param(IS_FUNCTIONAL_STATE(DMA_ChannelInitStruct->DMA_SrcProtect.PRIVELGED));

    /* �������� */
    DMA_Channel->SRC_DATA_END = (uint32_t)DMA_ChannelInitStruct->DMA_SrcDataEndPtr;
    DMA_Channel->CHANNEL_CFG_bit.SRC_SIZE = DMA_ChannelInitStruct->DMA_SrcDataSize;
    DMA_Channel->CHANNEL_CFG_bit.SRC_INC = DMA_ChannelInitStruct->DMA_SrcDataInc;
    DMA_Channel->CHANNEL_CFG_bit.SRC_PROT_BUFFERABLE = DMA_ChannelInitStruct->DMA_SrcProtect.BUFFERABLE;
    DMA_Channel->CHANNEL_CFG_bit.SRC_PROT_PRIVILEGED = DMA_ChannelInitStruct->DMA_SrcProtect.PRIVELGED;
    DMA_Channel->CHANNEL_CFG_bit.SRC_PROT_CACHEABLE = DMA_ChannelInitStruct->DMA_SrcProtect.CACHEABLE;
    /* �������� */
    DMA_Channel->DST_DATA_END = (uint32_t)DMA_ChannelInitStruct->DMA_DstDataEndPtr;
    DMA_Channel->CHANNEL_CFG_bit.DST_SIZE = DMA_ChannelInitStruct->DMA_DstDataSize;
    DMA_Channel->CHANNEL_CFG_bit.DST_INC = DMA_ChannelInitStruct->DMA_DstDataInc;
    DMA_Channel->CHANNEL_CFG_bit.DST_PROT_BUFFERABLE = DMA_ChannelInitStruct->DMA_DstProtect.BUFFERABLE;
    DMA_Channel->CHANNEL_CFG_bit.DST_PROT_PRIVILEGED = DMA_ChannelInitStruct->DMA_DstProtect.PRIVELGED;
    DMA_Channel->CHANNEL_CFG_bit.DST_PROT_CACHEABLE = DMA_ChannelInitStruct->DMA_DstProtect.CACHEABLE;
    /* ����� */
    DMA_Channel->CHANNEL_CFG_bit.NEXT_USEBURST = DMA_ChannelInitStruct->DMA_NextUseburst;
    DMA_Channel->CHANNEL_CFG_bit.R_POWER = DMA_ChannelInitStruct->DMA_ArbitrationRate;
    DMA_Channel->CHANNEL_CFG_bit.N_MINUS_1 = DMA_ChannelInitStruct->DMA_TransfersTotal - 1;
    DMA_Channel->CHANNEL_CFG_bit.CYCLE_CTRL = DMA_ChannelInitStruct->DMA_Mode;
}

/**
  * @brief  ���������� ������� ����� ��������� DMA_ChannelInitStruct ���������� �� ���������.
  * @param  DMA_ChannelInitStruct ��������� �� ��������� ���� @ref DMA_ChannelInit_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void DMA_ChannelStructInit(DMA_ChannelInit_TypeDef* DMA_ChannelInitStruct)
{
    /* �������� */
    DMA_ChannelInitStruct->DMA_SrcDataEndPtr = (uint32_t *)0x00000000;
    DMA_ChannelInitStruct->DMA_SrcDataSize = DMA_DataSize_8;
    DMA_ChannelInitStruct->DMA_SrcDataInc = DMA_DataInc_Disable;
    DMA_ChannelInitStruct->DMA_SrcProtect.BUFFERABLE = DISABLE;
    DMA_ChannelInitStruct->DMA_SrcProtect.PRIVELGED = DISABLE;
    DMA_ChannelInitStruct->DMA_SrcProtect.CACHEABLE = DISABLE;
    /* �������� */
    DMA_ChannelInitStruct->DMA_DstDataEndPtr = (uint32_t *)0x00000000;
    DMA_ChannelInitStruct->DMA_DstDataSize = DMA_DataSize_8;
    DMA_ChannelInitStruct->DMA_DstDataInc = DMA_DataInc_Disable;
    DMA_ChannelInitStruct->DMA_DstProtect.BUFFERABLE = DISABLE;
    DMA_ChannelInitStruct->DMA_DstProtect.PRIVELGED = DISABLE;
    DMA_ChannelInitStruct->DMA_DstProtect.CACHEABLE = DISABLE;
    /* ����� */
    DMA_ChannelInitStruct->DMA_NextUseburst = DISABLE;
    DMA_ChannelInitStruct->DMA_ArbitrationRate = DMA_ArbitrationRate_1;
    DMA_ChannelInitStruct->DMA_TransfersTotal = 1;
    DMA_ChannelInitStruct->DMA_Mode = DMA_Mode_Disable;
}

/**
  * @brief  ��������������� ����������� DMA.
  * @retval ���
  */

void DMA_DeInit()
{
    NT_DMA->CFG = 0;
    NT_DMA->CTRL_BASE_PTR = 0;
    NT_DMA->CHNL_ENABLE_CLR = 0xFFFFFFFF;
    NT_DMA->CHNL_PRIORITY_CLR = 0xFFFFFFFF;
    NT_DMA->CHNL_PRI_ALT_CLR = 0xFFFFFFFF;
    NT_DMA->CHNL_REQ_MASK_CLR = 0xFFFFFFFF;
    NT_DMA->CHNL_USEBURST_CLR = 0xFFFFFFFF;
}

/**
  * @brief  ������������� ����������� DMA.
  * @attention ������ ��� ���������������� DMA, ���������� ������������������� ������
  * � ������� @ref DMA_ChannelInit � ���������������� ������� ����� ����������� ���������
  * � ������� @ref DMA_BasePtrConfig.
  * @param  DMA_InitStruct ��������� �� ��������� ���� @ref DMA_Init_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval ���
  */

void DMA_Init(DMA_Init_TypeDef* DMA_InitStruct)
{
    DMA_ProtectionConfig(&(DMA_InitStruct->DMA_Protection));
    DMA_UseBurstCmd(DMA_InitStruct->DMA_Channel, DMA_InitStruct->DMA_UseBurst);
    DMA_PrmAltCmd(DMA_InitStruct->DMA_Channel,  DMA_InitStruct->DMA_PrmAlt);
    DMA_HighPriorityCmd(DMA_InitStruct->DMA_Channel,  DMA_InitStruct->DMA_HighPriority);
    DMA_ReqMaskCmd(DMA_InitStruct->DMA_Channel,  DMA_InitStruct->DMA_ReqMask);
    DMA_ChannelEnableCmd(DMA_InitStruct->DMA_Channel,  DMA_InitStruct->DMA_ChannelEnable);
}

/**
  * @brief  ���������� ������� ����� ��������� DMA_InitStruct ���������� �� ���������.
  * @param  DMA_InitStruct ��������� �� ��������� ���� @ref DMA_Init_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void DMA_StructInit(DMA_Init_TypeDef* DMA_InitStruct)
{
    DMA_InitStruct->DMA_Channel = 0xFFFFFF;
    DMA_InitStruct->DMA_ChannelEnable = DISABLE;
    DMA_InitStruct->DMA_HighPriority = DISABLE;
    DMA_InitStruct->DMA_PrmAlt = DISABLE;
    DMA_InitStruct->DMA_ReqMask = DISABLE;
    DMA_InitStruct->DMA_UseBurst = DISABLE;
    DMA_InitStruct->DMA_Protection.BUFFERABLE = DISABLE;
    DMA_InitStruct->DMA_Protection.CACHEABLE = DISABLE;
    DMA_InitStruct->DMA_Protection.PRIVELGED = DISABLE;
}

/**
  * @brief  ��������� �������� ������ ����������� �������.
  * @param  BasePtr  �������� �������� ������.
  * @retval ���
  */

void DMA_BasePtrConfig(uint32_t BasePtr)
{
    NT_DMA->CTRL_BASE_PTR = BasePtr;
}

/**
  * @brief  ���������� ������� ���� ��� ��������� DMA � ����������� ������.
  * @param  DMA_Protection  ���������, ���������� ������������ ������.
  *   �������� ��������� ��������� ���� @ref DMA_Protect_TypeDef.
  * @retval ���
  */

void DMA_ProtectionConfig(DMA_Protect_TypeDef *DMA_Protection)
{
    assert_param(IS_FUNCTIONAL_STATE(DMA_Protection->BUFFERABLE));
    assert_param(IS_FUNCTIONAL_STATE(DMA_Protection->CACHEABLE));
    assert_param(IS_FUNCTIONAL_STATE(DMA_Protection->PRIVELGED));

    if (DMA_Protection->PRIVELGED == ENABLE)
    {
        NT_DMA->CFG_bit.CHNL_PROT_CTRL |= (1<<0);
    }
    else /* DMA_Protection->PRIVELGED == DISABLE */
    {
        NT_DMA->CFG_bit.CHNL_PROT_CTRL &= ~(1<<0);
    }

    if (DMA_Protection->BUFFERABLE == ENABLE)
    {
        NT_DMA->CFG_bit.CHNL_PROT_CTRL |= (1<<1);
    }
    else /* DMA_Protection->BUFFERABLE == DISABLE */
    {
        NT_DMA->CFG_bit.CHNL_PROT_CTRL &= ~(1<<1);
    }

    if (DMA_Protection->CACHEABLE == ENABLE)
    {
        NT_DMA->CFG_bit.CHNL_PROT_CTRL |= (1<<2);
    }
    else /* DMA_Protection->CACHEABLE == DISABLE */
    {
        NT_DMA->CFG_bit.CHNL_PROT_CTRL &= ~(1<<2);
    }
}

/**
  * @brief  ���������� ������ ����������� DMA.
  * @attention ������ ��� �������� DMA, ���������� ������������������� ������
  * � ������� @ref DMA_ChannelInit � ���������������� ���������� DMA ����� �������
  * ������������� @ref DMA_Init ��� ������� - @ref DMA_Exported_Functions_Config.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void DMA_MasterEnableCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_DMA->CFG_bit.MASTER_EN = 1;
    }
    else /* State == DISABLE */
    {
        NT_DMA->CFG_bit.MASTER_EN = 0;
    }
}

/**
  * @brief  ����������� ������ �� ������������� ������� DMA �� ��������� �������.
  * @param  DMA_Channel  ����� ������.
  *   �������� ��������� ����� ������������ ����� �� @ref DMA_Exported_Defines_Channels_Num.
  * @retval ���
  */

void DMA_SWRequestCmd(uint32_t DMA_Channel)
{
    assert_param(IS_DMA_CHANNEL(DMA_Channel));

    NT_DMA->CHNL_SW_REQUEST = DMA_Channel;
}

/**
  * @brief  ��������� ��������� ������ ������� DMA.
  * @param  DMA_Channel  ����� ������.
  *   �������� ��������� ����� ������������ ����� �� @ref DMA_Exported_Defines_Channels_Num.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void DMA_UseBurstCmd(uint32_t DMA_Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_DMA->CHNL_USEBURST_SET = DMA_Channel;
    }
    else /* State == DISABLE */
    {
        NT_DMA->CHNL_USEBURST_CLR = DMA_Channel;
    }
}

/**
  * @brief  ������������ ������� DMA.
  * @attention �� ������������� ������� ������������ ������� �� ��������.
  * @param  DMA_Channel  ����� ������.
  *   �������� ��������� ����� ������������ ����� �� @ref DMA_Exported_Defines_Channels_Num.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void DMA_ReqMaskCmd(uint32_t DMA_Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_DMA->CHNL_REQ_MASK_SET = DMA_Channel;
    }
    else /* State == DISABLE */
    {
        NT_DMA->CHNL_REQ_MASK_CLR = DMA_Channel;
    }
}

/**
  * @brief  ��������� ������� DMA.
  * @param  DMA_Channel  ����� ������.
  *   �������� ��������� ����� ������������ ����� �� @ref DMA_Exported_Defines_Channels_Num.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void DMA_ChannelEnableCmd(uint32_t DMA_Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_DMA->CHNL_ENABLE_SET = DMA_Channel;
    }
    else /* State == DISABLE */
    {
        NT_DMA->CHNL_ENABLE_CLR = DMA_Channel;
    }
}

/**
  * @brief  ��������� ���������/�������������� ����������� ��������� ������� DMA.
  * @param  DMA_Channel  ����� ������.
  *   �������� ��������� ����� ������������ ����� �� @ref DMA_Exported_Defines_Channels_Num.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void DMA_PrmAltCmd(uint32_t DMA_Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_DMA->CHNL_PRI_ALT_SET = DMA_Channel;
    }
    else /* State == DISABLE */
    {
        NT_DMA->CHNL_PRI_ALT_CLR = DMA_Channel;
    }
}

/**
  * @brief  ��������� �������� ���������� ������� DMA.
  * @param  DMA_Channel  ����� ������.
  *   �������� ��������� ����� ������������ ����� �� @ref DMA_Exported_Defines_Channels_Num.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void DMA_HighPriorityCmd(uint32_t DMA_Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(DMA_Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_DMA->CHNL_PRIORITY_SET = DMA_Channel;
    }
    else /* State == DISABLE */
    {
        NT_DMA->CHNL_PRIORITY_CLR = DMA_Channel;
    }
}

/**
  * @brief  ������ � �������� ��������� �������� ����������� DMA.
  * @retval State ������� ��������� ��������� ��������.
  */

DMA_State_TypeDef DMA_StateStatus()
{
    DMA_State_TypeDef State;

    State = (DMA_State_TypeDef)NT_DMA->STATUS_bit.STATE;

    return State;
}

/**
  * @brief  ��������� ����������� DMA.
  * @retval Status ������� ��������� ����������� DMA.
  */

FunctionalState DMA_MasterEnableStatus()
{
    FunctionalState Status;

    if (NT_DMA->STATUS_bit.MASTER_EN)
    {
        Status = ENABLE;
    }
    else
    {
        Status = DISABLE;
    }

    return Status;
}

/**
  * @brief  ���������� ������������ �� ����� ��������� SREQ �������.
  * @retval Status ���� �� �������� @ref FunctionalState:
  *                 - ENABLE - �������������� SREQ (��� � ������� BREQ);
  *                 - DISABLE - �������������� ������ ������� ������� BREQ.
  */

FunctionalState DMA_WaitOnReqStatus(uint32_t DMA_Channel)
{
    FunctionalState Status;

    assert_param(IS_GET_DMA_CHANNEL(DMA_Channel));

    if (NT_DMA->WAITONREQ_STATUS & DMA_Channel)
    {
        Status = ENABLE;
    }
    else
    {
        Status = DISABLE;
    }

    return Status;
}

/**
  * @brief  ���������� ������� ������ �� ����.
  * @retval Status ���� �� �������� @ref OperationStatus:
  *                 - OK - ������ �� ����;
  *                 - ERROR - ��������� ������.
  */

OperationStatus DMA_ErrorStatus()
{
    OperationStatus Status;

    if (NT_DMA->ERR_CLR)
    {
        Status = ERROR;
    }
    else
    {
        Status = OK;
    }

    return Status;
}

/**
  * @brief  ����� ����� ������ �� ����.
  * @retval ���
  */

void DMA_ClearErrorStatus()
{
    NT_DMA->ERR_CLR = 1;
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
