
#ifndef __BORLANDC__
#include "niietcm4.h"
#include "spi.h"
#include "gpio.h"
#endif

void Init(void)
{
#ifndef __BORLANDC__
  v->CsBit = v->CsPin;
  v->CsReg = (uint32_t)GPIO_init(1, &v->CsBit, 1);
#endif
}

void Exec(void)
{
#ifndef __BORLANDC__
  SPI_init(v->SpiId, 1, 1, v->SpiBaud, v->SpiLen);
  GPIO_clrBits(v->CsReg, v->CsBit);
  v->Out = (uint16_t)SPI_send(v->SpiId, *v->In);
  GPIO_setBits(v->CsReg, v->CsBit);
#endif
}



