
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int  v_Cos, v_Sin;  //  Нормированные величины для расчетов внутри блока
  int  v_delt;    //  Выход фазового детектора
  int  r_delt;
  int  v_piout;  //  Выход ПИ-регулятора

// Циклический интегратор применительно к ист. переменной Thetap
  if ((short)*v->enable)
  {} else {
    v->piout=0;
    v->Up = 0;
    v->Ui = 0;
    v->Uerr=0;
  }

  if ((short)*v->phase_RST)
  {
    v->Thetap = *v->phase;
  } else {
    v->Thetap += (_IQ20mpy((v->f_basic + (v->piout >> 4)), v->Td >> 4) << 4);   // ???? ????? 20 ? 24 ????????,
  }                                                                        // ???? piout ?????????? ????

  if (v->Thetap > 105414357)    v->Thetap -= 105414357;
  if (v->Thetap < 0)      v->Thetap += 105414357;
  v->out_alpha   = _IQ24cos(v->Thetap);
  v->out_beta    = _IQ24sin(v->Thetap);
  v->out_theta   = v->Thetap;
  v->Freq   = v->f_basic + v->piout;

//  Фазовый детектор с нормализацией вычисляет разность между текущим sin/cos и beta/alpha из предыдущего шага
  v->Magn   =  _IQ24mag(*v->in_alpha, *v->in_beta);
  if (v->Magn <= labs(*v->in_alpha))  v->Magn = labs(*v->in_alpha);
  if (v->Magn <= labs(*v->in_beta))  v->Magn = labs(*v->in_beta);
  v_Cos    = _IQ24div(*v->in_alpha, v->Magn);
  v_Sin    = _IQ24div(*v->in_beta, v->Magn);
  v_delt  = _IQ24mpy(v->out_alpha, v_Sin) - _IQ24mpy(v->out_beta,v_Cos);
  r_delt  = v_delt;
  v->delt  = v_delt;

  // ПИ регулятор delt->Theta
  v->Ui    = v->Up + _IQ24mpy(_IQ24mpy(v->kp, r_delt), v->f_vf);
  if (v->Ui > v->f_delt)    v->Ui = v->f_delt;
  if (v->Ui < -(v->f_delt))    v->Ui = -v->f_delt;
  v->piout  = _IQ24mpy(r_delt, v->kp) + v->Ui;
  v->Up    = v->Ui;

  if (v->piout > v->f_delt)    v->piout = v->f_delt;
  if (v->piout < -(v->f_delt))    v->piout = -v->f_delt;
}

