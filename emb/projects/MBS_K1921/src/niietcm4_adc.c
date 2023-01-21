/**
  ******************************************************************************
  * @file    niietcm4_adc.c
  *
  * @brief   ���� �������� ���������� ���� ������� ��� ������ � �������� ���, 
  *          ������������, ��������� �������������.
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

/* Includes ------------------------------------------------------------------*/
#ifdef RELPATH
    #include "main.h"
#else
    #include "../inc/main.h"
#endif



/** @addtogroup Peripheral
  * @{
  */

/** @defgroup ADC 
  * @brief ������� ��� ������� ���, ���������  � ���� �����������, � �����
  *   �������� ������������.
  *
  * @attention ������� ��������� ��������� ������ ����������� ����������� ������� ���.
  *            ��������� ������������ ���������� ����������� ��������
  *            � ������� ������ @ref RCC :
  *            <br>- @ref RCC_CLK_Config_ADC.
  *
  * @attention ��� ����������� ���������������� ���, ����� ������� ��� ������ ���������� �������� �������� �� ��� ���� ������ ������,
  *  ������������� � ��������� �����������, ����������� �������� 0x18-0x1F.
  *  � ����� ������ ��������, ��� ����� ����� �������, ������ �������  @ref ADC_DC_DeInit() ���
  *  ������� �����������.
  *
  * @attention ������� �� ��������� ������������� �������� �� ���� �������� ����������� ������� ��� ������������.
  *   ����������� ������������� �������� �������� ����� 2. ���� ������������ ���� ���������, ���� ���������,
  *   ������������� ������ ��������� - ������ �������� ����� ������. ���� ������������ ������ ������
  *   ���������� � �������� ��������� ��� ����������, �� ������ �� ��� ������ ����� �������� ��� �������
  *   � 2 ����� ����� �������������.
  *
  * @attention ������������ ������������� ������������ ������ ���� ���������, ���� ��������� �����������,
  *   �� ���������� ������ ��������� (���� �������� �������, ���������� �������� �����������).
  *
  *  ����� ��� �������� �������������:
  *  - ��� ���� ������������ �������� ������� ��������������� @ref ADC_DC_DeInit(),
  *    ����� �������� � ������� ������ ������, ������������� � �����������, ����������� ��������;
  *  - (�����������) �������������� �������� ����������� (@ref ADC_Exported_Functions_Init >> @ref ADC_Exported_Functions_Init_DC);
  *  - �������������� ����������� ������ ��� (@ref ADC_Exported_Functions_Init >> @ref ADC_Exported_Functions_Init_ADC);
  *  - �������������� ������ ���������� ����������� (@ref ADC_Exported_Functions_Init >> @ref ADC_Exported_Functions_Init_SEQ);
  *  - (�����������) ������������ � ������� ������� ������ � DMA ��� ����������� � ������� @ref ADC_Exported_Functions_DMA;
  *  - (�����������) ����������� � �������� ���������� �������� ������������ � ����������� ����� @ref ADC_Exported_Functions_Int;
  *  - �������� ����������;
  *  - ��� ����� ��������� ��������� �� ��������.
  *
  *  ����� �������� ������������� � ������������� ��� �������� � ����������� � �������� ��������.
  * @{
  */ 

/** @defgroup ADC_Private ��������� ������
  * @{
  */

/** @defgroup ADC_Private_Defines ��������� ���������
  * @{
  */

/** @defgroup ADC_regs_reset_define ��������� �������� ���������
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADC_Private_Functions ��������� �������
  * @{
  */

/**
  * @brief  ��������� ������ ���.
  * @param  ADC_Module  ����� ���.
  *   �������� ��������� ����� �������� �� @ref ADC_Module_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void ADC_Cmd(ADC_Module_TypeDef ADC_Module, FunctionalState State)
{
    assert_param(IS_ADC_MODULE(ADC_Module));
    assert_param(IS_FUNCTIONAL_STATE(State));

    NT_ADC->PP_bit[(uint32_t)ADC_Module].ENA = (uint32_t)State;
}

/**
  * @brief  ������������� ��� �������� ������ ��� ���������� �� ���������.
  * @param  ADC_Module  ����� ������ ���.
  *   �������� ��������� ����� �������� �� @ref ADC_Module_TypeDef.
  * @retval ���
  */

