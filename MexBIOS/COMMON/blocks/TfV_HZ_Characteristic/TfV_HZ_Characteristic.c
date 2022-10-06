

static float Interpolation (BLOCK_STRUCT *v, float *DataY, float *DataX, float X)
{
float *CurDataX, *CurDataY;
float Y;
short i;

CurDataX = DataX;
CurDataY = DataY;


if (CurDataX[0]>CurDataX[v->BuffMax-1])
{
  if (X >= DataX[0]) { Y = DataY[0]; return Y; }
  if (X <= CurDataX[(v->BuffMax-1)]) {Y = CurDataY[(v->BuffMax-1)]; return Y; }
}
else
{
  if (X <= DataX[0]) { Y = DataY[0]; return Y; }
  if (X >= CurDataX[(v->BuffMax-1)]) {Y = CurDataY[(v->BuffMax-1)]; return Y; }
}


if       ((X <= CurDataX[0]) && (X <= CurDataX[v->BuffMax-1])) {Y = DataY[0]; return Y; }
else if  ((X >= CurDataX[0]) && (X >= CurDataX[v->BuffMax-1])) {Y = DataY[0]; return Y; }

if       ((X >= CurDataX[v->BuffMax-1]) && (X >= CurDataX[0])){Y = CurDataY[v->BuffMax-1]; return Y; }
else if  ((X <= CurDataX[v->BuffMax-1]) && (X <= CurDataX[0])){Y = CurDataY[v->BuffMax-1]; return Y; }

for (i = 1; i < v->BuffMax; i++)
{
  if (
      ((X <= CurDataX[1])&&(X > CurDataX[0]))
      ||
      ((X <= CurDataX[0])&&(X > CurDataX[1]))
     )
      break;
  CurDataX += 1;
  CurDataY += 1;
}
Y = CurDataY[0] + (X - CurDataX[0]) * (CurDataY[1] - CurDataY[0]) /  (CurDataX[1] - CurDataX[0]);
return Y;
}


void Init(void)
{

}

void Exec(void)
{
  float *DataU = (float *)*v->Buff_U;
  float *DataF = (float *)*v->Buff_F;
  float *DataT = (float *)*v->Buff_T;
  float Upoint;
  if ((*v->En) && (!v->pEn))
  {
    Upoint = Interpolation(v, DataU, DataF, *v->Fref);
//    Fpoint = Interpolation(v, DataF, DataU, *v->Uref);
    if (
        ((*v->Uref) >= DataU[0])
        &&
        ((*v->Fref) >= DataF[0])
       )
    {  // Fref > Fpoint && Uref > Upoint
      v->StartTime = 0.0;
      v->FmaxOut   = *v->Fmax;
      v->UmaxOut   = *v->Umax;
    }
    else if ((*v->Uref) >= Upoint)
    {  // Uref>Upoint
      v->StartTime = Interpolation(v, DataT, DataU, *v->Uref);
      v->FmaxOut   = *v->Fref;
      v->UmaxOut   = *v->Umax;
    }
    else if ((*v->Uref) < Upoint)
    {  // Fref>Fpoint
      v->StartTime = Interpolation(v, DataT, DataF, *v->Fref);
      v->FmaxOut   = *v->Fmax;
      v->UmaxOut   = *v->Uref;
    }
    else
    { // Fref < Fpoint && Uref < Upoint
      v->StartTime = DataT[v->BuffMax-1];
      v->FmaxOut   = *v->Fmax;
      v->UmaxOut   = *v->Uref;
    }
  }
 v->pEn=*v->En;
}


