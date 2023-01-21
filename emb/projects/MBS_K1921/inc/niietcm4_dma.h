/**
  ******************************************************************************
  * @file    niietcm4_dma.h
  *
  * @brief   ���� �������� ��� ��������� ������� ��� DMA.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NIIETCM4_DMA_H
#define __NIIETCM4_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "niietcm4.h"

/** @addtogroup Peripheral
  * @{
  */

/** @addtogroup DMA
  * @{
  */

/** @defgroup DMA_Exported_Defines ���������
  * @{
  */

/** @defgroup DMA_Exported_Defines_CHANNEL_CFG ����� ��� CHANNEL_CFG
 *  @brief  ������� ������� � ����� �������� CHANNEL_CFG � @ref DMA_Channel_TypeDef
  * @{
  */

#define CHANNEL_CFG_CYCLE_CTRL_Pos      0      /*!< ���� ������� ���� ����� DMA */
#define CHANNEL_CFG_NEXT_USEBURST_Pos   3      /*!< ������������ ��������� ��������������� ������ ���� � �������� NT_DMA->CHNL_USEBURST_SET */
#define CHANNEL_CFG_N_MINUS_1_Pos       4      /*!< ����� ���������� ������� � ����� ������ */
#define CHANNEL_CFG_R_POWER_Pos         14     /*!< ���������� ������� �� ���������� �������������� */
#define CHANNEL_CFG_SRC_PROT_CTRL_Pos   18     /*!< ������ ���� AHB-Lite ��� ������ ������ �� ��������� */
#define CHANNEL_CFG_DST_PROT_CTRL_Pos   21     /*!< ������ ���� AHB-Lite ��� ������ ������ � �������� */
#define CHANNEL_CFG_SRC_SIZE_Pos        24     /*!< ����������� ������ ��������� */
#define CHANNEL_CFG_SRC_INC_Pos         26     /*!< ��� ���������� ������ ��������� */
#define CHANNEL_CFG_DST_SIZE_Pos        28     /*!< ����������� ������ ��������� */
#define CHANNEL_CFG_DST_INC_Pos         30     /*!< ��� ���������� ������ ��������� */

#define CHANNEL_CFG_CYCLE_CTRL_Msk      ((uint32_t)0x00000007)     /*!< ���� ������� ���� ����� DMA */
#define CHANNEL_CFG_NEXT_USEBURST_Msk   ((uint32_t)0x00000008)     /*!< ������������ ��������� ��������������� ������ ���� � �������� NT_DMA->CHNL_USEBURST_SET */
#define CHANNEL_CFG_N_MINUS_1_Msk       ((uint32_t)0x00003FF0)     /*!< ����� ���������� ������� � ����� ������ */
#define CHANNEL_CFG_R_POWER_Msk         ((uint32_t)0x0003C000)     /*!< ���������� ������� �� ���������� �������������� */
#define CHANNEL_CFG_SRC_PROT_CTRL_Msk   ((uint32_t)0x001C0000)     /*!< ������ ���� AHB-Lite ��� ������ ������ �� ��������� */
#define CHANNEL_CFG_DST_PROT_CTRL_Msk   ((uint32_t)0x00E00000)     /*!< ������ ���� AHB-Lite ��� ������ ������ � �������� */
#define CHANNEL_CFG_SRC_SIZE_Msk        ((uint32_t)0x03000000)     /*!< ����������� ������ ��������� */
#define CHANNEL_CFG_SRC_INC_Msk         ((uint32_t)0x0C000000)     /*!< ��� ���������� ������ ��������� */
#define CHANNEL_CFG_DST_SIZE_Msk        ((uint32_t)0x30000000)     /*!< ����������� ������ ��������� */
#define CHANNEL_CFG_DST_INC_Msk         ((uint32_t)0xC0000000)     /*!< ��� ���������� ������ ��������� */

/**
  * @}
  */

 /** @defgroup DMA_Exported_Defines_Channels ����� ������� DMA
   * @{
   */

#define DMA_Channel_All           ((uint32_t)0x00FFFFFF)  /*!< ��� ������ DMA */

/** @defgroup DMA_Exported_Defines_Channels_Num ����� ������� �� ������
  * @{
  */

