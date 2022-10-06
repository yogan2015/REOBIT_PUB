
void Init(void)
{
  v->Buf = (long)&v->Par;
}

void Exec(void)
{
  short i;
  long *Data = (long *)&v->Par;

  for (i=0; i < v->NumOfIn; i++)
    Data[i] = *(&v->In)[i];
}

