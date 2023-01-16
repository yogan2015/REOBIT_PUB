#include "main.h"
#ifdef STM32H7xx_HAL_FDCAN_H
#include "mbs_can.h"
#include "header.h"



CAN_Structure g_CAN1;
CAN_Structure g_CAN2;
uint32_t status_canTx;

extern FDCAN_TxHeaderTypeDef TxHeader;
extern uint8_t TxData[8];

CAN_Speed_Str CAN_Speed[] = {
		{16, 15, 84, 15, 16, 15, 84, 15},// 50kbit/s
		{8, 15, 84, 15, 8, 15, 84, 15},// 100kbit/s
		{4, 24, 135, 24, 4, 24, 135, 24},// 125kbit/s
		{2, 24, 135, 24, 2, 24, 135, 24},// 250kbit/s
		{1, 24, 135, 24, 1, 24, 135, 24},// 500kbit/s
		{1, 15, 90, 15, 1, 15, 90, 15},// 800kbit/s
		{1, 11, 68, 11, 1, 11, 68, 11}// 1Mbit/s
};

void CAN_Init_Global_Structure(CAN_Structure* can_structure, uint8_t Can_ID)
{
	can_structure->Inited = 0;
	can_structure->TxMessage.Identifier = 0;
	can_structure->TxMessage.IdType = 0;
	can_structure->TxMessage.TxFrameType = 0;
	can_structure->TxMessage.DataLength = 0;
	can_structure->TxMessage.ErrorStateIndicator= 0;
	can_structure->TxMessage.BitRateSwitch = 0;
	can_structure->TxMessage.FDFormat = 0;
	can_structure->TxMessage.TxEventFifoControl = 0;
	can_structure->TxMessage.MessageMarker = 0;

    can_structure->aTxData[0]=0;
    can_structure->aTxData[1]=0;
    can_structure->aTxData[2]=0;
    can_structure->aTxData[3]=0;
    can_structure->aTxData[4]=0;
    can_structure->aTxData[5]=0;
    can_structure->aTxData[6]=0;
    can_structure->aTxData[7]=0;

    can_structure->RxMessage.Identifier = 0;
    can_structure->RxMessage.IdType = 0;
    can_structure->RxMessage.RxFrameType = 0;
    can_structure->RxMessage.DataLength = 0;
    can_structure->RxMessage.ErrorStateIndicator = 0;
    can_structure->RxMessage.BitRateSwitch = 0;
    can_structure->RxMessage.FDFormat = 0;
    can_structure->RxMessage.RxTimestamp = 0;
    can_structure->RxMessage.FilterIndex = 0;
    can_structure->RxMessage.IsFilterMatchingFrame = 0;

    can_structure->aRxData[0]=0;
    can_structure->aRxData[1]=0;
    can_structure->aRxData[2]=0;
    can_structure->aRxData[3]=0;
    can_structure->aRxData[4]=0;
    can_structure->aRxData[5]=0;
    can_structure->aRxData[6]=0;
    can_structure->aRxData[7]=0;

    can_structure->Resived_Pdo = 0;
    can_structure->Resived_Sdo = 0;
    can_structure->Last_PdoRx_Filtr_Updated = 0;
    can_structure->Last_SdoRx_Filtr_Updated = 0;

    for(int i = 0; i < 32; ++i)
    {
        can_structure->filtr[i].RxData[0]=0;
        can_structure->filtr[i].RxData[1]=0;
        can_structure->filtr[i].RxData[2]=0;
        can_structure->filtr[i].RxData[3]=0;
        can_structure->filtr[i].RxData[4]=0;
        can_structure->filtr[i].RxData[5]=0;
        can_structure->filtr[i].RxData[6]=0;
        can_structure->filtr[i].RxData[7]=0;
    }

    can_structure->MBS_filtr.RxData[0]=0;
	can_structure->MBS_filtr.RxData[1]=0;
	can_structure->MBS_filtr.RxData[2]=0;
	can_structure->MBS_filtr.RxData[3]=0;
	can_structure->MBS_filtr.RxData[4]=0;
	can_structure->MBS_filtr.RxData[5]=0;
	can_structure->MBS_filtr.RxData[6]=0;
	can_structure->MBS_filtr.RxData[7]=0;

    switch(Can_ID)
    {
    case 0:
        can_structure->Can_id.Instance = FDCAN1;
    	break;
    case 1:
        can_structure->Can_id.Instance = FDCAN2;
    	break;
    }
    can_structure->Can_id.ErrorCode = 0;
    can_structure->CAN_Speed= 0;
    can_structure->Transmited= 1;

    can_structure->Sample_Time = 0;

    can_structure->PdoRxBuff = 0;
    can_structure->PdoTxBuff = 0;
    can_structure->SdoRxBuff = 0;
    can_structure->SdoTxBuff = 0;
    can_structure->SdoRxEn = 0;
    can_structure->SdoTxEn = 0;
    can_structure->TimersPdoRxBuff = 0;
    can_structure->TimersPdoTxBuff = 0;

    can_structure->PdoRx_Number = 0;
    can_structure->PdoTx_Number = 0;
    can_structure->SdoRx_Number = 0;
    can_structure->SdoTx_Number = 0;

    can_structure->SendData_PdoTx = 0;
    can_structure->SendData_SdoTx = 0;
    can_structure->GetData_PdoRx = 0;
    can_structure->GetData_SdoRx = 0;

    can_structure->SendData_MBS = 0;
    can_structure->GetData_MBS = 0;

    can_structure->Reset = 0;
}

