/**
  ******************************************************************************
  * @file    niietcm4_gpio.c
  *
  * @brief   ���� �������� ���������� ���� ������� ��� ������ � �������� GPIO
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

/* Includes ------------------------------------------------------------------*/
#ifdef RELPATH
    #include "main.h"
#else
    #include "../inc/main.h"
#endif
/** @addtogroup Peripheral
  * @{
  */

/** @defgroup GPIO 
  * @brief ������� ��� ���������� ������� �����-������.
  *
  * @attention ���������� ��������� �������� ������ �������������� ������� ���
  *   ����� �����-���� ���������. ���� ���� � �� �� ������� ��������� �����������
  *   �� ������ ������ ��� ������� ��������������� ��������� (�������� RX � UART),
  *   �� ��������� ����� �������� ������� � ���������� �������. ������� �����
  *   �������� ������� �������� �� ������, ���������� ���� � ��������������� ���������
  *   � �������� �������� ���������������� �� �������������� ������� � �������
  *   ������� ���� ������ ��������. ��������� ���� ������ ������� � ��, � ����� �������
  *   � �������� ������ ���� �� UART.
  *
  *  ����� ��� �������� �������������:
  *  - �������������� ����������� ������ ����� � �� ���� (@ref GPIO_Init_Deinit);
  *  - (�����������) ������������ ���������� �������� ������� (@ref GPIO_Qualifier);
  *  - (�����������) ����������� � �������� ���������� (@ref GPIO_Interrupts);
  *  - ����� �����-������ ������ � ������.
  *
  *  ����� �������� ������������� � ������������� ������ �������� � ����������� � �������� ��������.
  *  ������� ������������� �������������� ������� ����� ����� � �������� ������ � ������ ����������,
  *  ������� ���������� ����� ��� ����������������.
  * @{
  */ 

/** @defgroup GPIO_Private ��������� ������
  * @{
  */

/** @defgroup GPIO_Private_Defines ��������� ���������
  * @{
  */

/** @defgroup GPIO_regs_reset_define ��������� �������� ���������
  * @{
  */

#define GPIO_DATAOUT_Reset_Value        ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� DATAOUT */
#define GPIO_GPIODEN0_Reset_Value       ((uint32_t)0x00020062)  /*!< �������� �� ������ �������� GPIODEN0 */
#define GPIO_GPIODEN1_Reset_Value       ((uint32_t)0x08000000)  /*!< �������� �� ������ �������� GPIODEN1 */
#define GPIO_GPIODEN2_Reset_Value       ((uint32_t)0x00000400)  /*!< �������� �� ������ �������� GPIODEN2 */
#define GPIO_GPIODEN3_Reset_Value       ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� GPIODEN3 */
#define GPIO_GPIOODCTLx_Reset_Value     ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� GPIOODCTLx */
#define GPIO_GPIOODSCTLx_Reset_Value    ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� GPIOODSCTLx */
#define GPIO_GPIOPUCTLx_Reset_Value     ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� GPIOPUCTLx */
#define GPIO_GPIOSEx_Reset_Value        ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� GPIOSEx */
#define GPIO_GPIOQEx_Reset_Value        ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� GPIOQEx */
#define GPIO_GPIOQMx_Reset_Value        ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� GPIOQMx */
#define GPIO_GPIOPCTLx_Reset_Value      ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� GPIOPCLTx */
#define GPIO_GPIOQPx_Reset_Value        ((uint32_t)0x00000000)  /*!< �������� �� ������ �������� GPIOQPx */

/**
  * @}
  */

/** @defgroup GPIO_regs_ports_mask ����� ������
  * @{
  */

