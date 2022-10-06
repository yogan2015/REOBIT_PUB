
void Init(void)
{
}

void Exec(void)
{
  long Sine, Cosine;

  Sine   = _IQ24sinPU(*v->Angle);
  Cosine = _IQ24cosPU(*v->Angle);

  v->Alpha = _IQ24mpy(*v->Ds, Cosine) - _IQ24mpy(*v->Qs, Sine);
  v->Beta  = _IQ24mpy(*v->Qs, Cosine) + _IQ24mpy(*v->Ds, Sine);
}

