
void Init(void)
{
}

void Exec(void)
{
  float Delta;

  if (v->PrevIn >= 0)
  {
    Delta = *v->In - v->PrevIn;
    if (Delta < -0.5) { if (++v->Cnt >= v->Max) v->Cnt = 0; }
    if (Delta >  0.5) { if (--v->Cnt <  0)      v->Cnt = v->Max - 1; }
  }

  v->Out = ((float)v->Cnt + *v->In - v->Offs) / v->Max;
  if (v->Out >= 1.0) v->Out -= 1.0;
  if (v->Out <  0.0) v->Out += 1.0;

  if (*v->R != 0)
  {
    v->Offs = *v->In;
    v->Out  = 0;
    v->Cnt  = 0;
  }

  v->PrevIn = *v->In;
}

