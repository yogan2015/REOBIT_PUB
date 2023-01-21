#ifdef RELPATH
    #include "main.h"
    #include "modbus_rtu.h"
#else
    #include "./inc/main.h"
    #include "../../cmn/modbus/modbus_rtu.h"
#endif

#include "./src/board_MBS.c"  // ������������ �����, �������� ���������� Init_CLK(), Init_GPIO()

#define SYSTICK_FREQ 2000

int16 main()
{
    int16 phase = 6;

    Init_CLK();  
    Init_GPIO();
    // ������������ MODBUS RTU
        TMbRTUPort *Mb = (TMbRTUPort *)0x20000200;
        TMbSlaveInfo *SlaveInfo;
        TMbGetData *GetData;
        TMbGetRecord *GetRecord;

        UART_Init_TypeDef *UART0_Init;


        SlaveInfo->DeviceDescr      = 'Z';
        SlaveInfo->DeviceInfo       = 'V';
        SlaveInfo->DeviceNumber     = 0;
        SlaveInfo->SlaveID          = 0;
        SlaveInfo->VersionDate      = 0;
        SlaveInfo->VersionNumber    = 0;

        Mb->Params.UartID           = 0;
        Mb->Params.Mode             = 1; // slave
        Mb->Params.Slave            = 1;
        Mb->Params.BaudRate         = 1152;
        Mb->Params.BrrValue         = 1152;
        Mb->Params.Parity           = 0;
        Mb->Params.StopBits         = 1;
        Mb->Params.UserMode         = 0;
        Mb->Params.RetryCount       = 0;
        Mb->Params.Scale            = 120000000/1000;
        Mb->Params.RxDelay          = 5;
        Mb->Params.TxDelay          = 2;
        Mb->Params.ConnTimeout      = (uint16_t)(3.0*SYSTICK_FREQ);
        Mb->Params.AckTimeout       = (uint16_t)(1.0*SYSTICK_FREQ);
        Mb->Params.SlaveInfo        = (TMbSlaveInfo *)&SlaveInfo;
        Mb->Params.TrEnable         = GetData;
        Mb->Params.GetData          = GetData;
        Mb->Params.GetRecord        = 0;



    #ifdef MODBUS ON    
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
    NT_GPIOC->DATA |=(0b011111<<8);
    while(1)
    {
        for (int32 j = 0; j<120000; j++)
        { asm("nop");  asm("nop");  asm("nop"); asm("nop");  asm("nop");  asm("nop");}
        phase--;
        if (phase<0) phase = 5;
            switch (phase)
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
}