/**
  ******************************************************************************
  * @file    niietcm4_adc.h
  *
  * @brief   ���� �������� ��� ��������� ������� ��� ������ � ���, ������������,
  *          ��������� �������������.
  *
  * @author  �����
  *             - ������ ������ (bkolbov), kolbov@niiet.ru
  * @date    10.12.2015
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
#ifndef __NIIETCM4_ADC_H
#define __NIIETCM4_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "niietcm4.h"

/** @addtogroup Peripheral
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/** @defgroup ADC_Exported_Constants ���������
  * @{
  */

/** @defgroup ADC_Exported_Constants_�han ����� ������� ��� ���������
  * @{
  */
#define ADC_Channel_None          ((uint32_t)0x00000000)  /*!< ����� ADC �� ������ */
#define ADC_Channel_0             ((uint32_t)0x00000001)  /*!< ����� ADC 0 */
#define ADC_Channel_1             ((uint32_t)0x00000002)  /*!< ����� ADC 1 */
#define ADC_Channel_2             ((uint32_t)0x00000004)  /*!< ����� ADC 2 */
#define ADC_Channel_3             ((uint32_t)0x00000008)  /*!< ����� ADC 3 */
#define ADC_Channel_4             ((uint32_t)0x00000010)  /*!< ����� ADC 4 */
#define ADC_Channel_5             ((uint32_t)0x00000020)  /*!< ����� ADC 5 */
#define ADC_Channel_6             ((uint32_t)0x00000040)  /*!< ����� ADC 6 */
#define ADC_Channel_7             ((uint32_t)0x00000080)  /*!< ����� ADC 7 */
#define ADC_Channel_8             ((uint32_t)0x00000100)  /*!< ����� ADC 8 */
#define ADC_Channel_9             ((uint32_t)0x00000200)  /*!< ����� ADC 9 */
#define ADC_Channel_10            ((uint32_t)0x00000400)  /*!< ����� ADC 10 */
#define ADC_Channel_11            ((uint32_t)0x00000800)  /*!< ����� ADC 11 */
#define ADC_Channel_12            ((uint32_t)0x00001000)  /*!< ����� ADC 12 */
#define ADC_Channel_13            ((uint32_t)0x00002000)  /*!< ����� ADC 13 */
#define ADC_Channel_14            ((uint32_t)0x00004000)  /*!< ����� ADC 14 */
#define ADC_Channel_15            ((uint32_t)0x00008000)  /*!< ����� ADC 15 */
#define ADC_Channel_16            ((uint32_t)0x00010000)  /*!< ����� ADC 16 */
#define ADC_Channel_17            ((uint32_t)0x00020000)  /*!< ����� ADC 17 */
#define ADC_Channel_18            ((uint32_t)0x00040000)  /*!< ����� ADC 18 */
#define ADC_Channel_19            ((uint32_t)0x00080000)  /*!< ����� ADC 19 */
#define ADC_Channel_20            ((uint32_t)0x00100000)  /*!< ����� ADC 20 */
#define ADC_Channel_21            ((uint32_t)0x00200000)  /*!< ����� ADC 21 */
#define ADC_Channel_22            ((uint32_t)0x00400000)  /*!< ����� ADC 22 */
#define ADC_Channel_23            ((uint32_t)0x00800000)  /*!< ����� ADC 23 */
#define ADC_Channel_All           ((uint32_t)0x00FFFFFF)  /*!< ��� ������ */
/**
  * @brief ������ �������� ��������� ����� ������� � ���������� ��������.
  */

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) & (uint32_t)0xFF000000) == ((uint32_t)0x000000))

/**
  * @}
  */

/** @defgroup ADC_Exported_Constants_DC ����� ������ �������� ������������
  * @{
  */

