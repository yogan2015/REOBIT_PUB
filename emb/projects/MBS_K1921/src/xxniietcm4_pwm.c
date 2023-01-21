/**
  ******************************************************************************
  * @file    niietcm4_pwm.c
  *
  * @brief   ���� �������� ���������� ���� ������� ��� ������ � ������� ���
  *
  * @author  �����
  *             - ������ ������ (bkolbov), kolbov@niiet.ru
  * @date    23.08.2016
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
  * <h2><center>&copy; 2016 ��� "�����"</center></h2>
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

/** @defgroup PWM
  * @brief ������� ��� ������ ���
  *
  * @attention ������� ��������� ��������� ������ ����������� ����������� ������� PWM, � ����� �� ����������� ��������������.
  *            ���������������� ����� �����-������, � ����� ��������� ������������ � ����� ������ ���������� ����������� ��������.
  *            <br>@ref GPIO : @ref GPIO_Init_Deinit.
  *            <br>@ref RCC : @ref RCC_CLK_Config, @ref RCC_RST_Config.
  *
  * ������� ������ �� ��������� ����������:
  * - @ref PWM_Exported_Functions_CTR
  * - @ref PWM_Exported_Functions_CMP
  * - @ref PWM_Exported_Functions_HighResolution
  * - @ref PWM_Exported_Functions_HoldDetector
  * - @ref PWM_Exported_Functions_DeadBand
  * - @ref PWM_Exported_Functions_PWM_Chopper
  * - @ref PWM_Exported_Functions_TripZone
  * - @ref PWM_Exported_Functions_EventTrigger
  * - @ref PWM_Exported_Functions_IT
  *
  * ����� ��� �������� �������������, ����� ������ ����� �� ������, ��������� ������������
  * � ��������� ������ �����-������:
  * - ����������� ������� (@ref PWM_Exported_Functions_CTR);
  * - ����������� ����������� (@ref PWM_Exported_Functions_CMP);
  * - �������� ���������� �� ��������, ���� ���������� (@ref PWM_Exported_Functions_IT);
  * - ����������� ������ ���������, ���� ��������� �� ����������;
  * - ������ @ref PWM_Exported_Functions_TripZone � @ref PWM_Exported_Functions_HoldDetector �����
  *   �� ������������ ������� ����������, ���� ���������� ���������� � �� ����������;
  * - �������� ������������ ������ ������ ��� (@ref PWM_PrescCmd);
  * - ���� ��� ���� ������� �����, �� �������� �������� �������, � �� ������ ������������,
  *   � ������������ � ��������� ���������, ���-�������.
  *
  * ����� �������� ������������� � ������������� PWM �������� � ����������� � �������� ��������.
  * @{
  */ 

/** @defgroup PWM_Private ��������� ������
  * @{
  */

/** @defgroup PWM_Private_Defines ��������� ���������
  * @{
  */

/**
  * @}
  */

/** @defgroup PWM_Private_Functions ��������� �������
  * @{
  */

/**
  * @brief  ���������� �������������� ������������ �������� ������ ���.
  * @param  Presc ����� ������������� ������.
  *   �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_Presc.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_PrescCmd(uint32_t Presc, FunctionalState State)
{
    assert_param(IS_PWM_PRESC(Presc));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == DISABLE)
    {
        NT_COMMON_REG->PWM_SYNC &= ~Presc;
    }
    else if (State == ENABLE)
    {
        NT_COMMON_REG->PWM_SYNC |= Presc;
    }
}

/**
  * @brief  ����� ����� ������������� ������ ���.
  * @param  SyncSelect  ����� �����.
  *   �������� ��������� ����� �������� �� @ref PWM_Sync_TypeDef.
  * @retval ���
  */

void PWM_SyncConfig(PWM_Sync_TypeDef SyncSelect)
{
    assert_param(IS_PWM_SYNC(SyncSelect));

    NT_COMMON_REG->PWM_CTRL_bit.SYNCSELECT = (uint32_t)SyncSelect;
}

/**
  * @brief  ������������� ��� �������� ����� ��� ���������� �� ���������.
  * @param  PWMx  ����� ������ PWM, ��� x ����� � ��������� 0-8
  * @retval ���
  */

void PWM_DeInit(NT_PWM_TypeDef* PWMx)
{
    RCC_PeriphRst_TypeDef PWMRst;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    if (PWMx == NT_PWM0)
    {
        PWMRst = RCC_PeriphRst_PWM0;
    }
    else if (PWMx == NT_PWM1)
    {
        PWMRst = RCC_PeriphRst_PWM1;
    }
    else if (PWMx == NT_PWM2)
    {
        PWMRst = RCC_PeriphRst_PWM2;
    }
    else if (PWMx == NT_PWM3)
    {
        PWMRst = RCC_PeriphRst_PWM3;
    }
    else if (PWMx == NT_PWM4)
    {
        PWMRst = RCC_PeriphRst_PWM4;
    }
    else if (PWMx == NT_PWM5)
    {
        PWMRst = RCC_PeriphRst_PWM5;
    }
    else if (PWMx == NT_PWM6)
    {
        PWMRst = RCC_PeriphRst_PWM6;
    }
    else if (PWMx == NT_PWM7)
    {
        PWMRst = RCC_PeriphRst_PWM7;
    }
    else /* (PWMx == NT_PWM8) */
    {
        PWMRst = RCC_PeriphRst_PWM8;
    }

    RCC_PeriphRstCmd(PWMRst, DISABLE);
    RCC_PeriphRstCmd(PWMRst, ENABLE);
}

/**
  * @brief  ����������� ������� ���������������� ���������� �� �����(�) PWM.
  * @param  PWMx  ����� ���, ��� x ����� � ��������� 0-8.
  * @param  Channel  ����� ������.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_Channel_TypeDef.
  * @param  ChActionA  ��� ����������� �� ����� �.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_ChAction_TypeDef.
  * @param  ChActionB  ��� ����������� �� ����� B.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_ChAction_TypeDef.
  * @retval ���
  */

