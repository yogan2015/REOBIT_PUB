
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int A, B;
  A = __IQ(*v->Alpha, 24);
  B = __IQ(*v->Beta, 24);
  v->Magn = _IQ24mag(A, B);
  v->Cos = _IQ24div(A, v->Magn);
  v->Sin = _IQ24div(B, v->Magn);
}
