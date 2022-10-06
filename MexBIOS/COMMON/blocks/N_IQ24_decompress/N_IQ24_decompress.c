
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->A = (*v->DW & 0xFFFF)         << 16;
  v->B = ((*v->DW >> 16) & 0xFFFF) << 16;
}

