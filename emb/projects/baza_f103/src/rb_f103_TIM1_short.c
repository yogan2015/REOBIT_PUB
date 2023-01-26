#include "../inc/main.h"
#define SA (TIM1->CR1 & TIM_CR1_DIR)
#define SB (!(TIM1->CR1 & TIM_CR1_DIR))
static inline void config_TIM1()
{
    TIM1->PSC = 200-1; // 1,024 mhz - 71-1
    TIM1->ARR = p_m;   
    TIM1->CCR1 = p_s;    TIM1->CCR2 = p_s;    TIM1->CCR3 = p_s;
    TIM1->CR1 |= TIM_CR1_CMS_0 | TIM_CR1_ARPE;
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E
                | TIM_CCER_CC1NE| TIM_CCER_CC2NE| TIM_CCER_CC3NE 
                | TIM_CCER_CC1P | TIM_CCER_CC2P | TIM_CCER_CC3P;
    TIM1->BDTR |= TIM_BDTR_MOE;    
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2
                |  TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2; // toggle mode
    TIM1->DIER |= TIM_DIER_UIE;
    TIM1->CR1  |= TIM_CR1_CEN;   
    
    NVIC_DisableIRQ(TIM1_UP_IRQn);
    NVIC_ClearPendingIRQ(TIM1_UP_IRQn);
    NVIC_EnableIRQ(TIM1_UP_IRQn);  
}