void PWM_ChForceContCmd(NT_PWM_TypeDef* PWMx, PWM_Channel_TypeDef Channel, PWM_ChAction_TypeDef ChActionA, PWM_ChAction_TypeDef ChActionB)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CHANNEL(Channel));
    assert_param(IS_PWM_CH_ACTION(ChActionA));
    assert_param(IS_PWM_CH_ACTION(ChActionB));

    if (Channel == PWM_Channel_A)
    {
        PWMx->AQCSFRC_bit.CSFA = (uint32_t)ChActionA;
    }
    else if (Channel == PWM_Channel_B)
    {
        PWMx->AQCSFRC_bit.CSFB = (uint32_t)ChActionB;
    }
    else /* if (Channel == PWM_Channel_AB) */
    {
        PWMx->AQCSFRC = ((uint32_t)ChActionA<<PWM_AQCSFRC_CSFA_Pos) |
                        ((uint32_t)ChActionB<<PWM_AQCSFRC_CSFB_Pos);
    }
}

/**
  * @brief  ��������� ���� ������������ ������������ ���������� �� �����(�) PWM.
  * @param  PWMx  ����� ���, ��� x ����� � ��������� 0-8.
  * @param  Channel  ����� ������.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_Channel_TypeDef.
  * @param  ChActionA  ��� ����������� �� ����� �.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_ChAction_TypeDef.
  * @param  ChActionB  ��� ����������� �� ����� B.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_ChAction_TypeDef.
  * @retval ���
  */

void PWM_ChForceConfig(NT_PWM_TypeDef* PWMx, PWM_Channel_TypeDef Channel, PWM_ChAction_TypeDef ChActionA, PWM_ChAction_TypeDef ChActionB)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CHANNEL(Channel));
    assert_param(IS_PWM_CH_ACTION(ChActionA));
    assert_param(IS_PWM_CH_ACTION(ChActionB));

    if (Channel == PWM_Channel_A)
    {
        PWMx->AQSFRC_bit.ACTSFA = (uint32_t)ChActionA;
    }
    else if (Channel == PWM_Channel_B)
    {
        PWMx->AQSFRC_bit.ACTSFB = (uint32_t)ChActionB;
    }
    else /* if (Channel == PWM_Channel_AB) */
    {
        PWMx->AQSFRC = ((uint32_t)ChActionA<<PWM_AQSFRC_ACTSFA_Pos) |
                       ((uint32_t)ChActionB<<PWM_AQSFRC_ACTSFB_Pos);
    }
}

/**
  * @brief  ���������� ���������� ������������ ������������ ���������� �� �����(�) PWM.
  * @param  PWMx  ����� ���, ��� x ����� � ��������� 0-8.
  * @param  Channel  ����� ������.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_Channel_TypeDef.
  * @retval ���
  */

void PWM_ChForceCmd(NT_PWM_TypeDef* PWMx, PWM_Channel_TypeDef Channel)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CHANNEL(Channel));

    if (Channel == PWM_Channel_A)
    {
        PWMx->AQSFRC_bit.OTSFA = 1;
    }
    else if (Channel == PWM_Channel_B)
    {
        PWMx->AQSFRC_bit.OTSFB = 1;
    }
    else /* if (Channel == PWM_Channel_AB) */
    {
        PWMx->AQSFRC |= (1<<PWM_AQSFRC_OTSFA_Pos) |
                        (1<<PWM_AQSFRC_OTSFB_Pos);
    }
}

/**
  * @brief  �������������� ������ PWMx �������� ���������� ��������� PWM_TimerInitStruct.
  * @param  PWMx  ����� ������ PWM, ��� x ����� � ��������� 0-8
  * @param  PWM_TimerInitStruct ��������� �� ��������� ���� @ref PWM_TimerInit_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval ���
  */

void PWM_CTR_Init(NT_PWM_TypeDef* PWMx, PWM_CTR_Init_TypeDef* PWM_CTR_InitStruct)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CH_ACTION(PWM_CTR_InitStruct->PWM_ChAction_CTREqPeriod_A));
    assert_param(IS_PWM_CH_ACTION(PWM_CTR_InitStruct->PWM_ChAction_CTREqPeriod_B));
    assert_param(IS_PWM_CH_ACTION(PWM_CTR_InitStruct->PWM_ChAction_CTREqZero_A));
    assert_param(IS_PWM_CH_ACTION(PWM_CTR_InitStruct->PWM_ChAction_CTREqZero_B));
    assert_param(IS_PWM_CLK_DIV(PWM_CTR_InitStruct->PWM_ClkDiv));
    assert_param(IS_PWM_CLK_DIV_EXTRA(PWM_CTR_InitStruct->PWM_ClkDivExtra));
    assert_param(IS_PWM_CTR_MODE(PWM_CTR_InitStruct->PWM_CTR_Mode));
    assert_param(IS_PWM_CTR_HALT(PWM_CTR_InitStruct->PWM_CTR_Halt));
    assert_param(IS_PWM_LOAD_MODE(PWM_CTR_InitStruct->PWM_LoadMode_Period));
    assert_param(IS_FUNCTIONAL_STATE(PWM_CTR_InitStruct->PWM_PhaseEn));
    assert_param(IS_PWM_CTR_DIR(PWM_CTR_InitStruct->PWM_CTR_Dir_Phase));
    assert_param(IS_PWM_CTR_SYNC_OUT(PWM_CTR_InitStruct->PWM_CTR_SyncOut));

    PWM_CTR_SetPhase(PWMx, PWM_CTR_InitStruct->PWM_Phase);

    PWMx->AQCTLA_bit.ZRO = (uint32_t)PWM_CTR_InitStruct->PWM_ChAction_CTREqZero_A;
    PWMx->AQCTLA_bit.PRD = (uint32_t)PWM_CTR_InitStruct->PWM_ChAction_CTREqPeriod_A;
    PWMx->AQCTLB_bit.ZRO = (uint32_t)PWM_CTR_InitStruct->PWM_ChAction_CTREqZero_B;
    PWMx->AQCTLB_bit.PRD = (uint32_t)PWM_CTR_InitStruct->PWM_ChAction_CTREqPeriod_B;

    PWMx->TBCTL_bit.PHSDIR = (uint32_t)PWM_CTR_InitStruct->PWM_CTR_Dir_Phase;
    PWMx->TBCTL_bit.CLKDIV = (uint32_t)PWM_CTR_InitStruct->PWM_ClkDiv;
    PWMx->TBCTL_bit.HSPCLKDIV = (uint32_t)PWM_CTR_InitStruct->PWM_ClkDivExtra;
    PWMx->TBCTL_bit.SYNCOSEL = (uint32_t)PWM_CTR_InitStruct->PWM_CTR_SyncOut;
    PWMx->TBCTL_bit.PRDLD = (uint32_t)PWM_CTR_InitStruct->PWM_LoadMode_Period;
    PWMx->TBCTL_bit.PHSEN = (uint32_t)PWM_CTR_InitStruct->PWM_PhaseEn;
    PWMx->TBCTL_bit.CTRMODE = (uint32_t)PWM_CTR_InitStruct->PWM_CTR_Mode;

    PWM_CTR_SetPeriod(PWMx, PWM_CTR_InitStruct->PWM_Period);
}

