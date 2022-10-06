
void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->R) { v->Out = ((short)*v->R & 0x2) ? *v->In : 0; v->DelayCount = 0; return; }

  if (*v->In > v->Out) v->Out = *v->In;
  else if (*v->In < v->Out)
  {
    if (++v->DelayCount >= v->DelayMax)
    {
      if (--v->Out < v->OutMin) v->Out = v->OutMin;
      v->DelayCount = 0;
    }
  }
}

