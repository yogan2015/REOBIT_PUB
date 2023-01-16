#ifndef __NUCLEO_H745__
#define __NUCLEO_H745__

/********Hall_Include********/
#include "main.h"
//#include "adc.h"
//#include "fdcan.h"
//#include "spi.h"
//#include "tim.h"
//#include "hrtim.h"
//#include "fmac.h"
//#include "cordic.h"
#include "usart.h"
//#include "gpio.h"

/****************************/

/********drivers include*********/
#include "uip.h"
#include "modbus_rtu.h"
#include "m95x.h"
//#include "mbs_hrtim.h"
//#include "mbs_can.h"
#include "IQMathLib.h"
#include "string.h"
//#include "lib_types.h"
//#include "menu2x.h"
/********************************/

/********drivers define*********/
#define MB_ADR			1





#define DEVICE_NUMBER   1
#define VERSION         006
#define VERSION_DATE	((21<<9)|(3<<5)|2) // YY:7 / MM:4 / DD::5

#define MAIN_ISR_FREQ_1kHz  1000
#define MAIN_ISR_FREQ   	5000
#define MEMORY_SIZE  		0x4000
/********************************/


// File operation settings
#if FILE_OP_ENABLE
#define FILE_ADDR        0x08020000
#define FILE_SIZE        0x4000
#endif



/*********SINCOS SENSOR CORRECTION******************/
int32_t Read_SinCorr(int32_t amp);
int32_t Read_CosCorr(int32_t amp);
/****************************/

/**********Struct init**********/

typedef union {
  uint16_t all;
  struct {
    uint16_t Mb1:1;
    uint16_t Mb2:1;
    uint16_t Mb3:1;
    uint16_t Uip:1;
    uint16_t NewVersion:1;
    uint16_t WriteConfiguration:1;
    uint16_t WriteProjectData:1;
    uint16_t WriteGlobalData:1;
    uint16_t ResetEEPROM:1;
    uint16_t ResetProject:1;
    uint16_t Rsvd:8;
  } bit;
} TConnStatus;

typedef struct {
  uint16_t       Slave;
  uint16_t       Speed;
  uint16_t       Parity;
  uint16_t       StopBits;
} TMbParStr;


// Project variables structure

typedef struct {
	uint16_t		Version; // 13
	TConnStatus		Status;      // 15
	uint16_t       	DevNumber;   // 16
	TMbParStr   	Mb1;         // 17-20
	TMbParStr		Mb2;		 // 21-23
	TMbParStr		Mb3;		 //
	UIP_PARAMS		Uip;		 //
	uint16_t       	Rsvd[3];     // 25-31
} TBrdData;


/******* Peripheral Prototype ********//****************************/



/************driver_init**************/
void DataProject_Update(TBrdData* );

void ReadBoardData(void);
//Modbus
void ModbusCheckParams(TMbRTUPort *hPort,TBrdData *structure, TMbParStr *params);
/*************************************/


///******* Global Variable ***********/
extern long __attribute__((section (".deviceRam")))  g_StartMemWrite;
extern long __attribute__((section (".deviceRam")))  g_period;
extern long __attribute__((section (".deviceRam")))  g_start_capture;
extern long __attribute__((section (".deviceRam")))  g_end_capture;
//
////extern CAN_Structure __attribute__((section (".deviceRam")))  g_CAN1;
////extern CAN_Structure __attribute__((section (".deviceRam")))  g_CAN2;
//extern uint32_t __attribute__((section (".deviceRam"))) status_canTx;
//
////extern AErrorStatus __attribute__((section (".deviceRam"))) ErrStatus;
//
extern TMbRTUPort __attribute__((section (".mbData"))) Mb1;
extern TMbRTUPort __attribute__((section (".mbData"))) Mb7;
//extern TMbRTUPort __attribute__((section (".mbData"))) Mb2;
//extern TMbRTUPort __attribute__((section (".mbData"))) Mb3;
//extern UIP_PORT __attribute__((section (".uipData"))) uip;
//extern UIP_UDP_SERVER __attribute__((section (".uipData"))) uip_udp_server;
//extern UIP_UDP_CLIENT __attribute__((section (".uipData"))) uip_udp_client;
extern TBrdData   __attribute__((section (".deviceRam"))) BrdData;
//// extern M95X __attribute__((section (".deviceRam"))) Eeprom;
//
//
extern long __attribute__((section (".deviceRam")))  g_period_1kHz;
extern long __attribute__((section (".deviceRam")))  g_start_capture_1kHz;
extern long __attribute__((section (".deviceRam")))  g_end_capture_1kHz;
extern long __attribute__((section (".deviceRam")))  g_MbsCpuLoad_1kHz;

extern long __attribute__((section (".deviceRam")))  g_period_100Hz;
extern long __attribute__((section (".deviceRam")))  g_start_capture_100Hz;
extern long __attribute__((section (".deviceRam")))  g_end_capture_100Hz;
extern long __attribute__((section (".deviceRam")))  g_MbsCpuLoad_100Hz;

extern long __attribute__((section (".deviceRam")))  g_MbsCpuLoad;
extern long __attribute__((section (".deviceRam")))  g_FLASHLogRdyFlag;
extern short __attribute__((section (".deviceRam"))) g_ResetAfterWDG;
extern long __attribute__((section (".deviceRam")))  StartSensorCapture;
extern long __attribute__((section (".deviceRam")))  pStartSensorCapture;
extern uint32_t __attribute__((section (".deviceRam")))  Result_S;
extern long __attribute__((section (".deviceRam")))  Result_mem;
extern long __attribute__((section (".deviceRam")))  SensorBaudRate;
extern uint16_t __attribute__((section (".deviceRam")))   J;
extern uint16_t __attribute__((section (".deviceRam")))  cSensorDelay;
extern short __attribute__((section (".deviceRam"))) ResetAfterWDG;

extern MBS_Handle __attribute__((section (".externData"))) KernelPtr;



#endif
