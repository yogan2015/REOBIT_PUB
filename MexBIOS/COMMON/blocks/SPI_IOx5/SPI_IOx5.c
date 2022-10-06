
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
  short spd_low, spd_hgh, pos_low, pos_hgh, err;

  SPI_init(v->SpiId, 1, 1, v->SpiBaud, v->SpiLen);

  GPIO_clrBits(v->CsReg3, v->CsBit3);
  GPIO_setBits(v->CsReg3, v->CsBit3);
  GPIO_clrBits(v->CsReg, v->CsBit);

  GPIO_clrBits(v->CsReg2, v->CsBit2);
  spd_low = (uint16_t)SPI_send(v->SpiId, 128);
  GPIO_setBits(v->CsReg2, v->CsBit2);

  GPIO_clrBits(v->CsReg2, v->CsBit2);
  spd_hgh = (uint16_t)SPI_send(v->SpiId, 129);
  GPIO_setBits(v->CsReg2, v->CsBit2);

  GPIO_clrBits(v->CsReg2, v->CsBit2);
  pos_low = (uint16_t)SPI_send(v->SpiId, 130);
  GPIO_setBits(v->CsReg2, v->CsBit2);

  GPIO_clrBits(v->CsReg2, v->CsBit2);
  pos_hgh = (uint16_t)SPI_send(v->SpiId, 131);
  GPIO_setBits(v->CsReg2, v->CsBit2);

  GPIO_clrBits(v->CsReg2, v->CsBit2);
  err = (uint16_t)SPI_send(v->SpiId, 255);
  GPIO_setBits(v->CsReg2, v->CsBit2);

  GPIO_setBits(v->CsReg, v->CsBit);

  v->spd = (((unsigned short)spd_low & 0xFF) << 8) | ((unsigned short)spd_hgh & 0xFF);
  v->pos = (((unsigned short)pos_low & 0xFF) << 8) | ((unsigned short)pos_hgh & 0xFF);
#endif

}



