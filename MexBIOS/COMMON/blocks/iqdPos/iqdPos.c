
void Init(void)
{
}

void Exec(void)
{
  long Temp;


  Temp = *v->mTheta - v->Theta;
  if (Temp < _IQ24(-0.5)) v->Rev++;
  if (Temp > _IQ24( 0.5)) v->Rev--;
  v->Theta = (*v->mTheta);

  if ((short)*v->R) { v->Pos = 0; v->Rev = 0; }
  else { v->Pos = (v->Rev << v->PosPrecision) + ((*v->mTheta) >> (24 - v->PosPrecision)); }
}