#define DMA_Channel_0             ((uint32_t)0x00000001)  /*!< ����� DMA 0 */
#define DMA_Channel_1             ((uint32_t)0x00000002)  /*!< ����� DMA 1 */
#define DMA_Channel_2             ((uint32_t)0x00000004)  /*!< ����� DMA 2 */
#define DMA_Channel_3             ((uint32_t)0x00000008)  /*!< ����� DMA 3 */
#define DMA_Channel_4             ((uint32_t)0x00000010)  /*!< ����� DMA 4 */
#define DMA_Channel_5             ((uint32_t)0x00000020)  /*!< ����� DMA 5 */
#define DMA_Channel_6             ((uint32_t)0x00000040)  /*!< ����� DMA 6 */
#define DMA_Channel_7             ((uint32_t)0x00000080)  /*!< ����� DMA 7 */
#define DMA_Channel_8             ((uint32_t)0x00000100)  /*!< ����� DMA 8 */
#define DMA_Channel_9             ((uint32_t)0x00000200)  /*!< ����� DMA 9 */
#define DMA_Channel_10            ((uint32_t)0x00000400)  /*!< ����� DMA 10 */
#define DMA_Channel_11            ((uint32_t)0x00000800)  /*!< ����� DMA 11 */
#define DMA_Channel_12            ((uint32_t)0x00001000)  /*!< ����� DMA 12 */
#define DMA_Channel_13            ((uint32_t)0x00002000)  /*!< ����� DMA 13 */
#define DMA_Channel_14            ((uint32_t)0x00004000)  /*!< ����� DMA 14 */
#define DMA_Channel_15            ((uint32_t)0x00008000)  /*!< ����� DMA 15 */
#define DMA_Channel_16            ((uint32_t)0x00010000)  /*!< ����� DMA 16 */
#define DMA_Channel_17            ((uint32_t)0x00020000)  /*!< ����� DMA 17 */
#define DMA_Channel_18            ((uint32_t)0x00040000)  /*!< ����� DMA 18 */
#define DMA_Channel_19            ((uint32_t)0x00080000)  /*!< ����� DMA 19 */
#define DMA_Channel_20            ((uint32_t)0x00100000)  /*!< ����� DMA 20 */
#define DMA_Channel_21            ((uint32_t)0x00200000)  /*!< ����� DMA 21 */
#define DMA_Channel_22            ((uint32_t)0x00400000)  /*!< ����� DMA 22 */
#define DMA_Channel_23            ((uint32_t)0x00800000)  /*!< ����� DMA 23 */

/**
   * @}
   */

/** @defgroup DMA_Exported_Defines_Channels_Name ����� ������� �� �����
  * @{
  */

