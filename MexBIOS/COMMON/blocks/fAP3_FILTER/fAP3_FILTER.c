
void Init(void)
{
}

void Exec(void)
{
  float Tf1;

  if (*v->Tf != v->PrevTf)
  {
    Tf1       = *v->Tf / 10;
    v->K1     = v->SampleTime / (Tf1 + v->SampleTime);
    v->K2     = Tf1           / (Tf1 + v->SampleTime);
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

  v->Out1     = *v->In  * v->K1 + v->PrevOut1 * v->K2;
  v->PrevOut1 = v->Out1;
  v->Out2     = v->Out1 * v->K1 + v->PrevOut2 * v->K2;
  v->PrevOut2 = v->Out2;
  v->Out      = v->Out2 * v->K1 + v->PrevOut  * v->K2;
  v->PrevOut  = v->Out;
}


