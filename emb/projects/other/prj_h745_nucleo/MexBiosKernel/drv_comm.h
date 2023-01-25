
#ifndef __DRV_COMM__
#define __DRV_COMM__

#define DRVC_DATA_MAX		120
#define DRVC_FRAME_MAX		(DRVC_DATA_MAX * 2 + 9)

#define DRVC_READ_REGS		0x03
#define DRVC_DIAGNOSTICS	0x08
#define DRVC_WRITE_REGS	0x10

typedef void   (*TDrvCommTxControl)(short);
typedef short *(*TDrvCommCallBack)(short, short, short*);

typedef struct {
	short UartID;						// UART identificator (ex., SCIA=0, SCIB=1, etc.)
	short Slave;						// Slave adrress (1...32)
	short BaudRate;					// Baudrate / 100 (ex., 192 => 19200)
	short BrrValue;					// Baudrate register value
	short Parity;						// Parity mode (0=None, 1=Odd, 2=Even)
	short RxDelay;						// Delay on byte reception
	short TxDelay;						// Delay before transmition begins
	short Prescale;					// Timing function frequency in kHz
	TDrvCommTxControl TxControl;	// Transmition control function
	TDrvCommCallBack  Callback;	// Callback function for updating new recieved packet
} TDrvCommParams;

typedef struct {
	short Exception;
	short NewMsg;
	short Acknoledge;
	short Timeout1_5;
	short Timeout3_5;
	short TimeoutAck;
	short Timer1_5;
	short Timer3_5;
	short TimerPre;
	short TimerPost;
	short TimerAck;
	short RxCounter;
	short TxCounter;
	short RxLength;
	short TxLength;
	short Buf[DRVC_FRAME_MAX];
} TDrvCommFrame;

typedef struct {
	short RxBytesCount;
	short TxBytesCount;
} TDrvCommStat;

typedef struct {
	TDrvCommParams Params;
	TDrvCommFrame  Frame;
	TDrvCommStat   Stat;
} TDrvCommPort;

void DrvCommInit(TDrvCommPort *);
void DrvCommTimings(TDrvCommPort *);
void DrvCommUpdate(TDrvCommPort *);
void DrvCommRxHandler(TDrvCommPort *);
void DrvCommTxHandler(TDrvCommPort *);

#endif /* __DRV_COMM__ */


