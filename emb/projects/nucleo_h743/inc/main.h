#ifdef RELPATH
    #include "stm32h743xx.h"
#else
    #include "../../../cmn/target/stm32f74x/stm32h743xx.h"
    #include "../../../cmn/target/stm32f74x/system_stm32h7xx.h"
    #include "../../../cmn/core/mpu_armv7.h"

    #include "../../../cmn/core/core_cm7.h"

    #include "../../../cmn/CMSIS/cmsis_compiler.h"
    #include "../../../cmn/CMSIS/cmsis_version.h"
    #include "../../../cmn/CMSIS/cmsis_gcc.h"
#endif
