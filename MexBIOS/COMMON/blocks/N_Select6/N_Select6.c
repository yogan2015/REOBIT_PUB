
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (*v->Mode == 0)
  {
    v->Out_1 = *v->In_1a;
    v->Out_2 = *v->In_2a;
    v->Out_3 = *v->In_3a;
    v->Out_4 = *v->In_4a;
    v->Out_5 = *v->In_5a;
    v->Out_6 = *v->In_6a;
  } else
  {
    v->Out_1 = *v->In_1b;
    v->Out_2 = *v->In_2b;
    v->Out_3 = *v->In_3b;
    v->Out_4 = *v->In_4b;
    v->Out_5 = *v->In_5b;
    v->Out_6 = *v->In_6b;
  }
}

