#ifdef RELPATH
    #include "main.h"
    #include "PWM_macros.h"
#else
    #include "../inc/main.h"
    #include "../inc/PWM_macros.h"
#endif

#define rb_PWM_PERIOD 0x1FFFFFF
#define rb_TIM_PERIOD 0x1FFFFF
void Init_TIM0()
{
    volatile uint32_t priority;
    volatile uint32_t priorityGroup;
    extern int *g_pfnVectors;

    //SCB->VTOR = (uint32_t)(&g_pfnVectors);
    //DINT;

    //NVIC_SetPriorityGrouping(4);
    //priorityGroup = NVIC_GetPriorityGrouping();

    NVIC_DisableIRQ(TIM0_IRQn);
    NVIC_ClearPendingIRQ(TIM0_IRQn);

    NVIC_EnableIRQ(TIM0_IRQn);
    //priority = NVIC_EncodePriority(priorityGroup, IRQ_PRIORITY_10K, 0);
    //NVIC_SetPriority(TIM0_IRQn, priority);

    NT_TIMER0->INTSTATUS_INTCLEAR_bit.INT   = 1;
    NT_TIMER0->RELOAD                       = rb_TIM_PERIOD;        // 3,57 kHz 2^13 дискрет
    NT_TIMER0->CTRL                        |= (0b1001);

    //EINT;
}

void Init_TIM1()
{
    ;
}

void Init_TIM2()
{
    ;
}

