
void Init(void)
{
}

void Exec(void)
{
  short __In = (short)*v->In;

  v->Out = 0;

  if (__In && !v->In_1 ) v->Time = v->SampleTime;

  if (v->Time != 0) { v->Time += v->SampleTime; v->Out = v->Ampl; }
  if ((v->Time > v->Time_Pulse_ON ) || !__In) v->Time = 0;

  v->In_1 = __In;
}