void ADC_DeInit(ADC_Module_TypeDef ADC_Module)
{
    assert_param(IS_ADC_MODULE(ADC_Module));

    if (ADC_Module == ADC_Module_0)
    {
        NT_ADC->SPC0_bit.PHASE0 = 0;
        NT_ADC->SAC_bit.AVG0 = 0;
    }
    else if (ADC_Module == ADC_Module_1)
    {
        NT_ADC->SPC0_bit.PHASE1 = 0;
        NT_ADC->SAC_bit.AVG1 = 0;
    }
    else if (ADC_Module == ADC_Module_2)
    {
        NT_ADC->SPC1_bit.PHASE2 = 0;
        NT_ADC->SAC_bit.AVG2 = 0;
    }
    else if (ADC_Module == ADC_Module_3)
    {
        NT_ADC->SPC1_bit.PHASE3 = 0;
        NT_ADC->SAC_bit.AVG3 = 0;
    }
    else if (ADC_Module == ADC_Module_4)
    {
        NT_ADC->SPC2_bit.PHASE4 = 0;
        NT_ADC->SAC_bit.AVG4 = 0;
    }
    else if (ADC_Module == ADC_Module_5)
    {
        NT_ADC->SPC2_bit.PHASE5 = 0;
        NT_ADC->SAC_bit.AVG5 = 0;
    }
    else if (ADC_Module == ADC_Module_6)
    {
        NT_ADC->SPC3_bit.PHASE6 = 0;
        NT_ADC->SAC_bit.AVG6 = 0;
    }
    else if (ADC_Module == ADC_Module_7)
    {
        NT_ADC->SPC3_bit.PHASE7 = 0;
        NT_ADC->SAC_bit.AVG7 = 0;
    }
    else if (ADC_Module == ADC_Module_8)
    {
        NT_ADC->SPC4_bit.PHASE8 = 0;
        NT_ADC->RICNT_bit.AVG8 = 0;
    }
    else if (ADC_Module == ADC_Module_9)
    {
        NT_ADC->SPC4_bit.PHASE9 = 0;
        NT_ADC->RICNT_bit.AVG9 = 0;
    }
    else if (ADC_Module == ADC_Module_10)
    {
        NT_ADC->SPC5_bit.PHASE10 = 0;
        NT_ADC->RICNT_bit.AVG10 = 0;
    }
    else if (ADC_Module == ADC_Module_11)
    {
        NT_ADC->SPC5_bit.PHASE11 = 0;
        NT_ADC->RICNT_bit.AVG11 = 0;
    }

    NT_ADC->PP_bit[(uint32_t)ADC_Module].OM = 0;
}

/**
  * @brief  �������������� ��������� ������ ��� �������� ���������� ��������� ADC_InitStruct.
  * @param  ADC_Module  ����� ������ ���.
  *   �������� ��������� ����� �������� �� @ref ADC_Module_TypeDef.
  * @param  ADC_InitStruct ��������� �� ��������� ���� @ref ADC_Init_TypeDef,
  *   ������� �������� ���������������� ����������.
  */

