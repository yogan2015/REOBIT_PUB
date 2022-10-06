
void Init(void)
{
}

void Exec(void)
{
  long Res = 1 << v->Format;
  short i;

  for (i=0; i < v->Degree; i++) Res = __IQmpy(Res, *v->In, v->Format);

  v->Out = Res;
}

