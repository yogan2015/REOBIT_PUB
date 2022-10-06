
void Init(void)
{

}

void Exec(void)
{
  long *Data = (long *)*v->Buf, *CurData, *CurData_Prev;

  if (!Data || (v->NumPoints < 2)) return;

  if (*v->X <= Data[0]) { v->Y = Data[1]; return; }

  CurData = &Data[(v->NumPoints-1)<<1];
  if (*v->X >= CurData[0]) { v->Y = CurData[1]; return; }

  CurData = Data + ((v->RealPoint - 1) * 2);

  if (*v->X <= CurData[2])
  {
    if(CurData > Data)
    {
      CurData_Prev = CurData - 2;

      if(*v->X <= CurData_Prev[2])
      {
        v->RealPoint--;

        if(v->RealPoint < 0)
        {
          v->RealPoint = 0;
        }
      }
    }
  }
  else
  {
    v->RealPoint++;

    if(v->RealPoint > v->NumPoints)
    {
      v->RealPoint = v->NumPoints;
    }
  }

  v->Y = CurData[1] + __IQdiv(__IQmpy(*v->X - CurData[0], CurData[3] - CurData[1], v->Format), CurData[2] - CurData[0], v->Format);
}