void ADC_Init(ADC_Module_TypeDef ADC_Module, ADC_Init_TypeDef* ADC_InitStruct)
{
    assert_param(IS_ADC_MODULE(ADC_Module));
    assert_param(IS_ADC_RESOLUTION(ADC_InitStruct->ADC_Resolution));
    assert_param(IS_ADC_MEASURE(ADC_InitStruct->ADC_Measure_A));
    assert_param(IS_ADC_MEASURE(ADC_InitStruct->ADC_Measure_B));
    assert_param(IS_ADC_PHASE(ADC_InitStruct->ADC_Phase));
    assert_param(IS_ADC_AVERAGE(ADC_InitStruct->ADC_Average));
    assert_param(IS_ADC_MODE(ADC_InitStruct->ADC_Mode));

    if (ADC_Module == ADC_Module_0)
    {
        NT_ADC->SPC0_bit.PHASE0 = ADC_InitStruct->ADC_Phase;
        NT_ADC->SAC_bit.AVG0 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_1)
    {
        NT_ADC->SPC0_bit.PHASE1 = ADC_InitStruct->ADC_Phase;
        NT_ADC->SAC_bit.AVG1 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_2)
    {
        NT_ADC->SPC1_bit.PHASE2 = ADC_InitStruct->ADC_Phase;
        NT_ADC->SAC_bit.AVG2 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_3)
    {
        NT_ADC->SPC1_bit.PHASE3 = ADC_InitStruct->ADC_Phase;
        NT_ADC->SAC_bit.AVG3 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_4)
    {
        NT_ADC->SPC2_bit.PHASE4 = ADC_InitStruct->ADC_Phase;
        NT_ADC->SAC_bit.AVG4 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_5)
    {
        NT_ADC->SPC2_bit.PHASE5 = ADC_InitStruct->ADC_Phase;
        NT_ADC->SAC_bit.AVG5 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_6)
    {
        NT_ADC->SPC3_bit.PHASE6 = ADC_InitStruct->ADC_Phase;
        NT_ADC->SAC_bit.AVG6 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_7)
    {
        NT_ADC->SPC3_bit.PHASE7 = ADC_InitStruct->ADC_Phase;
        NT_ADC->SAC_bit.AVG7 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_8)
    {
        NT_ADC->SPC4_bit.PHASE8 = ADC_InitStruct->ADC_Phase;
        NT_ADC->RICNT_bit.AVG8 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_9)
    {
        NT_ADC->SPC4_bit.PHASE9 = ADC_InitStruct->ADC_Phase;
        NT_ADC->RICNT_bit.AVG9 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_10)
    {
        NT_ADC->SPC5_bit.PHASE10 = ADC_InitStruct->ADC_Phase;
        NT_ADC->RICNT_bit.AVG10 = ADC_InitStruct->ADC_Average;
    }
    else if (ADC_Module == ADC_Module_11)
    {
        NT_ADC->SPC5_bit.PHASE11 = ADC_InitStruct->ADC_Phase;
        NT_ADC->RICNT_bit.AVG11 = ADC_InitStruct->ADC_Average;
    }

    NT_ADC->PP_bit[(uint32_t)ADC_Module].OM = (((uint32_t)ADC_InitStruct->ADC_Measure_B)<<6)  |
                                              (((uint32_t)ADC_InitStruct->ADC_Measure_A)<<4)  |
                                              (((uint32_t)ADC_InitStruct->ADC_Resolution)<<3) |
                                              (((uint32_t)ADC_InitStruct->ADC_Mode)<<0);
}

/**
  * @brief  ���������� ������� ����� ��������� ADC_InitStruct ���������� �� ���������.
  * @param  ADC_InitStruct ��������� �� ��������� ���� @ref ADC_Init_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void ADC_StructInit(ADC_Init_TypeDef* ADC_InitStruct)
{
    ADC_InitStruct->ADC_Resolution = ADC_Resolution_12bit;
    ADC_InitStruct->ADC_Measure_A = ADC_Measure_Single;
    ADC_InitStruct->ADC_Measure_B = ADC_Measure_Single;
    ADC_InitStruct->ADC_Phase = 0;
    ADC_InitStruct->ADC_Average = ADC_Average_Disable;
    ADC_InitStruct->ADC_Mode = ADC_Mode_Powerdown;
}

/**
  * @brief  ������������� ��� �������� ���������� ��������� ����������� ���������� �� ���������.
  * @param  ADC_DC_Module  ����� ������ ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @retval ���
  */

void ADC_DC_DeInit(ADC_DC_Module_TypeDef ADC_DC_Module)
{
    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));

    NT_ADC->DCCMP_bit[(uint32_t)ADC_DC_Module].COMP0 = 0;
    NT_ADC->DCCMP_bit[(uint32_t)ADC_DC_Module].COMP1 = 0;
    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CHNL = 0x1F; // �.�. 0 = ������ ������� �����, �� ����� ��������� � ����������� ���������
    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CTC = 0;
    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CTM = 0;
}

/**
  * @brief  �������������� ��������� ������ ��������� ����������� �������� ���������� ��������� ADC_DC_InitStruct.
  * @param  ADC_DC_Module  ����� ������ ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @param  ADC_DC_InitStruct ��������� �� ��������� ���� @ref ADC_DC_Init_TypeDef,
  *   ������� �������� ���������������� ����������.
  */