#define ADC_DC_None     ((uint32_t)0x00000000)  /*!< �������� ���������� �� ������ */
#define ADC_DC_0        ((uint32_t)0x00000001)  /*!< �������� ���������� 0 */
#define ADC_DC_1        ((uint32_t)0x00000002)  /*!< �������� ���������� 1 */
#define ADC_DC_2        ((uint32_t)0x00000004)  /*!< �������� ���������� 2 */
#define ADC_DC_3        ((uint32_t)0x00000008)  /*!< �������� ���������� 3 */
#define ADC_DC_4        ((uint32_t)0x00000010)  /*!< �������� ���������� 4 */
#define ADC_DC_5        ((uint32_t)0x00000020)  /*!< �������� ���������� 5 */
#define ADC_DC_6        ((uint32_t)0x00000040)  /*!< �������� ���������� 6 */
#define ADC_DC_7        ((uint32_t)0x00000080)  /*!< �������� ���������� 7 */
#define ADC_DC_8        ((uint32_t)0x00000100)  /*!< �������� ���������� 8 */
#define ADC_DC_9        ((uint32_t)0x00000200)  /*!< �������� ���������� 9 */
#define ADC_DC_10       ((uint32_t)0x00000400)  /*!< �������� ���������� 10 */
#define ADC_DC_11       ((uint32_t)0x00000800)  /*!< �������� ���������� 11 */
#define ADC_DC_12       ((uint32_t)0x00001000)  /*!< �������� ���������� 12 */
#define ADC_DC_13       ((uint32_t)0x00002000)  /*!< �������� ���������� 13 */
#define ADC_DC_14       ((uint32_t)0x00004000)  /*!< �������� ���������� 14 */
#define ADC_DC_15       ((uint32_t)0x00008000)  /*!< �������� ���������� 15 */
#define ADC_DC_16       ((uint32_t)0x00010000)  /*!< �������� ���������� 16 */
#define ADC_DC_17       ((uint32_t)0x00020000)  /*!< �������� ���������� 17 */
#define ADC_DC_18       ((uint32_t)0x00040000)  /*!< �������� ���������� 18 */
#define ADC_DC_19       ((uint32_t)0x00080000)  /*!< �������� ���������� 19 */
#define ADC_DC_20       ((uint32_t)0x00100000)  /*!< �������� ���������� 20 */
#define ADC_DC_21       ((uint32_t)0x00200000)  /*!< �������� ���������� 21 */
#define ADC_DC_22       ((uint32_t)0x00400000)  /*!< �������� ���������� 22 */
#define ADC_DC_23       ((uint32_t)0x00800000)  /*!< �������� ���������� 23 */
#define ADC_DC_All      ((uint32_t)0x00FFFFFF)  /*!< ��� �������� ����������� */

/**
  * @brief ������ �������� ��������� ����� ������������ � ���������� ��������.
  */

#define IS_ADC_DC(DC) (((DC) & (uint32_t)0xFF000000) == ((uint32_t)0x000000))

/**
  * @}
  */

/** @defgroup ADC_Exported_Constants_SEQ ����� ������ �����������
  * @{
  */

#define ADC_SEQ_0        ((uint32_t)0x00000001)  /*!< ��������� 0 */
#define ADC_SEQ_1        ((uint32_t)0x00000002)  /*!< ��������� 1 */
#define ADC_SEQ_2        ((uint32_t)0x00000004)  /*!< ��������� 2 */
#define ADC_SEQ_3        ((uint32_t)0x00000008)  /*!< ��������� 3 */
#define ADC_SEQ_4        ((uint32_t)0x00000010)  /*!< ��������� 4 */
#define ADC_SEQ_5        ((uint32_t)0x00000020)  /*!< ��������� 5 */
#define ADC_SEQ_6        ((uint32_t)0x00000040)  /*!< ��������� 6 */
#define ADC_SEQ_7        ((uint32_t)0x00000080)  /*!< ��������� 7 */

/**
  * @brief ������ �������� ��������� ����� ����������� � ���������� ��������.
  */

