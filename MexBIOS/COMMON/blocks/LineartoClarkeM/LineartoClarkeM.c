
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Alpha = (*v->AB * 2 + *v->BC) * (0.3333);
  v->Beta =  *v->BC * (0.5774);
  v->Magn = sqrt(v->Alpha * v->Alpha + v->Beta * v->Beta);
}

