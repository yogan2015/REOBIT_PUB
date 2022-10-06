#define NONE 0
#define RECT 1
#define RAMP 2
#define SIN  3

void Init(void)
{
  v->Out = v->Offset;
}

void Exec(void)
{
  float Tmp, Timeout, Tick, Temp, AngleVal;

switch (*v->Mode)
{
  case NONE:
  v->Out=*v->Ampl;
  break;
  case RECT:
    if ((short)*v->Reset)
    {
      v->Out = v->Offset;
      v->Timer = 0;
      return;
    }
    if (!*v->Freq) { v->Out = v->Offset; return; }
    Tmp = v->Out - v->Offset;
    Timeout = 0.5 / (*v->Freq * v->SampleTime);
    if (++v->Timer >= Timeout)
    {
      Tmp = (Tmp <= 0) ? *v->Ampl : -*v->Ampl;
      v->Timer = 0;
    }
    v->Out = Tmp + v->Offset;
  break;
  case RAMP:
    if ((short)*v->Reset || !*v->Freq)
    {
      v->Out   = v->Offset;
      v->Dir   = 0;
      v->Timer = 0;
      return;
    }
    Temp = v->Out - v->Offset;
    Tick = *v->Freq * v->SampleTime;
    if (!v->Dir)
    {
      Temp = Temp + (*v->Ampl * Tick * 4);
      if (Temp >= *v->Ampl) { Temp = *v->Ampl; v->Dir = 1; }
    }
    else
    {
      Temp = Temp - (*v->Ampl * Tick * 4);
      if (Temp <= -*v->Ampl) { Temp = -*v->Ampl; v->Dir = 0; }
    }
    if (++v->Timer >= (long)(1.0 / Tick)) { Temp = 0; v->Timer = 0; }
    v->Out = Temp + v->Offset;
    break;
  case SIN:
    if ((short)*v->Reset)
    {
      v->Timer = 0;
      AngleVal = 0;
    }
    else
    {
      v->Timer = v->Timer + (*v->Freq * v->SampleTime);
      if (v->Timer >= 1.0) v->Timer -= 1.0;
      AngleVal = v->Timer;
      if (AngleVal <  0.0) AngleVal += 1.0;
      if (AngleVal >= 1.0) AngleVal -= 1.0;
    }
    v->Out = v->Offset + *v->Ampl * sinf(2*M_PI * AngleVal);
    break;
}
}


