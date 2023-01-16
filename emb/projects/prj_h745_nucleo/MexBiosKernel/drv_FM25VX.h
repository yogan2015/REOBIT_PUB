
#ifndef __DRV_FM25VX__
#define __DRV_FM25VX__

#define FM25VX_SUCCESS		 0
#define FM25VX_BUSY		 	 1
#define FM25VX_EDISCON		-1
#define FM25VX_EWRITE_ERR	-2
#define FM25VX_BAD_DEVID	-3

#define FM25VX_WRITE		 0x01
#define FM25VX_READ		 	 0x02
#define FM25VX_STATUS	 	 0x04
#define FM25VX_PROTECT		 0x08
#define FM25VX_SLEEP		 0x10
#define FM25VX_WAKE_UP		 0x20
#define FM25VX_RDID		 	 0x40
#define FM25VX_SNR			 0x80

#define FM25VX_MEM_SIZE	 	 0x20000	// Size in words

typedef struct {
	short  SpiId;
	short  SpiBaud;
	short  Func;
	short  Count;
	long   Addr;
	short *Buffer;
	short  Mode;
	short  RdData;
	short  WrData;
	short  Counter;
	short  Status;
	short  BusyTimer;
	short  BusyTime;
	short  Temp;
	void (*CsFunc)(char);
} FM25VX;

#define FM25VX_IsReady(pMem)	(!(pMem)->Func)
#define FM25VX_IsError(pMem)	((pMem)->Status < 0)

void FM25VX_Init(FM25VX *);
void FM25VX_Update(FM25VX *);
void FM25VX_Func(FM25VX *, short Func, short Mode,
	long Addr, short *Data, short Count);
short FM25VX_ReadWord(FM25VX *, long Addr);

#endif /* __DRV_FM25VX__ */