#define DMA_Channel_UART0_TX      DMA_Channel_0   /*!< ����� DMA �� �������� �� UART0 */
#define DMA_Channel_UART1_TX      DMA_Channel_1   /*!< ����� DMA �� �������� �� UART1 */
#define DMA_Channel_UART2_TX      DMA_Channel_2   /*!< ����� DMA �� �������� �� UART2 */
#define DMA_Channel_UART3_TX      DMA_Channel_3   /*!< ����� DMA �� �������� �� UART3 */
#define DMA_Channel_UART0_RX      DMA_Channel_4   /*!< ����� DMA �� ������ �� UART0 */
#define DMA_Channel_UART1_RX      DMA_Channel_5   /*!< ����� DMA �� ������ �� UART1 */
#define DMA_Channel_UART2_RX      DMA_Channel_6   /*!< ����� DMA �� ������ �� UART2 */
#define DMA_Channel_UART3_RX      DMA_Channel_7   /*!< ����� DMA �� ������ �� UART3 */
#define DMA_Channel_ADCSEQ0       DMA_Channel_8   /*!< ����� DMA ���������� 0 ��� */
#define DMA_Channel_ADCSEQ1       DMA_Channel_9   /*!< ����� DMA ���������� 1 ��� */
#define DMA_Channel_ADCSEQ2       DMA_Channel_10  /*!< ����� DMA ���������� 2 ��� */
#define DMA_Channel_ADCSEQ3       DMA_Channel_11  /*!< ����� DMA ���������� 3 ��� */
#define DMA_Channel_ADCSEQ4       DMA_Channel_12  /*!< ����� DMA ���������� 4 ��� */
#define DMA_Channel_ADCSEQ5       DMA_Channel_13  /*!< ����� DMA ���������� 5 ��� */
#define DMA_Channel_ADCSEQ6       DMA_Channel_14  /*!< ����� DMA ���������� 6 ��� */
#define DMA_Channel_ADCSEQ7       DMA_Channel_15  /*!< ����� DMA ���������� 7 ��� */
#define DMA_Channel_SPI0_TX       DMA_Channel_16  /*!< ����� DMA �� �������� �� SPI0 */
#define DMA_Channel_SPI1_TX       DMA_Channel_17  /*!< ����� DMA �� �������� �� SPI1 */
#define DMA_Channel_SPI2_TX       DMA_Channel_18  /*!< ����� DMA �� �������� �� SPI2 */
#define DMA_Channel_SPI3_TX       DMA_Channel_19  /*!< ����� DMA �� �������� �� SPI3 */
#define DMA_Channel_SPI0_RX       DMA_Channel_20  /*!< ����� DMA �� ������ �� SPI0 */
#define DMA_Channel_SPI1_RX       DMA_Channel_21  /*!< ����� DMA �� ������ �� SPI1 */
#define DMA_Channel_SPI2_RX       DMA_Channel_22  /*!< ����� DMA �� ������ �� SPI2 */
#define DMA_Channel_SPI3_RX       DMA_Channel_23  /*!< ����� DMA �� ������ �� SPI3 */

/**
  * @}
  */

/**
  * @brief ������ �������� ����� ������� �� ��������� � ���������� ��������.
  */

#define IS_DMA_CHANNEL(CHANNEL) (((CHANNEL) != (uint32_t)0x000000) && (((CHANNEL) & (uint32_t)0xFF000000) == ((uint32_t)0x0000)))


/**
  * @brief ������ �������� ����� ������ ��� ������ � �������� �� �����������.
  */

