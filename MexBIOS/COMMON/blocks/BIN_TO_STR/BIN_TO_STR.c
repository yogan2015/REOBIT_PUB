
#include "strutils.h"

void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->Buf) binToStr((void *)*v->Buf, *v->In, v->Offset, v->Digits);
}



