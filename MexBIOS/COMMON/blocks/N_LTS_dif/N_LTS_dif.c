
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  float Acos, Bcos, Ccos;
  float Asin, Bsin, Csin;
  // Линейные составляющие в фазные
  Acos = (-0.3333) * (2 * *v->AB + *v->BC);
  Bcos = (0.3333) * (*v->AB - *v->BC);
  Ccos = (0.3333) * (*v->AB + 2 * *v->BC);

  // Восстановление векторов из проекций
    // A
    Asin = (Acos + v->Ap) * v-> Fd;
    // B
    Bsin = (Acos + v->Bp) * v-> Fd;
    // C
    Csin = (Acos + v->Cp) * v-> Fd;
  //Переписвание переменных хранения
  v->Ap = Acos;  v->Bp = Bcos;  v->Cp = Ccos;
  //Вычисление симметричных составляющих
  v->A1cos = (0.1666) * (2 * Acos - Bcos - Ccos - 1.732 * Bsin + 1.732 * Csin);
  v->A1sin = (0.1666) * (2 * Asin - Bsin - Csin + 1.732 * Bcos - 1.732 * Ccos);
  v->A2cos = (0.1666) * (2 * Acos - Bcos - Ccos + 1.732 * Bsin - 1.732 * Csin);
  v->A2sin = (0.1666) * (2 * Asin - Bsin - Csin - 1.732 * Bcos + 1.732 * Ccos);
}

