
#ifndef __DRV_AT45X__
#define __DRV_AT45X__

#define AT45X_SUCCESS		 0
#define AT45X_BUSY			 1
#define AT45X_EDISCON		-1
#define AT45X_EWRITE_ERR	-2

#define AT45X_NONE		 	 0x00
#define AT45X_WRITE		 	 0x01
#define AT45X_READ			 0x02
#define AT45X_STATUS	 	 0x04
#define AT45X_CHIP_ERASE	 0x08
#define AT45X_GET_DEVID	 0x10

typedef struct {
	char   SpiId;
	short  SpiBaud;
	char   Func;
	char   Mode;
	short *Buffer;
	long   Addr;
	short  Count;
	short  RdData;
	short  WrData;
	char   Counter;
	char   State;
	short  Status;
	short  BusyTime;
	short  BusyTimer;
	void (*CsFunc)(char);
} AT45X;

#define AT45X_IsReady(pMem)	(!(pMem)->Func)
#define AT45X_IsError(pMem)	((pMem)->Status < 0)

void AT45X_Init(AT45X *);
void AT45X_Update(AT45X *);
void AT45X_Func(AT45X *, char Func, char Mode,
	long Addr, short *Data, short Count);

#endif /* __DRV_AT45X__*/





