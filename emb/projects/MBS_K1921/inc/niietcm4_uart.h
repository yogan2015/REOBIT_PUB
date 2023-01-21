/**
  ******************************************************************************
  * @file    niietcm4_uart.h
  *
  * @brief   ���� �������� ��� ��������� ������� ��� UART
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NIIETCM4_UART_H
#define __NIIETCM4_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#ifndef RELPATH
  #include "niietcm4.h"
#endif
/** @addtogroup Peripheral
  * @{
  */

/** @addtogroup UART
  * @{
  */

/** @defgroup UART_Exported_Types ����
  * @{
  */

/**
  * @brief ������ �������� ����������� �������� ����� ����� �������� baudrate UART ���������.
  */

#define IS_UART_INT_DIV(INT_DIV) (((INT_DIV) > ((uint32_t)0x0)) && ((INT_DIV) < ((uint32_t)0x10000)))

/**
  * @brief ������ �������� ����������� �������� ������� ����� �������� baudrate UART ���������.
  */

#define IS_UART_FRAC_DIV(FRAC_DIV) ((FRAC_DIV) < ((uint32_t)0x40))

/**
  * @brief ������ �������� ������������ ������������ ������.
  */

#define IS_UART_DATA(DATA) ((DATA) < ((uint32_t)0x100))

/**
  * @brief  ����������� �������� UART.
  */

typedef enum
{
    UART_Dir_Rx,        /*!< ��������. */
    UART_Dir_Tx         /*!< �����. */
}UART_Dir_Typedef;

/**
  * @brief ������ �������� ���������� ���� @ref UART_Dir_Typedef.
  */

#define IS_UART_DIR(DIR)  (((DIR) == UART_Dir_Rx) || \
                           ((DIR) == UART_Dir_Tx))

/**
  * @brief  ����� ������ �������� ��������� ����.
  */

typedef enum
{
    UART_StopBit_1,        /*!< ���� �������� ���. */
    UART_StopBit_2         /*!< ��� �������� ����. */
}UART_StopBit_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref UART_StopBit_TypeDef.
  */

#define IS_UART_STOP_BIT(STOP_BIT)  (((STOP_BIT) == UART_StopBit_1) || \
                                     ((STOP_BIT) == UART_StopBit_2))

/**
  * @brief  ����� ������ ���� ��������.
  */

typedef enum
{
    UART_ParityBit_Disable,     /*!< �� ����������, �� �����������. */
    UART_ParityBit_Odd,         /*!< �������� ���������� ������. */
    UART_ParityBit_Even,        /*!< �������� �������� ������. */
    UART_ParityBit_High,        /*!< ��� �������� ��������� ����� �������. */
    UART_ParityBit_Low          /*!< ��� �������� ��������� ����� ����. */
}UART_ParityBit_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref UART_ParityBit_TypeDef.
  */

#define IS_UART_PARITY_BIT(PARITY_BIT)  (((PARITY_BIT) == UART_ParityBit_Disable) || \
                                         ((PARITY_BIT) == UART_ParityBit_Odd) || \
                                         ((PARITY_BIT) == UART_ParityBit_Even) || \
                                         ((PARITY_BIT) == UART_ParityBit_High) || \
                                         ((PARITY_BIT) == UART_ParityBit_Low))

/**
  * @brief  ���������� ������������/����������� �������������� ���.
  */

typedef enum
{
    UART_DataWidth_5,       /*!< ����� ��������������� ����� 5 ���. */
    UART_DataWidth_6,       /*!< ����� ��������������� ����� 6 ���. */
    UART_DataWidth_7,       /*!< ����� ��������������� ����� 7 ���. */
    UART_DataWidth_8        /*!< ����� ��������������� ����� 8 ���. */
}UART_DataWidth_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref UART_DataWidth_TypeDef.
  */

