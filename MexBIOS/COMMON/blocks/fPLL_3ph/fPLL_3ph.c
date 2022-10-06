// Do not initialize inputs!
#define FORWARD_EULER 0
#define BACKWARD_EULER 1
#define TRAPEZOIDAL 2

void Init(void)
{

}

void Exec(void)
{
  float Sine, Cosine, Up1, Out1, Ud;
  Sine   = sinf(v->Angle_inn * 2*M_PI);
  Cosine = cosf(v->Angle_inn * 2*M_PI);

  if ((short)*v->R)
  {
    v->Ualpha = 0;
    v->Ubeta  = 0;
    v->Ud_ = 0;
    v->Uq_ = 0;
    v->Ud_ff = 0;
    v->Uq_ff = 0;
    v->Mag = 0;
    v->Ui = 0;
    v->Up = 0;
    v->Freq = 0;
    v->fPrevAngle = 0;
    v->fAngle = 0;
    v->Angle = 0;
    v->Angle_inn = 0;
    v->Freq = 0;
    v->prevFreq = 0;
    return;
  }

  //A-B-C to alpha-beta
  v->Ualpha = (*v->Uab * 0.66666666666667) -  (*v->Ubc * 0.33333333333333) -  (*v->Uca * 0.33333333333333);
  v->Ubeta  = (*v->Ubc * 0.57735026918963) -  (*v->Uca * 0.57735026918963);

  //Расчет амплитуды вектора напряжений
  v->Mag = sqrtf((v->Ualpha * v->Ualpha) + (v->Ubeta * v->Ubeta));
  if (v->Mag >= 1500) v->Mag = 1500;
  if (v->Mag <= 10) v->Mag = 10;

  //alpha-beta to d-q-0 90 degrees behind phase A
  v->Ud_ = ((v->Ualpha * Sine) - (v->Ubeta * Cosine))/(v->Mag);
  v->Uq_ = ((v->Ualpha * Cosine) + (v->Ubeta * Sine))/(v->Mag);

  //Регулятор. Выход регулятора - частота
  Up1   = v->Kp * (0.0 - v->Uq_);
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

    v->Angle_inn = v->fAngle; //угол для внутернних координатных преобразований PLL


  // Компенсация фазы -30 градусов (параметр Offset) и компенсация задержки в расчете (параметр DelayCorrect)
  v->Angle = __IQtoF(__IQ((v->Angle_inn + v->Offset + (v->BaseFreq * v->DelayCorrect)) , 30) % __IQ(1, 30), 30);

  //Масштабирование выходных сигналов. Приведение к о.е. относительно напряжения в DC-шине инвертора.
  v->Ud_ff = (v->Mag * v->Ud_ * 1.154700538379)/(*v->Udc);
  v->Uq_ff = (v->Mag * v->Uq_ * 1.154700538379)/(*v->Udc);

}

