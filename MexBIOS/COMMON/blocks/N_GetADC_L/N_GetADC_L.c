
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int AB, BC;
  int A, B;
  AB = ((*((int *)(*v->adr + (4*v->index_AB))))<<12);
  BC = ((*((int *)(*v->adr + (4*v->index_BC))))<<12);
  v->mean_AB = _IQ24mpy(v->mean_AB, (v->k)) + _IQ24mpy(AB, 16777216 - v->k);
  v->mean_BC = _IQ24mpy(v->mean_BC, (v->k)) + _IQ24mpy(BC, 16777216 - v->k);
  A = __IQmpy ((-5592405), (((AB - v->mean_AB) << 1) + (BC - v->mean_BC)), 24);
  B = __IQmpy (5592405   , ((AB  - v->mean_AB)       - (BC - v->mean_BC)), 24);
  v->Out_A = _IQ24mpy((A), v->gain);
  v->Out_B = _IQ24mpy(_IQ24mpy((A) + ((B) << 1), 9686330), v->gain);
}

