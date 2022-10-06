
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  v->Idest = v->Idest + v->SampleTime * ( (*v->Udm - (v->Idest*v->Rs) - (v->Wrest * v->zp * v->Lq * v->Iqest))/v->Ld );
  v->Iqest = v->Iqest + v->SampleTime * ( (*v->Uqm - (v->Iqest*v->Rs) - (v->Wrest * v->zp * ((v->Idest * v->Lq) + v->flux) * v->Iqest))/v->Lq );
  v->Wrest = v->Kp*( (*v->Idm * v->Iqest) - (*v->Iqm * v->Idest) - ((*v->Iqm - v->Iqest)*(v->flux / v->Ld)) ) +
  v->Ki*(v->Wrest + v->SampleTime*( (*v->Idm * v->Iqest) - (*v->Iqm * v->Idest) - ((*v->Iqm - v->Iqest)*(v->flux / v->Ld)) ) );


}

