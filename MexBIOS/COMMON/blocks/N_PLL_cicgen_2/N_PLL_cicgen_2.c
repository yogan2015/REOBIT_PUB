
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->pr += (_IQ20mpy(*v->freq, (v->Td >> 4))<< 4);
  if (v->pr > __IQ(6.2831853,24)) v->pr -= __IQ(6.2831853, 24);
  if (v->pr < 0) v->pr += __IQ(6.2831853, 24);
  v->Cos_2 = _IQ24cos(v->pr);
  v->Sin_2 = _IQ24sin(v->pr);
  v->phase = __IQmpy(v->pr, __IQ(0.1591549, 24), 24);
}

