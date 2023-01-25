
#ifndef TARGET_H
#define TARGET_H

#if defined(STM32F303C6) || defined(STM32F303C8) || defined(STM32F303K6) || defined(STM32F303K8) || defined(STM32F303R6) || defined(STM32F303R8)
#define STM32F303x6_8
#endif
#if defined(STM32F303CB) || defined(STM32F303RB) || defined(STM32F303VB) || defined(STM32F303CC) || defined(STM32F303RC) || defined(STM32F303VC)
#define STM32F303xB_C
#endif
#if defined(STM32F303RD) || defined(STM32F303VD) || defined(STM32F303ZD) || defined(STM32F303RE) || defined(STM32F303VE) || defined(STM32F303ZE)
#define STM32F303xD_E
#endif

#endif

