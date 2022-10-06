
void Init(void)
{

}

void Exec(void)
{
  if (!*v->En) v->Out = 0;
  else v->Out = *v->In;
}

