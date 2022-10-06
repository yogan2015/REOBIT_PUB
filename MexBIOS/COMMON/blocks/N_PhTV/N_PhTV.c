
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Cos = *v->Ph;
  v->Sin = (v->Cos - v->pr) * *v->T;
  v->pr = v->Cos;
}

