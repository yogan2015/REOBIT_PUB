/**
  ******************************************************************************
  * @file    niietcm4_rcc.h
  *
  * @brief   ���� �������� ��� ��������� ������� ��� RCC (Reset & Clock Control).
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
#ifndef __NIIETCM4_RCC_H
#define __NIIETCM4_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "niietcm4.h"

/** @addtogroup Peripheral
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/** @defgroup RCC_Exported_Defines ���������
  * @{
  */

    #define RCC_CLK_CHANGE_TIMEOUT      ((uint32_t)10000) /*!< ����� �������� ����� ��������� ������������ */
    #define RCC_CLK_PLL_STABLE_TIMEOUT  ((uint32_t)100) /*!< ����� �������� ������������ �������� ������� PLL */

/**
  * @}
  */

/** @defgroup RCC_Exported_Types ����
  * @{
  */

/**
  * @brief  ����� ��������� �������� ������� PLL.
  */

typedef enum
{
    RCC_PLLRef_XI_OSC,       /*!< ������ �� ����� XI_OSC */
    RCC_PLLRef_USB_CLK,      /*!< ������ � ������� �������������� ������� CLK_USB */
    RCC_PLLRef_USB_60MHz,    /*!< ������ �� ������ ����� USB */
    RCC_PLLRef_ETH_25MHz     /*!< ������� �������� ������ ����� Ethernet */
}RCC_PLLRef_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref RCC_PLLRef_TypeDef.
  */

#define IS_RCC_PLL_REF(PLL_REF) (((PLL_REF) == RCC_PLLRef_XI_OSC) || \
                                 ((PLL_REF) == RCC_PLLRef_USB_CLK) || \
                                 ((PLL_REF) == RCC_PLLRef_USB_60MHz)|| \
                                 ((PLL_REF) == RCC_PLLRef_ETH_25MHz))


/**
  * @brief  �������� �������� NO
  */

typedef enum
{
    RCC_PLLNO_Disable,       /*!< �������� NO �������� */
    RCC_PLLNO_Div2,          /*!< ����������� ������� NO ����� 2 */
    RCC_PLLNO_Div4 = 3       /*!< ����������� ������� NO ����� 4 */
}RCC_PLLNO_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref RCC_PLLNO_TypeDef.
  */

#define IS_RCC_PLL_NO(PLL_NO) (((PLL_NO) == RCC_PLLNO_Disable) || \
                               ((PLL_NO) == RCC_PLLNO_Div2) || \
                               ((PLL_NO) == RCC_PLLNO_Div4))

/**
  * @brief  ����� ��������� ������������ ��� UART.
  */

typedef enum
{
    RCC_UARTClk_SYSCLK,     /*!< ������� ��������� ������� */
    RCC_UARTClk_XI_OSC,     /*!< ������ �� ����� XI_OSC */
    RCC_UARTClk_USB_CLK,    /*!< ������ � ������� �������������� ������� CLK_USB */
    RCC_UARTClk_USB_60MHz   /*!< ������ �� ������ ����� USB */
}RCC_UARTClk_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref RCC_UARTClk_TypeDef.
  */

#define IS_RCC_UART_CLK(UART_CLK) (((UART_CLK) == RCC_UARTClk_SYSCLK) || \
                                   ((UART_CLK) == RCC_UARTClk_XI_OSC) || \
                                   ((UART_CLK) == RCC_UARTClk_USB_CLK) || \
                                   ((UART_CLK) == RCC_UARTClk_USB_60MHz))

 /**
   * @brief  ����� ��������� ������������ ��� SPI.
   */

 typedef enum
 {
     RCC_SPIClk_SYSCLK,     /*!< ������� ��������� ������� */
     RCC_SPIClk_XI_OSC,     /*!< ������ �� ����� XI_OSC */
     RCC_SPIClk_USB_CLK,    /*!< ������ � ������� �������������� ������� CLK_USB */
     RCC_SPIClk_USB_60MHz   /*!< ������ �� ������ ����� USB */
 }RCC_SPIClk_TypeDef;

 /**
   * @brief ������ �������� ���������� ���� @ref RCC_SPIClk_TypeDef.
   */

 #define IS_RCC_SPI_CLK(SPI_CLK) (((SPI_CLK) == RCC_SPIClk_SYSCLK) || \
                                  ((SPI_CLK) == RCC_SPIClk_XI_OSC) || \
                                  ((SPI_CLK) == RCC_SPIClk_USB_CLK) || \
                                  ((SPI_CLK) == RCC_SPIClk_USB_60MHz))

