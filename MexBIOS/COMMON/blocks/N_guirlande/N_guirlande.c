
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if ((short)*v->RST)
  {
    v->old = 0;
    v->OUT = 0;
    return;
  }
  if ((short)*v->CNT)
  {
    if (v->old == 0)
    {
      v->old = 1;
    } else {
      v->old = (v->old + v->old) + 1;
    }
  }
  v->OUT = v->old;
}

