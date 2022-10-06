
void Init(void)
{
}

void Exec(void)
{
  long CurrFreq, Delta;
  long Temp1, Temp2;

  if ((short)*v->R & 0x1) v->Pos = 0;
  if ((short)*v->R & 0x2) return;

  if (!(short)*v->M)
  {
    CurrFreq = *v->Freq;
    Temp1 = 0;
  }
  else
  {
    CurrFreq = 0;
    Temp1 = (*v->Ref - v->Pos);
    if (Temp1 > 0) CurrFreq =  _IQabs(*v->Freq);
    if (Temp1 < 0) CurrFreq = -_IQabs(*v->Freq);
  }

  Delta = _IQ24mpy(v->SampleTime * v->BaseFreq, CurrFreq);
  if ((int)*v->M)
  {
    Temp2 = Delta >> 19;
    if ((Temp1 > 0) && (Temp2 > Temp1)) Delta = Temp1 << 19;
    if ((Temp1 < 0) && (Temp2 < Temp1)) Delta = Temp1 << 19;
  }
  v->CurrAngle = v->CurrAngle + Delta;

  if (v->CurrAngle > _IQ29(1.0)) { v->CurrAngle -= _IQ29(1.0); v->Pos += _IQ10(1.0); }
  if (v->CurrAngle < _IQ29(0.0)) { v->CurrAngle += _IQ29(1.0); v->Pos -= _IQ10(1.0); }

  v->Angle = _IQ24div(_IQ29mpy(v->CurrAngle, *v->Dev), *v->Dev);
  v->Pos   = ((v->Pos >> 10) << 10) + (v->CurrAngle >> 19);
}


