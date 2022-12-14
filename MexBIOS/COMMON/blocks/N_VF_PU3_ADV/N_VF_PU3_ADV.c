
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
  int  uP;     //  пропорциональная составляющая
  int mS, mV;
  int dth;

 if (!(short)*v->nRST){
    v->piout  = 0;
    v->uI     = 0;
  }

  v->out_Mag = _IQ24mag(*v->in_A, *v->in_B);

  // циклический интегратор
  dth = *v->f + v->piout;
//  v->out_pi = v->piout;
//  v->out_dTh = dth;
  v->pr_Th += _IQ20mpy(dth, (v->Td >> 4)) << 4;
  if (v->pr_Th > 16777216)  v->pr_Th -= 16777216;
  if (v->pr_Th < 0)         v->pr_Th += 16777216;
  v->out_A = _IQ24cosPU(v->pr_Th);
  v->out_B = _IQ24sinPU(v->pr_Th);
  v->out_Th = v->pr_Th;


  // фазовый детектор
  v->out_delt= -(_IQ24mpy(v->out_B, *v->in_A) - _IQ24mpy(v->out_A, *v->in_B));

  //  ПИ-регулятор
  uP       = _IQ24mpy(v->kP, v->out_delt);
  v->uI     = v->uI + _IQ24mpy(v->kI, v->out_delt);
  v->uI = _IQsat(v->uI, v->kI,-v->kI);
  v->piout  = (uP + v->uI)>> 4;
  v->piout    = _IQsat(v->piout, v->df_max, -v->df_max);
}