#define GPIO_Regs_A_C_E_G_Mask        ((uint32_t)0x0000FFFF)  /*!< ����� ��������� ��� �������� ������ */
#define GPIO_Regs_B_D_F_H_Mask        ((uint32_t)0xFFFF0000)  /*!< ����� ��������� ��� ������ ������ */
#define GPIO_Regs_GPIOA_Mask          ((uint32_t)0x0000FFFF)  /*!< ����� ��������� ��� ����� GPIOA */
#define GPIO_Regs_GPIOB_Mask          ((uint32_t)0xFFFF0000)  /*!< ����� ��������� ��� ����� GPIOB */
#define GPIO_Regs_GPIOC_Mask          ((uint32_t)0x0000FFFF)  /*!< ����� ��������� ��� ����� GPIOC */
#define GPIO_Regs_GPIOD_Mask          ((uint32_t)0xFFFF0000)  /*!< ����� ��������� ��� ����� GPIOD */
#define GPIO_Regs_GPIOE_Mask          ((uint32_t)0x0000FFFF)  /*!< ����� ��������� ��� ����� GPIOE */
#define GPIO_Regs_GPIOF_Mask          ((uint32_t)0xFFFF0000)  /*!< ����� ��������� ��� ����� GPIOF */
#define GPIO_Regs_GPIOG_Mask          ((uint32_t)0x0000FFFF)  /*!< ����� ��������� ��� ����� GPIOG */
#define GPIO_Regs_GPIOH_Mask          ((uint32_t)0xFFFF0000)  /*!< ����� ��������� ��� ����� GPIOH */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIO_Private_Functions ��������� �������
  * @{
  */

/**
  * @brief  ������������� ��� �������� ���������� GPIOx ���������� �� ���������.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @retval ���
  */

void GPIO_DeInit(NT_GPIO_TypeDef* GPIOx)
{
    uint32_t reg_port_mask;
    uint32_t gpioqp_port_mask;
    uint32_t gpiodenx_reset_value;
    __IO uint32_t* GPIODENx;
    __IO uint32_t* GPIOODCTLx;
    __IO uint32_t* GPIOODSCTLx;
    __IO uint32_t* GPIOPUCTLx;
    __IO uint32_t* GPIOSEx;
    __IO uint32_t* GPIOQEx;
    __IO uint32_t* GPIOQMx;
    __IO uint32_t* GPIOPCTLx;
    __IO uint32_t* GPIOQPx;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Preparation routine */
    if ((GPIOx == NT_GPIOA) || (GPIOx == NT_GPIOC) ||
        (GPIOx == NT_GPIOE) || (GPIOx == NT_GPIOG))
    {
        reg_port_mask = GPIO_Regs_A_C_E_G_Mask;
    }
    else /* ((GPIOx == NT_GPIOB) || (GPIOx == NT_GPIOD) ||
             (GPIOx == NT_GPIOF) || (GPIOx == NT_GPIOH)) */
    {
        reg_port_mask = GPIO_Regs_B_D_F_H_Mask;
    }

    if ((GPIOx == NT_GPIOA) || (GPIOx == NT_GPIOB))
    {
        GPIODENx = &(NT_COMMON_REG->GPIODEN0);
        gpiodenx_reset_value = GPIO_GPIODEN0_Reset_Value;
        GPIOODCTLx = &(NT_COMMON_REG->GPIOODCTL0);
        GPIOODSCTLx = &(NT_COMMON_REG->GPIOODSCTL0);
        GPIOPUCTLx = &(NT_COMMON_REG->GPIOPUCTL0);
        GPIOSEx = &(NT_COMMON_REG->GPIOSE0);
        GPIOQEx = &(NT_COMMON_REG->GPIOQE0);
        GPIOQMx = &(NT_COMMON_REG->GPIOQM0);
        GPIOQPx = &(NT_COMMON_REG->GPIOQPAD);
        if (GPIOx == NT_GPIOA)
        {
            GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLA);
            gpioqp_port_mask = COMMON_REG_GPIOQPAD_SPRDA_Msk;
        }
        else /* (GPIOx == NT_GPIOB) */
        {
            GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLB);
            gpioqp_port_mask = COMMON_REG_GPIOQPAD_SPRDB_Msk;
        }
    }
    else if ((GPIOx == NT_GPIOC) || (GPIOx == NT_GPIOD))
    {
        GPIODENx = &(NT_COMMON_REG->GPIODEN1);
        gpiodenx_reset_value = GPIO_GPIODEN1_Reset_Value;
        GPIOODCTLx = &(NT_COMMON_REG->GPIOODCTL1);
        GPIOODSCTLx = &(NT_COMMON_REG->GPIOODSCTL1);
        GPIOPUCTLx = &(NT_COMMON_REG->GPIOPUCTL1);
        GPIOSEx = &(NT_COMMON_REG->GPIOSE1);
        GPIOQEx = &(NT_COMMON_REG->GPIOQE1);
        GPIOQMx = &(NT_COMMON_REG->GPIOQM1);
        GPIOQPx = &(NT_COMMON_REG->GPIOQPAD);
        if (GPIOx == NT_GPIOC)
        {
            GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLC);
            gpioqp_port_mask = COMMON_REG_GPIOQPAD_SPRDC_Msk;
        }
        else /* (GPIOx == NT_GPIOD) */
        {
            GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLD);
            gpioqp_port_mask = COMMON_REG_GPIOQPAD_SPRDD_Msk;
        }
    }
    else if ((GPIOx == NT_GPIOE) || (GPIOx == NT_GPIOF))
    {
        GPIODENx = &(NT_COMMON_REG->GPIODEN2);
        gpiodenx_reset_value = GPIO_GPIODEN2_Reset_Value;
        GPIOODCTLx = &(NT_COMMON_REG->GPIOODCTL2);
        GPIOODSCTLx = &(NT_COMMON_REG->GPIOODSCTL2);
        GPIOPUCTLx = &(NT_COMMON_REG->GPIOPUCTL2);
        GPIOSEx = &(NT_COMMON_REG->GPIOSE2);
        GPIOQEx = &(NT_COMMON_REG->GPIOQE2);
        GPIOQMx = &(NT_COMMON_REG->GPIOQM2);
        GPIOQPx = &(NT_COMMON_REG->GPIOQPEH);
        if (GPIOx == NT_GPIOE)
        {
            GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLE);
            gpioqp_port_mask = COMMON_REG_GPIOQPEH_SPRDE_Msk;
        }
        else /* (GPIOx == NT_GPIOF) */
        {
            GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLF);
            gpioqp_port_mask = COMMON_REG_GPIOQPEH_SPRDF_Msk;
        }
    }
    else /* ((GPIOx == NT_GPIOG) || (GPIOx == NT_GPIOH)) */
    {
        GPIODENx = &(NT_COMMON_REG->GPIODEN3);
        gpiodenx_reset_value = GPIO_GPIODEN3_Reset_Value;
        GPIOODCTLx = &(NT_COMMON_REG->GPIOODCTL3);
        GPIOODSCTLx = &(NT_COMMON_REG->GPIOODSCTL3);
        GPIOPUCTLx = &(NT_COMMON_REG->GPIOPUCTL3);
        GPIOSEx = &(NT_COMMON_REG->GPIOSE3);
        GPIOQEx = &(NT_COMMON_REG->GPIOQE3);
        GPIOQMx = &(NT_COMMON_REG->GPIOQM3);
        GPIOQPx = &(NT_COMMON_REG->GPIOQPEH);
        if (GPIOx == NT_GPIOG)
        {
            GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLG);
            gpioqp_port_mask = COMMON_REG_GPIOQPEH_SPRDG_Msk;
        }
        else /* (GPIOx == NT_GPIOH) */
        {
            GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLH);
            gpioqp_port_mask = COMMON_REG_GPIOQPEH_SPRDH_Msk;
        }
    }
    /* Reset all port regs and bit fields */
    GPIOx->DATAOUT = GPIO_DATAOUT_Reset_Value;
    GPIOx->OUTENCLR = ((uint32_t)0xFFFFFFFF);
    GPIOx->ALTFUNCCLR = ((uint32_t)0xFFFFFFFF);
    GPIOx->INTENCLR = ((uint32_t)0xFFFFFFFF);
    GPIOx->INTTYPECLR = ((uint32_t)0xFFFFFFFF);
    GPIOx->INTPOLCLR = ((uint32_t)0xFFFFFFFF);
    GPIOx->INTSTATUS = ((uint32_t)0xFFFFFFFF);
    *GPIODENx &= ~reg_port_mask;
    *GPIODENx |= (gpiodenx_reset_value & reg_port_mask);
    *GPIOODCTLx &= ~reg_port_mask;
    *GPIOODCTLx |= (GPIO_GPIOODCTLx_Reset_Value & reg_port_mask);
    *GPIOODSCTLx &= ~reg_port_mask;
    *GPIOODSCTLx |= (GPIO_GPIOODSCTLx_Reset_Value & reg_port_mask);
    *GPIOPUCTLx &= ~reg_port_mask;
    *GPIOPUCTLx |= (GPIO_GPIOPUCTLx_Reset_Value & reg_port_mask);
    *GPIOSEx &= ~reg_port_mask;
    *GPIOSEx |= (GPIO_GPIOSEx_Reset_Value & reg_port_mask);
    *GPIOQEx &= ~reg_port_mask;
    *GPIOQEx |= (GPIO_GPIOQEx_Reset_Value & reg_port_mask);
    *GPIOQMx &= ~reg_port_mask;
    *GPIOQMx |= (GPIO_GPIOQMx_Reset_Value & reg_port_mask);
    *GPIOPCTLx = GPIO_GPIOPCTLx_Reset_Value;
    *GPIOQPx &= ~gpioqp_port_mask;
    *GPIOQPx |= (GPIO_GPIOQPx_Reset_Value & gpioqp_port_mask);
}

