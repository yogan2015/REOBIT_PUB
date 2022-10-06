
#include "strutils.h"

void Init(void)
{
}

void Exec(void)
{
  if ((short)*v->Buf) hexToStr((void *)*v->Buf, *v->In, v->Offset, v->Digits);
}



