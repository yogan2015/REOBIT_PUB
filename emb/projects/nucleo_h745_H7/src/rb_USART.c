 #ifdef RELPATH
    #include "main.h"
#else
    #include "../inc/main.h"
#endif

void rb_USART2_Init()
{
    const char *a = "abcdefghijklmnop";
    //тактируется APB1L
    //домен D2
    //RX - PD6
    //TX - PD5
    GPIOD->MODER   |=  GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1;
    GPIOD->AFR[0]  |=  GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_2;
}