/**
  * @brief  ���������� ������� ����� ��������� PWM_TimerInitStruct ���������� �� ���������.
  * @param  PWM_TimerInitStruct ��������� �� ��������� ���� @ref PWM_TimerInit_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void PWM_CTR_StructInit(PWM_CTR_Init_TypeDef* PWM_CTR_InitStruct)
{
    PWM_CTR_InitStruct->PWM_ChAction_CTREqPeriod_A = PWM_ChAction_None;
    PWM_CTR_InitStruct->PWM_ChAction_CTREqPeriod_B = PWM_ChAction_None;
    PWM_CTR_InitStruct->PWM_ChAction_CTREqZero_A = PWM_ChAction_None;
    PWM_CTR_InitStruct->PWM_ChAction_CTREqZero_B = PWM_ChAction_None;
    PWM_CTR_InitStruct->PWM_ClkDiv = PWM_ClkDiv_1;
    PWM_CTR_InitStruct->PWM_ClkDivExtra = PWM_ClkDivExtra_1;
    PWM_CTR_InitStruct->PWM_CTR_Mode = PWM_CTR_Mode_Up;
    PWM_CTR_InitStruct->PWM_CTR_Halt = PWM_CTR_Halt_StopOnTBCLK;
    PWM_CTR_InitStruct->PWM_LoadMode_Period = PWM_LoadMode_Shadow;
    PWM_CTR_InitStruct->PWM_Period = 0;
    PWM_CTR_InitStruct->PWM_Phase = 0;
    PWM_CTR_InitStruct->PWM_PhaseEn = DISABLE;
    PWM_CTR_InitStruct->PWM_CTR_Dir_Phase = PWM_CTR_Dir_Down;
    PWM_CTR_InitStruct->PWM_CTR_SyncOut = PWM_CTR_SyncOut_SyncIn;
}

/**
  * @brief  ������ ������� ����� ��������� ������� PWM.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  TimerStatus ����� ������.
  *   �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_CTR_Status.
  * @retval Status ������ ����������. ���� ������� ��������� ������,
  *   �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus PWM_CTR_Status(NT_PWM_TypeDef* PWMx, uint32_t CTR_Status)
{
    FlagStatus Status;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CTR_STATUS(CTR_Status));

    if (PWMx->TBSTS & CTR_Status)
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
  * @brief  ����� ������ �������� ������� PWM.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  TimerStatus ����� ������.
  *   �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_TimerStatus.
  * @retval ���
  */

void PWM_CTR_StatusClear(NT_PWM_TypeDef* PWMx, uint32_t CTR_Status)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CTR_STATUS(CTR_Status));

    PWMx->TBSTS = CTR_Status;
}

/**
  * @brief  ��������� �������� �������� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  CounterVal  �������� ��������.
  * @retval ���
  */

void PWM_CTR_SetValue(NT_PWM_TypeDef* PWMx, uint32_t CTR_Val)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_COUNTER_VAL(CTR_Val));

    PWMx->TBCTR = CTR_Val;
}

/**
  * @brief  ��������� �������� ������� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  PeriodVal  �������� �������.
  * @retval ���
  */

void PWM_CTR_SetPeriod(NT_PWM_TypeDef* PWMx, uint32_t CTR_PeriodVal)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_PERIOD_VAL(CTR_PeriodVal));

    PWMx->TBPRD = CTR_PeriodVal;
}

/**
  * @brief  ��������� �������� ���� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  PhaseVal  �������� ����.
  * @retval ���
  */

void PWM_CTR_SetPhase(NT_PWM_TypeDef* PWMx, uint32_t CTR_PhaseVal)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_PHASE_VAL(CTR_PhaseVal));

    PWMx->TBPHS_bit.TBPHS = CTR_PhaseVal;
}

/**
  * @brief  ��������� �������� �������� �������� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval CounterVal  �������� ��������.
  */

uint32_t PWM_CTR_GetValue(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    return PWMx->TBCTR;
}

/**
  * @brief  ��������� �������� �������� ������� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval PeriodVal  �������� �������.
  */

uint32_t PWM_CTR_GetPeriod(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    return PWMx->TBPRD;
}

/**
  * @brief  ��������� �������� �������� ���� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval PhaseVal  �������� ����.
  */

uint32_t PWM_CTR_GetPhase(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    return PWMx->TBPHS_bit.TBPHS;
}

/**
  * @brief  ����������� ������ �������� �������������� SYNCI.
  * @retval ���
  */

void PWM_CTR_SWSyncInCmd(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    PWMx->TBCTL_bit.SWFSYNC = 1;
}

/**
  * @brief  �������������� ����������� PWMx �������� ���������� ��������� PWM_CMP_InitStruct.
  * @param  PWMx  ����� ������ PWM, ��� x ����� � ��������� 0-8
  * @param  PWM_CMP_InitStruct ��������� �� ��������� ���� @ref PWM_CMP_Init_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval ���
  */

