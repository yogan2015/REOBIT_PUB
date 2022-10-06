
void Init(void)
{
}

void Exec(void)
{
  long Tf1;

  if (*v->Tf != v->PrevTf)
  {
    Tf1       = _IQ24div(*v->Tf,        _IQ24(10.0));
    v->K1     = _IQ24div(v->SampleTime, Tf1 + v->SampleTime);
    v->K2     = _IQ24div(Tf1,           Tf1 + v->SampleTime);
    v->PrevTf = *v->Tf;
  }

  if ((short)*v->R)
  {
    v->Out      = 0;
    v->PrevOut  = 0;
    v->Out1     = 0;
    v->PrevOut1 = 0;
    v->Out2     = 0;
    v->PrevOut2 = 0;
    return;
  }

  v->Out1     = _IQ24mpy(*v->In,  v->K1) + _IQ24mpy(v->PrevOut1, v->K2);
  v->PrevOut1 = v->Out1;
  v->Out2     = _IQ24mpy(v->Out1, v->K1) + _IQ24mpy(v->PrevOut2, v->K2);
  v->PrevOut2 = v->Out2;
  v->Out      = _IQ24mpy(v->Out2, v->K1) + _IQ24mpy(v->PrevOut,  v->K2);
  v->PrevOut  = v->Out;
}


