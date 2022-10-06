
void Init(void)
{
}

void Exec(void)
{
  if (!*v->Buf) return;
  if (v->Size) *((long *)(*v->Buf) + v->Offset) = *v->In;
  else *((short *)(*v->Buf) + v->Offset) = (short)*v->In;
}


