
void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->R) { v->Out = ((short)*v->R & 0x2) ? *v->In : 0; v->DelayCount = 0; return; }

  if (v->Out != *v->In)
  {
    if (++v->DelayCount >= v->DelayMax)
    {
      if (v->Out < *v->In)
      {
        if (++v->Out > v->OutMax) v->Out = v->OutMax;
      }
      else
      {
        if (--v->Out < v->OutMin) v->Out = v->OutMin;
      }
      v->DelayCount = 0;
    }
  }
}

