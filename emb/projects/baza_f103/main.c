#ifdef RELPATH
    #include "main.h"
    #include "rb_data.h"
#else
    #include "./inc/main.h"
    #include "./inc/rb_data.h"
#endif

void SystemInit()   // Настройка RCC на 72 MHz
{
    #ifdef ASS
        // HSI    
        RCC->CR |= RCC_CR_HSION;        // Включаем High-speed internal, 8MHz

        RCC->CR &=      ~(RCC_CR_HSEON      // High-speed external выкл.
                        | RCC_CR_CSSON      // Clock Security system выкл.
                        | RCC_CR_PLLON);    // PLL выкл.

        RCC->CR &=      ~(RCC_CR_HSEBYP);   // HSE Bypass выкл.

        // RCC->CFGR при сбросе инициализируется 0x00000000, тут на всякий случай делаем сброс
        RCC->CFGR &=    ~(RCC_CFGR_SW       // 00
                        //| RCC_CFGR_SWS    // read-only биты, сбрасывать не надо 
                        | RCC_CFGR_HPRE     // AHB Prescaler
                        | RCC_CFGR_PPRE1    // APB1 Prescaler
                        | RCC_CFGR_PPRE2    // APB2 Prescaler
                        | RCC_CFGR_ADCPRE   // ADC Prescaler
                        | RCC_CFGR_MCO);    // 4bit - Connectivity Line, иначе 3bit

        RCC->CFGR &=    ~(RCC_CFGR_PLLSRC   // PLL source
                        | RCC_CFGR_PLLXTPRE // PLL Divider
                        | RCC_CFGR_PLLMULL  // PLL Multiplication Factor 
                        | RCC_CFGR_USBPRE); // USB Prescaler

        RCC->CIR &=     ~(RCC_CIR_LSERDYIE  // Low-speed External
                        | RCC_CIR_LSIRDYIE  // Low-speed Internal
                        | RCC_CIR_HSIRDYIE  // High-speed Internal
                        | RCC_CIR_HSERDYIE  // High-speed External
                        | RCC_CIR_PLLRDYIE  // PLL
                        
                        | RCC_CIR_LSIRDYC  // Low-speed External
                        | RCC_CIR_LSERDYC  // Low-speed Internal
                        | RCC_CIR_HSIRDYC  // High-speed Internal
                        | RCC_CIR_HSERDYC  // High-speed External
                        | RCC_CIR_PLLRDYC  // PLL
                        | RCC_CIR_CSSC);   // Clock System Security

        // Устанавливаем частоту тактирования
        RCC->CR |= RCC_CR_HSEON;    // High-Speed External 9MHz
        while (!(RCC->CR & RCC_CR_HSERDY))

        FLASH->ACR  |= FLASH_ACR_PRFTBE;
        FLASH->ACR  &=~FLASH_ACR_LATENCY;
        FLASH->ACR  |= FLASH_ACR_LATENCY_2;
        
        RCC->CFGR   |=  RCC_CFGR_HPRE_DIV1;     // AHB Тактируется с частотой 72MHz SYSCLK
        RCC->CFGR   |=  RCC_CFGR_PPRE1_DIV2;    // APB1 тактируется AHB/2 с частотой 36MHz
        RCC->CFGR   |=  RCC_CFGR_PPRE2_DIV1;    // APB2 тактируется AHB с частотой 72MHz

        RCC->CFGR   &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
        RCC->CFGR   |=  (RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);    // Заводим HSEx9 на вход PLL
        
        RCC->CR   |=  RCC_CR_PLLON;             //  Включаем PLL
        while(!(RCC->CR & RCC_CR_PLLRDY));

        RCC->CFGR   &= ~RCC_CFGR_SW;
        RCC->CFGR   |=  RCC_CFGR_SW_PLL;        //  Устанавливаем PLL в качестве источника SYSCLK
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
    #endif
    main();
}

void main()
{

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH |= GPIO_CRH_MODE13_1;
    RCC->CFGR |= RCC_CFGR_PLLMULL9;
    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
    while(1){
        GPIOC->BSRR |= GPIO_BSRR_BR13;
        for (uint32_t i = 0; i<100000; i++){}
        GPIOC->BSRR |= GPIO_BSRR_BS13;
        for (uint32_t i = 0; i<100000; i++){}
    }

}