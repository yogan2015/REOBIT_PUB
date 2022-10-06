
void Init(void)
{
  v->Out = v->Offset;
}

void Exec(void)
{
  float AngleVal;

  if ((short)*v->Reset)
  {
    v->Timer = 0;
    AngleVal = 0;
  }
  else
  {
    v->Timer = v->Timer + (*v->Freq * v->SampleTime);
    if (v->Timer >= 1.0) v->Timer -= 1.0;

    AngleVal = *v->Angle + v->Timer;
    if (AngleVal <  0.0) AngleVal += 1.0;
    if (AngleVal >= 1.0) AngleVal -= 1.0;
  }

  v->Out = v->Offset + *v->Ampl * sin(2*M_PI * AngleVal);
}

