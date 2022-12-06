#ifdef RELPATH
    #include "main.h"
#else
    #include "inc/main.h"
#endif

void main()
{
    int a = 1;
}

void SystemInit()
{
    // выполняется до main()
}

void ADC3_IRQHandler()  //asdasda
{
    int a = 0xDEADBEEF;  //aaaa
}

void TIM15_IRQHandler()
{
    ;
}