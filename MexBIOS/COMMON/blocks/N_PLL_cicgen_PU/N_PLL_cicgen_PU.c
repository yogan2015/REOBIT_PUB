
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->pr += (_IQ20mpy(*v->freq, (v->Td >> 4))<< 4);
  if (v->pr > 16777216) v->pr -= 16777216;
  if (v->pr < 0) v->pr += 16777216;
  v->A = _IQ24cosPU(v->pr);
  v->B = _IQ24sinPU(v->pr);
  v->theta = v->pr;
}

