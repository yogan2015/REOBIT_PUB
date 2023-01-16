
#ifndef __CHIP__
#define __CHIP__

#ifndef _FUNC_CALL_
#ifndef __BORLANDC__
#define _FUNC_CALL_
#else
#define _FUNC_CALL_ __stdcall
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

// CPU-timer module
#ifndef CHIP_CPU_TIMER
#define CHIP_CPU_TIMER
void _FUNC_CALL_  ConfigCpuTimer(char Id, long Period);
#endif

// GPIO module
#ifndef CHIP_GPIO
#define CHIP_GPIO
void* _FUNC_CALL_ GPIO_init(short Type, short OutputType, short Pull, unsigned short *Bit, short Value);
#endif

// SCI/UART module
#ifndef CHIP_SCI
#define CHIP_SCI

#define SCI_PARITY_ERROR		0x04
#define SCI_OVERRUN_ERROR		0x08
#define SCI_FRAME_ERROR		0x10
#define SCI_RX_ERROR			0x1C
#define SCI_BREAK				0x20

void _FUNC_CALL_  SCI_init(char Id, short BaudRate, char Parity, char Length, char StopBits);
char _FUNC_CALL_  SCI_recieve(char Id);
void _FUNC_CALL_  SCI_transmit(char Id, char Data);
char _FUNC_CALL_  SCI_getstatus(char Id);
void _FUNC_CALL_  SCI_reset(char Id);
void _FUNC_CALL_  SCI_rx_enable(char Id);
void _FUNC_CALL_  SCI_rx_disable(char Id);
void _FUNC_CALL_  SCI_tx_enable(char Id);
void _FUNC_CALL_  SCI_tx_disable(char Id);
void _FUNC_CALL_  SCI_rx_int_enable(char Id);
void _FUNC_CALL_  SCI_rx_int_disable(char Id);
void _FUNC_CALL_  SCI_tx_int_enable(char Id);
void _FUNC_CALL_  SCI_tx_int_disable(char Id);
#endif

// SPI module
#ifndef CHIP_SPI
#define CHIP_SPI
void  _FUNC_CALL_ SPI_init(char Id, char Master, char Mode, short BaudRate, char Length);
short _FUNC_CALL_ SPI_send(char Id, short Data);
void  _FUNC_CALL_ SPI_transmit(char Id, short Data);
short _FUNC_CALL_ SPI_recieve(char Id);
char  _FUNC_CALL_ SPI_ready(char Id);
#endif

// ADC module
#ifndef CHIP_ADC
#define CHIP_ADC
void _FUNC_CALL_  ADC_init(char Id, void *Cfg);
long _FUNC_CALL_  ADC_get(char Id, char Chan);
#endif

// PWM module
#ifndef CHIP_PWM
#define CHIP_PWM
void _FUNC_CALL_  PWM2M_init(char Id1, char Id2, void *Cfg);
void _FUNC_CALL_  PWM2M_out(char Id1, char Id2, long Cmpr1, long Cmpr2);
void _FUNC_CALL_  PWM2_init(char Id1, char Id2, void *Cfg);
void _FUNC_CALL_  PWM2_setup(char Id1, char Id2, void *Cfg);
void _FUNC_CALL_  PWM4_init(char Id, void *Cfg);
void _FUNC_CALL_  PWM4_out(char Id, long Cmpr1, long Cmpr2, long Cmpr3);
void _FUNC_CALL_  PWM4M_init(char Id1, char Id2, void *Cfg);
void _FUNC_CALL_  PWM4M_out(char Id1, char Id2, long Cmpr1, long Cmpr2, long Cmpr3, long Cmpr4);
void _FUNC_CALL_  PWM6_init(char Id, void *Cfg);
void _FUNC_CALL_  PWM6_out(char Id, long Cmpr1, long Cmpr2, long Cmpr3);
void _FUNC_CALL_  PWM_setPeriod(char Id, long Period);
void _FUNC_CALL_  PWM_enable(char Id, char Enable, char State);
void _FUNC_CALL_  PWM6_enable(char Id, char Enable, char State);
void _FUNC_CALL_  PWM2_enable(char Id1, char Id2, char Enable, char State);
void _FUNC_CALL_  BLDC_PWM_init(char Id, long Period);
void _FUNC_CALL_  BLDC_PWM_out(char Id, char PwmActive, char CmtnPointer, long DutyFunc);
#endif

// QEP/CAP module
#ifndef CHIP_QEP
#define CHIP_QEP
void _FUNC_CALL_  QEP_init(char Id);
long _FUNC_CALL_  QEP_gettimer(char Id);
void _FUNC_CALL_  QEP_settimer(char Id, long Value);
void _FUNC_CALL_  CAP_init(char Id, void *Cfg);
long _FUNC_CALL_  CAP_read(char Id, char EventIndex);
#endif

// McBSP module
#ifndef CHIP_MCBSP
#define CHIP_MCBSP
void _FUNC_CALL_  MCBSP_SPI_init(char Id, char Mode, char ClkDiv, char Length);
short _FUNC_CALL_ MCBSP_SPI_send(char Id, short Data);
#endif

// I2C module
#ifndef CHIP_I2C
#define CHIP_I2C

// I2C error codes
#define I2C_SUCCESS                   0
#define I2C_ERR_INIT_FAILED           1
#define I2C_ERR_BUSY                  2
#define I2C_ERR_TX_DATA               3
#define I2C_ERR_RX_DATA               4

