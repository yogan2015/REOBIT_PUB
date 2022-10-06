
void Init(void)
{
}

void Exec(void)
{
  if(*v->R)
  {
    v->Out = 0;
  }
  else
  {
    if(*v->U_DC > *v->U_DC_MAX)
    {
      v->K_Dec = _IQ24(1.0) - ((_IQ11div((*v->U_DC - *v->U_DC_MAX), (*v->U_DC_MAX - v->U_DC_Nominal)) % _IQ11(1.0)) << 13);
    }
    else
    {
      v->K_Dec = _IQ24(1.0);
    }

    if(*v->In >= 0 && v->Out >= 0)
    {
      if(*v->In > v->Out)
      {
        v->Out += _IQ24div(_IQ24mpy(*v->Acc, v->Time_Discrete), *v->Time_Acc);
      }
      else if(*v->In < v->Out)
      {
        v->Out -= _IQ24mpy(_IQ24div(_IQ24mpy(*v->Dec, v->Time_Discrete), *v->Time_Dec), v->K_Dec);
      }
      else
      {
        v->Out = *v->In;
      }
    }
    else if(*v->In <= 0 && v->Out <= 0)
    {
      if(*v->In > v->Out)
      {
        v->Out += _IQ24mpy(_IQ24div(_IQ24mpy(*v->Dec, v->Time_Discrete), *v->Time_Dec), v->K_Dec);
      }
      else if(*v->In < v->Out)
      {
        v->Out -= _IQ24div(_IQ24mpy(*v->Acc, v->Time_Discrete), *v->Time_Acc);
      }
      else
      {
        v->Out = *v->In;
      }
    }
    else if(*v->In > 0 && v->Out < 0)
    {
      if(v->Out < 0)
      {
        v->Out += _IQ24mpy(_IQ24div(_IQ24mpy(*v->Dec, v->Time_Discrete), *v->Time_Dec), v->K_Dec);
      }
    }
    else if(*v->In < 0 && v->Out > 0)
    {
      if(v->Out > 0)
      {
        v->Out -= _IQ24mpy(_IQ24div(_IQ24mpy(*v->Dec, v->Time_Discrete), *v->Time_Dec), v->K_Dec);
      }
    }
  }
}