#define IS_UART_DATA_WIDTH(DATA_WIDTH)  (((DATA_WIDTH) == UART_DataWidth_5) || \
                                         ((DATA_WIDTH) == UART_DataWidth_6) || \
                                         ((DATA_WIDTH) == UART_DataWidth_7) || \
                                         ((DATA_WIDTH) == UART_DataWidth_8))

/**
  * @brief  ����� ���������� ������ ���������/�����������, �� ���������� ��������
  *   ����� �������������� ����������
  */

typedef enum
{
    UART_FIFOLevel_1_8,     /*!< ���������� FIFO �� 1/8. */
    UART_FIFOLevel_1_4,     /*!< ���������� FIFO �� 1/4. */
    UART_FIFOLevel_1_2,     /*!< ���������� FIFO �� 1/2. */
    UART_FIFOLevel_3_4,     /*!< ���������� FIFO �� 3/4. */
    UART_FIFOLevel_7_8      /*!< ���������� FIFO �� 7/8. */
}UART_FIFOLevel_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref UART_FIFOLevel_TypeDef.
  */

#define IS_UART_FIFO_LEVEL(FIFO_LEVEL)  (((FIFO_LEVEL) == UART_FIFOLevel_1_8) || \
                                         ((FIFO_LEVEL) == UART_FIFOLevel_1_4) || \
                                         ((FIFO_LEVEL) == UART_FIFOLevel_1_2) || \
                                         ((FIFO_LEVEL) == UART_FIFOLevel_3_4) || \
                                         ((FIFO_LEVEL) == UART_FIFOLevel_7_8))

/**
  * @brief  ��������� ������������� ��������� ������.
  */

