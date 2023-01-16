#ifndef __FLASH_H
#define __FLASH_H

#ifdef NUCLIO_G4
#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_flash_ex.h"
#include "stm32g4xx_hal_flash.h"
#else
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_flash_ex.h"
#include "stm32h7xx_hal_flash.h"
#endif



int16_t FlashErase();
int16_t FlashRead(uint8_t Mode, uint32_t Addr, void *pData, uint16_t Size);
int16_t FlashWrite(uint8_t Mode, uint32_t Addr, void *pData, uint16_t Size);

#endif
