
void Init(void)
{

}

void Exec(void)
{
  #define GET_TIME(A)  ((A >> 24) << 24)
  long *Data = (long *)*v->Buf;
  long Timer, TimeStamp;
  short i, aState;

  aState = (short)*v->State;
  if (aState != 0)
  {
     if ((aState < 1) || (aState > v->StateCount)) return;
     v->CurrState = aState - 1;
     v->Flag = (short)*v->Mode ? 2 : 1;
  }
  else if ((short)*v->R || (v->Flag == 2))
  {
    v->CurrState = 0;
    v->Seconds   = 0;
    v->Minutes   = 0;
    v->Hours     = 0;
    v->Timeout   = 0;
    v->Flag      = 0;
  }
  else if (!v->Flag)
  {
    v->Seconds += v->SampleTime;
    if (v->Seconds >= _IQ24(60.0)) { v->Minutes += _IQ24(1.0); v->Seconds -= _IQ24(60.0); }
    v->Minutes = GET_TIME(v->Minutes) + _IQ24div(GET_TIME(v->Seconds), _IQ24(60.0));
    if (v->Minutes >= _IQ24(60.0)) { v->Hours += _IQ24(1.0); v->Minutes -= _IQ24(60.0); }
    v->Hours = GET_TIME(v->Hours) + _IQ24div(GET_TIME(v->Minutes), _IQ24(60.0)) + _IQ15div(GET_TIME(v->Seconds), _IQ15(3600));

    switch(v->TimeUnit)
    {
      case 0:  Timer = v->Seconds; break;
      case 1:  Timer = v->Minutes; break;
      case 2:  Timer = v->Hours;   break;
      default: Timer = 0;
    }

    TimeStamp = *(Data + (v->CurrState * (v->ParamCount + 1)));
    if (v->TimeFormat > 24) TimeStamp >>= (v->TimeFormat - 24);
    if (v->TimeFormat < 24) TimeStamp <<= (24 - v->TimeFormat);

    if (Timer >= (v->Timeout + TimeStamp))
    {
      v->Timeout += TimeStamp;
      v->CurrState++;
      if (v->CurrState >= v->StateCount)
      {
        v->CurrState = 0;
        v->Flag = (short)*v->Mode ? 2 : 1;
      }
    }
  }

  Data += (v->CurrState * (v->ParamCount + 1) + 1);
  for (i = 0; i < v->ParamCount; i++)
    (&v->Out)[i] = Data[i];
}

