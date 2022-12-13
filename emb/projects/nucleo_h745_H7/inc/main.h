#define CORE_CM7

#ifdef RELPATH
    #include "stm32h745xx.h"
#else
    #include "../../../cmn/target/stm32h745xx.h"
#endif

void rb_USART2_Init();