#define IS_GET_DMA_CHANNEL(CHANNEL) (((CHANNEL) == (DMA_Channel_0)) || \
                                     ((CHANNEL) == (DMA_Channel_1)) || \
                                     ((CHANNEL) == (DMA_Channel_2)) || \
                                     ((CHANNEL) == (DMA_Channel_3)) || \
                                     ((CHANNEL) == (DMA_Channel_4)) || \
                                     ((CHANNEL) == (DMA_Channel_5)) || \
                                     ((CHANNEL) == (DMA_Channel_6)) || \
                                     ((CHANNEL) == (DMA_Channel_7)) || \
                                     ((CHANNEL) == (DMA_Channel_8)) || \
                                     ((CHANNEL) == (DMA_Channel_9)) || \
                                     ((CHANNEL) == (DMA_Channel_10)) || \
                                     ((CHANNEL) == (DMA_Channel_11)) || \
                                     ((CHANNEL) == (DMA_Channel_12)) || \
                                     ((CHANNEL) == (DMA_Channel_13)) || \
                                     ((CHANNEL) == (DMA_Channel_14)) || \
                                     ((CHANNEL) == (DMA_Channel_15)) || \
                                     ((CHANNEL) == (DMA_Channel_16)) || \
                                     ((CHANNEL) == (DMA_Channel_17)) || \
                                     ((CHANNEL) == (DMA_Channel_18)) || \
                                     ((CHANNEL) == (DMA_Channel_10)) || \
                                     ((CHANNEL) == (DMA_Channel_20)) || \
                                     ((CHANNEL) == (DMA_Channel_21)) || \
                                     ((CHANNEL) == (DMA_Channel_22)) || \
                                     ((CHANNEL) == (DMA_Channel_23)))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup DMA_Exported_Types ����
  * @{
  */

/**
  * @brief ������� ������ � �������� CHANNEL_CFG � @ref DMA_Channel_TypeDef
  */

typedef struct {
    uint32_t CYCLE_CTRL             :3;     /*!< ����� ������ ������ DMA */
    uint32_t NEXT_USEBURST          :1;     /*!< �������� ��������� ��������������� ������ ���� � �������� NT_DMA->CHNL_USEBURST_SET */
    uint32_t N_MINUS_1              :10;    /*!< ����� ���������� ������� N (� ���� ������� �������� N-1) */
    uint32_t R_POWER                :4;     /*!< ����� ���������� ������� �� ���������� �������������� */
    uint32_t SRC_PROT_PRIVILEGED    :1;     /*!< ������ ���� ��� ������ �� ���������: ����������������� ������ */
    uint32_t SRC_PROT_BUFFERABLE    :1;     /*!< ������ ���� ��� ������ �� ���������: ������������ */
    uint32_t SRC_PROT_CACHEABLE     :1;     /*!< ������ ���� ��� ������ �� ���������: ����������� */
    uint32_t DST_PROT_PRIVILEGED    :1;     /*!< ������ ���� ��� ������ � ��������: ����������������� ������ */
    uint32_t DST_PROT_BUFFERABLE    :1;     /*!< ������ ���� ��� ������ � ��������: ������������ */
    uint32_t DST_PROT_CACHEABLE     :1;     /*!< ������ ���� ��� ������ � ��������: ����������� */
    uint32_t SRC_SIZE               :2;     /*!< ����������� ������ ��������� */
    uint32_t SRC_INC                :2;     /*!< ��� ���������� ������ ��������� ��� ������ */
    uint32_t DST_SIZE               :2;     /*!< ����������� ������ ��������� */
    uint32_t DST_INC                :2;     /*!< ��� ���������� ������ ��������� ��� ������ */
}_CHANNEL_CFG_bits;

/**
  * @brief ���, ����������� ��������� ������ DMA.
  */

typedef struct
{
    uint32_t SRC_DATA_END; /*!< ����� ����� ������ ��������� */
    uint32_t DST_DATA_END; /*!< ����� ����� ������ ��������� */
    union
    {
        uint32_t CHANNEL_CFG;             /*!< ��������� ������ */
        _CHANNEL_CFG_bits CHANNEL_CFG_bit; /*!< ��������� ������: ��������� ������ */
    };
            uint32_t  RESERVED;
}DMA_Channel_TypeDef;

/**
  * @brief ����������� ��������� ������ DMA.
  */

typedef struct
{
    DMA_Channel_TypeDef CH[24];  /*!< ������������ �� ������ ���������� ������� DMA */
}DMA_ConfigStruct_TypeDef;

/**
  * @brief ������������ �� �������� � ����������� �������� DMA. ����� ������ 1 ��.
  * @attention ���������� ���� ��������� ������� ������������� ������������ ��
  *   1024 ������ � �������� ������������! ����������� ������: 0xXXXXX000,
  *   0xXXXXX400, 0xXXXXX800, 0xXXXXXC00.
  */

typedef struct
{
    DMA_ConfigStruct_TypeDef PRM_DATA;  /*!< �������� ����������� ��������� */
    uint32_t  RESERVED0[32];            /*!< �������� ��� ���������������� 8 ������� DMA */
    DMA_ConfigStruct_TypeDef ALT_DATA;  /*!< �������������� ����������� ��������� */
    uint32_t  RESERVED1[32];            /*!< �������� ��� ���������������� 8 ������� DMA */
}DMA_ConfigData_TypeDef;

/**
  * @brief ����� ������ ������ DMA.
  */

typedef enum
{
    DMA_Mode_Disable,           /*!< ���������� ��������� */
    DMA_Mode_Basic,             /*!< �������� ����� �������� */
    DMA_Mode_AutoReq,           /*!< ����� �������� � ����-�������� */
    DMA_Mode_PingPong,          /*!< ����� �������� "����-����" */
    DMA_Mode_PrmMemScatGath,    /*!< ������ � ������� � ������ "��������-������" � �������������� ��������� ����������� ��������� */
    DMA_Mode_AltMemScatGath,    /*!< ������ � ������� � ������ "��������-������" � �������������� �������������� ����������� ��������� */
    DMA_Mode_PrmPeriphScatGath, /*!< ������ � ���������� � ������ "��������-������" � �������������� ��������� ����������� ��������� */
    DMA_Mode_AltPeriphScatGath  /*!< ������ � ���������� � ������ "��������-������" � �������������� �������������� ����������� ��������� */
}DMA_Mode_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref DMA_Mode_TypeDef.
  */

#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Disable) || \
                           ((MODE) == DMA_Mode_Basic) || \
                           ((MODE) == DMA_Mode_AutoReq) || \
                           ((MODE) == DMA_Mode_PingPong) || \
                           ((MODE) == DMA_Mode_PrmMemScatGath) || \
                           ((MODE) == DMA_Mode_AltMemScatGath) || \
                           ((MODE) == DMA_Mode_PrmPeriphScatGath) || \
                           ((MODE) == DMA_Mode_AltPeriphScatGath))

 /**
   * @brief ����� ���������� ������� �� ���������� ��������������.
   */

