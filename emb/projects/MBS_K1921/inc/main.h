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

#define __INT16_TYPE__  signed char
#define __UINT16_TYPE__ unsigned char
#define __INT32_TYPE__  signed int
#define __UINT32_TYPE__ unsigned int

#include <stdint-gcc.h>
#include "DSP.h"
#include "modbus_rtu.h"

#include "niietcm4.h" // этот файл инклюдит niietcm4_conf.h, который инклюдит избранную периферию

static inline void Init_CLK(void);
static inline void Init_GPIO(void);
static inline void Init_MB(void);

int16 main(void);


#endif /* VINCLUDE_MAIN_H_ */
