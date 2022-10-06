
#include "fMotor.h"

void Init(void)
{
}

void Exec(void)
{
  double PsiRa, PsiRb;
  struct TFMOTOR *m = (struct TFMOTOR *)(*v->Buf);
  if (!m) return;

  if ( v->w >=  9999) { v->w =  9999; return; }
  if (-v->w <= -9999) { v->w = -9999; return; }

  PsiRa = m->PsiR * cos(v->th);
  PsiRb = m->PsiR * sin(v->th);

  v->f_ra = m->Ls * v->ia + PsiRa;
  v->f_rb = m->Ls * v->ib + PsiRb;

  v->ia = v->SampleTime / m->Ls * (*v->Ua - m->Rs * v->ia + v->w * m->Zp * PsiRb) + v->ia;
  v->ib = v->SampleTime / m->Ls * (*v->Ub - m->Rs * v->ib - v->w * m->Zp * PsiRa) + v->ib;
  v->M  = 1.5 * m->Zp * (v->f_ra * v->ib - v->f_rb * v->ia);
  v->w  = v->SampleTime / m->J * (v->M - (*v->Mc) - m->B * v->w) + v->w;

  if (v->Brake) v->w = 0;

  v->time = v->time + v->SampleTime;
  if (v->time <=  2 * v->SampleTime) v->th = v->th + *v->th0;
  else v->th = v->th + m->Zp * v->w * v->SampleTime;

  if (v->th > (2 * M_PI)) v->th = v->th - (2 * M_PI);
  if (v->th < 0.0)        v->th = v->th + (2 * M_PI);

  v->theta = v->th / (2 * M_PI) + 1.0;
  if (v->theta >= 1.0) v->theta = v->theta - 1.0;
  if (v->theta <= 0.0) v->theta = v->theta + 1.0;
}



