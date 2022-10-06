
void Init(void)
{
}

void Exec(void)
{
  v->B0 = (*v->DW >> 0)  & 0xFF;
  v->B1 = (*v->DW >> 8)  & 0xFF;
  v->B2 = (*v->DW >> 16) & 0xFF;
  v->B3 = (*v->DW >> 24) & 0xFF;
}

