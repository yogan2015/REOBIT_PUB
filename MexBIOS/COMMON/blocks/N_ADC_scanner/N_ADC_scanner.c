
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out = ((*((int *)(*v->adr + ((*v->index)<<2))))<<12);
}

