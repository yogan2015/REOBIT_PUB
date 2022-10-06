
void Init(void)
{
}

void Exec(void)
{
  short i;

  if (!(short)*v->In) { v->Out = 0; return; }

  for (i = 0; i < 32; i++)
  {
    if (*v->In & (1L << i)) { v->Out = i + 1; return; }
  }
}

