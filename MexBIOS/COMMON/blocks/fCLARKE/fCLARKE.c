
void Init(void)
{
}

void Exec(void)
{
  v->Alpha = *v->A;
  v->Beta  = (*v->A + 2.0 * (*v->B)) * 0.57735026918963;
}

