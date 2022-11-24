
void Init(void)
{
}

void Exec(void)
{
  v->Angle = v->Angle + (v->SampleTime * v->BaseFreq * (*v->Freq));

  if (v->Angle >= 1.0) v->Angle = v->Angle - 1.0;
  if (v->Angle <  0.0) v->Angle = v->Angle + 1.0;

  v->Out = (v->Angle * v->Gain) + v->Offset;
}


