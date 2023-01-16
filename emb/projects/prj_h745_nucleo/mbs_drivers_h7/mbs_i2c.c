#include "main.h"
#ifdef __STM32F4xx_LL_I2C_H
#include "chip.h"

#define I2C_TIMEOUT   1000
#define I2C_WRITE 1
#define I2C_READ 0


static long I2C_Speeds[3] = { 0, 0, 0 };

static I2C_TypeDef *GetI2cPort(char Id);
void I2C_Send7bitAddress(I2C_TypeDef *I2Cx, uint8_t Data, uint8_t Direction);

void I2C_init(char Id, long Speed)
{
	I2C_TypeDef *I2Cx;
	LL_I2C_InitTypeDef I2C_InitStructure = {0};
	
	I2Cx = GetI2cPort(Id);
	if (!I2Cx) return;
	
	switch(Id)
	{
		case 0: LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1); break;
		case 1: LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2); break;
		case 2: LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C3); break;
	}
	
	LL_I2C_DeInit(I2Cx);
	
	if (!Speed) Speed = I2C_Speeds[(uint8_t)Id];
	else I2C_Speeds[(uint8_t)Id] = Speed;

	I2C_InitStructure.ClockSpeed = (uint32_t)Speed;
	I2C_InitStructure.PeripheralMode = LL_I2C_MODE_I2C;
	I2C_InitStructure.DutyCycle = LL_I2C_DUTYCYCLE_2;
	I2C_InitStructure.OwnAddress1 = 0;
	I2C_InitStructure.TypeAcknowledge = LL_I2C_NACK;
	I2C_InitStructure.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;

	LL_I2C_Init(I2Cx, &I2C_InitStructure);
	LL_I2C_Enable(I2Cx);
}

char I2C_write(char Id, char DeviceAddr, char *pBuffer, char NumByteToWrite)
{
	I2C_TypeDef *I2Cx;
	uint16_t I2CTimeout;
	
	I2Cx = GetI2cPort(Id);
	if (!I2Cx) return I2C_ERR_INIT_FAILED;
	
	I2CTimeout = I2C_TIMEOUT;
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx))
	{	
		if(I2CTimeout--) continue;
		I2C_init(Id, 0);
		return I2C_ERR_BUSY;
	}
	
	LL_I2C_GenerateStartCondition(I2Cx);
	
	I2CTimeout = I2C_TIMEOUT;
	while(!(
			LL_I2C_IsActiveFlag_BUSY(I2Cx) && 
			LL_I2C_IsActiveFlag_MSL(I2Cx) && 
			LL_I2C_IsActiveFlag_SB(I2Cx)
			)
		  ) 
	{
		if((I2CTimeout--) == 0) 
		{
			return I2C_ERR_TX_DATA;
		}
	}
	
	I2C_Send7bitAddress(I2Cx, DeviceAddr, I2C_WRITE);
	
	I2CTimeout = I2C_TIMEOUT;
	while(!(
			LL_I2C_IsActiveFlag_BUSY(I2Cx) && 
			LL_I2C_IsActiveFlag_MSL(I2Cx) && 
			LL_I2C_IsActiveFlag_ADDR(I2Cx) && 
			LL_I2C_IsActiveFlag_TXE(I2Cx) && 
			LL_I2C_GetTransferDirection(I2Cx)
			)
		  ) 
	{
		if((I2CTimeout--) == 0) 
		{
			return I2C_ERR_TX_DATA;
		}
	}
	
	while(NumByteToWrite--)
	{
		LL_I2C_TransmitData8(I2Cx, *pBuffer++);
		
		I2CTimeout = I2C_TIMEOUT;
		while(!(
				LL_I2C_GetTransferDirection(I2Cx) &&
				LL_I2C_IsActiveFlag_BUSY(I2Cx) &&
				LL_I2C_IsActiveFlag_MSL(I2Cx) &&
				LL_I2C_IsActiveFlag_TXE(I2Cx) &&
				LL_I2C_IsActiveFlag_BTF(I2Cx)
			)) 
		{
			if((I2CTimeout--) == 0) 
			{
				return I2C_ERR_TX_DATA;
			}
		}
	}
	
	LL_I2C_GenerateStopCondition(I2Cx);
	
	return I2C_SUCCESS;
}

