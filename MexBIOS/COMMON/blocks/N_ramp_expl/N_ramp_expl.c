
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int dV;
  if ((short)*v->RST)
  {
    v->out_V = 0;
    v->p_V = 0;
    v->out_A = 0;
    return;
  } else {
    dV = (*v->ref_V - v->p_V);
    v->out_A = 0;
    if (dV > v->eps)
    {  //  нужно увелиичть скорость
      v->out_A = v->max_A;
    }
    if (dV < -v->eps)
    {  //  нужно уменьшать скорость
      v->out_A = -v->max_A;
    }
  }
  //  применение дельты ускорения
  v->out_V = v->p_V + _IQ24mpy(v->Td, v->out_A);
  if (v->out_V > v->max_V) v->out_V = v->max_V;
  if (v->out_V < (-v->max_V)) v->out_V = -v->max_V;
  v->p_V = v->out_V;
}
