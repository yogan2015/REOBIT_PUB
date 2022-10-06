
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
      v->Speed = 60.0 / (v->SampleTime * v->NumSteps * v->Timer * v->BaseSpeed);
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

