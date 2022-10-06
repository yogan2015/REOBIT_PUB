
void Init(void)
{

}

void Exec(void)
{
  float *DataX = (float *)*v->Buf_X, *CurDataX;
  float *DataY = (float *)*v->Buf_Y, *CurDataY;
  short i;

if (*v->En)
{
  if ((!DataX) || (!DataY) || (v->NumPoints < 2)) return;

  if (*v->X <= DataX[0]) { v->Y = DataY[0]; return; }

  CurDataX = &DataX[(v->NumPoints-1)];
  CurDataY = &DataY[(v->NumPoints-1)];

  if (*v->X >= CurDataX[0]) { v->Y = CurDataY[0]; return; }

  CurDataX = DataX;
  CurDataY = DataY;
  for (i = 1; i < v->NumPoints; i++) {
    if (*v->X <= CurDataX[1]) break;
    CurDataX += 1;
    CurDataY += 1;
  }

  v->Y = CurDataY[0] + (*v->X - CurDataX[0]) * (CurDataY[1] - CurDataY[0]) /  (CurDataX[1] - CurDataX[0]);
}
}



