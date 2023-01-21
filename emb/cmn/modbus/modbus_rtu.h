
#ifndef MODBUS_RTU_
#define MODBUS_RTU_

#include "responses.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MB_RTU_SLAVE                 0
#define MB_RTU_MASTER                1

#define MB_RTU_WORD_MAX              120
#define MB_RTU_BYTE_MAX              (MB_RTU_WORD_MAX * 2)
#define MB_RTU_FRAME_MAX             256

#define MB_RTU_READ_COILS            0x01
#define MB_RTU_READ_REGS             0x03
#define MB_RTU_READ_INPUTS           0x04
#define MB_RTU_WRITE_SINGLE_COIL     0x05
#define MB_RTU_WRITE_SINGLE_REG      0x06
#define MB_RTU_DIAGNOSTICS           0x08
#define MB_RTU_WRITE_MULTIPLE_COILS  0x0F
#define MB_RTU_WRITE_REGS            0x10
#define MB_RTU_REPORT_ID             0x11
#define MB_RTU_READ_FILE_REC         0x14

typedef void    (*TMbRTUTrEnable)(char);
typedef short * (*TMbGetData)(short, short, short *);
typedef short * (*TMbGetRecord)(short, short, short, char *, char *);

typedef struct {
	char				SlaveID;
	unsigned short		DeviceNumber;
	unsigned short		VersionNumber;
	unsigned short		VersionDate;
	const char         *DeviceInfo;
	const char         *DeviceDescr;
} TMbSlaveInfo;

typedef struct {
	char                UartID;
	char                Mode;
	char                Slave;
	short               BaudRate;
	short               BrrValue;
	char                Parity;
	char                StopBits;
	char                UserMode;
	char                RetryCount;
	char                Scale;
	unsigned short      RxDelay;
	unsigned short      TxDelay;
	unsigned short      ConnTimeout;
	unsigned short      AckTimeout;
	TMbSlaveInfo       *SlaveInfo;
	TMbRTUTrEnable      TrEnable;
	TMbGetData          GetData;
	TMbGetRecord        GetRecord;
} TMbRTUParams;

typedef struct {
	char                Request;
	unsigned short      SubRequest;
	char                Response;
	unsigned short      Addr;
	unsigned short      Count;
	unsigned short      RecNum;
	char                Exception;
	char                Acknoledge;
	char                Connected;
	char                RetryCounter;
	unsigned short      Data[MB_RTU_WORD_MAX];
} TMbRTUPacket;

typedef struct {
	char                NewMessage;
	char                WaitResponse;
	unsigned short      Timeout1_5;
	unsigned short      Timeout3_5;
	unsigned short      Timer1_5;
	unsigned short      Timer3_5;
	unsigned short      TimerPre;
	unsigned short      TimerPost;
	unsigned short      TimerAck;
	unsigned short      TimerConn;
	unsigned short      RxCounter;
	unsigned short      TxCounter;
	unsigned short      RxLength;
	unsigned short      TxLength;
	char                Buf[MB_RTU_FRAME_MAX];
} TMbRTUFrame;

typedef struct {
	unsigned short      RxBytesCount;
	unsigned short      TxBytesCount;
} TMbRTUStat;

typedef struct {
	TMbRTUParams        Params;
	TMbRTUPacket        Packet;
	TMbRTUFrame         Frame;
	TMbRTUStat          Stat;
} TMbRTUPort;

void ModBusRTUInit(TMbRTUPort *);
void ModBusRTUInvoke(TMbRTUPort *);
void ModBusRTUTimings(TMbRTUPort *);
void ModBusRTURxIsr(TMbRTUPort *);
void ModBusRTUTxIsr(TMbRTUPort *);

#ifdef __cplusplus
}
#endif // extern "C"

#endif



