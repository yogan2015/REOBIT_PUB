
void Init(void)
{
}

void Exec(void)
{
  long Gain, DeltaLo, DeltaHi, Delta;

  Gain    = _IQ24mpy(v->RevCount * v->SampleTime, _IQ17(1.0/60));
  DeltaLo = _IQ17mpy(v->MinFreq, Gain);
  DeltaHi = _IQ17mpy(v->MaxFreq, Gain);

  Delta = *v->Pos - v->PosPrev;
  if (labs(Delta - v->DeltaPrev) >= DeltaHi) Delta = v->DeltaPrev;
  if (Delta >  DeltaHi) Delta =  DeltaHi;
  if (Delta < -DeltaHi) Delta = -DeltaHi;

  if(labs(Delta) >= DeltaLo)
  {
    Gain         = _IQ17mpy(v->BaseFreq * v->PassIndex, Gain);
    v->Speed     = _IQ24div(Delta, Gain);
    v->PosPrev   = *v->Pos;
    v->DeltaPrev = Delta;
    v->PassIndex = 1;
  }
  else if (++v->PassIndex > v->PassCount) {
    v->Speed     = 0;
    v->PosPrev   = *v->Pos;
    v->DeltaPrev = 0;
    v->PassIndex = 1;
  }
}