#define IS_ADC_SEQ(SEQ) (((SEQ) != (uint32_t)0x00000000) && (((SEQ) & (uint32_t)0xFFFFFF00) == ((uint32_t)0x00)))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADC_Exported_Types ����
  * @{
  */

/**
  * @brief �������� �������� ���������� ������������ ������� ��� �����������
  *   ����� �������� ������������ ����������, �� ��������� � ���������� ��������.
  */

#define IS_ADC_SEQ_IT_RATE(IT_RATE) (((IT_RATE) > ((uint32_t)0x0)) && ((IT_RATE) < ((uint32_t)0x100)))

/**
  * @brief �������� �������� ���������� ������������ ������� ��� ����������� ����� ������� ���������� �� �������
  *   �� ��������� � ���������� ��������.
  */

#define IS_ADC_SEQ_CONVERSION_COUNT(CONVERSION_COUNT) (((CONVERSION_COUNT) > ((uint32_t)0x0)) && ((CONVERSION_COUNT) <= ((uint32_t)0x100)))

/**
  * @brief �������� �������� �������� ������� �������������� ������� ��� �� ��������� � ���������� ��������.
  */

#define IS_ADC_SEQ_CONVERSION_DELAY(CONVERSION_DELAY) ((CONVERSION_DELAY) < ((uint32_t)0x1000000))

/**
  * @brief �������� �������� �������� ������ �������������� ������� ��� ����� ������� ������ �����������
  *   �� ��������� � ���������� ��������.
  */

#define IS_ADC_PHASE(PHASE) ((PHASE) < ((uint32_t)0x1000))

/**
  * @brief �������� �������� ������ ��������� ������������ ����������� �� ��������� � ���������� ��������.
  */

#define IS_ADC_DC_THRESHOLD(THRESHOLD) ((THRESHOLD) < ((uint32_t)0x1000))

/**
  * @brief  ������� ������� �����������.
  */

typedef enum
{
    ADC_SEQ_StartEvent_SWReq   = ((uint32_t)0x0),    /*!< ������ �� ������������ �������. */
    ADC_SEQ_StartEvent_CMP0    = ((uint32_t)0x1),    /*!< ������ �� ����� ����������� ����������� 0. */
    ADC_SEQ_StartEvent_CMP1    = ((uint32_t)0x2),    /*!< ������ �� ����� ����������� ����������� 1. */
    ADC_SEQ_StartEvent_CMP2    = ((uint32_t)0x3),    /*!< ������ �� ����� ����������� ����������� 2. */
    ADC_SEQ_StartEvent_ITGPIO  = ((uint32_t)0x4),    /*!< ����� ���������� GPIO. */
    ADC_SEQ_StartEvent_TIM     = ((uint32_t)0x5),    /*!< ������ �� ����� ��������. */
    ADC_SEQ_StartEvent_PWM0    = ((uint32_t)0x6),    /*!< ������ �� ����� 0 ���. */
    ADC_SEQ_StartEvent_PWM1    = ((uint32_t)0x7),    /*!< ������ �� ����� 1 ���. */
    ADC_SEQ_StartEvent_PWM2    = ((uint32_t)0x8),    /*!< ������ �� ����� 2 ���. */
    ADC_SEQ_StartEvent_PWM3    = ((uint32_t)0x9),    /*!< ������ �� ����� 3 ���. */
    ADC_SEQ_StartEvent_PWM4    = ((uint32_t)0xA),    /*!< ������ �� ����� 4 ���. */
    ADC_SEQ_StartEvent_PWM5    = ((uint32_t)0xB),    /*!< ������ �� ����� 5 ���. */
    ADC_SEQ_StartEvent_Cycle   = ((uint32_t)0xF),    /*!< ����������� ������ ����� ����� ������� ���������� */
}ADC_SEQ_StartEvent_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_SEQ_StartEvent_TypeDef.
  */

#define IS_ADC_SEQ_START_EVENT(START_EVENT)  (((START_EVENT) == ADC_SEQ_StartEvent_SWReq)  || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_CMP0)   || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_CMP1)   || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_CMP2)   || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_ITGPIO) || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_TIM)    || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_PWM0)   || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_PWM1)   || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_PWM2)   || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_PWM3)   || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_PWM4)   || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_PWM5)   || \
                                              ((START_EVENT) == ADC_SEQ_StartEvent_Cycle))

/**
  * @brief  ���������� ���������, ������������ ��� ��������� ���������� ��������������.
  */

typedef enum
{
    ADC_Average_Disable,    /*!< ����������� �� ������������. */
    ADC_Average_2,          /*!< ���������� �� 2 ����������. */
    ADC_Average_4,          /*!< ���������� �� 4 ����������. */
    ADC_Average_8,          /*!< ���������� �� 8 ����������. */
    ADC_Average_16,         /*!< ���������� �� 16 ����������. */
    ADC_Average_32,         /*!< ���������� �� 32 ����������. */
    ADC_Average_64,         /*!< ���������� �� 64 ����������. */
}ADC_Average_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_Average_TypeDef.
  */

#define IS_ADC_AVERAGE(AVERAGE)  (((AVERAGE) == ADC_Average_Disable) || \
                                  ((AVERAGE) == ADC_Average_2)       || \
                                  ((AVERAGE) == ADC_Average_4)       || \
                                  ((AVERAGE) == ADC_Average_8)       || \
                                  ((AVERAGE) == ADC_Average_16)      || \
                                  ((AVERAGE) == ADC_Average_32)      || \
                                  ((AVERAGE) == ADC_Average_64))

/**
  * @brief  ����� ������, ������������� � ��������� �����������.
  */