void Init_PWM_common()
{
    NT_GPIOG->ALTFUNCSET_bit.ALTFUNCSET |= (0x7 << 5);      
    NT_GPIOA->ALTFUNCSET_bit.ALTFUNCSET |= (0x7 << 13);

    NT_COMMON_REG->PWM_CTRL             = (0x0);        // схема синхронизации последовательная, от таймера PWM0 

    //     PWM0          остановлен               Фаза уст. при синхр.    Источник синхр. - CTR=0             Счет вверх            
        NT_PWM0->TBCTL = (0x2                    | PWM_TBCTL_PHSEN_Msk   | (0b01 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk | PWM_TBCTL_FREE_SOFT_Msk);
        // PWM1-5        остановлен               Фаза уст. при синхр.    Источник синхр. - PWM0              Счет вверх       
        NT_PWM1->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        NT_PWM2->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        NT_PWM3->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        NT_PWM4->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        NT_PWM5->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        // PWM6          остановлен               Фаза уст. при синхр.    Источник синхр. - PWM0              Счет вверх       
        NT_PWM6->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);

    // Начальные фазы сигналов с учетом такта синхронизации
        NT_PWM0->TBPHS = 0;
        NT_PWM1->TBPHS = 1;
        NT_PWM2->TBPHS = 2;
        NT_PWM3->TBPHS = 3;
        NT_PWM4->TBPHS = 4;
        NT_PWM5->TBPHS = 5;

        NT_PWM6->TBPHS = 6;
        
    NT_COMMON_REG->PWM_SYNC &=~(0x01FF);    // сброс всех счетчиков

    // Период таймера
        NT_PWM0->TBPRD = rb_PWM_PERIOD;    // 2^13 - 3,57kHz
        NT_PWM1->TBPRD = rb_PWM_PERIOD;              
        NT_PWM2->TBPRD = rb_PWM_PERIOD;              
        NT_PWM3->TBPRD = rb_PWM_PERIOD;              
        NT_PWM4->TBPRD = rb_PWM_PERIOD;              
        NT_PWM5->TBPRD = rb_PWM_PERIOD;  
                    
        NT_PWM6->TBPRD = rb_PWM_PERIOD;  

    //     Компараторы
        NT_PWM0->CMPCTL = 0;        // CMPA, CMPB загружаются при CTR=0x0, CMPA загружается через теневой регистр
        NT_PWM1->CMPCTL = 0;
        NT_PWM2->CMPCTL = 0;
        NT_PWM3->CMPCTL = 0;
        NT_PWM4->CMPCTL = 0;
        NT_PWM5->CMPCTL = 0;   
        // PWM6
        NT_PWM6->CMPCTL = 0;         

    //     Начальное значение компараторов
        NT_PWM0->CMPA = 1+rb_PWM_PERIOD; NT_PWM0->CMPB = 1+rb_PWM_PERIOD;      // Никаких событий не происходит, т.к. CMPA>TBPRD
        NT_PWM1->CMPA = 1+rb_PWM_PERIOD; NT_PWM1->CMPB = 1+rb_PWM_PERIOD;
        NT_PWM2->CMPA = 1+rb_PWM_PERIOD; NT_PWM2->CMPB = 1+rb_PWM_PERIOD;
        NT_PWM3->CMPA = 1+rb_PWM_PERIOD; NT_PWM3->CMPB = 1+rb_PWM_PERIOD;
        NT_PWM4->CMPA = 1+rb_PWM_PERIOD; NT_PWM4->CMPB = 1+rb_PWM_PERIOD;
        NT_PWM5->CMPA = 1+rb_PWM_PERIOD; NT_PWM5->CMPB = 1+rb_PWM_PERIOD;
        // PWM6
        NT_PWM6->CMPA = 1+rb_PWM_PERIOD; NT_PWM6->CMPB = 1+rb_PWM_PERIOD;
    
    //     События компараторов
        NT_PWM0->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos));  // A включен при CTR>CMPA
        NT_PWM0->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));  // B включен при CTR<>>CMPA
        NT_PWM1->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM1->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        NT_PWM2->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM2->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        
        NT_PWM3->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM3->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        NT_PWM4->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM4->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        NT_PWM5->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM5->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        // PWM6
        NT_PWM6->AQCTLA = 0; NT_PWM6->AQCTLB = 0;   // выходы не используются

    //     Мертвое время - пока не используем, походу не обеспечивается симметричность. Можно вместо этого вводить разницу между CMPA и CMPB, сохраняя их сумму
        NT_PWM0->DBCTL = 0; NT_PWM0->DBRED = 0; NT_PWM0->DBFED = 0;
        NT_PWM1->DBCTL = 0; NT_PWM1->DBRED = 0; NT_PWM1->DBFED = 0;
        NT_PWM2->DBCTL = 0; NT_PWM2->DBRED = 0; NT_PWM2->DBFED = 0;
        NT_PWM3->DBCTL = 0; NT_PWM3->DBRED = 0; NT_PWM3->DBFED = 0;
        NT_PWM4->DBCTL = 0; NT_PWM4->DBRED = 0; NT_PWM4->DBFED = 0;
        NT_PWM5->DBCTL = 0; NT_PWM5->DBRED = 0; NT_PWM5->DBFED = 0;
        // PWM6
        NT_PWM6->DBCTL = 0; NT_PWM6->DBRED = 0; NT_PWM6->DBFED = 0;
 
    // Выбор источника аварии - потом проверить! Прерывания включить
        //NT_PWM0->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM0->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM1->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM1->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM2->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM2->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM3->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM3->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM4->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM4->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM5->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM5->TZEINT = PWM_TZEINT_OST_Msk;
        // PWM6
        NT_PWM0->TZSEL = 0;                     NT_PWM0->TZEINT = 0;

    // Дейтвия при аварии
        NT_PWM0->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));    // Оба выхода в ноль
        NT_PWM1->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        NT_PWM2->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        NT_PWM3->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        NT_PWM4->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        NT_PWM5->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        // PWM6 пусть считает 

    // Предварительный сброс флагов прерываний
        NT_PWM0->TZCLR |= 0x7;  NT_PWM0->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM1->TZCLR |= 0x7;  NT_PWM1->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM2->TZCLR |= 0x7;  NT_PWM2->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM3->TZCLR |= 0x7;  NT_PWM3->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM4->TZCLR |= 0x7;  NT_PWM4->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM5->TZCLR |= 0x7;  NT_PWM5->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        
        NT_PWM6->TZCLR |= 0x7;  NT_PWM6->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;

    // Прерывание SOC по таймеру 6
        //NT_PWM6->ETSEL |= PWM_ETSEL_SOCAEN_Msk  | (0b100 << PWM_ETSEL_SOCASEL_Pos);   //  CMPA вызывает прерывание SOQ
        NT_PWM0->ETSEL |= (PWM_ETSEL_INTEN_Msk   | (0b110 << PWM_ETSEL_INTSEL_Pos));      //  CMPB вызывает прерывание PWM6

    // Предделитель счетчика событий
        NT_PWM0->ETPS = 0;  // по умолчанию считаем каждое событие

    //DINT;
    //NVIC_DisableIRQ(PWM0_IRQn);
    NVIC_ClearPendingIRQ(PWM0_IRQn);
    NVIC_EnableIRQ(PWM0_IRQn);
    //EINT;

    NT_PWM0->CMPB = 0x0FFF;
    NT_PWM0->TBCTL &=~(0x1);
    NT_PWM1->TBCTL &=~(0x1);
    NT_PWM2->TBCTL &=~(0x1);
    NT_PWM3->TBCTL &=~(0x1);
    NT_PWM4->TBCTL &=~(0x1);
    NT_PWM5->TBCTL &=~(0x1);
    NT_PWM6->TBCTL &=~(0x1);
}

