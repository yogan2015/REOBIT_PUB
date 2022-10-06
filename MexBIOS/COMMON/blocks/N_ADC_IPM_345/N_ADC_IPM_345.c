#ifndef ADC_MACROSS
#define ADC_MACROSS

#define IPM0_Iu      0
#define IPM0_Iv      4
#define IPM0_Iw      8
#define IPM0_UDC     32
#define IPM0_T       36

#define IPM3_Iu      12
#define IPM3_Iv      16
#define IPM3_Iw      20
#define IPM3_UDC     24
#define IPM3_T       28

#define AI0          44
#define AI1          40
#define AI2          52
#define AI3          48
#define AI4          60
#define AI5          56

#endif

// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int cIu, cIv, cIw;
 // cIu = _IQ24mpy((((*((int *)(*v->offset + IPM0_Iu)))) << 12)) << 5, v->g_Iu);  // по умолчанию 0.0 соответствует 2048, переводим в IQ24
 // cIu = _IQ24mpy((((*((int *)(*v->offset + IPM0_Iv)))) << 12)) << 5, v->g_Iv);
 // cIu = _IQ24mpy((((*((int *)(*v->offset + IPM0_Iw)))) << 12)) << 5, v->g_Iw);
  switch(v->p_group)
  {
    case 0:
      cIu = _IQ24mpy(((((*((int *)(*v->offset + IPM3_Iu)))) << 12) - 8388607) << 5, v->g_Iu);
      cIv = _IQ24mpy(((((*((int *)(*v->offset + IPM3_Iv)))) << 12) - 8388607) << 5, v->g_Iv);
      cIw = -(cIu + cIv);
      break;
    case 1:
      cIv = _IQ24mpy(((((*((int *)(*v->offset + IPM3_Iv)))) << 12) - 8388607) << 5, v->g_Iv);
      cIw = _IQ24mpy(((((*((int *)(*v->offset + IPM3_Iw)))) << 12) - 8388607) << 5, v->g_Iw);
      cIu = -(cIv + cIw);
      break;
    case 2:
      cIu = _IQ24mpy(((((*((int *)(*v->offset + IPM3_Iu)))) << 12) - 8388607) << 5, v->g_Iu);
      cIw = _IQ24mpy(((((*((int *)(*v->offset + IPM3_Iw)))) << 12) - 8388607) << 5, v->g_Iw);
      cIv = -(cIu + cIw);
      break;
    default:
      break;
  }

  v->Iu_mean = _IQ24mpy(v->Iu_mean, (v->k_ap)) + _IQ24mpy(cIu, 16777216 - v->k_ap);  // считаем среднее
  v->Iv_mean = _IQ24mpy(v->Iv_mean, (v->k_ap)) + _IQ24mpy(cIv, 16777216 - v->k_ap);
  v->Iw_mean = _IQ24mpy(v->Iw_mean, (v->k_ap)) + _IQ24mpy(cIw, 16777216 - v->k_ap);

  // Преобразование Кларк
  v->Ia = _IQ24mpy(33554432 - v->k_ap, cIu) - v->Iu_mean;
  v->Ib  = _IQ24mpy(v->Ia + ((_IQ24mpy(33554432 - v->k_ap, cIv) - v->Iv_mean) << 1), 9686330);

  // Напряжение DC и температура
//  v->U_dc = _IQ8mpy((*((int *)(*v->offset + IPM0_UDC))) - 2048 - v->o_Udc, v->g_Udc);
//  v->T =    _IQ8mpy((*((int *)(*v->offset + IPM0_T))) - 2048 - v->o_T, v->g_T);
  v->U_dc = _IQ24mpy(((((*((int *)(*v->offset + IPM3_UDC)))) << 12) - v->o_Udc) << 5, v->g_Udc);
  v->T    = _IQ24mpy(((((*((int *)(*v->offset + IPM3_T)))) << 12) - v->o_T) << 5, v->g_T);

  // Признаки аварии
  v->WARN_5 = 0;
  if (labs(cIu - v->Iu_mean) >= *v->lim_I_max)
    { v->WARN_5 |= (1 << 0);}
  if (labs(cIv - v->Iv_mean) >= *v->lim_I_max)
    { v->WARN_5 |= (1 << 1);}
  if (labs(cIw - v->Iw_mean) >= *v->lim_I_max)
    { v->WARN_5 |= (1 << 2);}
  if (v->U_dc > *v->lim_UDC_max)
    { v->WARN_5 |= (1 << 3);}
  if (v->U_dc < *v->lim_UDC_min)
    { v->WARN_5 |= (1 << 4);}
}

