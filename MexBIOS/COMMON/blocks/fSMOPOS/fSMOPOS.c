
#define E0  0.5

void Init(void)
{
}

void Exec(void)
{
  float Va = *v->Valpha;
  float Vb = *v->Vbeta;
  float IalphaError;
  float IbetaError;

  if ((short)*v->SignWr > 0) { Va = -Va; Vb = -Vb; }

  // Sliding mode current observer
  v->EstIalpha = (v->Fsmopos * v->EstIalpha) + (v->Gsmopos * (Va - v->Ealpha - v->Zalpha));
  v->EstIbeta  = (v->Fsmopos * v->EstIbeta)  + (v->Gsmopos * (Vb - v->Ebeta  - v->Zbeta));

  // Current errors
  IalphaError = v->EstIalpha - (*v->Ialpha);
  IbetaError  = v->EstIbeta  - (*v->Ibeta);

  // Sliding control calculator
  if (fabs(IalphaError) < E0)
    v->Zalpha = v->Kslide * (IalphaError / E0);
  else if (IalphaError >= E0)
    v->Zalpha = v->Kslide;
  else if (IalphaError <= -E0)
    v->Zalpha = -v->Kslide;

  if (fabs(IbetaError) < E0)
    v->Zbeta = v->Kslide * (IbetaError / E0);
  else if (IbetaError >= E0)
    v->Zbeta = v->Kslide;
  else if (IbetaError <= -E0)
    v->Zbeta = -v->Kslide;

  // Sliding control filter -> back EMF calculator
  v->Ealpha = v->Ealpha + v->Kslf * (v->Zalpha - v->Ealpha);
  v->Ebeta  = v->Ebeta  + v->Kslf * (v->Zbeta  - v->Ebeta);

  // Rotor angle calculator -> Theta = atan(-Ealpha,Ebeta)
  if ((v->Ealpha == 0) && (v->Ebeta == 0)) v->Theta = 0;
  else v->Theta = atan2pu(-v->Ealpha, v->Ebeta);
}


