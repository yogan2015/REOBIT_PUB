
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int Rphase;
  v->phase += (_IQ20mpy(v->freq, (v->Td >> 4))<< 4);
  if (v->phase > 16777216)  v->phase -= 16777216;
  if (v->phase < 0)         v->phase += 16777216;
  Rphase = *v->ang - v->phase;
  v->A = _IQ24mpy(_IQ24cosPU(v->phase), *v->A1) + _IQ24mpy(_IQ24cosPU(Rphase), *v->A2);
  v->B = _IQ24mpy(_IQ24sinPU(v->phase), *v->A1) + _IQ24mpy(_IQ24sinPU(Rphase), *v->A2);
}

