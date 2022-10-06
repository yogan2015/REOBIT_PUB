
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->out_G = _IQ24div(((*v->A2_INT - *v->A1_INT) << 12), (*v->A2_24 - *v->A1_24));
  v->out_OFF = (*v->A1_INT << 12) - _IQ24mpy(v->out_G, *v->A1_24);
  v->TEST_OUT = _IQ24mpy(((*v->TEST_IN << 12) - v->out_OFF) << 5, v->out_G);
}

