#ifdef RELPATH
    #include "main.h"
#else
    #include "../inc/main.h"
#endif

void Init_UART(NT_UART_TypeDef* port)
   {
        port->CR_bit.UARTEN = 0;
        while (port->FR_bit.BUSY)
        {
            asm("nop");
        }
        port->LCR_H_bit.FEN = 1;

        port->IBRD = 39;        //115200
        port->FBRD = 4;

        port->CR_bit.TXE = 1;
        port->ICR_bit.TXIC = 1; // transmit complete

        port->CR_bit.UARTEN = 1;
   }