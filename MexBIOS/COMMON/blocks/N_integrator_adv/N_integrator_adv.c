
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{

  if (!(short)(*v->nRST))
  {
    v->pOut = *v->init;
  } else
  {
    v->pOut += _IQ24mpy(*v->In, v->Td);
    v->pOut = _IQsat(v->pOut, *v->lim_max, *v->lim_min);
  }
  v->Out = v->pOut;
}

