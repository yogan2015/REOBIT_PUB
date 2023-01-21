/**
  ******************************************************************************
  * @file    niietcm4.h
  *
  * @brief   ��� ������� ������������ ���� ��������, ������ ���������� � main.c.
  *
  *          ���� ���� ��������:
  *           - ������� ������������ ���� �������� ����������, � ��������� ���� ��������� ��� ���������
  *           - ������� ��������� ��������, ������� ��������� ����������������:
  *              - ������ �������� ����������
  *              - ������������ �������� �������
  *           - ������� ��� ������� � ��������� ���������
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

/** @addtogroup NIIETCM4_PeriphDriver ������� ���������
  * @{
  */

#ifndef __NIIETCM4_H
#define __NIIETCM4_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Driver_configuration_section ��������� ��������
  * @{
  */

#if defined (K1921VK01T)
    #include  "K1921BK01T.h"
/*  �����: ����� �������� ������������� ������ ��� �������� ���� ����,
 *         ����� �������� ����������� ���������� ����������� ����� ����.
 *         ��������, ��� GCC ARM ��� �������� ���:
 *         -DK1921VK01T
 */

#else
    #error "�� ������� ������� ���������� (���� niietcm4.h)"
#endif

/**
 * @brief ����������� ������� ������������� �������� ��������� ����������.
 *
 * �����: ����� �������� ������������� ������ ��� �������� ���� ����,
 *        ����� �������� ����������� ���������� ����������� ����� ����.
 *        <br>��������, ��� GCC ARM ��� �������� ���:
 *        <br>-DEXT_OSC_VALUE=16000000<br><br>
 */

#if !defined  EXT_OSC_VALUE
    #define EXT_OSC_VALUE    ((uint32_t)12000000) /*!< ������� �������� ��������� ���������� [��]. */
#endif /* EXT_OSC_VALUE */

/**
 * @brief ����������� ������� ������� ����������� ��������� ����������.
 *
 * �������������� ������������� � ����������� �� ���������� �������� ����������.
 */

#if defined (K1921VK01T)
    #if !defined  INT_OSC_VALUE
        #define INT_OSC_VALUE    ((uint32_t)5000000) /*!< ������� ����������� ��������� ���������� [��]. */
    #endif
#else
    #if !defined  INT_OSC_VALUE
        #define INT_OSC_VALUE    ((uint32_t)8000000) /*!< ������� ����������� ��������� ���������� [��]. */
    #endif /* INT_OSC_VALUE */
#endif

 /**
  * @brief ����������� ��������� �������.
  */

#if !defined (SYSCLK)
    #define SYSCLK    ((uint32_t)90e6) /*!< ������� �������� ��������� ���������� [��]. */
#endif /* EXT_OSC_VALUE */

/**
  * @}
  */



/** @addtogroup Exported_macro �������
  * @{
  */

/**
 * @brief ���������� ��� � ��������.
 */

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

/**
  * @brief �������� ��� � ��������.
  */

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

/**
  * @brief ��������� ��� �� ��������.
  */

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

/**
  * @brief �������� �������� ��������.
  */

#define CLEAR_REG(REG)        ((REG) = (0x0))

/**
  * @brief �������� �������� � �������.
  */

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

/**
  * @brief ��������� �������� �� ��������.
  */

#define READ_REG(REG)         ((REG))

/**
  * @brief �������� �������� �������� �� �����.
  */

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

/** @addtogroup Exported_Types ����
  * @{
  */

/**
  * @brief ��������� ���������� ��������� ���������.
  * ������������ ��� �������� ���������/���������� ������������ ������.
  */

typedef enum
{
    DISABLE = 0,
    ENABLE = 1
}FunctionalState;

/**
   * @brief ������ �������� ���������� ���� @ref FunctionalState.
   */

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

/**
  * @brief ��������� ���� �������� ��� ������� ��� ���������� �����-���� ��������.
  */

typedef enum
{
    OK = 0,
    ERROR = 1
}OperationStatus;

/**
  * @brief ��������� ��������� ��������� ����� ��� ������� ��� �������.
  */

typedef enum
{
    Flag_CLEAR = 0,
    Flag_SET = 1
}FlagStatus;

/**
  * @brief ������ �������� ���������� ���� @ref NT_TIMER_TypeDef.
  */

#define IS_TIMER_ALL_PERIPH(PERIPH) (((PERIPH) == NT_TIMER0) || \
                                     ((PERIPH) == NT_TIMER1) || \
                                     ((PERIPH) == NT_TIMER2))

