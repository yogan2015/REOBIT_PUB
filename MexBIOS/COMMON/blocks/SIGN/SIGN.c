
void Init(void)
{

}

void Exec(void)
{
  if (*v->In < 0) v->Out = -1;
  else if (*v->In > 0) v->Out = 1;
  else v->Out = 0;
}

