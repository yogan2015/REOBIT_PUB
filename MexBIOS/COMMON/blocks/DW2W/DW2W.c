
void Init(void)
{
}

void Exec(void)
{
  v->W0 = *v->DW & 0xFFFF; if (!v->Signed) v->W0 = (unsigned short)v->W0;
  v->W1 = (*v->DW >> 16) & 0xFFFF;
}

