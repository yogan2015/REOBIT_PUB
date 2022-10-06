
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  long e, i;

  if ((short)*v->RST)
  {
    v->Out = *v->Init;
    v->Ip  = *v->Init;
    return;
  }

  e      = *v->Ref - *v->Fb;
  v->Ip  += _IQ24mpy(e, _IQ24mpy(v->Ki, v->Kp));
  v->Ip = _IQsat(v->Ip, v->max, v->min);

  v->Out = _IQsat(v->Ip + _IQ24mpy(e, v->Kp), v->max, v->min);

}

