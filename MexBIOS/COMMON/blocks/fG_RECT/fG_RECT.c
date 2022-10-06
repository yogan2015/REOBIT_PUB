
void Init(void)
{
  v->Out = v->Offset;
}

void Exec(void)
{
  float Tmp, Timeout;

  if ((short)*v->Reset)
  {
    v->Out = v->Offset;
    v->Timer = 0;
    return;
  }

  if (!*v->Freq) { v->Out = v->Offset; return; }

  Tmp = v->Out - v->Offset;
  Timeout = 0.5 / (*v->Freq * v->SampleTime);

  if (++v->Timer >= Timeout)
  {
    Tmp = (Tmp <= 0) ? *v->Ampl : -*v->Ampl;
    v->Timer = 0;
  }

  v->Out = Tmp + v->Offset;
}


