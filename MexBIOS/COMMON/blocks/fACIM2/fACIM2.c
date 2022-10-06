
#include "fMotor.h"

void Init(void)
{
}

void Exec(void)
{
  double Kr, Re, Le, Ar;
  struct TFMOTOR *m = (struct TFMOTOR *)(*v->Buf);
  if (!m) return;

  if ( v->w >=  9999) { v->w =  9999; return; }
  if (-v->w <= -9999) { v->w = -9999; return; }

  Kr = m->Lm / m->Lr;
  Re = m->Rs + m->Rr * Kr * Kr;
  Le = m->Ls - m->Lm * m->Lm / m->Lr;
  Ar = m->Rr / m->Lr;

  v->ia = v->ia + 1.0 / Le * (*v->Ua - Re * v->ia + Kr * Ar * v->f_ra + Kr * m->Zp * v->w * v->f_rb) * v->SampleTime;
  v->ib = v->ib + 1.0 / Le * (*v->Ub - Re * v->ib + Kr * Ar * v->f_rb - Kr * m->Zp * v->w * v->f_ra) * v->SampleTime;

  v->f_ra = v->f_ra + (m->Rr * Kr * v->ia - Ar * v->f_ra - v->w * m->Zp * v->f_rb) * v->SampleTime;
  v->f_rb = v->f_rb + (m->Rr * Kr * v->ib - Ar * v->f_rb + v->w * m->Zp * v->f_ra) * v->SampleTime;

  v->M = 1.5 * m->Zp * Kr * (v->f_ra * v->ib - v->f_rb * v->ia);
  v->w = v->w + 1.0 / m->J * (v->M - (*v->Mc) - m->B * v->w) * v->SampleTime;
  if (v->Brake) v->w = 0;

  if ((v->f_ra == 0) && (v->f_rb == 0)) v->theta = 0;
  else v->theta = atan2pu(v->f_rb, v->f_ra);
}