/**
  * @brief  ������������ ����� �������������� ������� ������ GPIOx.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @param  GPIO_AltFunc  ����� ������ �������������� ������� ����.
  *   �������� ��������� ����� �������� �� @ref GPIO_AltFunc_TypeDef.
  * @retval ���
  */

void GPIO_AltFuncConfig(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIO_AltFunc_TypeDef GPIO_AltFunc)
{
    uint32_t alt_func_temp;
    __IO uint32_t* GPIOPCTLx;

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_ALT_FUNC(GPIO_AltFunc));

    if (GPIOx == NT_GPIOA)
    {
        GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLA);
    }
    else if (GPIOx == NT_GPIOB)
    {
        GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLB);
    }
    else if (GPIOx == NT_GPIOC)
    {
        GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLC);
    }
    else if (GPIOx == NT_GPIOD)
    {
        GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLD);
    }
    else if (GPIOx == NT_GPIOE)
    {
        GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLE);
    }
    else if (GPIOx == NT_GPIOF)
    {
        GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLF);
    }
    else if (GPIOx == NT_GPIOG)
    {
        GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLG);
    }
    else /* (GPIOx == NT_GPIOH) */
    {
        GPIOPCTLx = &(NT_COMMON_REG->GPIOPCTLH);
    }

    alt_func_temp = *GPIOPCTLx;
    for (uint32_t i = 0; i < 16; i++)
    {
        if (GPIO_Pin & (1<<i))
        {
            alt_func_temp &= ~(3 << i*2);
            alt_func_temp |= GPIO_AltFunc << i*2;
        }
    }
    *GPIOPCTLx = alt_func_temp;
}

