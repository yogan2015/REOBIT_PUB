#ifdef RELPATH
    #include "main.h"
    #include "rb_data.h"
#else
    #include "./inc/main.h"
    #include "./inc/rb_data.h"
#endif

void SystemInit()   
{

    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 0 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;


    //  переключение на HSE (на блюпилл - 8 МГц)
        RCC->CR |=  RCC_CR_HSEON;
        RCC->CR &= ~(RCC_CR_HSION | RCC_CR_CSSON | RCC_CR_PLLON | RCC_CR_HSEBYP);
        while (!(RCC->CR & RCC_CR_HSERDY));
        
    //  загрузка конфигурации проекта   (раскомментить нужное)
        //RCC->CFGR;        Clock configuration r.
        RCC->CFGR |= (  
                        RCC_CFGR_HPRE_DIV1         |
                        RCC_CFGR_PPRE1_DIV2        |
                        RCC_CFGR_PPRE2_DIV1        |
                        RCC_CFGR_ADCPRE_DIV6       |
                        RCC_CFGR_PLLSRC_HSE        |
                        RCC_CFGR_PLLXTPRE_HSE      |                    
                        RCC_CFGR_PLLMULL9          |
                        RCC_CFGR_USBPRE            
                        //RCC_CFGR_MCO_NOCLOCK
                        );

    //  включение pll
        RCC->CR   |= RCC_CR_PLLON;
        while (!(RCC->CR & RCC_CR_PLLRDY));

        //RCC->CR &= ~RCC_CR_HSION;
    //  включение тактирования от pll
        RCC->CFGR |= RCC_CFGR_SW_PLL;
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

        //RCC->CIR;         Clock interrupt r.
        //RCC->CIR =      0;

        //RCC->APB1RSTR;    APB1 Peripherial reset r.
        //RCC->APB1RSTR = 0;

        //RCC->APB2RSTR;    APB2 Peripherial reset r.
        //RCC->APB2RSTR = 0;

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
                          RCC_APB1ENR_USART3EN|
                          //RCC_APB1ENR_I2C1EN  |
                          //RCC_APB1ENR_I2C2EN  |
                          //RCC_APB1ENR_USBEN   |
                          //RCC_APB1ENR_CAN1EN  |
                          //RCC_APB1ENR_BKPEN   |
                          //RCC_APB1ENR_PWREN   |
                        0);

        //RCC->APB2ENR;     APB2 Peripherial clock enable r.
        RCC->APB2ENR  |= (
                          RCC_APB2ENR_AFIOEN  |
                          RCC_APB2ENR_IOPAEN  |
                          RCC_APB2ENR_IOPBEN  |
                          RCC_APB2ENR_IOPCEN  |
                          //RCC_APB2ENR_IOPDEN  |
                          //RCC_APB2ENR_IOPEEN  |
                          //RCC_APB2ENR_ADC1EN  |
                          //RCC_APB2ENR_ADC2EN  |
                          RCC_APB2ENR_TIM1EN  |
                          //RCC_APB2ENR_SPI1EN  |
                          //RCC_APB2ENR_USART1EN|
                          //RCC_APB2ENR_ADC2EN  |
                        0);

        //RCC->BDCR;        Backup domain control r.
        //RCC->BDCR   = 0;

    config_GPIO();
    config_TIM1_2();
    main();
}

static inline void config_GPIO()
{
    //  конфигурация GPIO
        GPIOC->CRH |= (GPIO_CRH_MODE13_0| GPIO_CRH_CNF13_0);
        GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_CNF9 | GPIO_CRH_CNF10);
        GPIOB->CRH &= ~(GPIO_CRH_CNF13| GPIO_CRH_CNF14| GPIO_CRH_CNF15);
        GPIOA->CRH |= (GPIO_CRH_MODE8_1| GPIO_CRH_MODE9_1| GPIO_CRH_MODE10_1|
                       GPIO_CRH_CNF8_1  | GPIO_CRH_CNF9_1  | GPIO_CRH_CNF10_1);
        GPIOB->CRH |= (GPIO_CRH_MODE13_1| GPIO_CRH_MODE14_1| GPIO_CRH_MODE15_1|
                       GPIO_CRH_CNF13_1 | GPIO_CRH_CNF14_1 | GPIO_CRH_CNF15_1);
}

