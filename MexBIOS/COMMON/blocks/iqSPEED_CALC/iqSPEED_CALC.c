
void Init(void)
{
}

void Exec(void)
{
  long Delta;

  if (++v->Counter < v->Period) return;
  v->Counter = 0;

  Delta = *v->Angle - v->PrevAngle;
  if (Delta < _IQ24(-0.5)) Delta += _IQ24(1.0);
  if (Delta > _IQ24( 0.5)) Delta -= _IQ24(1.0);
  v->PrevAngle = *v->Angle;

  v->Speed = _IQ17div(Delta * 60L, _IQ7mpy(v->SampleTime, v->Period * v->BaseSpeed));
}


