
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if ((short)*v->RST)
  {
    v->range = 0;
    v->low = *v->In;
    v->high = *v->In;
  } else
  {
    if (*v->In < v->low)  v->low  = *v->In;
    if (*v->In > v->high) v->high = *v->In;
    v->range = v->high - v->low;
  }
}