typedef struct
{
    FunctionalState UART_InvDTR;           /*!< ���������� ��������� ������� �� ����� ��������� ������ DTR. ����������� �������� �������� ������� ������� �������.
                                               �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    FunctionalState UART_InvRTS;           /*!< ���������� ��������� ������� �� ����� ��������� ������ RTS. ����������� �������� �������� ������� ������� �������.
                                               �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    FunctionalState UART_RTSEn;            /*!< ���������� ����������� ���������� ������� ������ �� ����� RTS.
                                               �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    FunctionalState UART_CTSEn;            /*!< ���������� ����������� ���������� ������� ������ �� ����� CTS.
                                               �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
}UART_ModemInit_TypeDef;

/**
  * @brief  ��������� ������������� UART.
  */

typedef struct
{
    UART_StopBit_TypeDef UART_StopBit;          /*!< ����� ������ �������� ��������� ����.
                                                    �������� ����� ��������� ����� �������� �� @ref UART_StopBit_TypeDef. */
    UART_ParityBit_TypeDef UART_ParityBit;      /*!< ����� ������ ���� ��������.
                                                    �������� ����� ��������� ����� �������� �� @ref UART_ParityBit_TypeDef. */
    UART_DataWidth_TypeDef UART_DataWidth;      /*!< ���������� ������������/����������� �������������� ���.
                                                    �������� ����� ��������� ����� �������� �� @ref UART_DataWidth_TypeDef. */
    uint32_t UART_ClkFreq;                      /*!< �������� ������� ������� � ��, ����������� � ����� UART */
    uint32_t UART_BaudRate;                     /*!< �������� �������� �������� ������ � ���/�
                                                    ������������ �������� 921600 */
    UART_FIFOLevel_TypeDef UART_FIFOLevelRx;    /*!< ����� ���������� ������� ��������� ��� ������������.
                                                    �������� ����� ��������� ����� �������� �� @ref UART_FIFOLevel_TypeDef. */
    UART_FIFOLevel_TypeDef UART_FIFOLevelTx;    /*!< ����� ���������� ������� ����������� ��� ������������.
                                                    �������� ����� ��������� ����� �������� �� @ref UART_FIFOLevel_TypeDef. */
    FunctionalState UART_FIFOEn;                /*!< ���������� ������ FIFO ������ ��������� � �����������.
                                                    �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    FunctionalState UART_RxEn;                  /*!< ���������� ������.
                                                    �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    FunctionalState UART_TxEn;                  /*!< ���������� ��������.
                                                    �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
}UART_Init_TypeDef;

/**
 * @}
 */

/** @defgroup UART_Exported_Constants ���������
  * @{
  */

/** @defgroup UART_Exported_Constants_ITSource ��������� ���������� UART
  * @{
  */

#define UART_ITSource_ChangeRI          ((uint32_t)0x00000001)      /*!< ��������� ��������� ����� UART_RI */
#define UART_ITSource_ChangeCTS         ((uint32_t)0x00000002)      /*!< ��������� ��������� ����� UART_CTS */
#define UART_ITSource_ChangeDCD         ((uint32_t)0x00000004)      /*!< ��������� ��������� ����� UART_DCD */
#define UART_ITSource_ChangeDSR         ((uint32_t)0x00000008)      /*!< ��������� ��������� ����� UART_DSR */
#define UART_ITSource_RxFIFOLevel       ((uint32_t)0x00000010)      /*!< ����� ������������ ������ ��������� */
#define UART_ITSource_TxFIFOLevel       ((uint32_t)0x00000020)      /*!< ����� ����������� ������ ����������� */
#define UART_ITSource_RecieveTimeout    ((uint32_t)0x00000040)      /*!< ������� ������ ������ */
#define UART_ITSource_ErrorFrame        ((uint32_t)0x00000080)      /*!< ������ � ��������� ����� */
#define UART_ITSource_ErrorParity       ((uint32_t)0x00000100)      /*!< ������ �������� �������� */
#define UART_ITSource_ErrorBreak        ((uint32_t)0x00000200)      /*!< ������ ����� */
#define UART_ITSource_ErrorOverflow     ((uint32_t)0x00000400)      /*!< ������������ ������� ��������� */
#define UART_ITSource_All               ((uint32_t)0x000007FF)      /*!< ��� ��������� �������. */

/**
  * @brief ������ �������� ������� ���������� ���������� �� ��������� � ���������� ��������.
  */

#define IS_UART_IT_SOURCE(IT_SOURCE)  (((IT_SOURCE) & ~UART_ITSource_All) == 0)

 /**
   * @}
   */

/** @defgroup UART_Exported_Constants_Flag ����� ������ UART
  * @{
  */

#define UART_Flag_InvCTS        ((uint32_t)0x00000001)      /*!< ���� �������� ������� �� ����� UART_CTS. */
#define UART_Flag_InvDSR        ((uint32_t)0x00000002)      /*!< ���� �������� ������� �� ����� UART_DSR. */
#define UART_Flag_InvDCD        ((uint32_t)0x00000004)      /*!< ���� �������� ������� �� ����� UART_DSR. */
#define UART_Flag_Busy          ((uint32_t)0x00000008)      /*!< ���� ��������� ����� UART. */
#define UART_Flag_RxFIFOEmpty   ((uint32_t)0x00000010)      /*!< ���� ������� ������� ���������. */
#define UART_Flag_TxFIFOFull    ((uint32_t)0x00000020)      /*!< ���� ���������� ������� �����������. */
#define UART_Flag_RxFIFOFull    ((uint32_t)0x00000040)      /*!< ���� ���������� ������� ���������. */
#define UART_Flag_TxFIFOEmpty   ((uint32_t)0x00000080)      /*!< ���� ������� ������� �����������. */
#define UART_Flag_InvRI         ((uint32_t)0x00000100)      /*!< ���� �������� ������� �� ����� UART_RI. */
#define UART_Flag_All           ((uint32_t)0x000001FF)      /*!< ��� ����� �������. */

 /**
   * @brief ������ �������� ������� ������ �� ��������� � ���������� ��������.
   */

#define IS_UART_FLAG(FLAG)  (((FLAG) & ~UART_Flag_All) == 0)

/**
  * @}
  */

 /** @defgroup UART_Exported_Constants_Error ������ ��������� UART
   * @{
   */

#define UART_Error_Frame        ((uint32_t)0x00000001)      /*!< ���� ������ � ��������� �����. */
#define UART_Error_Parity       ((uint32_t)0x00000002)      /*!< ���� ������ �������� ��������. */
#define UART_Error_Break        ((uint32_t)0x00000004)      /*!< ���� ������� �����. */
#define UART_Error_Overflow     ((uint32_t)0x00000008)      /*!< ���� ������������ ������� ���������. */
#define UART_Error_All          ((uint32_t)0x0000000F)      /*!< ��� ����� ������ �������. */

/**
  * @brief ������ �������� ������� ������ ������ �� ��������� � ���������� ��������.
  */

#define IS_UART_ERROR(ERROR)  (((ERROR) & ~UART_Error_All) == 0)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup UART_Exported_Functions �������
  * @{
  */

void UART_Cmd(NT_UART_TypeDef* UARTx, FunctionalState State);
void UART_BaudRateDivConfig(NT_UART_TypeDef* UARTx, uint32_t IntDiv, uint32_t FracDiv);
void UART_Break(NT_UART_TypeDef* UARTx, FunctionalState State);

/** @defgroup UART_Init_Deinit ������������� � ���������������
  * @{
  */

void UART_DeInit(NT_UART_TypeDef* UARTx);
OperationStatus UART_Init(NT_UART_TypeDef* UARTx, UART_Init_TypeDef* UART_InitStruct);
void UART_StructInit(UART_Init_TypeDef* UART_InitStruct);

/**
  * @}
  */

/** @defgroup UART_SendRecieve ����� � ��������
  * @{
  */

void UART_SendData(NT_UART_TypeDef* UARTx, uint32_t Data);
uint32_t UART_RecieveData(NT_UART_TypeDef* UARTx);
FlagStatus UART_FlagStatus(NT_UART_TypeDef* UARTx, uint32_t UART_Flag);
FlagStatus UART_ErrorStatus(NT_UART_TypeDef* UARTx, uint32_t UART_Error);
void UART_ErrorStatusClear(NT_UART_TypeDef* UARTx, uint32_t UART_Error);

/**
  * @}
  */

/** @defgroup UART_ModemInit ����� ������
  * @{
  */

void UART_ModemConfig(NT_UART_TypeDef* UARTx, UART_ModemInit_TypeDef* UART_ModemInitStruct);
void UART_ModemStructInit(UART_ModemInit_TypeDef* UART_ModemInitStruct);

/**
  * @}
  */

/** @defgroup UART_IT ����������
  * @{
  */

void UART_ITFIFOLevelConfig(NT_UART_TypeDef* UARTx, UART_Dir_Typedef UART_Dir,  UART_FIFOLevel_TypeDef UART_FIFOLevel);
void UART_ITCmd(NT_UART_TypeDef* UARTx, uint32_t UART_ITSource,  FunctionalState State);
FlagStatus UART_ITRawStatus(NT_UART_TypeDef *UARTx, uint32_t UART_ITSource);
FlagStatus UART_ITMaskedStatus(NT_UART_TypeDef* UARTx, uint32_t UART_ITSource);
void UART_ITStatusClear(NT_UART_TypeDef* UARTx, uint32_t UART_ITSource);

/**
  * @}
  */

/** @defgroup UART_DMA ��������� DMA
  * @{
  */

void UART_DMABlkOnErrCmd(NT_UART_TypeDef* UARTx,  FunctionalState State);
void UART_DMACmd(NT_UART_TypeDef* UARTx, UART_Dir_Typedef UART_Dir,  FunctionalState State);

/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* __NIIETCM4_UART_H */



/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2015 NIIET *****END OF FILE****/
