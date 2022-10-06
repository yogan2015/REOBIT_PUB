
void Init(void)
{
}

void Exec(void)
{
  if (*v->In >= v->Level_ON)  v->Out = 1;
  if (*v->In <= v->Level_OFF) v->Out = 0;
}

