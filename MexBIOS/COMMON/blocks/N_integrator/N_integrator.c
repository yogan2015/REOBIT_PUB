
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{

  if (!(short)(*v->nRST))
  {
    v->pOut = 0;
  } else
  {
    v->pOut += _IQ24mpy(*v->In, v->Td);
    v->pOut = ((v->pOut > *v->lim) ? (*v->lim) : ((-v->pOut > *v->lim) ? (-*v->lim) : (v->pOut)));
  }
  v->Out = v->pOut;
}

