
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int cUu, cUv, cUw;  // фазные составл€ющие

  cUu = __IQmpy ((-5592405), (((*v->U_AB - v->UAB_mean) << 1) + (*v->U_BC - v->UBC_mean)), 24);  // фазные составл€ющие
  cUv = __IQmpy (5592405   , ((*v->U_AB - v->UAB_mean) - (*v->U_BC - v->UBC_mean))       , 24);
  cUw = __IQmpy (-16777216, cUu + cUv, 24);

  v->UAB_mean = _IQ24mpy(v->UAB_mean, (v->k_ap)) + _IQ24mpy(*v->U_AB, 16777216 - v->k_ap);  // считаем среднее
  v->UBC_mean = _IQ24mpy(v->UBC_mean, (v->k_ap)) + _IQ24mpy(*v->U_BC, 16777216 - v->k_ap);

  v->Ua = cUu;                                        // преобразовани€  ларк
  v->Ub  = _IQ24mpy(cUu + (cUv << 1), 9686330);

  v->WARN_3 = 0;
  if (labs(cUu) >= *v->lim_UAC)
    { v->WARN_3 |= (1 << 0);}
  if (labs(cUv) >= *v->lim_UAC)
    { v->WARN_3 |= (1 << 1);}
  if (labs(cUw) >= *v->lim_UAC)
    { v->WARN_3 |= (1 << 2);}

}

