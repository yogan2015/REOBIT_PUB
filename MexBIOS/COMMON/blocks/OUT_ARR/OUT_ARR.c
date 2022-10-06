
void Init(void)
{
}

void Exec(void)
{
  short i;
  long *Data = (long *)*v->Buf + v->Offset;

  for (i=0; i < v->NumOfOut; i++)
    (&v->Out)[i] = Data[i];
}

