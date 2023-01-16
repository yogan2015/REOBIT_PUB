#include "../inc/main.h"

static inline void config_TIM1()
{
        TIM1->PSC   =   71-1;
        TIM1->ARR   =   1024-1;
    //  Âêë. TIM1
        //  TIM1 Control r. 1
            TIM1->CR1 |= (
            //              TIM_CR1_CEN     |
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
            //              TIM_EGR_UG      |
            //              TIM_EGR_CC1G    |
            //              TIM_EGR_CC2G    |
            //              TIM_EGR_CC3G    |
            //              TIM_EGR_CC4G    |
            //              TIM_EGR_TG      |
            //               TIM_EGR_BG      |
                            0);
        //  TIM1 capture/compare enable r.

            TIM1->CCER |= (
                            TIM_CCER_CC1E   |
                            TIM_CCER_CC1P   |
                            TIM_CCER_CC1NE  |
            //              TIM_CCER_CC1NP  |
                            TIM_CCER_CC2E   |
                            TIM_CCER_CC2P   |
                            TIM_CCER_CC2NE  |
            //              TIM_CCER_CC2NP  |
                            TIM_CCER_CC3E   |
                            TIM_CCER_CC3P   |
                            TIM_CCER_CC3NE  |
            //              TIM_CCER_CC3NP  |
            //              TIM_CCER_CC4E   |
            //              TIM_CCER_CC4P   |
            //              TIM_CCER_CC4NP  |
                            0);
        //  TIM1 capture/compare mode r. 1
            TIM1->CCMR1 |= (
            //              TIM_CCMR1_CC1S_0    |   TIM_CCMR1_CC1S_1 |
            //              TIM_CCMR1_OC1FE     |
            //              TIM_CCMR1_OC1PE     |
                            TIM_CCMR1_OC1M_1    |  TIM_CCMR1_OC1M_2    |
            //              TIM_CCMR1_OC1CE     |
            //              TIM_CCMR1_CC2S_0    |   TIM_CCMR1_CC2S_1 |
            //              TIM_CCMR1_OC2FE     |
            //              TIM_CCMR1_OC2PE     |
                            TIM_CCMR1_OC2M_1    |  TIM_CCMR1_OC2M_2    |
            //              TIM_CCMR1_OC2CE     |
                            0);

        //  TIM1 capture/compare mode r. 2
            TIM1->CCMR2 |= (
            //              TIM_CCMR2_CC3S_0    |   TIM_CCMR2_CC3S_1 |
            //              TIM_CCMR2_OC3FE     |
            //              TIM_CCMR2_OC3PE     |
                            TIM_CCMR2_OC3M_1    |  TIM_CCMR2_OC3M_2    |
            //              TIM_CCMR2_OC3CE     |
            //              TIM_CCMR2_CC4S_0    |   TIM_CCMR2_CC4S_1 |
            //              TIM_CCMR2_OC4FE     |
            //              TIM_CCMR2_OC4PE     |
            //              TIM_CCMR2_OC4M_0    |   TIM_CCMR2_OC4M_1    TIM_CCMR2_OC4M_2    |
            //              TIM_CCMR2_OC4CE     |
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
                            TIM_BDTR_MOE    |
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

        // Start
            TIM1->CR1 |= TIM_CR1_CEN;
            TIM1->CCR1 = 511;
            TIM1->CCR2 = 511;
            TIM1->CCR3 = 511;
}
