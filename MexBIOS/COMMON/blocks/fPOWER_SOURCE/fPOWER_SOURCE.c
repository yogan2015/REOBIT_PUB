
void Init(void)
{

}

void Exec(void)
{
  float Time;

  v->Angle = v->Angle + (v->SampleTime * v->Freq);
  if (v->Angle >= 1.0) v->Angle = v->Angle - 1.0;
  if (v->Angle <  0.0) v->Angle = v->Angle + 1.0;

  Time = 2*M_PI * v->Angle;

  v->Ua = v->Ampl * sin(Time);
  v->Ub = v->Ampl * sin(Time - 2*M_PI/3);
  v->Uc = v->Ampl * sin(Time + 2*M_PI/3);

  v->Ualpha = v->Ampl * sin(Time);
  v->Ubeta  = v->Ampl * sin(Time - M_PI/2);
}

