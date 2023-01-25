/******************************************************************************
 * @file		main.h
 * @brief		������������ ���� ��� �������� ����� �������
 * @version		v1.0
 * @date		11 ������� 2015
 *
 * @note
 * ��� "��� ������", ��� ����� ��������. ��� ����: http://motorcontrol.ru
 *
 * @par
 * ��� "��� ������" �������������� ��� ����������� ����������� � ����������������
 * �����, � ��� ����� ���������������� ��������.
 *
 * @par
 * ������ ����������� ����������� ���������������� "��� ����", � ��,
 * ��� ������������, ���������� �� ���� ��� �����, ��������� � ��� ��������������.
 * ��� "��� ������" �� ����� ������� ��������������� �� ��������� ������,
 * ��������� � ��� ��������������.
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
    //#define __STDC_HOSTED__ 0                     // �� ������ ������
    
    #include "DSP.h"
    #include "modbus_rtu.h"

    #include "niietcm4.h" // ���� ���� �������� niietcm4_conf.h, ������� �������� ��������� ���������

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
