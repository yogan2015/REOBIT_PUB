
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->A = (-0.3333) * (2 * *v->AB + *v->BC);
  v->B = (0.3333) * (*v->AB - *v->BC);
  v->C = (0.3333) * (*v->AB + 2 * *v->BC);
}

