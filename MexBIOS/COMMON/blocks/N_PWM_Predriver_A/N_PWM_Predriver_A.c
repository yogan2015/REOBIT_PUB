// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int Ka, Kb;
  int Va, Vb, Vc;
  int Sector = 0;
  int Ta, Tb, Tc;
  int A1, B1;
  long Sine, Cosine;

  Sine   = _IQ24sinPU(*v->Th);
  Cosine = _IQ24cosPU(*v->Th);
  A1  = _IQ24mpy(*v->Alpha, Cosine) + _IQ24mpy(*v->Beta,  Sine);
  B1  = _IQ24mpy(*v->Beta,  Cosine) - _IQ24mpy(*v->Alpha, Sine);
  Ka = _IQ24mpy(A1, 14529495);  //0.86602540378443864676372317
  Kb = B1 >> 1;

  Va = B1;
  Vb =  Ka - Kb;
  Vc = -Ka - Kb;

  if (Va > 0) Sector = 1;
  if (Vb > 0) Sector = Sector + 2;
  if (Vc > 0) Sector = Sector + 4;

  Vb =  Ka + Kb;
  Vc = -Ka + Kb;

  switch(Sector)
  {
    case 0:
      Ta = 8388608;
      Tb = 8388608;
      Tc = 8388608;
      break;
    case 1:
      Tb = (16777216 - Vc - Vb) >> 1;
      Ta = Tb + Vc;
      Tc = Ta + Vb;
      break;
    case 2:
      Ta = (16777216 - Vb + Va) >> 1;
      Tc = Ta + Vb;
      Tb = Tc - Va;
      break;
    case 3:
      Ta = (16777216 + Vc - Va) >> 1;
      Tb = Ta - Vc;
      Tc = Tb + Va;
      break;
    case 4:
      Tc = (16777216 + Va - Vc) >> 1;
      Tb = Tc - Va;
      Ta = Tb + Vc;
      break;
    case 5:
      Tb = (16777216 - Va + Vb) >> 1;
      Tc = Tb + Va;
      Ta = Tc - Vb;
      break;
    case 6:
      Tc = (16777216 + Vb + Vc) >> 1;
      Ta = Tc - Vb;
      Tb = Ta - Vc;
      break;
  }

  Ta = 16777216 - (Ta << 1);
//  Tb = 16777216 - (Tb << 1);
//  Tc = 16777216 - (Tc << 1);

   v->Out_TOP =  16777216 + (__IQmpy(*v->k, Ta - 16777216, 24)>>1);
   v->Out_BOT = -16777216 + (__IQmpy(*v->k, Ta + 16777216, 24)>>1);
}

