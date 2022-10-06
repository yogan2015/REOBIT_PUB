
void Init(void)
{

}

void Exec(void)
{
  #ifndef __BORLANDC__
  short i, *Data, DataCount;
  long NextAddr;

  if (!(short)*v->En || !*v->Buf) { v->Addr = 0; v->Timer = 0; return; }
  if (v->Timer > 0) { v->Timer--; return; }

  DataCount = v->Count - 2;
  NextAddr = v->Addr + DataCount;
  if (NextAddr > v->BufCount) return;

  Data = &(((short *)(*v->Buf))[v->Addr]);
  for (i = 0; i < DataCount; i++) Data[i] = (short)__IQmpy(*(&v->In1)[i], v->Gain, v->Format);

  v->Addr = NextAddr;
  v->Timer = v->Delay;
  #endif
}


