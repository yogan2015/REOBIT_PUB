
void Init(void)
{
}

void Exec(void)
{
if ((short)R){
  Timer1=0;
  OffsetA=0;
  IntegralA = StartOffset ;
  En = 1;
}

Timer1++;

if (Timer1 <= TimeOfsCalc){
    IntegralA = IntegralA + In;
    //на выходе 0
    Out = 0;
    En = 1;
	
    if (Timer1 == TimeOfsCalc){
      OffsetA = IntegralA/Timer1;
    }
}

else {
  En = 0;
  Out = (In - OffsetA)* GainA;
}

}
