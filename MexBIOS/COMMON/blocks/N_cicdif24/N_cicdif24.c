
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out = _IQ24frac(*v->In);
  if (v->Out > (1 << 23))  v->Out -= (1 << 24);
  if (v->Out < -(1 << 23)) v->Out += (1 << 24);

}

