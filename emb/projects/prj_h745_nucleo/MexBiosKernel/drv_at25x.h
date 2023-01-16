
#ifndef __DRV_AT25X__
#define __DRV_AT25X__

#define AT25X_SUCCESS		 0
#define AT25X_BUSY			 1
#define AT25X_EDISCON		-1
#define AT25X_EWRITE_ERR	-2

#define AT25X_NONE		 	 0x00
#define AT25X_WRITE		 	 0x01
#define AT25X_READ			 0x02
#define AT25X_STATUS	 	 0x04
#define AT25X_PROTECT		 0x08
#define AT25X_WR_EN		 	 0x10
#define AT25X_WR_DIS		 0x20

typedef struct {
	char   SpiId;
	short  SpiBaud;
	char   Func;
	char   Mode;
	short *Buffer;
	short  Addr;
	short  Count;
	short  RdData;
	short  WrData;
	char   Counter;
	char   State;
	short  Status;
	short  BusyTime;
	short  BusyTimer;
	short  Temp;
	void (*CsFunc)(char);
} AT25X;

#define AT25X_IsReady(pMem)	(!(pMem)->Func)
#define AT25X_IsError(pMem)	((pMem)->Status < 0)

void AT25X_Init(AT25X *);
void AT25X_Update(AT25X *);
void AT25X_Func(AT25X *, char Func, char Mode,
	short Addr, short *Data, short Count);

#endif /* __DRV_AT25X__*/





