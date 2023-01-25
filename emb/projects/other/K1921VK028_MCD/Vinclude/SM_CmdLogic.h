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

 \file      SMCmdLogic.h
 \brief     ��������� ������ � �������, ����������� �� ��������� ����������. (��. TSM_CmdLogic)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  SMCmdLogic ��������� ������ � �������, ����������� �� ��������� ����������. (��. TSM_CmdLogic)
 @{
*/


#ifndef SM_CmdLogicH
#define SM_CmdLogicH

#include "V_common.h"

#ifdef __cplusplus
extern "C"
{
#endif


//! ������� �����������, ������ � ������� (�����)
#define CMD_LOGIC_TURNED_OFF 		0x0
//! ��������� ������
#define CMD_LOGIC_TURNED_ON			0x2

#if defined (HW_MCB3)
//��� ���������� ������������ �� ���������� ������� ���������� ����� � �������������� ���������� (��. V_DIO)
#define	STARTBUTTON     (dio.in_bit.n0)	    //�������� �� ������� ���� � ������� ���������� ������
#define	STOPBUTTON 	    (dio.in_bit.n1)	    //�������� �� ������� ���� � ������� ���������� ������
#define	RESETBUTTON 	(dio.in_bit.n2)	    //�������� �� ������� ���� � ������� ���������� ������
#elif defined (HW_MCB3_SIMULATOR)
#define STARTBUTTON     0
#define STOPBUTTON      0
#define RESETBUTTON     0
#endif


/*! \class TSM_CmdLogic
      \brief ��������� ������ � �������, ����������� �� ��������� ����������.

      ����� \a TSM_CmdLogic, ���������� �� ��������� SSMCmdLogic, ������ ��� ��������� ������
      ������������ ���������� � ������� ��������. ������� ����� ��������� ��� �� CANOpen,
      ��� � �� ������ ���������� (ModBus). �������� ���������� �������, ������� ����������� 
      ������� ����� ����������� ������ � ������� (�����).
*/

//! ��. TSM_CmdLogic
  struct SSM_CmdLogic
  {
    int state;//!<C��������
    int state_prev;//!<���������� ���������
    int E;//!<���� ������� ���������
    TCmd cmd_by_level_prev;//!<���������� ��������� ���������� �����
    int ReRunCounter;//!< ������� ������� � ������� ����������� ������� �������
    int StartButtonPrev;
    int StartButton;
    int StopButtonPrev;
    int StopButton;
    int ResetButton;
    int ResetButtonPrev;
    void (*init)(volatile struct SSM_CmdLogic*);//!<    Pointer to the init funcion
    void (*slow_calc)(volatile struct SSM_CmdLogic*);//!< Pointer to the calc funtion
    void (*ms_calc)(volatile struct SSM_CmdLogic*); //!< Pointer to the calc funtion
  };

  typedef volatile  struct SSM_CmdLogic TSM_CmdLogic;
  
//! ������������ �� ���������
#define SM_CMD_LOGIC_DEFAULTS {0,0,0,{0},0,0,0,0,0,0,0,\
    SM_CmdLogicInit,\
    SM_CmdLogicSlow_Calc,\
    SM_CmdLogicms_Calc}

//! \memberof TSM_CmdLogic
  void SM_CmdLogicInit(TSM_CmdLogic*);
//! \memberof TSM_CmdLogic
  void SM_CmdLogicSlow_Calc(TSM_CmdLogic*);
//! \memberof TSM_CmdLogic
  void SM_CmdLogicms_Calc(TSM_CmdLogic*);


#ifdef __cplusplus
}
#endif

#endif


/*@}*/





