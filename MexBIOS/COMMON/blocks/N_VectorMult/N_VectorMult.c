
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out_s = _IQ24mpy(*v->A_a, *v->B_b) - _IQ24mpy(*v->A_b, *v->B_a);
}

