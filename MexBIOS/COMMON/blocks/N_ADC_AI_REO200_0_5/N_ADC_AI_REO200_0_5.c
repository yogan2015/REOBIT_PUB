#ifndef ADC_MACROSS
#define ADC_MACROSS



#endif

// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int c_GED_Iu, c_GED_Iv, c_GED_Iw, PSP_Uab, PSP_Ubc, c_PSP_Uu, c_PSP_Uv, c_PSP_Uw;
  //GED
      c_GED_Iu =_IQ24mpy((*v->GED_Iu << 12) - 8388607,v->g_GED_Iu);
      c_GED_Iv =_IQ24mpy((*v->GED_Iv << 12) - 8388607,v->g_GED_Iv);
      c_GED_Iw =_IQ24mpy((*v->GED_Iw << 12) - 8388607,v->g_GED_Iw);
      // считаем среднее
      v->GED_Iu_mean = _IQ24mpy(v->GED_Iu_mean, (v->k_ap)) + _IQ24mpy(c_GED_Iu, 16777216 - v->k_ap);
      v->GED_Iv_mean = _IQ24mpy(v->GED_Iv_mean, (v->k_ap)) + _IQ24mpy(c_GED_Iv, 16777216 - v->k_ap);
      v->GED_Iw_mean = _IQ24mpy(v->GED_Iw_mean, (v->k_ap)) + _IQ24mpy(c_GED_Iw, 16777216 - v->k_ap);

      // Преобразование Кларк
      v->GED_Ia = _IQ24mpy(33554432 - v->k_ap, c_GED_Iu) - v->GED_Iu_mean;
      v->GED_Ib  = _IQ24mpy(v->GED_Ia + ((_IQ24mpy(33554432 - v->k_ap, c_GED_Iv) - v->GED_Iv_mean) << 1), 9686330);


  //PSP_U
      PSP_Uab = _IQ24mpy((*v->PSP_UAB << 12) - 8388607,v->g_PSP_UAB);
      PSP_Ubc = _IQ24mpy((*v->PSP_UBC << 12) - 8388607,v->g_PSP_UBC);

      c_PSP_Uu = __IQmpy ((-5592405), (((PSP_Uab - v->PSP_UAB_mean) << 1) + (PSP_Ubc - v->PSP_UBC_mean)), 24);
      c_PSP_Uv = __IQmpy (5592405   , ((PSP_Uab - v->PSP_UAB_mean) - (PSP_Ubc - v->PSP_UBC_mean))       , 24);
      c_PSP_Uw = __IQmpy (-16777216   , c_PSP_Uu + c_PSP_Uv  , 24);



      // считаем среднее
      v->PSP_UAB_mean = _IQ24mpy(v->PSP_UAB_mean, (v->k_ap)) + _IQ24mpy(PSP_Uab, 16777216 - v->k_ap);
      v->PSP_UBC_mean = _IQ24mpy(v->PSP_UBC_mean, (v->k_ap)) + _IQ24mpy(PSP_Ubc, 16777216 - v->k_ap);

      // преобразования Кларк
      v->PSP_Ua = c_PSP_Uu;
      v->PSP_Ub  = _IQ24mpy(c_PSP_Uu + (c_PSP_Uv << 1), 9686330);

  // Напряжение DC
    v->GED_Udc = _IQ24mpy((*v->GED_UDC << 12) - v->o_GED_Udc, v->g_GED_Udc);

  // Признаки аварии
  v->WARN_AI05 = 0;
  if (v->GED_Udc < *v->UDC_MIN)
    { v->WARN_AI05 |= (1 << 16);}
  if (v->GED_Udc > *v->UDC_MAX)
    { v->WARN_AI05 |= (1 << 17);}
  if (labs(c_PSP_Uu) > *v->PSP_UAC_MAX)
    { v->WARN_AI05 |= (1 << 2);}
  if (labs(c_PSP_Uv) > *v->PSP_UAC_MAX)
    { v->WARN_AI05 |= (1 << 3);}
  if (labs(c_PSP_Uw) > *v->PSP_UAC_MAX)
    { v->WARN_AI05 |= (1 << 4);}
  if (labs(c_GED_Iu - v->GED_Iu_mean) >= *v->GED_IAC_MAX)
    { v->WARN_AI05 |= (1 << 18);}
  if (labs(c_GED_Iv - v->GED_Iv_mean) >= *v->GED_IAC_MAX)
    { v->WARN_AI05 |= (1 << 19);}
  if (labs(c_GED_Iw - v->GED_Iw_mean) >= *v->GED_IAC_MAX)
    { v->WARN_AI05 |= (1 << 20);}
}

