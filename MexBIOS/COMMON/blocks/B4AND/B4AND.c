
void Init(void)
{
}

void Exec(void)
{
  short i;

  v->Out = 0xFFFFFFFF;
  for (i=0; i < v->NumOfIn; i++)
    v->Out = v->Out & *(&v->In)[i];
}