static inline void config_TIM1()
{
    //  Вкл. TIM1
        //  TIM1 Control r. 1
            TIM1->CR1 |= (
                            TIM_CR1_CEN     |
            //              TIM_CR1_UDIS    |
            //              TIM_CR1_URS     |
            //              TIM_CR1_OPM     |
            //              TIM_CR1_DIR     |
                            TIM_CR1_CMS_0   | //TIM_CR1_CMS_1   |
                            TIM_CR1_ARPE    |
            //              TIM_CR1_CKD     |
                            0);
        //  TIM1 Control r. 2
            TIM1->CCR2 |= (
            //              TIM_CR2_CCPC    |
            //              TIM_CR2_CCUS    |
            //              TIM_CR2_CCDS    |
            //              TIM_CR2_MMS_0   |   TIM_CR2_MMS_1   |   TIM_CR2_MMS_2   |
            //              TIM_CR2_TI1S    |
            //              TIM_CR2_OIS1    |
            //              TIM_CR2_OIS1N   |
            //              TIM_CR2_OIS2    |
            //              TIM_CR2_OIS2N   |
            //              TIM_CR2_OIS3    |
            //              TIM_CR2_OIS3N   |
            //              TIM_CR2_OIS4    |
                            0);
        //  TIM1 slave mode control r.
            //TIM1->SMCR;

        //  TIM1 DMA/interrupt enable register
            TIM1->DIER |= (
            //              TIM_DIER_UIE    |
            //              TIM_DIER_CC1IE  |
            //              TIM_DIER_CC2IE  |
            //              TIM_DIER_CC3IE  |
            //              TIM_DIER_CC4IE  |
            //              TIM_DIER_COMIE  |
            //              TIM_DIER_TIE    |
            //              TIM_DIER_BIE    |
            //              TIM_DIER_UDE    |
            //              TIM_DIER_CC1DE  |
            //              TIM_DIER_CC2DE  |
            //              TIM_DIER_CC3DE  |
            //              TIM_DIER_CC4DE  |
            //              TIM_DIER_COMDE  |
            //              TIM_DIER_TDE    |
                            0);

        //  TIM1 event generation r.
            TIM1->EGR |= (
                            TIM_EGR_UG      |
            //              TIM_EGR_CC1G    |
            //              TIM_EGR_CC2G    |
            //              TIM_EGR_CC3G    |
            //              TIM_EGR_CC4G    |
            //              TIM_EGR_TG      |
            //               TIM_EGR_BG      |
                            0);
        //  TIM1 capture/compare mode r. 1
            TIM1->CCMR1 |= (
            //              TIM_CCMR1_CC1S_0    |   TIM_CCMR1_CC1S_1 |
            //              TIM_CCMR1_OC1FE     |
                            TIM_CCMR1_OC1PE     |
                            TIM_CCMR1_OC1M_0    |   TIM_CCMR1_OC1M_1 |  TIM_CCMR1_OC1M_2    |
            //              TIM_CCMR1_OC1CE     |
            //              TIM_CCMR1_CC2S_0    |   TIM_CCMR1_CC2S_1 |
            //              TIM_CCMR1_OC2FE     |
                            TIM_CCMR1_OC2PE     |
                            TIM_CCMR1_OC2M_0    |   TIM_CCMR1_OC2M_1 |  TIM_CCMR1_OC2M_2    |
            //              TIM_CCMR1_OC2CE     |
                            0);

        //  TIM1 capture/compare mode r. 2
            TIM1->CCMR2 |= (
            //              TIM_CCMR2_CC3S_0    |   TIM_CCMR2_CC3S_1 |
            //              TIM_CCMR2_OC3FE     |
                            TIM_CCMR2_OC3PE     |
                            TIM_CCMR2_OC3M_0    |   TIM_CCMR2_OC3M_1 |  TIM_CCMR2_OC3M_2    |
            //              TIM_CCMR2_OC3CE     |
            //              TIM_CCMR2_CC4S_0    |   TIM_CCMR2_CC4S_1 |
            //              TIM_CCMR2_OC4FE     |
            //              TIM_CCMR2_OC4PE     |
            //              TIM_CCMR2_OC4M_0    |   TIM_CCMR2_OC4M_1    TIM_CCMR2_OC4M_2    |
            //              TIM_CCMR2_OC4CE     |
                            0);

        //  TIM1 capture/compare enable r.
            TIM1->CCER |= (
            //              TIM_CCER_CC1E   |
            //              TIM_CCER_CC1P   |
            //              TIM_CCER_CC1NE  |
            //              TIM_CCER_CC1NP  |
            //              TIM_CCER_CC2E   |
            //              TIM_CCER_CC2P   |
            //              TIM_CCER_CC2NE  |
            //              TIM_CCER_CC2NP  |
            //              TIM_CCER_CC3E   |
            //              TIM_CCER_CC3P   |
            //              TIM_CCER_CC3NE  |
            //              TIM_CCER_CC3NP  |
            //              TIM_CCER_CC4E   |
            //              TIM_CCER_CC4P   |
            //              TIM_CCER_CC4NP  |
                            0);

        //  TIM1 break and dead-time r.
            TIM1->BDTR |= (
            //              TIM_BDTR_DTG    |
            //              TIM_BDTR_LOCK_0 |   TIM_BDTR_LOCK_1 |
            //              TIM_BDTR_OSSI   |
            //              TIM_BDTR_OSSR   |
            //              TIM_BDTR_BKE    |
            //              TIM_BDTR_BKP    |
            //              TIM_BDTR_AOE    |
            //              TIM_BDTR_MOE    |
                            0);
        
        //  TIM1 DMA control r.
            TIM1->DCR |= (
            //              TIM_DCR_DBA     |
            //              TIM_DCR_DBL     |
                            0);

        //  TIM1 DMA address for full transfer
            TIM1->DMAR |= (
            //              TIM_DMAR_DMAB   |
                            0);
        
        TIM1->PSC   =   1000;
        TIM1->ARR   =   1000;
        TIM1->CCR1  =   500;
        TIM1->CCR2  =   500;
        TIM1->CCR3  =   500;
}

static inline void config_TIM1_2()
{
    //NVIC_EnableIRQ(TIM1_CC_IRQn);
    TIM1->PSC = 0;
    TIM1->ARR = 72-1;    
    TIM1->CCR1 = 36;    TIM1->CCR2 = 36;    TIM1->CCR3 = 36;
    TIM1->CR1 |= TIM_CR1_CMS_0 | TIM_CR1_ARPE;
    //TIM1->CCR2 = 0x1000;
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E
                | TIM_CCER_CC1NE| TIM_CCER_CC2NE| TIM_CCER_CC3NE 
                | TIM_CCER_CC1P | TIM_CCER_CC2P | TIM_CCER_CC3P;
    TIM1->BDTR |= TIM_BDTR_MOE;    
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2
                |  TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
    //TIM1->CR1  |= TIM_CR1_CEN;
    TIM1->DIER |= TIM_DIER_CC1IE;
    TIM1->CR1  |= TIM_CR1_CEN;   
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