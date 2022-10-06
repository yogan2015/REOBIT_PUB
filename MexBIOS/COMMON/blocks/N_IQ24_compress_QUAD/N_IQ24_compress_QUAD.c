
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->DW1 = ((*v->B1) & 0xFFFF0000) | ((*v->A1 >> 16) & 0xFFFF);
  v->DW2 = ((*v->B2) & 0xFFFF0000) | ((*v->A2 >> 16) & 0xFFFF);
  v->DW3 = ((*v->B3) & 0xFFFF0000) | ((*v->A3 >> 16) & 0xFFFF);
  v->DW4 = ((*v->B4) & 0xFFFF0000) | ((*v->A4 >> 16) & 0xFFFF);
}

