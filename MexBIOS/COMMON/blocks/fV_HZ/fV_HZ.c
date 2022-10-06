
void Init(void)
{
}

void Exec(void)
{
  float AbsFreq, VfSlope;

  // Take absolute frequency to allow the operation of both rotational directions
  AbsFreq = fabs(*v->Freq);

  if (AbsFreq <= v->LowFreq)
    // Compute output voltage in profile #1
    v->VoltOut = v->VoltMin;
  else if ((AbsFreq > v->LowFreq) && (AbsFreq <= v->HighFreq))
  {
    // Compute slope of V/f profile
    VfSlope = (v->VoltMax - v->VoltMin) / (v->HighFreq - v->LowFreq);
    // Compute output voltage in profile #2
    v->VoltOut = v->VoltMin + VfSlope * (AbsFreq - v->LowFreq);
  }
  else if ((AbsFreq > v->HighFreq) && (AbsFreq < v->MaxFreq))
    // Compute output voltage in profile #3
    v->VoltOut = v->VoltMax;
}


