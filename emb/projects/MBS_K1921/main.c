#define MB_MODE 1
#include "inc/main.h"

#if defined(MB_MODE)
	#include "../../cmn/modbus/modbus_rtu.h"
#endif

// RS485 Communication driver structure
#if defined(MB_MODE)
	TMbRTUPort *Mb = (TMbRTUPort *)0x20000200;
#endif

// Project local function prototypes

#if defined(MB_MODE)
	static void ModbusUpdate(void);
	static void ModbusTxControl(char);
#endif

#if defined(MB_MODE)
	void USART0_RX_IRQHandler(void)
	{
	ModBusRTURxIsr(Mb);
	UART_ITStatusClear(NT_UART0, UART_ITSource_RxFIFOLevel);
	}

	void USART0_TX_IRQHandler(void)
	{
	ModBusRTUTxIsr(Mb);
	UART_ITStatusClear(NT_UART0, UART_ITSource_TxFIFOLevel);
	}
#endif

#if defined(MB_MODE)
	static void ModbusUpdate(void)
	{
	Mb->Params.Slave = BrdData->Slave;
	BrdData->Status.bit.Mb = Mb->Packet.Connected;

	ModBusRTUInvoke(Mb);
	ModBusRTUTimings(Mb);
	}

	static void ModbusTxControl(char Level)
	{
	GPIO_WriteBit(NT_GPIOE, GPIO_Pin_15, Level);
	}
#endif