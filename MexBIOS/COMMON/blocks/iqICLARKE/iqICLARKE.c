
void Init(void)
{

}

void Exec(void)
{
  v->A = *v->Alpha;
  v->B = _IQ24mpy(_IQ24(-0.5), *v->Alpha) + _IQ24mpy(_IQ24(0.86602540378444), *v->Beta);
  v->C = _IQ24mpy(_IQ24(-0.5), *v->Alpha) - _IQ24mpy(_IQ24(0.86602540378444), *v->Beta);
}

