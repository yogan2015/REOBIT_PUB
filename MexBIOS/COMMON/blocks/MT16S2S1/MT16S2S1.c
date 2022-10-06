
#ifndef __BORLANDC__
#include "niietcm4.h"
#include "spi.h"
#include "gpio.h"

#define __CLR             0x01          // очистка дисплея
#define __HOME            0x02          // перемещение курсора в стартовую позицию
#define __GGADDR          0x40          // адрес для генерации символов
#define __DDADDR          0x80          // адрес для данных
#define __FSTR            0x00|__DDADDR // адрес первой строчки
#define __SSTR            0x40|__DDADDR // адрес второй строчки
#define __PG              0x01          // страница знакогенератора
#define __C               0x02          // включение/выключение курсора
#define __D               0x04          // включение/выключение дисплея
#define __RL              0x04          // сдвиг влево/враво
#define __SC              0x08          // выбор перемещение курсора/сдвиг дисплея
#define __EXT             0x04          // выбор расширенного режима
#define __DL              0x10          // разрядность 4/8 бита
#define __SH              0x01          // разрешение сдвига дисплея
#define __ID              0x02          // направления сдвига курсора влево/вправо

#define ENTRY_MODE_SET    (__ID | 0x04)
#define DISPLAY_ON        (__D  | 0x08)
#define DISPLAY_OFF       (0x08)
#define CUR_DISPL_SHIFT   (__RL | 0x10)
#define FUNCTION_SET      (__DL | 0x28)

static const uint16_t RusTable[] = {
  0x041, // 'А', // 0xc0 // 0
  0x1BD, // 'Б', // 0xc1 // 1
  0x042, // 'В', // 0xc2 // 2
  0x17C, // 'Г', // 0xc3 // 3
  0x17D, // 'Д', // 0xc4 // 4
  0x045, // 'Е', // 0xc5 // 5
  0x1C0, // 'Ж', // 0xc6 // 6
  0x1C1, // 'З', // 0xc7 // 7
  0x1C2, // 'И', // 0xc8 // 8
  0x1C3, // 'Й', // 0xc9 // 9
  0x1C4, // 'К', // 0xca // 10
  0x1C5, // 'Л', // 0xcb // 11
  0x182, // 'М', // 0xcc // 12
  0x048, // 'Н', // 0xcd // 13
  0x04F, // 'О', // 0xce // 14
  0x186, // 'П', // 0xcf // 15
  0x050, // 'Р', // 0xd0 // 16
  0x043, // 'С', // 0xd1 // 17
  0x188, // 'Т', // 0xd2 // 18
  0x1C7, // 'У', // 0xd3 // 19
  0x1C8, // 'Ф', // 0xd4 // 20
  0x058, // 'Х', // 0xd5 // 21
  0x1C9, // 'Ц', // 0xd6 // 22
  0x1CA, // 'Ч', // 0xd7 // 23
  0x1CB, // 'Ш', // 0xd8 // 24
  0x1CC, // 'Щ', // 0xd9 // 25
  0x1CD, // 'Ъ', // 0xda // 26
  0x1CE, // 'Ы', // 0xdb // 27
  0x1CF, // 'Ь', // 0xdc // 28
  0x1D0, // 'Э', // 0xdd // 29
  0x1D1, // 'Ю', // 0xde // 30
  0x1D2, // 'Я', // 0xdf // 31
  0x061, // 'а', // 0xe0 // 32
  0x1D3, // 'б', // 0xe1 // 33
  0x1D4, // 'в', // 0xe2 // 34
  0x1D5, // 'г', // 0xe3 // 35
  0x1D6, // 'д', // 0xe4 // 36
  0x065, // 'е', // 0xe5 // 37
  0x1D7, // 'ж', // 0xe6 // 38
  0x1D8, // 'з', // 0xe7 // 39
  0x1D9, // 'и', // 0xe8 // 40
  0x1DA, // 'й', // 0xe9 // 41
  0x1DB, // 'к', // 0xea // 42
  0x1DC, // 'л', // 0xeb // 43
  0x1DD, // 'м', // 0xec // 44
  0x1DE, // 'н', // 0xed // 45
  0x06F, // 'о', // 0xee // 46
  0x1DF, // 'п', // 0xef // 47
  0x070, // 'р', // 0xf0 // 48
  0x063, // 'с', // 0xf1 // 49
  0x1E0, // 'т', // 0xf2 // 50
  0x079, // 'у', // 0xf3 // 51
  0x1E1, // 'ф', // 0xf4 // 52
  0x078, // 'х', // 0xf5 // 53
  0x1E2, // 'ц', // 0xf6 // 54
  0x1E3, // 'ч', // 0xf7 // 55
  0x1E4, // 'ш', // 0xf8 // 56
  0x1E5, // 'щ', // 0xf9 // 57
  0x1E6, // 'ъ', // 0xfa // 58
  0x1E7, // 'ы', // 0xfb // 59
  0x1E8, // 'ь', // 0xfc // 60
  0x1E9, // 'э', // 0xfd // 61
  0x1EA, // 'ю', // 0xfe // 62
  0x1EB, // 'я', // 0xff // 63
  0x045, // 'Ё', // 0xfe // 64
  0x11F, // 'ё', // 0xff // 65
};

