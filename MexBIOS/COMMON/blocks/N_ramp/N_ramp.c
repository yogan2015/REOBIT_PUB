
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if ((short)*v->RST)
  {
    v->Out = 0;
    v->pOut = 0;
    v->V = 0;
    return;
  } else {
    if (v->pOut < *v->In)     v->V += _IQ24mpy(v->Amax,  v->Td);
    if (v->pOut > *v->In)     v->V -= _IQ24mpy(v->Amax,  v->Td);
    if (v->V > v->Vmax)       v->V =  v->Vmax;
    if ((0 - v->V) > v->Vmax) v->V =  -v->Vmax;
    v->Out = v->pOut + _IQ24mpy(v->V, v->Td);
    if ((v->pOut <= *v->In) == (v->Out >= *v->In))
    {
      v->fin = 1;
      v->V = 0;
      v->Out = *v->In;
    } else
    {
      v->fin = 0;
    }
  }
  v->pOut = v->Out;
}

