#include "../inc/main.h"
int a;

void config_EXTI()
{
    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0_PA;  // A1
    EXTI->FTSR|= EXTI_FTSR_TR0;
    EXTI->RTSR|= EXTI_RTSR_TR0;

    EXTI->PR  |= EXTI_PR_PR0;                   // bit cleared by writing 1
    EXTI->IMR |= EXTI_IMR_MR0;                  //  A1 for interrupt input
    
    NVIC_EnableIRQ(EXTI0_IRQn);
}
