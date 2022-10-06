
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (!(short)*v->RST) {
  v->Out += _IQ24mpy(v->Td, *v->In);
  if (v->Out > *v->lim) v->Out = *v->lim;
  if (v->Out < -(*v->lim)) v->Out = -*v->lim;
  } else {
  v->Out = 0;
  }
}

