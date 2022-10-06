
void Init(void)
{

}

void Exec(void)
{
  v->Timer = v->Timer + 1;
  v->Summ  = v->Summ + (*v->In >> 9);
  if (v->Timer >= *v->Prd)
  {
    v->Av    = _IQ1div(v->Summ, *v->Prd << 1);
    v->Timer = 0;
    v->Summ  = 0;
  }
}

