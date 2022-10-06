
void Init(void)
{
}

void Exec(void)
{
  short i, Temp = 1;

  for (i=0; i < v->NumOfIn; i++)
    Temp = Temp && *(&v->In)[i];

  v->Out   = !Temp && v->Out_1;
  v->Out_1 = Temp;
}

