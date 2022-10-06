
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->pr += __IQ((*v->freq * v->Td),24);
  if (v->pr > __IQ(6.2831853,24)) v->pr -= __IQ(6.2831853, 24);
  if (v->pr < 0) v->pr += __IQ(6.2831853, 24);
  v->Cos_2 = _IQ24cos(v->pr);
  v->Sin_2 = _IQ24sin(v->pr);
}

