/*!
    Copyright 2017 	�� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      SMProtect.h
 \brief     ������ �����. (��. TSM_Protect)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  SMProtect ������ �����. (��. TSM_Protect)
 @{
*/
#ifndef SM_Protect_H
#define SM_Protect_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "build.h"

//! ������ ���� ��������
#define PROT_OFF 			0
//! ������ ����� �������
#define PROT_ON_OK	 		1
//! ������ ����� � ��������� ������ (��������� ������)
#define PROT_FAIL 			2

//������ ������ (���� ����, �� ������) � ������ (���� 1, �� �����) ���������� ������
#if defined HW_VECTOR_MK_40_4
#define DRV_FAULT	(NT_GPIOA->DATA & (1 << 8))
#define RESET_FAULT_BUTTON	0 //������ ������ ������ �� �������������
#endif

#if defined (HW_VECTORCARD_DRV8301_EVM) || defined(HW_VECTORCARD_DRV8312_EVM)
#define DRV_FAULT	(NT_GPIOC->DATA & (1 << 4))
#define RESET_FAULT_BUTTON	0 //������ ������ ������ �� �������������
#endif

#if defined (HW_VECTORCARD_SIMULATOR) || defined(HW_NIIET_BOARD_SIMULATOR)
#define DRV_FAULT	1 //������ ����� � ���������� �� �������������
#define RESET_FAULT_BUTTON	0 //������ ������ ������ �� �������������
#endif

#if defined (HW_MOTORCONTROLBOARD)
#define DRV_FAULT	(NT_GPIOG->DATA & (1 << 13))	//����� ����� ������
#define DRV_FAULT1	(NT_GPIOA->DATA & (1 << 9))		//������ ����� A0
#define DRV_FAULT2	(NT_GPIOG->DATA & (1 << 15))	//������ ����� A1
#define DRV_FAULT3	(NT_GPIOE->DATA & (1 << 7))		//������ ����� A2
#define DRV_FAULT4	(NT_GPIOC->DATA & (1 << 8))		//������ ����� B0 ��� B1 ��� B2

//��� ������ ���������� ������ � ������ ����������� ������������� ������� ���������� ���� �����
#define RESET_FAULT_BUTTON	(BIT_IS_SET(input_vect, 2) ? 1 : 0) //���� ���������� 3-� ��� � ������� ���������� ������
#endif


/*! \class TSM_Protect
      \brief ������ �����.

      ����� \a TSM_Protect, ���������� �� ��������� SSMProtect,
      ������������ ��� ��������� ��������� �������� � �������� ��������������� ����
      ������ ��� � ����� �� ���� bit_fault 1-2. ����� ���������� ��������� ���� ����, �,
      ���� ��� ������ �� �������������, ���������� ������� �������.
*/

//! ��. TSM_Protect
  struct SSM_Protect
  {
    Uint16 state;//!< ���������
    Uint16 state_prev;//!< ��������� ����������

    Uint16 readDrvSts; //!<���� ������� ������ ������� drv8301
    Uint16 clearDrvFault; //!<���� ������� ������ ������ drv8301

    Uint16 bit_fault1;//!<����� ������ 1
    Uint16 bit_fault2;//!<����� ������ 2

    Uint16 masked_bit_fault1;//!<����� ������ ����� ������������
    Uint16 masked_bit_fault2;//!<����� ������ ����� ������������

    Uint16 mask_fault1;//!<����� ������ 1
    Uint16 mask_fault2;//!<����� ������ 2
    
    Uint16 bit_fault_written1;
    Uint16 bit_fault_written2;

    long Imax_protect;	//!<������� �����������-������� ������
    long Umax_protect; 	//!<������� ������ max ���������� �� ���
    long Umin_protect;	//!<������� ������ min ���������� �� ���
    long speed_max;		//!<������� ������������ ��������
    long T_max;			//!<������� ������������ �����������

    int E;//!<���� ������� ���������
    Uint16 Main_ErrorCode;//!< //����������� ��� ������
    Uint32 Main_Flags;//!< //���� ��������� ���������� �����
    Uint16 powered_okCounter;//!< ������� ��� �������� �������� ������ ����� ����� �������������
    void (*init)(struct SSM_Protect*);     /* Pointer to the init funcion           */
    void (*slow_calc)(struct SSM_Protect*);     /* Pointer to the calc funtion           */
    void (*fast_calc)(struct SSM_Protect*);     /* Pointer to the calc funtion           */
    void (*ms_calc)(struct SSM_Protect*);     /* Pointer to the calc funtion           */
  } ;
  typedef struct SSM_Protect TSM_Protect;

 //!������������� �� ���������
#define SM_PROTECT_DEFAULTS {0,0,\
    0,0,\
	0,0,\
	0,0,\
    0,0,\
    0,0,\
    0,0,0,0,0,\
    0,0,0,0,\
    SM_Protect_Init,\
    SM_Protect_Slow_Calc,\
    SM_Protect_Fast_Calc,\
    SM_Protect_ms_Calc,\
  }

//! \memberof TSM_Protect
  void SM_Protect_Init(TSM_Protect*);
//! \memberof TSM_Protect
  void SM_Protect_Slow_Calc(TSM_Protect*);
//! \memberof TSM_Protect
  void SM_Protect_Fast_Calc(TSM_Protect*);
//! \memberof TSM_Protect
  void SM_Protect_ms_Calc(TSM_Protect*);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/