/**
  * @brief  ����� ��������� ������������ ��� USB.
  */

typedef enum
{
    RCC_USBClk_XI_OSC,      /*!< ������ �� ����� XI_OSC */
    RCC_USBClk_USB_CLK      /*!< ������ � ������� �������������� ������� CLK_USB */
}RCC_USBClk_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref RCC_USBClk_TypeDef.
  */

#define IS_RCC_USB_CLK(USB_CLK) (((USB_CLK) == RCC_USBClk_XI_OSC) || \
                                 ((USB_CLK) == RCC_USBClk_USB_CLK))

/**
  * @brief  ����� ������������� ������� �� ����� CLK_USB.
  */

typedef enum
{
    RCC_USBFreq_12MHz,      /*!< 12 ��� ������ �� ����� CLK_USB */
    RCC_USBFreq_24MHz       /*!< 24 ��� ������ �� ����� CLK_USB */
}RCC_USBFreq_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref RCC_USBFreq_TypeDef.
  */

#define IS_RCC_USB_FREQ(USB_FREQ) (((USB_FREQ) == RCC_USBFreq_12MHz) || \
                                   ((USB_FREQ) == RCC_USBFreq_24MHz))

/**
  * @brief  ����� ������ ADC ��� ��������� ��� ��������� �������.
  */

typedef enum
{
    RCC_ADCClk_0,      /*!< �������� ������ ADC 0 */
    RCC_ADCClk_1,      /*!< �������� ������ ADC 1 */
    RCC_ADCClk_2,      /*!< �������� ������ ADC 2 */
    RCC_ADCClk_3,      /*!< �������� ������ ADC 3 */
    RCC_ADCClk_4,      /*!< �������� ������ ADC 4 */
    RCC_ADCClk_5,      /*!< �������� ������ ADC 5 */
    RCC_ADCClk_6,      /*!< �������� ������ ADC 6 */
    RCC_ADCClk_7,      /*!< �������� ������ ADC 7 */
    RCC_ADCClk_8,      /*!< �������� ������ ADC 8 */
    RCC_ADCClk_9,      /*!< �������� ������ ADC 9 */
    RCC_ADCClk_10,     /*!< �������� ������ ADC 10 */
    RCC_ADCClk_11,     /*!< �������� ������ ADC 11 */
}RCC_ADCClk_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref RCC_ADCClk_TypeDef.
  */

#define IS_RCC_ADC_CLK(ADC_CLK) (((ADC_CLK) == RCC_ADCClk_0) || \
                                 ((ADC_CLK) == RCC_ADCClk_1) || \
                                 ((ADC_CLK) == RCC_ADCClk_2) || \
                                 ((ADC_CLK) == RCC_ADCClk_3) || \
                                 ((ADC_CLK) == RCC_ADCClk_4) || \
                                 ((ADC_CLK) == RCC_ADCClk_5) || \
                                 ((ADC_CLK) == RCC_ADCClk_6) || \
                                 ((ADC_CLK) == RCC_ADCClk_7) || \
                                 ((ADC_CLK) == RCC_ADCClk_8) || \
                                 ((ADC_CLK) == RCC_ADCClk_9) || \
                                 ((ADC_CLK) == RCC_ADCClk_10) || \
                                 ((ADC_CLK) == RCC_ADCClk_11))

/**
  * @brief  ����� ��������� ��������� �������.
  */

typedef enum
{
    RCC_SysClk_CPE_Sel,     /*!< �������� ������������ ���������� ������ CPE: 0-POR, 1-XI_OSC */
    RCC_SysClk_POR,         /*!< ���������� �������� ��������� ������� */
    RCC_SysClk_XI_OSC,      /*!< ������� �������� ��������� ������� �� ����� XI_OSC */
    RCC_SysClk_PLL,         /*!< ����� ����� PLL */
    RCC_SysClk_PLLDIV,      /*!< ����� ����� PLL ����� �������� PLL DIV */
    RCC_SysClk_USB60MHz,    /*!< ����� ����� USB 60 ��� */
    RCC_SysClk_USB_CLK,     /*!< ������� �������� ��������� ������� �� ����� CLK_USB */
    RCC_SysClk_ETH25MHz,    /*!< ������� �������� ������ ����� Ethernet */
}RCC_SysClk_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref RCC_SysClk_TypeDef.
  */

