
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (*v->Hold == 1)
  {
    v->Out_1 = v->Par_1;
    v->Out_2 = v->Par_2;
  }
  else
  {
    v->Out_1 = *v->In_1;
    v->Out_2 = *v->In_2;
    v->Par_1 = *v->In_1;
    v->Par_2 = *v->In_2;
  }

}

