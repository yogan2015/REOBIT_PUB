
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out_a = _IQ24mpy(*v->A_a, *v->B_a) + _IQ24mpy(*v->A_b, *v->B_b);
  v->Out_b = -(_IQ24mpy(*v->A_b, *v->B_a) - _IQ24mpy(*v->A_a, *v->B_b));
}

