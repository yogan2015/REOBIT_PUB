
void Init(void)
{
}

void Exec(void)
{
  #ifndef __BORLANDC__
  long Addr = v->Address + v->Offset;
  if (!Addr) return;
  switch(v->Type)
  {
    case 0: v->Out = *((short          *)Addr); break;
    case 1: v->Out = *((long           *)Addr); break;
    case 2: v->Out = *((unsigned short *)Addr); break;
    case 3: v->Out = *((char           *)Addr); break;
  }
  #endif
}

