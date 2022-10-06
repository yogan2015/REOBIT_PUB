
void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->In)
  {
    if ((short)v->Out) { v->Time = 0; return; }
    v->Time += v->SampleTime;
    if (v->Time >= v->Time_Del_ON) v->Out = *v->In;
  }
  else
  {
    if (!(short)v->Out) { v->Time = 0; return; }
    v->Time += v->SampleTime;
    if (v->Time >= v->Time_Del_OFF) v->Out = 0;
  }
}

