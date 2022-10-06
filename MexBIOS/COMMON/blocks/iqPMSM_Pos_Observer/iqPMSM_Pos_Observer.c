
#define sqrt2 1.4142135623730950488016887242097
#define sqrt3 1.7320508075688772935274463415059
#define _2pi 6.283185307179586476925286766559
#define _45deg 0.875
#define _2_24 16777216


// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Rs_PU = _IQtoIQ(_IQ20div(_IQ20mpy(_IQ20mpy(*v->Inom, _IQ20(sqrt2)), *v->Rs >> 1), _IQ20div(*v->Udc, _IQ20(sqrt3))), 20, 24);
  v->Tf = _IQ24div(_IQ19(1.0), _IQ24mpy(_IQ24mpy(_IQsat(labs(*v->W), v->W_Max, v->W_Min), *v->fnom >> 1), _IQ24(_2pi)));
  v->Tf_out = v->Tf;

  if(v->Tf != v->PrevTf)
  {
    v->K1 = _IQ24div(v->SampleTime, v->Tf + v->SampleTime);
    v->K2 = _IQ24div(v->Tf, v->Tf + v->SampleTime);
    v->PrevTf = v->Tf;
  }

  if(*v->Enable_L)
  {
    v->Flux_a1_Filtered = 0;
    v->Flux_a1_Prev = 0;
    v->Flux_b1_Filtered = 0;
    v->Flux_b1_Prev = 0;
  }
  else
  {
   //Расчет потокосцепления статора через НЧ фильтр, как замена интегратору
    v->Flux_a1_Filtered = _IQ24mpy(_IQ24mpy(*v->U_Alfa - _IQ24mpy(*v->I_Alfa, v->Rs_PU), v->Tf), v->K1) + _IQ24mpy(v->Flux_a1_Prev, v->K2);
    v->Flux_a1_Prev = v->Flux_a1_Filtered;
    v->Flux_b1_Filtered = _IQ24mpy(_IQ24mpy(*v->U_Betta - _IQ24mpy(*v->I_Betta, v->Rs_PU), v->Tf), v->K1) + _IQ24mpy(v->Flux_b1_Prev, v->K2);
    v->Flux_b1_Prev = v->Flux_b1_Filtered;
  }
  //Компенсация фазового сдвига -45
  v->Flux_a1 = _IQ24mpy(_IQ24cosPU((_IQ24atan2PU(v->Flux_b1_Filtered, v->Flux_a1_Filtered) + _IQ24(_45deg)) % _2_24), _IQ24mag(v->Flux_a1_Filtered, v->Flux_b1_Filtered));
  v->Flux_b1 = _IQ24mpy(_IQ24sinPU((_IQ24atan2PU(v->Flux_b1_Filtered, v->Flux_a1_Filtered) + _IQ24(_45deg)) % _2_24), _IQ24mag(v->Flux_a1_Filtered, v->Flux_b1_Filtered));
  v->Flux_a1_out = v->Flux_a1;
  v->Flux_b1_out = v->Flux_b1;
//Перевод индуктивности в о.е.
  v->Ls = _IQtoIQ(_IQ20mpy((*v->Ld + *v->Lq) >> 1, _IQ20div(_IQ20mpy(*v->Inom, _IQ20(sqrt2)), _IQ20div(*v->Udc, _IQ20(sqrt3)))), 20, 24);
  v->Ls_Delta = _IQtoIQ(_IQ20mpy((*v->Ld - *v->Lq) >> 1, _IQ20div(_IQ20mpy(*v->Inom, _IQ20(sqrt2)), _IQ20div(*v->Udc, _IQ20(sqrt3)))), 20, 24);
 //Расчет потокосцелпения статора от углового положения
  v->Lsa = v->Ls + _IQ24mpy(v->Ls_Delta, _IQ24cosPU(v->thetta_est << 1));
  v->Lsb = v->Ls - _IQ24mpy(v->Ls_Delta, _IQ24cosPU(v->thetta_est << 1));
  v->Lm = _IQ24mpy(v->Ls_Delta, _IQ24sinPU(v->thetta_est << 1));

  v->Flux_a2 = _IQ24mpy(*v->I_Alfa, v->Lsa) + _IQ24mpy(*v->I_Betta, v->Lm);
  v->Flux_b2 = _IQ24mpy(*v->I_Betta, v->Lsb) + _IQ24mpy(*v->I_Alfa, v->Lm);

  //Расчет положения
  if(*v->Enable_L)
  {
    v->thetta_est = 0;
  }
  else
  {
    v->thetta_est = _IQ24atan2PU((v->Flux_b1 - v->Flux_b2), (v->Flux_a1 - v->Flux_a2)) % _2_24;
  }
  //Расчет скорости
  //v->w_est = _IQ22div(((v->Flux_a2_Prev >> 13)*((v->Flux_b1 - v->Flux_b2) >> 13) - ((v->Flux_a1 - v->Flux_a2) >> 13)*(v->Flux_b2_Prev >> 13)), _IQsat(((v->Flux_a2 >> 13)*(v->Flux_a2 >> 13) + (v->Flux_b2 >> 13)*(v->Flux_b2 >> 13)), 4194304, 1));

  v->Flux_a2_Prev = v->Flux_a1 - v->Flux_a2;
  v->Flux_b2_Prev = v->Flux_b1 - v->Flux_b2;
  v->Flux_a2_out = v->Flux_a2;
  v->Flux_b2_out = v->Flux_b2;

}