typedef enum
{
    ADC_DC_Channel_0,          /*!< ��������� � ������ 0 ����� ������� �� ����������. */
    ADC_DC_Channel_1,          /*!< ��������� � ������ 1 ����� ������� �� ����������. */
    ADC_DC_Channel_2,          /*!< ��������� � ������ 2 ����� ������� �� ����������. */
    ADC_DC_Channel_3,          /*!< ��������� � ������ 3 ����� ������� �� ����������. */
    ADC_DC_Channel_4,          /*!< ��������� � ������ 4 ����� ������� �� ����������. */
    ADC_DC_Channel_5,          /*!< ��������� � ������ 5 ����� ������� �� ����������. */
    ADC_DC_Channel_6,          /*!< ��������� � ������ 6 ����� ������� �� ����������. */
    ADC_DC_Channel_7,          /*!< ��������� � ������ 7 ����� ������� �� ����������. */
    ADC_DC_Channel_8,          /*!< ��������� � ������ 8 ����� ������� �� ����������. */
    ADC_DC_Channel_9,          /*!< ��������� � ������ 9 ����� ������� �� ����������. */
    ADC_DC_Channel_10,         /*!< ��������� � ������ 10 ����� ������� �� ����������. */
    ADC_DC_Channel_11,         /*!< ��������� � ������ 11 ����� ������� �� ����������. */
    ADC_DC_Channel_12,         /*!< ��������� � ������ 12 ����� ������� �� ����������. */
    ADC_DC_Channel_13,         /*!< ��������� � ������ 13 ����� ������� �� ����������. */
    ADC_DC_Channel_14,         /*!< ��������� � ������ 14 ����� ������� �� ����������. */
    ADC_DC_Channel_15,         /*!< ��������� � ������ 15 ����� ������� �� ����������. */
    ADC_DC_Channel_16,         /*!< ��������� � ������ 16 ����� ������� �� ����������. */
    ADC_DC_Channel_17,         /*!< ��������� � ������ 17 ����� ������� �� ����������. */
    ADC_DC_Channel_18,         /*!< ��������� � ������ 18 ����� ������� �� ����������. */
    ADC_DC_Channel_19,         /*!< ��������� � ������ 19 ����� ������� �� ����������. */
    ADC_DC_Channel_20,         /*!< ��������� � ������ 20 ����� ������� �� ����������. */
    ADC_DC_Channel_21,         /*!< ��������� � ������ 21 ����� ������� �� ����������. */
    ADC_DC_Channel_22,         /*!< ��������� � ������ 22 ����� ������� �� ����������. */
    ADC_DC_Channel_23,         /*!< ��������� � ������ 23 ����� ������� �� ����������. */
    ADC_DC_Channel_None,       /*!< �� ���� �� ������� �� ��������� � �����������. */
}ADC_DC_Channel_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_DC_Channel_TypeDef.
  */

#define IS_ADC_DC_CHANNEL(CHANNEL)  (((CHANNEL) == ADC_DC_Channel_0)  || \
                                     ((CHANNEL) == ADC_DC_Channel_1)  || \
                                     ((CHANNEL) == ADC_DC_Channel_2)  || \
                                     ((CHANNEL) == ADC_DC_Channel_3)  || \
                                     ((CHANNEL) == ADC_DC_Channel_4)  || \
                                     ((CHANNEL) == ADC_DC_Channel_5)  || \
                                     ((CHANNEL) == ADC_DC_Channel_6)  || \
                                     ((CHANNEL) == ADC_DC_Channel_7)  || \
                                     ((CHANNEL) == ADC_DC_Channel_8)  || \
                                     ((CHANNEL) == ADC_DC_Channel_9)  || \
                                     ((CHANNEL) == ADC_DC_Channel_10) || \
                                     ((CHANNEL) == ADC_DC_Channel_11) || \
                                     ((CHANNEL) == ADC_DC_Channel_12) || \
                                     ((CHANNEL) == ADC_DC_Channel_13) || \
                                     ((CHANNEL) == ADC_DC_Channel_14) || \
                                     ((CHANNEL) == ADC_DC_Channel_15) || \
                                     ((CHANNEL) == ADC_DC_Channel_16) || \
                                     ((CHANNEL) == ADC_DC_Channel_17) || \
                                     ((CHANNEL) == ADC_DC_Channel_18) || \
                                     ((CHANNEL) == ADC_DC_Channel_19) || \
                                     ((CHANNEL) == ADC_DC_Channel_20) || \
                                     ((CHANNEL) == ADC_DC_Channel_21) || \
                                     ((CHANNEL) == ADC_DC_Channel_22) || \
                                     ((CHANNEL) == ADC_DC_Channel_23) || \
                                     ((CHANNEL) == ADC_DC_Channel_None))

/**
  * @brief  ����� ������������ �����������.
  */

typedef enum
{
    ADC_DC_Mode_Multiple,          /*!< ������������. */
    ADC_DC_Mode_Single,            /*!< �����������. */
    ADC_DC_Mode_MultipleHyst,      /*!< ������������ � ������������. */
    ADC_DC_Mode_SingleHyst,        /*!< ����������� � ������������. */ 
}ADC_DC_Mode_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_DC_Mode_TypeDef.
  */

#define IS_ADC_DC_MODE(MODE)  (((MODE) == ADC_DC_Mode_Single)     || \
                               ((MODE) == ADC_DC_Mode_Multiple)   || \
                               ((MODE) == ADC_DC_Mode_SingleHyst) || \
                               ((MODE) == ADC_DC_Mode_MultipleHyst))

/**
  * @brief  ������� ������������ �����������.
  */

typedef enum
{
    ADC_DC_Condition_Low    = ((uint32_t)0),    /*!< ��������� ������ ���� ����� ������ �������. */
    ADC_DC_Condition_Window = ((uint32_t)1),    /*!< ��������� ������ ���������, ����������� ���������, ���� ����� ����� �� ���. */
    ADC_DC_Condition_High   = ((uint32_t)3),    /*!< ��������� ���� ���� ����� ������� �������. */
}ADC_DC_Condition_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_DC_Condition_TypeDef.
  */

#define IS_ADC_DC_CONDITION(CONDITION)  (((CONDITION) == ADC_DC_Condition_Low)    || \
                                         ((CONDITION) == ADC_DC_Condition_Window) || \
                                         ((CONDITION) == ADC_DC_Condition_High))

