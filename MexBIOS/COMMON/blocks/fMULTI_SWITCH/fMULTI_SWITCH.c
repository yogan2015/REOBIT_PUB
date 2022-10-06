
void Init(void)
{
}

void Exec(void)
{
  short __In = (short)*v->In;

  if ((short)*v->R)
  {
    v->Flag = 0;
    v->Out = 0;
    v->Time = 0;
    v->In_1 = __In;
    return;
  }

  if (__In && !v->In_1) switch (v->Flag)
  {
    case 5:  v->Flag = 0; break;
    case 1:  v->Time = v->SampleTime; v->Flag = 5; break;
    default: v->Time = v->SampleTime; v->Flag = 1;
  }

  if (!__In && v->In_1 && (v->Flag == 1)) { v->Time = v->SampleTime; v->Flag = 2; }
  if (v->Time != 0) v->Time += v->SampleTime;
  if ((v->Time > v->T_trg) && (v->Flag == 1)) v->Flag = 5;
  if (v->Time > v->TWarn_ON) v->Flag = 3;
  if (v->Time > (v->TWarn_ON + v->dTWarn)) v->Flag = 4;
  if (v->Time > v->T_ON) v->Flag = 0;

  switch(v->Flag)
  {
    case 0:  v->Out = 0; v->Time = 0; break;
    case 1:  v->Out = 1; break;
    case 2:  v->Out = 1; break;
    case 3:  v->Out = 0; break;
    case 4:  v->Out = 1; break;
    default: v->Out = 1; v->Time = 0;
  }

  v->In_1 = __In;
}

