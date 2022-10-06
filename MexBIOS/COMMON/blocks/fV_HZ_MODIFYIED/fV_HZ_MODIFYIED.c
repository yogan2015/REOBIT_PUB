// List PDO_RX //
#define _FREQ(__index__)       (0+(__index__-1)*2)
#define _VOLT(__index__)       (1+(__index__-1)*2)


void Init(void)
{

}

void Exec(void)
{
  int i;
  float *Data = (float *)*v->Buff;
  // Take absolute frequency to allow the operation of both rotational directions
 if (
     (*v->Fmin != v->prevFmin)
     ||
     (*v->Fmax != v->prevFmax)
     ||
     (*v->VoltMin != v->prevVoltMin)
     ||
     (*v->VoltMax != v->prevVoltMax)
     ||
     (*v->Flim != v->prevFlim)
     ||
     (*v->Exp != v->prevExp)
    )
 {
   Data[_FREQ(1)] = *v->Fmin;
   Data[_VOLT(1)] = *v->VoltMin;
   Data[_FREQ(v->BuffMax)]= *v->Fmax;
   Data[_VOLT(v->BuffMax)] = *v->VoltMax;

   v->step = (*v->Fmax - *v->Fmin) / __IQtoF(v->BuffMax - 1,0);
   v->freq = *v->Fmin;
   for (i=2; i < v->BuffMax; ++i)
   {
     v->freq = v->freq + v->step;
     Data[_FREQ(i)] = v->freq;
     Data[_VOLT(i)] = *v->VoltMin + (*v->VoltMax  - *v->VoltMin) * (powf(((v->freq - *v->Fmin) / (*v->Fmax-*v->Fmin)), *v->Exp));
   }
    v->prevFmin = *v->Fmin;
    v->prevFmax = *v->Fmax;
    v->prevVoltMin = *v->VoltMin;
    v->prevVoltMax = *v->VoltMax;
    v->prevFlim = *v->Flim;
    v->prevExp = *v->Exp;
 }
}


