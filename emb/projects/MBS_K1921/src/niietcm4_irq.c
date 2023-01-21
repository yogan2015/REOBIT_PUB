/**
  *******************************************************************************
  * @file    niietcm4_irq.�
  *
  * @brief   ���� �������� ���������� ���� ������� ��� ���������� ������������
  *          ���������� �� ����� ���������� ���������
  *
  * @author  ������ ������������, vitkorob@gmail.com
  *
  *          �����
  *             - ������ ������ (bkolbov), kolbov@niiet.ru
  *
  * @date    03.08.2016
  *
  *******************************************************************************
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
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#ifdef RELPATH
    #include "main.h"
#else
    #include "../inc/main.h"
#endif
/** @addtogroup Misc
  * @{
  */

/** @defgroup IRQ
  * @brief ���������� ������������ ���������� �� ����� ���������� ���������
  * @{
  */

/** @defgroup IRQ_Private ��������� ������
  * @{
  */

/** @defgroup IRQ_Private_Macros ��������� �������
  * @{
  */

/**
  * @brief �������� ������������ RAM ������� ��������
  */

#define IS_VECTORS_ALIGNED(VECTORS) (((uint32_t)VECTORS & 0x7f) == 0)

/**
 * @}
 */

/** @defgroup IRQ_Private_Functions ��������� �������
  * @{
  */

#if defined (__ICCARM__)
    #pragma data_alignment=128
    static __no_init void (*Vectors[IRQ_TOTAL])(void) @ "VTABLE";
#elif defined (__GNUC__)
    static __attribute__((section("vtable")))
    void (*Vectors[IRQ_TOTAL])(void) __attribute__((aligned(128)));
#else
    #error "��� ���������� ��� ������ ����������"
#endif

/*
 * This is the default interrupt handler for all interrupts. It simply loops
 * forever so that the system state is preserved for observation by a
 * debugger. Since interrupts should be disabled before unregistering the
 * corresponding handler, this should never be called.
 */
static void IntDefaultHandler(void)
{
    while (1)
    {
        // Capture
    }
}

/**
  * @brief  ��������� ������� ��� ��������� ����������.
  * @attention ��� ������ ������ �������� ������� �������� ���������� � ��� ��, �����
  *   ������ ������ ����������� ����������. ��� ����������� ������� ��������������
  * ������ ������ ������������ ����������.
  * @param  IRQn ������������� ���������.
  * @param  pfnHandler ��������� �� �������.
  * @retval ���
  */

void IRQ_HandlerInit(IRQn_Type IRQn, void (*pfnHandler)(void))
{
    assert_param(IS_IRQ_NUM(IRQn));
    assert_param(IS_VECTORS_ALIGNED(Vectors));

    /*
     * See if the RAM vector table has been initialized.
     */
    if (SCB->VTOR != (uint32_t)Vectors)
    {
        uint32_t *src = (uint32_t *)SCB->VTOR;
        uint32_t *dst = (uint32_t *)Vectors;
        uint32_t n = IRQ_TOTAL;

        /*
         * Copy the vector table from the beginning of FLASH
         * to the RAM vector table.
         */
        while (n--)
            *dst++ = *src++;

        /*
         * Point the NVIC at the RAM vector table.
         */
        SCB->VTOR = (uint32_t)Vectors;
    }

    /*
     * Save the interrupt handler.
     */
    Vectors[IRQ_NUM(IRQn)] = pfnHandler;
}

/**
  * @brief  ��������� �������-�������� (����������� ����) ��� ��������� ����������.
  * @attention ����� ������� ���� ������� ��������������� ���������� ������ ���� ��������������,
  *   ����� ��� ����� �������� � ��������� ���� ��������� ����������������.
  * @param  IRQn ������������� ���������.
  * @retval ���
  */

void IRQ_HandlerDeInit(IRQn_Type IRQn)
{
    assert_param(IS_IRQ_NUM(IRQn));

    /*
     * Reset the interrupt handler.
     */
    Vectors[IRQ_NUM(IRQn)] = IntDefaultHandler;
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
