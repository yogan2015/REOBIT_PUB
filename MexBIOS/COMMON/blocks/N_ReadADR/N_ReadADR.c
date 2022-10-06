
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->DATA = *((int *)(*v->ADR + 4));
}

