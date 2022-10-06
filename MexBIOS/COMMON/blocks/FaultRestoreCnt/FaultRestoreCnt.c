
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
long *CntTime  = (long *)(*v->CntTimeBuf);
long *CntRestores  = (long *)(*v->CntRestoresBuf);
v->j = 0;

v->ResetModFault = 0;
for (v->i = 0; v->i < 15; v->i++){
  if (*v->R) {
  CntTime[v->j] = 0;
  CntRestores[v->j] = 0;
  }
  if (((v->Mask & (0x1<<v->i)) != 0) && ((*v->ProtectWord & (0x1<<v->i)) == 0)){ // нет аварии
  if ((v->prevProtectWord &(0x1<<v->i)) != 0) CntTime[v->j] = 0;
  if (CntRestores[v->j] > 0)   CntTime[v->j] += v->SampleTime * (CntTime[v->j] <= v->ResetCntTime);
  if (CntTime[v->j] >= v->ResetCntTime ) CntRestores[v->j] = 0;
  }
  if (((v->Mask & (0x1<<v->i)) != 0) && ((*v->ProtectWord & (0x1<<v->i)) != 0)){ // Есть авария
    if ((v->prevProtectWord &(0x1<<v->i)) == 0) {
      CntTime[v->j]  = 0;
     if (CntRestores[v->j] < 50)   CntRestores[v->j]++;             // однократное инкрементация счетчика аварии
    }
      if (CntTime[v->j] < v->RestorePWMCoolDown)
        CntTime[v->j] += v->SampleTime ;
      else v->ResetModFault = 1;
  }
  if ( CntRestores[v->j] >= v->ResetCntBlock ) v->ResetModFault = 0;
  if ((v->Mask & (0x1<<v->i)) != 0) v->j++;
}

v->prevProtectWord = *v->ProtectWord;

}