/**
  * @brief  ���������� ����������� ��������� ���������� � ����� ����������, �� ���������� �������� ���������� DMA.
  */

typedef enum
{
    ADC_SEQ_FIFOLevel_1  = ((uint32_t)1),    /*!< ������ DMA ����� ���������� 1 ������ � �������. */
    ADC_SEQ_FIFOLevel_2  = ((uint32_t)2),    /*!< ������ DMA ����� ���������� 2 ����� � �������. */
    ADC_SEQ_FIFOLevel_4  = ((uint32_t)3),    /*!< ������ DMA ����� ���������� 4 ����� � �������. */
    ADC_SEQ_FIFOLevel_8  = ((uint32_t)4),    /*!< ������ DMA ����� ���������� 8 ����� � �������. */
    ADC_SEQ_FIFOLevel_16 = ((uint32_t)5),    /*!< ������ DMA ����� ���������� 16 ����� � �������. */
    ADC_SEQ_FIFOLevel_32 = ((uint32_t)6),    /*!< ������ DMA ����� ���������� 32 ����� � �������. */
}ADC_SEQ_FIFOLevel_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_SEQ_FIFOLevel_TypeDef.
  */

#define IS_ADC_SEQ_FIFO_LEVEL(FIFO_LEVEL)  (((FIFO_LEVEL) == ADC_SEQ_FIFOLevel_1)  || \
                                            ((FIFO_LEVEL) == ADC_SEQ_FIFOLevel_2)  || \
                                            ((FIFO_LEVEL) == ADC_SEQ_FIFOLevel_4)  || \
                                            ((FIFO_LEVEL) == ADC_SEQ_FIFOLevel_8)  || \
                                            ((FIFO_LEVEL) == ADC_SEQ_FIFOLevel_16) || \
                                            ((FIFO_LEVEL) == ADC_SEQ_FIFOLevel_32))

/**
  * @brief  ����� ������ ��������� �����������.
  */

typedef enum
{
    ADC_DC_Module_0,          /*!< ������ ��������� ����������� 0. */
    ADC_DC_Module_1,          /*!< ������ ��������� ����������� 1 */
    ADC_DC_Module_2,          /*!< ������ ��������� ����������� 2 */
    ADC_DC_Module_3,          /*!< ������ ��������� ����������� 3 */
    ADC_DC_Module_4,          /*!< ������ ��������� ����������� 4 */
    ADC_DC_Module_5,          /*!< ������ ��������� ����������� 5 */
    ADC_DC_Module_6,          /*!< ������ ��������� ����������� 6 */
    ADC_DC_Module_7,          /*!< ������ ��������� ����������� 7 */
    ADC_DC_Module_8,          /*!< ������ ��������� ����������� 8 */
    ADC_DC_Module_9,          /*!< ������ ��������� ����������� 9 */
    ADC_DC_Module_10,         /*!< ������ ��������� ����������� 10 */
    ADC_DC_Module_11,         /*!< ������ ��������� ����������� 11 */
    ADC_DC_Module_12,         /*!< ������ ��������� ����������� 12 */
    ADC_DC_Module_13,         /*!< ������ ��������� ����������� 13 */
    ADC_DC_Module_14,         /*!< ������ ��������� ����������� 14 */
    ADC_DC_Module_15,         /*!< ������ ��������� ����������� 15 */
    ADC_DC_Module_16,         /*!< ������ ��������� ����������� 16 */
    ADC_DC_Module_17,         /*!< ������ ��������� ����������� 17 */
    ADC_DC_Module_18,         /*!< ������ ��������� ����������� 18 */
    ADC_DC_Module_19,         /*!< ������ ��������� ����������� 19 */
    ADC_DC_Module_20,         /*!< ������ ��������� ����������� 20 */
    ADC_DC_Module_21,         /*!< ������ ��������� ����������� 21 */
    ADC_DC_Module_22,         /*!< ������ ��������� ����������� 22 */
    ADC_DC_Module_23,         /*!< ������ ��������� ����������� 23 */
}ADC_DC_Module_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_DC_Module_TypeDef.
  */

