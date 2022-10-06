#ifndef __BORLANDC__
#include "niietcm4.h"
#include "gpio.h"
#endif

// Do not initialize inputs!
void Init(void)
{
  #ifndef __BORLANDC__
    v->reg0 = (uint32_t)GPIO_init(1, &v->Bit0, 0);
    v->reg1 = (uint32_t)GPIO_init(1, &v->Bit1, 0);
    v->reg2 = (uint32_t)GPIO_init(1, &v->Bit2, 0);
    v->reg3 = (uint32_t)GPIO_init(1, &v->Bit3, 0);
    v->reg4 = (uint32_t)GPIO_init(1, &v->Bit4, 0);
    v->reg5 = (uint32_t)GPIO_init(1, &v->Bit5, 0);
    v->reg6 = (uint32_t)GPIO_init(1, &v->Bit6, 0);
    v->reg7 = (uint32_t)GPIO_init(1, &v->Bit7, 0);
    v->reg8 = (uint32_t)GPIO_init(1, &v->Bit8, 0);
    v->reg9 = (uint32_t)GPIO_init(1, &v->Bit9, 0);
  #endif
}

void Exec(void)
{
#ifndef __BORLANDC__
  if ((short)*v->IN & (1 << 0)) GPIO_setBits(v->reg0, v->Bit0); else GPIO_clrBits(v->reg0, v->Bit0);
  if ((short)*v->IN & (1 << 1)) GPIO_setBits(v->reg1, v->Bit1); else GPIO_clrBits(v->reg1, v->Bit1);
  if ((short)*v->IN & (1 << 2)) GPIO_setBits(v->reg2, v->Bit2); else GPIO_clrBits(v->reg2, v->Bit2);
  if ((short)*v->IN & (1 << 3)) GPIO_setBits(v->reg3, v->Bit3); else GPIO_clrBits(v->reg3, v->Bit3);
  if ((short)*v->IN & (1 << 4)) GPIO_setBits(v->reg4, v->Bit4); else GPIO_clrBits(v->reg4, v->Bit4);
  if ((short)*v->IN & (1 << 5)) GPIO_setBits(v->reg5, v->Bit5); else GPIO_clrBits(v->reg5, v->Bit5);
  if ((short)*v->IN & (1 << 6)) GPIO_setBits(v->reg6, v->Bit6); else GPIO_clrBits(v->reg6, v->Bit6);
  if ((short)*v->IN & (1 << 7)) GPIO_setBits(v->reg7, v->Bit7); else GPIO_clrBits(v->reg7, v->Bit7);
  if ((short)*v->IN & (1 << 8)) GPIO_setBits(v->reg8, v->Bit8); else GPIO_clrBits(v->reg8, v->Bit8);
  if ((short)*v->IN & (1 << 9)) GPIO_setBits(v->reg9, v->Bit9); else GPIO_clrBits(v->reg9, v->Bit9);
#endif

}

