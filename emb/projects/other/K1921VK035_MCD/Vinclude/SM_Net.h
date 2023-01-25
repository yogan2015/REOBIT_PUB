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
 
 \file      SMNet.h
 \brief     ������ ������ ���������� ��� ������ � �����. (��. TSM_Net)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  SMNet ������ ������ ���������� ��� ������ � �����. (��. TSM_Net)
 @{
*/

#ifndef SM_Net_H
#define SM_Net_H

#ifdef __cplusplus
extern "C"
{
#endif

#define DRV_STATUS_INIT 0x0
#define DRV_STATUS_READY 0x1
#define DRV_STATUS_RUNNING 0x2
#define DRV_STATUS_FAULT 0x3
#define DRV_STATUS_TESTING 0x4
#define DRV_STATUS_STOPPED 0x5
#define DRV_STATUS_AUTO_SET 0x6
#define DRV_STATUS_ALARM 0x8

/*! \class TSM_Net
      \brief ������ ������ ���������� ��� ������ � �����.

      ����� \a TSM_Net, ���������� �� ��������� SSMNet, ��������
      ������ ������ ���������� ��� ������ � ���������� �������� ������������.
      ����� ������� ������� ���������� ������� �������, ������ � ��������������� �������������� � �.�.

*/

//! ��. TSM_Net
  struct SSM_Net
  {
    int state; //!<���������
    int state_prev;//!<��������� ����������
    int E;//!<���� ������� ���������
    void (*init)(struct SSM_Net*);     /* Pointer to the init funcion           */
    void (*slow_calc)(struct SSM_Net*);     /* Pointer to the calc funtion           */
    void (*ms_calc)(struct SSM_Net*);     /* Pointer to the calc funtion           */
    void (*fast_calc)(struct SSM_Net*);     /* Pointer to the calc funtion           */
  } ;
  typedef struct SSM_Net TSM_Net;

//!������������� �� ���������
#define SM_NET_DEFAULTS {0,0,0,\
    SM_Net_Init,\
    SM_Net_Slow_Calc,\
    SM_Net_ms_Calc,\
    SM_Net_fast_Calc,\
}

  //! \memberof TSM_Net
  void SM_Net_Init(TSM_Net*);
  //! \memberof TSM_Net
  void SM_Net_Slow_Calc(TSM_Net*);
  //! \memberof TSM_Net
  void SM_Net_ms_Calc(TSM_Net*);
  //! \memberof TSM_Net
  void SM_Net_fast_Calc(TSM_Net*);
  
#ifdef __cplusplus
}
#endif


#endif


/*@}*/




