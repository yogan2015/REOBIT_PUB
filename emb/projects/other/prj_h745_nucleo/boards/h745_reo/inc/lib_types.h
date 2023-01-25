#ifndef __LIBTYPES__
#define __LIBTYPES__

typedef struct _PWM_STR {
  long   *Cmp1;
  long   *Cmp2;
  long   *Cmp3;
  long   *Cmp4;
  short   Id;
  short   CountMode;
  long    Frequency;
  short   CountCMP;
  short   Polarity;
  short   OutInverted;
  short   __rsvd1;
  long    DeadTime;
  long    Pulse;
  short   MasterTimer;
  short   MasterSlaveMode;
  short   InputTrigger;
  short   IntEnable;
  short   BreakPolarity;
  short   __rsvd2;
  long    TimerFreq;
  long    PwmPeriod;
  long    newFreq;
  long    hCmp1;
  long    hCmp2;
  long    hCmp3;
  long    hCmp4;
} PWM_STR;


#endif