void PWM_CMP_Init(NT_PWM_TypeDef* PWMx, PWM_CMP_Init_TypeDef* PWM_CMP_InitStruct)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CH_ACTION(PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Down_A));
    assert_param(IS_PWM_CH_ACTION(PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Up_A));
    assert_param(IS_PWM_CH_ACTION(PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Down_A));
    assert_param(IS_PWM_CH_ACTION(PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Up_A));
    assert_param(IS_PWM_LOAD_EVENT(PWM_CMP_InitStruct->PWM_LoadEvent_CMPA));
    assert_param(IS_PWM_LOAD_MODE(PWM_CMP_InitStruct->PWM_LoadMode_CMPA));
    assert_param(IS_PWM_CH_ACTION(PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Down_B));
    assert_param(IS_PWM_CH_ACTION(PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Up_B));
    assert_param(IS_PWM_CH_ACTION(PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Down_B));
    assert_param(IS_PWM_CH_ACTION(PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Up_B));
    assert_param(IS_PWM_LOAD_EVENT(PWM_CMP_InitStruct->PWM_LoadEvent_CMPB));
    assert_param(IS_PWM_LOAD_MODE(PWM_CMP_InitStruct->PWM_LoadMode_CMPB));

    PWMx->CMPCTL_bit.LOADAMODE = (uint32_t)PWM_CMP_InitStruct->PWM_LoadEvent_CMPA;
    PWMx->CMPCTL_bit.LOADBMODE = (uint32_t)PWM_CMP_InitStruct->PWM_LoadEvent_CMPB;
    PWMx->CMPCTL_bit.SHDWAMODE = (uint32_t)PWM_CMP_InitStruct->PWM_LoadMode_CMPA;
    PWMx->CMPCTL_bit.SHDWBMODE = (uint32_t)PWM_CMP_InitStruct->PWM_LoadMode_CMPB;

    PWMx->AQCTLA_bit.CAD = (uint32_t)PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Down_A;
    PWMx->AQCTLA_bit.CAU = (uint32_t)PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Up_A;
    PWMx->AQCTLA_bit.CBD = (uint32_t)PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Down_A;
    PWMx->AQCTLA_bit.CBU = (uint32_t)PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Up_A;
    PWMx->AQCTLB_bit.CAD = (uint32_t)PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Down_B;
    PWMx->AQCTLB_bit.CAU = (uint32_t)PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Up_B;
    PWMx->AQCTLB_bit.CBD = (uint32_t)PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Down_B;
    PWMx->AQCTLB_bit.CBU = (uint32_t)PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Up_B;

    PWM_CMP_SetA(PWMx, PWM_CMP_InitStruct->PWM_CMPA);
    PWM_CMP_SetB(PWMx, PWM_CMP_InitStruct->PWM_CMPB);
}

/**
  * @brief  ���������� ������� ����� ��������� PWM_CMPInitStruct ���������� �� ���������.
  * @param  PWM_CMPInitStruct ��������� �� ��������� ���� @ref PWM_CMPInit_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void PWM_CMP_StructInit(PWM_CMP_Init_TypeDef* PWM_CMP_InitStruct)
{
    PWM_CMP_InitStruct->PWM_CMPA = 0;
    PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Down_A = PWM_ChAction_None;
    PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Up_A = PWM_ChAction_None;
    PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Down_A = PWM_ChAction_None;
    PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Up_A = PWM_ChAction_None;
    PWM_CMP_InitStruct->PWM_LoadEvent_CMPA = PWM_LoadEvent_CTREqZero;
    PWM_CMP_InitStruct->PWM_LoadMode_CMPA = PWM_LoadMode_Shadow;
    PWM_CMP_InitStruct->PWM_CMPB = 0;
    PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Down_B = PWM_ChAction_None;
    PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPA_Up_B = PWM_ChAction_None;
    PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Down_B = PWM_ChAction_None;
    PWM_CMP_InitStruct->PWM_ChAction_CTREqCMPB_Up_B = PWM_ChAction_None;
    PWM_CMP_InitStruct->PWM_LoadEvent_CMPB = PWM_LoadEvent_CTREqZero;
    PWM_CMP_InitStruct->PWM_LoadMode_CMPB = PWM_LoadMode_Shadow;
}


/**
  * @brief  ��������� �������� ��������� ����������� A ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  CMPAVal  �������� ���������.
  * @retval ���
  */

void PWM_CMP_SetA(NT_PWM_TypeDef* PWMx, uint32_t CMPAVal)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CMP_VAL(CMPAVal));

    PWMx->CMPA_bit.CMPA = CMPAVal;
}

/**
  * @brief  ��������� �������� ��������� ����������� B ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  CMPBVal  �������� ���������.
  * @retval ���
  */

void PWM_CMP_SetB(NT_PWM_TypeDef* PWMx, uint32_t CMPBVal)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CMP_VAL(CMPBVal));

    PWMx->CMPB_bit.CMPB = CMPBVal;
}

/**
  * @brief  ��������� �������� �������� ��������� ����������� A ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval CMPAVal  �������� ���������.
  */

uint32_t PWM_CMP_GetA(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    return PWMx->CMPA_bit.CMPA;
}

/**
  * @brief  ��������� �������� �������� ��������� ����������� B ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval CMPBVal  �������� ���������.
  */

uint32_t PWM_CMP_GetB(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    return PWMx->CMPB_bit.CMPB;
}

/**
  * @brief  ������ ������� ����� ��������� ������������ PWM.
  *     ����� �����������, ���� ��������� ������ � �������� ������� �������� ��������� �� ��������.
  *     ������������ ����� ������������� ��� ������ ������ � ������� �������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  CMP_Status ����� ������.
  *   �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_CMP_Status.
  * @retval Status ������ ������. ���� ������� ��������� ������,
  *   �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus PWM_CMP_Status(NT_PWM_TypeDef* PWMx, uint32_t CMP_Status)
{
    FlagStatus Status;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_CMP_STATUS(CMP_Status));

    if (PWMx->CMPCTL & CMP_Status)
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
  * @brief  �������������� ����� �������� ���������� PWMx �������� ���������� ��������� PWM_HR_InitStruct.
  * @attention
  *     - ����� �������� ������ ��� ������� � ���0-5.
  *     - ��������� ������ ���������� ��������� ������ ����� ��������� �������� � ������������:
  *     @ref PWM_CTR_Init � @ref PWM_CMP_Init.
  *     - ��� ������� �������� �������� ���������� ����� ���������� �������� ��������� � ��� ������� ������,
  *     ��������� ������� ��� ������� ������ ������ ��������� � ����������� ������� ������ �������� CMPA
  *     (@ref PWM_CMP_Init).
  * @param  PWMx  ����� ������ PWM, ��� x ����� � ��������� 0-5.
  * @param  PWM_HR_InitStruct ��������� �� ��������� ���� @ref PWM_HR_Init_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval ���
  */

