
void Init(void)
{
}

void Exec(void)
{
  long Sine, Cosine;

  Sine   = _IQ24sinPU(*v->Angle);
  Cosine = _IQ24cosPU(*v->Angle);

  v->Ds = _IQ24mpy(*v->Alpha, Cosine) + _IQ24mpy(*v->Beta,  Sine);
  v->Qs = _IQ24mpy(*v->Beta,  Cosine) - _IQ24mpy(*v->Alpha, Sine);
}



