#ifdef RELPATH
    #include "main.h"
#else
    #include "./inc/main.h"
    
#endif

#include "./src/board_MBS.c"  // ������������ �����, �������� ���������� Init_CLK(), Init_GPIO()

int16 main()
{
    int16 phase = 6;

    Init_CLK();  
    Init_GPIO();

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