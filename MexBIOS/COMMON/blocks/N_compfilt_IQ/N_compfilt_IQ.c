
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out = __IQmpy(v->k, (*v->A + *v->U), 24) + __IQmpy((16777216-v->k), (v->A_p), 24);
  v->A_p = v->Out;
}

