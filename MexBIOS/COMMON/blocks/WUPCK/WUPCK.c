
void Init(void)
{

}

void Exec(void)
{
  short i;

  for(i=0; i < v->NumOut; i++)
    (&v->b0)[i] = (*v->In & (1<<i)) != 0;
}

