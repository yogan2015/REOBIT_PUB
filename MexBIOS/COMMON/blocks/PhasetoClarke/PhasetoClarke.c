
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Alpha = (2/3) * (*v->A - (*v->B + *v->C)/2);
  v->Beta =  (0.57735026918962576450914878050196) * (*v->B - *v->C);
  v->Zero =  (1/2) * (*v->A + *v->B + *v->C);
}

