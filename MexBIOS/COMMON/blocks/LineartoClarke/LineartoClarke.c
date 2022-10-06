
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Alpha = (*v->AB * 2 + *v->BC) * (-0.333333);
  v->Beta =  *v->BC * (-0.57735027);
}

