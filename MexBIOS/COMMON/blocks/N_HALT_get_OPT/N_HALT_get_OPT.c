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
  #endif
}

void Exec(void)
{
#ifndef __BORLANDC__
  v->WARN_6 = 0;
  v->WARN_6 |= !((GPIO_readBits(v->reg0, v->Bit0) != 0)) << 0;
  v->WARN_6 |= !((GPIO_readBits(v->reg1, v->Bit1) != 0)) << 1;
  v->WARN_6 |= !((GPIO_readBits(v->reg2, v->Bit2) != 0)) << 2;
  v->WARN_6 |= !((GPIO_readBits(v->reg3, v->Bit3) != 0)) << 3;
  v->WARN_6 |= !((GPIO_readBits(v->reg4, v->Bit4) != 0)) << 4;
  v->WARN_6 |= !((GPIO_readBits(v->reg5, v->Bit5) != 0)) << 5;
  v->WARN_6 &= v->MASK;
#else
  v->WARN_6 = 0;
#endif

}

