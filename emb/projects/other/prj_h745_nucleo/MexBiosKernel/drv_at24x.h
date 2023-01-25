
#ifndef __DRV_AT24X__
#define __DRV_AT24X__

#define AT24X_SUCCESS		 0
#define AT24X_BUSY			 1
#define AT24X_EDISCON		-1
#define AT24X_EWRITE_ERR	-2

#define AT24X_NONE		 	 0x00
#define AT24X_WRITE		 	 0x01
#define AT24X_READ			 0x02
#define AT24X_STATUS	 	 0x04

typedef struct {
	struct I2CMSG  *Msg;
	char            Slave;
	char            Func;
	char            Mode;
	unsigned short  Addr;
	unsigned short *Buffer;
	unsigned short  Count;
	unsigned short  RdData;
	unsigned short  WrData;
	unsigned short  Counter;
	short           Status;
	unsigned short  ReadTime;
	unsigned short  WriteTime;
	unsigned short  BusyTimer;
} AT24X;

#define AT24X_IsReady(pMem)	(!(pMem)->Func)
#define AT24X_IsError(pMem)	((pMem)->Status < 0)

void AT24X_Update(AT24X *);
void AT24X_Func(AT24X *, char Func, char Mode,
	unsigned short Addr, unsigned short *Data, unsigned short Count);
unsigned short AT24X_ReadWord(AT24X *, unsigned short Addr);

#endif /* __DRV_AT24X__*/





