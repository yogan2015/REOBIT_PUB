
void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->S) v->Out |= *v->S;
  if ((short)*v->R) v->Out  = 0;
}

