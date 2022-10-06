
void Init(void)
{
}

void Exec(void)
{
  v->DW = (*v->W1 << 16) | (*v->W0 & 0xFFFF);
}

