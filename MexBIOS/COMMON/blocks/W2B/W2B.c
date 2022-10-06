
void Init(void)
{
}

void Exec(void)
{
  v->B0 = ((unsigned short)*v->W) & 0xFF;
  v->B1 = ((unsigned short)*v->W) >> 8;
}

