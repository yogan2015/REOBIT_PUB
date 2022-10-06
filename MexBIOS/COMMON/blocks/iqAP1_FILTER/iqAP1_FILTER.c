
void Init(void)
{
}

void Exec(void)
{
  if (*v->Tf != v->PrevTf)
  {
    v->K1 = _IQ24div(v->SampleTime, *v->Tf + v->SampleTime);
    v->K2 = _IQ24div(*v->Tf,        *v->Tf + v->SampleTime);
    v->PrevTf = *v->Tf;
  }

  if ((short)*v->R)
  {
    v->Out = 0;
    v->PrevOut = 0;
    return;
  }

  v->Out = _IQ24mpy(*v->In, v->K1) + _IQ24mpy(v->PrevOut, v->K2);
  v->PrevOut = v->Out;
}

