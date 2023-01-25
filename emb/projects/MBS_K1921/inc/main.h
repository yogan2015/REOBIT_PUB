/******************************************************************************
 * @file		main.h
 * @brief		Заголовочный файл для главного файла проекта
 * @version		v1.0
 * @date		11 декабря 2015
 *
 * @note
 * ООО "НПФ Вектор", все права защищены. Наш сайт: http://motorcontrol.ru
 *
 * @par
 * ООО "НПФ Вектор" распространяет это программное обеспечение в демонстрационных
 * целях, и оно может распространяться свободно.
 *
 * @par
 * Данное программное обеспечение распространяется "как есть", и Вы,
 * его пользователь, принимаете на себя все риски, связанные с его использованием.
 * ООО "НПФ Вектор" не несет никакой ответственности за возможные убытки,
 * связанные с его использованием.
 *
 ******************************************************************************/

#ifndef VINCLUDE_MAIN_H_
    #define VINCLUDE_MAIN_H_

    //#define __INT8_TYPE__   signed char
    //#define __UINT8_TYPE__  unsigned char
    //#define __INT16_TYPE__  signed char
    //#define __UINT16_TYPE__ unsigned char
    //#define __INT32_TYPE__  signed long int
    //#define __UINT32_TYPE__ unsigned long int
    //#define __STDC_HOSTED__ 0                     // на всякий случай
    
    #include "DSP.h"
    #include "modbus_rtu.h"

    #include "niietcm4.h" // этот файл инклюдит niietcm4_conf.h, который инклюдит избранную периферию

    #include "rb_tim.h"
    #include "rb_uart.h"
    
    
    static int16 phase = 5;
    static uint16_t p = 0;
    static inline void Init_CLK(void);
    static inline void Init_GPIO(void);
    static inline void Init_UART0(void);
    static inline void Init_UART1(void);
    static inline void Init_UART2(void);
    static inline void Init_UART3(void);
    //static inline void Init_MB(void);

    int16 main(void);


#endif /* VINCLUDE_MAIN_H_ */
