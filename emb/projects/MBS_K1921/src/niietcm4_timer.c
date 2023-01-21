/**
  ******************************************************************************
  * @file    niietcm4_timer.c
  *
  * @brief   ���� �������� ���������� ���� ������� ��� ������ � ���������
  *
  * @author  �����
  *             - ������ ������ (bkolbov), kolbov@niiet.ru
  * @date    03.12.2015
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

/** @defgroup TIMER
  * @brief ������� ��� ��������
  * @{
  */ 

/** @defgroup TIMER_Private ��������� ������
  * @{
  */

/** @defgroup TIMER_Private_Defines ��������� ���������
  * @{
  */

/**
  * @}
  */

/** @defgroup TIMER_Private_Functions ��������� �������
  * @{
  */

/**
  * @brief  ���������� ������ ���������� �������.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void TIMER_Cmd(NT_TIMER_TypeDef* TIMERx, FunctionalState State)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    TIMERx->CTRL_bit.ON = (uint32_t)State;
}

/**
  * @brief  ��������� ������� ����������� ���������� �������.
  * @attention � �������� ������������ ����� ����������� ��� ������ ����������
  *   �������� ������������ @ref TIMER_SetReload ��� � �������������� ������,
  *   ������ �� �������� ������� ����������� ������� @ref TIMER_FreqConfig.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @param  TimerClkFreq  ������� � ��, ������� ����������� ������.
  * @param  TimerPeriod   ������ ����������� ������� � ���.
  * @retval ���
  */

void TIMER_PeriodConfig(NT_TIMER_TypeDef* TIMERx, uint32_t TimerClkFreq, uint32_t TimerPeriod)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->RELOAD = TimerPeriod * (TimerClkFreq / 1000000);
}

/**
  * @brief  ��������� ������� ����������� ���������� �������.
  * @attention � �������� ������������ ����� ����������� ��� ������ ����������
  *   �������� ������������ @ref TIMER_SetReload ��� � �������������� ������,
  *   ������ �� ��������� ������� ����������� ������� @ref TIMER_PeriodConfig.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @param  TimerClkFreq  ������� � ��, ������� ����������� ������.
  * @param  TimerFreq   ������� ����������� ������� � ��.
  * @retval ���
  */

void TIMER_FreqConfig(NT_TIMER_TypeDef* TIMERx, uint32_t TimerClkFreq, uint32_t TimerFreq)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->RELOAD = TimerClkFreq / TimerFreq;
}

/**
  * @brief  ��������� �������� ������������.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @param  ReloadVal  �������� ������������.
  * @retval ���
  */

void TIMER_SetReload(NT_TIMER_TypeDef* TIMERx, uint32_t ReloadVal)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->RELOAD = ReloadVal;
}

/**
  * @brief  ��������� �������� �������� ������������.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @retval ReloadVal  �������� ������������.
  */

uint32_t TIMER_GetReload(NT_TIMER_TypeDef* TIMERx)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return TIMERx->RELOAD;
}

/**
  * @brief  ��������� �������� ��������.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @param  CounterVal  �������� ��������.
  * @retval ���
  */

void TIMER_SetCounter(NT_TIMER_TypeDef* TIMERx, uint32_t CounterVal)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->VALUE = CounterVal;
}

/**
  * @brief  ��������� �������� �������� ��������.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @retval CounterVal  �������� ��������.
  */

uint32_t TIMER_GetCounter(NT_TIMER_TypeDef* TIMERx)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    return TIMERx->VALUE;
}

/**
  * @brief  ����� ������ ������ ����� �������� ������������.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @param  TIMER_ExtInput  ����� ������ ������.
  *   �������� ��������� ����� �������� �� @ref TIMER_ExtInput_TypeDef.
  * @retval ���
  */

void TIMER_ExtInputConfig(NT_TIMER_TypeDef* TIMERx, TIMER_ExtInput_TypeDef TIMER_ExtInput)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_TIMER_EXT_INPUT(TIMER_ExtInput));

    if (TIMER_ExtInput == TIMER_ExtInput_CountEn)
    {
        TIMERx->CTRL_bit.EXTINPUT_EN = 1;
    }
    else if (TIMER_ExtInput == TIMER_ExtInput_CountClk)
    {
        TIMERx->CTRL_bit.EXTINPUT_CLK = 1;
        TIMERx->CTRL_bit.EXTINPUT_EN = 1;
    }
    else /* (TIMER_ExtInput == TIMER_ExtInput_Disable) */
    {
        TIMERx->CTRL_bit.EXTINPUT_CLK = 0;
        TIMERx->CTRL_bit.EXTINPUT_EN = 0;
    }
}

/**
  * @brief  ���������� ������ ���������� ���������� �������.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void TIMER_ITCmd(NT_TIMER_TypeDef* TIMERx, FunctionalState State)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));
    assert_param(IS_FUNCTIONAL_STATE(State));

    TIMERx->CTRL_bit.INTEN = (uint32_t)State;
}

/**
  * @brief  ������ ������� ���������� ���������� �������.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @retval Status ������ ����������.
  */

FlagStatus TIMER_ITStatus(NT_TIMER_TypeDef* TIMERx)
{
    FlagStatus Status;

    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    if (TIMERx->INTSTATUS_INTCLEAR_bit.INT)
    {
        Status = Flag_SET;
    }
    else /* (TIMERx->INTSTATUS_INTCLEAR_bit.INT) */
    {
        Status = Flag_CLEAR;
    }

    return Status;
}

/**
  * @brief  �������� ���������� ���� ���������� ���������� �������.
  * @param  TIMERx  ����� �������, ��� x ����� � ��������� 0-2.
  * @retval ���
  */

void TIMER_ITStatusClear(NT_TIMER_TypeDef* TIMERx)
{
    assert_param(IS_TIMER_ALL_PERIPH(TIMERx));

    TIMERx->INTSTATUS_INTCLEAR_bit.INT = 1;
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
