#ifndef __BORLANDC__
#include "stm32f4xx.h"
#endif
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
#ifndef __BORLANDC__
if ((*v->En == 1) && (v->prevIn == 0))  NVIC_SystemReset();
#endif

}

