/**
  ******************************************************************************
  * @file    niietcm4_gpio.h
  *
  * @brief   ���� �������� ��� ��������� ������� ��� GPIO
  *
  * @author  �����
  *             - ������ ������ (bkolbov), kolbov@niiet.ru
  * @date    26.10.2015
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
#ifndef __NIIETCM4_GPIO_H
#define __NIIETCM4_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "niietcm4.h"

/** @addtogroup Peripheral
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Types ����
  * @{
  */

/**
   * @brief ������ �������� ����������� �������� ������� ���������� ������������ ���������.
   */

#define IS_GPIO_QUAL_PERIOD(PERIOD) (((PERIOD) & ((uint32_t)0xFFFFFF00)) == ((uint32_t)0x00))

/**
  * @brief  ���, ������������ ��������� ����.
  */

typedef enum
{
    Bit_CLEAR = 0,    /*!< ��� ������. */
    Bit_SET           /*!< ��� ����������. */
}BitAction;

/**
  * @brief ������ �������� ���������� ���� @ref BitAction.
  */

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_CLEAR) || ((ACTION) == Bit_SET))

/**
  * @brief  ����� ����������� ������ ����.
  */

typedef enum
{
    GPIO_Dir_In,         /*!< ��� �������� �� ����. */
    GPIO_Dir_Out         /*!< ��� �������� �� �����. */
}GPIO_Dir_TypeDef;

/**
   * @brief ������ �������� ���������� ���� @ref GPIO_Dir_TypeDef.
   */

#define IS_GPIO_DIR(DIR) (((DIR) == GPIO_Dir_In) || \
                           ((DIR) == GPIO_Dir_Out))

/**
  * @brief  ����� ������ ������ ����.
  */

typedef enum
{
    GPIO_Mode_IO,        /*!< ��� � ������ �����-������. */
    GPIO_Mode_AltFunc    /*!< ��� � ������ �������������� �������. */
}GPIO_Mode_TypeDef;

/**
   * @brief ������ �������� ���������� ���� @ref GPIO_Mode_TypeDef.
   */

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IO) || \
                            ((MODE) == GPIO_Mode_AltFunc))

/**
  * @brief  ����� ������� ��� ������������� ����������.
  */

typedef enum
{
    GPIO_IntType_Level,  /*!< ���������� �� ������. */
    GPIO_IntType_Edge    /*!< ���������� �� ��������. */
}GPIO_IntType_TypeDef;

/**
   * @brief ������ �������� ���������� ���� @ref GPIO_IntType_TypeDef.
   */

#define IS_GPIO_INT_TYPE(INT_TYPE) (((INT_TYPE) == GPIO_IntType_Level) || \
                                    ((INT_TYPE) == GPIO_IntType_Edge))

/**
  * @brief  ����� ���������� ������� ��� ������������� ����������.
  */

typedef enum
{
    GPIO_IntPol_Neg,     /*!< ���������� �� ������� ������ ��� �������������� ������. */
    GPIO_IntPol_Pos      /*!< ���������� �� �������� ������ ��� �������������� ������. */
}GPIO_IntPol_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref GPIO_IntPol_TypeDef.
  */

#define IS_GPIO_INT_POL(INT_POL) (((INT_POL) == GPIO_IntPol_Neg) || \
                                  ((INT_POL) == GPIO_IntPol_Pos))

/**
  * @brief  ��������� ������ ����.
  */

typedef enum
{
    GPIO_Out_Dis,        /*!< ��� � ������� ���������. */
    GPIO_Out_En          /*!< ��� �������� ��� �����. */
}GPIO_Out_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref GPIO_Out_TypeDef.
  */

#define IS_GPIO_OUT(OUT) (((OUT) == GPIO_Out_Dis) || \
                          ((OUT) == GPIO_Out_En))

/**
  * @brief  ����� ������������ ����������� ����������� ����.
  */