typedef enum
{
    DMA_ArbitrationRate_1,      /*!< �������������� ������ �������� DMA */
    DMA_ArbitrationRate_2,      /*!< �������������� ������ 2 �������� DMA */
    DMA_ArbitrationRate_4,      /*!< �������������� ������ 4 �������� DMA */
    DMA_ArbitrationRate_8,      /*!< �������������� ������ 8 ������� DMA */
    DMA_ArbitrationRate_16,     /*!< �������������� ������ 16 ������� DMA */
    DMA_ArbitrationRate_32,     /*!< �������������� ������ 32 �������� DMA */
    DMA_ArbitrationRate_64,     /*!< �������������� ������ 64 �������� DMA */
    DMA_ArbitrationRate_128,    /*!< �������������� ������ 128 ������� DMA */
    DMA_ArbitrationRate_256,    /*!< �������������� ������ 256 ������� DMA */
    DMA_ArbitrationRate_512,    /*!< �������������� ������ 512 ������� DMA */
    DMA_ArbitrationRate_1024    /*!< �������������� ������ 1024 �������� DMA */
}DMA_ArbitrationRate_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref DMA_ArbitrationRate_TypeDef.
  */

#define IS_DMA_ARBITRATION_RATE(ARBITRATION_RATE) (((ARBITRATION_RATE) == DMA_ArbitrationRate_1) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_2) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_4) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_8) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_16) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_32) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_64) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_128) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_256) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_512) || \
                                                   ((ARBITRATION_RATE) == DMA_ArbitrationRate_1024))

/**
  * @brief  ������ ���� ��� ������ �� ��������� ��� ������ � �������� ����� DMA.
  */

typedef struct
{
    FunctionalState PRIVELGED;  /*!< ���������� ����������������� �������� */
    FunctionalState BUFFERABLE; /*!< ���������� ������������� ������� */
    FunctionalState CACHEABLE;  /*!< ���������� ������������ ������� */
}DMA_Protect_TypeDef;

/**
  * @brief  ����������� ������ ��������� ��� ���������
  */

typedef enum
{
    DMA_DataSize_8,             /*!< ����������� ������ 8 ��� */
    DMA_DataSize_16,            /*!< ����������� ������ 16 ��� */
    DMA_DataSize_32             /*!< ����������� ������ 32 ��� */
}DMA_DataSize_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref DMA_DataSize_TypeDef.
  */

#define IS_DMA_DATA_SIZE(DATA_SIZE) (((DATA_SIZE) == DMA_DataSize_8) || \
                                     ((DATA_SIZE) == DMA_DataSize_16) || \
                                     ((DATA_SIZE) == DMA_DataSize_32))

/**
  * @brief  ��� ���������� ������ ��������� ��� ������ ��� ��������� ��� ������
  */

typedef enum
{
    DMA_DataInc_8,              /*!< ��������� ������ 8 ��� */
    DMA_DataInc_16,             /*!< ��������� ������ 16 ��� */
    DMA_DataInc_32,             /*!< ��������� ������ 32 ��� */
    DMA_DataInc_Disable         /*!< ��������� ����������� */
}DMA_DataInc_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref DMA_DataSize_TypeDef.
  */

