
void Init(void)
{
}

void Exec(void)
{
  v->Out = ((unsigned long)*v->In << 16) | ((unsigned long)*v->In >> 16);
}