/**
  * @brief  �������������� ������ GPIOx �������� ���������� ��������� GPIO_InitStruct.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_InitStruct ��������� �� ��������� ���� @ref GPIO_Init_TypeDef,
  *         ������� �������� ���������������� ����������.
  * @retval ���
  */

void GPIO_Init(NT_GPIO_TypeDef* GPIOx, GPIO_Init_TypeDef* GPIO_InitStruct)
{
    uint32_t port_offset;
    __IO uint32_t* GPIOODSCTLx;
    __IO uint32_t* GPIOPUCTLx;
    __IO uint32_t* GPIOODCTLx;
    __IO uint32_t* GPIODENx;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    assert_param(IS_GPIO_DIR(GPIO_InitStruct->GPIO_Dir));
    assert_param(IS_GPIO_OUT(GPIO_InitStruct->GPIO_Out));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
    assert_param(IS_GPIO_ALT_FUNC(GPIO_InitStruct->GPIO_AltFunc));
    assert_param(IS_GPIO_LOAD(GPIO_InitStruct->GPIO_Load));
    assert_param(IS_GPIO_OUT_MODE(GPIO_InitStruct->GPIO_OutMode));
    assert_param(IS_GPIO_PULLUP(GPIO_InitStruct->GPIO_PullUp));

    /* Preparation routine */
    if ((GPIOx == NT_GPIOA) || (GPIOx == NT_GPIOC) ||
        (GPIOx == NT_GPIOE) || (GPIOx == NT_GPIOG))
    {
        port_offset = 0;
    }
    else /* ((GPIOx == NT_GPIOB) || (GPIOx == NT_GPIOD) ||
             (GPIOx == NT_GPIOF) || (GPIOx == NT_GPIOH)) */
    {
        port_offset = 16;
    }

    if ((GPIOx == NT_GPIOA) || (GPIOx == NT_GPIOB))
    {
        GPIOODSCTLx = &(NT_COMMON_REG->GPIOODSCTL0);
        GPIOPUCTLx = &(NT_COMMON_REG->GPIOODSCTL0);
        GPIOODCTLx = &(NT_COMMON_REG->GPIOODCTL0);
        GPIODENx = &(NT_COMMON_REG->GPIODEN0);
    }
    else if ((GPIOx == NT_GPIOC) || (GPIOx == NT_GPIOD))
    {
        GPIOODSCTLx = &(NT_COMMON_REG->GPIOODSCTL1);
        GPIOPUCTLx = &(NT_COMMON_REG->GPIOODSCTL1);
        GPIOODCTLx = &(NT_COMMON_REG->GPIOODCTL1);
        GPIODENx = &(NT_COMMON_REG->GPIODEN1);
    }
    else if ((GPIOx == NT_GPIOE) || (GPIOx == NT_GPIOF))
    {
        GPIOODSCTLx = &(NT_COMMON_REG->GPIOODSCTL2);
        GPIOPUCTLx = &(NT_COMMON_REG->GPIOODSCTL2);
        GPIOODCTLx = &(NT_COMMON_REG->GPIOODCTL2);
        GPIODENx = &(NT_COMMON_REG->GPIODEN2);
    }
    else /* ((GPIOx == NT_GPIOG) || (GPIOx == NT_GPIOH)) */
    {
        GPIOODSCTLx = &(NT_COMMON_REG->GPIOODSCTL3);
        GPIOPUCTLx = &(NT_COMMON_REG->GPIOODSCTL3);
        GPIOODCTLx = &(NT_COMMON_REG->GPIOODCTL3);
        GPIODENx = &(NT_COMMON_REG->GPIODEN3);
    }

    /* Init routine */
    GPIO_AltFuncConfig(GPIOx, GPIO_InitStruct->GPIO_Pin, GPIO_InitStruct->GPIO_AltFunc);

    if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IO)
    {
        GPIOx->ALTFUNCCLR = GPIO_InitStruct->GPIO_Pin;
    }
    else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AltFunc)
    {
        GPIOx->ALTFUNCSET = GPIO_InitStruct->GPIO_Pin;
    }

    if (GPIO_InitStruct->GPIO_Dir == GPIO_Dir_In)
    {
        GPIOx->OUTENCLR = GPIO_InitStruct->GPIO_Pin;
    }
    else if (GPIO_InitStruct->GPIO_Dir == GPIO_Dir_Out)
    {
        GPIOx->OUTENSET = GPIO_InitStruct->GPIO_Pin;
    }

    if (GPIO_InitStruct->GPIO_Load == GPIO_Load_8mA)
    {
        *GPIOODSCTLx &= ~(GPIO_InitStruct->GPIO_Pin << port_offset);
    }
    else if (GPIO_InitStruct->GPIO_Load == GPIO_Load_16mA)
    {
        *GPIOODSCTLx |= (GPIO_InitStruct->GPIO_Pin << port_offset);
    }

    if (GPIO_InitStruct->GPIO_PullUp == GPIO_PullUp_Dis)
    {
        *GPIOPUCTLx &= ~(GPIO_InitStruct->GPIO_Pin << port_offset);
    }
    else if (GPIO_InitStruct->GPIO_PullUp == GPIO_PullUp_En)
    {
        *GPIOPUCTLx |= (GPIO_InitStruct->GPIO_Pin << port_offset);
    }

    if (GPIO_InitStruct->GPIO_OutMode == GPIO_OutMode_PP)
    {
        *GPIOODCTLx &= ~(GPIO_InitStruct->GPIO_Pin << port_offset);
    }
    else if (GPIO_InitStruct->GPIO_OutMode == GPIO_OutMode_OD)
    {
        *GPIOODCTLx |= (GPIO_InitStruct->GPIO_Pin << port_offset);
    }

    if (GPIO_InitStruct->GPIO_Out == GPIO_Out_Dis)
    {
        *GPIODENx &= ~(GPIO_InitStruct->GPIO_Pin << port_offset);
    }
    else if (GPIO_InitStruct->GPIO_Out == GPIO_Out_En)
    {
        *GPIODENx |= (GPIO_InitStruct->GPIO_Pin << port_offset);
    }
}

