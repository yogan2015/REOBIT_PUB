#include "header.h"

M95X Eeprom;
TMbRTUPort Mb1;
TBrdData BrdData;

const TMbSlaveInfo SlaveInfo = {MB_ADR, DEVICE_NUMBER, VERSION, VERSION_DATE, "h745_reo", "STM32H745II" };

static void EepromSetCs(uint8_t);
static void ModbusTxControl7(char);

#if FILE_OP_ENABLE
	static short *GetFileRecord(short, short, short, char *, char *);
#endif

extern unsigned short* MBS_sGetData(unsigned short Addr,unsigned short Count,unsigned short *Mode);
extern unsigned short Bit;
extern void *Reg;


void InitBoardPeripherial(void)
{
	MBS_Board_GPIO_Init(); 	// In, Out,
	MBS_Board_SPI4_Init();	// +EEPROM and others
	MBS_Board_UART7_Init();	// +RS485 XT1 (MB1)
	MBS_Board_ADC_Init(); 	// ADC
	MBS_Board_TIM1_Init();	// PWMA
	MBS_Board_TIM8_Init();	// PWMB
	MBS_Board_TIM4_Init();	// ENC

	Eeprom.SpiId    = 3;
	Eeprom.SpiBaud  = 0x6;
	Eeprom.Type     = M95M02_TYPE;
	Eeprom.BusyTime = (uint16_t)(0.02*MAIN_ISR_FREQ);
	Eeprom.CsFunc   = EepromSetCs;
	M95X_Init(&Eeprom);

	ReadBoardData();

	// Modbus Communication driver initialization
	#ifdef MB
	Mb1.Params.UartID      = 6;
	Mb1.Params.Mode        = MB_MODE;
	Mb1.Params.Slave       = BrdData.Mb1.Slave;
	Mb1.Params.BaudRate    = BrdData.Mb1.Speed;
	Mb1.Params.BrrValue    = BrdData.Mb1.Speed;
	Mb1.Params.Parity      = BrdData.Mb1.Parity;
	Mb1.Params.StopBits    = BrdData.Mb1.StopBits;
	Mb1.Params.UserMode    = 0;
	Mb1.Params.RetryCount  = 0;
	Mb1.Params.Scale       = (MAIN_ISR_FREQ)/1000;
	Mb1.Params.RxDelay     = 5;
	Mb1.Params.TxDelay     = 2;
	#if MB_MODE == MB_RTU_SLAVE
	Mb1.Params.ConnTimeout = (uint16_t)(3.0*MAIN_ISR_FREQ);
	#elif MB_MODE == MB_RTU_MASTER
	Mb1.Params.ConnTimeout = (uint16_t)(0.2*MAIN_ISR_FREQ);
	#endif
	Mb1.Params.AckTimeout  = 1*MAIN_ISR_FREQ;
	Mb1.Params.SlaveInfo   = (TMbSlaveInfo *)&SlaveInfo;
	Mb1.Params.TrEnable    = ModbusTxControl7;
	Mb1.Params.GetData     = MBS_sGetData;
	#if FILE_OP_ENABLE
	Mb1.Params.GetRecord   = (TMbGetRecord)GetFileRecord;;
	#else
	Mb1.Params.GetRecord   = 0;
	#endif
	ModBusRTUInit(&Mb1);
	#endif
}

void ExecuteBoardBackgroundTask(void)
{
}

void Slow_ExecuteBoardInterruptTask (void)
{
//	if (IsBoardMemoryReady())
//	 {
//		if (Mb1.Params.Mode!=MB_RTU_MASTER)
//		{
//		 ModbusCheckParams(&Mb1, &BrdData ,&BrdData.Mb1);
//		}
//	 }
	MBS_MonExecute();
	DataProject_Update(&BrdData);
	M95X_Update(&Eeprom);
	ModBusRTUTimings(&Mb1);
	ModBusRTUInvoke(&Mb1);
//	 if (Mb1.Params.Mode!=MB_RTU_MASTER)
//	 {
//		 if (!Mb1.Packet.Connected) { ModbusTxControl1(0); BrdData.Status.bit.Mb1 = 0;}
//		 else { BrdData.Status.bit.Mb1 = 1; }
//	 }
}