void ADC_DC_Init(ADC_DC_Module_TypeDef ADC_DC_Module, ADC_DC_Init_TypeDef* ADC_DC_InitStruct)
{
    assert_param(IS_ADC_DC(ADC_DC_Module));
    assert_param(IS_ADC_DC_THRESHOLD(ADC_DC_InitStruct->ADC_DC_ThresholdLow));
    assert_param(IS_ADC_DC_THRESHOLD(ADC_DC_InitStruct->ADC_DC_ThresholdHigh));
    assert_param(IS_ADC_DC_CHANNEL(ADC_DC_InitStruct->ADC_DC_Channel));
    assert_param(IS_ADC_DC_MODE(ADC_DC_InitStruct->ADC_DC_Mode));
    assert_param(IS_ADC_DC_CONDITION(ADC_DC_InitStruct->ADC_DC_Condition));

    NT_ADC->DCCMP_bit[(uint32_t)ADC_DC_Module].COMP0 = ADC_DC_InitStruct->ADC_DC_ThresholdLow;
    NT_ADC->DCCMP_bit[(uint32_t)ADC_DC_Module].COMP1 = ADC_DC_InitStruct->ADC_DC_ThresholdHigh;
    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CHNL = (uint32_t)ADC_DC_InitStruct->ADC_DC_Channel;
    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CTC = (uint32_t)ADC_DC_InitStruct->ADC_DC_Condition;
    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CTM = (uint32_t)ADC_DC_InitStruct->ADC_DC_Mode;
}

/**
  * @brief  ���������� ������� ����� ��������� ADC_DC_InitStruct ���������� �� ���������.
  * @param  ADC_DC_InitStruct ��������� �� ��������� ���� @ref ADC_DC_Init_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void ADC_DC_StructInit(ADC_DC_Init_TypeDef* ADC_DC_InitStruct)
{
    ADC_DC_InitStruct->ADC_DC_ThresholdLow = 0;
    ADC_DC_InitStruct->ADC_DC_ThresholdHigh = 0;
    ADC_DC_InitStruct->ADC_DC_Channel = ADC_DC_Channel_None;
    ADC_DC_InitStruct->ADC_DC_Mode = ADC_DC_Mode_Single;
    ADC_DC_InitStruct->ADC_DC_Condition = ADC_DC_Condition_Low;
}

/**
  * @brief  ������������� ��� �������� ���������� ���������� ���������� �� ���������.
  * @param  ADC_SEQ_Module  ����� ������ ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval ���
  */

void ADC_SEQ_DeInit(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    if (ADC_SEQ_Module == ADC_SEQ_Module_0)
    {
        NT_ADC->EMUX_bit.EM0 = 0;
        NT_ADC->PSSI_bit.SS0 = 0;
    }
    else if (ADC_SEQ_Module == ADC_SEQ_Module_1)
    {
        NT_ADC->EMUX_bit.EM1 = 0;
        NT_ADC->PSSI_bit.SS1 = 0;
    }
    else if (ADC_SEQ_Module == ADC_SEQ_Module_2)
    {
        NT_ADC->EMUX_bit.EM2 = 0;
        NT_ADC->PSSI_bit.SS2 = 0;
    }
    else if (ADC_SEQ_Module == ADC_SEQ_Module_3)
    {
        NT_ADC->EMUX_bit.EM3 = 0;
        NT_ADC->PSSI_bit.SS3 = 0;
    }
    else if (ADC_SEQ_Module == ADC_SEQ_Module_4)
    {
        NT_ADC->EMUX_bit.EM4 = 0;
        NT_ADC->PSSI_bit.SS4 = 0;
    }
    else if (ADC_SEQ_Module == ADC_SEQ_Module_5)
    {
        NT_ADC->EMUX_bit.EM5 = 0;
        NT_ADC->PSSI_bit.SS5 = 0;
    }
    else if (ADC_SEQ_Module == ADC_SEQ_Module_6)
    {
        NT_ADC->EMUX_bit.EM6 = 0;
        NT_ADC->PSSI_bit.SS6 = 0;
    }
    else if (ADC_SEQ_Module == ADC_SEQ_Module_7)
    {
        NT_ADC->EMUX_bit.EM7 = 0;
        NT_ADC->PSSI_bit.SS7 = 0;
    }

    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].CTL_bit.RCNT = 0;
    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].TMR_bit.TMR = 2;
    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].DCP = 0;
    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].MUX = 0;
}

/**
  * @brief  �������������� ��������� ��������� �������� ���������� ��������� ADC_SEQ_InitStruct.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @param  ADC_SEQ_InitStruct ��������� �� ��������� ���� @ref ADC_SEQ_Init_TypeDef,
  *   ������� �������� ���������������� ����������.
  * @retval ���
  */

