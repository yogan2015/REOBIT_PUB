
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int dif_pos, dif_neg, dif, spdSign;
  int dif_limit;
  // расчет разности положений
  dif = v->pPos - *v->Pos;
  if (dif > 0)
  {
    dif_pos = dif;
    if (dif_pos > v->spdMax)
    {
      dif_pos = v->spdMax;
    }
  } else {dif_pos = 0;}
  if (dif <= 0)
  {
    dif_neg = dif;
    if (dif_neg < -v->spdMax)
    {
      dif_pos = -v->spdMax;
    }
  } else {dif_neg = 0;}
  v->pPos = *v->Pos;

  // расчет знаковой скорости
  if (*v->reverse)
  {
    spdSign = (*v->Spd);
  } else {
    spdSign = (*v->Spd - 65536);
  }
  dif_limit = spdSign >> 2;

  // детектирование ошибки
  v->error = ((dif_pos < dif_limit) && (!*v->reverse)) || ((dif_neg > -dif_limit) && (*v->reverse));

  // расчет добавки по скорости
  if (v->error)
  {
    v->delt += spdSign >> 1;
  } else {
    v->delt = 0;
  }

  // применение компенсация
  if (*v->enable)
  {
    v->IntPos = *v->Pos + v->delt;
  } else {
    v->IntPos = *v->Pos;
  }
}
