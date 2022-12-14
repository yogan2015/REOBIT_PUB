
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int max, max2;
  int v1, v2, v3;
  v1 = (*((int *)(*v->adr + (4*v->index_v1))));
  v2 = (*((int *)(*v->adr + (4*v->index_v2))));
  v3 = (*((int *)(*v->adr + (4*v->index_v3))));
  max = abs(v1-v2);
  max2= abs(v2-v3);
  max = ((max>max2)?(max):(max2));
  max2= abs(v1-v3);
  max = ((max>max2)?(max):(max2));
  v->out = max;
}

