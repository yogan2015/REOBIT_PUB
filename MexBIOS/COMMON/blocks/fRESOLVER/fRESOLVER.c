
void Init(void)
{
}

void Exec(void)
{
  float Temp;

  if ((*v->SinIn == 0) && (*v->CosIn == 0)) v->mTheta = 0;
  else v->mTheta = atan2pu(*v->SinIn, *v->CosIn);

  Temp = (v->mTheta * v->Np) + (*v->Offs);
  while (Temp > 1.0) Temp = Temp - 1.0;
  v->eTheta = Temp;

  Temp = v->mTheta - v->Theta;
  if (Temp < -0.5) v->Rev++;
  if (Temp >  0.5) v->Rev--;
  v->Theta = v->mTheta;

  if ((short)*v->R) { v->Pos = 0; v->Rev = 0; }
  else { v->Pos = (v->Rev << v->PosPrecision) + (long)(v->mTheta * (1L << v->PosPrecision)); }
}



