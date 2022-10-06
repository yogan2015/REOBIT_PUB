
void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->R)  { v->Out = 0;      v->Time = 0; return; }
  if ((short)*v->In) { v->Out = *v->In; v->Time = 0; return; }

  v->Time += v->SampleTime;
  if (v->Time >= v->Time_Del_OFF)
  {
    v->Out = 0;
    v->Time = v->Time_Del_OFF;
  }
}

