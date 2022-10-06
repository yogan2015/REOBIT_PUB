
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->OUT_A = *v->A1 + *v->A2;
  v->OUT_B = *v->B1 + *v->B2;
}

