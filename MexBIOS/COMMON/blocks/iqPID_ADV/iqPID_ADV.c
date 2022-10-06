
void Init(void)
{
}

void Exec(void)
{
  long Up1, Ud, Out1;

  if ((short)*v->R)
  {
    v->Out    = 0;
    v->Up     = 0;
    v->Ui     = 0;
    v->SatErr = 0;
    return;
  }

  Up1       = __IQmpy(*v->Kp, *v->Ref - *v->Fdb, v->Format);
  v->Ui     = v->Ui + __IQmpy(*v->Ki, Up1, v->Format) + __IQmpy(*v->Kc, v->SatErr, v->Format);
  Ud        = __IQmpy(*v->Kd, Up1 - v->Up, v->Format);
  Out1      = Up1 + v->Ui + Ud;
  v->Out    = _IQsat(Out1, *v->Max, *v->Min);
  v->SatErr = v->Out - Out1;
  v->Up     = Up1;
}


