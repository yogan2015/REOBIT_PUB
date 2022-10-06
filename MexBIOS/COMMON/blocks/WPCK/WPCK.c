
void Init(void)
{

}

void Exec(void)
{
  short i;
  long  Res = 0;

  for (i=0; i < v->NumIn; i++)
    if (*(&v->b0)[i]) Res |= (1<<i);

  v->Out = Res;
}

