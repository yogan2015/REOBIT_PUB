
void Init(void)
{
}

void Exec(void)
{
  if ( (*v->In1 - *v->In2) >= v->Level_ON)  v->Out = 1;
  if ( (*v->In1 - *v->In2) <= v->Level_OFF) v->Out = 0;
}