void ADC_SEQ_Init(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, ADC_SEQ_Init_TypeDef* ADC_SEQ_InitStruct)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));
    assert_param(IS_ADC_SEQ_START_EVENT(ADC_SEQ_InitStruct->ADC_SEQ_StartEvent));
    assert_param(IS_FUNCTIONAL_STATE(ADC_SEQ_InitStruct->ADC_SEQ_SWReqEn));
    assert_param(IS_ADC_CHANNEL(ADC_SEQ_InitStruct->ADC_Channels));
    assert_param(IS_ADC_SEQ_CONVERSION_COUNT(ADC_SEQ_InitStruct->ADC_SEQ_ConversionCount));
    assert_param(IS_ADC_SEQ_CONVERSION_DELAY(ADC_SEQ_InitStruct->ADC_SEQ_ConversionDelay));
    assert_param(IS_ADC_DC(ADC_SEQ_InitStruct->ADC_SEQ_DC));

    NT_ADC->EMUX &= ~(0xF<<((uint32_t)ADC_SEQ_Module*4));
    NT_ADC->EMUX |= ((uint32_t)ADC_SEQ_InitStruct->ADC_SEQ_StartEvent)<<((uint32_t)ADC_SEQ_Module*4);

    if (ADC_SEQ_InitStruct->ADC_SEQ_SWReqEn == ENABLE)
    {
        NT_ADC->PSSI |= 1<<((uint32_t)ADC_SEQ_Module);
    }
    else
    {
        NT_ADC->PSSI &= ~(1<<((uint32_t)ADC_SEQ_Module));
    }

    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].CTL_bit.RCNT = (uint32_t)(ADC_SEQ_InitStruct->ADC_SEQ_ConversionCount-1);
    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].TMR_bit.TMR = (uint32_t)ADC_SEQ_InitStruct->ADC_SEQ_ConversionDelay;
    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].DCP = (uint32_t)ADC_SEQ_InitStruct->ADC_SEQ_DC;
    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].MUX = (uint32_t)ADC_SEQ_InitStruct->ADC_Channels;
}

/**
  * @brief  ���������� ������� ����� ��������� ADC_SEQ_InitStruct ���������� �� ���������.
  * @param  ADC_SEQ_InitStruct ��������� �� ��������� ���� @ref ADC_SEQ_Init_TypeDef,
  *         ������� ���������� �������������������.
  * @retval ���
  */

void ADC_SEQ_StructInit(ADC_SEQ_Init_TypeDef* ADC_SEQ_InitStruct)
{
    ADC_SEQ_InitStruct->ADC_SEQ_StartEvent = ADC_SEQ_StartEvent_SWReq;
    ADC_SEQ_InitStruct->ADC_SEQ_SWReqEn = ENABLE;
    ADC_SEQ_InitStruct->ADC_Channels = ADC_Channel_None;
    ADC_SEQ_InitStruct->ADC_SEQ_ConversionCount = 1;
    ADC_SEQ_InitStruct->ADC_SEQ_ConversionDelay = 2;
    ADC_SEQ_InitStruct->ADC_SEQ_DC = ADC_DC_None;
}

/**
  * @brief  ��������������� ��������� ��������� ��� ������ � DMA.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @param  ADC_SEQ_FIFOLevel  ���������� ����������� ��������� ���������� � ����� ����������, �� ���������� �������� ���������� DMA.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_FIFOLevel_TypeDef.
  * @retval ���
  */

void ADC_SEQ_DMAConfig(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, ADC_SEQ_FIFOLevel_TypeDef ADC_SEQ_FIFOLevel)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));
    assert_param(IS_ADC_SEQ_FIFO_LEVEL(ADC_SEQ_FIFOLevel));

    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].CTL_bit.WMARK = (uint32_t)ADC_SEQ_FIFOLevel;
}

/**
  * @brief  �������� ��� ���������� ���������� ������������� �������� DMA.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void ADC_SEQ_DMACmd(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, FunctionalState State)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));
    assert_param(IS_FUNCTIONAL_STATE(State));

    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].CTL_bit.DMAEN = (uint32_t)State;
}

/**
  * @brief  �������� ������� ������, ����� ��� ������� ���� �������������� �������� DMA
  *   �� ���������� ����������, ������ ������ ������, ������� �� ����� ���� ���������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval FlagStatus ������� ��������� �����.
  */

FlagStatus ADC_SEQ_DMAErrorStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    FlagStatus Status;

    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    if (NT_ADC->OSTAT & (1<<((uint32_t)ADC_SEQ_Module + 16))) // � ������ 16 - ����� ���������� ������ ����������
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
  * @brief  ����� ������� ������ DMA.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval ���
  */

void ADC_SEQ_DMAErrorStatusClear(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    NT_ADC->OSTAT = 1<<((uint32_t)ADC_SEQ_Module + 16);
}