#define IS_ADC_DC_MODULE(MODULE)  (((MODULE) == ADC_DC_Module_0)  || \
                                   ((MODULE) == ADC_DC_Module_1)  || \
                                   ((MODULE) == ADC_DC_Module_2)  || \
                                   ((MODULE) == ADC_DC_Module_3)  || \
                                   ((MODULE) == ADC_DC_Module_4)  || \
                                   ((MODULE) == ADC_DC_Module_5)  || \
                                   ((MODULE) == ADC_DC_Module_6)  || \
                                   ((MODULE) == ADC_DC_Module_7)  || \
                                   ((MODULE) == ADC_DC_Module_8)  || \
                                   ((MODULE) == ADC_DC_Module_9)  || \
                                   ((MODULE) == ADC_DC_Module_10) || \
                                   ((MODULE) == ADC_DC_Module_11) || \
                                   ((MODULE) == ADC_DC_Module_12) || \
                                   ((MODULE) == ADC_DC_Module_13) || \
                                   ((MODULE) == ADC_DC_Module_14) || \
                                   ((MODULE) == ADC_DC_Module_15) || \
                                   ((MODULE) == ADC_DC_Module_16) || \
                                   ((MODULE) == ADC_DC_Module_17) || \
                                   ((MODULE) == ADC_DC_Module_18) || \
                                   ((MODULE) == ADC_DC_Module_19) || \
                                   ((MODULE) == ADC_DC_Module_20) || \
                                   ((MODULE) == ADC_DC_Module_21) || \
                                   ((MODULE) == ADC_DC_Module_22) || \
                                   ((MODULE) == ADC_DC_Module_23))

/**
  * @brief  ����� ������ ����������.
  */

typedef enum
{
    ADC_SEQ_Module_0,          /*!< �������� 0.*/
    ADC_SEQ_Module_1,          /*!< �������� 1 */
    ADC_SEQ_Module_2,          /*!< �������� 2 */
    ADC_SEQ_Module_3,          /*!< �������� 3 */
    ADC_SEQ_Module_4,          /*!< �������� 4 */
    ADC_SEQ_Module_5,          /*!< �������� 5 */
    ADC_SEQ_Module_6,          /*!< �������� 6 */
    ADC_SEQ_Module_7,          /*!< �������� 7 */
}ADC_SEQ_Module_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_SEQ_Module_TypeDef.
  */

#define IS_ADC_SEQ_MODULE(MODULE)  (((MODULE) == ADC_SEQ_Module_0)  || \
                                    ((MODULE) == ADC_SEQ_Module_1)  || \
                                    ((MODULE) == ADC_SEQ_Module_2)  || \
                                    ((MODULE) == ADC_SEQ_Module_3)  || \
                                    ((MODULE) == ADC_SEQ_Module_4)  || \
                                    ((MODULE) == ADC_SEQ_Module_5)  || \
                                    ((MODULE) == ADC_SEQ_Module_6)  || \
                                    ((MODULE) == ADC_SEQ_Module_7))

/**
  * @brief  ����� ������ ���.
  */

typedef enum
{
    ADC_Module_0,          /*!< ������ ��� 0. */
    ADC_Module_1,          /*!< ������ ��� 1 */
    ADC_Module_2,          /*!< ������ ��� 2 */
    ADC_Module_3,          /*!< ������ ��� 3 */
    ADC_Module_4,          /*!< ������ ��� 4 */
    ADC_Module_5,          /*!< ������ ��� 5 */
    ADC_Module_6,          /*!< ������ ��� 6 */
    ADC_Module_7,          /*!< ������ ��� 7 */
    ADC_Module_8,          /*!< ������ ��� 8 */
    ADC_Module_9,          /*!< ������ ��� 9 */
    ADC_Module_10,         /*!< ������ ��� 10 */
    ADC_Module_11,         /*!< ������ ��� 11 */
}ADC_Module_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_Module_TypeDef.
  */

#define IS_ADC_MODULE(MODULE)  (((MODULE) == ADC_Module_0)  || \
                                ((MODULE) == ADC_Module_1)  || \
                                ((MODULE) == ADC_Module_2)  || \
                                ((MODULE) == ADC_Module_3)  || \
                                ((MODULE) == ADC_Module_4)  || \
                                ((MODULE) == ADC_Module_5)  || \
                                ((MODULE) == ADC_Module_6)  || \
                                ((MODULE) == ADC_Module_7)  || \
                                ((MODULE) == ADC_Module_8)  || \
                                ((MODULE) == ADC_Module_9)  || \
                                ((MODULE) == ADC_Module_10) || \
                                ((MODULE) == ADC_Module_11))

/**
  * @brief  ����� ����������� ������ ���.
  */

typedef enum
{
    ADC_Resolution_12bit,          /*!< ����������� ������ 12 ���. */
    ADC_Resolution_10bit,          /*!< ����������� ������ 10 ��� */
}ADC_Resolution_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_Resolution_TypeDef.
  */

#define IS_ADC_RESOLUTION(RESOLUTION)  (((RESOLUTION) == ADC_Resolution_12bit) || \
                                        ((RESOLUTION) == ADC_Resolution_10bit))

/**
  * @brief  ����� ������ ������ ���.
  */

typedef enum
{
    ADC_Measure_Single,         /*!< ������������ ����� ��������� �� ������. */
    ADC_Measure_Diff,           /*!< ���������������� ����� � ��������������� �������. */
}ADC_Measure_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_Measure_TypeDef.
  */

#define IS_ADC_MEASURE(MEASURE)  (((MEASURE) == ADC_Measure_Single) || \
                                  ((MEASURE) == ADC_Measure_Diff))

/**
  * @brief  ����� ������ ������ ���.
  */

