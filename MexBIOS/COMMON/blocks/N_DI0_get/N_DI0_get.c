#ifndef __BORLANDC__
#include "niietcm4.h"
#include "gpio.h"
#endif

// Do not initialize inputs!
void Init(void)
{
  #ifndef __BORLANDC__
    v->reg0 = (uint32_t)GPIO_init(0, &v->Bit0, 0);
    v->reg1 = (uint32_t)GPIO_init(0, &v->Bit1, 0);
    v->reg2 = (uint32_t)GPIO_init(0, &v->Bit2, 0);
    v->reg3 = (uint32_t)GPIO_init(0, &v->Bit3, 0);
    v->reg4 = (uint32_t)GPIO_init(0, &v->Bit4, 0);
    v->reg5 = (uint32_t)GPIO_init(0, &v->Bit5, 0);
    v->reg6 = (uint32_t)GPIO_init(0, &v->Bit6, 0);
    v->reg7 = (uint32_t)GPIO_init(0, &v->Bit7, 0);
    v->reg8 = (uint32_t)GPIO_init(0, &v->Bit8, 0);
    v->reg9 = (uint32_t)GPIO_init(0, &v->Bit9, 0);
  #endif
}

void Exec(void)
{
#ifndef __BORLANDC__
  v->OUT = 0;
  v->OUT |= (GPIO_readBits(v->reg0, v->Bit0) != 0) << 0;
  v->OUT |= (GPIO_readBits(v->reg1, v->Bit1) != 0) << 1;
  v->OUT |= (GPIO_readBits(v->reg2, v->Bit2) != 0) << 2;
  v->OUT |= (GPIO_readBits(v->reg3, v->Bit3) != 0) << 3;
  v->OUT |= (GPIO_readBits(v->reg4, v->Bit4) != 0) << 4;
  v->OUT |= (GPIO_readBits(v->reg5, v->Bit5) != 0) << 5;
  v->OUT |= (GPIO_readBits(v->reg6, v->Bit6) != 0) << 6;
  v->OUT |= (GPIO_readBits(v->reg7, v->Bit7) != 0) << 7;
  v->OUT |= (GPIO_readBits(v->reg8, v->Bit8) != 0) << 8;
  v->OUT |= (GPIO_readBits(v->reg9, v->Bit9) != 0) << 9;
#else
  v->OUT = 0;
#endif

}

