
//#define __UINT32_TYPE__ unsigned int
#ifndef rb_general_include
#include <stdint.h>

    #ifdef __cplusplus
        #define   __I     volatile             /*!< Defines 'read only' permissions */
    #else
        #define   __I     volatile const       /*!< Defines 'read only' permissions */
    #endif
    #define     __O     volatile             /*!< Defines 'write only' permissions */
    #define     __IO    volatile             /*!< Defines 'read / write' permissions */

    /* following defines should be used for structure members */
    #define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
    #define     __OM     volatile            /*! Defines 'write only' structure member permissions */
    #define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */
    
#ifdef RELPATH    
    #include "stm32f10x.h"
    #include "core_cm3.h"
    #include "stm32f10x_conf.h"
    #include "system_stm32f10x.h"

    #include "cmsis_version.h"
    #include "cmsis_gcc.h"
    #include "cmsis_device.h"
    #include "cmsis_compiler.h"

#else    
    #define STM32F10X_MD
    #include "../../../cmn/core/core_cm3.h"
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
static inline void config_RCC   (void);
static inline void config_GPIO  (void);      
static inline void config_TIM1  (void);
static inline void config_TIM4  (void);
static inline void config_USART3(void);

static inline void config_NVIC  (void);

void main(void);
