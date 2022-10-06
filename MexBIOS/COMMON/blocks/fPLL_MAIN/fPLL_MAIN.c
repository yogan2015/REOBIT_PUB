// Do not initialize inputs!
#define FORWARD_EULER 0
#define BACKWARD_EULER 1
#define TRAPEZOIDAL 2

void Init(void)
{

}

void Exec(void)
{
  float Up1, Out1, Ud;
  if ((short)*v->R)
  {
    v->Ui = 0;
    v->Up = 0;
    v->Freq = 0;
    v->fPrevAngle = 0;
    v->fAngle = 0;
    v->Angle = 0;
    v->Freq = 0;
    v->prevFreq = 0;
    return;
  }
  //Регулятор. Выход регулятора - частота
  Up1   = v->Kp * (*v->In);
  v->Ui = v->Ui + v->Ki * Up1 + v->Kc * v->SatErr;
  Ud    = v->Kd * (Up1 - v->Up);
  Out1  = Up1 + v->Ui + Ud;
  v->Freq = Out1;
  if (v->Freq > v->Max) v->Freq = v->Max;
  if (v->Freq < v->Min) v->Freq = v->Min;
  v->SatErr = v->Freq - Out1;
  v->Up = Up1;
  //Интегратор. Выход интегратора - угловое положение вектора напряжений
  switch (v->Integrator_Type)
  {
    case FORWARD_EULER:
    v->fAngle = __IQtoF(__IQ(v->fPrevAngle + (v->SampleTime * v->prevFreq ), 30) % __IQ(1, 30), 30);
    v->fPrevAngle = v->fAngle;
    v->prevFreq = v->Freq;
    break;

    case BACKWARD_EULER:
    v->fAngle = __IQtoF(__IQ(v->fPrevAngle + (v->SampleTime * v->Freq ), 30) % __IQ(1, 30), 30);
    v->fPrevAngle = v->fAngle;
    break;

    case TRAPEZOIDAL:
    // Trapeziodal: y(n) = y(n-1) + K*[t(n)-t(n-1)]*[u(n)+u(n-1)]/2
    v->fAngle = __IQtoF(__IQ(v->fPrevAngle + 0.5*(v->SampleTime * (v->Freq + v->prevFreq)), 30) % __IQ(1, 30), 30);
    v->fPrevAngle = v->fAngle;
    v->prevFreq = v->Freq;
    break;
   }
  // Компенсация фазы -30 градусов (параметр Offset) и компенсация задержки в расчете (параметр DelayCorrect)
  v->Angle = __IQtoF(__IQ((v->fAngle + v->Offset + (v->BaseFreq * v->DelayCorrect)) , 30) % __IQ(1, 30), 30);
}