void Init_PWM_common_foof()
{
    NT_GPIOG->ALTFUNCSET_bit.ALTFUNCSET |= (0x7 << 5);      
    NT_GPIOA->ALTFUNCSET_bit.ALTFUNCSET |= (0x7 << 13);

    NT_COMMON_REG->PWM_CTRL             = (0x0);        // схема синхронизации последовательная, от таймера PWM0 

    //     PWM0          остановлен               Фаза уст. при синхр.    Источник синхр. - CTR=0             Счет вверх            
        NT_PWM0->TBCTL = (0x2                    | PWM_TBCTL_PHSEN_Msk   | (0b01 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk | PWM_TBCTL_FREE_SOFT_Msk);
        // PWM1-5        остановлен               Фаза уст. при синхр.    Источник синхр. - PWM0              Счет вверх       
        NT_PWM1->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        NT_PWM2->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        NT_PWM3->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        NT_PWM4->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        NT_PWM5->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);
        // PWM6          остановлен               Фаза уст. при синхр.    Источник синхр. - PWM0              Счет вверх       
        NT_PWM6->TBCTL = (PWM_TBCTL_CTRMODE_Msk  | PWM_TBCTL_PHSEN_Msk   | (0b00 << PWM_TBCTL_SYNCOSEL_Pos)  | PWM_TBCTL_PHSDIR_Msk);

    // Начальные фазы сигналов с учетом такта синхронизации
        NT_PWM0->TBPHS = 0;
        NT_PWM1->TBPHS = 1;
        NT_PWM2->TBPHS = 2;
        NT_PWM3->TBPHS = 3;
        NT_PWM4->TBPHS = 4;
        NT_PWM5->TBPHS = 5;

        NT_PWM6->TBPHS = 6;
        
    NT_COMMON_REG->PWM_SYNC &=~(0x01FF);    // сброс всех счетчиков

    // Период таймера
        NT_PWM0->TBPRD = rb_PWM_PERIOD;    // 2^13 - 3,57kHz
        NT_PWM1->TBPRD = rb_PWM_PERIOD;              
        NT_PWM2->TBPRD = rb_PWM_PERIOD;              
        NT_PWM3->TBPRD = rb_PWM_PERIOD;              
        NT_PWM4->TBPRD = rb_PWM_PERIOD;              
        NT_PWM5->TBPRD = rb_PWM_PERIOD;  
                    
        NT_PWM6->TBPRD = rb_PWM_PERIOD;  

    //     Компараторы
        NT_PWM0->CMPCTL = 0;        // CMPA, CMPB загружаются при CTR=0x0, CMPA загружается через теневой регистр
        NT_PWM1->CMPCTL = 0;
        NT_PWM2->CMPCTL = 0;
        NT_PWM3->CMPCTL = 0;
        NT_PWM4->CMPCTL = 0;
        NT_PWM5->CMPCTL = 0;   
        // PWM6
        NT_PWM6->CMPCTL = 0;         

    //     Начальное значение компараторов
        NT_PWM0->CMPA = 1+rb_PWM_PERIOD; NT_PWM0->CMPB = 1+rb_PWM_PERIOD;      // Никаких событий не происходит, т.к. CMPA>TBPRD
        NT_PWM1->CMPA = 1+rb_PWM_PERIOD; NT_PWM1->CMPB = 1+rb_PWM_PERIOD;
        NT_PWM2->CMPA = 1+rb_PWM_PERIOD; NT_PWM2->CMPB = 1+rb_PWM_PERIOD;
        NT_PWM3->CMPA = 1+rb_PWM_PERIOD; NT_PWM3->CMPB = 1+rb_PWM_PERIOD;
        NT_PWM4->CMPA = 1+rb_PWM_PERIOD; NT_PWM4->CMPB = 1+rb_PWM_PERIOD;
        NT_PWM5->CMPA = 1+rb_PWM_PERIOD; NT_PWM5->CMPB = 1+rb_PWM_PERIOD;
        // PWM6
        NT_PWM6->CMPA = 1+rb_PWM_PERIOD; NT_PWM6->CMPB = 1+rb_PWM_PERIOD;
    
    //     События компараторов
        NT_PWM0->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos));  // A включен при CTR>CMPA
        NT_PWM0->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));  // B включен при CTR<>>CMPA
        NT_PWM1->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM1->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        NT_PWM2->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM2->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        
        NT_PWM3->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM3->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        NT_PWM4->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM4->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        NT_PWM5->AQCTLA = ((01 << PWM_AQCTLA_CAD_Pos) | (10 << PWM_AQCTLA_CAU_Pos)); 
        NT_PWM5->AQCTLB = ((10 << PWM_AQCTLA_CAD_Pos) | (01 << PWM_AQCTLA_CAU_Pos));
        // PWM6
        NT_PWM6->AQCTLA = 0; NT_PWM6->AQCTLB = 0;   // выходы не используются

    //     Мертвое время - пока не используем, походу не обеспечивается симметричность. Можно вместо этого вводить разницу между CMPA и CMPB, сохраняя их сумму
        NT_PWM0->DBCTL = 0; NT_PWM0->DBRED = 0; NT_PWM0->DBFED = 0;
        NT_PWM1->DBCTL = 0; NT_PWM1->DBRED = 0; NT_PWM1->DBFED = 0;
        NT_PWM2->DBCTL = 0; NT_PWM2->DBRED = 0; NT_PWM2->DBFED = 0;
        NT_PWM3->DBCTL = 0; NT_PWM3->DBRED = 0; NT_PWM3->DBFED = 0;
        NT_PWM4->DBCTL = 0; NT_PWM4->DBRED = 0; NT_PWM4->DBFED = 0;
        NT_PWM5->DBCTL = 0; NT_PWM5->DBRED = 0; NT_PWM5->DBFED = 0;
        // PWM6
        NT_PWM6->DBCTL = 0; NT_PWM6->DBRED = 0; NT_PWM6->DBFED = 0;
 
    // Выбор источника аварии - потом проверить! Прерывания включить
        //NT_PWM0->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM0->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM1->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM1->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM2->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM2->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM3->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM3->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM4->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM4->TZEINT = PWM_TZEINT_OST_Msk;
        //NT_PWM5->TZSEL = PWM_TZSEL_OSHT0_Msk;   NT_PWM5->TZEINT = PWM_TZEINT_OST_Msk;
        // PWM6
        NT_PWM0->TZSEL = 0;                     NT_PWM0->TZEINT = 0;

    // Дейтвия при аварии
        NT_PWM0->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));    // Оба выхода в ноль
        NT_PWM1->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        NT_PWM2->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        NT_PWM3->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        NT_PWM4->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        NT_PWM5->TZCTL |= ((0b10 << PWM_TZCTL_TZA_Pos) | (0b10 << PWM_TZCTL_TZB_Pos));
        // PWM6 пусть считает 

    // Предварительный сброс флагов прерываний
        NT_PWM0->TZCLR |= 0x7;  NT_PWM0->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM1->TZCLR |= 0x7;  NT_PWM1->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM2->TZCLR |= 0x7;  NT_PWM2->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM3->TZCLR |= 0x7;  NT_PWM3->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM4->TZCLR |= 0x7;  NT_PWM4->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        NT_PWM5->TZCLR |= 0x7;  NT_PWM5->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;
        
        NT_PWM6->TZCLR |= 0x7;  NT_PWM6->TZINTCLR |= PWM_TZINTCLR_TZINT_Msk;

    // Прерывание SOC по таймеру 6
        //NT_PWM6->ETSEL |= PWM_ETSEL_SOCAEN_Msk  | (0b100 << PWM_ETSEL_SOCASEL_Pos);   //  CMPA вызывает прерывание SOQ
        NT_PWM0->ETSEL |= (PWM_ETSEL_INTEN_Msk   | (0b110 << PWM_ETSEL_INTSEL_Pos));      //  CMPB вызывает прерывание PWM6

    // Предделитель счетчика событий
        NT_PWM0->ETPS = 0;  // по умолчанию считаем каждое событие

    //DINT;
    //NVIC_DisableIRQ(PWM0_IRQn);
    NVIC_ClearPendingIRQ(PWM0_IRQn);
    NVIC_EnableIRQ(PWM0_IRQn);
    //EINT;

    NT_PWM0->CMPB = 0x0FFF;
    NT_PWM0->TBCTL &=~(0x1);
    NT_PWM1->TBCTL &=~(0x1);
    NT_PWM2->TBCTL &=~(0x1);
    NT_PWM3->TBCTL &=~(0x1);
    NT_PWM4->TBCTL &=~(0x1);
    NT_PWM5->TBCTL &=~(0x1);
    NT_PWM6->TBCTL &=~(0x1);
}

