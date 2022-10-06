
void Init(void)
{

}

void Exec(void)
{
  #define GET_TIME(A)  (float)((long)A)
  float *Data = (float *)*v->Buf;
  float Timer, TimeStamp;
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
    if (v->Seconds >= 60) { v->Minutes++; v->Seconds -= 60; }
    v->Minutes = GET_TIME(v->Minutes) + (v->Seconds / 60);
    if (v->Minutes >= 60) { v->Hours++; v->Minutes -= 60; }
    v->Hours = GET_TIME(v->Hours) + (GET_TIME(v->Minutes) / 60) + (GET_TIME(v->Seconds) / 3600);

    switch(v->TimeUnit)
    {
      case 0:  Timer = v->Seconds; break;
      case 1:  Timer = v->Minutes; break;
      case 2:  Timer = v->Hours;   break;
      default: Timer = 0;
    }

    TimeStamp = *(Data + (v->CurrState * (v->ParamCount + 1)));
    if (Timer >= (v->Timeout + TimeStamp))
    {
      v->Timeout += TimeStamp;
      v->CurrState++;
      if (v->CurrState >= v->StateCount)
      {
        v->CurrState = 0;
        v->Flag  = (short)*v->Mode ? 2 : 1;
      }
    }
  }

  Data += (v->CurrState * (v->ParamCount + 1) + 1);
  for (i = 0; i < v->ParamCount; i++)
    (&v->Out)[i] = Data[i];
}

