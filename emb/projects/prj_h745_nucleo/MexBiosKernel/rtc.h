
#ifndef RTC_
#define RTC_

#ifndef _FUNC_CALL_
#ifndef __BORLANDC__
#define _FUNC_CALL_
#else
#define _FUNC_CALL_ __stdcall
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define RTC_AM_PM         0x20 // 0 - AM, 1 - PM
#define RTC_AM_PM_MODE    0x40 // Enable

typedef unsigned short TRtcVar;

union TTimeVar {
	TRtcVar all;
	struct {
		TRtcVar Min:6;
		TRtcVar Hour:10;
	} bit;
};

union TDateVar {
	TRtcVar all;
	struct {
  	TRtcVar Day:5;
	   TRtcVar Month:4;
  	TRtcVar Year:7;
	} bit;
};

struct TRtcCalendar {
	TRtcVar Sec;
	TRtcVar Min;
	TRtcVar Hour;
	TRtcVar WeekDay;
	TRtcVar Day;
	TRtcVar Month;
	TRtcVar Year;
};

void    _FUNC_CALL_ RTC_Tick(struct TRtcCalendar *);
TRtcVar _FUNC_CALL_ RTC_DefMaxDay(TRtcVar Year, TRtcVar Month);
void    _FUNC_CALL_ RTC_DecodeTime(struct TRtcCalendar *, union TTimeVar *Time, TRtcVar Sec);
void    _FUNC_CALL_ RTC_DecodeDate(struct TRtcCalendar *, union TDateVar *Date, TRtcVar WeekDay);
void    _FUNC_CALL_ RTC_EncodeTime(struct TRtcCalendar *, union TTimeVar *Time);
void    _FUNC_CALL_ RTC_EncodeDate(struct TRtcCalendar *, union TDateVar *Date);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* RTC */ 