void Init_PWM_left()
{
    // исп. модули PWM0-PWM2
    NT_COMMON_REG->GPIOPCTLG_bit.PIN2  = 0;	//PWM0_A
	NT_COMMON_REG->GPIOPCTLG_bit.PIN3  = 0;	//PWM1_A
	NT_COMMON_REG->GPIOPCTLG_bit.PIN4  = 0;	//PWM2_A
	NT_COMMON_REG->GPIOPCTLA_bit.PIN10 = 2;	//PWM0_B
	NT_COMMON_REG->GPIOPCTLA_bit.PIN11 = 2;	//PWM1_B
	NT_COMMON_REG->GPIOPCTLA_bit.PIN12 = 2;	//PWM2_B

    NT_GPIOG->ALTFUNCSET_bit.ALTFUNCSET |= (0x7 << 2);
    NT_GPIOA->ALTFUNCSET_bit.ALTFUNCSET |= (0x7 << 10);

    NT_PWM0->TZCLR = 0x7;
    NT_PWM0->TZINTCLR_bit.TZINT = 1;
    NT_PWM1->TZCLR = 0x7;
    NT_PWM1->TZINTCLR_bit.TZINT = 1;
    NT_PWM2->TZCLR = 0x7;
    NT_PWM2->TZINTCLR_bit.TZINT = 1;
}


