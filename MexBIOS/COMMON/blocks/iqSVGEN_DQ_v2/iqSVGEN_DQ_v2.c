
void Init(void)
{
}

void Exec(void)
{
  long Ka, Kb;
  long Va, Vb, Vc;
  long Sector = 0;

  Ka = _IQ24mpy(*v->Alpha, _IQ24(0.86602540378443864676372317));
  Kb = *v->Beta >> 1;

  Va = *v->Beta;
  Vb =  Ka - Kb;
  Vc = -Ka - Kb;

  if (Va > _IQ24(0.0)) Sector = 1;
  if (Vb > _IQ24(0.0)) Sector = Sector + 2;
  if (Vc > _IQ24(0.0)) Sector = Sector + 4;

  Vb =  Ka + Kb;
  Vc = -Ka + Kb;

  switch(Sector)
  {
    case 0:
      v->Ta = _IQ24(0.5);
      v->Tb = _IQ24(0.5);
      v->Tc = _IQ24(0.5);
      break;
    case 1:
      v->Tb = (_IQ24(1.0) - Vc - Vb) >> 1;
      v->Ta = v->Tb + Vc;
      v->Tc = v->Ta + Vb;
      break;
    case 2:
      v->Ta = (_IQ24(1.0) - Vb + Va) >> 1;
      v->Tc = v->Ta + Vb;
      v->Tb = v->Tc - Va;
      break;
    case 3:
      v->Ta = (_IQ24(1.0) + Vc - Va) >> 1;
      v->Tb = v->Ta - Vc;
      v->Tc = v->Tb + Va;
      break;
    case 4:
      v->Tc = (_IQ24(1.0) + Va - Vc) >> 1;
      v->Tb = v->Tc - Va;
      v->Ta = v->Tb + Vc;
      break;
    case 5:
      v->Tb = (_IQ24(1.0) - Va + Vb) >> 1;
      v->Tc = v->Tb + Va;
      v->Ta = v->Tc - Vb;
      break;
    case 6:
      v->Tc = (_IQ24(1.0) + Vb + Vc) >> 1;
      v->Ta = v->Tc - Vb;
      v->Tb = v->Ta - Vc;
      break;
  }

  v->Ta = _IQ(1.0) - (v->Ta << 1);
  v->Tb = _IQ(1.0) - (v->Tb << 1);
  v->Tc = _IQ(1.0) - (v->Tc << 1);

switch (v->PWM_Type)
  {
  case 0:
  v->Ta_=v->Ta;
  v->Tb_=v->Tb;
  v->Tc_=v->Tc;
  break;
  case 1: //SVPWM MacDonald
    v->Min1 = (v->Ta < v->Tb)? v->Ta : v->Tb;
    v->Min2 = (v->Tb < v->Tc)? v->Tb : v->Tc;
    v->Min3 = (v->Min1 < v->Min2)? v->Min1 : v->Min2;

    v->Ta_ = v->Ta - v->Min3 - _IQ24mag(*v->Alpha, *v->Beta);
    v->Tb_ = v->Tb - v->Min3 - _IQ24mag(*v->Alpha, *v->Beta);
    v->Tc_ = v->Tc - v->Min3 - _IQ24mag(*v->Alpha, *v->Beta);
  break;
  case 2: // DPWM MacDonald
    v->Min1 = (v->Ta < v->Tb)? v->Ta : v->Tb;
    v->Min2 = (v->Tb < v->Tc)? v->Tb : v->Tc;
    v->Min3 = (v->Min1 < v->Min2)? v->Min1 : v->Min2;

    v->Ta_ = v->Ta - v->Min3 - _IQ24(1.0);
    v->Tb_ = v->Tb - v->Min3 - _IQ24(1.0);
    v->Tc_ = v->Tc - v->Min3 - _IQ24(1.0);
  break;
  }

}


