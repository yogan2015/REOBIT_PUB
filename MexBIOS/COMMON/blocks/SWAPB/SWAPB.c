
void Init(void)
{
}

void Exec(void)
{
  v->Out = (unsigned short)(*v->In << 8) | ((unsigned short)*v->In >> 8);
}

