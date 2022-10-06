
void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->R)
  {
    v->Timer1 = 0;
    v->OffsetA = 0;
    v->IntegralA = v->StartOffset;
    v->En = 1;
  }

  v->Timer1++;
  if (v->Timer1 <= v->TimeOfsCalc)
  {
    v->IntegralA = v->IntegralA + (*v->In);
    v->Out = 0;
    v->En = 1;
    if (v->Timer1 == v->TimeOfsCalc) v->OffsetA = v->IntegralA / v->Timer1;
  }
  else
  {
    v->En = 0;
    v->Out = (*v->In - v->OffsetA) * v->GainA;
  }
}