void Init_PWM_rigt_foof()
{
    // исп. модули PWM3-PWM5
    NT_GPIOG->ALTFUNCSET_bit.ALTFUNCSET |= (0x7 << 5);
    NT_GPIOA->ALTFUNCSET_bit.ALTFUNCSET |= (0x7 << 13);

    NT_PWM3->TZCLR                  = 0x7;
    NT_PWM3->TZINTCLR_bit.TZINT     = 1;
    NT_PWM4->TZCLR                  = 0x7;
    NT_PWM4->TZINTCLR_bit.TZINT     = 1;
    NT_PWM5->TZCLR                  = 0x7;
    NT_PWM5->TZINTCLR_bit.TZINT     = 1;

    NT_PWM3->TBPRD_bit.TBPRD        = (0b1111111111111);        // 3,57 kHz 2^13 дискрет
    NT_PWM3->TBPHS_bit.TBPHS        = 0;
    NT_PWM3->TBCTR                  = 0;

    NT_PWM3->TBCTL_bit.PRDLD        = TB_SHADOW;
    NT_PWM3->TBCTL_bit.CTRMODE      = TB_COUNT_UPDOWN;
    NT_PWM3->TBCTL_bit.PHSEN        = TB_DISABLE;
    NT_PWM3->TBCTL_bit.HSPCLKDIV    = 0;
    NT_PWM3->TBCTL_bit.CLKDIV       = 0;
    NT_PWM3->TBCTL_bit.SYNCOSEL     = TB_CTR_ZERO;

    NT_PWM3->CMPCTL_bit.SHDWAMODE   = CC_SHADOW;
    NT_PWM3->CMPCTL_bit.LOADAMODE   = CC_CTR_ZERO;
    NT_PWM3->CMPCTL_bit.SHDWBMODE   = CC_SHADOW;
    NT_PWM3->CMPCTL_bit.LOADBMODE   = CC_CTR_ZERO;
    
    NT_PWM3->CMPA_bit.CMPA          = 2000;
    NT_PWM3->CMPB_bit.CMPB          = 2000;

    NT_PWM3->AQCTLA                 = 0;
    NT_PWM3->AQCTLA_bit.ZRO         = 1;
    NT_PWM3->AQCTLA_bit.CAU         = 2;
    NT_PWM3->AQCTLA_bit.CAD         = 1;
    NT_PWM3->AQCTLB = NT_PWM3->AQCTLA;
    NT_PWM3->AQSFRC_bit.RLDCSF      = 3;

    NT_PWM3->DBRED                  = 10;
    NT_PWM3->DBFED = NT_PWM3->DBRED;
    NT_PWM3->DBCTL_bit.IN_MODE      = DBA_RED_DBB_FED;
    NT_PWM3->DBCTL_bit.OUT_MODE     = DB_FULL_ENABLE;
    NT_PWM3->DBCTL_bit.POLSEL       = DB_ACTV_HIC;

    NT_PWM3->ETSEL_bit.INTSEL       = ET_DISABLE;
    NT_PWM3->ETSEL_bit.INTEN        = 0;

    NT_PWM3->TBCTL_bit.FREE_SOFT    = 0;

    NT_PWM3->TZSEL_bit.OSHT0        = TZ_DISABLE;
    NT_PWM3->TZSEL_bit.OSHT1        = TZ_DISABLE;
    NT_PWM3->TZSEL_bit.OSHT2        = TZ_DISABLE;
    NT_PWM3->TZSEL_bit.OSHT3        = TZ_DISABLE;
    NT_PWM3->TZSEL_bit.OSHT4        = TZ_DISABLE;
    NT_PWM3->TZSEL_bit.OSHT5        = TZ_DISABLE;

    NT_PWM3->TZEINT_bit.OST         = 0;

    NT_PWM3->TZCTL_bit.TZA          = 0;
    NT_PWM3->TZCTL_bit.TZB          = 0;

    // PWM4, PWM5 по образцу
    #ifdef ass
        NT_PWM4->TBPRD = NT_PWM3->TBPRD;
        NT_PWM5->TBPRD = NT_PWM3->TBPRD;
        NT_PWM4->TBPHS = 1;
        NT_PWM5->TBPHS = 1;
        NT_PWM4->TBCTR = 0;
        NT_PWM4->TBCTR = 0;

        NT_PWM4->TBCTL_bit.PRDLD        = TB_SHADOW;
        NT_PWM4->TBCTL_bit.CTRMODE      = TB_COUNT_UPDOWN;
        NT_PWM4->TBCTL_bit.PHSEN        = TB_ENABLE;
        NT_PWM4->TBCTL_bit.HSPCLKDIV    = 0;
        NT_PWM4->TBCTL_bit.CLKDIV       = 0;
        NT_PWM4->TBCTL_bit.SYNCOSEL     = TB_SYNC_IN;
        NT_PWM5->TBCTL_bit = NT_PWM4->TBCTL_bit;

        NT_PWM4->CMPCTL_bit = NT_PWM3->CMPCTL_bit;
        NT_PWM5->CMPCTL_bit = NT_PWM3->CMPCTL_bit;
        
        NT_PWM4->CMPA_bit = 2000;
        NT_PWM5->CMPA_bit = 2000;
        NT_PWM4->CMPB_bit = 2000;
        NT_PWM5->CMPB_bit = 2000;

        NT_PWM4->AQCTLA                 = NT_PWM3->AQCTLA;
        NT_PWM5->AQCTLA                 = NT_PWM3->AQCTLA;
        NT_PWM4->AQCTLB                 = NT_PWM3->AQCTLB;
        NT_PWM5->AQCTLB                 = NT_PWM3->AQCTLB;
        NT_PWM4->AQSFRC_bit.RLDCSF      = NT_PWM3->AQSFRC_bit.RLDCSF;
        NT_PWM5->AQSFRC_bit.RLDCSF      = NT_PWM3->AQSFRC_bit.RLDCSF;

        NT_PWM4->DBRED                  = NT_PWM3->DBRED;
        NT_PWM5->DBRED                  = NT_PWM3->DBRED;
        NT_PWM4->DBFED                  = NT_PWM3->DBFED;
        NT_PWM5->DBFED                  = NT_PWM3->DBFED;
        
        NT_PWM4->DBCTL_bit.IN_MODE      = NT_PWM3->DBCTL_bit.IN_MODE;
        NT_PWM4->DBCTL_bit.OUT_MODE     = NT_PWM3->DBCTL_bit.OUT_MODE;
        NT_PWM4->DBCTL_bit.POLSEL       = NT_PWM3->DBCTL_bit.POLSEL;
        NT_PWM5->DBCTL_bit.IN_MODE      = NT_PWM3->DBCTL_bit.IN_MODE;
        NT_PWM5->DBCTL_bit.OUT_MODE     = NT_PWM3->DBCTL_bit.OUT_MODE;
        NT_PWM5->DBCTL_bit.POLSEL       = NT_PWM3->DBCTL_bit.POLSEL;

        NT_PWM4->ETSEL_bit.INTSEL       = 0;
        NT_PWM5->ETSEL_bit.INTSEL       = 0;

        NT_PWM4->ETSEL_bit.INTEN        = ET_DISABLE;
        NT_PWM5->ETSEL_bit.INTEN        = ET_DISABLE;

        NT_PWM4->TZSEL_bit = NT_PWM3->TZSEL_bit;
        NT_PWM5->TZSEL_bit = NT_PWM3->TZSEL_bit;
        
        NT_PWM4->TZCTL_bit = NT_PWM3->TZCTL_bit;
        NT_PWM5->TZCTL_bit = NT_PWM3->TZCTL_bit;
    #endif
    NT_COMMON_REG->PWM_SYNC_bit.TBCLKSYNC = 0x01FF;
}  

void Init_PWM_rigt()
{
    // исп. модули PWM3-PWM5

}