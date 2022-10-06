
void Init(void)
{

}

void Exec(void)
{
  v->Timer = v->Timer + 1;
  v->Summ  = v->Summ + (*v->In);
  if (v->Timer >= *v->Prd)
  {
    v->Av    = v->Summ / *v->Prd;
    v->Timer = 0;
    v->Summ  = 0;
  }
}

