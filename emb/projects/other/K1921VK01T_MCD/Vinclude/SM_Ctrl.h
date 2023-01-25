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
 
 \file      SMCtrl.h
 \brief     �������� �� ������������ ������ ���������� (��. TSM_Ctrl)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  SMCtrl �������� �� ������������ ������ ����������  (��. TSM_Ctrl)
 @{
*/

#ifndef SM_Ctrl_H
#define SM_Ctrl_H

#ifdef __cplusplus
extern "C"
{
#endif


/*! \class TSM_Ctrl
      \brief �������� �� ������������ ������ ����������

      ����� \a TSM_Ctrl, ���������� �� ��������� SSMCtrl, ��������
      �������� ���������� ������� ������������ ������ ����������. � ������ ��
      ��������� ������� �������� ����������� �� ��� ���� ��������� ����������.
      ��������� ���������� �� ������� ������. ������ ����������� ������ ���,
      ������ � ������������ ��������������, ���, �� � �.�. ��������� ���������� ����� ����:
      ��������� ����������, ��������� �� ���� ������� ����������, ��������� ���������� � �.�.
      � run_mode �������� ����� �������� ��������� ����������.
       */

//! ��. TSM_Ctrl

  struct SSM_Ctrl
  {
    long ctrl_counter;//!<������� ������� ���������� � ����� ���������
    long run_mode;//!�������� ����� ������ (�������� ���������). ��������� ����������, ���������, ���������� ��� � �.�.
    int state;//!<��������� ����������� �������� - ��� �� ������� ��������� ����������.
    int state_prev;//!<���������� ���������
    int E;//!<���� ������� ���������.
    long AnglePrev;//!< ���������� �������� ���� ��� ������ ������������� ���
    long AngleDemo;//!< ���� ��� ����-������ ������� ���������
    void (*init)(struct SSM_Ctrl*);     //!< Pointer to the init funcion
    void (*slow_calc)(struct SSM_Ctrl*);//!< Pointer to the calc funtion
    void (*fast_calc)(struct SSM_Ctrl*); //!< Pointer to the calc funtion
    void (*ms_calc)(struct SSM_Ctrl*);  //!< Pointer to the calc funtion
  } ;

  typedef struct SSM_Ctrl TSM_Ctrl;

//!������������� �� ���������
#define SM_CTRL_DEFAULTS {0,0,0,0,0,0,0,\
    SM_Ctrl_Init,\
    SM_Ctrl_Slow_Calc,\
    SM_Ctrl_Fast_Calc,\
	SM_Ctrl_ms_Calc,\
    }

  //! \memberof TSM_Ctrl
  void SM_Ctrl_Init(TSM_Ctrl*);
  //! \memberof TSM_Ctrl
  void SM_Ctrl_Slow_Calc(TSM_Ctrl*);
  //! \memberof TSM_Ctrl
  void SM_Ctrl_Fast_Calc(TSM_Ctrl*);
  //! \memberof TSM_Ctrl
  void SM_Ctrl_ms_Calc(TSM_Ctrl*);

#ifdef __cplusplus
}
#endif


#endif


/*@}*/




