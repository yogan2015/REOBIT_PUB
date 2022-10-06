
void Init(void)
{
}

void Exec(void)
{
  float Delta;

  if (++v->Counter < v->Period) return;
  v->Counter = 0;

  Delta = *v->Angle - v->PrevAngle;
  if (Delta < -0.5) Delta += 1.0;
  if (Delta >  0.5) Delta -= 1.0;
  v->PrevAngle = *v->Angle;

  v->Speed = (Delta * 60.0) / (v->SampleTime * v->Period * v->BaseSpeed);
}


