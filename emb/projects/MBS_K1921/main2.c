#ifdef RELPATH
    #include "main.h"
    #include "modbus_rtu.h"

    //#include "./src/rb_uart.c"
#else
    #include "./inc/main.h"
    #include "../../cmn/modbus/modbus_rtu.h"
    #include "./src/rb_uart.c"
#endif

#include "./src/board_MBS.c"  // конфигурация платы, содержит реализацию Init_CLK(), Init_GPIO()

#define SYSTICK_FREQ 2000

static void inline pulsar(int16 p)
{
        switch (p)
        {
        case 0:
            NT_GPIOC->DATA |= (1<< 8);
            NT_GPIOC->DATA &=~(1<<13);
            break;
        
        case 1:
            NT_GPIOC->DATA |= (1<< 9);
            NT_GPIOC->DATA &=~(1<< 8);
            break;

        case 2:
            NT_GPIOC->DATA |= (1<<10);
            NT_GPIOC->DATA &=~(1<< 9);
            break;

        case 3:
            NT_GPIOC->DATA |= (1<<11);
            NT_GPIOC->DATA &=~(1<<10);
            break;

        case 4:
            NT_GPIOC->DATA |= (1<<12);
            NT_GPIOC->DATA &=~(1<<11);
            break;

        case 5:
            NT_GPIOC->DATA |= (1<<13);
            NT_GPIOC->DATA &=~(1<<12);
            break;
        default:
            break;
        }
}

void MARKER()
    {
        asm("nop");
    }

int16 main()
{
    uint16_t a = 1;
    uint32_t b = 1;
    int16_t  c = 1;
    int32_t  d = 1;
    DINT;
    Init_CLK();  
    Init_GPIO();
    Init_TIM0();
    Init_PWM_rigt(NT_PWM0, 1);
    Init_PWM_rigt(NT_PWM1, 1);
    Init_PWM_rigt(NT_PWM2, 1);
    Init_PWM_rigt(NT_PWM3, 1);
    Init_PWM_rigt(NT_PWM4, 1);
    Init_PWM_rigt(NT_PWM5, 1);
    Init_UART(NT_UART0);
    NT_COMMON_REG->PWM_SYNC_bit.TBCLKSYNC = 0x01FF;

    // конфигурация MODBUS RTU
        static TMbRTUPort *Mb;
        static TMbSlaveInfo *SlaveInfo;
        static TMbGetData *GetData;
        static TMbGetRecord *GetRecord;

        static UART_Init_TypeDef *UART0_Init;
        #define Part1
        #define Part2
        #define Part3
        #ifdef Part1
            SlaveInfo->DeviceDescr      = 0;
            SlaveInfo->DeviceInfo       = 0;
            SlaveInfo->DeviceNumber     = 0;
            SlaveInfo->SlaveID          = 0;
            SlaveInfo->VersionDate      = 0;
            SlaveInfo->VersionNumber    = 0;
        #endif
        #ifdef Part2
            Mb->Params.UartID           = 0;
            Mb->Params.Mode             = 1; // slave
            Mb->Params.Slave            = 1;
            Mb->Params.BaudRate         = 1152;
            Mb->Params.BrrValue         = 1152;
            Mb->Params.Parity           = 0;
            Mb->Params.StopBits         = 1;
            Mb->Params.UserMode         = 0;
            Mb->Params.RetryCount       = 0;
            Mb->Params.Scale            = 4;
            Mb->Params.RxDelay          = 5;
            Mb->Params.TxDelay          = 2;
            Mb->Params.ConnTimeout      = (uint16_t)(3.0*SYSTICK_FREQ);
            Mb->Params.AckTimeout       = (uint16_t)(1.0*SYSTICK_FREQ);
            Mb->Params.SlaveInfo        = (TMbSlaveInfo *)&SlaveInfo;
            Mb->Params.TrEnable         = GetData;
            Mb->Params.GetData          = GetData;
            Mb->Params.GetRecord        = 0;
        #endif
        #ifdef Part3
            UART0_Init->UART_DataWidth  = UART_DataWidth_8;
            UART0_Init->UART_FIFOEn     = DISABLE;
            UART0_Init->UART_ParityBit  = UART_ParityBit_Odd;
            UART0_Init->UART_RxEn       = ENABLE;
            UART0_Init->UART_TxEn       = ENABLE;
        #endif

    //UART_Init(NT_UART0, UART0_Init);
    NT_GPIOC->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 8 );
    NT_GPIOC->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 9 );
    NT_GPIOC->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 10);
    NT_GPIOC->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 11);
    NT_GPIOC->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 12);
    NT_GPIOC->ALTFUNCCLR_bit.ALTFUNCCLR = (1 << 13);
    NT_GPIOC->OUTENSET_bit.OUTENSET |= (0b111111 << 8);
    NT_GPIOC->DATA |=(0b111111<<8);
    EINT;
    NT_PWM0->TBCTL_bit.CTRMODE      = 0x10;
    //NT_PWM1->TBCTL_bit.CTRMODE      = 0x10;
    //NT_PWM2->TBCTL_bit.CTRMODE      = 0x10;
    NT_PWM3->TBCTL_bit.CTRMODE      = 0x10;
    NT_PWM4->TBCTL_bit.CTRMODE      = 0x10;
    NT_PWM5->TBCTL_bit.CTRMODE      = 0x10;

    NT_PWM6->TBCTL_bit.CTRMODE      = 0x10;
    while (1)
    {
        ;
    }
    
}

void TIM0_IRQHandler (void)
{
    //return;
    //phase = (phase < 0)?(5):(phase-1);
    //pulsar(phase);
    //NT_GPIOC->DATA ^= (1 << 8);
    //if (NT_PWM3->TBCTR > rb_PWM_HALFPERIOD)
    //{
    //    NT_GPIOC->DATA |= (1<<9);
    //    NT_GPIOC->DATA &=~(1<<10);
    //} else
    //{
    //    NT_GPIOC->DATA &=~(1<<9);
    //    NT_GPIOC->DATA |= (1<<10);
    //}    
    
    if (NT_PWM0->TBSTS & PWM_TBSTS_CTRDIR_Msk) NT_GPIOC->DATA ^=(1 << 8);
    if (NT_PWM1->TBSTS & PWM_TBSTS_CTRDIR_Msk) NT_GPIOC->DATA ^=(1 << 9);
    if (NT_PWM2->TBSTS & PWM_TBSTS_CTRDIR_Msk) NT_GPIOC->DATA ^=(1 <<10);
    if (NT_PWM3->TBSTS & PWM_TBSTS_CTRDIR_Msk) NT_GPIOC->DATA ^=(1 <<11);
    if (NT_PWM4->TBSTS & PWM_TBSTS_CTRDIR_Msk) NT_GPIOC->DATA ^=(1 <<12);
    if (NT_PWM5->TBSTS & PWM_TBSTS_CTRDIR_Msk) NT_GPIOC->DATA ^=(1 <<13);

    NT_TIMER0->INTSTATUS_INTCLEAR_bit.INT = 1;
}

extern void EPWM_0_IRQHandler(void)
{
    NT_GPIOC->DATA ^= (1<< 13);
    NT_PWM0->ETCLR |= 0x1;
}