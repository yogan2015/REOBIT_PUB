#ifndef ADC_MACROSS
#define ADC_MACROSS



#endif

// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int c_PSP_Iu, c_PSP_Iv, c_PSP_Iw;
  //PSP
      c_PSP_Iu =_IQ24mpy((*v->PSP_Iu << 12) - 8388607,v->g_PSP_Iu);
      c_PSP_Iv =_IQ24mpy((*v->PSP_Iv << 12) - 8388607,v->g_PSP_Iv);
      c_PSP_Iw =_IQ24mpy((*v->PSP_Iw << 12) - 8388607,v->g_PSP_Iw);
      // считаем среднее
      v->PSP_Iu_mean = _IQ24mpy(v->PSP_Iu_mean, (v->k_ap)) + _IQ24mpy(c_PSP_Iu, 16777216 - v->k_ap);
      v->PSP_Iv_mean = _IQ24mpy(v->PSP_Iv_mean, (v->k_ap)) + _IQ24mpy(c_PSP_Iv, 16777216 - v->k_ap);
      v->PSP_Iw_mean = _IQ24mpy(v->PSP_Iw_mean, (v->k_ap)) + _IQ24mpy(c_PSP_Iw, 16777216 - v->k_ap);

      // Преобразование Кларк
      v->PSP_Ia = _IQ24mpy(33554432 - v->k_ap, c_PSP_Iu) - v->PSP_Iu_mean;
      v->PSP_Ib  = _IQ24mpy(v->PSP_Ia + ((_IQ24mpy(33554432 - v->k_ap, c_PSP_Iv) - v->PSP_Iv_mean) << 1), 9686330);



  // Напряжение DC
    v->PSP_Udc = _IQ24mpy((*v->PSP_UDC << 12) - v->o_PSP_Udc, v->g_PSP_Udc);
  // Ток DC
    v->PSP_Idc = _IQ24mpy((*v->PSP_IDC << 12) - v->o_PSP_Idc, v->g_PSP_Idc);
  // Признаки аварии
  v->WARN_AI610 = 0;
  if (v->PSP_Udc < *v->UDC_MIN)
    { v->WARN_AI610 |= (1 << 0);}
  if (v->PSP_Udc > *v->UDC_MAX)
    { v->WARN_AI610 |= (1 << 1);}
  if (labs(c_PSP_Iu - v->PSP_Iu_mean) >= *v->PSP_IAC_MAX)
    { v->WARN_AI610 |= (1 << 5);}
  if (labs(c_PSP_Iv - v->PSP_Iv_mean) >= *v->PSP_IAC_MAX)
    { v->WARN_AI610 |= (1 << 6);}
  if (labs(c_PSP_Iw - v->PSP_Iw_mean) >= *v->PSP_IAC_MAX)
    { v->WARN_AI610 |= (1 << 7);}
  if (labs(v->PSP_Idc) >= *v->PSP_IDC_MAX)
    { v->WARN_AI610 |= (1 << 8);}
}