typedef enum
{
    ADC_Mode_Powerdown = ((uint32_t)0),     /*!< ������ ��������. */
    ADC_Mode_StandBy   = ((uint32_t)1),     /*!< ����� ��������. */
    ADC_Mode_Active    = ((uint32_t)3),     /*!< ������ �������. */
}ADC_Mode_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref ADC_Mode_TypeDef.
  */

#define IS_ADC_MODE(MODE)  (((MODE) == ADC_Mode_Powerdown) || \
                            ((MODE) == ADC_Mode_StandBy) || \
                            ((MODE) == ADC_Mode_Active))

/**
  * @brief  ��������� ������������� ������� ���
  * @attention ������ ������������� ��� ������ � ���������������� ����� (��������� @ref ADC_Measure_A � @ref ADC_Measure_B).
  */

typedef struct
{
    ADC_Resolution_TypeDef ADC_Resolution;  /*!< ���������� ����������� ������ ���.
                                                �������� ����� ��������� ����� �������� �� @ref ADC_Resolution_TypeDef. */
    ADC_Measure_TypeDef ADC_Measure_A;      /*!< ���������� ����� ��������� �� ������ A: ������������ � ���������������� (A-B).
                                                �������� ����� ��������� ����� �������� �� @ref ADC_Measure_TypeDef. */
    ADC_Measure_TypeDef ADC_Measure_B;      /*!< ���������� ����� ��������� �� ������ B: ������������ � ���������������� (B-A).
                                                �������� ����� ��������� ����� �������� �� @ref ADC_Measure_TypeDef. */
    uint32_t ADC_Phase;                     /*!< ������� �������� ������ �������������� ������� ��� ����� ������� ������ �����������.
                                                �������� ����� ��������� ����� �������� �� ��������� 0 - 4095. */
    ADC_Average_TypeDef ADC_Average;        /*!< ���������� ���������, ������������ ��� ��������� ���������� ��������������.
                                                �������� ����� ��������� ����� �������� �� @ref ADC_Average_TypeDef. */
    ADC_Mode_TypeDef ADC_Mode;              /*!< ���������� ����� ������ ������ ���.
                                                �������� ����� ��������� ����� �������� �� @ref ADC_Mode_TypeDef. */
}ADC_Init_TypeDef;

/**
  * @brief  ��������� ������������� �������� ������������.
  * @attention
  *   - ������� ������������ �� ��������� � �������� �� �������� � �������������� �������� ������.
  *   - ������ ������ ���������� ������� ADC_DC_ThresholdLow <= ADC_DC_ThresholdHigh.
  */

typedef struct
{
    uint32_t ADC_DC_ThresholdLow;               /*!< ������ ����� ������������ �����������.
                                                    �������� ����� ��������� ����� �������� �� ��������� 0 - 4095. */
    uint32_t ADC_DC_ThresholdHigh;              /*!< ������� ����� ������������ �����������.
                                                    �������� ����� ��������� ����� �������� �� ��������� 0 - 4095. */
    ADC_DC_Channel_TypeDef ADC_DC_Channel;      /*!< �������� �����, ��������� ��������� �������� ����� ������� �� ����������.
                                                    �������� ����� ��������� ����� �������� �� @ref ADC_DC_Channel_TypeDef. */
    ADC_DC_Mode_TypeDef ADC_DC_Mode;            /*!< �������� ����� ������������ �����������.
                                                    �������� ����� ��������� ����� �������� �� @ref ADC_DC_Mode_TypeDef. */
    ADC_DC_Condition_TypeDef ADC_DC_Condition;  /*!< �������� ������� ������������ �����������.
                                                    �������� ����� ��������� ����� �������� �� @ref ADC_DC_Condition_TypeDef. */
}ADC_DC_Init_TypeDef;

/**
  * @brief  ��������� ������������� �����������.
  */