#define IS_RCC_SYS_CLK(SYS_CLK) (((SYS_CLK) == RCC_SysClk_CPE_Sel) || \
                                 ((SYS_CLK) == RCC_SysClk_POR) || \
                                 ((SYS_CLK) == RCC_SysClk_XI_OSC) || \
                                 ((SYS_CLK) == RCC_SysClk_PLL) || \
                                 ((SYS_CLK) == RCC_SysClk_PLLDIV) || \
                                 ((SYS_CLK) == RCC_SysClk_USB60MHz) || \
                                 ((SYS_CLK) == RCC_SysClk_USB_CLK) || \
                                 ((SYS_CLK) == RCC_SysClk_ETH25MHz))

/**
  * @brief  ���������� ������������� ������������ ������
  */

typedef enum
{
    RCC_PeriphClk_QEP0 = ((uint32_t)(1<<1)),        /*!< ���������� ������������� ����� QEP 0 */
    RCC_PeriphClk_QEP1 = ((uint32_t)(1<<2)),        /*!< ���������� ������������� ����� QEP 1 */
    RCC_PeriphClk_CMP  = ((uint32_t)(1<<9)),        /*!< ���������� ������������� ����� ����������� ����������� */
    RCC_PeriphClk_PWM0 = ((uint32_t)(1<<10)),       /*!< ���������� ������������� ����� PWM 0 */
    RCC_PeriphClk_PWM1 = ((uint32_t)(1<<11)),       /*!< ���������� ������������� ����� PWM 1 */
    RCC_PeriphClk_PWM2 = ((uint32_t)(1<<12)),       /*!< ���������� ������������� ����� PWM 2 */
    RCC_PeriphClk_PWM3 = ((uint32_t)(1<<13)),       /*!< ���������� ������������� ����� PWM 3 */
    RCC_PeriphClk_PWM4 = ((uint32_t)(1<<14)),       /*!< ���������� ������������� ����� PWM 4 */
    RCC_PeriphClk_PWM5 = ((uint32_t)(1<<15)),       /*!< ���������� ������������� ����� PWM 5 */
    RCC_PeriphClk_PWM6 = ((uint32_t)(1<<16)),       /*!< ���������� ������������� ����� PWM 6 */
    RCC_PeriphClk_PWM7 = ((uint32_t)(1<<17)),       /*!< ���������� ������������� ����� PWM 7 */
    RCC_PeriphClk_PWM8 = ((uint32_t)(1<<18)),       /*!< ���������� ������������� ����� PWM 8 */
    RCC_PeriphClk_WD   = ((uint32_t)(1<<19)),       /*!< ���������� ������������� ����������� ������� */
    RCC_PeriphClk_I2C0 = ((uint32_t)(1<<20)),       /*!< ���������� ������������� ����� I2C 0 */
    RCC_PeriphClk_I2C1 = ((uint32_t)(1<<21)),       /*!< ���������� ������������� ����� I2C 1 */
    RCC_PeriphClk_ADC  = ((uint32_t)(1<<24))        /*!< ���������� ������������� ����������� ADC */
}RCC_PeriphClk_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref RCC_PeriphClk_TypeDef.
  */

#define IS_RCC_PERIPH_CLK(PERIPH_CLK) (((PERIPH_CLK) == RCC_PeriphClk_QEP0) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_QEP1) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_CMP) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_PWM0) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_PWM1) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_PWM2) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_PWM4) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_PWM5) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_PWM6) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_PWM7) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_PWM8) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_WD) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_I2C0) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_I2C1) || \
                                       ((PERIPH_CLK) == RCC_PeriphClk_ADC))

/**
  * @brief  ���������� ������� ������������ ������
  */