/**
  * @brief ������ �������� ���������� ���� @ref NT_GPIO_TypeDef.
  */

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == NT_GPIOA) || \
                                    ((PERIPH) == NT_GPIOB) || \
                                    ((PERIPH) == NT_GPIOC) || \
                                    ((PERIPH) == NT_GPIOD) || \
                                    ((PERIPH) == NT_GPIOE) || \
                                    ((PERIPH) == NT_GPIOF) || \
                                    ((PERIPH) == NT_GPIOG) || \
                                    ((PERIPH) == NT_GPIOH))

/**
  * @brief ������ �������� ���������� ���� @ref NT_UART_TypeDef.
  */

#define IS_UART_ALL_PERIPH(PERIPH) (((PERIPH) == NT_UART0) || \
                                    ((PERIPH) == NT_UART1) || \
                                    ((PERIPH) == NT_UART2) || \
                                    ((PERIPH) == NT_UART3))

/**
  * @brief ������ �������� ���������� ���� @ref NT_SPI_TypeDef.
  */

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == NT_SPI0) || \
                                   ((PERIPH) == NT_SPI1) || \
                                   ((PERIPH) == NT_SPI2) || \
                                   ((PERIPH) == NT_SPI3))

/**
  * @brief ������ �������� ���������� ���� @ref NT_CAP_TypeDef.
  */

#define IS_CAP_ALL_PERIPH(PERIPH) (((PERIPH) == NT_CAP0) || \
                                   ((PERIPH) == NT_CAP1) || \
                                   ((PERIPH) == NT_CAP2) || \
                                   ((PERIPH) == NT_CAP3) || \
                                   ((PERIPH) == NT_CAP4) || \
                                   ((PERIPH) == NT_CAP5))

/**
  * @brief ������ �������� ���������� ���� @ref NT_PWM_TypeDef.
  */

#define IS_PWM_ALL_PERIPH(PERIPH) (((PERIPH) == NT_PWM0) || \
                                   ((PERIPH) == NT_PWM1) || \
                                   ((PERIPH) == NT_PWM2) || \
                                   ((PERIPH) == NT_PWM3) || \
                                   ((PERIPH) == NT_PWM4) || \
                                   ((PERIPH) == NT_PWM5) || \
                                   ((PERIPH) == NT_PWM6) || \
                                   ((PERIPH) == NT_PWM7) || \
                                   ((PERIPH) == NT_PWM8))

 /**
   * @brief ������ �������� ���������� ���� @ref NT_PWM_TypeDef, � ������� �������� ����� �������� ����������.
   */

 #define IS_PWM_HR_ALL_PERIPH(PERIPH) (((PERIPH) == NT_PWM0) || \
                                       ((PERIPH) == NT_PWM1) || \
                                       ((PERIPH) == NT_PWM2) || \
                                       ((PERIPH) == NT_PWM3) || \
                                       ((PERIPH) == NT_PWM4) || \
                                       ((PERIPH) == NT_PWM5))

/**
  * @}
  */

/** @addtogroup Peripheral ���������
  * @{
  */

#include "niietcm4_conf.h"

/**
  * @}
  */

/** @defgroup Misc �������������� ������
  * @{
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __NIIETCM4_H */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2015 NIIET *****END OF FILE****/