typedef enum
{
    GPIO_Load_8mA,        /*!< ������������ ��� 8��. */
    GPIO_Load_16mA        /*!< ������������ ��� 16��. */
}GPIO_Load_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref GPIO_Load_TypeDef.
  */

#define IS_GPIO_LOAD(LOAD) (((LOAD) == GPIO_Load_8mA) || \
                            ((LOAD) == GPIO_Load_16mA))

/**
  * @brief  ����� ������ ������ �������� ��������.
  */

typedef enum
{
    GPIO_OutMode_PP,    /*!< ����� ���-����. */
    GPIO_OutMode_OD     /*!< ����� ��������� ����������. */
}GPIO_OutMode_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref GPIO_OutMode_TypeDef.
  */

#define IS_GPIO_OUT_MODE(OUT_MODE) (((OUT_MODE) == GPIO_OutMode_PP) || \
                                    ((OUT_MODE) == GPIO_OutMode_OD))

/**
  * @brief  ��������� �������� � �������.
  */

typedef enum
{
    GPIO_PullUp_Dis,     /*!< ���������� �������� � ������� ���������. */
    GPIO_PullUp_En       /*!< ���������� �������� � ������� ��������. */
}GPIO_PullUp_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref GPIO_PullUp_TypeDef.
  */

#define IS_GPIO_PULLUP(PULLUP)  (((PULLUP) == GPIO_PullUp_Dis) || \
                                 ((PULLUP) == GPIO_PullUp_En))

/**
  * @brief  ��������� ������ ����������������� ������ ����� 2 ��������-�������.
  */

typedef enum
{
    GPIO_Sync_Dis,       /*!< ����������������� ����� ���������. */
    GPIO_Sync_En         /*!< ����������������� ����� ��������. */
}GPIO_Sync_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref GPIO_Sync_TypeDef.
  */

#define IS_GPIO_SYNC(SYNC) (((SYNC) == GPIO_Sync_Dis) || \
                            ((SYNC) == GPIO_Sync_En))

/**
  * @brief  ��������� �������� �������.
  */

typedef enum
{
    GPIO_Qual_Dis,       /*!< ������� ������ ��������. */
    GPIO_Qual_En         /*!< ������� ������ �������. */
}GPIO_Qual_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref GPIO_Qual_TypeDef.
  */

#define IS_GPIO_QUAL(QUAL) (((QUAL) == GPIO_Qual_Dis) || \
                            ((QUAL) == GPIO_Qual_En))

/**
  * @brief  ����� ������ ������ �������� �������.
  */

typedef enum
{
    GPIO_QualMode_3sample,  /*!< ������������ 3 ������� ��� ����������. */
    GPIO_QualMode_6sample   /*!< ������������ 6 �������� ��� ����������. */
}GPIO_QualMode_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref GPIO_QualMode_TypeDef.
  */

#define IS_GPIO_QUAL_MODE(QUAL_MODE) (((QUAL_MODE) == GPIO_QualMode_3sample) || \
                                       ((QUAL_MODE) == GPIO_QualMode_6sample))

/**
  * @brief  ����� ������ �������������� ������� ����.
  */

typedef enum
{
    GPIO_AltFunc_1,     /*!< �������������� ������� 1. */
    GPIO_AltFunc_2,     /*!< �������������� ������� 2. */
    GPIO_AltFunc_3      /*!< �������������� ������� 3. */
}GPIO_AltFunc_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref GPIO_AltFunc_TypeDef.
  */

#define IS_GPIO_ALT_FUNC(ALT_FUNC) (((ALT_FUNC) == GPIO_AltFunc_1) || \
                                    ((ALT_FUNC) == GPIO_AltFunc_2) || \
                                    ((ALT_FUNC) == GPIO_AltFunc_3))

/**
  * @brief  ��������� ������������� GPIO
  */

