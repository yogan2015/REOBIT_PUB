#include "../inc/main.h"

static inline void config_TIM1()
{
    //NVIC_EnableIRQ(TIM1_CC_IRQn);
    TIM1->PSC = 71-1; // 1,024 mhz - 71-1
    TIM1->ARR = 1024;   
    TIM1->CCR1 = 512;    TIM1->CCR2 = 512;    TIM1->CCR3 = 512;
    TIM1->CR1 |= TIM_CR1_CMS_0 | TIM_CR1_ARPE;
    //TIM1->CCR2 = 0x1000;
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E
                | TIM_CCER_CC1NE| TIM_CCER_CC2NE| TIM_CCER_CC3NE 
                | TIM_CCER_CC1P | TIM_CCER_CC2P | TIM_CCER_CC3P;
    TIM1->BDTR |= TIM_BDTR_MOE;    
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2
                |  TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
    //TIM1->CR1  |= TIM_CR1_CEN;
    TIM1->DIER |= TIM_DIER_CC1IE;
    TIM1->CR1  |= TIM_CR1_CEN;   
}