void PWM_HR_Init(NT_PWM_TypeDef* PWMx, PWM_HR_Init_TypeDef* PWM_HR_InitStruct)
{
    assert_param(IS_PWM_HR_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_HR_CMP_LOAD(PWM_HR_InitStruct->PWM_HR_CMPLoad));
    assert_param(IS_PWM_HR_MODE(PWM_HR_InitStruct->PWM_HR_Mode));
    assert_param(IS_PWM_HR_EDGE(PWM_HR_InitStruct->PWM_HR_Edge));

    PWMx->HRCNFG_bit.HR_LOAD = (uint32_t)PWM_HR_InitStruct->PWM_HR_CMPLoad;
    PWMx->HRCNFG_bit.CTLMODE = (uint32_t)PWM_HR_InitStruct->PWM_HR_Mode;
    PWMx->HRCNFG_bit.EDGMODE = (uint32_t)PWM_HR_InitStruct->PWM_HR_Edge;

    PWM_HR_SetCMP(PWMx, PWM_HR_InitStruct->PWM_HR_CMP);
    PWM_HR_SetPhase(PWMx, PWM_HR_InitStruct->PWM_HR_Phase);
}

/**
  * @brief  ���������� ������� ����� ��������� PWM_HR_InitStruct ���������� �� ���������.
  * @param  PWM_HR_InitStruct ��������� �� ��������� ���� @ref PWM_HR_Init_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */


void PWM_HR_StructInit(PWM_HR_Init_TypeDef* PWM_HR_InitStruct)
{
    PWM_HR_InitStruct->PWM_HR_CMPLoad = PWM_HR_CMPLoad_CTREqZero;
    PWM_HR_InitStruct->PWM_HR_Mode = PWM_HR_Mode_CMP;
    PWM_HR_InitStruct->PWM_HR_Edge = PWM_HR_Edge_None;
    PWM_HR_InitStruct->PWM_HR_CMP = 0;
    PWM_HR_InitStruct->PWM_HR_Phase = 0;
}

/**
  * @brief  ��������� ������������ �������� ��������� ����������� A ��� �������� ����������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-5.
  * @param  HR_CMPVal  �������� ���������.
  * @retval ���
  */

void PWM_HR_SetCMP(NT_PWM_TypeDef* PWMx, uint32_t HR_CMPVal)
{
    assert_param(IS_PWM_HR_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_HR_CMP_VAL(HR_CMPVal));

    PWMx->CMPA_bit.CMPAHR = HR_CMPVal;
}

/**
  * @brief  ��������� ������������ �������� ���� ��� �������� ����������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-5.
  * @param  HR_PhaseVal  �������� ����.
  * @retval ���
  */

void PWM_HR_SetPhase(NT_PWM_TypeDef* PWMx, uint32_t HR_PhaseVal)
{
    assert_param(IS_PWM_HR_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_HR_PHASE_VAL(HR_PhaseVal));

    PWMx->TBPHS_bit.TBPHSHR = HR_PhaseVal;
}

/**
  * @brief  ��������� �������� ������������ �������� ��������� ��� �������� ����������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-5.
  * @retval HR_CMPVal  �������� ���������.
  */

uint32_t PWM_HR_GetCMP(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_HR_ALL_PERIPH(PWMx));

    return PWMx->CMPA_bit.CMPAHR;
}

/**
  * @brief  ��������� �������� ������������ �������� ���� ��� �������� ����������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-5.
  * @retval HR_PhaseVal  �������� ���������.
  */

uint32_t PWM_HR_GetPhase(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_HR_ALL_PERIPH(PWMx));

    return PWMx->TBPHS_bit.TBPHSHR;
}

/**
  * @brief  ��������� ���������� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  PWM_Event_TypeDef  ����� ������� ��� ������������� ����������.
  *   �������� ��������� ����� �������� �� @ref PWM_Event_TypeDef.
  * @param  ITPeriod  ����� ���������� ������� ��� ������������� ����������.
  *   �������� ��������� ����� �������� �� ��������� 0-3,
  *   ��� 0 - ������������ ������� �������, 1 - ������� ������� � �.�.
  * @retval ���
  */

void PWM_ITConfig(NT_PWM_TypeDef* PWMx, PWM_Event_TypeDef Event, uint32_t ITPeriod)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_EVENT(Event));
    assert_param(IS_PWM_IT_PERIOD(ITPeriod));

    PWMx->ETSEL_bit.INTSEL = (uint32_t)Event;
    PWMx->ETPS_bit.INTPRD = ITPeriod;
}

/**
  * @brief  ���������� ������ ���������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_ITCmd(NT_PWM_TypeDef* PWMx, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    PWMx->ETSEL_bit.INTEN = (uint32_t)State;
}

/**
  * @brief  ��������� �������� �������� �������� �������, ���������� � ����������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval EventCount  ��������.
  */

uint32_t PWM_GetITEventCount(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    return PWMx->ETPS_bit.INTCNT;
}

/**
  * @brief  ������ ������� ����� ���������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval Status ������ ����������.
  */

FlagStatus PWM_ITStatus(NT_PWM_TypeDef* PWMx)
{
    FlagStatus Status;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    if (PWMx->ETFLG_bit.INT)
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
  * @brief  ����� ����� ���������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval ���
  */

void PWM_ITStatusClear(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    PWMx->ETCLR_bit.INT = 1;
}

/**
  * @brief  ������ ������� ������� ���������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval Status ������ ������� ����������.
  */

FlagStatus PWM_ITPendStatus(NT_PWM_TypeDef* PWMx)
{
    FlagStatus Status;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    if (PWMx->INTCLR_bit.INT)
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
  * @brief  ����� ������� ���������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval ���
  */

void PWM_ITPendClear(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    PWMx->INTCLR_bit.INT = 1;
}

/**
  * @brief  ����������� ����� ���������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval ���
  */

void PWM_ITForce(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    PWMx->ETFRC_bit.INT = 1;
}

/**
  * @brief  �������������� ���� "�������� �������" PWMx �������� ���������� ��������� PWM_DB_InitStruct.
  * @param  PWMx  ����� ������ PWM, ��� x ����� � ��������� 0-8
  * @param  PWM_DB_InitStruct ��������� �� ��������� ���� @ref PWM_DB_Init_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval ���
  */

void PWM_DB_Init(NT_PWM_TypeDef* PWMx, PWM_DB_Init_TypeDef* PWM_DB_InitStruct)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_DB_IN(PWM_DB_InitStruct->PWM_DB_In));
    assert_param(IS_PWM_DB_POL(PWM_DB_InitStruct->PWM_DB_Pol));
    assert_param(IS_PWM_DB_OUT(PWM_DB_InitStruct->PWM_DB_Out));

    PWMx->DBCTL_bit.IN_MODE = (uint32_t)PWM_DB_InitStruct->PWM_DB_In;
    PWMx->DBCTL_bit.POLSEL = (uint32_t)PWM_DB_InitStruct->PWM_DB_Pol;
    PWMx->DBCTL_bit.OUT_MODE = (uint32_t)PWM_DB_InitStruct->PWM_DB_Out;

    PWM_DB_SetRiseDelay(PWMx, PWM_DB_InitStruct->PWM_DB_RiseDelay);
    PWM_DB_SetFallDelay(PWMx, PWM_DB_InitStruct->PWM_DB_FallDelay);
}

