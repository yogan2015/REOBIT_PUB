
void Init(void)
{

}

void Exec(void)
{
  v->A = *v->Alpha + *v->ZeroSeq;
  v->B = (-0.5 * (*v->Alpha) + 0.86602540378443864676372317 * (*v->Beta)) + *v->ZeroSeq;
  v->C = (-0.5 * (*v->Alpha) - 0.86602540378443864676372317 * (*v->Beta)) + *v->ZeroSeq;


}

