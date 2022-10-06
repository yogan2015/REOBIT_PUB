
void Init(void)
{
}

void Exec(void)
{
  v->Alpha = _IQ24mpy(*v->A, _IQ24(0.66666666666667)) - _IQ24mpy(*v->B, _IQ24(0.33333333333333))-
  _IQ24mpy(*v->C, _IQ24(0.33333333333333));

  v->Beta  = _IQ24mpy(*v->A, _IQ24(0.57735026918963)) - _IQ24mpy(*v->C, _IQ24(0.57735026918963));

  v->Zero = _IQ24mpy((*v->A + *v->B + *v->C), _IQ24(0.33333333333333));

}

