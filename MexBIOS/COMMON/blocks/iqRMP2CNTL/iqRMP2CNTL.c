
void Init(void)
{
}

void Exec(void)
{
  if (Out != In)
  {
    if (++DelayCount >= DelayMax)
    {
      if (Out < In)
      {
        Out++;
        if (Out > OutMax) Out = OutMax;
      }
      else
      {
        Out--;
        if (Out < OutMin) Out = OutMin;
      }
      DelayCount = 0;
    }
  }
}

