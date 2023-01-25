/******************************************************************************
 * @file		main.c
 * @brief		������� ���� �������
 * @version		v1.0
 * @date		25 ���� 2019
 *
 * @note
 * ��� "��� ������" (http://motorcontrol.ru), ��� ����� ��������.
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

//� ���� ������� �������� ������ � ����������� ������� ����������������.
//������� ������������ ������������� ��� ��� ������ � ������ ����������� ������.
//����� ��������� �������� � ����������� ����, ��� � ���������, ���������� � ���������� TimerPeriod,
//�� ������ �� ���������� ���������� � ����������� 6 �����������.
//������� ��������� "��������� �����" ��� ������ � ���������� ���������.

#include "main.h"

// ������� ��� ������ ������� ������������ ���������� (����� ����������������� ���� �� ���)
#define TOGGLE_BY_MASK              0
//#define TOGGLE_BY_DATAOUTSET_CLR    1
//#define TOGGLE_BY_DATATOGGLE        2
//#define TOGGLE_BY_DATA              3

//���������� ���������� ������� ����� ������� (����� ���� �������� ��� ��������� ������� � ���� ��������� ����������)
int TimerPeriod = 500000;

// ���������� ���������� ��� �������� ��������� ����������
int ledState = 0;


//������� ������������� ���������� ������� ���������������� ��� ���������� ������������
void LED_init (void)
{
	// �� ����� MotorControlBoard_028 ������� ��� ����������, ������� ��������� � ������� 14 � 15 ����� K ����������������
    // � ������� ������ ���� ������� � ������ ��������� ������ �� �������������. ����� ��������� �� ��� ������ � ��������
    // ����������� ������� ����� ������� ���������
    // 1) �������� ������������ ����� K ����� GPIO ������� "1" � ��������������� ��� �������� HCLKCFG
    // 2) ������� ���� �� ��������� ������ ������� "1" � ��������������� ��� �������� HRSTCFG
    // 3) ��������� ��� ������, ������� "1" � ��������������� ��� (��� �8) �������� DENSET. ����� ����� ����� ������ ���������������.
    //    �� ��������� � ������������ � ������������ �� ������ ���� �����-������ ������ ���������� (����������� ����������, � ��
    //    �����-���� ������������ �����������) � �������� �� _����_ �������, � �� �� ������
    // 4) ����� A8 ����������� � ����� _������_ �������� ������� "1" � ��������������� ��� ������� OUTENSET. �� ���������, ��������
    //    ������ ����� "0", ������� ����� �8 ������ ��������� "0".
    RCU->HCLKCFG_bit.GPIOKEN = 1;
    RCU->HRSTCFG_bit.GPIOKEN = 1;

    GPIOK->DENSET = (1 << 14);
	GPIOK->OUTENSET = (1 << 14);
	GPIOK->DENSET = (1 << 15);
    GPIOK->OUTENSET = (1 << 15);
}



//������� ������� ������������
void LED_blink (void) {
	static int timer;	//���������� �������

	if (timer > TimerPeriod)
	{
		timer = 0;
		ledState ^= 0x1;

#ifdef TOGGLE_BY_MASK
		// ������ 1. ��������� � GPIO �� ����� (��. ������������): MASKLOWBYTE - � �������� ����� ��������, MASKHIGHBYTE - � ��������.
		//��������, �� ����� ������ "1" �� GPIO2, GPIO3 � GPIO4 ����� C:
		//0001 1100     �����, �������� �������� � ������� MASKLOWBYTE
		//xxx1 11xx     ������������ ��������: � ������ ����� - �������, � ��������� - �� �����, �.�. ��� �� �������� � ����� � �� ����� ��������
		//NT_GPIOC->MASKLOWBYTE_bit[28].MASKLB = 28;    ��� �������� ��� �������, ��� �������: NT_GPIOC->MASKLOWBYTE_bit[28].MASKLB = 0xFF;
		//���� ���� �������� GPIO2 � GPIO4 � ��������� GPIO3, ��:
		//NT_GPIOC->MASKLOWBYTE_bit[28].MASKLB = 20;    20 = 0001 0100b
		//������ � ����� ����� �� ����� �����������, ��� ������ ����, ������� �� �������� � �����, ����� �� ���������.
		//����� ������ �� ����� ��������� ������������ ����� �������� ����������� ��� ���� �����, ���� ��� ���������.
		// � ������ ������� ����� ����� 192 (-> 1100 0000) � ������������ � ������� MASKHB (High Byte) ��� �������������
		// ������� 14 � 15
		if (ledState == 0x1){
		    GPIOK->MASKHB[192].MASKHB = 0xFF << 8;
		} else {
		    GPIOK->MASKHB[192].MASKHB = 0;
		}

#endif

#ifdef TOGGLE_BY_DATAOUTSET_CLR
		//������ 2 (����� ����������������� ������ TOGGLE_BY_DATAOUTSET_CLR � ������ �����, � ���������������� ���������)
		// ����� ������ "1" � ���� �� ����� �������� DATAOUTSET, ��������������� ����� ��������� ��������� "1", ����������
		// �� ����������� ���������.
        // ����� ������ "1" � ���� �� ����� �������� DATAOUTCLR, ��������������� ����� ��������� ��������� "0", ����������
        // �� ����������� ���������.
		// ������ ����������: ��� ������ ��� �������� ���������� �� ��������, ������� ���� �������� � ���������� ���.
        // ������� � �� ����, ������� �� ������ ������ ��� ���������, ����������� ����� �������� ����. �� ���� ������ �����
        // �������� ���������� ��� (�������� DATAOUTSET |= (1 << 8) ) �����������, ��� ��� ��� ���� ����� ������� ��������
        // �������� DATAOUTSET, � ����������� �������� ����� �������� 8 ��� � ������������ �������� ����� �������� �������. ���
        // ������� � ��������� ���� �������, ��������������� ���� ������� ���� ����� "1". ���������� ��� DATAOUTCLR.
		// ������:
		// ��� ������ ��������� ������� DATAOUTSET ����� "0000 0000 0000 0000"
		// � �����-�� ����� ���������  ��� ������� 4 ����� �������� DATAOUTSET |= (1 << 4): ��������� �������� "0000 0000 0000 0000",
		// ������� 4 ���, ������������ �������� �������� �������. ������ DATAOUTSET ����� "0000 0000 0001 0000".
		// ����� ����� ��� �������� �������� DATAOUTCLR |= (1 << 4).
		// �������� �������� DATAOUTSET ��� ���� �� ����������: DATAOUTSET ����� "0000 0000 0001 0000"
		// ����� ������������ ������� �������� 8 ����� ����� �������� DATAOUTSET |= (1 << 8).
		// ������ ����� ������ DATAOUTSET � ��������� 8 ����, � ���� ����� �������� �������� "0000 0001 0001 0000", ���
		// ������� � ��������� � 4, � 8 �������.
		if (ledState == 0x1) {
		    GPIOK->DATAOUTSET = (1 << 14);
		    GPIOK->DATAOUTSET = (1 << 15);
		} else {
		    GPIOK->DATAOUTCLR = (1 << 14);
		    GPIOK->DATAOUTCLR = (1 << 15);
		}

#endif

#ifdef TOGGLE_BY_DATATOGGLE
        //�������� 3 (����� ����������������� ������ TOGGLE_BY_DATATOGGLE � ������ �����, � ���������������� ���������)
        // ������ "1" � ���� �� ����� �������� DATAOUTTGL ������ ��������� �������������� ����� �� ���������������.
		// ��� ���� � �� ����, ������� �� ������ �������������, ����������� ����� �������� ����. �� ���� ������ �����
		// �������� ���������� ��� (�������� DATAOUTTGL |= (1 << 8) ) �����������, ��� ��� ��� ���� ����� ������� ��������
		// �������� TGL, � ����������� �������� ����� �������� 8 ��� � ������������ �������� ����� �������� �������. ���
		// ������� � ������������ ���� �������, ��������������� ���� ������� ���� ����� "1".
		// ����������: ��� ������ ���� ������� ���������� ����� ��������, ������� ���� � ���� �������� � ���������� ���.
        GPIOK->DATAOUTTGL = (1 << 14);
        GPIOK->DATAOUTTGL = (1 << 15);

#endif

#ifdef TOGGLE_BY_DATA
        //�������� 4 (����� ����������������� ������ TOGGLE_BY_DATA � ������ �����, � ���������������� ���������)
        // ������ ��������� �������� ��������� �������. ����� ������ ���������� �������� �������������. ���������:
        //�����������, ������������ ������ ��� ������� ���� NT_GPIOK->DATA &= ~(1 << 14) � GPIOK->DATA |= (1 << 15). ��� ���������
        //�������� DATA ����� ������ ��������� �� �����, � ����� 2 ����� (��� ������� � ��������������). ����
        //������ �������� 2 �������, �������� GPIOK->DATA &= ~(1 << 14) � GPIOK->DATA &= ~(1 << 15), �� ������
        //� ������� ������������ �� ���������, ��� ��� ������ � ���� �������������� ������� ������� ����� �����, ���������� �������
        //���� � ������� ��� �����. �� ������ �� GPIO ���������� ������� ��������� �����, � � ������� ���������� ������ ������� (������ ������ ��)
        //����������� ��������� �� ����� ��������� ���������, ������� ������� ������ �������, ������� ������ ������� ������ ��� ���,
        //������� ������ ��������� ������ �������.
        //��� ���� �������� ����������� ������ ��� ���������� ������� ����������� �����������. ��� ����������� ���������� ����������
        //���������� ����� ������������ ������ ����� ����������� � GPIO � ������������� �������� �����������.

        if (ledState == 0x1){
            GPIOK->DATAOUT &= ~(1 << 14);
            GPIOK->DATAOUT &= ~(1 << 15);
        } else {
            GPIOK->DATAOUT |= (1 << 14);
            GPIOK->DATAOUT |= (1 << 15);
        }
#endif


	}

	timer++;
}


int16 main (void){
	//������������� ����������������: ��������� ��������, ������������ ������������ ���������
    SystemInit();

	//������������� ��������� ��� ���������� �������
	LED_init();

	//����������� ����
	while(1)
	{
		LED_blink();	//������� �������
	}
}

/*@}*/
