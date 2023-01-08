#define CORE_CM7

#ifdef RELPATH
    #include "main.h"
#else
    #include "inc/main.h"
#endif

void main()
{
    int a = 1;

    RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
    GPIOB->MODER &= (~(GPIO_MODER_MODE14_Msk | GPIO_MODER_MODE0_Msk) | GPIO_MODER_MODE14_0 | GPIO_MODER_MODE0_0);
    while(1){
        GPIOB->BSRR |= GPIO_BSRR_BS14 | GPIO_BSRR_BR0;
        for(int i = 0; i<120000; i++);        
        GPIOB->BSRR |= GPIO_BSRR_BR14 | GPIO_BSRR_BS0;
        for(int i = 0; i<120000; i++);
    }
}

void SystemInit()
{
    // выполняется до main()
    const uint32_t RB_RCC_CR        = 0x00000000;
    const uint32_t RB_RCC_HSICFGR   = 0x00000000;
    const uint32_t RB_RCC_CRRCR     = 0x00000000;
    const uint32_t RB_RCC_CSICFGR   = 0x00000000;
    const uint32_t RB_RCC_CFGR      = 0x00000000;
    const uint32_t RB_RCC_D1CFGR    = 0x00000000;
    const uint32_t RB_RCC_D2CFGR    = 0x00000000;
    const uint32_t RB_RCC_D3CFGR    = 0x00000000;
    const uint32_t RB_RCC_PLLCKSELR = 0x00000000;
    const uint32_t RB_RCC_PLLCFGR   = 0x00000000;
    const uint32_t RB_RCC_PLL1DIVR  = 0x00000000;
    const uint32_t RB_RCC_PLL2DIVR  = 0x00000000;
    const uint32_t RB_RCC_PLL3DIVR  = 0x00000000;
    const uint32_t RB_RCC_PLL1FRACR = 0x00000000;
    const uint32_t RB_RCC_PLL2FRACR = 0x00000000;
    const uint32_t RB_RCC_PLL3FRACR = 0x00000000;
    const uint32_t RB_RCC_D1CCIPR   = 0x00000000;
    const uint32_t RB_RCC_D2CCIP1R  = 0x00000000;
    const uint32_t RB_RCC_D2CCIP2R  = 0x00000000;
    const uint32_t RB_RCC_D3CCIPR   = 0x00000000;
    const uint32_t RB_RCC_CIER      = 0x00000000;
    const uint32_t RB_RCC_CIFR      = 0x00000000;
    const uint32_t RB_RCC_CICR      = 0x00000000;
    const uint32_t RB_RCC_BDCR      = 0x00000000;
    const uint32_t RB_RCC_CSR       = 0x00000000;
    const uint32_t RB_RCC_AHB1RSTR  = 0x00000000;
    const uint32_t RB_RCC_AHB2RSTR  = 0x00000000;
    const uint32_t RB_RCC_AHB3RSTR  = 0x00000000;
    const uint32_t RB_RCC_AHB4RSTR  = 0x00000000;
    const uint32_t RB_RCC_APB3RSTR  = 0x00000000;
    const uint32_t RB_RCC_APB1LRSTR = 0x00000000;
    const uint32_t RB_RCC_APB1HRSTR = 0x00000000;
    const uint32_t RB_RCC_APB2RSTR  = 0x00000000;
    const uint32_t RB_RCC_APB4RSTR  = 0x00000000;
    const uint32_t RB_RCC_GCR       = 0x00000000;
    const uint32_t RB_RCC_D3AMR     = 0x00000000;
    const uint32_t RB_RCC_RSR       = 0x00000000;
    const uint32_t RB_RCC_AHB1ENR   = 0x00000000;
    const uint32_t RB_RCC_AHB2ENR   = 0x00000000;
    const uint32_t RB_RCC_AHB3ENR   = 0x00000000;
    const uint32_t RB_RCC_AHB4ENR   = 0x00000000;
    const uint32_t RB_RCC_APB1HENR  = 0x00000000;
    const uint32_t RB_RCC_APB1LENR  = 0x00000000;
    const uint32_t RB_RCC_APB2ENR   = 0x00000000;
    const uint32_t RB_RCC_APB3ENR   = 0x00000000;
    const uint32_t RB_RCC_APB4ENR   = 0x00000000;

    const uint32_t RB_RCC_AHB1LPENR = 0x00000000;
    const uint32_t RB_RCC_AHB2LPENR = 0x00000000;
    const uint32_t RB_RCC_AHB3LPENR = 0x00000000;
    const uint32_t RB_RCC_AHB4LPENR = 0x00000000;

    const uint32_t RB_RCC_APB1LLPENR= 0x00000000;
    const uint32_t RB_RCC_APB1HLPENR= 0x00000000;
    const uint32_t RB_RCC_APB2LPENR = 0x00000000;
    const uint32_t RB_RCC_APB3LPENR = 0x00000000;
    const uint32_t RB_RCC_APB4LPENR = 0x00000000;

    // адреса для совместимости с другими продуктами
#ifdef RB_use_C1
    const uint32_t RB_RCC_C1_AHB1ENR= 0x00000000;
    const uint32_t RB_RCC_C1_AHB2ENR= 0x00000000;
    const uint32_t RB_RCC_C1_AHB3ENR= 0x00000000;
    const uint32_t RB_RCC_C1_AHB4ENR= 0x00000000;

    const uint32_t RB_RCC_C1_APB1LENR   = 0x00000000;
    const uint32_t RB_RCC_C1_APB1HENR   = 0x00000000;
    const uint32_t RB_RCC_C1_APB2ENR    = 0x00000000;
    const uint32_t RB_RCC_C1_APB3ENR    = 0x00000000;
    const uint32_t RB_RCC_C1_APB4ENR    = 0x00000000;
    
    const uint32_t RB_RCC_C1_AHB1LPENR  = 0x00000000;
    const uint32_t RB_RCC_C1_AHB2LPENR  = 0x00000000;
    const uint32_t RB_RCC_C1_AHB3LPENR  = 0x00000000;
    const uint32_t RB_RCC_C1_AHB4LPENR  = 0x00000000;

    const uint32_t RB_RCC_C1_APB1LLPENR = 0x00000000;
    const uint32_t RB_RCC_C1_APB1HLPENR = 0x00000000;
    const uint32_t RB_RCC_C1_APB2LPENR  = 0x00000000;
    const uint32_t RB_RCC_C1_APB3LPENR  = 0x00000000;
    const uint32_t RB_RCC_C1_APB4LPENR  = 0x00000000;
#endif
    SYSCFG->UR1 |= SYSCFG_UR1_BCM4;
    main();
}

void ADC3_IRQHandler()  //asdasda
{
    int a = 0xDEADBEEF;  //aaaa
}

void TIM15_IRQHandler()
{
    ;
}