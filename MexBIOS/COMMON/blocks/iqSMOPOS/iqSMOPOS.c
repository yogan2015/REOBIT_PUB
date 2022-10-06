
#define E0  _IQ24(0.5)

void Init(void)
{
}

void Exec(void)
{
  _iq Va = *v->Valpha;
  _iq Vb = *v->Vbeta;
  _iq IalphaError;
  _iq IbetaError;

  if ((short)*v->SignWr > 0) { Va = -Va; Vb = -Vb; }

  // Sliding mode current observer
  v->EstIalpha = _IQ24mpy(v->Fsmopos, v->EstIalpha) + _IQ24mpy(v->Gsmopos, Va - v->Ealpha - v->Zalpha);
  v->EstIbeta  = _IQ24mpy(v->Fsmopos, v->EstIbeta)  + _IQ24mpy(v->Gsmopos, Vb - v->Ebeta  - v->Zbeta);

  // Current errors
  IalphaError = v->EstIalpha - (*v->Ialpha);
  IbetaError  = v->EstIbeta  - (*v->Ibeta);

  // Sliding control calculator
  if (_IQabs(IalphaError) < E0)
    v->Zalpha = _IQ24mpy(v->Kslide, _IQ24div(IalphaError, E0));
  else if (IalphaError >= E0)
    v->Zalpha = v->Kslide;
  else if (IalphaError <= -E0)
    v->Zalpha = -v->Kslide;

  if (_IQabs(IbetaError) < E0)
    v->Zbeta = _IQ24mpy(v->Kslide, _IQ24div(IbetaError, E0));
  else if (IbetaError >= E0)
    v->Zbeta = v->Kslide;
  else if (IbetaError <= -E0)
    v->Zbeta = -v->Kslide;

  // Sliding control filter -> back EMF calculator
  v->Ealpha = v->Ealpha + _IQ24mpy(v->Kslf, v->Zalpha - v->Ealpha);
  v->Ebeta  = v->Ebeta  + _IQ24mpy(v->Kslf, v->Zbeta  - v->Ebeta);

  // Rotor angle calculator -> Theta = atan(-Ealpha,Ebeta)
  v->Theta = _IQ24atan2PU(-v->Ealpha, v->Ebeta);
}


