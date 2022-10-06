
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Acos = *v->Kdir * *v->A1cos + *v->Krev * *v->A2cos;    v->Asin = *v->Kdir * *v->A1sin + *v->Krev * *v->A2sin;
  v->Bcos = *v->Kdir*((*v->A1cos) * (-0.5) +   (*v->A1sin) * (0.866) )+*v->Krev*((*v->A2cos) * (-0.5) + (*v->A2sin) * (-0.866));
  v->Bsin = *v->Kdir*((*v->A1cos) * (-0.866) + (*v->A1sin) * (-0.5)  )+*v->Krev*((*v->A2cos) * (0.866) + (*v->A2sin) * (-0.5));
  v->Ccos = *v->Kdir*((*v->A1cos) * (-0.5) +   (*v->A1sin) * (-0.866))+*v->Krev*((*v->A2cos) * (-0.5) + (*v->A2sin) * (0.866));
  v->Csin = *v->Kdir*((*v->A1cos) * (0.866) +  (*v->A1sin) * (-0.5)  )+*v->Krev*((*v->A2cos) * (-0.866) + (*v->A2sin) * (-0.5));

}

