
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  long xn;
  v->y = 0;
  xn = *v->x;
  v->y += _IQ24mpy(xn, v->a1) + v->b;
  xn = _IQ24mpy(xn, *v->x);
  v->y += _IQ24mpy(xn, v->a2);
  xn = _IQ24mpy(xn, *v->x);
  v->y += _IQ24mpy(xn, v->a3);
}