/**
  * @brief  ���������� ������� ����� ��������� PWM_DB_InitStruct ���������� �� ���������.
  * @param  PWM_DB_InitStruct ��������� �� ��������� ���� @ref PWM_DB_Init_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void PWM_DB_StructInit(PWM_DB_Init_TypeDef* PWM_DB_InitStruct)
{
    PWM_DB_InitStruct->PWM_DB_In = PWM_DB_In_A;
    PWM_DB_InitStruct->PWM_DB_Pol = PWM_DB_Pol_ActHigh;
    PWM_DB_InitStruct->PWM_DB_Out = PWM_DB_Out_BypassAB;
    PWM_DB_InitStruct->PWM_DB_RiseDelay = 0;
    PWM_DB_InitStruct->PWM_DB_FallDelay = 0;
}

/**
  * @brief  ��������� �������� �������� �������� �� ��������� ������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  RiseDelayVal  ��������.
  * @retval ���
  */

void PWM_DB_SetRiseDelay(NT_PWM_TypeDef* PWMx, uint32_t RiseDelayVal)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_DB_DELAY_VAL(RiseDelayVal));

    PWMx->DBRED = RiseDelayVal;
}

/**
  * @brief  ��������� �������� �������� �������� �� ������� ������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  FallDelayVal  ��������.
  * @retval ���
  */

void PWM_DB_SetFallDelay(NT_PWM_TypeDef* PWMx, uint32_t FallDelayVal)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_DB_DELAY_VAL(RiseDelayVal));

    PWMx->DBFED = FallDelayVal;
}

/**
  * @brief  ��������� �������� �������� �������� �������� �� ��������� ������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval RiseDelayVal  ��������.
  */

uint32_t PWM_DB_GetRiseDelay(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    return PWMx->DBRED;
}

/**
  * @brief  ��������� �������� �������� �������� �������� �� ������� ������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval FallDelayVal  ��������.
  */

uint32_t PWM_DB_GetFallDelay(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    return PWMx->DBFED;
}

/**
  * @brief  ��������� ������ ���������� �������� ���������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  FilterVal  ��������.
  *     �������� ��������� ����� �������� �� ��������� 0x00-0xFF,
  *     ��� 0 - ������ ��������, � 0xFF - 25.6 ��� (��� ��������� 0.1 ���).
  * @retval ���
  */

void PWM_FilterConfig(NT_PWM_TypeDef* PWMx, uint32_t FilterVal)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_FILTER(FilterVal));

    PWMx->FWDTH = FilterVal;
}

/**
  * @brief ��������� ���������� �������� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  DutyVal  �������� ���������� ������� � ������������ ���������.
  *     �������� ��������� ����� �������� �� ��������� 0x0-0x6,
  *     ��� 0x0 - ���������� 1/8, � 0x6 - 7/8.
  * @param  FreqDivVal  �������� �������� ������� ������� � ������������ ���������.
  *     �������� ��������� ����� �������� �� ��������� 0x0-0x7,
  *     ��� 0x0 - ��� �������, 0x1 - � ����. 1/2, � 0x7 - 1/8.
  * @param  FirstWidthVal  �������� ������ ������� �������� � ������ SysClk/8.
  *     �������� ��������� ����� �������� �� ��������� 0x0-0xF,
  *     ��� 0x0 - 1 ����, � 0xF - 16 ������.
  * @retval ���
  */

void PWM_PC_Config(NT_PWM_TypeDef* PWMx, uint32_t DutyVal, uint32_t FreqDivVal, uint32_t FirstWidthVal)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_PC_DUTY(DutyVal));
    assert_param(IS_PWM_PC_FREQ_DIV(FreqDivVal));
    assert_param(IS_PWM_PC_FIRST_WIDTH(FirstWidthVal));

    PWMx->PCCTL_bit.CHPDUTY = DutyVal;
    PWMx->PCCTL_bit.SHRFREQ = FreqDivVal;
    PWMx->PCCTL_bit.OSHTWTH = FirstWidthVal;
}

/**
  * @brief  ��������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_PC_Cmd(NT_PWM_TypeDef* PWMx, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    PWMx->PCCTL_bit.CHPEN = (uint32_t)State;
}

/**
  * @brief  ��������� ��������� ������ ��� ����������� ������� ������.
  * @param  PWMx  ����� ���, ��� x ����� � ��������� 0-8.
  * @param  TZ_ActionA  ����� �������� ��� ������ A.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_TZ_Action_TypeDef.
  * @param  TZ_ActionB  ����� �������� ��� ������ B.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_TZ_Action_TypeDef.
  * @retval ���
  */

void PWM_TZ_ActionConfig(NT_PWM_TypeDef* PWMx, PWM_TZ_Action_TypeDef TZ_ActionA, PWM_TZ_Action_TypeDef TZ_ActionB)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_TZ_ACTION(TZ_ActionA));
    assert_param(IS_PWM_TZ_ACTION(TZ_ActionB));

    PWMx->TZCTL_bit.TZA = (uint32_t)TZ_ActionA;
    PWMx->TZCTL_bit.TZB = (uint32_t)TZ_ActionB;
}

