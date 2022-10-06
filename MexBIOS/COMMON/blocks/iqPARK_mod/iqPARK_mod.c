
void Init(void)
{
}

void Exec(void)
{
  long Sine, Cosine, Alpha, Beta;

  Alpha = *v->A;
  Beta  = _IQ24mpy(*v->A + (*v->B << 1), _IQ24(0.57735026918963));

  Sine   = _IQ24sinPU(*v->Angle);
  Cosine = _IQ24cosPU(*v->Angle);

  v->Ds = _IQ24mpy(Alpha, Cosine) + _IQ24mpy(Beta,  Sine);
  v->Qs = _IQ24mpy(Beta,  Cosine) - _IQ24mpy(Alpha, Sine);
}



