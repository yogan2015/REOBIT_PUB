
void Init(void)
{
}

void Exec(void)
{
  v->Time += v->SampleTime;

  switch (v->State)
  {
    case 0:
      v->Out = 0;
      v->Time = 0;
      v->Counter = 0;
      if ((short)*v->En) v->State = 1;
      break;
    case 1:
      v->Out = v->Ampl;
      if (v->Time >= v->Time_Pulse_ON) { v->Time = 0; v->State = 2; }
      break;
    case 2:
      v->Out = 0;
      if (v->Time >= v->Time_Pulse_OFF)
      {
        v->Time = 0;
        if (++v->Counter < abs(*v->N)) v->State = 1;
        else if (!(short)*v->En || !v->Time_Restart) v->State = 0;
        else v->State = 3;
      }
      break;
    case 3:
      if (v->Time >= v->Time_Restart) { v->Time = 0; v->Counter = 0; v->State = 1; }
      break;
  }
}

