
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->A1cos = (0.1666) * (2 * *v->Acos - *v->Bcos - *v->Ccos - 1.732 * *v->Bsin + 1.732 * *v->Csin);
  v->A1sin = (0.1666) * (2 * *v->Asin - *v->Bsin - *v->Csin + 1.732 * *v->Bcos - 1.732 * *v->Ccos);
  v->A2cos = (0.1666) * (2 * *v->Acos - *v->Bcos - *v->Ccos + 1.732 * *v->Bsin - 1.732 * *v->Csin);
  v->A2sin = (0.1666) * (2 * *v->Asin - *v->Bsin - *v->Csin - 1.732 * *v->Bcos + 1.732 * *v->Ccos);
}

