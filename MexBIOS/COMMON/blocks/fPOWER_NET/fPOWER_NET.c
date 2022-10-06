
static float GetAngleValue(float Ang, short Ng, float Offs);

void Init(void)
{

}

void Exec(void)
{
  float Input, U1 = 0, U2 = 0, U3 = 0;
  short i;

  v->Angle = v->Angle + (v->SampleTime * v->BaseFreq * *v->Freq);
  if (v->Angle >= 1.0) v->Angle = v->Angle - 1.0;
  if (v->Angle <  0.0) v->Angle = v->Angle + 1.0;

  for (i = 1; i < v->Count-1; i++)
  {
    Input = *v->Ampl * *(&v->G1)[i-1];
    U1 = U1 + Input * GetAngleValue(v->Angle, i, 0);
    U2 = U2 + Input * GetAngleValue(v->Angle, i, -1.0/3.0);
    U3 = U3 + Input * GetAngleValue(v->Angle, i, +1.0/3.0);
  }

  v->Ua = U1;
  v->Ub = U2;
  v->Uc = U3;
}

static float GetAngleValue(float Ang, short Ng, float Offs)
{
  Ang = (Ang + Offs) * Ng;
  while(Ang >= 1.0) Ang = Ang - 1.0;
  while(Ang <  0.0) Ang = Ang + 1.0;
  return sin(Ang * 2*M_PI);
}







