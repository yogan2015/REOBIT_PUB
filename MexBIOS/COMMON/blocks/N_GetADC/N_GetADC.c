
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out = (*((int *)(*v->adr + (4*v->index))))<<12;
}

