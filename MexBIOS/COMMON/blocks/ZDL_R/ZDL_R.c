void Init(void)
{

}

void Exec(void)
{
  short i;
  long *Data = (long *)(*v->Buf);

 /* Delta = *v->Angle - v->PrevAngle;
  if (Delta < -0.5) Delta += 1.0;
  if (Delta >  0.5) Delta -= 1.0;
  v->PrevAngle = *v->Angle;
 */
/*
if (abs((*v->In - v->Signal))>_IQ24(0.5))
{

  Data[0] = 0;
   Data[1] = 0 ;
    Data[2] = 0;
     Data[3] = 0;
      Data[4] = 0;
  v->Signal = 0;
  v->Signal1 = 0;
  v->Signal2 = 0;
  v->Signal3 = 0;


  v->OutReset = 1;

return;
}*/
  v->OutReset = 0;
  Data[0] = *v->In;
  Data[1] = v->Signal;
  Data[2] = v->Signal1;
  Data[3] = v->Signal2;
  Data[4] = v->Signal3;



  v->Signal3 = v->Signal2;
  v->Signal2 = v->Signal1;
  v->Signal1 = v->Signal;
  v->Signal = *v->In;








}



