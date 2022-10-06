
#include "fMotor.h"

void Init(void)
{
}

void Exec(void)
{
  struct TFMOTOR *m = (struct TFMOTOR *)(*v->Buf);
  if (!m) return;

  if ( v->w >=  9999) { v->w =  9999; return; }
  if (-v->w <= -9999) { v->w = -9999; return; }

  v->i = v->i + (*v->Udc - m->Rs * v->i - m->C * v->w) / m->Ls * v->SampleTime;
  v->M = v->i * m->C;
  v->w = v->w + (v->M - (*v->Mc) - m->B * v->w) / m->J * v->SampleTime;

  if (v->Brake) v->w = 0;

  v->pos = v->pos + v->w * v->SampleTime;
}

