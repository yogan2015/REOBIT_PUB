
void Init(void)
{

}

void Exec(void)
{
  long *Data = (long *)*v->Buf, *CurData;
  short i;

  if (!Data || (v->NumPoints < 2)) return;

  if (*v->X <= Data[0]) { v->Y = Data[1]; return; }

  CurData = &Data[(v->NumPoints-1)<<1];
  if (*v->X >= CurData[0]) { v->Y = CurData[1]; return; }

  CurData = Data;
  for (i = 1; i < v->NumPoints; i++) {
    if (*v->X <= CurData[2]) break;
    CurData += 2;
  }

  v->Y = CurData[1] + __IQdiv(__IQmpy(*v->X - CurData[0], CurData[3] - CurData[1], v->Format), CurData[2] - CurData[0], v->Format);
}



