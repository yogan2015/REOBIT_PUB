
void Init(void)
{
}


void Exec(void)
{
  if (*v->In != v->Prev)
    MBS_setData(v->Index, *v->In, 1);

  v->Prev = *v->In;
}

