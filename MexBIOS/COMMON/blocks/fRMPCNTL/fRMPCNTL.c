
void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->R) { v->Out = ((short)*v->R & 0x2) ? *v->In : 0; v->RampDelayCount = 0; return; }

  if (fabs(*v->In - v->Out) > v->DeltStep)
  {
    if (++v->RampDelayCount >= v->RampDelayMax)
    {
      if (*v->In >= v->Out)
      {
        v->Out += v->DeltStep;
        if (v->Out > v->RampHighLimit) v->Out = v->RampHighLimit;
       }
       else
       {
         v->Out -= v->DeltStep;
         if (v->Out < v->RampLowLimit) v->Out = v->RampLowLimit;
       }
       v->RampDelayCount = 0;
    }
  }
  else
  {
    v->Out = *v->In;
  }
}




