
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  float ThCos, ThSin;
  ThCos = cos(*v->ANG);  ThSin = sin(*v->ANG);
  v->Cos1_out = *v->Cos1 * ThCos + *v->Sin1 * ThSin;
  v->Sin1_out = *v->Sin1 * ThCos - *v->Cos1 * ThSin;
  v->Cos2_out = *v->Cos2 * ThCos + *v->Sin2 * ThSin;
  v->Sin2_out = *v->Sin2 * ThCos - *v->Cos2 * ThSin;
}

