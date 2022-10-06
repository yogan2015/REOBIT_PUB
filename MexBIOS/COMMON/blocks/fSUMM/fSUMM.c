
void Init(void)
{
}

void Exec(void)
{
  short i;
  float Result = 0;

  for (i = 0; i < v->InCnt; i++)
    Result = Result + *(&v->In)[i];

  v->Out = Result;
}

