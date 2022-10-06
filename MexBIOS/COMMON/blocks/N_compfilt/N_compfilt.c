
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out = (*v->k * (*v->A + *v->U)) + ((1-*v->k) * (v->A_p));
  v->A_p = v->Out;
}

