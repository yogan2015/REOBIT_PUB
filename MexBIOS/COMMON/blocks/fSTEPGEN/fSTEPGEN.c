
void Init(void)
{
}

void Exec(void)
{
  float CurrFreq, Delta;
  float Temp;

  if ((short)*v->R & 0x1) v->Pos = 0;
  if ((short)*v->R & 0x2) return;

  if (!(short)*v->M)
  {
    CurrFreq = *v->Freq;
    Temp = 0;
  }
  else
  {
    CurrFreq = 0;
    Temp = (*v->Ref - v->Pos);
    if (Temp > 0) CurrFreq =  fabs(*v->Freq);
    if (Temp < 0) CurrFreq = -fabs(*v->Freq);
  }

  Delta = v->SampleTime * v->BaseFreq * CurrFreq;
  if ((short)*v->M)
  {
    if ((Temp > 0) && (Delta > Temp)) Delta = Temp;
    if ((Temp < 0) && (Delta < Temp)) Delta = Temp;
  }
  v->CurrAngle = v->CurrAngle + Delta;

  if (v->CurrAngle > 1.0) { v->CurrAngle -= 1.0; v->Pos++; }
  if (v->CurrAngle < 0.0) { v->CurrAngle += 1.0; v->Pos--; }

  v->Angle = (float)((long)(v->CurrAngle * (*v->Dev))) / (*v->Dev);
  v->Pos   = (float)((long)v->Pos) + v->CurrAngle;
}


