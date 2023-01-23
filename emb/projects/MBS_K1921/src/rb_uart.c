#ifdef RELPATH
    #include "main.h"
#else
    #include "../inc/main.h"
#endif

    static inline void Init_UART0()
    {
        UART_Init_TypeDef* UART0_Config;

        UART0_Config->UART_DataWidth    = UART_DataWidth_8;
        UART0_Config->UART_FIFOEn       = DISABLE;
        UART0_Config->UART_FIFOLevelRx  = UART_FIFOLevel_1_2;
        UART0_Config->UART_FIFOLevelTx  = UART_FIFOLevel_1_2;
        UART0_Config->UART_ParityBit    = UART_ParityBit_Disable;
        UART0_Config->UART_StopBit      = UART_StopBit_1;
        UART0_Config->UART_RxEn         = ENABLE;
        UART0_Config->UART_TxEn         = ENABLE;

        UART_Init(NT_UART0, &UART0_Config);
    }

    static inline void Init_UART1()
    {
        ;
    }

    static inline void Init_UART2()
    {
        ;
    }

    static inline void Init_UART3()
    {
        ;
    }