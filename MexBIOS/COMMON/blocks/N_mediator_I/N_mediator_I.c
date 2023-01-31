
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (!(short)*v->RST)
  {
    v->Cnt = ((v->Cnt == 0) ? (0) : (v->Cnt - 1));
    if ((short)v->Cnt)
    {
      v->medium += *v->In;
    }
    else
    {
      v->Out = v->medium >> 10;
    }
  }
  else
  {
    v->Cnt = v->frame;
    v->medium = *v->In;
  }
}

