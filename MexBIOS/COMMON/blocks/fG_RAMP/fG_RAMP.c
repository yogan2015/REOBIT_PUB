
void Init(void)
{
  v->Out = v->Offset;
}

void Exec(void)
{
  float Temp, Tick;

  if ((short)*v->Reset || !*v->Freq)
  {
    v->Out   = v->Offset;
    v->Dir   = 0;
    v->Timer = 0;
    return;
  }

  Temp = v->Out - v->Offset;
  Tick = *v->Freq * v->SampleTime;

  if (!v->BiDirectional)
  {
    Temp = Temp + (*v->Ampl * Tick);
  }
  else if (!v->Dir)
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
}


