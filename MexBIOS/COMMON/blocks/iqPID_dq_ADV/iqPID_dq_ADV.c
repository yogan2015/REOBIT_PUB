
void Init(void)
{
}

void Exec(void)
{
  long Up1_d, Ud_d, Out1_d;
  long Up1_q, Ud_q, Out1_q;

  long U_dc_Calc, Kp_d_Calc, Kp_q_Calc;

  long Max_d, Min_d, Max_q, Min_q;
  long Result;

  if ((short)*v->R)
  {
    v->Out_d    = 0;
    v->Up_d     = 0;
    v->Ui_d     = 0;
    v->SatErr_d = 0;
    v->Out_q    = 0;
    v->Up_q     = 0;
    v->Ui_q     = 0;
    v->SatErr_q = 0;
    return;
  }

  U_dc_Calc = _IQtoIQ(_IQ11div(*v->U_dc_Base, *v->U_dc), 11, 24);

  Kp_d_Calc = _IQ24mpy(v->Kp_d, U_dc_Calc);
  Kp_q_Calc = _IQ24mpy(v->Kp_q, U_dc_Calc);


  Up1_d       = _IQ24mpy(Kp_d_Calc, *v->Ref_d - *v->Fdb_d);
  v->Ui_d     = v->Ui_d + _IQ24mpy(v->Ki_d, Up1_d) + _IQ24mpy(v->Kc_d, v->SatErr_d);
  Ud_d        = _IQ24mpy(v->Kd_d, Up1_d - v->Up_d);
  Out1_d      = Up1_d + v->Ui_d + Ud_d;
  Max_d     = v->Max_Out;
  Min_d     = -v->Max_Out;
  v->Out_d    = _IQsat(Out1_d, Max_d, Min_d);
  v->SatErr_d = v->Out_d - Out1_d;
  v->Up_d     = Up1_d;

  Result = _IQ24mpy(v->Max_Out - v->Out_d, v->Max_Out + v->Out_d);

  if (Result < 0)
  {
    Result = 0;
  }
  else
  {
    Result = _IQ24sqrt(Result);
  }

  Up1_q       = _IQ24mpy(Kp_q_Calc, *v->Ref_q - *v->Fdb_q);
  v->Ui_q     = v->Ui_q + _IQ24mpy(v->Ki_q, Up1_q) + _IQ24mpy(v->Kc_q, v->SatErr_q);
  Ud_q        = _IQ24mpy(v->Kd_q, Up1_q - v->Up_q);
  Out1_q      = Up1_q + v->Ui_q + Ud_q;
  Max_q     = Result;
  Min_q     = -Result;
  v->Out_q    = _IQsat(Out1_q, Max_q, Min_q);
  v->SatErr_q = v->Out_q - Out1_q;
  v->Up_q    = Up1_q;
}