int32_t CAN_Peripherial_Init(CAN_Structure* p, uint8_t CAN_ID_Number, uint8_t CAN_Speed_Number)
{

    HAL_FDCAN_Stop(&(p->Can_id));

	HAL_FDCAN_DeactivateNotification(&(p->Can_id), FDCAN_IT_RX_FIFO0_NEW_MESSAGE);
	HAL_FDCAN_DeactivateNotification(&(p->Can_id), FDCAN_IT_RX_FIFO1_NEW_MESSAGE);
	HAL_FDCAN_DeactivateNotification(&(p->Can_id), FDCAN_IT_TX_FIFO_EMPTY);

	memset(&p->Can_id, 0, sizeof(FDCAN_HandleTypeDef));
	switch(CAN_ID_Number)
	{
	case 0:
		p->Can_id.Instance = FDCAN1;
	break;
	case 1:
		p->Can_id.Instance = FDCAN2;
	break;
	}
	p->Can_id.Init.FrameFormat = FDCAN_CLASSIC_CAN;
	p->Can_id.Init.Mode = FDCAN_MODE_NORMAL;
	p->Can_id.Init.AutoRetransmission = DISABLE;
	p->Can_id.Init.TransmitPause = DISABLE;
	p->Can_id.Init.ProtocolException = DISABLE;
	p->Can_id.Init.NominalPrescaler = CAN_Speed[CAN_Speed_Number].NominalPrescaler;
	p->Can_id.Init.NominalSyncJumpWidth = CAN_Speed[CAN_Speed_Number].NominalSyncJumpWidth;
	p->Can_id.Init.NominalTimeSeg1 = CAN_Speed[CAN_Speed_Number].NominalTimeSeg1;
	p->Can_id.Init.NominalTimeSeg2 = CAN_Speed[CAN_Speed_Number].NominalTimeSeg2;
	p->Can_id.Init.DataPrescaler = CAN_Speed[CAN_Speed_Number].DataPrescaler;
	p->Can_id.Init.DataSyncJumpWidth = CAN_Speed[CAN_Speed_Number].DataSyncJumpWidth;
	p->Can_id.Init.DataTimeSeg1 = CAN_Speed[CAN_Speed_Number].DataTimeSeg1;
	p->Can_id.Init.DataTimeSeg2 = CAN_Speed[CAN_Speed_Number].DataTimeSeg2;
	p->Can_id.Init.MessageRAMOffset = 0;
	p->Can_id.Init.StdFiltersNbr = 120;
	p->Can_id.Init.ExtFiltersNbr = 60;
	p->Can_id.Init.RxFifo0ElmtsNbr = 1;
	p->Can_id.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
	p->Can_id.Init.RxFifo1ElmtsNbr = 1;
	p->Can_id.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
	p->Can_id.Init.RxBuffersNbr = 0;
	p->Can_id.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
	p->Can_id.Init.TxEventsNbr = 0;
	p->Can_id.Init.TxBuffersNbr = 0;
	p->Can_id.Init.TxFifoQueueElmtsNbr = 1;
	p->Can_id.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
	p->Can_id.Init.TxElmtSize = FDCAN_DATA_BYTES_8;

	if (HAL_FDCAN_Init(&p->Can_id) != HAL_OK)
	{
	/* Initialization Error */
	Error_Handler();
	}

	/* Start the FDCAN module */
	if (HAL_FDCAN_Start(&p->Can_id) != HAL_OK)
	{
	/* Start Error */
	Error_Handler();
	}

	if (HAL_FDCAN_ActivateNotification(&p->Can_id, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
	{
	/* Notification Error */
	Error_Handler();
	}



	if (HAL_FDCAN_ActivateNotification(&p->Can_id, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
	{
	/* Notification Error */
	Error_Handler();
	}

	if (HAL_FDCAN_ActivateNotification(&p->Can_id, FDCAN_IT_TX_FIFO_EMPTY, 0) != HAL_OK)
	{
	/* Notification Error */
	Error_Handler();
	}

     return 1;
}

void CAN_Filters_Init(CAN_Structure* p)
{
	FDCAN_FilterTypeDef sFilterConfig = {0};

	sFilterConfig.IdType = p->IdLength;
	sFilterConfig.FilterIndex = 0;
	sFilterConfig.FilterType = FDCAN_FILTER_MASK;
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	sFilterConfig.FilterID1 = p->MBS_RX_Id;

	switch(sFilterConfig.IdType)
	{
	case FDCAN_STANDARD_ID:
		sFilterConfig.FilterID2 = 0x7FF;
		break;
	case FDCAN_EXTENDED_ID:
		sFilterConfig.FilterID2 = 0x1FFFFFFF;
		break;
	}

	if (HAL_FDCAN_ConfigFilter(&(p->Can_id), &sFilterConfig) != HAL_OK)
	{
		/* Filter configuration Error */
		Error_Handler();
	}

	for(int i = 1; i <= p->PdoRx_Number; ++i)
	{
		sFilterConfig.IdType = p->IdLength;
		sFilterConfig.FilterIndex = i;
		sFilterConfig.FilterType = FDCAN_FILTER_MASK;
		sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
		sFilterConfig.FilterID1 = p->PdoRxBuff[_PDOrx_CANid(i)];

		switch(sFilterConfig.IdType)
		{
		case FDCAN_STANDARD_ID:
			sFilterConfig.FilterID2 = 0x7FF;
			break;
		case FDCAN_EXTENDED_ID:
			sFilterConfig.FilterID2 = 0x1FFFFFFF;
			break;
		}

		if (HAL_FDCAN_ConfigFilter(&(p->Can_id), &sFilterConfig) != HAL_OK)
		{
			/* Filter configuration Error */
			Error_Handler();
		}
	}

	for(int i = 1; i <= p->SdoRx_Number; ++i)
	{
		sFilterConfig.IdType = p->IdLength;
		sFilterConfig.FilterIndex = p->PdoRx_Number + i;
		sFilterConfig.FilterType = FDCAN_FILTER_MASK;
		sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
		sFilterConfig.FilterID1 = p->SdoRxBuff[_SDOrx_CANid(i)];

		switch(sFilterConfig.IdType)
		{
		case FDCAN_STANDARD_ID:
			sFilterConfig.FilterID2 = 0x7FF;
			break;
		case FDCAN_EXTENDED_ID:
			sFilterConfig.FilterID2 = 0x1FFFFFFF;
			break;
		}

		if (HAL_FDCAN_ConfigFilter(&(p->Can_id), &sFilterConfig) != HAL_OK)
		{
			/* Filter configuration Error */
			Error_Handler();
		}
	}

	HAL_FDCAN_ConfigGlobalFilter(&(p->Can_id), FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

}

void PDO_TX_SendData(CAN_Structure* p)
{

	  /* Prepare Tx Header */
	p->TxMessage.IdType   = p->IdLength;
	p->TxMessage.Identifier = p->PdoTxBuff[_PDOtx_CANid(p->Current_PdoTx_Number)];
	p->TxMessage.TxFrameType = FDCAN_DATA_FRAME;
	p->TxMessage.DataLength = FDCAN_DLC_BYTES_8;
	p->TxMessage.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	p->TxMessage.BitRateSwitch = FDCAN_BRS_OFF;
	p->TxMessage.FDFormat = FDCAN_CLASSIC_CAN;
	p->TxMessage.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	p->TxMessage.MessageMarker = 0;


	p->aTxData[7] = (uint8_t) p->Param_Low_TX;
	p->aTxData[6] = (uint8_t) (p->Param_Low_TX >> 8);
	p->aTxData[5] = (uint8_t) (p->Param_Low_TX >> 16);
	p->aTxData[4] = (uint8_t) (p->Param_Low_TX >> 24);
	p->aTxData[3] = (uint8_t) p->Param_High_TX;
	p->aTxData[2] = (uint8_t) (p->Param_High_TX >> 8);
	p->aTxData[1] = (uint8_t) (p->Param_High_TX >> 16);
	p->aTxData[0] = (uint8_t) (p->Param_High_TX >> 24);

	CAN_TxMessage(&(p->Can_id), &(p->TxMessage), (p->aTxData));
	p->Transmited = 0;
	p->TimersPdoTxBuff[_TimerTx_en(p->Current_PdoTx_Number)] = 0;
}

void PDO_TX_Update(CAN_Structure* p)
{
	for(int i = 1; i <= p->PdoTx_Number; ++i)
	{
		p->TimersPdoTxBuff[_TimerTx_counter(i)] += p->Sample_Time;
		if (
				(p->TimersPdoTxBuff[_TimerTx_counter(i)])
			>
				(_IQ16div(_IQ16(1.0),(p->PdoTxBuff[_PDOtx_Freq(i)] << 16)) << 8)
		)
		{
			p->TimersPdoTxBuff[_TimerTx_counter(i)] = 0;
			p->TimersPdoTxBuff[_TimerTx_en(i)] = 1;
		}
	}
	if(!p->SendData_PdoTx)
	{
		for(int i = 1; i <= p->PdoTx_Number; ++i)
		{
			if(p->TimersPdoTxBuff[_TimerTx_en(i)])
			{
				p->Current_PdoTx_Number = i;
				p->SendData_PdoTx = 1;
				break;
			}
		}
	}
}

void SDO_TX_SendData(CAN_Structure* p)
{

	  /* Prepare Tx Header */
	p->TxMessage.IdType   = p->IdLength;
	p->TxMessage.Identifier = p->SdoTxBuff[_SDOtx_CANid(p->Current_SdoTx_Number)];
	p->TxMessage.TxFrameType = FDCAN_DATA_FRAME;
	p->TxMessage.DataLength = FDCAN_DLC_BYTES_8;
	p->TxMessage.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	p->TxMessage.BitRateSwitch = FDCAN_BRS_OFF;
	p->TxMessage.FDFormat = FDCAN_CLASSIC_CAN;
	p->TxMessage.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	p->TxMessage.MessageMarker = 0;


	p->aTxData[7] = (uint8_t) p->Param_Low_TX;
	p->aTxData[6] = (uint8_t) (p->Param_Low_TX >> 8);
	p->aTxData[5] = (uint8_t) (p->Param_Low_TX >> 16);
	p->aTxData[4] = (uint8_t) (p->Param_Low_TX >> 24);
	p->aTxData[3] = (uint8_t) p->Param_High_TX;
	p->aTxData[2] = (uint8_t) (p->Param_High_TX >> 8);
	p->aTxData[1] = (uint8_t) (p->Param_High_TX >> 16);
	p->aTxData[0] = (uint8_t) (p->Param_High_TX >> 24);

	CAN_TxMessage(&(p->Can_id), &(p->TxMessage), (p->aTxData));
	p->Transmited = 0;
	p->SdoTxEn[p->Current_SdoTx_Number] = 0;
}

void SDO_TX_Update(CAN_Structure* p)
{
	if(!p->SendData_SdoTx)
	{
		for(int i = 1; i <= p->SdoTx_Number; ++i)
		{
			if(p->SdoTxEn[i])
			{
				p->Current_SdoTx_Number = i;
				p->SendData_SdoTx = 1;
				break;
			}
		}
	}
}

void MBS_SendData(CAN_Structure* p)
{
	  /* Prepare Tx Header */
	p->TxMessage.IdType   = p->IdLength;
	p->TxMessage.Identifier = p->MBS_TX_Id;
	p->TxMessage.TxFrameType = FDCAN_DATA_FRAME;
	p->TxMessage.DataLength = FDCAN_DLC_BYTES_8;
	p->TxMessage.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	p->TxMessage.BitRateSwitch = FDCAN_BRS_OFF;
	p->TxMessage.FDFormat = FDCAN_CLASSIC_CAN;
	p->TxMessage.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	p->TxMessage.MessageMarker = 0;

    p->aTxData[0] =(uint8_t) (p->MBS_Data);
    p->aTxData[1] =(uint8_t) (p->MBS_Data >> 8);
    p->aTxData[2] =(uint8_t) (p->MBS_Data >> 16);
    p->aTxData[3] =(uint8_t) (p->MBS_Data >> 24);

    p->aTxData[4] =(uint8_t) (p->MBS_Address);
    p->aTxData[5] =(uint8_t) (p->MBS_Address >> 8);

    p->aTxData[6] =(uint8_t) (p->MBS_Id);

    p->aTxData[7] =(uint8_t) (p->MBS_Cmd);

	CAN_TxMessage(&(p->Can_id), &(p->TxMessage), (p->aTxData));
	p->Transmited = 0;
}

void MBS_TX_Update(CAN_Structure* p)
{
	if(p->SendData_MBS)
	{
		p->MBS_Id = 0x43;
	}
}

void CAN_TX_Update(CAN_Structure* p)
{
	if(p->Inited)
	{
		PDO_TX_Update(p);
		SDO_TX_Update(p);
		MBS_TX_Update(p);
	}
}

void PDO_RX_Update(CAN_Structure* p)
{
	if(p->Resived_Pdo)
	{
		if(p->Last_PdoRx_Filtr_Updated <= p->PdoRx_Number)
		{
			if(p->Resived_Pdo & (1 << (p->Last_PdoRx_Filtr_Updated - 1)))
			{
				p->Resived_Pdo &= (~(1 << (p->Last_PdoRx_Filtr_Updated - 1)));
				p->Param_Low_PdoRx  = (p->filtr[p->Last_PdoRx_Filtr_Updated].RxData[4] <<24) | (p->filtr[p->Last_PdoRx_Filtr_Updated].RxData[5]<<16) | (p->filtr[p->Last_PdoRx_Filtr_Updated].RxData[6]<<8) | p->filtr[p->Last_PdoRx_Filtr_Updated].RxData[7];
				p->Param_High_PdoRx = (p->filtr[p->Last_PdoRx_Filtr_Updated].RxData[0] <<24) | (p->filtr[p->Last_PdoRx_Filtr_Updated].RxData[1]<<16) | (p->filtr[p->Last_PdoRx_Filtr_Updated].RxData[2]<<8) | p->filtr[p->Last_PdoRx_Filtr_Updated].RxData[3];
				p->TimersPdoRxBuff[_TimerRx_counter(p->Last_PdoRx_Filtr_Updated)] = 0;
				p->GetData_PdoRx = 1;
			}
			else
			{
				p->Last_PdoRx_Filtr_Updated++;
			}
		}
		else
		{
			p->Last_PdoRx_Filtr_Updated = 1;
		}
	}

	for(int i = 1; i <= p->PdoRx_Number; ++i)
	{
		p->TimersPdoRxBuff[_TimerRx_counter(i)] += p->Sample_Time;
		if (
				(p->TimersPdoRxBuff[_TimerRx_counter(i)])
			>
				(_IQ16div(_IQ16(1.0),(p->PdoRxBuff[_PDOrx_Freq(i)] << 16)) << 8)
		)
		{
			p->TimersPdoRxBuff[_TimerRx_counter(i)] = 0;
			p->Reset = 1;
		}
	}
}

void SDO_RX_Update(CAN_Structure* p)
{
	if(p->Resived_Sdo)
	{
		if(p->Last_SdoRx_Filtr_Updated <= p->SdoRx_Number)
		{
			if(p->Resived_Sdo & (1 << (p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number - 1)))
			{
				p->Resived_Sdo &= (~(1 << (p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number - 1)));
				p->Param_Low_SdoRx  = (p->filtr[p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number].RxData[4] <<24) | (p->filtr[p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number].RxData[5]<<16) | (p->filtr[p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number].RxData[6]<<8) | p->filtr[p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number].RxData[7];
				p->Param_High_SdoRx = (p->filtr[p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number].RxData[0] <<24) | (p->filtr[p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number].RxData[1]<<16) | (p->filtr[p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number].RxData[2]<<8) | p->filtr[p->Last_SdoRx_Filtr_Updated + p->PdoRx_Number].RxData[3];
				p->GetData_SdoRx = 1;
			}
			else
			{
				p->Last_SdoRx_Filtr_Updated++;
			}
		}
		else
		{
			p->Last_SdoRx_Filtr_Updated = 1;
		}
	}
}

void MBS_RX_Update(CAN_Structure* p)
{
	if(p->GetData_MBS)
	{
		p->MBS_Id   = p->MBS_filtr.RxData[6];
		p->MBS_Cmd  = p->MBS_filtr.RxData[7];
		p->MBS_Address =(p->MBS_filtr.RxData[5] << 8) | (p->MBS_filtr.RxData[4]);
		p->MBS_Data =(p->MBS_filtr.RxData[3] << 24) | (p->MBS_filtr.RxData[2] << 16) | (p->MBS_filtr.RxData[1] << 8) |p->MBS_filtr.RxData[0];

		if(p->MBS_Cmd == 0x10)
		{
			p->GetData_MBS = 1;
		}
		else if(p->MBS_Cmd == 0x03)
		{
			p->GetData_MBS = 0;
			p->SendData_MBS = 1;
		}
	}
}

void CAN_RX_Update(CAN_Structure* p)
{
	if(p->Inited)
	{
		MBS_RX_Update(p);
		PDO_RX_Update(p);
		SDO_RX_Update(p);
	}
}

void CAN_GetData(CAN_Structure* p)
{
	uint32_t i = p->RxMessage.FilterIndex;
	if(i == 0)
	{
		uint8_t* Rx_Buffer_Ptr = (p->MBS_filtr.RxData);
		Rx_Buffer_Ptr[0] = p->aRxData[0];
		Rx_Buffer_Ptr[1] = p->aRxData[1];
		Rx_Buffer_Ptr[2] = p->aRxData[2];
		Rx_Buffer_Ptr[3] = p->aRxData[3];
		Rx_Buffer_Ptr[4] = p->aRxData[4];
		Rx_Buffer_Ptr[5] = p->aRxData[5];
		Rx_Buffer_Ptr[6] = p->aRxData[6];
		Rx_Buffer_Ptr[7] = p->aRxData[7];
		p->GetData_MBS = 1;
	}
	else
	{
		if(i <= p->PdoRx_Number)
		{
			p->Resived_Pdo |= 1 << (i - 1);
		}
		else
		{
			p->Resived_Sdo |= 1 << (i - 1);
		}

		uint8_t* Rx_Buffer_Ptr = (p->filtr[i].RxData);
		Rx_Buffer_Ptr[0] = p->aRxData[0];
		Rx_Buffer_Ptr[1] = p->aRxData[1];
		Rx_Buffer_Ptr[2] = p->aRxData[2];
		Rx_Buffer_Ptr[3] = p->aRxData[3];
		Rx_Buffer_Ptr[4] = p->aRxData[4];
		Rx_Buffer_Ptr[5] = p->aRxData[5];
		Rx_Buffer_Ptr[6] = p->aRxData[6];
		Rx_Buffer_Ptr[7] = p->aRxData[7];
	}
}

void CAN_TxMessage(FDCAN_HandleTypeDef* can_id, FDCAN_TxHeaderTypeDef* TxMessage, uint8_t aData[])
{
	status_canTx = HAL_FDCAN_AddMessageToTxFifoQ(can_id, TxMessage, aData);
}

#endif
