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

  if ((short)*v->SHORT)
  {
   v->Out_r1_TOP =  16777216;
   v->Out_r1_BOT =  16777216;

   v->Out_r2_TOP =  16777216;
   v->Out_r2_BOT =  16777216;

   v->Out_r3_TOP =  16777216;
   v->Out_r3_BOT =  16777216;

    return;
  }
  Ka = _IQ24mpy(*v->Alpha, 14529495);  //0.86602540378443864676372317
  Kb = *v->Beta >> 1;

  Va = *v->Beta;
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

  Ta = 16777216 - (Ta << 1) + *v->DC;
  Tb = 16777216 - (Tb << 1) + *v->DC;
  Tc = 16777216 - (Tc << 1) + *v->DC;

   v->Out_r1_TOP =  16777216 + (__IQmpy(*v->k, Ta - 16777216, 24)>>1);
   v->Out_r1_BOT = -16777216 + (__IQmpy(*v->k, Ta + 16777216, 24)>>1);

   v->Out_r2_TOP =  16777216 + (__IQmpy(*v->k, Tb - 16777216, 24)>>1);
   v->Out_r2_BOT = -16777216 + (__IQmpy(*v->k, Tb + 16777216, 24)>>1);

   v->Out_r3_TOP =  16777216 + (__IQmpy(*v->k, Tc - 16777216, 24)>>1);
   v->Out_r3_BOT = -16777216 + (__IQmpy(*v->k, Tc + 16777216, 24)>>1);
}

