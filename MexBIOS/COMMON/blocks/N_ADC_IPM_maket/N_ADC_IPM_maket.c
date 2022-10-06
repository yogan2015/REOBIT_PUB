#ifndef ADC_MACROSS
#define ADC_MACROSS

#define IPM0_Iu      0
#define IPM0_Iv      4
#define IPM0_Iw      8
#define IPM0_UDC     36
#define IPM0_T       32

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
  cIu = _IQ24mpy(((*v->raw_Iu << 12) - 8388607) << 5, v->g_Iu);
  cIv = _IQ24mpy(((*v->raw_Iv << 12) - 8388607) << 5, v->g_Iv);
  cIw = _IQ24mpy(((*v->raw_Iw << 12) - 8388607) << 5, v->g_Iw);
  //v->Iu = _IQ24mpy(33554432 - v->k_ap, cIu) - v->Iu_mean;  // среднее из предыдущего шага в соотв. с формулой
  //v->Iv = _IQ24mpy(33554432 - v->k_ap, cIv) - v->Iv_mean;
  //v->Iw = _IQ24mpy(33554432 - v->k_ap, cIw) - v->Iw_mean;
  v->Iu_mean = _IQ24mpy(v->Iu_mean, (v->k_ap)) + _IQ24mpy(cIu, 16777216 - v->k_ap);  // считаем среднее
  v->Iv_mean = _IQ24mpy(v->Iv_mean, (v->k_ap)) + _IQ24mpy(cIv, 16777216 - v->k_ap);
  v->Iw_mean = _IQ24mpy(v->Iw_mean, (v->k_ap)) + _IQ24mpy(cIw, 16777216 - v->k_ap);

  // Преобразование Кларк
  v->Ia = _IQ24mpy(33554432 - v->k_ap, cIu) - v->Iu_mean;
  v->Ib  = _IQ24mpy(v->Ia + ((_IQ24mpy(33554432 - v->k_ap, cIv) - v->Iv_mean) << 1), 9686330);

  // Напряжение DC и температура
  v->U_dc = _IQ8mpy((*v->raw_Udc) - 2048 - v->o_Udc, v->g_Udc);
  v->T =    _IQ8mpy((*v->raw_T) - 2048 - v->o_T, v->g_T);
  // Признаки аварии
  v->WARN = 0;
  if (labs(v->Ia) >= *v->lim_I_max)
    { v->WARN |= (1 << 0);}
  if (labs(v->Ib) >= *v->lim_I_max)
    { v->WARN |= (1 << 1);}
  if (labs(v->Ia - v->Ib) >= *v->lim_I_max)
    { v->WARN |= (1 << 2);}
  if (v->U_dc > *v->lim_UDC_max)
    { v->WARN |= (1 << 3);}
  if (v->U_dc < *v->lim_UDC_min)
    { v->WARN |= (1 << 4);}
}

