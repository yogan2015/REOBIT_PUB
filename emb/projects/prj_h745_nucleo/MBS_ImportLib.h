 
#ifndef MBS_IMPORT_LIB_
#define MBS_IMPORT_LIB_
 
#include "kernel.h"


extern struct MBS_KERNEL Kernel;
extern const short MBS_Matrix[];
 
extern void*  MBS_Create(void);
extern void   MBS_init(MBS_Handle);
extern void   MBS_isr_execute(MBS_Handle, short);
extern void   MBS_mon_execute(MBS_Handle);
extern short* MBS_GetData(short, short, short *);
 
#define MbsKernel                   (&Kernel)
#define MbsAppVersion               MbsKernel->control.appVersion
#define MbsEnable                   MbsKernel->control.enable
#define MbsStatus                   MbsKernel->control.krnlStatus
#define MbsError                    MbsKernel->control.error
#define MbsMemCmd                   MbsKernel->memCmd
#define MbsMemStatus                MbsKernel->control.memStatus
#define MbsCpuLoad                  MbsKernel->control.cpuLoad
#define MbsMaxConfigSize            0x2D00
#define MbsProjData                 MbsKernel->pjtData
#define MbsProjDataSize             MbsKernel->pjtDataSize
 
#define MBS_ReadConfiguration()     pgm_blkRead((short *)MBS_Matrix, (short *)MbsKernel->cfg, 0x247L * sizeof(short))
#define MBS_WriteConfiguration()    WriteToBoardMemory(0, MbsProjDataSize, (short *)MbsKernel->cfg, *((long *)((short *)MbsKernel->cfg + 2)) / sizeof(short))
#define MBS_EraseConfiguration()    WriteToBoardMemory(0, MbsProjDataSize, (short *)0, MbsMaxConfigSize)
#define MBS_ReadGlobalData()        
#define MBS_WriteGlobalData()       WriteToBoardMemory(1, MbsProjDataSize + MbsMaxConfigSize, (short *)MbsKernel->glData, MbsKernel->glCount * 2)
#define MBS_WriteGlobalVar()        WriteToBoardMemory(0, MbsProjDataSize + MbsMaxConfigSize + MbsKernel->varIndex * 2, (short*)MbsKernel->glData[MbsKernel->varIndex], 2)
#define MBS_EraseGlobalData()       WriteToBoardMemory(1, MbsProjDataSize + MbsMaxConfigSize, (short *)0, MbsKernel->glCount * 2)
#define MBS_ReadProjectData()       ReadFromBoardMemory(0, 0, (short *)MbsProjData, MbsProjDataSize)
#define MBS_WriteProjectData()      WriteToBoardMemory(0, 0, (short *)MbsProjData, MbsProjDataSize)
#define MBS_WriteProjectVar()       WriteToBoardMemory(0, MbsKernel->pjtDataAddr, (short *)MbsProjData + MbsKernel->pjtDataAddr, MbsKernel->pjtDataLen)
#define MBS_EraseProjectData()      WriteToBoardMemory(0, 0, (short *)0, MbsProjDataSize)
 
#define MBS_Init()                  MBS_init(MbsKernel)
#define MBS_IsrExecute(Vec)         MBS_isr_execute(MbsKernel, Vec)
#define MBS_MonExecute()            MBS_mon_execute(MbsKernel)
#define MBS_GetDataAddr             ((long)&MBS_GetData)
 
#endif
 
