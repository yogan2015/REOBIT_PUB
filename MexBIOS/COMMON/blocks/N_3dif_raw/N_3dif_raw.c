
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int max;
  int max2;
  max = abs(*v->v1 - *v->v2);
  max2= abs(*v->v2 - *v->v3);
  max = ((max>max2)?(max):(max2));
  max2= abs(*v->v1 - *v->v3);
  max = ((max>max2)?(max):(max2));
  v->out = max;
}

