
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int mS, mV;
  mV = _IQ24mpy(*v->A_a, *v->B_a) + _IQ24mpy(*v->A_b, *v->B_b);
  v->Out_s = _IQ24mpy(*v->A_a, *v->B_b) - _IQ24mpy(*v->A_b, *v->B_a);
  if (mV < 0)
  {
    if (v->Out_s < 0)
      { v->Out_s = -16777216; }
    else
      { v->Out_s = 16777216;  }
  }

}

