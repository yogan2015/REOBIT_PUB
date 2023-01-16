
#ifndef __BOARDS__
#define __BOARDS__

#ifdef NUCLEO_H755ZI_Q
#include "board_nucleo_h755ZI_Q.h"
#endif

#ifdef HYDROPRESS_H7
#include "board_hydropress_h7.h"
#endif

#ifdef H745_REO
#include "board_h745_reo.h"
#endif

#ifdef H745_NUCLEO
#include "board_h745_nucleo.h"
#endif

void InitBoardPeripherial(void);
void ExecuteBoardBackgroundTask(void);
void Fast_ExecuteBoardInterruptTask(void);
void Slow_ExecuteBoardInterruptTask(void);
void ReadBoardData(void);

int16_t GetBoardMemoryStatus(void);
int16_t IsBoardMemoryReady(void);
int16_t ReadFromBoardMemory(int16_t Mode, int32_t Addr, int16_t *Buf, int32_t Size);
int16_t WriteToBoardMemory(int16_t Mode, int32_t Addr, int16_t *Buf, int32_t Size);

#define MBS_EraseEEPROM() 				WriteToBoardMemory(0, 0, 0, MEMORY_SIZE)
#ifdef FLASH_MBS_CFG
#include "mbs_flash.h"

#define EraseBoardMemory		FlashErase
#define MBS_FLASH_ReadConfiguration()	FlashRead(0, 0, (short *)MbsKernel->cfg, MbsMaxConfigSize)
#define MBS_FLASH_WriteConfiguration()	FlashWrite(0, 0, (short *)MbsKernel->cfg, *((long *)((short *)MbsKernel->cfg + 2)) / sizeof(short))
#define MBS_FLASH_ReadGlobalData()  	ReadFromBoardMemory(1, MbsProjDataSize, (short *)MbsKernel->glData, MbsKernel->glCount * 2)
#define MBS_FLASH_WriteGlobalData()	WriteToBoardMemory(1, MbsProjDataSize, (short *)MbsKernel->glData, MbsKernel->glCount * 2)
#define MBS_FLASH_WriteGlobalVar()		WriteToBoardMemory(0, MbsProjDataSize + MbsKernel->varIndex * 2, (short*)MbsKernel->glData[MbsKernel->varIndex], 2)
#define MBS_FLASH_EraseGlobalData() 	WriteToBoardMemory(1, MbsProjDataSize, (short *)0, MbsKernel->glCount * 2)
#endif


#endif