static void WriteByte(BLOCK_STRUCT *v, uint16_t b);
#endif

void Init(void)
{
#ifndef __BORLANDC__
  v->RES_Bit = v->RES; v->RES_Reg = (uint32_t)GPIO_init(1, &v->RES_Bit, 1);
  v->A0_Bit  = v->A0;  v->A0_Reg  = (uint32_t)GPIO_init(1, &v->A0_Bit,  1);
  v->CS_Bit  = v->CS;  v->CS_Reg  = (uint32_t)GPIO_init(1, &v->CS_Bit,  1);

  SPI_init(v->SpiId, 1, 1, v->SpiBaud, 8);

  GPIO_clrBits(v->A0_Reg,  v->A0_Bit);
  GPIO_clrBits(v->RES_Reg, v->RES_Bit); DelayUs(10);
  GPIO_setBits(v->RES_Reg, v->RES_Bit); DelayUs(1000);

  WriteByte(v, __DL|0x20);       DelayUs(40);
  WriteByte(v, __DL|0x20);       DelayUs(40);
  WriteByte(v, __DL|0x20);
  WriteByte(v, FUNCTION_SET);    DelayUs(40);
  WriteByte(v, DISPLAY_OFF);     DelayUs(40);
  WriteByte(v, __CLR);           DelayUs(1520);
  WriteByte(v, ENTRY_MODE_SET);  DelayUs(40);
  WriteByte(v, CUR_DISPL_SHIFT); DelayUs(40);
  WriteByte(v, DISPLAY_ON);      DelayUs(40);
#endif
}

void Exec(void)
{
#ifndef __BORLANDC__
  uint16_t uiTemp;
  uint32_t ulData;

  SPI_init(v->SpiId, 1, 3, v->SpiBaud, 8);

  uiTemp = (uint16_t)v->Address;
  switch((uint16_t)v->State)
  {
    case 0:
      if (uiTemp < 16)
      {
        if (*v->HiStr)
        {
          ulData = ((uint32_t *)*v->HiStr)[uiTemp >> 2];
          uiTemp = (uint16_t)(ulData >> ((3 - (uiTemp % 4)) << 3)) & 0xFF;
        }
        else uiTemp = 0x20;
      }
      else
      {
        if (*v->LoStr)
        {
          uiTemp -= 16;
          ulData = ((uint32_t *)*v->LoStr)[uiTemp >> 2];
          uiTemp = (uint16_t)(ulData >> ((3 - (uiTemp % 4)) << 3)) & 0xFF;
        }
        else uiTemp = 0x20;
      }
      if (uiTemp == 0xA8) uiTemp = RusTable[0x40];
      else if (uiTemp == 0xB8) uiTemp = RusTable[0x41];
      else if (uiTemp >= 0xC0) uiTemp = RusTable[uiTemp - 0xC0];
      GPIO_clrBits(v->A0_Reg, v->A0_Bit);
      if (!(uiTemp & 0x100)) WriteByte(v, DISPLAY_ON);
      else { WriteByte(v, DISPLAY_ON | __PG); uiTemp &= ~0x100; }
      v->Code  = uiTemp;
      v->State = 1;
      break;
    case 1:
      if (uiTemp < 16) uiTemp = uiTemp | __FSTR;
      else uiTemp = (uiTemp - 16) | __SSTR;
      WriteByte(v, uiTemp);
      v->State = 2;
      break;
    case 2:
      GPIO_setBits(v->A0_Reg, v->A0_Bit);
      WriteByte(v, v->Code);
      if (uiTemp < 31) v->Address = v->Address + 1;
      else v->Address = 0;
      v->State = 0;
      break;
  }
#endif
}

#ifndef __BORLANDC__
static void WriteByte(BLOCK_STRUCT *v, uint16_t b)
{
  GPIO_clrBits(v->CS_Reg, v->CS_Bit); DelayUs(1);
  SPI_send(v->SpiId, b);
  GPIO_setBits(v->CS_Reg, v->CS_Bit); DelayUs(2);
}
#endif