typedef enum
{
    RCC_PeriphRst_WD,          /*!< ���������� ������� ����������� ������� */
    RCC_PeriphRst_I2C0,        /*!< ���������� ������� ����� I2C 0 */
    RCC_PeriphRst_I2C1,       /*!< ���������� ������� ����� I2C 1 */
    RCC_PeriphRst_USB,         /*!< ���������� ������� ����� USB */
    RCC_PeriphRst_Timer0,      /*!< ���������� ������� ����� Timer 0 */
    RCC_PeriphRst_Timer1,      /*!< ���������� ������� ����� Timer 1 */
    RCC_PeriphRst_Timer2,      /*!< ���������� ������� ����� Timer 2 */
    RCC_PeriphRst_UART0,       /*!< ���������� ������� ����� UART 0 */
    RCC_PeriphRst_UART1,       /*!< ���������� ������� ����� UART 1 */
    RCC_PeriphRst_UART2,       /*!< ���������� ������� ����� UART 2 */
    RCC_PeriphRst_UART3,       /*!< ���������� ������� ����� UART 3 */
    RCC_PeriphRst_SPI0,        /*!< ���������� ������� ����� SPI 0 */
    RCC_PeriphRst_SPI1,        /*!< ���������� ������� ����� SPI 1 */
    RCC_PeriphRst_SPI2,        /*!< ���������� ������� ����� SPI 2 */
    RCC_PeriphRst_SPI3,        /*!< ���������� ������� ����� SPI 3 */
    RCC_PeriphRst_ETH ,        /*!< ���������� ������� ����� Ethernet */
    RCC_PeriphRst_QEP0,        /*!< ���������� ������� ����� QEP 0 */
    RCC_PeriphRst_QEP1,        /*!< ���������� ������� ����� QEP 1 */
    RCC_PeriphRst_PWM0,        /*!< ���������� ������� ����� PWM 0 */
    RCC_PeriphRst_PWM1,        /*!< ���������� ������� ����� PWM 1 */
    RCC_PeriphRst_PWM2,        /*!< ���������� ������� ����� PWM 2 */
    RCC_PeriphRst_PWM3,        /*!< ���������� ������� ����� PWM 3 */
    RCC_PeriphRst_PWM4,        /*!< ���������� ������� ����� PWM 4 */
    RCC_PeriphRst_PWM5,        /*!< ���������� ������� ����� PWM 5 */
    RCC_PeriphRst_PWM6,        /*!< ���������� ������� ����� PWM 6 */
    RCC_PeriphRst_PWM7,        /*!< ���������� ������� ����� PWM 7 */
    RCC_PeriphRst_PWM8,        /*!< ���������� ������� ����� PWM 8 */
    RCC_PeriphRst_CAP0,        /*!< ���������� ������� ����� CAP 0 */
    RCC_PeriphRst_CAP1,        /*!< ���������� ������� ����� CAP 1 */
    RCC_PeriphRst_CAP2,        /*!< ���������� ������� ����� CAP 2 */
    RCC_PeriphRst_CAP3,        /*!< ���������� ������� ����� CAP 3 */
    RCC_PeriphRst_CAP4,        /*!< ���������� ������� ����� CAP 4 */
    RCC_PeriphRst_CAP5,        /*!< ���������� ������� ����� CAP 5 */
    RCC_PeriphRst_CMP          /*!< ���������� ������� ����� ����������� ����������� */
}RCC_PeriphRst_TypeDef;

/**
  * @brief ������ �������� ���������� ���� @ref RCC_PeriphRst_TypeDef.
  */

#define IS_RCC_PERIPH_RST(PERIPH_RST) (((PERIPH_RST) == RCC_PeriphRst_WD) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_I2C0) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_I2C1) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_USB) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_Timer0) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_Timer1) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_Timer2) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_UART0) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_UART1) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_UART2) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_UART3) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_SPI0) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_SPI1) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_SPI2) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_SPI3) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_ETH) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_QEP0) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_QEP1) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_PWM0) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_PWM1) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_PWM2) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_PWM3) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_PWM4) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_PWM5) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_PWM6) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_PWM7) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_PWM8) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_CAP0) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_CAP1) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_CAP2) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_CAP3) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_CAP4) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_CAP5) || \
                                       ((PERIPH_RST) == RCC_PeriphRst_CMP))

/**
  * @brief  ��������� ������������� PLL
  *
  */

typedef struct
{
    uint32_t RCC_PLLDiv;                    /*!< �������� �������� ������� �� ������ ����� PLL.
                                                 �������� ����� ��������� ����� �������� �� ��������� 0-255. */
    RCC_PLLRef_TypeDef RCC_PLLRef;          /*!< �������� �������� ������� PLL.
                                                 �������� ����� ��������� ����� �������� �� @ref RCC_PLLRef_TypeDef. */
    RCC_PLLNO_TypeDef RCC_PLLNO;             /*!< �������� �������� NO.
                                                 �������� ����� ��������� ����� �������� �� @ref RCC_PLLNO_TypeDef. */
    uint32_t RCC_PLLNR;                     /*!< ������� �������� NR.
                                                 �������� ����� ��������� ����� �������� �� �������� 2-33. */
    uint32_t RCC_PLLNF;                     /*!< �������� �������� ����� NF.
                                                 �������� ����� ��������� ����� �������� �� �������� 2-513. */
}RCC_PLLInit_TypeDef;

