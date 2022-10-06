
#include "rtc.h"

void Init(void)
{
  struct TRtcCalendar *RtcObj = (struct TRtcCalendar *)v->Obj;

  v->Buf = (long)RtcObj;

  RtcObj->Sec     = 0;
  RtcObj->Min     = 0;
  RtcObj->Hour    = 0;
  RtcObj->WeekDay = 1;
  RtcObj->Day     = 1;
  RtcObj->Month   = 1;
  RtcObj->Year    = 0;
}

void Exec(void)
{
  struct TRtcCalendar *RtcObj = (struct TRtcCalendar *)v->Obj;

  v->Wr = 0;

  v->Counter = v->Counter + 1;
  if (v->Counter < v->Period) return;
  v->Counter = 0;

  if (v->Enable) RTC_Tick(RtcObj);

  if ((short)*v->InTime != v->PrevTime)
  {
    v->PrevTime = (short)*v->InTime;
    RTC_DecodeTime(RtcObj, (union TTimeVar *)&v->PrevTime, 0);
    v->Wr = 1;
  }

  if ((short)*v->InDate != v->PrevDate)
  {
    v->PrevDate = (short)*v->InDate;
    RTC_DecodeDate(RtcObj, (union TDateVar *)&v->PrevDate, 1);
    v->Wr = 1;
  }

  if (!(short)v->Wr)
  {
    RTC_EncodeTime(RtcObj, (union TTimeVar *)&v->Time);
    RTC_EncodeDate(RtcObj, (union TDateVar *)&v->Date);
  }
}

