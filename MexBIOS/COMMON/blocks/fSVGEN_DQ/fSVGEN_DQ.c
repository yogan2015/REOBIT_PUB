
void Init(void)
{
}

void Exec(void)
{
  float Ka, Kb;
  float Va, Vb, Vc;
  long  Sector = 0;

  Ka = *v->Alpha * 0.86602540378443864676372317;
  Kb = *v->Beta  * 0.5;

  Va = *v->Beta;
  Vb =  Ka - Kb;
  Vc = -Ka - Kb;

  if (Va > 0.0) Sector = 1;
  if (Vb > 0.0) Sector = Sector + 2;
  if (Vc > 0.0) Sector = Sector + 4;

  Vb =  Ka + Kb;
  Vc = -Ka + Kb;

  switch(Sector)
  {
    case 0:
      v->Ta = 0.5;
      v->Tb = 0.5;
      v->Tc = 0.5;
      break;
    case 1:
      v->Tb = (1.0 - Vc - Vb) * 0.5;
      v->Ta = v->Tb + Vc;
      v->Tc = v->Ta + Vb;
      break;
    case 2:
      v->Ta = (1.0 - Vb + Va) * 0.5;
      v->Tc = v->Ta + Vb;
      v->Tb = v->Tc - Va;
      break;
    case 3:
      v->Ta = (1.0 + Vc - Va) * 0.5;
      v->Tb = v->Ta - Vc;
      v->Tc = v->Tb + Va;
      break;
    case 4:
      v->Tc = (1.0 + Va - Vc) * 0.5;
      v->Tb = v->Tc - Va;
      v->Ta = v->Tb + Vc;
      break;
    case 5:
      v->Tb = (1.0 - Va + Vb) * 0.5;
      v->Tc = v->Tb + Va;
      v->Ta = v->Tc - Vb;
      break;
    case 6:
      v->Tc = (1.0 + Vb + Vc) * 0.5;
      v->Ta = v->Tc - Vb;
      v->Tb = v->Ta - Vc;
      break;
  }

  v->Ta = 1.0 - (v->Ta * 2.0);
  v->Tb = 1.0 - (v->Tb * 2.0);
  v->Tc = 1.0 - (v->Tc * 2.0);
}


