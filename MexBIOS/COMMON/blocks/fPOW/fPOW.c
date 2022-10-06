
void Init(void)
{
}

void Exec(void)
{
  float Res = 1;
  short i;

  for (i=0; i < v->Degree; i++) Res = Res * *v->In;

  v->Out = Res;
}

