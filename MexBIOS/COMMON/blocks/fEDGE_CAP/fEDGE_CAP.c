
void Init(void)
{
}

void Exec(void)
{
  v->Out = 0;
  switch(v->Mode)
  {
    case 1: if (*v->In  > v->Prev) v->Out = 1; break;
    case 2: if (*v->In  < v->Prev) v->Out = 1; break;
    case 3: if (*v->In != v->Prev) v->Out = 1; break;
  }
  v->Prev = *v->In;
}



