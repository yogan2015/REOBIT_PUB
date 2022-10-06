
void Init(void)
{

}

void Exec(void)
{
  unsigned short N = (unsigned short)*v->In;
  if (N > 31) { v->Out = 0; return; }
  v->Out = 1 << N;
}

