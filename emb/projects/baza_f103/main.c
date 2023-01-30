#ifdef RELPATH
    #include "main.h"
    #include "rb_data.h"
#else
    #include "./inc/main.h"
    #include "./inc/rb_data.h"
#endif

#include "./src/rb_f103_TIM1_short.c"
#include "./src/rb_f103_GPIO.c"
#include "./src/rb_f103_RCC.c"
#include "./src/rb_f103_EXTI.c"

static uint16_t phase = 1740;
static char sector = 0;

void SystemInit()   
{   
    __disable_irq();
    config_RCC();
    config_GPIO();
    config_TIM1();
    config_EXTI();
    main();
}

void main()
{
    __enable_irq();
    while (1)
    {
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        asm("nop");
        
    }   
}

int a = 10;

extern void EXTI0_IRQHandler()
{
    EXTI->PR &= ~EXTI_PR_PR0;           // видимо, отличие от STM32, там по инструкции необходимо писать 1 чтобы обнулить
    if (GPIOA->IDR & GPIO_IDR_IDR0) 
    {
        GPIOC->BSRR |= GPIO_BSRR_BS13;
    } else {
        GPIOC->BSRR |= GPIO_BSRR_BR13;
    }
}

extern void TIM1_UP_IRQHandler()
{
    if SB sector++;
    if (sector>=3) sector=0;
    int cr1, cr2, cr3;
    cr1 = p_l+1;    cr2 = p_l+1; cr3 = p_l+1;
    // настраиваем CCR3 для работы в области 1A-1B
    if (sector == 0)
    {
        
        cr1 = p_s;
        if SA {
            cr2 = ((phase<p_s)?(p_s-phase):(p_l));
        } else cr2 = p_l;
    }
    if (sector == 1)
    {
        cr2 = ((phase>p_s)?(phase-p_s):(p_l));
    }
    if (sector == 2)
    {
        cr3 = p_s;
        if SB {
            cr2 = ((phase<p_s)?(p_s-phase):(p_l));
        } else cr2 = p_l;
    }
    TIM1->CCR1 = cr1;
    TIM1->CCR2 = cr2;
    TIM1->CCR3 = cr3;

    phase++;
    phase=((phase>p_l)?(0):(phase));

    TIM1->SR &= ~TIM_SR_UIF;
}