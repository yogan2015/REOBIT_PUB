#ifdef RELPATH
    #include "main.h"
    #include "PWM_macros.h"
#else
    #include "../inc/main.h"
    #include "../inc/PWM_macros.h"
#endif



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

void Init_PWM_rigt(NT_PWM_TypeDef* SHIM, char del)
{
    // исп. модули PWM3-PWM5
    NT_GPIOG->ALTFUNCSET_bit.ALTFUNCSET |= (0x3F << 2);
    NT_GPIOA->ALTFUNCSET_bit.ALTFUNCSET |= (0x3F << 10);

    SHIM->TZCLR                  = 0x7;
    SHIM->TZINTCLR_bit.TZINT     = 1;

    SHIM->TBPRD_bit.TBPRD        = (rb_PWM_PERIOD);        // 3,57 kHz 2^13 дискрет
    SHIM->TBPHS_bit.TBPHS        = (int) del;
    SHIM->TBCTR                  = 0;

    SHIM->TBCTL_bit.PRDLD        = TB_SHADOW;
    SHIM->TBCTL_bit.CTRMODE      = TB_FREEZE;   
    SHIM->TBCTL_bit.PHSEN        = TB_ENABLE;
    SHIM->TBCTL_bit.HSPCLKDIV    = 0;
    SHIM->TBCTL_bit.CLKDIV       = 0;
    if (del == 0) {
        SHIM->TBCTL_bit.SYNCOSEL     = 0x1;
    } else {
        SHIM->TBCTL_bit.SYNCOSEL     = 0x0;
    }

    SHIM->CMPCTL_bit.SHDWAMODE   = CC_SHADOW;
    SHIM->CMPCTL_bit.LOADAMODE   = CC_CTR_ZERO;
    SHIM->CMPCTL_bit.SHDWBMODE   = CC_SHADOW;
    SHIM->CMPCTL_bit.LOADBMODE   = CC_CTR_ZERO;
    
    SHIM->CMPA_bit.CMPA          = rb_PWM_HALFPERIOD;
    SHIM->CMPB_bit.CMPB          = rb_PWM_HALFPERIOD-1;

    SHIM->AQCTLA                 = 0;
    SHIM->AQCTLA_bit.ZRO         = 1;
    SHIM->AQCTLA_bit.CAU         = 2;
    SHIM->AQCTLA_bit.CAD         = 1;
    SHIM->AQCTLB = SHIM->AQCTLA;
    SHIM->AQSFRC_bit.RLDCSF      = 3;

    SHIM->DBRED                  = 1;
    SHIM->DBFED = SHIM->DBRED;
    SHIM->DBCTL_bit.IN_MODE      = DBA_RED_DBB_FED;
    SHIM->DBCTL_bit.OUT_MODE     = DB_FULL_ENABLE;
    SHIM->DBCTL_bit.POLSEL       = DB_ACTV_HIC;

    SHIM->ETSEL_bit.INTSEL       = ET_DISABLE;
    SHIM->ETSEL_bit.INTEN        = 0;

    SHIM->TBCTL_bit.FREE_SOFT    = 0;

    SHIM->TZSEL_bit.OSHT0        = TZ_DISABLE;
    SHIM->TZSEL_bit.OSHT1        = TZ_DISABLE;
    SHIM->TZSEL_bit.OSHT2        = TZ_DISABLE;
    SHIM->TZSEL_bit.OSHT3        = TZ_DISABLE;
    SHIM->TZSEL_bit.OSHT4        = TZ_DISABLE;
    SHIM->TZSEL_bit.OSHT5        = TZ_DISABLE;

    SHIM->TZEINT_bit.OST         = 0;

    SHIM->TZCTL_bit.TZA          = 0;
    SHIM->TZCTL_bit.TZB          = 0;
}