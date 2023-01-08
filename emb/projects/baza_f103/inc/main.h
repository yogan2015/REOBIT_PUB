
//#define __UINT32_TYPE__ unsigned int
#ifndef rb_general_include
#include <stdint.h>

#ifdef RELPATH    
    #include "core_cm3.h"
    #include "stm32f10x.h"
    #include "stm32f10x_conf.h"
    #include "system_stm32f10x.h"

    #include "cmsis_version.h"
    #include "cmsis_gcc.h"
    #include "cmsis_device.h"
    #include "cmsis_compiler.h"

#else    
    #define STM32F10X_MD

    //#include "../../../cmn/core/core_cm3.h"
    #include "../../../cmn/target/stm32f10x.h"
//    #include "../../../cmn/target/stm32f10x_conf.h"
//    #include "../../../cmn/target/system_stm32f10x.h"
//    #include "../../../cmn/cmsis/cmsis_compiler.h"
//    #include "../../../cmn/cmsis/cmsis_device.h"
//    #include "../../../cmn/cmsis/cmsis_gcc.h"
//    #include "../../../cmn/cmsis/cmsis_version.h"
#endif

#define rb_general_include
#endif

void SystemInit(void);
void main(void);
