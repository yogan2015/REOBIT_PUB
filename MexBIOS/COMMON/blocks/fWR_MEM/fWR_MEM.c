
void Init(void)
{
}

void Exec(void)
{
  #ifndef __BORLANDC__
  if (!v->Address) return;
  Eallow();
  *((float *)(v->Address + v->Offset)) = *v->In;
  Edis();
  #endif
}


