
void Init(void)
{
  v->Out = v->Offset;
}

void Exec(void)
{
  long AngleVal;

  if ((short)*v->Reset)
  {
    v->Timer = 0;
    AngleVal = 0;
  }
  else
  {
    v->Timer = v->Timer + _IQ24mpy(*v->Freq, v->SampleTime);
    if (v->Timer >= _IQ24(1.0)) v->Timer -= _IQ24(1.0);

    AngleVal = *v->Angle + v->Timer;
    if (AngleVal <  _IQ24(0.0)) AngleVal += _IQ24(1.0);
    if (AngleVal >= _IQ24(1.0)) AngleVal -= _IQ24(1.0);
  }

  v->Out = v->Offset + _IQ24mpy(*v->Ampl, _IQ24sinPU(AngleVal));
}


