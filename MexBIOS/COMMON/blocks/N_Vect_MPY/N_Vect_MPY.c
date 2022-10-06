
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->OUT_A = _IQ24mpy(*v->A, *v->k);
  v->OUT_B = _IQ24mpy(*v->B, *v->k);
}

