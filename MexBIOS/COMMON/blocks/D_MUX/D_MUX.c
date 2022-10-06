
void Init(void)
{

}

void Exec(void)
{
  short i, Index = (short)*v->Sel;
  for (i = 0; i < v->NumOut; i++)
  {
    if (i == Index) (&v->Out0)[i] = *v->In;
    else (&v->Out0)[i] = 0;
  }
}

