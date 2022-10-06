
void Init(void)
{
}

void Exec(void)
{
  float Result = (*v->In1 - *v->In2) * (*v->In1 + *v->In2);
  if (Result < 0) v->Out = 0;
  else v->Out = sqrt(Result);
}


