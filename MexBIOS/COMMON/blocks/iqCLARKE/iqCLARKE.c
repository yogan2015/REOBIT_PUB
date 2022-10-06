
void Init(void)
{
}

void Exec(void)
{
  v->Alpha = *v->A;
  v->Beta  = _IQ24mpy(*v->A + (*v->B << 1), _IQ24(0.57735026918963));
}

