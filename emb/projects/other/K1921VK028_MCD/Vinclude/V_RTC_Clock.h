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

 \file        V_RTC_Clock.h
 \brief   ������ ������ � ������ ��������� �������
 \author    ��� "��� ������". ��� ����� ��������. http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  V_rmp_ctrl �������� ������������� (��. TRMPCtrl)

 @{
*/
#ifndef V_RTC_CLOCK_H_
#define V_RTC_CLOCK_H_

#define RTC_SLAVE_ADDRESS	0x68			// ��� RTC DS1340 ����� 1101 000b = 0x68 (���� � ����������� ��� ��� ��� �� ��������� ����
											// � �������� 1101 0000b = 0xD0)
#define RTC_WRITE_ERROR		1
#define RTC_READ_ERROR		2
#define RTC_TIMEOUT_ERROR	3

#define RTC_TIMEOUT			1000		// ���������� �������� ����
#define RTC_SECOND_WAITING_TIMEOUT			10000		// �����, � ������� �������� ������ ��������� ������� (�������� � ��). ���� �� ��������, ������ ���� �� ��������.

struct SRTCClock{
	Uint16 ms;			// �� ������
	Uint16 msInDay;		// ���������� � ������ �����
	Uint16 error;		// ��� ������
	Uint16 tryCounter;	// ������� �������� ����

	Uint16 second;
	Uint16 minute;
	Uint16 hour;

	Uint16 DOW;			// DayOfWeek - ���� ������ (����� �����, ���, ����� ��� ��?)
	Uint16 day;			// Date - ��� ����� ������
	Uint16 month;
	Uint16 year;

	Uint32 packed_time;	// �����, ����������� � �����
	Uint32 timeToSet;	// �����, ������� ����� ���������� �� �����, ����������� � �����

	Uint16 setTimeFlag;
	Uint16 readTimeFlag;

	Uint16 secondPrev;
	Uint16 stoppedCounter;
	Uint16 ClockOk;
	void (*init)(volatile struct SRTCClock*);					// �������������
	void (*read)(volatile struct SRTCClock*);					// ��������� ����� �� �������
	void (*set)(volatile struct SRTCClock*);					// �������� ����� � ������
	void (*msCalc)(volatile struct SRTCClock*);
	void (*slowCalc)(volatile struct SRTCClock*);
};

typedef volatile struct SRTCClock TRTCClock;

#define RTC_CLOCK_DEFAULTS {0,0,0,0, 0,0,0, 0,0,0,0, 0,0, 0,0, 0,0,0,\
							RTC_Clock_Init,\
							RTC_Clock_Read_Time,\
							RTC_Clock_Set_Time,\
							RTC_Clock_Ms_Calc,\
							RTC_Clock_Slow_Calc}

void RTC_Clock_Init (TRTCClock *);
void RTC_Clock_Read_Time (TRTCClock *);
void RTC_Clock_Set_Time (TRTCClock *);
void RTC_Clock_Ms_Calc (TRTCClock *);
void RTC_Clock_Slow_Calc (TRTCClock *);

#endif /* V_I2CCLOCK_H_ */
