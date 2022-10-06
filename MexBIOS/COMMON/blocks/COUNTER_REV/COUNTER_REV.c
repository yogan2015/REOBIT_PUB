
void Init(void)
{
  v->D = v->StartValue;
}

void Exec(void)
{
  short Flag = 0, CntV = (short)*v->Cnt;

  if ((short)*v->R) v->D = v->StartValue;

  switch(v->Mode)
  {
    case 1: if ( CntV && !v->Cnt_1) Flag = 1; break;
    case 2: if (!CntV &&  v->Cnt_1) Flag = 1; break;
    case 3: if ((CntV && !v->Cnt_1) || (!CntV && v->Cnt_1)) Flag = 1; break;
  }
  v->Cnt_1 = CntV;

  if (Flag)
  {
    if (!(short)*v->Dir) v->D++; else v->D--;
  }

  if (!(short)v->Q && (v->D == v->Q_ON))  v->Q = 1;
  if ( (short)v->Q && (v->D == v->Q_OFF)) v->Q = 0;
}



