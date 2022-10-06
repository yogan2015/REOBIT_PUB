
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->A1 = (v->DW1 & 0xFFFF) << 16;
  v->B1 = ((v->DW1 >> 16))  << 16;

  v->A2 = (v->DW2 & 0xFFFF) << 16;
  v->B2 = ((v->DW2 >> 16))  << 16;

  v->A3 = (v->DW3 & 0xFFFF) << 16;
  v->B3 = ((v->DW3 >> 16))  << 16;

  v->A4 = (v->DW4 & 0xFFFF) << 16;
  v->B4 = ((v->DW4 >> 16))  << 16;
}

