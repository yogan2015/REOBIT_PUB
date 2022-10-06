
void Init(void)
{
}

void Exec(void)
{
  if (In > Out) Out = In;
  else if (In < Out)
  {
    if (++DelayCount >= DelayMax)
    {
      Out--;
      if (Out < OutMin) Out = OutMin;
      DelayCount = 0;
    }
  }
}