typedef struct
{
    uint32_t GPIO_Pin;                    /*!< ���������� ����, ������� ����� ���������.
                                               �������� ����� ��������� ����� �������� �� @ref GPIO_pins_define. */
    GPIO_Dir_TypeDef GPIO_Dir;             /*!< ����������� ����������� ������ ��������� �����.
                                               �������� ����� ��������� ����� �������� �� @ref GPIO_Dir_TypeDef. */
    GPIO_Out_TypeDef GPIO_Out;             /*!< ���������� ��������� ������ ��������� �����.
                                               �������� ����� ��������� ����� �������� �� @ref GPIO_Out_TypeDef. */
    GPIO_Mode_TypeDef GPIO_Mode;           /*!< ���������� ����� ������ ��������� �����.
                                               �������� ����� ��������� ����� �������� �� @ref GPIO_Mode_TypeDef. */
    GPIO_AltFunc_TypeDef GPIO_AltFunc;    /*!< ���������� ����� �������������� ������� ��������� �����.
                                               �������� ����� ��������� ����� �������� �� @ref GPIO_AltFunc_TypeDef. */
    GPIO_Load_TypeDef GPIO_Load;           /*!< ���������� ����������� �������� ��������� �����.
                                               �������� ����� ��������� ����� �������� �� @ref GPIO_Load_TypeDef. */
    GPIO_OutMode_TypeDef GPIO_OutMode;    /*!< ���������� ����� ������ �������� �������� ��������� �����.
                                               �������� ����� ��������� ����� �������� �� @ref GPIO_OutMode_TypeDef. */
    GPIO_PullUp_TypeDef GPIO_PullUp;       /*!< ���������� ��������� ���������� �������� � ������� ��������� �����.
                                               �������� ����� ��������� ����� �������� �� @ref GPIO_PullUp_TypeDef. */
}GPIO_Init_TypeDef;

