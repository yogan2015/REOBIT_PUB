#include "../inc/main.h"

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