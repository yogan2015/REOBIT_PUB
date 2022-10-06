
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  float Acos, Bcos, Ccos;
  // Линейные составляющие в фазные
  Acos = (-0.3333) * (2 * *v->AB + *v->BC);
  Bcos = (0.3333) * (*v->AB - *v->BC);
  Ccos = (0.3333) * (*v->AB + 2 * *v->BC);

  // Восстановление векторов из проекций
    // A
    v->Asin = v->Asin + Acos * v->Td * *v->T;
    // B
    v->Bsin = v->Asin + Acos * v->Td * *v->T;
    // C
    v->Csin = v->Asin + Acos * v->Td * *v->T;

  //Вычисление симметричных составляющих
  v->A1cos = (0.1666) * (2 * Acos - Bcos - Ccos - 1.732 * v->Bsin + 1.732 * v->Csin);
  v->A1sin = (0.1666) * (2 * v->Asin - v->Bsin - v->Csin + 1.732 * Bcos - 1.732 * Ccos);
  v->A2cos = (0.1666) * (2 * Acos - Bcos - Ccos + 1.732 * v->Bsin - 1.732 * v->Csin);
  v->A2sin = (0.1666) * (2 * v->Asin - v->Bsin - v->Csin - 1.732 * Bcos + 1.732 * Ccos);
}

