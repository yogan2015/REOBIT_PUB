
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Dif = (*v->A_Cos * *v->B_Sin) - (*v->A_Sin * *v->B_Cos);
}

