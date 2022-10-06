
void Init(void)
{
  v->Out = v->Offset;
}

void Exec(void)
{
  long Tmp, Timeout;

  if ((short)*v->Reset)
  {
    v->Out = v->Offset;
    v->Timer = 0;
    return;
  }

  if (!*v->Freq) { v->Out = v->Offset; return; }

  Tmp = v->Out - v->Offset;
  Timeout = _IQ1div(_IQ24(0.25), _IQ24mpy(*v->Freq, v->SampleTime));

  if (++v->Timer >= Timeout)
  {
    Tmp = (Tmp <= 0) ? *v->Ampl : -*v->Ampl;
    v->Timer = 0;
  }

  v->Out = Tmp + v->Offset;
}


