
void Init(void)
{
}

void Exec(void)
{
  v->Q = v->Out_1;
  if ((short)*v->In && !v->In_1) v->D++;

  v->Time += v->SampleTime;
  if (v->Time >= v->T)
  {
    if (v->D >= v->Level_ON)  v->Q = 1;
    if (v->D <= v->Level_OFF) v->Q = 0;
    v->Time = 0;
    v->D = 0;
  }

  v->Out_1 = (short)v->Q;
  v->In_1  = (short)*v->In;
}

