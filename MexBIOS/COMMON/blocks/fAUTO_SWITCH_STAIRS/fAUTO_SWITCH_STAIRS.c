
void Init(void)
{
}

void Exec(void)
{
  v->Out = 0;

  if ( ((short)*v->In != 0) && !v->In_1 )
    v->Time = v->SampleTime;

  if ( v->Time != 0 )
    { v->Time += v->SampleTime; v->Out = 1; }

  if ( v->Time > v->TWarn_ON )
        v->Out = 0;

  if ( v->Time > ( v->TWarn_ON + v->dTWarn ) )
        v->Out = 1;

    if ( v->Time > v->T_ON )
        { v->Time = 0; v->Out = 0; }

    v->In_1 = (short)*v->In;
}