/**
  * @brief  ��������� ����������� ������������ ������ ����������.
  * @param  ADC_DC_Module  ����� ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void ADC_DC_ITGenCmd(ADC_DC_Module_TypeDef ADC_DC_Module, FunctionalState State)
{
    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));
    assert_param(IS_FUNCTIONAL_STATE(State));

    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CIE = (uint32_t)State;
}

/**
  * @brief  ������������ ������� ���������� ��������� �����������.
  * @param  ADC_DC_Module  ����� ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void ADC_DC_ITMaskCmd(ADC_DC_Module_TypeDef ADC_DC_Module, FunctionalState State)
{
    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_ADC->IM |= 1<<((uint32_t)ADC_DC_Module + 8); // ������ 8 - ��� ����������
    }
    else /* if (State == DISABLE) */
    {
        NT_ADC->IM &= ~(1<<((uint32_t)ADC_DC_Module + 8)); // ������ 8 - ��� ����������
    }
}

/**
  * @brief  ��������� ���������� ����������� � ������������� ������������ ������� ����� ����������.
  *   ��� ����, ��� �� �������� ����� ��������� ����� ������� �������� ��������������� �������:
  *   @ref ADC_DC_ITGenCmd � @ref ADC_DC_ITMaskCmd.
  * @param  ADC_DC_Module  ����� ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void ADC_DC_ITCmd(ADC_DC_Module_TypeDef ADC_DC_Module, FunctionalState State)
{
    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));
    assert_param(IS_FUNCTIONAL_STATE(State));

    //����������/���������� ��������� ������� ���������� �����������
    ADC_DC_ITGenCmd(ADC_DC_Module, State);

    //������������ ������� ���������� ��� ��������� ������ NVIC
    ADC_DC_ITMaskCmd(ADC_DC_Module, State);
}

/**
  * @brief  ��������� ������� ������ ���������� ��������� �����������. ������� ������
  *   ���������� � ������� ������������ ��������� �������� ����������� ����� �� ���������.
  * @param  ADC_DC_Module  ����� ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @param  ADC_DC_Mode  ����� ������������ �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Mode_TypeDef.
  * @param  ADC_DC_Condition  ������� ������������ �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Condition_TypeDef.
  * @retval ���
  */

void ADC_DC_ITConfig(ADC_DC_Module_TypeDef ADC_DC_Module, ADC_DC_Mode_TypeDef ADC_DC_Mode, ADC_DC_Condition_TypeDef ADC_DC_Condition)
{
    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));
    assert_param(IS_ADC_DC_MODE(ADC_DC_Mode));
    assert_param(IS_ADC_DC_CONDITION(ADC_DC_Condition));

    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CIC = (uint32_t)ADC_DC_Condition;
    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CIM = (uint32_t)ADC_DC_Mode;
}

/**
  * @brief  �������� ������ ��������������� ����������.
  * @param  ADC_DC_Module  ����� ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @retval FlagStatus ������� ��������� �����.
  */

FlagStatus ADC_DC_ITRawStatus(ADC_DC_Module_TypeDef ADC_DC_Module)
{
    FlagStatus Status;

    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));

    if (NT_ADC->RIS & (1<<((uint32_t)ADC_DC_Module + 8)))
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
  * @brief  �������� ������ ������������� ����������.
  * @param  ADC_DC_Module  ����� ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @retval FlagStatus ������� ��������� �����.
  */

FlagStatus ADC_DC_ITMaskedStatus(ADC_DC_Module_TypeDef ADC_DC_Module)
{
    FlagStatus Status;

    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));

    if (NT_ADC->ISC & (1<<((uint32_t)ADC_DC_Module + 8)))
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
  * @brief  ����� ����� ������ ���������� ��������� �����������.
  *   ���������� ��� �������������, ��� � ��������������� �����.
  * @param  ADC_DC_Module  ����� ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @retval ���
  */

void ADC_DC_ITStatusClear(ADC_DC_Module_TypeDef ADC_DC_Module)
{
    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));

    NT_ADC->ISC = 1<<((uint32_t)ADC_DC_Module + 8); // ������ 8 - ��� ����������
}

/**
  * @brief  ��������� ���������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void ADC_SEQ_ITCmd(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, FunctionalState State)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
        NT_ADC->IM |= 1<<((uint32_t)ADC_SEQ_Module); // ������ 8 - ��� ����������
    }
    else /* if (State == DISABLE) */
    {
        NT_ADC->IM &= ~(1<<((uint32_t)ADC_SEQ_Module)); // ������ 8 - ��� ����������
    }
}

