
void Init(void)
{
}

void Exec(void)
{
  long Delta;

  if (++v->Counter < v->Period) return;
  v->Counter = 0;

  Delta =v->PrevPrevAngle - (v->PrevAngle<<1) + *v->Angle;
  if (Delta < _IQ24(-0.5)) Delta += _IQ24(1.0);
  if (Delta > _IQ24( 0.5)) Delta -= _IQ24(1.0);

  v->PrevPrevAngle = v->PrevAngle;
  v->PrevAngle = *v->Angle;
  v->Acc = _IQ17div(Delta * 60L, _IQ7mpy(v->SampleTime, v->Period * v->BaseSpeed));
}


