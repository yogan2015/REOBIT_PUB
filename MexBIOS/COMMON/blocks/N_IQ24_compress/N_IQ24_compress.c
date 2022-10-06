
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Out = ((*v->A2) & 0xFFFF0000) | ((*v->A1 >> 16) & 0xFFFF);
}