/**
  * @brief  ���������� ������� ����� ��������� GPIO_InitStruct ���������� �� ���������.
  * @param  GPIO_InitStruct ��������� �� ��������� ���� @ref GPIO_Init_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void GPIO_StructInit(GPIO_Init_TypeDef* GPIO_InitStruct)
{
    /* Reset GPIO init structure parameters values */
    GPIO_InitStruct->GPIO_AltFunc = GPIO_AltFunc_1;
    GPIO_InitStruct->GPIO_Dir = GPIO_Dir_In;
    GPIO_InitStruct->GPIO_Load = GPIO_Load_8mA;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IO;
    GPIO_InitStruct->GPIO_Out = GPIO_Out_Dis;
    GPIO_InitStruct->GPIO_OutMode = GPIO_OutMode_PP;
    GPIO_InitStruct->GPIO_PullUp = GPIO_PullUp_Dis;
    GPIO_InitStruct->GPIO_Pin = GPIO_Pin_All;
}

/**
  * @brief  ������ ��������� ���������� ����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @retval "��������� ���������� ����"
  */

uint32_t GPIO_ReadBit(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    uint32_t bitval;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->DATA & GPIO_Pin) != (uint32_t)Bit_CLEAR)
    {
        bitval = (uint32_t)Bit_SET;
    }
    else
    {
        bitval = (uint32_t)Bit_CLEAR;
    }

    return bitval;
}

