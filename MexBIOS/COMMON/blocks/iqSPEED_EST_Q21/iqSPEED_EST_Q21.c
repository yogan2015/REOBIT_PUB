
#define DIFF_MAX_LIMIT    _IQ24(0.50)

void Init(void)
{

}

void Exec(void)
{
  _iq Temp, tc;

  if ((*v->fb != v->Prevfb) || (v->fc != v->Prevfc))
  {

    tc        = _IQ24div(_IQ24(1.0), _IQ24mpy(v->fc, _IQ(6.283185)));
    v->K1     = _IQ21div(_IQ21(1.0), _IQ21mpy(*v->fb, v->SampleTime >> 3));
    v->K2     = _IQ24div(tc, tc + v->SampleTime);
    v->K3     = _IQ24div(v->SampleTime, tc + v->SampleTime);
    v->Prevfb = *v->fb;
    v->Prevfc = v->fc;
  }

  // Synchronous speed computation
  Temp = *v->th - v->OldTheta;
  if (Temp < -DIFF_MAX_LIMIT) Temp = Temp + _IQ24(1.0);
  if (Temp >  DIFF_MAX_LIMIT) Temp = Temp - _IQ24(1.0);
  Temp = _IQ24mpy(v->K1, Temp << 3);

  // Low-pass filter
  v->Speed = _IQ24mpy(v->K2, v->Speed) + _IQ24mpy(v->K3, Temp);


  // Update the electrical angle
  v->OldTheta = *v->th;
}