/**
  * @brief  ��������� ������ ���������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @param  ADC_SEQ_ITRate  �������� ���������� ������������ ������� ��� �����������
  *   ����� �������� ������������ ����������.
  *   �������� ��������� ����� �������� �� ��������� 1 - 256.
  * @param  ADC_SEQ_ITCountSEQRst  ���������� ������ �������� ���������� �� ������� ����������.
  *   ���� ���������, �� ������� ����� ����� ���������� ������ ���������� ����� @ref ADC_SEQ_ITCountRst.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void ADC_SEQ_ITConfig(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, uint32_t ADC_SEQ_ITRate, FunctionalState ADC_SEQ_ITCountSEQRst)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));
    assert_param(IS_ADC_SEQ_IT_RATE(ADC_SEQ_ITRate));
    assert_param(IS_FUNCTIONAL_STATE(ADC_SEQ_ITCountSEQRst));

    if (ADC_SEQ_ITCountSEQRst == ENABLE)
    {
         NT_ADC->RICNT |= 1<<((uint32_t)ADC_SEQ_Module + 16); // ������ 16 - ��� ����������� 8-11
    }
    else /* if (State == DISABLE) */
    {
        NT_ADC->RICNT &= ~(1<<((uint32_t)ADC_SEQ_Module + 16)); // ������ 16 - ��� ����������� 8-11
    }

    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].CTL_bit.ICNT = ADC_SEQ_ITRate - 1;
}

/**
  * @brief  ������� �������� �������� ���������, ������� ������������ ��� ��������� ���������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval ITCount
  */

uint32_t ADC_SEQ_GetITCount(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    uint32_t ITCount;

    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    ITCount = NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].OP_bit.ICNT;

    return ITCount;
}

/**
  * @brief  ����� �������� ���������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval ���
  */

void ADC_SEQ_ITCountRst(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].OP_bit.ICNT = 1;
}

/**
  * @brief  �������� ������ ��������������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval FlagStatus ������� ��������� �����.
  */

FlagStatus ADC_SEQ_ITRawStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    FlagStatus Status;

    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    if (NT_ADC->RIS & (1<<((uint32_t)ADC_SEQ_Module)))
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
  * @brief  �������� ������ ������������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval FlagStatus ������� ��������� �����.
  */

FlagStatus ADC_SEQ_ITMaskedStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    FlagStatus Status;

    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    if (NT_ADC->ISC & (1<<((uint32_t)ADC_SEQ_Module)))
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
  * @brief  ����� ����� ������ ���������� ����������. ���������� ��� �������������, ��� � ��������������� �����.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval ���
  */

void ADC_SEQ_ITStatusClear(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    NT_ADC->ISC = 1<<((uint32_t)ADC_SEQ_Module);
}

/**
  * @brief  ��������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void ADC_SEQ_Cmd(ADC_SEQ_Module_TypeDef ADC_SEQ_Module, FunctionalState State)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
    {
         NT_ADC->ACTSS |= 1<<((uint32_t)ADC_SEQ_Module);
    }
    else /* if (State == DISABLE) */
    {
        NT_ADC->ACTSS &= ~(1<<((uint32_t)ADC_SEQ_Module));
    }
}

/**
  * @brief  ����������� ������ ��������� ���� ����������� �����������.
  * @retval ���
  */

void ADC_SEQ_SWReq()
{
    NT_ADC->PSSI_bit.GSYNC = 1;
}

/**
  * @brief  ��������� ���������� ��������� �� ������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval Data ��������� ���������.
  */

uint32_t ADC_SEQ_GetFIFOData(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    uint32_t Data;

    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    Data = NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].FIFO_bit.DATA;

    return Data;
}

/**
  * @brief  ��������� ���������� ���������, ����������� �������� ��� � ������� ������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval Data ��������� ���������.
  */

uint32_t ADC_SEQ_GetConversionCount(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    uint32_t Count;

    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    Count = NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].OP_bit.RCNT;

    return Count;
}

/**
  * @brief  ��������� ���������� ���������, ����������� � ������ ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval Data ��������� ���������.
  */

uint32_t ADC_SEQ_GetFIFOLoad(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    uint32_t Load;

    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    Load = NT_ADC->SEQ[(uint32_t)ADC_SEQ_Module].FSTAT_bit.FLOAD;

    return Load;
}

