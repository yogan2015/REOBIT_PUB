
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

 \file      Global_time.c
 \brief     ������ ������ �� ��������
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.2 2013_10_16

*/

/** \addtogroup Global_time */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif


#include <main.h>


//!������������� ������

//!���� ���� ���� ��������� �������, ��������� �� ��� �����.
//!��������������� ����� ������ � ������� ����������� ��������� �� SPI.

//! \memberof TGlobalTime
void GlobalTime_init(TGlobalTime *p)
{
	p->read_PowerOn_time(p);
	p->read_oper_time(p);


	#ifdef USE_ABSOLUTE_TIME_CLOCK
	//������������� ����������� �������
	if (p->time_type == 1)
	{
		//������������� �� ����� ��������� �������
		p->absolute_time.day=spiclock.day;
		p->absolute_time.hour=spiclock.hour;
		p->absolute_time.minute=spiclock.minute;
		p->absolute_time.second=spiclock.second;
		p->absolute_time.year=spiclock.year;
	}
	#endif
	//������������� �������������� �������
	p->relative_time1.ON = 1;//�.�. 1-� ����� �������� ������������

	p->relative_time1.relative_date.hour = (p->PowerOn_time >> 6);
	p->relative_time1.relative_date.minute = (p->PowerOn_time & 0x3f);

	p->relative_time2.relative_date.hour = (p->operational_time >> 6);
	p->relative_time2.relative_date.minute = (p->operational_time & 0x3f);
}




//!������ �������������� �������.

//!�������� ������� ������� ������������ ������� �, ���� ����, ��������� �����
//!� ������ ����� ��������� ������� � ���������� �����.

//! \memberof TGlobalTime
void GlobalTime_calc(TGlobalTime *p)
{
	//���� ������������� ������
	GlobalTime_REL_TIME_calc(&p->relative_time1);
	GlobalTime_REL_TIME_calc(&p->relative_time2);
}


//!������ �������������� �������.

//!�������� ������� ������� ������������ ������� �, ���� ����, ��������� �����
//!� ������ ����� ��������� ������� � ���������� �����.

//! \memberof TGlobalTime
void GlobalTime_ms_calc(TGlobalTime *p) {

	//���������� ������ operational_time
	if (sm_ctrl.state != 0) //���� � �����-�� ������ ������
		global_time.relative_time2.ON = TRUE;
	else
		global_time.relative_time2.ON = FALSE;

	//����� ����������� ��������� � �������
	p->PowerOn_time = (global_time.relative_time1.relative_date.hour << 6) + (global_time.relative_time1.relative_date.minute & 0x3f);
	//����� � ������, � �������
	p->operational_time = (global_time.relative_time2.relative_date.hour << 6) + (global_time.relative_time2.relative_date.minute & 0x3f);

	p->PowerOn_time_min = p->relative_time1.relative_date.hour*60 +p->relative_time1.relative_date.minute;
	p->operational_time_min = p->relative_time2.relative_date.hour*60 + p->relative_time2.relative_date.minute;


#ifdef USE_ABSOLUTE_TIME_CLOCK
	if (global_time.time_type == 1) {
		//����� - �� ����� ��������� �������
		global_time.absolute_time.day = spiclock.day;
		global_time.absolute_time.hour = spiclock.hour;
		global_time.absolute_time.minute = spiclock.minute;
		global_time.absolute_time.second = spiclock.second;
		global_time.absolute_time.year = spiclock.year;
	}
#endif
}

//!������ �������������� �������

//!��������, ��� ������� ���������� � �����-�� ������������ ��������������,
//!�������������� ������������� �����, ���������� �� � ��������� ���� RELATIVE_TIME
//! \memberof TGlobalTime
void GlobalTime_REL_TIME_calc(RELATIVE_TIME *p) {
	if (p->ON == 0)
		return;
	if (p->tic_isr != 0)
		p->tic_isr--;
	p->delta_millisecond = 0;
	p->delta_second = 0;
	if (p->tic_isr == 0) {
		//������������
		p->tic_isr = GLOBAL_TIME_CALC_FREQ;
		p->millisecond_counter++;
		p->delta_millisecond = 1;
		if (p->relative_date.millisecond == 999) {
			//�������
			p->relative_date.millisecond = 0;
			p->second_counter++;
			p->delta_second = 1;
			if (p->relative_date.second == 59) {
				//������
				p->relative_date.second = 0;
				if (p->relative_date.minute == 59) {
					//���
					p->relative_date.minute = 0;
					p->relative_date.hour++;
				} else
					p->relative_date.minute++;
			} else
				p->relative_date.second++;
		} else
			p->relative_date.millisecond++;
	}
}


//!������ ����� ���������.

//! \memberof TCurPar
void GlobalTime_read_PowerOn_time(TGlobalTime *p) { //������ work_time
	UserMem.MemStartAddr = GLOBAL_TIME_POWER_ON_TIME_ADDR;
	UserMem.MCUStartAddr = (Uint16*) (&(p->PowerOn_time));
	UserMem.data_length = 4;
	UserMem.read(&UserMem);
}


//!���������� ����� ���������.

//! \memberof TCurPar
void GlobalTime_write_PowerOn_time(TGlobalTime *p) { //������ work_time
	UserMem.MemStartAddr = GLOBAL_TIME_POWER_ON_TIME_ADDR;
	UserMem.MCUStartAddr = (Uint16*) (&(p->PowerOn_time));
	UserMem.data_length = 4;
	UserMem.write(&UserMem);
}

//!������ ����� ����������� ���������.
//! \memberof TCurPar
void GlobalTime_read_oper_time(TGlobalTime *p) { //������ operational_time
	UserMem.MemStartAddr = GLOBAL_TIME_OPERATIONAL_TIME_ADDR;
	UserMem.MCUStartAddr = (Uint16*) (&(p->operational_time));
	UserMem.data_length = 4;
	UserMem.read(&UserMem);
}

//!���������� ����� ����������� ���������.
//! \memberof TCurPar
void GlobalTime_write_oper_time(TGlobalTime *p) { //������ operational_time
	UserMem.MemStartAddr = GLOBAL_TIME_OPERATIONAL_TIME_ADDR;
	UserMem.MCUStartAddr = (Uint16*) (&(p->operational_time));
	UserMem.data_length = 4;
	UserMem.write(&UserMem);
}


void GlobalTime_slow_calc(TGlobalTime*p) {
	//���� ����� ���� �� ���������� ������ � SPI ��� � ������ ������� ������ ������ ���
	if ((p->WtiteSPI_flag) || (p->PrevWriteSPIHour != global_time.relative_time1.relative_date.hour)) {

		p->write_PowerOn_time(p); //������ ������� ���. ���������
		p->write_oper_time(p); //������ �������� �������
		p->PrevWriteSPIHour = global_time.relative_time1.relative_date.hour;
		p->WtiteSPI_flag = 0;
	}
}



#ifdef __cplusplus
} // Extern "C"
#endif
/*@}*/

