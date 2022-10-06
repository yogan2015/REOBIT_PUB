
#include "strutils.h"

void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->Buf) decToStr((void *)*v->Buf, *v->In, v->Offset, v->Precision, v->Digits, v->TrailZeros);
}


