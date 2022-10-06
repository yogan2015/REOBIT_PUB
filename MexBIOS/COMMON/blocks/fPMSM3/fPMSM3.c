
#include "fMotor.h"

void Init(void)
{
}

void Exec(void)
{
  double l_s, l_x;
  double l_aa, l_bb, l_cc;
  double l_ab, l_ac, l_bc;
  double i_x, i_y, f_rx, f_ry;
  struct TFMOTOR *m = (struct TFMOTOR *)(*v->Buf);
  if (!m) return;

  if ( v->w >=  9999) { v->w =  9999; return; }
  if (-v->w <= -9999) { v->w = -9999; return; }

  v->time = v->time + v->SampleTime;

  l_s = 0.5 * (m->Lr + m->Ls);
  l_x = 0.5 * (m->Lr - m->Ls);

  l_aa = l_s + l_x * cos(v->th);
  l_bb = l_s + l_x * cos(v->th + (2.0 * M_PI / 3.0));
  l_cc = l_s + l_x * cos(v->th - (2.0 * M_PI / 3.0));

  l_ab =  0.5 * l_s + l_x * cos(2 * v->th - (2.0 * M_PI / 3.0));
  l_bc =  0.5 * l_s + l_x * cos(2 * v->th );
  l_ac =  0.5 * l_s + l_x * cos(2 * v->th + 2.0* M_PI / 3.0);

  v->di_a = (v->SampleTime / l_aa) * (*v->Ua - m->Rs * v->ia + m->PsiR * v->w * sin(v->th)) - (l_ab / l_aa) * v->di_b - (l_ac / l_aa) * v->di_c;
  v->ia   = v->ia + v->di_a;

  v->di_b = (v->SampleTime / l_bb) * (*v->Ub - m->Rs * v->ib - 0.5 * m->PsiR * v->w * (sin(v->th) + 1.732 * cos(v->th))) - (l_ab / l_bb) * v->di_a - (l_bc / l_bb) * v->di_c;
  v->ib   = v->ib + v->di_b;

  v->di_c = (v->SampleTime / l_cc) * (*v->Uc - m->Rs * v->ic - 0.5 * m->PsiR * v->w * (sin(v->th) - 1.732 * cos(v->th))) - (l_ac / l_cc) * v->di_a - (l_bc / l_cc) * v->di_b;
  v->ic   = v->ic + v->di_c;

  v->f_ra = l_aa * v->ia + l_ab * v->ib + l_ac * v->ic + m->PsiR * cos(v->th);
  v->f_rb = l_ab * v->ia + l_bb * v->ib + l_bc * v->ic + m->PsiR * cos(v->th - 2.0* M_PI / 3.0);
  v->f_rc = l_ac * v->ia + l_bc * v->ib + l_cc * v->ic + m->PsiR * cos(v->th + 2.0* M_PI / 3.0);

  i_x = v->ia - 0.5 * (v->ic + v->ib);
  i_y = 1.73205 * (v->ib - v->ic);

  f_rx = v->f_ra - 0.5 * (v->f_rc + v->f_rb);
  f_ry = 1.73205 * (v->f_rb - v->f_rc);
  v->f_r  = sqrt(f_rx * f_rx + f_ry * f_ry);

  v->M = 1.5 * m->Zp * (i_y * f_rx - i_x * f_ry);
  v->w = v->w + v->SampleTime * (v->M - (*v->Mc) - m->B * v->w)/ m->J;

  if (v->Brake) v->w = 0;

  if (v->time <= 2 * v->SampleTime) v->th = v->th + *v->th0;
  else v->th = v->th + m->Zp * v->w * v->SampleTime;
  if (v->th > (2.0 * M_PI)) v->th = v->th - (2.0 * M_PI);
  if (v->th < 0.0) v->th = v->th + (2.0 * M_PI);

  v->theta = v->th / (M_PI * 2.0) + 1;
  if (v->theta >= 1.0) v->theta = v->theta - 1.0;
  if (v->theta <= 0.0) v->theta = v->theta + 1.0;
}




