
void Init(void)
{
}

void Exec(void)
{
  if (!*v->Buf) return;
  switch(v->Size)
  {
    case 0: v->Out = *((short *)(*v->Buf) + v->Offset);          break;
    case 1: v->Out = *((long *)(*v->Buf) + v->Offset);           break;
    case 2: v->Out = *((unsigned short *)(*v->Buf) + v->Offset); break;
  }
}

