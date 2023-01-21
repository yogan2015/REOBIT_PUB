/**
  ******************************************************************************
  * @file    niietcm4_timer.h
  *
  * @brief   ���� �������� ��� ��������� ������� ��� ��������
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NIIETCM4_TIMER_H
#define __NIIETCM4_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "niietcm4.h"

/** @addtogroup Peripheral
  * @{
  */

/** @addtogroup TIMER
  * @{
  */

/** @defgroup TIMER_Exported_Types ����
  * @{
  */

/**
  * @brief  ��������� �������� ������������ �������.
  */

typedef enum
{
    TIMER_ExtInput_Disable,    /*!< ������� ������������ �� ������������. */
    TIMER_ExtInput_CountClk,   /*!< ������ ������� �� �������� ��������� �������. */
    TIMER_ExtInput_CountEn     /*!< ������ ������� �� ����������� ��������� ������� � ������ �����, ����� �� ������ "1". */
}TIMER_ExtInput_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref TIMER_ExtInput_TypeDef.
  */

#define IS_TIMER_EXT_INPUT(EXT_INPUT)  (((EXT_INPUT) == TIMER_ExtInput_Disable) || \
                                        ((EXT_INPUT) == TIMER_ExtInput_CountClk) || \
                                        ((EXT_INPUT) == TIMER_ExtInput_CountEn))

/**
 * @}
 */

/** @defgroup TIMER_Exported_Constants ���������
  * @{
  */

/**
  * @}
  */

/** @defgroup TIMER_Exported_Functions �������
  * @{
  */

/** @defgroup TIMER_Config ������������
  * @{
  */

void TIMER_Cmd(NT_TIMER_TypeDef* TIMERx, FunctionalState State);
void TIMER_PeriodConfig(NT_TIMER_TypeDef* TIMERx, uint32_t TimerClkFreq, uint32_t TimerPeriod);
void TIMER_FreqConfig(NT_TIMER_TypeDef* TIMERx, uint32_t TimerClkFreq, uint32_t TimerFreq);
void TIMER_SetReload(NT_TIMER_TypeDef* TIMERx, uint32_t ReloadVal);
uint32_t TIMER_GetReload(NT_TIMER_TypeDef* TIMERx);
void TIMER_SetCounter(NT_TIMER_TypeDef* TIMERx, uint32_t CounterVal);
uint32_t TIMER_GetCounter(NT_TIMER_TypeDef* TIMERx);
void TIMER_ExtInputConfig(NT_TIMER_TypeDef* TIMERx, TIMER_ExtInput_TypeDef TIMER_ExtInput);

/**
  * @}
  */

/** @defgroup TIMER_IT ����������
  * @{
  */

void TIMER_ITCmd(NT_TIMER_TypeDef* TIMERx, FunctionalState State);
FlagStatus TIMER_ITStatus(NT_TIMER_TypeDef* TIMERx);
void TIMER_ITStatusClear(NT_TIMER_TypeDef* TIMERx);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __NIIETCM4_TIMER_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2015 NIIET *****END OF FILE****/
