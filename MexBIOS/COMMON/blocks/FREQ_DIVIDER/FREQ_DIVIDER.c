
void Init(void)
{
}

void Exec(void)
{
  if (++v->Counter >= *v->In) { v->Out = 1; v->Counter = 0;}
  else v->Out = 0;
}

