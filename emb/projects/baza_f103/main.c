#ifdef RELPATH
    #include "main.h"
    #include "rb_data.h"
#else
    #include "./inc/main.h"
    #include "./inc/rb_data.h"
#endif

void SystemInit()   
{
    //  ������������ �� HSE (�� ������� - 8 ���)
        RCC->CR |=  RCC_CR_HSEON;
        while (!(RCC->CR & RCC_CR_HSERDY))

    //  �������� ������������ �������   (������������� ������)
        //RCC->CFGR;        Clock configuration r.
        RCC->CFGR |= (  
                        RCC_CFGR_HPRE_DIV1    |
                        RCC_CFGR_PPRE1_DIV2   |
                        RCC_CFGR_PPRE2_DIV1   |
                        RCC_CFGR_ADCPRE_DIV6  |
                        RCC_CFGR_PLLSRC_HSE   |
                        RCC_CFGR_PLLXTPRE_HSE |                    
                        RCC_CFGR_PLLMULL9     |
                        RCC_CFGR_USBPRE       |
                        RCC_CFGR_MCO_NOCLOCK
                        );

        //RCC->CIR;         Clock interrupt r.
        RCC->CIR =      0;

        //RCC->APB1RSTR;    APB1 Peripherial reset r.
        RCC->APB1RSTR = 0;

        //RCC->APB2RSTR;    APB2 Peripherial reset r.
        RCC->APB2RSTR = 0;

        //RCC->AHBENR;      AHB Peripherial clock enable r.
        //RCC->AHBENR =  (RCC_AHBENR_DMA1EN   |
        //                RCC_AHBENR_SRAMEN   |
        //                RCC_AHBENR_FLITFEN  |
        //                RCC_AHBENR_CRCEN);

        //RCC->APB1ENR;     APB1 Peripherial clock enable r.
        RCC->APB1ENR  |= (
                          //RCC_APB1ENR_TIM2EN  |
                          //RCC_APB1ENR_TIM3EN  |
                          //RCC_APB1ENR_TIM4EN  |
                          //RCC_APB1ENR_WWDGEN  |
                          //RCC_APB1ENR_SPI2EN  |
                          //RCC_APB1ENR_USART2EN|
                          //RCC_APB1ENR_USART3EN|
                          //RCC_APB1ENR_I2C1EN  |
                          //RCC_APB1ENR_I2C2EN  |
                          //RCC_APB1ENR_USBEN   |
                          //RCC_APB1ENR_CAN1EN  |
                          //RCC_APB1ENR_BKPEN   |
                          //RCC_APB1ENR_PWREN   |
                        0);

        //RCC->APB2ENR;     APB2 Peripherial clock enable r.
        RCC->APB2ENR  |= (
                          //RCC_APB2ENR_AFIOEN  |
                          //RCC_APB2ENR_IOPAEN  |
                          //RCC_APB2ENR_IOPBEN  |
                          //RCC_APB2ENR_IOPCEN  |
                          //RCC_APB2ENR_IOPDEN  |
                          //RCC_APB2ENR_IOPEEN  |
                          //RCC_APB2ENR_ADC1EN  |
                          //RCC_APB2ENR_ADC2EN  |
                          //RCC_APB2ENR_TIM1EN  |
                          //RCC_APB2ENR_SPI1EN  |
                          //RCC_APB2ENR_USART1EN|
                          //RCC_APB2ENR_ADC2EN  |
                        0);

        //RCC->BDCR;        Backup domain control r.
        RCC->BDCR   = 0;
    
    //  ��������� pll
        RCC->CR   |= RCC_CR_PLLON;
        while (!(RCC->CR & RCC_CR_PLLRDY))

    //  ��������� ������������ �� pll
        RCC->CFGR &= ~RCC_CFGR_SW;
        RCC->CFGR |= RCC_CFGR_SW_PLL;
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)

    main();
}

void main()
{
    while (1)
    {
        ;
    }
    
}