/**
  * @brief  ������ ��������� ���������� ����� GPIOx.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @retval "��������� ����� GPIOx"
  */

uint32_t GPIO_Read(NT_GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint32_t)GPIOx->DATA);
}

/**
  * @brief  ������ ��������� ���������� ����� GPIOx c �������������� �����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  MaskVal �������� ����� ������.
  * @retval "��������� ����� GPIOx � ������ �����"
  */

uint32_t GPIO_ReadMask(NT_GPIO_TypeDef* GPIOx, uint32_t MaskVal)
{
    uint32_t mask_low_byte_offset;
    uint32_t mask_high_byte_offset;
    uint32_t low_byte;
    uint32_t high_byte;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    mask_low_byte_offset = (MaskVal & GPIO_MASKLOWBYTE_MASKLB_Msk) >> GPIO_MASKLOWBYTE_MASKLB_Pos;
    mask_high_byte_offset = (MaskVal & GPIO_MASKHIGHBYTE_MASKHB_Msk) >> GPIO_MASKHIGHBYTE_MASKHB_Pos;
    low_byte = GPIOx->MASKLOWBYTE[mask_low_byte_offset];
    high_byte = GPIOx->MASKHIGHBYTE[mask_high_byte_offset];

    return ((low_byte | high_byte));
}

/**
  * @brief  ��������� ��������� ���������� ����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @param  BitVal �������� ������� ����� ��������.
  *   �������� ����� ��������� ����� �������� �� @ref BitAction.
  * @retval ���
  */

void GPIO_WriteBit(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, BitAction BitVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_BIT_ACTION(BitVal));

    if (BitVal == Bit_SET)
    {
        GPIOx->DATAOUT |= GPIO_Pin;
    }
    else if (BitVal == Bit_CLEAR)
    {
        GPIOx->DATAOUT &= ~GPIO_Pin;
    }
}

/**
  * @brief  ��������� ��������� ���������� ����� GPIOx.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  PortVal �������� ������� ����� ��������.
  * @retval ���
  */

void GPIO_Write(NT_GPIO_TypeDef* GPIOx, uint32_t PortVal)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->DATAOUT = PortVal;
}

/**
  * @brief  ��������� ��������� ���������� ����� GPIOx � �������������� �����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  MaskVal �������� �����.
  * @param  PortVal �������� ������� ����� ��������.
  * @retval ���
  */

void GPIO_WriteMask(NT_GPIO_TypeDef* GPIOx, uint32_t MaskVal, uint32_t PortVal)
{
    uint32_t mask_low_byte_offset;
    uint32_t mask_high_byte_offset;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    mask_low_byte_offset = (MaskVal & GPIO_MASKLOWBYTE_MASKLB_Msk) >> GPIO_MASKLOWBYTE_MASKLB_Pos;
    mask_high_byte_offset = (MaskVal & GPIO_MASKHIGHBYTE_MASKHB_Msk) >> GPIO_MASKHIGHBYTE_MASKHB_Pos;
    GPIOx->MASKLOWBYTE[mask_low_byte_offset] = PortVal;
    GPIOx->MASKHIGHBYTE[mask_high_byte_offset] = PortVal;
}


/**
  * @brief  ��������� ��������� �����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @retval ���
  */

void GPIO_SetBits(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->DATAOUT |= GPIO_Pin;
}

/**
  * @brief  ����� ��������� �����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @retval ���
  */

void GPIO_ClearBits(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->DATAOUT &= ~GPIO_Pin;
}

/**
  * @brief  ������������ ��������� ����� � ��������������� ���������.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @retval ���
  */

void GPIO_ToggleBits(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->DATAOUT ^= GPIO_Pin;
}

/**
  * @brief  ��������� ������� ��������� �����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @param  Mode  ����� ������ ������.
  *   �������� ����� ��������� ����� �������� �� @ref GPIO_QualMode_TypeDef.
  * @param  SamplePerod  ���������� ������ ��������� ������� ����� ��������� �������.
  *   �������� ��������� ����� �������� �� ��������� 0...255.
  * @retval ���
  */

