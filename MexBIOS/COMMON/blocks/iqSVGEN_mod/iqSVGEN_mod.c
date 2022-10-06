
void Init(void)
{
}

void Exec(void)
{
  long Ka, Kb;
  long Va, Vb, Vc;
  long Sector = 0;
  long Sine;
  long Cosine;
  long Alpha;
  long Beta;

  Sine   = _IQ24sinPU(*v->Angle);
  Cosine = _IQ24cosPU(*v->Angle);

  Alpha = _IQ24mpy(*v->Ds, Cosine) - _IQ24mpy(*v->Qs, Sine);
  Beta  = _IQ24mpy(*v->Qs, Cosine) + _IQ24mpy(*v->Ds, Sine);

  Ka = _IQ24mpy(Alpha, _IQ24(0.86602540378443864676372317));
  Kb = Beta >> 1;

  Va = Beta;
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
}


