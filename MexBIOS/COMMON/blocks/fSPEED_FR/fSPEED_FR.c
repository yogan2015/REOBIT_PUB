
void Init(void)
{
}

void Exec(void)
{
  float Gain;
  long  DeltaLo, DeltaHi, Delta;

  Gain    = (v->SampleTime * v->RevCount) * (1.0/60.0);
  DeltaLo = (long)(Gain * v->MinFreq);
  DeltaHi = (long)(Gain * v->MaxFreq);

  Delta = *v->Pos - v->PosPrev;
  if (labs(Delta - v->DeltaPrev) >= DeltaHi) Delta = v->DeltaPrev;
  if (Delta >  DeltaHi) Delta =  DeltaHi;
  if (Delta < -DeltaHi) Delta = -DeltaHi;

  if (labs(Delta) >= DeltaLo)
  {
    v->Speed     = Delta / (Gain * v->BaseFreq * v->PassIndex);
    v->PosPrev   = *v->Pos;
    v->DeltaPrev = Delta;
    v->PassIndex = 1;
  }
  else if (++v->PassIndex > v->PassCount)
  {
    v->Speed     = 0;
    v->PosPrev   = *v->Pos;
    v->DeltaPrev = 0;
    v->PassIndex = 1;
  }
}


