
void Init(void)
{
}

void Exec(void)
{
  if (*v->In1 > *v->In2)
    v->Out = *v->In1;
  else
    v->Out = *v->In2;
}