#define IS_DMA_DATA_INC(DATA_INC) (((DATA_INC) == DMA_DataInc_8) || \
                                   ((DATA_INC) == DMA_DataInc_16) || \
                                   ((DATA_INC) == DMA_DataInc_32) || \
                                   ((DATA_INC) == DMA_DataInc_Disable))

/**
  * @brief  ��������� ������������� ������ DMA
  */

typedef struct
{
    uint32_t *DMA_SrcDataEndPtr;                       /*!< ��������� ����� ������ ���������. */
    uint32_t *DMA_DstDataEndPtr;                        /*!< ��������� ����� ������ ���������. */
    DMA_Mode_TypeDef DMA_Mode;                          /*!< ����� ������ ������ DMA.
                                                            �������� ����� ��������� ����� �������� �� @ref DMA_Mode_TypeDef. */
    FunctionalState DMA_NextUseburst;                   /*!< �������� ��������� ��������������� ������ ���� � �������� NT_DMA->CHNL_USEBURST_SET.
                                                            �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    uint32_t DMA_TransfersTotal;                        /*!< ����� ���������� ������� DMA.
                                                            �������� ����� ��������� ����� �������� �� ��������� 1-1024 */
    DMA_ArbitrationRate_TypeDef DMA_ArbitrationRate;    /*!< ����� ���������� ������� �� ���������� ��������������.
                                                            �������� ����� ��������� ����� �������� �� @ref DMA_ArbitrationRate_TypeDef. */
    DMA_Protect_TypeDef DMA_SrcProtect;                 /*!< ������ ���� ��� ������ �� ��������� ����� DMA
                                                            �������� ����� ��������� ����� �������� �� @ref DMA_Protect_TypeDef.*/
    DMA_Protect_TypeDef DMA_DstProtect;                 /*!< ������ ���� ��� ������ � �������� ����� DMA
                                                            �������� ����� ��������� ����� �������� �� @ref DMA_Protect_TypeDef.*/
    DMA_DataSize_TypeDef DMA_SrcDataSize;               /*!< ����������� ������ ���������
                                                            �������� ����� ��������� ����� �������� �� @ref DMA_DataSize_TypeDef.*/
    DMA_DataSize_TypeDef DMA_DstDataSize;               /*!< ����������� ������ ���������
                                                            �������� ����� ��������� ����� �������� �� @ref DMA_DataSize_TypeDef.*/
    DMA_DataInc_TypeDef DMA_SrcDataInc;                 /*!< ��� ���������� ������ ��������� ��� ������
                                                            �������� ����� ��������� ����� �������� �� @ref DMA_DataInc_TypeDef.*/
    DMA_DataInc_TypeDef DMA_DstDataInc;                 /*!< ��� ���������� ������ ��������� ��� ������
                                                            �������� ����� ��������� ����� �������� �� @ref DMA_DataInc_TypeDef.*/
}DMA_ChannelInit_TypeDef;

/**
   * @brief ������ �������� ����������� �������� DMA_TransfersTotal �� @ref DMA_ChannelInit_TypeDef ������������ ���������.
   */

#define IS_DMA_TRANSFERS_TOTAL(TRANSFERS_TOTAL) (((TRANSFERS_TOTAL) <= ((uint32_t)1024)) && ((TRANSFERS_TOTAL) >= ((uint32_t)1)))

/**
  * @brief  ��������� ������������� ����������� DMA
  */

typedef struct
{
    uint32_t DMA_Channel;                   /*!< ���������� ������, ������� ����� ���������.
                                               �������� ����� ��������� ����� �������� ����� ��� ���������� ����� �� @ref DMA_Exported_Defines_Channels_Num. */
    DMA_Protect_TypeDef DMA_Protection;     /*!< ���������� ������� ���� ��� ��������� DMA � ����������� ������. */
    FunctionalState DMA_UseBurst;           /*!< ��������� ��������� ������ ������� DMA
                                                �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    FunctionalState DMA_ReqMask;            /*!< ������������ (�������������) �������� �� ��������� �� ������������ ������� DMA.
                                                �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    FunctionalState DMA_PrmAlt;             /*!< ��������� ���������/�������������� ����������� ��������� ������� DMA.
                                                �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    FunctionalState DMA_HighPriority;       /*!< ��������� �������� ���������� ������� DMA.
                                                �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
    FunctionalState DMA_ChannelEnable;      /*!< ���������� ������ ������� DMA.
                                                �������� ����� ��������� ����� �������� �� @ref FunctionalState. */
}DMA_Init_TypeDef;

