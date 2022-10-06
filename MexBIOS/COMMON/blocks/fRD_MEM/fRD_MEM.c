
void Init(void)
{
}

void Exec(void)
{
  #ifndef __BORLANDC__
  if (!v->Address) return;
  v->Out = *((float *)(v->Address + v->Offset));
  #endif
}