/**
  * @brief ������ �������� �������� ��������� �������� PLL �� ��������� � ���������� ��������.
  */

#define IS_RCC_PLLDIV(PLLDIV) (((PLLDIV) & ((uint32_t)0xFFFFFF00)) == ((uint32_t)0x00))

/**
  * @brief ������ �������� �������� �������� �������� PLL �� ��������� � ���������� ��������.
  */

#define IS_RCC_PLL_NR(PLL_NR) (((PLL_NR) <= ((uint32_t)33)) && ((PLL_NR) >= ((uint32_t)2)))

/**
  * @brief ������ �������� �������� �������� �� PLL �� ��������� � ���������� ��������.
  */

#define IS_RCC_PLL_NF(PLL_NF) (((PLL_NF) <= ((uint32_t)513)) && ((PLL_NF) >= ((uint32_t)2)))

/**
  * @brief ������ �������� �������� �������� ��������� ������� �� ��������� � ���������� ��������.
  */

#define IS_RCC_CLK_DIV(CLK_DIV) ((CLK_DIV) < ((uint32_t)64))

 /**
   * @brief ������ �������� �������� �������� ������� ��� ������������� � ���������� ��������.
   */

 #define IS_RCC_SYS_FREQ(SYS_FREQ) (((SYS_FREQ) < ((uint32_t)100000000)) && ((SYS_FREQ) >= ((uint32_t)1000000)))

/**
  * @}
  */


/** @defgroup RCC_Exported_Functions �������
  * @{
  */

void RCC_SysClkDiv2Out(FunctionalState State);

/** @defgroup RCC_Init_Deinit ������������ PLL
  * @{
  */

OperationStatus RCC_PLLAutoConfig(RCC_PLLRef_TypeDef RCC_PLLRef, uint32_t SysFreq);
void RCC_PLLInit(RCC_PLLInit_TypeDef* RCC_PLLInit_Struct);
void RCC_PLLDeInit();
void RCC_PLLStructInit(RCC_PLLInit_TypeDef* RCC_PLLInit_Struct);
void RCC_PLLPowerDownCmd(FunctionalState State);

/**
  * @}
  */

/** @defgroup RCC_CLK_Config ���������� �������������
  * @{
  */

void RCC_PeriphClkCmd(RCC_PeriphClk_TypeDef RCC_PeriphClk, FunctionalState State);
OperationStatus RCC_SysClkSel(RCC_SysClk_TypeDef RCC_SysClk);
RCC_SysClk_TypeDef RCC_SysClkStatus();

/** @defgroup RCC_CLK_Config_USB ������������ USB
  * @{
  */

void RCC_USBClkConfig(RCC_USBClk_TypeDef RCC_USBClk, RCC_USBFreq_TypeDef RCC_USBFreq);
void RCC_USBClkCmd(FunctionalState State);

/**
  * @}
  */

/** @defgroup RCC_CLK_Config_UART ������������ UART
  * @{
  */

void RCC_UARTClkSel(NT_UART_TypeDef* UARTx, RCC_UARTClk_TypeDef RCC_UARTClk);
void RCC_UARTClkDivConfig(NT_UART_TypeDef* UARTx, uint32_t DivVal, FunctionalState DivState);
void RCC_UARTClkCmd(NT_UART_TypeDef* UARTx, FunctionalState State);

/**
  * @}
  */

/** @defgroup RCC_CLK_Config_SPI ������������ SPI
  * @{
  */

void RCC_SPIClkSel(NT_SPI_TypeDef* SPIx, RCC_SPIClk_TypeDef RCC_SPIClk);
void RCC_SPIClkDivConfig(NT_SPI_TypeDef* SPIx, uint32_t DivVal, FunctionalState DivState);
void RCC_SPIClkCmd(NT_SPI_TypeDef* SPIx, FunctionalState State);

/**
  * @}
  */

/** @defgroup RCC_CLK_Config_ADC ������������ ADC
  * @{
  */

void RCC_ADCClkDivConfig(RCC_ADCClk_TypeDef RCC_ADCClk, uint32_t DivVal, FunctionalState DivState);
void RCC_ADCClkCmd(RCC_ADCClk_TypeDef RCC_ADCClk, FunctionalState State);

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCC_RST_Config ���������� �������
  * @{
  */

void RCC_PeriphRstCmd(RCC_PeriphRst_TypeDef RCC_PeriphRst, FunctionalState State);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __NIIETCM4_RCC_H */

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