typedef struct
{
    ADC_SEQ_StartEvent_TypeDef ADC_SEQ_StartEvent;  /*!< ���������� c������ ������� ����������.
                                                        �������� ����� ��������� ����� �������� �� @ref ADC_SEQ_StartEvent_TypeDef. */
    FunctionalState ADC_SEQ_SWReqEn;                /*!< ��������� ���������� ����������� �� ������������ �������.
                                                        �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    uint32_t ADC_Channels;                          /*!< ����� ������� ��� ���������.
                                                        �������� ����� ��������� ����� ������������ �������� �� @ref ADC_Exported_Constants_�han. */
    uint32_t ADC_SEQ_ConversionCount;               /*!< ������� ���������� ������������ ������� ��� ����������� ����� ��� ������� �� �������.
                                                        �������� ����� ��������� ����� �������� �� ��������� 1 - 256. */
    uint32_t ADC_SEQ_ConversionDelay;               /*!< ������� �������� ������� ������ ���.
                                                        �������� ����� ��������� ����� �������� �� ��������� 0x00000000 - 0x00FFFFFF. */
    uint32_t ADC_SEQ_DC;                            /*!< ���������� ������ ��������� ����������� �����������.
                                                        �������� ����� ��������� ����� ������������ �������� �� @ref ADC_Exported_Constants_DC. */
}ADC_SEQ_Init_TypeDef;

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions �������
  * @{
  */

/** @defgroup ADC_Exported_Functions_Init ������������
  * @{
  */

/** @defgroup ADC_Exported_Functions_Init_ADC ������ ���
  * @{
  */

void ADC_DeInit(ADC_Module_TypeDef ADC_Module);
void ADC_Init(ADC_Module_TypeDef ADC_Module, ADC_Init_TypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_Init_TypeDef* ADC_InitStruct);

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Init_DC �������� �����������
  * @{
  */


void ADC_DC_DeInit(ADC_DC_Module_TypeDef ADC_DC_Module);
void ADC_DC_Init(ADC_DC_Module_TypeDef ADC_DC_Module, ADC_DC_Init_TypeDef* ADC_DC_InitStruct);
void ADC_DC_StructInit(ADC_DC_Init_TypeDef* ADC_DC_InitStruct);

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Init_SEQ ����������
  * @{
  */

void ADC_SEQ_DeInit(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
void ADC_SEQ_Init(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, ADC_SEQ_Init_TypeDef* ADC_SEQ_InitStruct);
void ADC_SEQ_StructInit(ADC_SEQ_Init_TypeDef* ADC_SEQ_InitStruct);

/**
  * @}
  */

/**
  * @}
  */

void ADC_Cmd(ADC_Module_TypeDef ADC_Module, FunctionalState State);
void ADC_SEQ_Cmd(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, FunctionalState State);
void ADC_SEQ_SWReq();
uint32_t ADC_SEQ_GetFIFOData(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
uint32_t ADC_SEQ_GetConversionCount(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
uint32_t ADC_SEQ_GetFIFOLoad(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
FlagStatus ADC_SEQ_FIFOFullStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
void ADC_SEQ_FIFOFullStatusClear(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
FlagStatus ADC_SEQ_FIFOEmptyStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
void ADC_SEQ_FIFOEmptyStatusClear(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);

void ADC_DC_Cmd(ADC_DC_Module_TypeDef ADC_DC_Module, FunctionalState State);
FlagStatus ADC_DC_TrigStatus(ADC_DC_Module_TypeDef ADC_DC_Module);
void ADC_DC_TrigStatusClear(ADC_DC_Module_TypeDef ADC_DC_Module);
uint32_t ADC_DC_GetLastData(ADC_DC_Module_TypeDef ADC_DC_Module);

/** @defgroup ADC_Exported_Functions_DMA ������������ ����������� ��� DMA
  * @{
  */

void ADC_SEQ_DMAConfig(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, ADC_SEQ_FIFOLevel_TypeDef ADC_SEQ_FIFOLevel);
void ADC_SEQ_DMACmd(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, FunctionalState State);
FlagStatus ADC_SEQ_DMAErrorStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
void ADC_SEQ_DMAErrorStatusClear(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Int ������������ ����������
  * @{
  */

/** @defgroup ADC_Exported_Functions_Int_DC �������� �����������
  * @{
  */

void ADC_DC_ITCmd(ADC_DC_Module_TypeDef ADC_DC_Module, FunctionalState State);
void ADC_DC_ITConfig(ADC_DC_Module_TypeDef ADC_DC_Module, ADC_DC_Mode_TypeDef ADC_DC_Mode, ADC_DC_Condition_TypeDef ADC_DC_Condition);
void ADC_DC_ITGenCmd(ADC_DC_Module_TypeDef ADC_DC_Module, FunctionalState State);
void ADC_DC_ITMaskCmd(ADC_DC_Module_TypeDef ADC_DC_Module, FunctionalState State);
FlagStatus ADC_DC_ITRawStatus(ADC_DC_Module_TypeDef ADC_DC_Module);
FlagStatus ADC_DC_ITMaskedStatus(ADC_DC_Module_TypeDef ADC_DC_Module);
void ADC_DC_ITStatusClear(ADC_DC_Module_TypeDef ADC_DC_Module);

/**
  * @}
  */

/** @defgroup ADC_Exported_Functions_Int_SEQ ����������
  * @{
  */

void ADC_SEQ_ITCmd(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, FunctionalState State);
void ADC_SEQ_ITConfig(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, uint32_t ADC_SEQ_ITRate, FunctionalState ADC_SEQ_ITCountSEQRst);
uint32_t ADC_SEQ_GetITCount(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
void ADC_SEQ_ITCountRst(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
FlagStatus ADC_SEQ_ITRawStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
FlagStatus ADC_SEQ_ITMaskedStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);
void ADC_SEQ_ITStatusClear(ADC_SEQ_Module_TypeDef ADC_SEQ_Module);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __NIIETCM4_ADC_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2015 NIIET *****END OF FILE****/
