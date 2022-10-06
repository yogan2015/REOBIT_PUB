
void Init(void)
{
}

void Exec(void)
{
  float Tf1;

  if (Tf != PrevTf)
  {
    Tf1    = Tf / 10;
    K1     = SampleTime / (Tf1 + SampleTime);
    K2     = Tf1        / (Tf1 + SampleTime);
    PrevTf = Tf;
  }

  if ((short)R)
  {
    Out      = 0;
    PrevOut  = 0;
    Out1     = 0;
    PrevOut1 = 0;
    Out2     = 0;
    PrevOut2 = 0;
    return;
  }

  Out1     = In * K1   + PrevOut1 * K2;
  PrevOut1 = Out1;
  Out2     = Out1 * K1 + PrevOut2 * K2;
  PrevOut2 = Out2;
  Out      = Out2 * K1 + PrevOut  * K2;
  PrevOut  = Out;
}


