#ifndef __BORLANDC__
#include "stm32f4xx.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_dma.h"
#include "ws2812.h"
#endif
#define ONE_HIGH 128
#define TWO_HIGH 64
#define THREE_HIGH 32
// Do not initialize inputs!
void Init(void)
{
#ifndef __BORLANDC__

#endif

}

void Exec(void)
{
#ifndef __BORLANDC__
short j;

if (*v->En)
{
  v->Time = _IQ24(0.0);
  v->State = 0;
  for (j = 2; j < (v->LED_Nums + 2); j++)
  {
    if (v->RED_Buff[j]) v->Red = ONE_HIGH; else v->Red = 0;
    if (v->GREEN_Buff[j]) v->Green = ONE_HIGH; else v->Green = 0;
    if (v->BLUE_Buff[j]) v->Blue = ONE_HIGH; else v->Blue = 0;

    if (v->RED_Buff[j] && v->GREEN_Buff[j])
    {
      v->Red = TWO_HIGH;
      v->Green = TWO_HIGH;
    }
    if (v->RED_Buff[j] && v->BLUE_Buff[j])
    {
      v->Red = TWO_HIGH;
      v->Blue = TWO_HIGH;
    }
    if (v->GREEN_Buff[j] && v->BLUE_Buff[j])
    {
      v->Green = TWO_HIGH;
      v->Blue = TWO_HIGH;
    }
    if (v->GREEN_Buff[j] && v->BLUE_Buff[j] && v->RED_Buff[j])
    {
      v->Red = THREE_HIGH;
      v->Green = THREE_HIGH;
      v->Blue = THREE_HIGH;
    }

    ws2812_pixel_rgb_to_buf_dma(v->Red, v->Green, v->Blue, (j - 2));
  }
}
else
{
  switch (v->State) //Write to board memeory indicate
   {
    case 0:
      v->Time += v->SampleTime;
      ws2812_pixel_rgb_to_buf_dma(0, ONE_HIGH, 0, 11);
      if (v->Time >= _IQ24(0.3))
        {
          v->Time = _IQ24(0.0);
          v->State = 1;
        }
    break;

    case 1:
     v->Time += v->SampleTime;
     ws2812_pixel_rgb_to_buf_dma(0, 0, ONE_HIGH, 11);
     if (v->Time >= _IQ24(0.3))
        {
          v->Time = _IQ24(0.0);
          v->State = 0;
    break;
    }
  }
}


 #endif
}