/**
  * @brief  ��������� ��������� ��������� �������� ���������� ������������ DMA.
  */

typedef enum
{
    DMA_State_Free,                /*!< � �����. */
    DMA_State_ReadConfigData,      /*!< ������ ����������� ������ ������. */
    DMA_State_ReadSrcDataEndPtr,   /*!< ������ ��������� ����� ������ ���������. */
    DMA_State_ReadDstDataEndPtr,   /*!< ������ ��������� ����� ������ ���������. */
    DMA_State_ReadSrcData,         /*!< ������ ������ ���������. */
    DMA_State_WriteDstData,        /*!< ������ ������ � ��������. */
    DMA_State_WaitReq,             /*!< �������� ������� �� ���������� ������� �������. */
    DMA_State_WriteConfigData,     /*!< ������ ����������� ������ ������. */
    DMA_State_Pause,               /*!< �������������. */
    DMA_State_Done,                /*!< ��������. */
    DMA_State_PeriphScatGath,      /*!< ������ � ���������� � ������ "��������-������". */
}DMA_State_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref DMA_State_TypeDef.
  */

#define IS_DMA_STATE(STATE) (((STATE) == DMA_State_Free) || \
                             ((STATE) == DMA_State_ReadConfigData) || \
                             ((STATE) == DMA_State_ReadSrcDataEndPtr) || \
                             ((STATE) == DMA_State_ReadDstDataEndPtr) || \
                             ((STATE) == DMA_State_ReadSrcData) || \
                             ((STATE) == DMA_State_WriteDstData) || \
                             ((STATE) == DMA_State_WaitReq) || \
                             ((STATE) == DMA_State_Pause) || \
                             ((STATE) == DMA_State_Done) || \
                             ((STATE) == DMA_State_PeriphScatGath))

/**
  * @}
  */


/** @defgroup DMA_Exported_Functions �������
  * @{
  */

/** @defgroup DMA_Exported_Functions_Init_Channel ������������� ������� DMA
  * @{
  */

void DMA_ChannelDeInit(DMA_Channel_TypeDef* DMA_Channel);
void DMA_ChannelInit(DMA_Channel_TypeDef* DMA_Channel, DMA_ChannelInit_TypeDef* DMA_ChannelInitStruct);
void DMA_ChannelStructInit(DMA_ChannelInit_TypeDef* DMA_ChannelInitStruct);

/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Init ������������� ����������� DMA
  * @{
  */

void DMA_DeInit();
void DMA_Init(DMA_Init_TypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_Init_TypeDef* DMA_InitStruct);

/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Config ������������ ����������� DMA
  * @{
  */

void DMA_BasePtrConfig(uint32_t BasePtr);
void DMA_ProtectionConfig(DMA_Protect_TypeDef *DMA_Protection);
void DMA_MasterEnableCmd(FunctionalState State);
void DMA_SWRequestCmd(uint32_t DMA_Channel);
void DMA_UseBurstCmd(uint32_t DMA_Channel, FunctionalState State);
void DMA_ReqMaskCmd(uint32_t DMA_Channel, FunctionalState State);
void DMA_ChannelEnableCmd(uint32_t DMA_Channel, FunctionalState State);
void DMA_PrmAltCmd(uint32_t DMA_Channel, FunctionalState State);
void DMA_HighPriorityCmd(uint32_t DMA_Channel, FunctionalState State);

/**
  * @}
  */


/** @defgroup DMA_Exported_Functions_Status ��������� ����������
  * @{
  */

DMA_State_TypeDef DMA_StateStatus();
FunctionalState DMA_MasterEnableStatus();
FunctionalState DMA_WaitOnReqStatus(uint32_t DMA_Channel);
OperationStatus DMA_ErrorStatus();
void DMA_ClearErrorStatus();

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __NIIETCM4_DMA_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2015 NIIET *****END OF FILE****/
