#ifndef rb_general_include

#ifdef RELPATH
    #include "stm32f10x.h"
    #include "stm32f10x_conf.h"
    #include "system_stm32f10x.h"
    #include "core_cm3.h"
    #include "cmsis_version.h"
    #include "cmsis_gcc.h"
    #include "cmsis_device.h"
    #include "cmsis_compiler.h"
#else
    #include "../../../target/stm32f103/CMSIS/device/stm32f10x.h"
    #include "../../../target/stm32f103/CMSIS/device/stm32f10x_conf.h"
    #include "../../../target/stm32f103/CMSIS/device/system_stm32f10x.h"
    #include "../../../target/stm32f103/CMSIS/core/core_cm3.h"
    #include "../../../target/stm32f103/CMSIS/core/cmsis_version.h"
    #include "../../../target/stm32f103/CMSIS/core/cmsis_gcc.h"
    #include "../../../target/stm32f103/CMSIS/core/cmsis_device.h"
    #include "../../../target/stm32f103/CMSIS/core/cmsis_compiler.h"
#endif

#define rb_general_include
#endif

void SystemInit(void);
void main(void);
