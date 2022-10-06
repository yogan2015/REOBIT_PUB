
void Init(void)
{
}

void Exec(void)
{
  v->W = (((unsigned short)*v->B1 & 0xFF) << 8) | ((unsigned short)*v->B0 & 0xFF);
  if (v->Signed) v->W = (short)v->W;
}

