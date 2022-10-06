
void Init(void)
{
  v->Out = v->Offset;
}

void Exec(void)
{
  long Temp, Tick;

  if ((short)*v->Reset || !*v->Freq)
  {
    v->Out   = v->Offset;
    v->Dir   = 0;
    v->Timer = 0;
    return;
  }

  Temp = v->Out - v->Offset;
  Tick = _IQ24mpy(*v->Freq, v->SampleTime);

  if (!v->BiDirectional)
  {
    Temp = Temp + _IQ24mpy(*v->Ampl, Tick);
  }
  else if (!v->Dir)
  {
    Temp = Temp + _IQ22mpy(*v->Ampl, Tick);
    if (Temp >= *v->Ampl) { Temp = *v->Ampl; v->Dir = 1; }
  }
  else
  {
    Temp = Temp - _IQ22mpy(*v->Ampl, Tick);
    if (Temp <= -*v->Ampl) { Temp = -*v->Ampl; v->Dir = 0; }
  }

  if (++v->Timer >= _IQ1div(_IQ24(0.5), Tick)) { Temp = 0; v->Timer = 0; }

  v->Out = Temp + v->Offset;
}


