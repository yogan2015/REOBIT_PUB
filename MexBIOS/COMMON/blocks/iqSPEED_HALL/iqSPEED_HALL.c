
void Init(void)
{
}

void Exec(void)
{
  short Delta;

  Delta = (short)*v->Theta - v->OldTheta;
  if (Delta >  1) Delta -= v->NumSteps;
  if (Delta < -1) Delta += v->NumSteps;
  v->OldTheta = (short)*v->Theta;

  if (v->Timer < v->Timeout)
  {
    v->Timer++;
    if (Delta != 0)
    {
      v->Speed = _IQ24div(60, v->Timer * v->NumSteps);
      v->Speed = _IQ24div(v->Speed, v->SampleTime * v->BaseSpeed);
      if (Delta < 0) v->Speed = -v->Speed;
      v->Timer = 0;
    }
  }
  else
  {
    v->Speed = 0;
    if (Delta != 0) v->Timer = 0;
  }
}