/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants ���������
  * @{
  */

/** @defgroup GPIO_pins_define ����� �����
  * @{
  */

#define GPIO_Pin_0                 ((uint32_t)0x0001)  /*!< ��� 0 ������. */
#define GPIO_Pin_1                 ((uint32_t)0x0002)  /*!< ��� 1 ������. */
#define GPIO_Pin_2                 ((uint32_t)0x0004)  /*!< ��� 2 ������. */
#define GPIO_Pin_3                 ((uint32_t)0x0008)  /*!< ��� 3 ������. */
#define GPIO_Pin_4                 ((uint32_t)0x0010)  /*!< ��� 4 ������. */
#define GPIO_Pin_5                 ((uint32_t)0x0020)  /*!< ��� 5 ������. */
#define GPIO_Pin_6                 ((uint32_t)0x0040)  /*!< ��� 6 ������. */
#define GPIO_Pin_7                 ((uint32_t)0x0080)  /*!< ��� 7 ������. */
#define GPIO_Pin_8                 ((uint32_t)0x0100)  /*!< ��� 8 ������. */
#define GPIO_Pin_9                 ((uint32_t)0x0200)  /*!< ��� 9 ������. */
#define GPIO_Pin_10                ((uint32_t)0x0400)  /*!< ��� 10 ������. */
#define GPIO_Pin_11                ((uint32_t)0x0800)  /*!< ��� 11 ������. */
#define GPIO_Pin_12                ((uint32_t)0x1000)  /*!< ��� 12 ������. */
#define GPIO_Pin_13                ((uint32_t)0x2000)  /*!< ��� 13 ������. */
#define GPIO_Pin_14                ((uint32_t)0x4000)  /*!< ��� 14 ������. */
#define GPIO_Pin_15                ((uint32_t)0x8000)  /*!< ��� 15 ������. */
#define GPIO_Pin_0_3               ((uint32_t)0x000F)  /*!< ���� 0-3 �������. */
#define GPIO_Pin_3_0               GPIO_Pin_0_3        /*!< ���� 3-0 �������. */
#define GPIO_Pin_4_7               ((uint32_t)0x00F0)  /*!< ���� 4-7 �������. */
#define GPIO_Pin_7_4               GPIO_Pin_4_7        /*!< ���� 7-4 �������. */
#define GPIO_Pin_8_11              ((uint32_t)0x0F00)  /*!< ���� 8-11 �������. */
#define GPIO_Pin_11_8              GPIO_Pin_8_11       /*!< ���� 11-8 �������. */
#define GPIO_Pin_12_15             ((uint32_t)0xF000)  /*!< ���� 12-15 �������. */
#define GPIO_Pin_15_12             GPIO_Pin_12_15      /*!< ���� 15-12 �������. */
#define GPIO_Pin_0_7               ((uint32_t)0x00FF)  /*!< ���� 0-7 �������. */
#define GPIO_Pin_7_0               GPIO_Pin_0_7        /*!< ���� 7-0 �������. */
#define GPIO_Pin_8_15              ((uint32_t)0xFF00)  /*!< ���� 8-15 �������. */
#define GPIO_Pin_15_8              GPIO_Pin_8_15       /*!< ���� 15-8 �������. */
#define GPIO_Pin_All               ((uint32_t)0xFFFF)  /*!< ��� ���� �������. */

/**
  * @brief ������ �������� ������� ����� �� ��������� � ���������� ��������.
  */

#define IS_GPIO_PIN(PIN) (((PIN) != (uint32_t)0x0000) && (((PIN) & (uint32_t)0xFFFF0000) == ((uint32_t)0x0000)))


/**
  * @brief ������ �������� ������ ���� ��� ������ � ������ �� �����������.
  */

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions �������
  * @{
  */

/** @defgroup GPIO_Init_Deinit ������������� � ���������������
  * @{
  */

void GPIO_DeInit(NT_GPIO_TypeDef* GPIOx);
void GPIO_Init(NT_GPIO_TypeDef* GPIOx, GPIO_Init_TypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_Init_TypeDef* GPIO_InitStruct);

/**
  * @}
  */

/** @defgroup GPIO_Config ������������
  * @{
  */

void GPIO_AltFuncConfig(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIO_AltFunc_TypeDef GPIO_AltFunc);

/**
  * @}
  */

/** @defgroup GPIO_Read_Write ������ � ������
  * @{
  */

/** @defgroup GPIO_Read ������
  * @{
  */

uint32_t GPIO_ReadBit(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
uint32_t GPIO_Read(NT_GPIO_TypeDef* GPIOx);
uint32_t GPIO_ReadMask(NT_GPIO_TypeDef* GPIOx, uint32_t MaskVal);

/**
  * @}
  */

/** @defgroup GPIO_Write ������
  * @{
  */

void GPIO_WriteBit(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(NT_GPIO_TypeDef* GPIOx, uint32_t PortVal);
void GPIO_WriteMask(NT_GPIO_TypeDef* GPIOx, uint32_t MaskVal, uint32_t PortVal);

/**
  * @}
  */

/** @defgroup GPIO_Bit_Operations ������� ��������
  * @{
  */

void GPIO_SetBits(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void GPIO_ClearBits(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void GPIO_ToggleBits(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIO_Qualifier ����������
  * @{
  */

void GPIO_QualConfig(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIO_QualMode_TypeDef Mode, uint32_t SamplePerod);
void GPIO_QualCmd(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState State);
void GPIO_SyncCmd(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState State);

/**
  * @}
  */

/** @defgroup GPIO_Interrupts ����������
  * @{
  */

void GPIO_ITConfig(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIO_IntType_TypeDef IntType, GPIO_IntPol_TypeDef IntPol);
void GPIO_ITCmd(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState State);
void GPIO_ITStatusClear(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
FlagStatus GPIO_ITStatus(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __NIIETCM4_GPIO_H */

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
