
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  if (*v->Mode == 0)
  {
    v->Out = *v->In_1;
  } else
  {
    v->Out = *v->In_2;
  }
}

