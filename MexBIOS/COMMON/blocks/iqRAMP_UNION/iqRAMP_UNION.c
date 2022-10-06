
void Init(void)
{
}

void Exec(void)
{
  long Delta;

  if (v->PrevIn >= 0)
  {
    Delta = *v->In - v->PrevIn;
    if (Delta < _IQ24(-0.5)) { if (++v->Cnt >= v->Max) v->Cnt = 0; }
    if (Delta > _IQ24( 0.5)) { if (--v->Cnt <  0)      v->Cnt = v->Max - 1; }
  }

  v->Out = _IQ24div(v->Cnt, v->Max) + _IQ1div(*v->In - v->Offs, v->Max << 1);
  if (v->Out >= _IQ24(1.0)) v->Out -= _IQ24(1.0);
  if (v->Out <  _IQ24(0.0)) v->Out += _IQ24(1.0);

  if (*v->R != 0)
  {
    v->Offs = *v->In;
    v->Out  = 0;
    v->Cnt  = 0;
  }

  v->PrevIn = *v->In;
}

