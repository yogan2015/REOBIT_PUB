
void Init(void)
{
}

void Exec(void)
{
  v->Angle = v->Angle + _IQ24mpy(_IQ24mpy(v->SampleTime, v->BaseFreq), *v->Freq);

  if (v->Angle >= _IQ24(1.0)) v->Angle = v->Angle - _IQ24(1.0);
  if (v->Angle <  _IQ24(0.0)) v->Angle = v->Angle + _IQ24(1.0);

  v->Out = _IQ24mpy(v->Angle, v->Gain) + v->Offset;
}


