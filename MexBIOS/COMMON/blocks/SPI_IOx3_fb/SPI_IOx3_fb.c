
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

  v->CsBit2 = v->FSSPin;
  v->CsReg2 = (uint32_t)GPIO_init(1, &v->CsBit2, 1);

  v->CsBit3 = v->SamplePin;
  v->CsReg3 = (uint32_t)GPIO_init(1, &v->CsBit3, 1);
#endif
}

void Exec(void)
{
#ifndef __BORLANDC__
  int i = 0;
  SPI_init(v->SpiId, 1, 1, v->SpiBaud, v->SpiLen);

  GPIO_clrBits(v->CsReg3, v->CsBit3);
  //manual delay to provide necessary Sample low hold time
  for (i=0;i<27;i++) asm volatile ("nop");
  GPIO_setBits(v->CsReg3, v->CsBit3);

  GPIO_clrBits(v->CsReg, v->CsBit);

  GPIO_clrBits(v->CsReg2, v->CsBit2);
  v->Out = (uint16_t)SPI_send(v->SpiId, *v->In);
  GPIO_setBits(v->CsReg2, v->CsBit2);

  GPIO_clrBits(v->CsReg2, v->CsBit2);
  v->Out1 = (uint16_t)SPI_send(v->SpiId, *v->In1);
  GPIO_setBits(v->CsReg2, v->CsBit2);

  GPIO_clrBits(v->CsReg2, v->CsBit2);
  v->Out2 = (uint16_t)SPI_send(v->SpiId, *v->In2);
  GPIO_setBits(v->CsReg2, v->CsBit2);

  GPIO_setBits(v->CsReg, v->CsBit);
#endif
}



