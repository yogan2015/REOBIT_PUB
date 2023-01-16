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
    TIM1->SR &= ~TIM_SR_UIF;
}