// I2C message commands
#define I2C_MSGSTAT_INACTIVE          0x00
#define I2C_MSGSTAT_SEND_WITHSTOP     0x10
#define I2C_MSGSTAT_WRITE_BUSY        0x11
#define I2C_MSGSTAT_WRITE_WAIT        0x12
#define I2C_MSGSTAT_SEND_NOSTOP       0x20
#define I2C_MSGSTAT_SEND_NOSTOP_BUSY  0x21
#define I2C_MSGSTAT_RESTART           0x22
#define I2C_MSGSTAT_READ_BUSY         0x23
#define I2C_MSGSTAT_NACK              0x30

// I2C Message Structure
struct I2CMSG {
	char  Id;				// I2C Ident
	short Status;			// Message Command
	short Slave;			// Address of slave
	short RxBytes;			// Number of valid bytes
	short TxBytes;			// Number of valid bytes
	short Buffer[16];		// Array holding message data
};

extern void _FUNC_CALL_ I2C_init(char Id, long Speed);
extern char _FUNC_CALL_ I2C_write(char Id, char DeviceAddr, char *pBuffer, char NumByteToWrite);
extern char _FUNC_CALL_ I2C_read(char Id, char DeviceAddr, char *pBuffer, char NumByteToWrite, char NumByteToRead);
extern void _FUNC_CALL_ I2C_msgSend(struct I2CMSG *Msg, char DeviceAddr, char Command, char NumByteToWrite, char NumByteToRead);
extern void _FUNC_CALL_ I2C_update(struct I2CMSG *Msg);
#endif

// Service functions
#ifndef CHIP_SRV
#define CHIP_SRV
void _FUNC_CALL_  Eallow(void);
void _FUNC_CALL_  Edis(void);

void _FUNC_CALL_  DelayUs(unsigned short Delay);

void  _FUNC_CALL_ pgm_blkRead(void *, void *, unsigned short);
void  _FUNC_CALL_ pgm_blkWrite(void *, void *, unsigned short);
void  _FUNC_CALL_ pgm_strRead(char *, char *);
void  _FUNC_CALL_ pgm_strWrite(char *, char *);

void _FUNC_CALL_  MemCopy(char *SourceAddr, char *SourceEndAddr, char *DestAddr);
#endif

// Math functions
#ifdef __BORLANDC__
float _FUNC_CALL_ cosf(float A);
float _FUNC_CALL_ coshf(float A);
float _FUNC_CALL_ logf(float A);
float _FUNC_CALL_ log10f(float A);
float _FUNC_CALL_ sinf(float A);
float _FUNC_CALL_ sinhf(float A);
float _FUNC_CALL_ acosf(float A);
float _FUNC_CALL_ asinf(float A);
float _FUNC_CALL_ atanf(float A);
float _FUNC_CALL_ atan2f(float A, float B);
float _FUNC_CALL_ ceilf(float A);
float _FUNC_CALL_ expf(float A);
float _FUNC_CALL_ fabsf(float A);
float _FUNC_CALL_ floorf(float A);
float _FUNC_CALL_ fmodf(float A, float B);
float _FUNC_CALL_ frexpf(float A, long *B);
float _FUNC_CALL_ ldexpf(float A, long B);
float _FUNC_CALL_ modff(float A, float *B);
float _FUNC_CALL_ powf(float A, float B);
float _FUNC_CALL_ sqrtf(float A);
float _FUNC_CALL_ tanf(float A);
float _FUNC_CALL_ tanhf(float A);
float _FUNC_CALL_ acoshf(float A);
float _FUNC_CALL_ asinhf(float A);
float _FUNC_CALL_ atanhf(float A);
float _FUNC_CALL_ cbrtf(float A);
float _FUNC_CALL_ copysignf(float A, float B);
float _FUNC_CALL_ erff(float A);
float _FUNC_CALL_ erfcf(float A);
float _FUNC_CALL_ expm1f(float A);
float _FUNC_CALL_ exp2f(float A);
float _FUNC_CALL_ fdimf(float A, float B);
float _FUNC_CALL_ fmaf(float A, float B, float C);
float _FUNC_CALL_ fmaxf(float A, float B);
float _FUNC_CALL_ fminf(float A, float B);
float _FUNC_CALL_ hypotf(float A, float B);
long _FUNC_CALL_ ilogbf(float A);
float _FUNC_CALL_ lgammaf(float A);
__int64 _FUNC_CALL_ llrintf(float A);
__int64 _FUNC_CALL_ llroundf(float A);
float _FUNC_CALL_ log1pf(float A);
float _FUNC_CALL_ logbf(float A);
long  _FUNC_CALL_ lrintf(float A);
long  _FUNC_CALL_ lroundf(float A);
float _FUNC_CALL_ nanf(const char *A);
float _FUNC_CALL_ nearbyintf(float A);
float _FUNC_CALL_ nextafterf(float A, float B);
float _FUNC_CALL_ nexttowardf(float A, long double B);
float _FUNC_CALL_ remainderf(float A, float B);
float _FUNC_CALL_ remquof(float A, float B, long *C);
float _FUNC_CALL_ rintf(float A);
float _FUNC_CALL_ roundf(float A);
float _FUNC_CALL_ scalbnf(float A, long B);
float _FUNC_CALL_ scalblnf(float A, long B);
float _FUNC_CALL_ tgammaf(float A);
float _FUNC_CALL_ truncf(float A);
#endif

#define atan2pu(A,B)	((atan2(A,B)/6.283185307) >= 0.0 ? (atan2(A,B)/6.283185307):1.0 + (atan2(A,B)/6.283185307))

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* __CHIP__ */



