
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->delt = _IQ24mpy(*v->Cos_2, *v->Sin_1) - _IQ24mpy(*v->Sin_2, *v->Cos_1);
}

