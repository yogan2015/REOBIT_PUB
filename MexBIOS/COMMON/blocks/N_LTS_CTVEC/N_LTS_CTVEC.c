
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  float Asin, Bsin, Csin;
  float Acos, Bcos, Ccos;

  Acos = (-0.3333) * (2 * *v->AB + *v->BC);
  Bcos = (0.3333) * (*v->AB - *v->BC);
  Ccos = (0.3333) * (*v->AB + 2 * *v->BC);

  Asin = (Acos - v->Ap) * -480 * *v->T;
  Bsin = (Bcos - v->Bp) * -480 * *v->T;
  Csin = (Ccos - v->Cp) * -480 * *v->T;

  v->Ap = Acos;  v->Bp = Bcos;  v->Cp = Ccos;

  v->A1cos = (0.1666) * (2 * Acos - Bcos - Ccos - 1.732 * Bsin + 1.732 * Csin);
  v->A1sin = (0.1666) * (2 * Asin - Bsin - Csin + 1.732 * Bcos - 1.732 * Ccos);
  v->A2cos = (0.1666) * (2 * Acos - Bcos - Ccos + 1.732 * Bsin - 1.732 * Csin);
  v->A2sin = (0.1666) * (2 * Asin - Bsin - Csin - 1.732 * Bcos + 1.732 * Ccos);
  //v->A1cos = Acos;
  //v->A1sin = Asin;
  //v->A2cos = Bcos;
  //v->A2sin = Bsin;
}

