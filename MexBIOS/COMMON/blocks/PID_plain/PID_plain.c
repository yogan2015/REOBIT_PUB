
// Do not initialize inputs!
void Init(void)
{
  v->g = 0;
}

void Exec(void)
{
  if (*v->RST){
    v->g = 0;
    v->Ui= 0;
  };

v->Ui = v->Ui + *v->e * v->T_d * v->K_i;
v->g = v->Ui + *v->e * v->K_p;
}