void GPIO_QualConfig(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIO_QualMode_TypeDef Mode, uint32_t SamplePerod)
{
    uint32_t gpioqp_port_pos;
    __IO uint32_t* GPIOQMx;
    __IO uint32_t* GPIOQPx;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_QUAL_MODE(Mode));
    assert_param(IS_GPIO_QUAL_PERIOD(SamplePerod));

    /* Preparation routine */
    if ((GPIOx == NT_GPIOA) || (GPIOx == NT_GPIOB))
    {
        GPIOQMx = &(NT_COMMON_REG->GPIOQM0);
        GPIOQPx = &(NT_COMMON_REG->GPIOQPAD);
        if (GPIOx == NT_GPIOA)
        {
            gpioqp_port_pos = COMMON_REG_GPIOQPAD_SPRDA_Pos;
        }
        else /* (GPIOx == NT_GPIOB) */
        {
            gpioqp_port_pos = COMMON_REG_GPIOQPAD_SPRDB_Pos;
        }
    }
    else if ((GPIOx == NT_GPIOC) || (GPIOx == NT_GPIOD))
    {
        GPIOQMx = &(NT_COMMON_REG->GPIOQM1);
        GPIOQPx = &(NT_COMMON_REG->GPIOQPAD);
        if (GPIOx == NT_GPIOC)
        {
            gpioqp_port_pos = COMMON_REG_GPIOQPAD_SPRDC_Pos;
        }
        else /* (GPIOx == NT_GPIOD) */
        {
            gpioqp_port_pos = COMMON_REG_GPIOQPAD_SPRDD_Pos;
        }
    }
    else if ((GPIOx == NT_GPIOE) || (GPIOx == NT_GPIOF))
    {
        GPIOQMx = &(NT_COMMON_REG->GPIOQM2);
        GPIOQPx = &(NT_COMMON_REG->GPIOQPEH);
        if (GPIOx == NT_GPIOE)
        {
            gpioqp_port_pos = COMMON_REG_GPIOQPEH_SPRDE_Pos;
        }
        else /* (GPIOx == NT_GPIOF) */
        {
            gpioqp_port_pos = COMMON_REG_GPIOQPEH_SPRDF_Pos;
        }
    }
    else /* ((GPIOx == NT_GPIOG) || (GPIOx == NT_GPIOH)) */
    {
        GPIOQMx = &(NT_COMMON_REG->GPIOQM3);
        GPIOQPx = &(NT_COMMON_REG->GPIOQPEH);
        if (GPIOx == NT_GPIOG)
        {
            gpioqp_port_pos = COMMON_REG_GPIOQPEH_SPRDG_Pos;
        }
        else /* (GPIOx == NT_GPIOH) */
        {
            gpioqp_port_pos = COMMON_REG_GPIOQPEH_SPRDH_Pos;
        }
    }

    /* Config procedure */
    if (Mode == GPIO_QualMode_3sample)
    {
        *GPIOQMx &= ~GPIO_Pin;
    }
    else if (Mode == GPIO_QualMode_6sample)
    {
        *GPIOQMx |= GPIO_Pin;
    }

    *GPIOQPx = SamplePerod << gpioqp_port_pos;
}

/**
  * @brief  ��������� ������� ��������.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void GPIO_QualCmd(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState State)
{
    uint32_t port_offset;
    __IO uint32_t* GPIOQEx;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    assert_param(IS_FUNCTIONAL_STATE(State));

    /* Preparation routine */
    if ((GPIOx == NT_GPIOA) || (GPIOx == NT_GPIOC) ||
        (GPIOx == NT_GPIOE) || (GPIOx == NT_GPIOG))
    {
        port_offset = 0;
    }
    else /* ((GPIOx == NT_GPIOB) || (GPIOx == NT_GPIOD) ||
             (GPIOx == NT_GPIOF) || (GPIOx == NT_GPIOH)) */
    {
        port_offset = 16;
    }

    if ((GPIOx == NT_GPIOA) || (GPIOx == NT_GPIOB))
    {
        GPIOQEx = &(NT_COMMON_REG->GPIOQE0);
    }
    else if ((GPIOx == NT_GPIOB) || (GPIOx == NT_GPIOC))
    {
        GPIOQEx = &(NT_COMMON_REG->GPIOQE1);
    }
    else if ((GPIOx == NT_GPIOD) || (GPIOx == NT_GPIOE))
    {
        GPIOQEx = &(NT_COMMON_REG->GPIOQE2);
    }
    else /* ((GPIOx == NT_GPIOF) || (GPIOx == NT_GPIOG)) */
    {
        GPIOQEx = &(NT_COMMON_REG->GPIOQE3);
    }

    /* Cmd procedure */
    if (State == DISABLE)
    {
        *GPIOQEx &= ~(GPIO_Pin<<port_offset);
    }
    else if (State == ENABLE)
    {
        *GPIOQEx |= GPIO_Pin<<port_offset;
    }
}


