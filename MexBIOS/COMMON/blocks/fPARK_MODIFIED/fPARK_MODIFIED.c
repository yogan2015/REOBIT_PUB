
void Init(void)
{
}

void Exec(void)
{
  float Sine, Cosine;

  Sine   = sinf(*v->Angle * 2 * M_PI);
  Cosine = cosf(*v->Angle * 2 * M_PI);

  switch (v->Aligment)
  {
    case 0:
      v->Ds = (*v->Alpha * Cosine) + (*v->Beta * Sine);
      v->Qs = (*v->Beta * Cosine) - (*v->Alpha * Sine);
    break;

    case 1:
      v->Ds = (*v->Alpha * Sine) - (*v->Beta * Cosine);
      v->Qs = (*v->Alpha * Cosine) + (*v->Beta * Sine);
    break;
  }
}