/**
  * @brief  ��������� ����������� ��������� ������� ������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  TZ_Channel ����� ������� ������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_TZ_Channel.
  * @param  State  ����� ���������.
  *     �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_TZ_CycleCmd(NT_PWM_TypeDef* PWMx, uint32_t TZ_Channel, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_TZ_CHANNEL(TZ_Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        PWMx->TZSEL |= (uint32_t)TZ_Channel;
    }
    else
    {
        PWMx->TZSEL &= ~(uint32_t)TZ_Channel;
    }
}

/**
  * @brief  ��������� ����������� ��������� ������� ������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  TZ_Channel ����� ������� ������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_TZ_Channel.
  * @param  State  ����� ���������.
  *     �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_TZ_OneShotCmd(NT_PWM_TypeDef* PWMx, uint32_t TZ_Channel, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_TZ_CHANNEL(TZ_Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        PWMx->TZSEL |= ((uint32_t)TZ_Channel << 8);
    }
    else
    {
        PWMx->TZSEL &= ~((uint32_t)TZ_Channel << 8);
    }
}

/**
  * @brief  ��������� ���������� �� ������� ������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  TZ_ITSource ����� ��������� ����������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_TZ_ITSource.
  * @param  State  ����� ���������.
  *     �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_TZ_ITCmd(NT_PWM_TypeDef* PWMx, uint32_t TZ_ITSource, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_TZ_IT_SOURCE(TZ_ITSource));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        PWMx->TZEINT |= (uint32_t)TZ_ITSource;
    }
    else
    {
        PWMx->TZEINT &= ~(uint32_t)TZ_ITSource;
    }
}

/**
  * @brief  ������ ������� ����� ���������� �� ����������� �������� ������ ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  TZ_ITStatus ����� ������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_TZ_ITStatus.
  * @retval Status ������ ����������. ���� ������� ��������� ������,
  *     �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus PWM_TZ_ITStatus(NT_PWM_TypeDef* PWMx, uint32_t TZ_ITStatus)
{
    FlagStatus Status;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_TZ_IT_STATUS(TZ_ITStatus));

    if (PWMx->TZFLG & TZ_ITStatus)
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
  * @brief  ����� ����� ���������� �� ����������� �������� ������ ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  TZ_ITStatus ����� ������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_TZ_ITStatus.
  * @retval ���
  */

void PWM_TZ_ITStatusClear(NT_PWM_TypeDef* PWMx, uint32_t TZ_ITStatus)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_TZ_IT_STATUS(TZ_ITStatus));

    PWMx->TZCLR = TZ_ITStatus;
}

/**
  * @brief  ������ ������� ������� ���������� �� ������� ������ ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval Status ������ ������� ����������.
  */

FlagStatus PWM_TZ_ITPendStatus(NT_PWM_TypeDef* PWMx)
{
    FlagStatus Status;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    if (PWMx->TZINTCLR_bit.TZINT)
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
  * @brief  ����� ������� ���������� �� ������� ������ ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval ���
  */

void PWM_TZ_ITPendClear(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    PWMx->TZINTCLR_bit.TZINT = 1;
}

/**
  * @brief  ����������� ����� ���������� �� ������� ������ ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  TZ_ITSource ����� ��������� ����������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_TZ_ITSource
  * @retval ���
  */

void PWM_TZ_ITForce(NT_PWM_TypeDef* PWMx, uint32_t TZ_ITSource)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_TZ_IT_SOURCE(TZ_ITSource));

    PWMx->TZFRC = TZ_ITSource;
}

/**
  * @brief  �������������� ���� "�������� �������" PWMx, �������� ���������� ��������� PWM_ET_InitStruct.
  * @param  PWMx  ����� ������ PWM, ��� x ����� � ��������� 0-8
  * @param  PWM_ET_InitStruct ��������� �� ��������� ���� @ref PWM_ET_Init_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval ���
  */

void PWM_ET_Init(NT_PWM_TypeDef* PWMx, PWM_ET_Init_TypeDef* PWM_ET_InitStruct)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_EVENT(PWM_ET_InitStruct->PWM_ET_Event_A));
    assert_param(IS_PWM_ET_PERIOD(PWM_ET_InitStruct->PWM_ET_Period_A));
    assert_param(IS_PWM_EVENT(PWM_ET_InitStruct->PWM_ET_Event_B));
    assert_param(IS_PWM_ET_PERIOD(PWM_ET_InitStruct->PWM_ET_Period_B));

    PWMx->ETSEL_bit.SOCASEL = (uint32_t)PWM_ET_InitStruct->PWM_ET_Event_A;
    PWMx->ETSEL_bit.SOCBSEL = (uint32_t)PWM_ET_InitStruct->PWM_ET_Event_B;

    PWMx->ETPS_bit.SOCAPRD = PWM_ET_InitStruct->PWM_ET_Period_A;
    PWMx->ETPS_bit.SOCBPRD = PWM_ET_InitStruct->PWM_ET_Period_B;
}

/**
  * @brief  ���������� ������� ����� ��������� PWM_ET_InitStruct ���������� �� ���������.
  * @param  PWM_ET_InitStruct ��������� �� ��������� ���� @ref PWM_ET_Init_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void PWM_ET_StructInit(PWM_ET_Init_TypeDef* PWM_ET_InitStruct)
{
    PWM_ET_InitStruct->PWM_ET_Event_A = PWM_Event_None;
    PWM_ET_InitStruct->PWM_ET_Event_B = PWM_Event_None;
    PWM_ET_InitStruct->PWM_ET_Period_A = 0;
    PWM_ET_InitStruct->PWM_ET_Period_B = 0;
}

/**
  * @brief  ��������� ��������� ������ ������� ��� �� �������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  ET_Channel ����� ������-���������.
  *     �������� ��������� ����� �������� �� @ref PWM_ET_Channel_TypeDef.
  * @param  State  ����� ���������.
  *     �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_ET_Cmd(NT_PWM_TypeDef* PWMx, PWM_ET_Channel_TypeDef ET_Channel, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_ET_CHANNEL(ET_Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (ET_Channel == PWM_ET_Channel_A)
    {
        PWMx->ETSEL_bit.SOCAEN = (uint32_t)State;
    }
    else /* if (ET_Channel == PWM_ET_Channel_B) */
    {
        PWMx->ETSEL_bit.SOCBEN = (uint32_t)State;
    }
}

/**
  * @brief  ��������� �������� �������� �������� �������, ����������� � ��������� ������� ������� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval EventCount  ��������.
  */

uint32_t PWM_ET_GetEventCount(NT_PWM_TypeDef* PWMx, PWM_ET_Channel_TypeDef ET_Channel)
{
    uint32_t EventCount;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_ET_CHANNEL(ET_Channel));

    if (ET_Channel == PWM_ET_Channel_A)
    {
        EventCount = PWMx->ETPS_bit.SOCACNT;
    }
    else /* if (ET_Channel == PWM_ET_Channel_B) */
    {
        EventCount = PWMx->ETPS_bit.SOCBCNT;
    }

    return EventCount;
}

