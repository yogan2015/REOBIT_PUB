
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int A, B;
  A = ((*((int *)(*v->adr + (4*v->index_A))))<<12);
  B = ((*((int *)(*v->adr + (4*v->index_B))))<<12);
  v->mean_A = _IQ24mpy(v->mean_A, (v->k)) + _IQ24mpy(A, 16777216 - v->k);
  v->mean_B = _IQ24mpy(v->mean_B, (v->k)) + _IQ24mpy(B, 16777216 - v->k);
  v->Out_A = _IQ24mpy((A - v->mean_A), v->gain);
  v->Out_B = _IQ24mpy(_IQ24mpy(v->Out_A + ((B - v->mean_B) << 1), 9686330), v->gain);
}

