
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Alpha = (0.33333333333333333333333333333333) * (2 * *v->A - *v->B - *v->C);
  v->Beta =  (0.5774) * (*v->B - *v->C);
  v->Magn =  sqrt(v->Alpha * v->Alpha + v->Beta * v->Beta);
}

