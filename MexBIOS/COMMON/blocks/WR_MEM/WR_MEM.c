
void Init(void)
{
}

void Exec(void)
{
  #ifndef __BORLANDC__
  long Addr = v->Address + v->Offset;
  if (!Addr) return;
  Eallow();
  switch(v->Type)
  {
    case 0: *((short          *)Addr) = (short         )*v->In; break;
    case 1: *((long           *)Addr) = (long          )*v->In; break;
    case 2: *((unsigned short *)Addr) = (unsigned short)*v->In; break;
    case 3: *((char           *)Addr) = (char          )*v->In; break;
  }
  Edis();
  #endif
}


