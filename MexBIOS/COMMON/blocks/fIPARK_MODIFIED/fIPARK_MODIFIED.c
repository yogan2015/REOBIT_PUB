
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
    v->Alpha = (*v->Ds * Cosine) - (*v->Qs * Sine);
    v->Beta  = (*v->Qs * Cosine) + (*v->Ds * Sine);
   break;

   case 1:
    v->Alpha = (*v->Ds * Sine) + (*v->Qs * Cosine);
    v->Beta  = (*v->Qs * Sine) - (*v->Ds * Cosine);
   break;
  }
}

