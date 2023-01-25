#include "main.h"
#ifdef STM32H7xx_LL_ADC_H



const uint32_t Get_ADC_Common_Multimode[] = {
	LL_ADC_MULTI_INDEPENDENT,
	LL_ADC_MULTI_DUAL_REG_SIMULT,
	LL_ADC_MULTI_DUAL_REG_INTERL,
	LL_ADC_MULTI_DUAL_INJ_SIMULT,
	LL_ADC_MULTI_DUAL_INJ_ALTERN,
	LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM,
	LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT,
	LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM
};

const uint32_t Get_ADC_Common_CommonClock[] = {
	LL_ADC_CLOCK_SYNC_PCLK_DIV1,
	LL_ADC_CLOCK_SYNC_PCLK_DIV2,
	LL_ADC_CLOCK_SYNC_PCLK_DIV4,
	LL_ADC_CLOCK_ASYNC_DIV1,
	LL_ADC_CLOCK_ASYNC_DIV2,
	LL_ADC_CLOCK_ASYNC_DIV4,
	LL_ADC_CLOCK_ASYNC_DIV6,
	LL_ADC_CLOCK_ASYNC_DIV8,
	LL_ADC_CLOCK_ASYNC_DIV10,
	LL_ADC_CLOCK_ASYNC_DIV12,
	LL_ADC_CLOCK_ASYNC_DIV16,
	LL_ADC_CLOCK_ASYNC_DIV32,
	LL_ADC_CLOCK_ASYNC_DIV64,
	LL_ADC_CLOCK_ASYNC_DIV128,
	LL_ADC_CLOCK_ASYNC_DIV256
};

const uint32_t Get_ADC_Common_MultiDMATransfer[] = {
	LL_ADC_MULTI_REG_DMA_EACH_ADC,
	LL_ADC_MULTI_REG_DMA_RES_32_10B,
	LL_ADC_MULTI_REG_DMA_RES_8B
};

const uint32_t Get_ADC_Common_MultiTwoSamplingDelay[] = {
	LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE_5,
	LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES_5,
	LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES_5,
	LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES_5,
	LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES_5_8_BITS,
	LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES_5,
	LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES_5_10_BITS,
	LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES,
	LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES_5,
	LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES_5_12_BITS,
	LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES_5,
	LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES,
	LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES
};


ADC_TypeDef *Get_ADC_Base[] = {
	ADC1,
	ADC2,
	ADC3
};

const uint32_t Get_ADC_WDG[] = {
	LL_ADC_AWD1,
	LL_ADC_AWD2,
	LL_ADC_AWD3
};

const uint32_t Get_ADC_Resolution[] = {
		LL_ADC_RESOLUTION_16B,
		LL_ADC_RESOLUTION_14B,
		LL_ADC_RESOLUTION_12B,
		LL_ADC_RESOLUTION_10B,
		LL_ADC_RESOLUTION_14B_OPT,
		LL_ADC_RESOLUTION_12B_OPT,
		LL_ADC_RESOLUTION_8B
};

const uint32_t Get_ADC_REG_TriggerSource[] = {
	LL_ADC_REG_TRIG_SOFTWARE,
	LL_ADC_REG_TRIG_EXT_TIM1_CH1,
	LL_ADC_REG_TRIG_EXT_TIM1_CH2,
	LL_ADC_REG_TRIG_EXT_TIM1_CH3,
	LL_ADC_REG_TRIG_EXT_TIM2_CH2,
	LL_ADC_REG_TRIG_EXT_TIM3_TRGO,
	LL_ADC_REG_TRIG_EXT_TIM4_CH4,
	LL_ADC_REG_TRIG_EXT_EXTI_LINE11,
	LL_ADC_REG_TRIG_EXT_TIM8_TRGO,
	LL_ADC_REG_TRIG_EXT_TIM8_TRGO2,
	LL_ADC_REG_TRIG_EXT_TIM1_TRGO,
	LL_ADC_REG_TRIG_EXT_TIM1_TRGO2,
	LL_ADC_REG_TRIG_EXT_TIM2_TRGO,
	LL_ADC_REG_TRIG_EXT_TIM4_TRGO,
	LL_ADC_REG_TRIG_EXT_TIM6_TRGO,
	LL_ADC_REG_TRIG_EXT_TIM15_TRGO,
	LL_ADC_REG_TRIG_EXT_TIM3_CH4,
	LL_ADC_REG_TRIG_EXT_HRTIM_TRG1,
	LL_ADC_REG_TRIG_EXT_HRTIM_TRG3,
	LL_ADC_REG_TRIG_EXT_LPTIM1_OUT,
	LL_ADC_REG_TRIG_EXT_LPTIM2_OUT,
	LL_ADC_REG_TRIG_EXT_LPTIM3_OUT
};

const uint32_t Get_ADC_Rank[] = {
    LL_ADC_REG_RANK_1,
    LL_ADC_REG_RANK_2,
    LL_ADC_REG_RANK_3,
    LL_ADC_REG_RANK_4,
    LL_ADC_REG_RANK_5,
    LL_ADC_REG_RANK_6,
    LL_ADC_REG_RANK_7,
    LL_ADC_REG_RANK_8,
    LL_ADC_REG_RANK_9,
    LL_ADC_REG_RANK_10,
    LL_ADC_REG_RANK_11,
    LL_ADC_REG_RANK_12,
    LL_ADC_REG_RANK_13,
    LL_ADC_REG_RANK_14,
    LL_ADC_REG_RANK_15,
    LL_ADC_REG_RANK_16
};

const uint32_t Get_ADC_Chanel[] = {
	LL_ADC_CHANNEL_0,
	LL_ADC_CHANNEL_1,
	LL_ADC_CHANNEL_2,
	LL_ADC_CHANNEL_3,
	LL_ADC_CHANNEL_4,
	LL_ADC_CHANNEL_5,
	LL_ADC_CHANNEL_6,
	LL_ADC_CHANNEL_7,
	LL_ADC_CHANNEL_8,
	LL_ADC_CHANNEL_9,
	LL_ADC_CHANNEL_10,
	LL_ADC_CHANNEL_11,
	LL_ADC_CHANNEL_12,
	LL_ADC_CHANNEL_13,
	LL_ADC_CHANNEL_14,
	LL_ADC_CHANNEL_15,
	LL_ADC_CHANNEL_16,
	LL_ADC_CHANNEL_17,
	LL_ADC_CHANNEL_18,
	LL_ADC_CHANNEL_19
};

const uint32_t Get_ADC_DMA_Stream[] = {
    LL_DMA_STREAM_0,
    LL_DMA_STREAM_1,
    LL_DMA_STREAM_2,
    LL_DMA_STREAM_3,
    LL_DMA_STREAM_4,
    LL_DMA_STREAM_5,
    LL_DMA_STREAM_6,
    LL_DMA_STREAM_7
};

const uint32_t Get_ADC_DMARequest[] = {
	LL_DMAMUX1_REQ_ADC1,
	LL_DMAMUX1_REQ_ADC2,
	LL_DMAMUX1_REQ_ADC3
};


const uint32_t Get_ADC_BOOST[] = {
		LL_ADC_BOOST_MODE_6MHZ25,
		LL_ADC_BOOST_MODE_12MHZ5,
		LL_ADC_BOOST_MODE_20MHZ,
		LL_ADC_BOOST_MODE_25MHZ,
		LL_ADC_BOOST_MODE_50MHZ
};

#endif