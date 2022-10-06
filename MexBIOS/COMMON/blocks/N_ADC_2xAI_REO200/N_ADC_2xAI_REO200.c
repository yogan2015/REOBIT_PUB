#ifndef ADC_MACROSS
#define ADC_MACROSS

//AI(0-5)
#define GED_Iv       0
#define GED_Iu       4
#define GED_Udc      8
#define GED_Iw       12
#define SN_UacBC     16
#define SN_UacAB     20
//AI(6-11)
#define SN_Iv        24
#define SN_Iu        28
#define SN_Udc       32
#define SN_Iw        36
#define SN_Idc       40

#endif

// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int c_GED_Iu, c_GED_Iv, c_GED_Iw, c_SN_Iu, c_SN_Iv, c_SN_Iw, c_SN_Idc, SN_U_AB, SN_U_BC, c_SN_Uu, c_SN_Uv, c_SN_Uw;
  //GED
      c_GED_Iu = _IQ24mpy(((((*((int *)(*v->offset + GED_Iu)))) << 12) - v->o_GED_Iu) << 5, v->g_GED_Iu);
      c_GED_Iv = _IQ24mpy(((((*((int *)(*v->offset + GED_Iv)))) << 12) - v->o_GED_Iv) << 5, v->g_GED_Iv);
      c_GED_Iw = _IQ24mpy(((((*((int *)(*v->offset + GED_Iw)))) << 12) - v->o_GED_Iw) << 5, v->g_GED_Iw);

      // считаем среднее
      v->GED_Iu_mean = _IQ24mpy(v->GED_Iu_mean, (v->GED_k_ap)) + _IQ24mpy(c_GED_Iu, 16777216 - v->GED_k_ap);
      v->GED_Iv_mean = _IQ24mpy(v->GED_Iv_mean, (v->GED_k_ap)) + _IQ24mpy(c_GED_Iv, 16777216 - v->GED_k_ap);
      v->GED_Iw_mean = _IQ24mpy(v->GED_Iw_mean, (v->GED_k_ap)) + _IQ24mpy(c_GED_Iw, 16777216 - v->GED_k_ap);

      // Преобразование Кларк
      v->GED_Ia = _IQ24mpy(33554432 - v->GED_k_ap, c_GED_Iu) - v->GED_Iu_mean;
      v->GED_Ib  = _IQ24mpy(v->GED_Ia + ((_IQ24mpy(33554432 - v->GED_k_ap, c_GED_Iv) - v->GED_Iv_mean) << 1), 9686330);


  //SN_I
      //AC
      c_SN_Iu = _IQ24mpy(((((*((int *)(*v->offset + SN_Iu)))) << 12) - v->o_SN_Iu) << 5, v->g_SN_Iu);
      c_SN_Iv = _IQ24mpy(((((*((int *)(*v->offset + SN_Iv)))) << 12) - v->o_SN_Iv) << 5, v->g_SN_Iv);
      c_SN_Iw = _IQ24mpy(((((*((int *)(*v->offset + SN_Iw)))) << 12) - v->o_SN_Iw) << 5, v->g_SN_Iw);
      //DC
      c_SN_Idc = _IQ24mpy(((((*((int *)(*v->offset + SN_Idc)))) << 12) - v->o_SN_Idc) << 5, v->g_SN_Idc);

      // считаем среднее
      v->SN_Iu_mean = _IQ24mpy(v->SN_Iu_mean, (v->SN_k_ap)) + _IQ24mpy(c_SN_Iu, 16777216 - v->SN_k_ap);
      v->SN_Iv_mean = _IQ24mpy(v->SN_Iv_mean, (v->SN_k_ap)) + _IQ24mpy(c_SN_Iv, 16777216 - v->SN_k_ap);
      v->SN_Iw_mean = _IQ24mpy(v->SN_Iw_mean, (v->SN_k_ap)) + _IQ24mpy(c_SN_Iw, 16777216 - v->SN_k_ap);

      // Преобразование Кларк
      v->SN_Ia = _IQ24mpy(33554432 - v->SN_k_ap, c_SN_Iu) - v->SN_Iu_mean;
      v->SN_Ib  = _IQ24mpy(v->SN_Ia + ((_IQ24mpy(33554432 - v->SN_k_ap, c_SN_Iv) - v->SN_Iv_mean) << 1), 9686330);

  //SN_U
      SN_U_AB = _IQ24mpy(((((*((int *)(*v->offset + SN_UacAB)))) << 12) - v->o_SN_UacAB) << 5, v->g_SN_UacAB);
      SN_U_BC = _IQ24mpy(((((*((int *)(*v->offset + SN_UacBC)))) << 12) - v->o_SN_UacBC) << 5, v->g_SN_UacBC);

      c_SN_Uu = __IQmpy ((-5592405), (((SN_U_AB - v->SN_UacAB_mean) << 1) + (SN_U_BC - v->SN_UacBC_mean)), 24);
      c_SN_Uv = __IQmpy (5592405   , ((SN_U_AB - v->SN_UacAB_mean) - (SN_U_BC - v->SN_UacBC_mean))       , 24);
      c_SN_Uw = __IQmpy (5592405   , ((SN_U_AB - v->SN_UacAB_mean) + (SN_U_BC - v->SN_UacBC_mean) << 1)  , 24);

      // считаем среднее
      v->SN_UacAB_mean = _IQ24mpy(v->SN_UacAB_mean, (v->SN_k_ap)) + _IQ24mpy(SN_U_AB, 16777216 - v->SN_k_ap);
      v->SN_UacBC_mean = _IQ24mpy(v->SN_UacBC_mean, (v->SN_k_ap)) + _IQ24mpy(SN_U_BC, 16777216 - v->SN_k_ap);

      // преобразования Кларк
      v->SN_Ua = c_SN_Uu;
      v->SN_Ub  = _IQ24mpy(c_SN_Uu + (c_SN_Uv << 1), 9686330);

  // Напряжение DC
    v->Udc = _IQ24mpy(((((*((int *)(*v->offset + GED_Udc)))) << 12) - v->o_GED_Udc) << 5, v->g_GED_Udc);

  // Признаки аварии
  v->WARN = 0;
  if (v->Udc < *v->UDC_MIN)
    { v->WARN |= (1 << 0);}
  if (v->Udc > *v->UDC_MIN)
    { v->WARN |= (1 << 1);}
  if (labs(c_SN_Uu) >= *v->UAC_PSP_MAX)
    { v->WARN |= (1 << 2);}
  if (labs(c_SN_Uv) >= *v->UAC_PSP_MAX)
    { v->WARN |= (1 << 3);}
  if (labs(c_SN_Uw) >= *v->UAC_PSP_MAX)
    { v->WARN |= (1 << 4);}

  if (labs(c_SN_Idc) >= *v->IDC_PSP_MAX)
    { v->WARN |= (1 << 5);}

  if (labs(c_SN_Iu - v->SN_Iu_mean) >= *v->IAC_PSP_MAX)
    { v->WARN |= (1 << 6);}
  if (labs(c_SN_Iv - v->SN_Iv_mean) >= *v->IAC_PSP_MAX)
    { v->WARN |= (1 << 7);}
  if (labs(c_SN_Iw - v->SN_Iw_mean) >= *v->IAC_PSP_MAX)
    { v->WARN |= (1 << 8);}
  if (labs(c_GED_Iu - v->GED_Iu_mean) >= *v->IAC_GED_MAX)
    { v->WARN |= (1 << 9);}
  if (labs(c_GED_Iv - v->GED_Iv_mean) >= *v->IAC_GED_MAX)
    { v->WARN |= (1 << 10);}
  if (labs(c_GED_Iw - v->GED_Iw_mean) >= *v->IAC_GED_MAX)
    { v->WARN |= (1 << 11);}
}

