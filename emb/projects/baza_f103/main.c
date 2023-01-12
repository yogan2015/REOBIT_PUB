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

void SystemInit()   
{
    config_RCC();
    config_GPIO();
    config_TIM1();
    main();
}




extern void TIM1_UP_IRQHandler()
{
    //NVIC->ICPR |= NVIC_ClearPendingIRQ(TIM1_UP_IRQn);
    TIM1->SR &= ~TIM_SR_UIF;
    GPIOC->ODR ^= GPIO_ODR_ODR13;
}

void main()
{
    while (1)
    {
        ;
    }   
}