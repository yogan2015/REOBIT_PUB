
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int v_Cos, v_Sin;  //  Нормированные величины для расчетов внутри блока
  int v_delt;        //  Выход фазового детектора
  float r_delt;
  float v_piout;      //  Выход ПИ-регулятора

  //  Фазовый детектор с нормализацией вычисляет разность между текущим sin/cos и beta/alpha из предыдущего шага
  v->Magn =  _IQ24mag(*v->in_alpha, *v->in_beta);
  v_Cos = _IQ24div(*v->in_alpha, v->Magn);
  v_Sin = _IQ24div(*v->in_beta, v->Magn);
  v_delt= _IQ24mpy(v->pout_alpha, v_Sin) - _IQ24mpy(v->pout_beta,v_Cos);
  v->pout_alpha = v->out_alpha;
  v->pout_beta = v->out_beta;

  r_delt = __IQtoF(v_delt, 24);
  // ПИ регулятор delt->Theta
  v->Ui = v->Up + (v->kp * r_delt / v->f_vf);
  if (v->Ui > v->f_delt)   v->Ui = v->f_delt;
  if (v->Ui < -(v->f_delt))  v->Ui = -v->f_delt;
  v_piout = r_delt * v->kp + v->Ui;
  v->Up = v->Ui;

  if (v_piout > v->f_delt)   v_piout = v->f_delt;
  if (v_piout < -(v->f_delt))  v_piout = -v->f_delt;

  if (v->Thetap > __IQ(6.2831853, 24)) v->Thetap -= __IQ(6.2831853, 24);
  if (v->Thetap < __IQ(0, 24)) v->Thetap += __IQ(6.2831853, 24);
  v->out_alpha = _IQ24cos(v->Thetap);
  v->out_beta  = _IQ24sin(v->Thetap);
  v->out_theta = v->Thetap;
  v->Freq = v->f_basic + v_piout;
  v->delt = v_delt;

  // Циклический интегратор применительно к ист. переменной Thetap

  if ((short)*v->enable)
  {} else {
    v_piout=0;
    v->Up = 0;
    v->Ui = 0;
    v->Uerr=0;
  }

  if ((short)*v->phase_RST)
  {
    v->Thetap = *v->phase;
  } else {
      v->Thetap += __IQ(((v->f_basic + v_piout)* v->Td), 24);
  }


}

