
void Init(void)
{
}

void Exec(void)
{
  short i;
  long Result = (1L << v->Format);

  for (i = 0; i < v->InCnt; i++)
    Result = __IQmpy(Result, *(&v->In)[i], v->Format);

  v->Out = Result;
}

