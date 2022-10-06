
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  ((short)*v->RST ? (v->B = 0) : (v->B |= *v->A));
}

