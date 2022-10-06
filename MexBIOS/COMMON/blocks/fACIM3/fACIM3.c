
#include "fMotor.h"

void Init(void)
{
}

void Exec(void)
{
  #define SQRT3  1.73205080756887729352744634
  struct TFMOTOR *m = (struct TFMOTOR *)(*v->Buf);
  if (!m) return;

  if ( v->w >=  9999) { v->w =  9999; return; }
  if (-v->w <= -9999) { v->w = -9999; return; }

  // Currents of stator
  v->di_sa = (*v->Ua - v->ia * m->Rs + m->Lm * (0.5 * (v->di_sb + v->di_sc) - v->di_ra + 0.5 * (v->di_rb + v->di_rc))) / m->Ls;
  v->ia    = v->ia + v->di_sa * v->SampleTime;

  v->di_sb = (*v->Ub - v->ib * m->Rs + m->Lm * (0.5 * (v->di_sa + v->di_sc) - v->di_rb + 0.5 * (v->di_ra + v->di_rc))) / m->Ls;
  v->ib    = v->ib + v->di_sb * v->SampleTime;

  v->di_sc = (*v->Uc - v->ic * m->Rs + m->Lm * (0.5 * (v->di_sb + v->di_sa) - v->di_rc + 0.5 * (v->di_rb + v->di_ra))) / m->Ls;
  v->ic    = v->ic + v->di_sc * v->SampleTime;

  //  lux of rotor
  v->f_ra = m->Lr * v->i_ra + m->Lm * ((v->ia - 0.5 * v->ib - 0.5 * v->ic) - 0.5 * (v->i_rb + v->i_rc));
  v->f_rb = m->Lr * v->i_rb + m->Lm * ((v->ib - 0.5 * v->ia - 0.5 * v->ic) - 0.5 * (v->i_ra + v->i_rc));
  v->f_rc = m->Lr * v->i_rc + m->Lm * ((v->ic - 0.5 * v->ib - 0.5 * v->ia) - 0.5 * (v->i_rb + v->i_ra));

  // EMF rotor
  v->e_rc = (v->f_ra - v->f_rb) * v->w / SQRT3 * 2.0 * m->Zp * m->Lr;
  v->e_rb = (v->f_rc - v->f_ra) * v->w / SQRT3 * 2.0 * m->Zp * m->Lr;
  v->e_ra = (v->f_rb - v->f_rc) * v->w / SQRT3 * 2.0 * m->Zp * m->Lr;

  // Rotor currents
  v->di_ra = (( - v->i_ra * m->Rr + m->Lm * (0.5 * (v->di_rb + v->di_rc) - v->di_sa + 0.5 * (v->di_sb + v->di_sc)) - v->e_ra) / m->Lr);
  v->i_ra  = v->i_ra + v->di_ra * v->SampleTime;

  v->di_rb = (( - v->i_rb * m->Rr + m->Lm * (0.5 * (v->di_ra + v->di_rc) - v->di_sb + 0.5 * (v->di_sa + v->di_sc)) - v->e_rb) / m->Lr);
  v->i_rb  = v->i_rb + v->di_rb * v->SampleTime;

  v->di_rc = (( - v->i_rc * m->Rr + m->Lm * (0.5 * (v->di_ra + v->di_rb) - v->di_sc + 0.5 * (v->di_sa + v->di_sb)) - v->e_rc) / m->Lr);
  v->i_rc  = v->i_rc + v->di_rc * v->SampleTime;

  // Torque
  v->M  = (SQRT3 / 2.0 * m->Zp * m->Lm * (v->ia * v->i_rc + v->ib * v->i_ra + v->ic * v->i_rb - v->ia * v->i_rb - v->ib * v->i_rc - v->ic * v->i_ra));
  v->dw = (v->M - (*v->Mc) - m->B * v->w) / m->J;
  v->w  = v->w + v->dw * v->SampleTime;

  if (v->Brake) v->w = 0;

  v->psi_ra = v->f_ra;
  v->psi_rb = (v->f_rb * 2.0 + v->f_ra) / SQRT3;
  
  if ((v->psi_ra == 0) && (v->psi_rb == 0)) v->theta = 0;
  else v->theta = atan2pu(v->psi_rb, v->psi_ra);
}


