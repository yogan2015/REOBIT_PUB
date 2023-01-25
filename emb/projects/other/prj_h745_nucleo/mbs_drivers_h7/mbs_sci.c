#include "main.h"
#ifdef STM32H7xx_LL_USART_H
#include "chip.h"

USART_TypeDef *GetUartRegs(char Id);


void SCI_init(char Id, short BaudRate, char Parity, char Length, char StopBits)
{
	USART_TypeDef *USARTx = GetUartRegs(Id);
	LL_USART_InitTypeDef USART_InitStructure = {0};

	if (!USARTx) return;

	switch(Id)
	{
	#if defined(USART1)
		case 0:   LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1); break;
	#endif
	#if defined(USART2)
		case 1:   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2); break;
	#endif
	#if defined(USART3)
		case 2:   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3); break;
	#endif
	#if defined(UART4)
		case 3:   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4); break;
	#endif
	#if defined(UART5)
		case 4:   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5); break;
	#endif
	#if defined(USART6)
		case 5:   LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6); break;
	#endif
	#if defined(UART7)
		case 6:   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7); break;
	#endif
	#if defined(UART8)
		case 7:   LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART8); break;
	#endif
	}

	USART_InitStructure.OverSampling = LL_USART_OVERSAMPLING_8;

	USART_InitStructure.BaudRate = (uint32_t)BaudRate * 100;
	USART_InitStructure.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStructure.StopBits =  (StopBits == 2) ? LL_USART_STOPBITS_2 : LL_USART_STOPBITS_1;
	switch(Parity)
	  {
	  	 case 1:  USART_InitStructure.Parity = LL_USART_PARITY_ODD;  break;
	  	 case 2:  USART_InitStructure.Parity = LL_USART_PARITY_EVEN; break;
	  	 default: USART_InitStructure.Parity = LL_USART_PARITY_NONE;
	  }
	USART_InitStructure.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStructure.HardwareFlowControl = LL_USART_HWCONTROL_NONE;


	LL_USART_Init(USARTx, &USART_InitStructure);
	LL_USART_ConfigAsyncMode(USARTx);
	LL_USART_Enable(USARTx);

	LL_USART_DisableIT_RXNE(USARTx);
	LL_USART_DisableIT_TC(USARTx);
}

char SCI_recieve(char Id)
{
	USART_TypeDef *USARTx = GetUartRegs(Id);
	if (!USARTx) return 0xFF;
	return LL_USART_ReceiveData8(USARTx);
}

void SCI_transmit(char Id, char Data)
{
	USART_TypeDef *USARTx = GetUartRegs(Id);
	if (!USARTx) return;
	LL_USART_TransmitData8(USARTx, Data);
}

char SCI_getstatus(char Id)
{
	return 0;
}

void SCI_reset(char Id)
{
}

void SCI_rx_enable(char Id)
{
//	USART_TypeDef *USARTx = GetUartRegs(Id);
//	if (!USARTx) return;
//	USARTx->CR1 |= USART_Mode_Rx;
}

void SCI_rx_disable(char Id)
{
//	USART_TypeDef *USARTx = GetUartRegs(Id);
//	if (!USARTx) return;
//	USARTx->CR1 &= ~USART_Mode_Rx;
}

void SCI_tx_enable(char Id)
{
//	USART_TypeDef *USARTx = GetUartRegs(Id);
//	if (!USARTx) return;
//	USARTx->CR1 |= USART_Mode_Tx;
}

void SCI_tx_disable(char Id)
{
//	USART_TypeDef *USARTx = GetUartRegs(Id);
//	if (!USARTx) return;
//	USARTx->CR1 &= ~USART_Mode_Tx;
}

void SCI_rx_int_enable(char Id)
{
	USART_TypeDef *USARTx = GetUartRegs(Id);
	if (!USARTx) return;
	LL_USART_EnableIT_RXNE(USARTx);
}

void SCI_rx_int_disable(char Id)
{
	USART_TypeDef *USARTx = GetUartRegs(Id);
	if (!USARTx) return;
	LL_USART_DisableIT_RXNE(USARTx);
}

void SCI_tx_int_enable(char Id)
{
	USART_TypeDef *USARTx = GetUartRegs(Id);
	if (!USARTx) return;
	LL_USART_EnableIT_TC(USARTx);
}

void SCI_tx_int_disable(char Id)
{
	USART_TypeDef *USARTx = GetUartRegs(Id);
	if (!USARTx) return;
	LL_USART_DisableIT_TC(USARTx);
}

USART_TypeDef *GetUartRegs(char Id)
{
	switch(Id)
	{
	#if defined(USART1)
		case 0: return USART1;
	#endif
	#if defined(USART2)
		case 1: return USART2;
	#endif
	#if defined(USART3)
		case 2: return USART3;
	#endif
	#if defined(UART4)
		case 3: return UART4;
	#endif
	#if defined(UART5)
		case 4: return UART5;
	#endif
	#if defined(USART6)
		case 5: return USART6;
	#endif
	#if defined(UART7)
		case 6: return UART7;
	#endif
	#if defined(UART8)
		case 7: return UART8;
	#endif
	}
	return 0;
}
#endif
