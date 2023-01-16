#include "main.h"
#ifdef __STM32H7xx_LL_TIM_H

const uint32_t Get_TIM_DMA_Stream[] = {
    LL_DMA_STREAM_0,
    LL_DMA_STREAM_1,
    LL_DMA_STREAM_2,
    LL_DMA_STREAM_3,
    LL_DMA_STREAM_4,
    LL_DMA_STREAM_5,
    LL_DMA_STREAM_6,
    LL_DMA_STREAM_7
};

const uint32_t Get_TIM_DMAMUX_Channel[] = {
	LL_DMAMUX_CHANNEL_0,
	LL_DMAMUX_CHANNEL_1,
	LL_DMAMUX_CHANNEL_2,
	LL_DMAMUX_CHANNEL_3,
	LL_DMAMUX_CHANNEL_4,
	LL_DMAMUX_CHANNEL_5,
	LL_DMAMUX_CHANNEL_6,
	LL_DMAMUX_CHANNEL_7,
	LL_DMAMUX_CHANNEL_8,
	LL_DMAMUX_CHANNEL_9,
	LL_DMAMUX_CHANNEL_10,
	LL_DMAMUX_CHANNEL_11,
	LL_DMAMUX_CHANNEL_12,
	LL_DMAMUX_CHANNEL_13,
	LL_DMAMUX_CHANNEL_14,
	LL_DMAMUX_CHANNEL_15
};

const uint32_t Get_TIM_DMAMUX_Request[] = {
	LL_DMAMUX1_REQ_TIM1_UP,
	LL_DMAMUX1_REQ_TIM2_UP,
	LL_DMAMUX1_REQ_TIM3_UP,
	LL_DMAMUX1_REQ_TIM4_UP,
	LL_DMAMUX1_REQ_TIM5_UP,
	LL_DMAMUX1_REQ_TIM6_UP,
	LL_DMAMUX1_REQ_TIM7_UP,
	LL_DMAMUX1_REQ_TIM8_UP,
	LL_DMAMUX1_REQ_TIM15_UP,
	LL_DMAMUX1_REQ_TIM16_UP,
	LL_DMAMUX1_REQ_TIM17_UP
};

void TIM_Configure(TIM_TypeDef *TIMx, uint16_t CntMode, uint16_t Period, uint16_t Prescaller)
{
	LL_TIM_InitTypeDef TIM_TimeBaseStructure = {0};
	TIM_TimeBaseStructure.Prescaler = Prescaller;
	TIM_TimeBaseStructure.CounterMode = CntMode;
	TIM_TimeBaseStructure.Autoreload = Period;
	TIM_TimeBaseStructure.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	TIM_TimeBaseStructure.RepetitionCounter = 0;
	LL_TIM_Init(TIMx, &TIM_TimeBaseStructure);
}

TIM_TypeDef *TIM_GetBase(uint8_t TimerId)
{
  switch(TimerId)
  {
    case 0:  return TIM1;
    case 1:  return TIM2;
    case 2:  return TIM3;
    case 3:  return TIM4;
    case 4:  return TIM5;
    case 5:  return TIM6;
    case 6:  return TIM7;
    case 7:  return TIM8;
    case 8: return TIM12;
    case 9: return TIM13;
    case 10: return TIM14;
    case 11: return TIM15;
    case 12: return TIM16;
    case 13: return TIM17;
  }
  return 0;
}

uint8_t TIM_EnClocks(uint8_t TimerId)
{
  switch(TimerId)
  {
    case 0:  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1); return 1;
    case 1:  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2); return 1;
    case 2:  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3); return 1;
    case 3:  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4); return 1;
    case 4:  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5); return 1;
    case 5:  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6); return 1;
    case 6:  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7); return 1;
    case 7:  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8); return 1;
    case 8: LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM12); return 1;
    case 9: LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM13); return 1;
    case 10: LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14); return 1;
    case 11: LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15); return 1;
    case 12: LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16); return 1;
    case 13: LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17); return 1;
  }
  return 0;
}
#endif
