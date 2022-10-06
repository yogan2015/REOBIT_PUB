
void Init(void)
{
}

void Exec(void)
{
  float Up1, Ud, Out1;

  if ((short)*v->R)
  {
    v->Out    = 0;
    v->Up     = 0;
    v->Ui     = 0;
    v->SatErr = 0;
    return;
  }

  Up1   = *v->Kp * (*v->Ref - *v->Fdb);
  v->Ui = v->Ui + *v->Ki * Up1 + *v->Kc * v->SatErr;
  Ud    = *v->Kd * (Up1 - v->Up);
  Out1  = Up1 + v->Ui + Ud;

  v->Out = Out1;
  if (v->Out > *v->Max) v->Out = *v->Max;
  if (v->Out < *v->Min) v->Out = *v->Min;

  v->SatErr = v->Out - Out1;
  v->Up     = Up1;
}


