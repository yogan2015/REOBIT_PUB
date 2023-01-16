#include "main.h"
#ifdef STM32H7xx_LL_SPI_H
#include "chip.h"

static SPI_TypeDef *GetSpiPort(char Id);


void SPI_init(char Id, char Master, char Mode, short BaudRate, char Length)
{
	SPI_TypeDef *SPIx = GetSpiPort(Id);
	LL_SPI_InitTypeDef SPI_InitStruct = {0};

	if (!SPIx) return;

	switch(Id)
	{
	#if defined(SPI1)
		case 0: LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1); break;
	#endif
	#if defined(SPI2)
		case 1: LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2); break;
	#endif
	#if defined(SPI3)
		case 2: LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3); break;
	#endif
	#if defined(SPI4)
		case 3: LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4); break;
	#endif
	#if defined(SPI5)
		case 4: LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5); break;
	#endif
	#if defined(SPI6)
		case 5: LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_SPI6); break;
	#endif
	}

	LL_SPI_DeInit(SPIx);

	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = Master ? LL_SPI_MODE_MASTER : LL_SPI_MODE_SLAVE ;
	if (Length == 16)
	{
		SPI_InitStruct.DataWidth=LL_SPI_DATAWIDTH_16BIT;
		LL_SPI_SetFIFOThreshold(SPIx,LL_SPI_FIFO_TH_01DATA);
	}
	else
	{
		SPI_InitStruct.DataWidth=LL_SPI_DATAWIDTH_8BIT;
		LL_SPI_SetFIFOThreshold(SPIx,LL_SPI_FIFO_TH_01DATA);
	}
	SPI_InitStruct.ClockPolarity =  (Mode & 0x2) ? LL_SPI_POLARITY_HIGH : LL_SPI_POLARITY_LOW;
	SPI_InitStruct.ClockPhase = 	(Mode & 0x1) ? LL_SPI_PHASE_2EDGE : LL_SPI_PHASE_1EDGE;
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
	SPI_InitStruct.BaudRate = (BaudRate & 0x7) << SPI_CFG1_MBR_Pos;
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
	SPI_InitStruct.CRCPoly = 7;

	LL_SPI_Init(SPIx, &SPI_InitStruct);
	LL_SPI_SetStandard(SPIx, LL_SPI_PROTOCOL_MOTOROLA);

	LL_SPI_Enable(SPIx);
	LL_SPI_StartMasterTransfer(SPIx);
}


short SPI_send(char Id, short Data)
{
	SPI_TypeDef *SPIx = GetSpiPort(Id);
	if (!SPIx) return 0xFF;
	LL_SPI_TransmitData8(SPIx, Data);

	while (LL_SPI_IsActiveFlag_RXP(SPIx) == RESET);
	return LL_SPI_ReceiveData8(SPIx);
}

void SPI_transmit(char Id, short Data)
{
	SPI_TypeDef *SPIx = GetSpiPort(Id);
	if (!SPIx) return;
	LL_SPI_TransmitData8(SPIx, Data);
}

short SPI_recieve(char Id)
{
	SPI_TypeDef *SPIx = GetSpiPort(Id);
	if (!SPIx) return 0xFF;
	return LL_SPI_ReceiveData8(SPIx);
}

char SPI_ready(char Id)
{
	SPI_TypeDef *SPIx = GetSpiPort(Id);
	if (!SPIx) return 0;
	return (LL_SPI_IsActiveFlag_RXP(SPIx) != RESET);
}

void SPI_int_config(char Id, char IT, char State)
{
//	SPI_TypeDef *SPIx = GetSpiPort(Id);
//	if (SPIx)
//	{
//	 switch (IT)
//	 {
//	  case SPI_CR2_RXNEIE :
//		  	  	  	  	  	if (State) LL_SPI_EnableIT_RXWNE(SPIx);
//		  	  	  	  	  	else LL_SPI_DisableIT_RXWNE(SPIx);
//		  	  	  	  	  	break;
//	  case SPI_CR2_ERRIE  :
//		  	  	  	  	  	if (State) LL_SPI_EnableIT_ERR (SPIx);
//	  	  	  	  	  	  	else  LL_SPI_DisableIT_ERR(SPIx);
//		  	  	  	  	  	break;
//	  case SPI_CR2_TXEIE  : if (State) LL_SPI_EnableIT_TXE(SPIx);
//		  	  	  	  	  	else LL_SPI_DisableIT_TXE(SPIx);
//		  	  	  	  	  	break;
//	 }
//	}
}



static SPI_TypeDef *GetSpiPort(char Id)
{
	switch(Id)
	{
	#if defined(SPI1)
		case 0: return SPI1;
	#endif
	#if defined(SPI2)
		case 1: return SPI2;
	#endif
	#if defined(SPI3)
		case 2: return SPI3;
	#endif
	#if defined(SPI4)
		case 3: return SPI4;
	#endif
	#if defined(SPI5)
		case 4: return SPI5;
	#endif
	#if defined(SPI6)
		case 5: return SPI6;
	#endif
	}
	return (SPI_TypeDef *)0;
}
#endif