/**
  * @brief  ��������� ����������������� ������ ����� 2 ��������-�������.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void GPIO_SyncCmd(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState State)
{
    uint32_t port_offset;
    __IO uint32_t* GPIOSEx;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    assert_param(IS_FUNCTIONAL_STATE(State));

    /* Preparation routine */
    if ((GPIOx == NT_GPIOA) || (GPIOx == NT_GPIOC) ||
        (GPIOx == NT_GPIOE) || (GPIOx == NT_GPIOG))
    {
        port_offset = 0;
    }
    else /* ((GPIOx == NT_GPIOB) || (GPIOx == NT_GPIOD) ||
             (GPIOx == NT_GPIOF) || (GPIOx == NT_GPIOH)) */
    {
        port_offset = 16;
    }

    if ((GPIOx == NT_GPIOA) || (GPIOx == NT_GPIOB))
    {
        GPIOSEx = &(NT_COMMON_REG->GPIOSE0);
    }
    else if ((GPIOx == NT_GPIOB) || (GPIOx == NT_GPIOC))
    {
        GPIOSEx = &(NT_COMMON_REG->GPIOSE1);
    }
    else if ((GPIOx == NT_GPIOD) || (GPIOx == NT_GPIOE))
    {
        GPIOSEx = &(NT_COMMON_REG->GPIOSE2);
    }
    else /* ((GPIOx == NT_GPIOF) || (GPIOx == NT_GPIOG)) */
    {
        GPIOSEx = &(NT_COMMON_REG->GPIOSE3);
    }

    /* Cmd procedure */
    if (State == DISABLE)
    {
        *GPIOSEx &= ~(GPIO_Pin<<port_offset);
    }
    else if (State == ENABLE)
    {
        *GPIOSEx |= GPIO_Pin<<port_offset;
    }
}

/**
  * @brief  ��������� ���������� �����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @param  IntType  ����� ������� ��� ������������� ����������.
  *   �������� ��������� ����� �������� �� @ref GPIO_IntType_TypeDef.
  * @param  IntPol  ����� ���������� ������� ��� ������������� ����������.
  *   �������� ��������� ����� �������� �� @ref GPIO_IntPol_TypeDef.
  * @retval ���
  */

void GPIO_ITConfig(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIO_IntType_TypeDef IntType, GPIO_IntPol_TypeDef IntPol)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_INT_TYPE(IntType));
    assert_param(IS_GPIO_INT_POL(IntPol));

    if (IntType == GPIO_IntType_Level)
    {
        GPIOx->INTTYPECLR = GPIO_Pin;
    }
    else if (IntType == GPIO_IntType_Edge)
    {
        GPIOx->INTTYPESET = GPIO_Pin;
    }

    if (IntPol == GPIO_IntPol_Neg)
    {
        GPIOx->INTPOLCLR = GPIO_Pin;
    }
    else if (IntPol == GPIO_IntPol_Pos)
    {
        GPIOx->INTPOLSET = GPIO_Pin;
    }
}

/**
  * @brief  ��������� ���������� ��������� �����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void GPIO_ITCmd(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, FunctionalState State)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == DISABLE)
    {
        GPIOx->INTENCLR = GPIO_Pin;
    }
    else if (State == ENABLE)
    {
        GPIOx->INTENSET = GPIO_Pin;
    }
}

/**
  * @brief  ������� ������ ���������� ��������� �����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @retval ���
  */

void GPIO_ITStatusClear(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->INTSTATUS = GPIO_Pin;
}

/**
  * @brief  ������ ����� ���������� ��������� �����.
  * @param  GPIOx  ����� �����, ��� x ����� � ��������� A..H.
  * @param  GPIO_Pin  ����� �����.
  *   ���� �������� ����� ��������� ����� �������� �� GPIO_Pin_x, ��� x ����� � ��������� 0..15.
  * @retval Status  ��������� �����. ���� ������� ��������� ����������,
  *   �� ��������� ������������ ����������� ��� �� ���������.
  */

FlagStatus GPIO_ITStatus(NT_GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
    FlagStatus Status;
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    if (GPIOx->INTSTATUS & GPIO_Pin)
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
