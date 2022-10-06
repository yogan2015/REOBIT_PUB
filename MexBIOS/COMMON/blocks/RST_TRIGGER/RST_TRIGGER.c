
void Init(void)
{
}

void Exec(void)
{
  if (v->Priority)
  {
    if ((short)*v->S) v->Out = 1;
    if ((short)*v->R) v->Out = 0;
  }
  else
  {
    if ((short)*v->R) v->Out = 0;
    if ((short)*v->S) v->Out = 1;
  }
  if (!(short)*v->R && !(short)*v->S && v->T_1 && !(short)*v->T) v->Out = !(short)v->Out;
  v->T_1 = (short)*v->T;
}

