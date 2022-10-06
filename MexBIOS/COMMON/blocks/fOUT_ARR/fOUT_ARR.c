
void Init(void)
{
}

void Exec(void)
{
  short i;
  float *Data = (float *)*v->Buf + v->Offset;

  for (i=0; i < v->NumOfOut; i++)
    (&v->Out)[i] = Data[i];
}

