
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int cUu, cUv;  // фазные составл€ющие

  cUu = *v->U_A - v->UA_mean;  // фазные составл€ющие
  cUv = *v->U_B - v->UB_mean;

  v->UA_mean = _IQ24mpy(v->UA_mean, (v->k_ap)) + _IQ24mpy(*v->U_A, 16777216 - v->k_ap);  // считаем среднее
  v->UB_mean = _IQ24mpy(v->UB_mean, (v->k_ap)) + _IQ24mpy(*v->U_B, 16777216 - v->k_ap);

  v->Ua = cUu;                                        // преобразовани€  ларк
  v->Ub  = _IQ24mpy(cUu + (cUv << 1), 9686330);

  v->WARN_3 = 0;
  if (labs(cUu) >= *v->lim_UAC)
    { v->WARN_3 |= (1 << 0);}
  if (labs(cUv) >= *v->lim_UAC)
    { v->WARN_3 |= (1 << 1);}
  if (labs(cUu + cUv) >= *v->lim_UAC)
    { v->WARN_3 |= (1 << 2);}

}

