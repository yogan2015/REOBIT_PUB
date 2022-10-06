
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int local_a = *v->A;
  int local_b = *v->B;
  while ((local_b - local_a) > (1 << (v->Format - 1)))
  {
    local_a += (1 << v->Format);
  }
  while ((local_a - local_b) > (1 << (v->Format - 1)))
  {
    local_b += (1 << v->Format);
  }
  v->DIF = local_a - local_b;
}

