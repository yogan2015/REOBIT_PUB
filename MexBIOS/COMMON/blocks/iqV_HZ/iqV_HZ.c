
void Init(void)
{
}

void Exec(void)
{
  long AbsFreq, VfSlope;

  // Take absolute frequency to allow the operation of both rotational directions
  AbsFreq = _IQabs(*v->Freq);

  if (AbsFreq <= v->LowFreq)
    // Compute output voltage in profile #1
    v->VoltOut = v->VoltMin;
  else if ((AbsFreq > v->LowFreq) && (AbsFreq <= v->HighFreq))
  {
    // Compute slope of V/f profile
    VfSlope = _IQ24div(v->VoltMax - v->VoltMin, v->HighFreq - v->LowFreq);
    // Compute output voltage in profile #2
    v->VoltOut = v->VoltMin + _IQ24mpy(VfSlope, AbsFreq - v->LowFreq);
  }
  else if ((AbsFreq > v->HighFreq) && (AbsFreq < v->MaxFreq))
    // Compute output voltage in profile #3
    v->VoltOut = v->VoltMax;
}