char I2C_read(char Id, char DeviceAddr, char *pBuffer, char NumByteToWrite, char NumByteToRead)
{
	I2C_TypeDef *I2Cx;
	uint16_t I2CTimeout;
	char *pRxBuffer = pBuffer;
	
	I2Cx = GetI2cPort(Id);
	if (!I2Cx) return I2C_ERR_INIT_FAILED;
	
	I2CTimeout = I2C_TIMEOUT;
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx))
	{	
		if(I2CTimeout--) continue;
		I2C_init(Id, 0);
		return I2C_ERR_BUSY;
	}	
	
	LL_I2C_GenerateStartCondition(I2Cx);
	
	I2CTimeout = I2C_TIMEOUT;
	while(!(
			LL_I2C_IsActiveFlag_BUSY(I2Cx) && 
			LL_I2C_IsActiveFlag_MSL(I2Cx) && 
			LL_I2C_IsActiveFlag_SB(I2Cx)
			)
		  ) 
	{
		if((I2CTimeout--) == 0) 
		{
			return I2C_ERR_RX_DATA;
		}
	}
	
	I2C_Send7bitAddress(I2Cx, DeviceAddr, I2C_WRITE);
	
	I2CTimeout = I2C_TIMEOUT;
	while(!(
			LL_I2C_IsActiveFlag_BUSY(I2Cx) && 
			LL_I2C_IsActiveFlag_MSL(I2Cx) && 
			LL_I2C_IsActiveFlag_ADDR(I2Cx) && 
			LL_I2C_IsActiveFlag_TXE(I2Cx) && 
			LL_I2C_GetTransferDirection(I2Cx)
			)
		  ) 
	{
		if((I2CTimeout--) == 0) 
		{
			return I2C_ERR_RX_DATA;
		}
	}
	
	while(NumByteToWrite--)
	{
		LL_I2C_TransmitData8(I2Cx, *pBuffer++);
		
		I2CTimeout = I2C_TIMEOUT;
		while(!(
				LL_I2C_GetTransferDirection(I2Cx) &&
				LL_I2C_IsActiveFlag_BUSY(I2Cx) &&
				LL_I2C_IsActiveFlag_MSL(I2Cx) &&
				LL_I2C_IsActiveFlag_TXE(I2Cx) &&
				LL_I2C_IsActiveFlag_BTF(I2Cx)
			)) 
		{
			if((I2CTimeout--) == 0) 
			{
				return I2C_ERR_TX_DATA;
			}
		}
	}

	LL_I2C_GenerateStartCondition(I2Cx);
	
	I2CTimeout = I2C_TIMEOUT;
	while(!(
			LL_I2C_IsActiveFlag_BUSY(I2Cx) && 
			LL_I2C_IsActiveFlag_MSL(I2Cx) && 
			LL_I2C_IsActiveFlag_SB(I2Cx)
			)
		  ) 
	{
		if((I2CTimeout--) == 0) 
		{
			return I2C_ERR_RX_DATA;
		}
	}
	
	I2C_Send7bitAddress(I2Cx, DeviceAddr, I2C_READ);
	
	I2CTimeout = I2C_TIMEOUT;	
	while(!(
			LL_I2C_IsActiveFlag_BUSY(I2Cx) && 
			LL_I2C_IsActiveFlag_MSL(I2Cx) && 
			LL_I2C_IsActiveFlag_ADDR(I2Cx)
			)
		  ) 
	{
		if((I2CTimeout--) == 0) 
		{
			return I2C_ERR_RX_DATA;
		}
	}

	while(NumByteToRead--)
	{
		LL_I2C_AcknowledgeNextData(I2Cx, (NumByteToRead != 0) ? LL_I2C_ACK : LL_I2C_NACK);

		I2CTimeout = I2C_TIMEOUT;
		while(!(
				LL_I2C_IsActiveFlag_BUSY(I2Cx) && 
				LL_I2C_IsActiveFlag_MSL(I2Cx) && 
				LL_I2C_IsActiveFlag_RXNE(I2Cx)
				)
			  ) 
		{
			if((I2CTimeout--) == 0) 
			{
				return I2C_ERR_RX_DATA;
			}
		}

		*pRxBuffer++ = LL_I2C_ReceiveData8(I2Cx);
	}

	LL_I2C_GenerateStopCondition(I2Cx);
	
	return I2C_SUCCESS;		
}

void I2C_Send7bitAddress(I2C_TypeDef *I2Cx, uint8_t Data, uint8_t Direction)
{
	if(Direction == I2C_WRITE)
	{
		LL_I2C_TransmitData8(I2Cx, (Data << 1) | I2C_WRITE);
	}
	else if(Direction == I2C_READ)
	{
		LL_I2C_TransmitData8(I2Cx, (Data << 1) | I2C_READ);
	}
}

static I2C_TypeDef *GetI2cPort(char Id)
{
	switch(Id)
	{
		case 0: return I2C1;
		case 1: return I2C2;
		case 2: return I2C3;
	}
	return (I2C_TypeDef *)0;	
}
#endif
