
void Init(void)
{
}

void Exec(void)
{
  long Delta;
   if (*v->R != 0)
  {
    //v->Offs = *v->In;
    v->Out  = 0;
    v->Cnt  = 0;
  return;
  }
  if (!v->StartOffset)
  {
    if (*v->In > _IQ24(0.5))
    {
      v->Cnt = _IQ24(-0.1);
    }
    else
    {
      v->Cnt = 0;
    }
    v->StartOffset = 1;
  }
  if (v->PrevIn > 0)
  {
    Delta = *v->In - v->PrevIn;
    if (Delta < _IQ24(-0.5))
      {
        v->Cnt=v->Cnt+_IQ24(1.0);
        if (v->Cnt >= v->Max)            v->Cnt = 0;
      }
    if (Delta > _IQ24( 0.5))
      {
        v->Cnt=v->Cnt-_IQ24(1.0);
        if (v->Cnt <  (- (v->Max)))      v->Cnt = v->Max - 1;
      }
  }
  v->Out = v->Cnt + *v->In ;
  if (v->Out >= _IQ24(1.0)) v->Out -= _IQ24(1.0);
  if (v->Out <  _IQ24(0.0)) v->Out += _IQ24(1.0);
  v->PrevIn = *v->In;
}

