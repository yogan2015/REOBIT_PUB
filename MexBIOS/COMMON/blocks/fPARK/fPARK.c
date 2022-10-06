
void Init(void)
{
}

void Exec(void)
{
  float Sine, Cosine;

  Sine   = sin(*v->Angle * 2*M_PI);
  Cosine = cos(*v->Angle * 2*M_PI);

  v->Ds = (*v->Alpha * Cosine) + (*v->Beta  * Sine);
  v->Qs = (*v->Beta  * Cosine) - (*v->Alpha * Sine);
}



