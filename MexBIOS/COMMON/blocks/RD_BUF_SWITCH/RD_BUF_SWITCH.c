
void Init(void)
{
}

void Exec(void)
{
  if (!*v->Buf||(*v->Sel<0)) return;
  switch(v->Size)
  {
    case 0: v->Out = *((short *)(*v->Buf) + v->Offset + *v->Sel);          break;
    case 1: v->Out = *((long *)(*v->Buf) + v->Offset + *v->Sel);           break;
    case 2: v->Out = *((unsigned short *)(*v->Buf) + v->Offset + *v->Sel); break;
  }
}

