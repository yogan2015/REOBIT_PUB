
void Init(void)
{
}

void Exec(void)
{
  float Sine, Cosine;

  Sine   = sin(*v->Angle * 2*M_PI);
  Cosine = cos(*v->Angle * 2*M_PI);

  v->Alpha = (*v->Ds * Cosine) - (*v->Qs * Sine);
  v->Beta  = (*v->Qs * Cosine) + (*v->Ds * Sine);
}

