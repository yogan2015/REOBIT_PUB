#include <stdint.h>
#include "../cmn/core/core_cm3.h"
#include "../cmn/target/stm32f10x.h"

void SystemInit()
{

}

void main()
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
  RCC
}