/**
  * @brief  ������ ������� ����� ��������� ������� ������� ��� ��������� ������ ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  ET_Status ����� ������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_ET_Status.
  * @retval Status ������. ���� ������� ��������� ������,
  *     �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus PWM_ET_Status(NT_PWM_TypeDef* PWMx, uint32_t ET_Status)
{
    FlagStatus Status;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_ET_STATUS(ET_Status));

    if (PWMx->ETFLG & ET_Status)
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
  * @brief  ����� ����� ��������� ������� ������� ��� ��������� ������ ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  ET_Status ����� ������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_ET_Status.
  * @retval ���
  */

void PWM_ET_StatusClear(NT_PWM_TypeDef* PWMx, uint32_t ET_Status)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_ET_STATUS(ET_Status));

    PWMx->ETCLR = ET_Status;
}

/**
  * @brief  ����������� ����� ��������� ������� ������� ��� ��������� ������ ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  ET_Status ����� ������-���������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_ET_Status
  * @retval ���
  */

void PWM_ET_Force(NT_PWM_TypeDef* PWMx, uint32_t ET_Status)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_ET_STATUS(ET_Status));

    PWMx->ETFRC = ET_Status;
}

/**
  * @brief  ��������� ��������� ������ ��� ����������� ������� ���������.
  * @param  PWMx  ����� ���, ��� x ����� � ��������� 0-8.
  * @param  HD_ActionA  ����� �������� ��� ������ A.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_HD_Action_TypeDef.
  * @param  HD_ActionB  ����� �������� ��� ������ B.
  *     �������� ����� ��������� ����� �������� �� @ref PWM_HD_Action_TypeDef.
  * @retval ���
  */

void PWM_HD_ActionConfig(NT_PWM_TypeDef* PWMx, PWM_HD_Action_TypeDef HD_ActionA, PWM_HD_Action_TypeDef HD_ActionB)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_HD_ACTION(HD_ActionA));
    assert_param(IS_PWM_HD_ACTION(HD_ActionB));

    PWMx->HDCTL_bit.HDA = (uint32_t)HD_ActionA;
    PWMx->HDCTL_bit.HDB = (uint32_t)HD_ActionB;
}

/**
  * @brief  ����� ������� ��� ��������� ������� ���������.
  * @param  PWMx  ����� ���, ��� x ����� � ��������� 0-8.
  * @param  HD_Channel ����� ������-���������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_HD_Channel
  * @param  State  ����� ���������.
  *     �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_HD_ChannelCmd(NT_PWM_TypeDef* PWMx, uint32_t HD_Channel, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_HD_CHANNEL(HD_Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        PWMx->HDSEL |= (uint32_t)HD_Channel;
    }
    else
    {
        PWMx->HDSEL &= ~(uint32_t)HD_Channel;
    }
}

/**
  * @brief  ��������� ����������� ��������� ������� ���������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  State  ����� ���������.
  *     �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_HD_CycleCmd(NT_PWM_TypeDef* PWMx, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    PWMx->HDSEL_bit.CBC = (uint32_t)State;
}

/**
  * @brief  ��������� ����������� ��������� ������� ���������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  State  ����� ���������.
  *     �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_HD_OneShotCmd(NT_PWM_TypeDef* PWMx, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    PWMx->HDSEL_bit.OSHT = (uint32_t)State;
}

/**
  * @brief  ��������� ���������� �� ������� ���������.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  HD_ITSource ����� ��������� ����������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_HD_ITSource.
  * @param  State  ����� ���������.
  *     �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void PWM_HD_ITCmd(NT_PWM_TypeDef* PWMx, uint32_t HD_ITSource, FunctionalState State)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_HD_IT_SOURCE(HD_ITSource));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        PWMx->HDEINT |= (uint32_t)HD_ITSource;
    }
    else
    {
        PWMx->HDEINT &= ~(uint32_t)HD_ITSource;
    }
}

/**
  * @brief  ������ ������� ����� ���������� �� ����������� ������� ��������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  HD_ITStatus ����� ������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_HD_ITStatus.
  * @retval Status ������ ����������. ���� ������� ��������� ������,
  *     �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus PWM_HD_ITStatus(NT_PWM_TypeDef* PWMx, uint32_t HD_ITStatus)
{
    FlagStatus Status;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_HD_IT_STATUS(HD_ITStatus));

    if (PWMx->HDFLG & HD_ITStatus)
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
  * @brief  ����� ����� ���������� �� ����������� ������� ��������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  HD_ITStatus ����� ������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_HD_ITStatus.
  * @retval ���
  */

void PWM_HD_ITStatusClear(NT_PWM_TypeDef* PWMx, uint32_t HD_ITStatus)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_TZ_IT_STATUS(HD_ITStatus));

    PWMx->HDCLR = HD_ITStatus;
}

/**
  * @brief  ������ ������� ������� ���������� �� ����������� ������� ��������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval Status ������ ������� ����������.
  */

FlagStatus PWM_HD_ITPendStatus(NT_PWM_TypeDef* PWMx)
{
    FlagStatus Status;

    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    if (PWMx->HDINTCLR_bit.HDINT)
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
  * @brief  ����� ������� ���������� �� ����������� ������� ��������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @retval ���
  */

void PWM_HD_ITPendClear(NT_PWM_TypeDef* PWMx)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));

    PWMx->HDINTCLR_bit.HDINT = 1;
}

/**
  * @brief  ����������� ����� ���������� �� ����������� ������� ��������� ���������� ����� ���.
  * @param  PWMx  ����� PWM, ��� x ����� � ��������� 0-8.
  * @param  HD_ITSource ����� ��������� ����������.
  *     �������� ��������� ����� ������������ �������� �� @ref PWM_Exported_Constants_HD_ITSource
  * @retval ���
  */

void PWM_HD_ITForce(NT_PWM_TypeDef* PWMx, uint32_t HD_ITSource)
{
    assert_param(IS_PWM_ALL_PERIPH(PWMx));
    assert_param(IS_PWM_HD_IT_SOURCE(HD_ITSource));

    PWMx->HDFRC = HD_ITSource;
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

/******************* (C) COPYRIGHT 2016 NIIET *****END OF FILE****/
