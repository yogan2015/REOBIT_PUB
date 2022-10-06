
void Init(void)
{
}

void Exec(void)
{
  v->DW = ((*v->B3 & 0xFF) << 24) | ((*v->B2 & 0xFF) << 16) | ((*v->B1 & 0xFF) << 8) | (*v->B0 & 0xFF);
}

