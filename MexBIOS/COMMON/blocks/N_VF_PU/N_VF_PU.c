
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int  uP;     //  пропорциональная составляющая
  int signA, signB;
// Циклический интегратор применительно к ист. переменной Thetap
  if ((short)*v->enable)
  {} else {
    v->piout  = 0;
    v->uI     = 0;
    //v->Thetap = 0;
  }

  // Защита от ошибки в 180 град.
  signA = _IQ24mpy(*v->in_alpha, v->out_alpha);
  signB = _IQ24mpy(*v->in_beta,  v->out_beta);
  if ((signA < 0) && (signB < 0) && ((short)*v->enable)) v->Thetap += 8388608;

  v->Thetap += _IQ20mpy((v->f0 + (v->piout >> 4)), v->Td >> 4) << 4;
  if (v->Thetap > 16777216)    v->Thetap -= 16777216;
  if (v->Thetap < 0)      v->Thetap += 16777216;
  v->out_alpha   = _IQ24cosPU(v->Thetap);
  v->out_beta    = _IQ24sinPU(v->Thetap);
  v->out_theta   = v->Thetap;
  v->Freq   = v->f0 + (v->piout >> 4);

//  Фазовый детектор с нормализацией вычисляет разность между текущим sin/cos и beta/alpha из предыдущего шага
  v->Magn   =  _IQ24mag(*v->in_alpha, *v->in_beta);
  if (v->Magn <= labs(*v->in_alpha))  v->Magn = labs(*v->in_alpha);
  if (v->Magn <= labs(*v->in_beta))  v->Magn = labs(*v->in_beta);
  v->delt  = _IQ24mpy(v->out_alpha, *v->in_beta) - _IQ24mpy(v->out_beta, *v->in_alpha);

  // ПИ регулятор delt->Theta
  uP    = (_IQ20mpy((v->delt >> 4), v->Kp)) << 4;
  v->uI = ((v->uI >> 4) + _IQ20mpy(uP, v->Ki)) << 4;
  v->piout = uP + v->uI;
  if (v->piout > v->f_delt)    v->piout = v->f_delt;
  if (v->piout < -(v->f_delt))    v->piout = -v->f_delt;
}

