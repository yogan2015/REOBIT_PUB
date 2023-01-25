
#ifndef __M95X__
#define __M95X__

#include <stdint.h>

#define M95512_TYPE      0
#define M95M02_TYPE      1
#define M95256_TYPE      2

#define M95X_SUCCESS     0
#define M95X_BUSY        1
#define M95X_EDISCON    -1
#define M95X_EWRITE_ERR -2

#define M95X_NONE        0x00
#define M95X_WRITE       0x01
#define M95X_READ        0x02
#define M95X_STATUS      0x04
#define M95X_PROTECT     0x08
#define M95X_WR_EN       0x10
#define M95X_WR_DIS      0x20

typedef struct {
	uint8_t   SpiId;
	uint16_t  SpiBaud;
	uint8_t   Type;
	uint32_t  Size;
	uint8_t   Func;
	uint8_t   Mode;
	uint8_t  *Buffer;
	uint32_t  Addr;
	uint16_t  Count;
	uint8_t   RdData;
	uint8_t   WrData;
	uint8_t   State;
	int16_t   Status;
	uint8_t   Counter;
	uint16_t  BusyTime;
	uint16_t  BusyTimer;
	void (*CsFunc)(uint8_t);
} M95X;

#define M95X_IsReady(pMem)	(!(pMem)->Func)
#define M95X_IsError(pMem)	((pMem)->Status < 0)

void M95X_Init(M95X *);
void M95X_Update(M95X *);
void M95X_Func(M95X *, uint8_t Func, uint8_t Mode,
	uint32_t Addr, uint8_t *Data, uint16_t Count);

#endif /* __M95X__*/