/**
  * @brief  �������� ����� ���������� ������� ����������.
  *   ���� ���� ����������, �� ������ ��� ������ �������� � ��� ����������� ������
  *   � ������ ����� ������������� �� ��������� ��� ������� ����� ��������� ������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval FlagStatus ������� ��������� �����.
  */

FlagStatus ADC_SEQ_FIFOFullStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    FlagStatus Status;

    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    if (NT_ADC->OSTAT & (1<<((uint32_t)ADC_SEQ_Module)))
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
  * @brief  C���� ����� ���������� ������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval ���
  */

void ADC_SEQ_FIFOFullStatusClear(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    NT_ADC->OSTAT = 1<<((uint32_t)ADC_SEQ_Module);
}

/**
  * @brief  �������� ����� ������� ������� ����������.
  *  ���� ���������� ����� ����� ��������� ����.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval FlagStatus ������� ��������� �����.
  */

FlagStatus ADC_SEQ_FIFOEmptyStatus(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    FlagStatus Status;

    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    if (NT_ADC->USTAT & (1<<((uint32_t)ADC_SEQ_Module)))
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
  * @brief  C���� ����� ������� ������� ����������.
  * @param  ADC_SEQ_Module  ����� ����������.
  *   �������� ��������� ����� �������� �� @ref ADC_SEQ_Module_TypeDef.
  * @retval ���
  */

void ADC_SEQ_FIFOEmptyStatusClear(ADC_SEQ_Module_TypeDef ADC_SEQ_Module)
{
    assert_param(IS_ADC_SEQ_MODULE(ADC_SEQ_Module));

    NT_ADC->USTAT = 1<<((uint32_t)ADC_SEQ_Module);
}

/**
  * @brief  ��������� ��������� �������� ��������� �����������.
  * @param  ADC_DC_Module  ����� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @param  State  ����� ���������.
  *   �������� ��������� ����� �������� �� @ref FunctionalState.
  * @retval ���
  */

void ADC_DC_Cmd(ADC_DC_Module_TypeDef ADC_DC_Module, FunctionalState State)
{
    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));
    assert_param(IS_FUNCTIONAL_STATE(State));

    NT_ADC->DCCTL_bit[(uint32_t)ADC_DC_Module].CTE = (uint32_t)State;
}

/**
  * @brief  �������� ���������� ���������, ������� ��������� ��������������
  *   ������������ ��� �������� �� ������������ ��������.
  * @param  ADC_DC_Module  ����� ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @retval Data ��������� ���������.
  */

uint32_t ADC_DC_GetLastData(ADC_DC_Module_TypeDef ADC_DC_Module)
{
    uint32_t Value;

    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));

    Value = NT_ADC->DCVAL_bit[(uint32_t)ADC_DC_Module].VAL;

    return Value;
}

/**
  * @brief  �������� ��������� ��������� �������� �����������.
  * @param  ADC_DC_Module  ����� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @retval FlagStatus ������� ��������� ��������.
  */

FlagStatus ADC_DC_TrigStatus(ADC_DC_Module_TypeDef ADC_DC_Module)
{
    FlagStatus Status;

    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));

    if (NT_ADC->DCRTC & (1<<((uint32_t)ADC_DC_Module)))
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
  * @brief  C���� ��������� �������� ��������� �����������.
  * @attention ������������ �� ������� ��������� 0 � 1 ����������� ������������
  *   �������� 10 � 11 ����������� �������������. �� �� ����� ����������� � ��� ��������� ������.
  *   ��� ��������� ��������� � ������������ �������� �� ���������.
  * @param  ADC_DC_Module  ����� ��������� �����������.
  *   �������� ��������� ����� �������� �� @ref ADC_DC_Module_TypeDef.
  * @retval ���
  */

void ADC_DC_TrigStatusClear(ADC_DC_Module_TypeDef ADC_DC_Module)
{
    assert_param(IS_ADC_DC_MODULE(ADC_DC_Module));

    // ����� �������� 0 � 1 �����������, ����� ������ � ���� 10 � 11 ������������ ��������������
    if ((ADC_DC_Module == ADC_DC_Module_0) |
        (ADC_DC_Module == ADC_DC_Module_1))
    {
        ADC_DC_Module = (ADC_DC_Module_TypeDef)((uint32_t)ADC_DC_Module + 10);
    }

    NT_ADC->DCRTC = 1<<((uint32_t)ADC_DC_Module + 8);
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