void Fast_ExecuteBoardInterruptTask(void)
{

 M95X_Update(&Eeprom);
 DataProject_Update(&BrdData);
}


void MBS_Board_GPIO_Init(void) // In, Out,
{
	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOJ);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOK);

	  /* GPIO_OUT XP7 Initialisation state */
	  LL_GPIO_ResetOutputPin(DO0_GPIO_Port, DO0_Pin);
	  LL_GPIO_ResetOutputPin(DO1_GPIO_Port, DO1_Pin);
	  LL_GPIO_ResetOutputPin(DO2_GPIO_Port, DO2_Pin);
	  LL_GPIO_ResetOutputPin(DO3_GPIO_Port, DO3_Pin);
	  LL_GPIO_ResetOutputPin(DO4_GPIO_Port, DO4_Pin);
	  LL_GPIO_ResetOutputPin(DO5_GPIO_Port, DO5_Pin);
	  LL_GPIO_ResetOutputPin(DO6_GPIO_Port, DO6_Pin);
	  LL_GPIO_ResetOutputPin(DO7_GPIO_Port, DO7_Pin);
	  LL_GPIO_ResetOutputPin(DO8_GPIO_Port, DO8_Pin);
	  LL_GPIO_ResetOutputPin(DO9_GPIO_Port, DO9_Pin);

	  /* GPIO_OUT U2 LCD MT16S2S */
	  LL_GPIO_ResetOutputPin(LCD_B0_GPIO_Port, LCD_B0_Pin);
	  LL_GPIO_ResetOutputPin(LCD_G1_GPIO_Port, LCD_G1_Pin);
	  LL_GPIO_ResetOutputPin(LCD_B7_GPIO_Port, LCD_B7_Pin);

	  /* GPIO_OUT Config */
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;

	  GPIO_InitStruct.Pin = DO0_Pin;
	  	  	   LL_GPIO_Init(DO0_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DO1_Pin;
	  	  	   LL_GPIO_Init(DO1_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DO2_Pin;
	  	  	   LL_GPIO_Init(DO2_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DO3_Pin;
	   	  	   LL_GPIO_Init(DO3_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DO4_Pin;
	  	  	   LL_GPIO_Init(DO4_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DO5_Pin;
	  	  	   LL_GPIO_Init(DO5_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DO6_Pin;
	   	  	   LL_GPIO_Init(DO6_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DO7_Pin;
	   	  	   LL_GPIO_Init(DO7_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DO8_Pin;
	  	  	   LL_GPIO_Init(DO8_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DO9_Pin;
	  	  	   LL_GPIO_Init(DO9_GPIO_Port,  &GPIO_InitStruct);


	  GPIO_InitStruct.Pin = LCD_B0_Pin;
	   	  	   LL_GPIO_Init(LCD_B0_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = LCD_G1_Pin;
	  	  	   LL_GPIO_Init(LCD_G1_GPIO_Port,  &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = LCD_B7_Pin;
	  	  	   LL_GPIO_Init(LCD_B7_GPIO_Port,  &GPIO_InitStruct);

	  /* GPIO_IN Config */
  	  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;

  	  /* XP5 Discret Input */
  	  GPIO_InitStruct.Pin = DI0_Pin;
  	  	  	   LL_GPIO_Init(DI0_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI1_Pin;
  	  	  	   LL_GPIO_Init(DI1_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI2_Pin;
  	  	  	   LL_GPIO_Init(DI2_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI3_Pin;
  	  	  	   LL_GPIO_Init(DI3_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI4_Pin;
  	  	  	   LL_GPIO_Init(DI4_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI5_Pin;
  	  	  	   LL_GPIO_Init(DI5_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI6_Pin;
  	  	  	   LL_GPIO_Init(DI6_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI7_Pin;
  	  	  	   LL_GPIO_Init(DI7_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI8_Pin;
  	  	  	   LL_GPIO_Init(DI8_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI9_Pin;
  	  	  	   LL_GPIO_Init(DI9_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI10_Pin;
  	  	  	   LL_GPIO_Init(DI10_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI11_Pin;
  	  	  	   LL_GPIO_Init(DI11_GPIO_Port, &GPIO_InitStruct);

  	  /* XP4 DI Additional */
  	  GPIO_InitStruct.Pin = DI12_Pin;
  	  	  	   LL_GPIO_Init(DI12_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI13_Pin;
  	  	  	   LL_GPIO_Init(DI13_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = DI14_Pin;
  	  	  	   LL_GPIO_Init(DI14_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = DI15_Pin;
 	  	  	   LL_GPIO_Init(DI15_GPIO_Port, &GPIO_InitStruct);

 	  /* XP7 HALT Out (out from Semicube) */
 	  GPIO_InitStruct.Pin = HALTOUT1_Pin;
 	  	  	   LL_GPIO_Init(HALTOUT1_GPIO_Port, &GPIO_InitStruct);
 	  GPIO_InitStruct.Pin = HALTOUT2_Pin;
 	  	  	   LL_GPIO_Init(HALTOUT2_GPIO_Port, &GPIO_InitStruct);


  	  /* X16 X19 ERROR1,4 OPT_IN */
  	  GPIO_InitStruct.Pin = ERROR1_Pin;
  	  	  	   LL_GPIO_Init(ERROR1_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = ERROR4_Pin;
  	  	  	   LL_GPIO_Init(ERROR4_GPIO_Port, &GPIO_InitStruct);

  	  /* DD33 ERROR0, DD32 ERROR3  (out from Semicube) */
  	  GPIO_InitStruct.Pin = ERROR0_Pin;
  	  	  	   LL_GPIO_Init(ERROR0_GPIO_Port, &GPIO_InitStruct);
  	  GPIO_InitStruct.Pin = ERROR3_Pin;
  	  	  	   LL_GPIO_Init(ERROR3_GPIO_Port, &GPIO_InitStruct);
}

/////////////SPI4/////////////////////////////////////////////////////////////
void MBS_Board_SPI4_Init(void)
{
	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  LL_RCC_SetSPIClockSource(LL_RCC_SPI45_CLKSOURCE_PCLK2);

	  /* Peripheral clock enable */
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4);

	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);

	  /**SPI4 GPIO Configuration
	  PE12   ------> SPI4_SCK
	  PE13   ------> SPI4_MISO
	  PE14   ------> SPI4_MOSI
	  */
	  GPIO_InitStruct.Pin = SPI4_SCK_Pin|SPI4_MISO_Pin|SPI4_MOSI_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
	  LL_GPIO_Init(GPIOE, &GPIO_InitStruct);


	  /**/
	  LL_GPIO_SetOutputPin(SPI4_CS_GPIO_Port, SPI4_CS_Pin); 	// CS - EEPROM
	  LL_GPIO_SetOutputPin(LCD_G0_GPIO_Port, LCD_G0_Pin); 		// CS - MTT16S2S
	  LL_GPIO_SetOutputPin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin); 	// CS - XP2 BH24
	  LL_GPIO_SetOutputPin(GPIO1_GPIO_Port, GPIO1_Pin); 		//reserved CS/I2C - XP2 BH24
	  LL_GPIO_SetOutputPin(GPIO2_GPIO_Port, GPIO2_Pin); 		//reserved CS - XP2 BH24
	  LL_GPIO_SetOutputPin(GPIO3_GPIO_Port, GPIO3_Pin); 		//reserved CS - XP2 BH24
	  LL_GPIO_SetOutputPin(GPIO4_GPIO_Port, GPIO4_Pin); 		//reserved CS - XP2 BH24
	  LL_GPIO_SetOutputPin(GPIO5_GPIO_Port, GPIO5_Pin); 		//reserved CS - XP2 BH24
	  LL_GPIO_SetOutputPin(GPIO6_GPIO_Port, GPIO6_Pin); 		//reserved CS - XP1 BH24
	  LL_GPIO_SetOutputPin(GPIO7_GPIO_Port, GPIO7_Pin); 		//reserved CS - XP1 BH24
	  LL_GPIO_SetOutputPin(GPIO8_GPIO_Port, GPIO8_Pin); 		//reserved CS - XP1 BH24
	  LL_GPIO_SetOutputPin(GPIO9_GPIO_Port, GPIO9_Pin); 		//reserved CS - XP1 BH24
	  /**/

	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Pin = SPI4_CS_Pin;
	  	  	   LL_GPIO_Init(SPI4_CS_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = LCD_G0_Pin;
	  	  	   LL_GPIO_Init(LCD_G0_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = SPI4_NSS_Pin;
	  	  	   LL_GPIO_Init(SPI4_NSS_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = GPIO1_Pin;
	   	  	   LL_GPIO_Init(GPIO1_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = GPIO2_Pin;
	   	  	   LL_GPIO_Init(GPIO2_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = GPIO3_Pin;
	  	  	   LL_GPIO_Init(GPIO3_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = GPIO4_Pin;
	  	  	   LL_GPIO_Init(GPIO4_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = GPIO5_Pin;
	  		   LL_GPIO_Init(GPIO5_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = GPIO6_Pin;
	  	  	   LL_GPIO_Init(GPIO6_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = GPIO7_Pin;
	  	  	   LL_GPIO_Init(GPIO7_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = GPIO8_Pin;
	  	  	   LL_GPIO_Init(GPIO8_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = GPIO9_Pin;
	  	  	   LL_GPIO_Init(GPIO9_GPIO_Port, &GPIO_InitStruct);
}

void MBS_Board_ADC_Init(void)
{
	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_PLL2P);

	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADC12);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_ADC3);

	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF);

	  /**ADC1 GPIO Configuration
	  PC0   ------> ADC1_INP10
	  PA4   ------> ADC1_INP18
	  PA5   ------> ADC1_INP19
	  PA6   ------> ADC1_INP3
	  PF11   ------> ADC1_INP2
	  PF12   ------> ADC1_INP6
	  */

	  /**ADC2 GPIO Configuration
	  PF13   ------> ADC2_INP2
	  PF14   ------> ADC2_INP6
	  */

	  /**ADC3 GPIO Configuration
	  PF3   ------> ADC3_INP5
	  PF4   ------> ADC3_INP9
	  PF5   ------> ADC3_INP4
	  PF6   ------> ADC3_INP8
	  PF7   ------> ADC3_INP3
	  PF8   ------> ADC3_INP7
	  PF9   ------> ADC3_INP2
	  PF10   ------> ADC3_INP6
	  */


	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Pin = ADC12_INP18_Pin;	// IPM0
	  	  	   LL_GPIO_Init(ADC12_INP18_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC12_INP19_Pin;	// IPM0
	  	  	   LL_GPIO_Init(ADC12_INP19_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC12_INP3_Pin;		// IPM0
	  	  	   LL_GPIO_Init(ADC12_INP3_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC3_INP5_Pin; 		// IPM3
	  		   LL_GPIO_Init(ADC3_INP5_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC3_INP9_Pin; 		// IPM3
	  	  	   LL_GPIO_Init(ADC3_INP9_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC3_INP4_Pin; 		// IPM3
	  	  	   LL_GPIO_Init(ADC3_INP4_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC3_INP8_Pin; 		// IPM4
	  	  	   LL_GPIO_Init(ADC3_INP8_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC3_INP3_Pin; 		// IPM5
	  		   LL_GPIO_Init(ADC3_INP3_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC3_INP7_Pin; 		// IO
	  	  	   LL_GPIO_Init(ADC3_INP7_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC3_INP2_Pin; 		// IO
	  	  	   LL_GPIO_Init(ADC3_INP2_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC3_INP6_Pin; 		// IO
	  	  	   LL_GPIO_Init(ADC3_INP6_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC1_INP2_Pin; 		// IO
	  	  	   LL_GPIO_Init(ADC1_INP2_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC1_INP6_Pin; 		// IO
	  	  	   LL_GPIO_Init(ADC1_INP6_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC2_INP2_Pin; 		// IPM1
	  	  	   LL_GPIO_Init(ADC2_INP2_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC2_INP6_Pin; 		// IPM2
	  	  	   LL_GPIO_Init(ADC2_INP6_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = ADC123_INP10_Pin; 	// IO
	  	  	   LL_GPIO_Init(ADC123_INP10_GPIO_Port, &GPIO_InitStruct);
}

///////////////////////TIM1/////////////////
void MBS_Board_TIM1_Init(void)
{
	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	  /* Peripheral clock enable */

	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOJ);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOK);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);

	  /**TIM1 GPIO Configuration
	  PJ8     ------> TIM1_CH3N
	  PJ10     ------> TIM1_CH2N
	  PK0     ------> TIM1_CH1N
	  PA8     ------> TIM1_CH1
	  PA9     ------> TIM1_CH2
	  PA10     ------> TIM1_CH3
	  */

	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
	  GPIO_InitStruct.Pin = PWM_A0_Pin;
	  	  	   LL_GPIO_Init(PWM_A0_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_A1_Pin;
	 	  	   LL_GPIO_Init(PWM_A1_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_A2_Pin;
		  	   LL_GPIO_Init(PWM_A2_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_B0_Pin;
	 	  	   LL_GPIO_Init(PWM_B0_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_B1_Pin;
		  	   LL_GPIO_Init(PWM_B1_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_B2_Pin;
	 	  	   LL_GPIO_Init(PWM_B2_GPIO_Port, &GPIO_InitStruct);
}

///////////////////////TIM8/////////////////
void MBS_Board_TIM8_Init(void)
{
	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	  /* Peripheral clock enable */

	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOJ);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOK);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);

	  /**TIM1 GPIO Configuration
    	PJ9     ------> TIM8_CH1N
    	PJ11     ------> TIM8_CH2N
    	PK1     ------> TIM8_CH3N
    	PC6     ------> TIM8_CH1
    	PC7     ------> TIM8_CH2
    	PC8     ------> TIM8_CH3
	  */

	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
	  GPIO_InitStruct.Pin = PWM_A3_Pin;
	  	  	   LL_GPIO_Init(PWM_A3_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_A4_Pin;
	 	  	   LL_GPIO_Init(PWM_A4_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_A5_Pin;
		  	   LL_GPIO_Init(PWM_A5_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_B3_Pin;
	 	  	   LL_GPIO_Init(PWM_B3_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_B4_Pin;
		  	   LL_GPIO_Init(PWM_B4_GPIO_Port, &GPIO_InitStruct);
	  GPIO_InitStruct.Pin = PWM_B5_Pin;
	 	  	   LL_GPIO_Init(PWM_B5_GPIO_Port, &GPIO_InitStruct);
}

void MBS_Board_TIM4_Init (void)
{
	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD);


	  GPIO_InitStruct.Pin = TIM4_CH1_Pin|TIM4_CH2_Pin|TIM4_CH3_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
	  LL_GPIO_Init(TIM4_CH1_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = TIM4_ETR_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
	  LL_GPIO_Init(TIM4_ETR_GPIO_Port, &GPIO_InitStruct);
}

/////////////////////////MODBUS///////////////////////////////////////////////////
void MBS_Board_UART7_Init(void)
{

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  LL_RCC_SetUSARTClockSource(LL_RCC_USART234578_CLKSOURCE_PCLK1);

	  /* Peripheral clock enable */
	  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);

	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
	  /**UART7 GPIO Configuration
	  PE7   ------> UART7_RX
	  PE8   ------> UART7_TX
	  */
	  GPIO_InitStruct.Pin = UART7_RX_Pin|UART7_TX_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	  LL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	  /**/
	  LL_GPIO_ResetOutputPin(UART7_TX_EN_GPIO_Port, UART7_TX_EN_Pin);

	  /**/
	  GPIO_InitStruct.Pin = UART7_TX_EN_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(UART7_TX_EN_GPIO_Port, &GPIO_InitStruct);

}


void UART7_IRQHandler(void)
{
  if (UART7->ISR & (USART_ISR_NE|USART_ISR_FE|USART_ISR_PE|USART_ISR_ORE))
  {
 	   LL_USART_ClearFlag_FE(UART7);
  	   LL_USART_ClearFlag_NE(UART7);
  	   LL_USART_ClearFlag_ORE(UART7);
  }

  if (LL_USART_IsActiveFlag_RXNE(UART7) != RESET)
  {
    ModBusRTURxIsr(&Mb1);
  }

  if (LL_USART_IsActiveFlag_TC(UART7)  != RESET)
  {
	 LL_USART_ClearFlag_TC(UART7);
    ModBusRTUTxIsr(&Mb1);
  }
}

static void ModbusTxControl7(char State)
{
 if (State) { LL_GPIO_SetOutputPin(UART7_TX_EN_GPIO_Port, UART7_TX_EN_Pin); }
 else 	   { LL_GPIO_ResetOutputPin(UART7_TX_EN_GPIO_Port, UART7_TX_EN_Pin); }
}
//
//void ModbusCheckParams(TMbRTUPort *hPort,TBrdData *structure, TMbParStr *params)
//{
//  uint16_t flag = 0;
//  if (hPort->Params.Slave != params->Slave)
//  {
//    hPort->Params.Slave = params->Slave;
//    flag = 1;
//  }
//  if (hPort->Params.BaudRate != params->Speed)
//  {
//    hPort->Params.BaudRate = params->Speed;
//    hPort->Params.BrrValue = params->Speed;
//    flag = 1;
//  }
//  if (hPort->Params.Parity != params->Parity)
//  {
//    hPort->Params.Parity = params->Parity;
//    flag = 1;
//  }
//  if (hPort->Params.StopBits != params->StopBits)
//  {
//    hPort->Params.StopBits = params->StopBits;
//    flag = 1;
//  }
//  if (flag)
//  {
// 	ModBusRTUInit(hPort);
//    WriteToBoardMemory(0, ((int32_t)params - (int32_t)structure)>>1, (short *)params, sizeof(TMbParStr)>>1);
//  }
//}
//

/**/

#define CheckRange(sAddr, Cnt, Val, sMod) \
  if((Addr >= sAddr) && (lAddr < (sAddr + Cnt))) { \
    Data = (unsigned short *)(Val) + (Addr - sAddr); *Mode = sMod; }


unsigned short* MBS_sGetData(unsigned short Addr,unsigned short Count,unsigned short *Mode)
{
	unsigned short *Data = 0;
	unsigned short  lAddr = Addr + Count - 1;
	CheckRange(0x400, sizeof(struct MBS_CONTROL) / sizeof(short), &Kernel.control, 0) else
	CheckRange(0x0, Kernel.glCount * sizeof(long) / sizeof(short), Kernel.glData, 1) else
	CheckRange(0x3120, 0x800 / sizeof(short), Kernel.monAddr, 0) else
	CheckRange(0x420, 0x5A00 / sizeof(short), Kernel.cfg, 0)
	return Data;
}
//
#if FILE_OP_ENABLE
static short *GetFileRecord(short FileNum, short RecNum, short RecSize, char *AckFlag, char *Exception)
{
  #define MB_FILE_REC_SIZE  10000
  uint32_t FileAddr;

  if (RecSize > MB_RTU_WORD_MAX) { *Exception = EX_ILLEGAL_DATA_VALUE; return 0; }
  if (RecNum >= MB_FILE_REC_SIZE) { *Exception = EX_ILLEGAL_DATA_ADDRESS; return 0; }
  if ((RecNum + RecSize) > MB_FILE_REC_SIZE) { *Exception = EX_ILLEGAL_DATA_ADDRESS; return 0; }

  FileAddr = (uint32_t)FileNum * MB_FILE_REC_SIZE + RecNum;
  if ((FileAddr + RecSize) > FILE_SIZE) { *Exception = EX_ILLEGAL_DATA_ADDRESS; return 0; }

  return ((short *)FILE_ADDR + FileAddr);
}
#endif
//
//
///*//////////CAN//////////////////////
//
//void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
//{
// if (hcan->Instance == CAN1)
// {
//  g_CAN1.Resived=1;
//  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &g_CAN1.RxMessage, g_CAN1.aRxData);
// }
// else if (hcan->Instance == CAN2)
// {
//  g_CAN2.Resived=1;
//  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &g_CAN2.RxMessage, g_CAN2.aRxData);
// }
//}
//
//
//void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
//{
// if (hcan->Instance == CAN1)
// {
//  g_CAN1.Resived=1;
//  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &g_CAN1.RxMessage, g_CAN1.aRxPdoData);
// }
// else if (hcan->Instance == CAN2)
// {
//  g_CAN2.Resived=1;
//  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &g_CAN2.RxMessage, g_CAN2.aRxPdoData);
// }
//}
//
//void CAN1_RX0_IRQHandler(void)
//{
//	HAL_CAN_IRQHandler(&g_CAN1.Can_id);
//}
//
//void CAN1_RX1_IRQHandler(void)
//{
//	HAL_CAN_IRQHandler(&g_CAN1.Can_id);
//}
//
//void CAN2_RX0_IRQHandler(void)
//{
//	HAL_CAN_IRQHandler(&g_CAN2.Can_id);
//}
//
//void CAN2_RX1_IRQHandler(void)
//{
//	HAL_CAN_IRQHandler(&g_CAN2.Can_id);
//}
//
////////////////////////////////////*/
//



int16_t GetBoardMemoryStatus(void)
{
 return Eeprom.Status;
}

int16_t IsBoardMemoryReady(void)
{
 return M95X_IsReady(&Eeprom);
}

int16_t ReadFromBoardMemory(int16_t Mode, int32_t Addr, int16_t *Buf, int32_t Size)
{

 if (M95X_IsError(&Eeprom)) return 0;
 if (((Addr + Size)<<1) > (int32_t)(Eeprom.Size)) {Eeprom.Status = -3; return 0;}
 M95X_Func(&Eeprom, M95X_READ, Mode, Addr << 1, (uint8_t *)Buf, Size << 1);
 do {M95X_Update(&Eeprom);} while (!M95X_IsReady(&Eeprom));

 return 0;
}

int16_t WriteToBoardMemory(int16_t Mode, int32_t Addr, int16_t *Buf, int32_t Size)
{
 if (Eeprom.Status == -1) return 0;
 if (((Addr + Size)<<1) > (int32_t)Eeprom.Size ) {Eeprom.Status = -3; return 0;}
 M95X_Func(&Eeprom, M95X_WRITE, Mode, Addr << 1, (uint8_t *)Buf, Size << 1);
 return 0;
}

static void EepromSetCs(uint8_t State)
{
if (State) {   LL_GPIO_SetOutputPin(SPI4_CS_GPIO_Port, SPI4_CS_Pin); }
else 	   { LL_GPIO_ResetOutputPin(SPI4_CS_GPIO_Port, SPI4_CS_Pin); }
}
//
////////////////////////////////////////////////////////////////////////////
//
//
void ReadBoardData(void)
{
	  MbsProjData = &BrdData;
	  MbsProjDataSize = sizeof(BrdData)>>1;;
	  MBS_ReadProjectData();
	#if (PROJECT_MEMORY_ERASE == 1)

	  MBS_FLASH_EraseEEPROM();
	  BrdData.Version       = VERSION;
	  BrdData.DevNumber      = SlaveInfo.DeviceNumber;

	  BrdData.Mb1.Slave      = MB1_ADR;
	  BrdData.Mb1.Speed      = MB1_SPEED;
	  BrdData.Mb1.Parity     = MB1_PARITY;
	  BrdData.Mb1.StopBits   = MB1_STOPBIT;


	  BrdData.Status.all = 0;
	  BrdData.Status.bit.NewVersion = 1;
	  BrdData.Status.bit.WriteProjectData=0;
	  BrdData.Status.bit.WriteGloтеbalData=0;

	  DelayUsecs(2000);
	#else
	 if (BrdData.Version != VERSION)
	  {
	    BrdData.Version    = VERSION;

	    BrdData.Mb1.Slave      = MB_ADR;
	    BrdData.Mb1.Speed      = MB_SPEED;
	    BrdData.Mb1.Parity     = MB_PARITY;
	    BrdData.Mb1.StopBits   = MB_STOPBIT;
	    BrdData.Status.all = 0;
	    BrdData.Status.bit.NewVersion = 1;
	    BrdData.Status.bit.WriteProjectData=1;
	    BrdData.Status.bit.WriteGlobalData=1;
	    #ifdef FLASH_MBS_CFG
	      BrdData.Status.bit.WriteConfiguration=1;
	    #endif
	  }
	#endif
}
//
void DataProject_Update (TBrdData *p)
{
#ifdef FLASH_MBS_CFG
 int16_t status_flash;
 if (!IsBoardMemoryReady()) {  return;  }

 if (p->Status.bit.NewVersion)        { p->Status.bit.NewVersion=0; p->Status.bit.WriteProjectData=1;       }
 else if (p->Status.bit.WriteConfiguration)
 {
  __disable_irq();
  p->Status.bit.WriteConfiguration=0;
  status_flash = EraseBoardMemory();
  if (!status_flash)  status_flash = MBS_FLASH_WriteConfiguration();
  MbsMemStatus = status_flash;
  __enable_irq();
 }
 else if (p->Status.bit.WriteGlobalData)    { p->Status.bit.WriteGlobalData=0;    MBS_FLASH_WriteGlobalData();	}
 else if (p->Status.bit.WriteProjectData)
 {
	 p->Status.bit.WriteProjectData=0;   MBS_WriteProjectData();
 }
 else if (p->Status.bit.ResetEEPROM)     	{ p->Status.bit.ResetEEPROM=0;    	  MBS_EraseEEPROM();			}
 else if (p->Status.bit.ResetProject)
    	{
	   	p->Status.bit.NewVersion = 1;         // ��������� ������ ��.
	    p->Status.bit.WriteConfiguration=1;       // ������ ������� � ���������� ������
	    p->Status.bit.WriteProjectData=1;       // ������ ���������� �������
	    p->Status.bit.WriteGlobalData=1;       // ������ ���������� ����������
	    p->Status.bit.ResetProject=0;         // ���������� ���� "����� ������������"
	    MBS_ReadConfiguration() ;          // ��������� �� FLASH �����������
	    MbsStatus     = 0;               // ���������� ���� ������� KERNEL
	    MbsEnable    = 1;                 // �������� ������ ���������
	    MBS_Init();                 // �������� ������������� ���������� MexBiosa
	    }
 #else
 if (!IsBoardMemoryReady()) {  return;  }
 if (p->Status.bit.NewVersion)        		{ p->Status.bit.NewVersion=0;    p->Status.bit.WriteProjectData=1;  }
 else if (p->Status.bit.WriteGlobalData)   { p->Status.bit.WriteGlobalData=0;  MBS_WriteGlobalData();      	}
 else if (p->Status.bit.WriteProjectData)  { p->Status.bit.WriteProjectData=0; MBS_WriteProjectData();         }
 else if (p->Status.bit.ResetEEPROM)     	{ p->Status.bit.ResetEEPROM=0;    MBS_EraseEEPROM();        		}
 else if (p->Status.bit.ResetProject)
 	 	 {
		 p->Status.bit.NewVersion = 1;         // ��������� ������ ��.
		 p->Status.bit.WriteConfiguration=1;       // ������ ������� � ���������� ������
		 p->Status.bit.WriteProjectData=1;       // ������ ���������� �������
		 p->Status.bit.WriteGlobalData=1;       // ������ ���������� ����������
		 p->Status.bit.ResetProject=0;         // ���������� ���� "����� ������������"
		 MBS_ReadConfiguration() ;          // ��������� �� FLASH �����������
		 MbsStatus     = 0;               // ���������� ���� ������� KERNEL
		 MbsEnable    = 1;                 // �������� ������ ���������
		 MBS_Init();                 // �������� ������������� ���������� MexBiosa
	     }
#endif
}
