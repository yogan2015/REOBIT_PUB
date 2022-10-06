
void Init(void)
{
}

void Exec(void)
{
  if (*v->Tf != v->PrevTf)
  {
    v->K1 = v->SampleTime / (*v->Tf + v->SampleTime);
    v->K2 = *v->Tf        / (*v->Tf + v->SampleTime);
    v->PrevTf = *v->Tf;
  }

  if ((short)*v->R)
  {
    v->Out = 0;
    v->PrevOut = 0;
    return;
  }

  v->Out = *v->In * v->K1 + v->PrevOut * v->K2;
  v->PrevOut = v->Out;
}

