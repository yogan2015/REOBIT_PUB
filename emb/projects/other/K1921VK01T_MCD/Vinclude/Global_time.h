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

 \file      Global_time.h
 \brief     ������ ������ �� ��������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.1 2010_02_24

*/

#ifndef GLOBAL_TIME_H
#define GLOBAL_TIME_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "DSP.h"

#define GLOBAL_TIME_CALC_FREQ	10	//!<��� ������� ������ ������� calc
//#define USE_ABSOLUTE_TIME_CLOCK	//���������������� ���� ������������ ���� ��������� �������



#define GLOBAL_TIME_SPI_START_ADDR 6500						//!<��������� ����� � SPI

#define GLOBAL_TIME_POWER_ON_TIME_ADDR GLOBAL_TIME_SPI_START_ADDR
#define GLOBAL_TIME_OPERATIONAL_TIME_ADDR GLOBAL_TIME_SPI_START_ADDR + 4


//!���������� �����
  struct SABSOLUTE_TIME
  {
    int16 second;
    int16 minute;
    int16 hour;
    int16 day;
    int16 year;
  };
  typedef volatile struct SABSOLUTE_TIME ABSOLUTE_TIME;

//!������������� ����
  typedef struct
  {
    int16 millisecond;
    int16 second;
    int16 minute;
    int32 hour;
  }RELATIVE_DATE;


//!������������� �����
  struct SRELATIVE_TIME
  {
    int		ON;
    Uint32  tic_isr;
    Uint32  millisecond_counter;
    Uint32  second_counter;
    int16 	delta_millisecond;
    int16 	delta_second;
    RELATIVE_DATE	relative_date;
  };
  typedef volatile struct SRELATIVE_TIME RELATIVE_TIME;



  /*! \class TGlobalTime
        \brief ������ ������ �� ��������.

        ����� \a TGlobalTime, ���������� �� ��������� SGlobalTime, �������� ������
        ��� ������ �� ��������.����������� ����� �:\n
  				  ��� ������� ������� ������ � �.�.:\n
  					�����������:	0-999\n
  					�������:		0-59\n
  					������:			0-59\n
  					����:			0-23\n
  					���:			0-364\n
  					����:			0-�������� �� 160 ���\n
  				  ��� ������� ����� (���������� �������):\n
  					�����������:	0-0xFFFFFFFF - ������������� �������� 1.5 �������\n
  					�������:		0-0xFFFFFFFF - ������������� �������� 160 �����\n

      ���� ����������� ������, ����������� ����������� �������� ������� � ���������
  �� ����������� �  ��������� ���. ������������ ���������� delta_millisecond,
  ������� ���������� � ������� ������ ������������ � �� ��������� ������� ���
  ������������. ����� ����� � ����������� ������� �������� counter+=delta_millisecond �
  �������� � counter ������� �����������. ���������� delta_second.

  ����������:   1. ������ �� ������� �������������
  				2. ������������� ����������������� ��� ��������� ������� �������

  ��� ���������� ������ ������ ������������ ������:
  1. � ������� GLOBAL_TIME_CALC_FREQ ��������� �������  ������� ������� ������ ������� �������.
  ������� ��������, ��� �������� GLOBAL_TIME_CALC_FREQ �������������, �������
  ������ ��������� �������� ������ ��� ����� ��������� ������� ������� (� ���).
  ���������� ������ � ���������� ����������� ������.
  */

//! ��. TGlobalTime
  struct SGlobalTime
  {
    RELATIVE_TIME relative_time1;//!������������� ����� 1
    RELATIVE_TIME relative_time2;//!������������� ����� 2
    ABSOLUTE_TIME absolute_time;//!���������� �����
    int16 time_type;//!���� ��������� ������� (1 - ����)
	int32 PowerOn_time;				//!<����� ����� ���������
	int32 PowerOn_time_min;				//!<����� ����� ��������� � �������
	int32 operational_time;	//!<����� ����� ����������� ���������
	int32 operational_time_min;				//!<����� ����� ����������� ��������� � �������
	int16 WtiteSPI_flag;
	int32 PrevWriteSPIHour;
    void	(*init)(volatile struct SGlobalTime*);
    void	(*calc)(volatile struct SGlobalTime*);
    void	(*ms_calc)(volatile struct SGlobalTime*);
    void	(*slow_calc)(volatile struct SGlobalTime*);
	void (*read_PowerOn_time)(volatile struct SGlobalTime*);
	void (*write_PowerOn_time)(volatile struct SGlobalTime*);
	void (*read_oper_time) (volatile struct SGlobalTime*);
	void (*write_oper_time)(volatile struct SGlobalTime*);
  };

  typedef volatile struct SGlobalTime TGlobalTime;

//!������������ ������������� ����.
#define RELATIVE_DATE_DEFAULTS {0,0,0,0}

//!������������� �������������� �������.
#define RELATIVE_TIME_DEFAULTS {0,\
    0,0,0,0,0,\
    RELATIVE_DATE_DEFAULTS,\
  }
//!������������� ����������� �������.
#define ABSOLUTE_TIME_DEFAULTS {0,0,0,0,0}

//!������������� TGlobalTime.
#define GLOBAL_TIME_DEFAULTS { RELATIVE_TIME_DEFAULTS,\
    RELATIVE_TIME_DEFAULTS,\
    ABSOLUTE_TIME_DEFAULTS,\
    1,0,0,0,0,0,0,\
    GlobalTime_init,\
    GlobalTime_calc,\
    GlobalTime_ms_calc,\
    GlobalTime_slow_calc,\
	GlobalTime_read_PowerOn_time, \
	GlobalTime_write_PowerOn_time, \
	GlobalTime_read_oper_time, \
	GlobalTime_write_oper_time,\
  }

//! \memberof TGlobalTime
  void GlobalTime_init(TGlobalTime*);
//! \memberof TGlobalTime
  void GlobalTime_calc(TGlobalTime*);
  //! \memberof TGlobalTime
  void GlobalTime_ms_calc(TGlobalTime*);
//! \memberof TGlobalTime
  void GlobalTime_slow_calc(TGlobalTime*);

//! \memberof TGlobalTime
  void GlobalTime_REL_TIME_calc(RELATIVE_TIME *p);

//! \memberof TGlobalTime
void GlobalTime_read_PowerOn_time(TGlobalTime*);
//! \memberof TGlobalTime
void GlobalTime_write_PowerOn_time(TGlobalTime*);
//! \memberof TGlobalTime
void GlobalTime_read_oper_time(TGlobalTime*);
//! \memberof TGlobalTime
void GlobalTime_write_oper_time(TGlobalTime*);



#ifdef __cplusplus
}
#endif


#endif



/*@}*/

