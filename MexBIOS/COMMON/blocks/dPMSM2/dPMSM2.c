
#include "dMotor.h"

void Init(void)
{
}

void Exec(void)
{
  double Psi_fa, Psi_fb;
  struct TDMOTOR *m = (struct TDMOTOR *)Buf;
  if (!m) return;

  if (w_ > 1000) { w = 9999; return; }

  Psi_fa=m->PsiR*cos(th);
  Psi_fb=m->PsiR*sin(th);

  Psi_a=m->Ls*ia_+Psi_fa;
  Psi_b=m->Ls*ib_+Psi_fb;

  ia_=SampleTime/m->Ls*(Ua-m->Rs*ia_+w_*m->Zp*Psi_fb)+ia_;
  ib_=SampleTime/m->Ls*(Ub-m->Rs*ib_-w_*m->Zp*Psi_fa)+ib_;
  M_=1.5*m->Zp*(Psi_a*ib_-Psi_b*ia_);
  w_=SampleTime/m->J*(M_-Mc)+w_;

  if (Brake) w_=0;

  time = time + SampleTime;
  if(time <= 2*SampleTime) th = th + th0;
  else th = th + m->Zp * w_ * SampleTime;

  if (th > (2*M_PI)) th = th - (2*M_PI);
  if (th < (0) )     th = th + (2*M_PI);

  theta_ = th/(2*M_PI)+1.0;
  if (theta_ >= 1.0) theta_ = theta_ - 1.0;
  if (theta_ <= 0.0) theta_ = theta_ + 1.0;

  w     = w_;
  M     = M_;
  f_ra  = Psi_a;
  f_rb  = Psi_b;
  ia    = ia_;
  ib    = ib_;
  theta = theta_;
}



