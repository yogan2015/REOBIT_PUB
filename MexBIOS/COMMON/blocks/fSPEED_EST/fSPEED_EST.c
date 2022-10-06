
#define DIFF_MAX_LIMIT    0.50

void Init(void)
{

}

void Exec(void)
{
  float Temp, tc;

  if ((v->fb != v->Prevfb )|| (v->fc != v->Prevfc))
  {
    tc        = 1.0 / (v->fc * 6.283185);
    v->K1     = 8.00059 / (v->fb * v->SampleTime);
    v->K2     = tc / (tc + v->SampleTime);
    v->K3     = v->SampleTime / (tc + v->SampleTime);
    v->Prevfb = v->fb;
    v->Prevfc = v->fc;
  }

  // Synchronous speed computation
  Temp = *v->Theta - v->OldTheta;
  if (Temp < -DIFF_MAX_LIMIT) Temp = Temp + 1.0;
  if (Temp >  DIFF_MAX_LIMIT) Temp = Temp - 1.0;
  Temp = v->K1 * Temp;

  // Low-pass filter
  v->Speed = v->K2 * v->Speed + v->K3 * Temp;
  if (v->Speed >  2.0) v->Speed =  2.0;
  if (v->Speed < -2.0) v->Speed = -2.0;

  // Update the electrical angle
  v->OldTheta = *v->Theta;
}



