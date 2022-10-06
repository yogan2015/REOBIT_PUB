
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
      v->Ta_SVPWM = _IQ24(0.5);
      v->Tb_SVPWM = _IQ24(0.5);
      v->Tc = _IQ24(0.5);
      break;
    case 1:
      v->Tb_SVPWM = (_IQ24(1.0) - Vc - Vb) >> 1;
      v->Ta_SVPWM = v->Tb_SVPWM + Vc;
      v->Tc = v->Ta_SVPWM + Vb;
      break;
    case 2:
      v->Ta_SVPWM = (_IQ24(1.0) - Vb + Va) >> 1;
      v->Tc = v->Ta_SVPWM + Vb;
      v->Tb_SVPWM = v->Tc - Va;
      break;
    case 3:
      v->Ta_SVPWM = (_IQ24(1.0) + Vc - Va) >> 1;
      v->Tb_SVPWM = v->Ta_SVPWM - Vc;
      v->Tc = v->Tb_SVPWM + Va;
      break;
    case 4:
      v->Tc = (_IQ24(1.0) + Va - Vc) >> 1;
      v->Tb_SVPWM = v->Tc - Va;
      v->Ta_SVPWM = v->Tb_SVPWM + Vc;
      break;
    case 5:
      v->Tb_SVPWM = (_IQ24(1.0) - Va + Vb) >> 1;
      v->Tc = v->Tb + Va;
      v->Ta_SVPWM = v->Tc - Vb;
      break;
    case 6:
      v->Tc = (_IQ24(1.0) + Vb + Vc) >> 1;
      v->Ta_SVPWM = v->Tc - Vb;
      v->Tb_SVPWM = v->Ta_SVPWM - Vc;
      break;
  }

  v->Ta_SVPWM = _IQ(1.0) - (v->Ta_SVPWM << 1);
  v->Tb_SVPWM = _IQ(1.0) - (v->Tb_SVPWM << 1);
  v->Tc_SVPWM = _IQ(1.0) - (v->Tc_SVPWM << 1);

  if (!v->PWM_Type)
  {
    v->Ta = v->Ta_SVPWM;
    v->Tb = v->Tb_SVPWM ;
    v->Tc = v->Tc_SVPWM;
  }
  else
  {
    v->Min1 = (v->Ta_SVPWM < v->Tb_SVPWM)? v->Ta_SVPWM : v->Tb_SVPWM;
    v->Min2 = (v->Tb_SVPWM < v->Tc_SVPWM)? v->Tb_SVPWM : v->Tc_SVPWM;
    v->Min3 = (v->Min1 < v->Min2)? v->Min1 : v->Min2;

    v->Ta = v->Ta_SVPWM - v->Min3 - _IQ24mag(*v->Alpha, *v->Beta);
    v->Tb = v->Tb_SVPWM - v->Min3 - _IQ24mag(*v->Alpha, *v->Beta);
    v->Tc = v->Tc_SVPWM - v->Min3 - _IQ24mag(*v->Alpha, *v->Beta);
  }
}


