#ifndef CAN_H
#define CAN_H

typedef struct{
	uint32_t NominalPrescaler;
	uint32_t NominalSyncJumpWidth;
	uint32_t NominalTimeSeg1;
	uint32_t NominalTimeSeg2;
	uint32_t DataPrescaler;
	uint32_t DataSyncJumpWidth;
	uint32_t DataTimeSeg1;
	uint32_t DataTimeSeg2;
}CAN_Speed_Str;

typedef union {
  uint32_t all;
  struct {
	  uint32_t f0:1;
	  uint32_t f1:1;
	  uint32_t f2:1;
	  uint32_t f3:1;
	  uint32_t f4:1;
	  uint32_t f5:1;
	  uint32_t f6:1;
	  uint32_t f7:1;
	  uint32_t f8:1;
	  uint32_t f9:1;
	  uint32_t f10:1;
	  uint32_t f11:1;
	  uint32_t f12:1;
	  uint32_t f13:1;
	  uint32_t f14:1;
	  uint32_t f15:1;
	  uint32_t f16:1;
	  uint32_t f17:1;
	  uint32_t f18:1;
	  uint32_t f19:1;
	  uint32_t f20:1;
	  uint32_t f21:1;
	  uint32_t f22:1;
	  uint32_t f23:1;
	  uint32_t f24:1;
	  uint32_t f25:1;
	  uint32_t f26:1;
	  uint32_t f27:1;
	  uint32_t f28:1;
	  uint32_t f29:1;
	  uint32_t f30:1;
	  uint32_t f31:1;
  } bit;
} TCanReceiveStatus;

typedef struct{
	uint8_t RxData[8];
}CAN_filtr_struct;

typedef struct{
// External Params
	FDCAN_TxHeaderTypeDef TxMessage;
	uint8_t aTxData[8];
	FDCAN_RxHeaderTypeDef RxMessage;
	uint8_t aRxData[8];
// Internal_Params
////////////////////////
	uint32_t Resived_Pdo;
	uint32_t Resived_Sdo;
    uint8_t Transmited;
////////////////////////
    CAN_filtr_struct MBS_filtr;
    CAN_filtr_struct filtr[32];

    uint16_t CAN_Speed;
    uint32_t IdLength;

    FDCAN_HandleTypeDef Can_id;

    uint32_t *PdoRxBuff;
    uint32_t *PdoTxBuff;
    uint32_t *SdoRxBuff;
    uint32_t *SdoTxBuff;
    uint32_t *SdoRxEn;
    uint32_t *SdoTxEn;
    uint32_t *TimersPdoRxBuff;
    uint32_t *TimersPdoTxBuff;
    uint8_t PdoRx_Number;
    uint8_t PdoTx_Number;
    uint8_t SdoRx_Number;
    uint8_t SdoTx_Number;

    uint8_t Current_PdoRx_Number;
    uint8_t Current_PdoTx_Number;
    uint8_t Current_SdoRx_Number;
    uint8_t Current_SdoTx_Number;

    uint8_t SendData_PdoTx;
    uint8_t SendData_SdoTx;

    uint32_t Param_Low_TX;
    uint32_t Param_High_TX;

    uint8_t Last_PdoRx_Filtr_Updated;
    uint8_t Last_SdoRx_Filtr_Updated;

    uint8_t GetData_PdoRx;
    uint8_t GetData_SdoRx;

    uint8_t GetData_MBS;
    uint8_t SendData_MBS;

    uint32_t Param_Low_SdoRx;
    uint32_t Param_High_SdoRx;

    uint32_t Param_Low_PdoRx;
    uint32_t Param_High_PdoRx;

    uint32_t Sample_Time;

    uint32_t MBS_RX_Id;
    uint32_t MBS_TX_Id;
    uint8_t MBS_Id;
    uint8_t MBS_Cmd;
    uint16_t MBS_Address;
    uint32_t MBS_Data;

    uint32_t Transmit_Error_Counter;
    uint32_t Transmit_Error_Counter_Previous;

    uint8_t Reset;
    uint8_t Inited;

/////////////////////////////

}CAN_Structure;



// List PDO_RX //
#define _PDOrx_CANid(__index__)           (1+(__index__-1)*4)
#define _PDOrx_AddrNum(__index__)         (2+(__index__-1)*4)
#define _PDOrx_Freq(__index__)            (3+(__index__-1)*4)
#define _PDOrx_Filtr(__index__)           (4+(__index__-1)*4)

// List PDO_TX //
#define _PDOtx_CANid(__index__)           (1+(__index__-1)*3)
#define _PDOtx_AddrNum(__index__)         (2+(__index__-1)*3)
#define _PDOtx_Freq(__index__)            (3+(__index__-1)*3)

// List SDO_RX //
#define _SDOrx_CANid(__index__)           (1+(__index__-1)*3)
#define _SDOrx_AddrNum(__index__)         (2+(__index__-1)*3)
#define _SDOrx_Filtr(__index__)           (3+(__index__-1)*3)

// List SDO_TX //
#define _SDOtx_CANid(__index__)           (1+(__index__-1)*2)
#define _SDOtx_AddrNum(__index__)         (2+(__index__-1)*2)

// List Timer_RX //
#define _TimerRx_counter(__index__)       (1+(__index__-1)*2)
#define _TimerRx_en(__index__)            (2+(__index__-1)*2)

// List Timer_TX //
#define _TimerTx_counter(__index__)       (1+(__index__-1)*2)
#define _TimerTx_en(__index__)            (2+(__index__-1)*2)

#define _11bit 0
#define _29bit 4

#define S_MBS  1
#define S_SDO  2
#define S_PDO  3
#define S_CTRL 4

#define SDO_TYPE 0
#define PDO_TYPE 1

void CAN_Init_Global_Structure(CAN_Structure* can_structure, uint8_t Can_ID);
int32_t CAN_Peripherial_Init(CAN_Structure* p, uint8_t CAN_ID_Number, uint8_t CAN_Speed_Number);
void CAN_Filters_Init(CAN_Structure* p);
void PDO_TX_SendData(CAN_Structure* p);
void PDO_TX_Update(CAN_Structure* p);
void SDO_TX_SendData(CAN_Structure* p);
void SDO_TX_Update(CAN_Structure* p);
void MBS_SendData(CAN_Structure* p);
void MBS_TX_Update(CAN_Structure* p);
void CAN_TX_Update(CAN_Structure* p);
void PDO_RX_Update(CAN_Structure* p);
void SDO_RX_Update(CAN_Structure* p);
void MBS_RX_Update(CAN_Structure* p);
void CAN_RX_Update(CAN_Structure* p);
void CAN_GetData(CAN_Structure* p);
void CAN_TxMessage(FDCAN_HandleTypeDef* can_id, FDCAN_TxHeaderTypeDef* TxMessage, uint8_t aData[]);

#endif
