
void Init(void)
{

}

void Exec(void)
{
  if (Tf != PrevTf)
  {
    K1 = SampleTime / (Tf + SampleTime);
    K2 = Tf         / (Tf + SampleTime);
    PrevTf  = Tf;
  }

  if ((short)R)
  {
    Out = 0;
    PrevOut = 0;
    return;
  }

  Out = In * K1 + PrevOut * K2;
  PrevOut = Out;
}

