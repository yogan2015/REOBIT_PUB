#include "header.h"

M95X Eeprom;
TMbRTUPort Mb1;
TBrdData BrdData;

const TMbSlaveInfo SlaveInfo = {MB_ADR, DEVICE_NUMBER, VERSION, VERSION_DATE, "h745_nucleo", "STM32H745ZI" };

static void EepromSetCs(uint8_t);
static void ModbusTxControl1(char);

#if FILE_OP_ENABLE
	static short *GetFileRecord(short, short, short, char *, char *);
#endif

extern unsigned short* MBS_sGetData(unsigned short Addr,unsigned short Count,unsigned short *Mode);
extern unsigned short Bit;
extern void *Reg;
void MBS_Board_USART1_Init(void);
void MBS_Board_SPI1_Init(void);
void MBS_Board_ADC1_Init(void);

void InitBoardPeripherial(void)
{

//	Reg = GPIO_init(0, 0, 0, &Bit, 0);

//MBS_Board_GPIO_Init();		// +LED,OUT,en_PWM


//	MX_GPIO_Init();

//	MX_ADC1_Init();
//	MX_ADC2_Init();


//	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//	  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_PLL2P);
//
//
//	  /* Peripheral clock enable */
//	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADC12);
//	  /* Peripheral clock enable */
//	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_ADC3);
//
//
//
//	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
//	  /**ADC1 GPIO Configuration
//	  PA3   ------> ADC1_INP15
//	  */
//	  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
//	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
//	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//
//	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
//	  /**ADC2 GPIO Configuration
//	  PB1   ------> ADC2_INP5
//	  */
//	  GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
//	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
//	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//
//	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
//	  /**ADC3 GPIO Configuration
//	  PC0   ------> ADC3_INP10
//	  PC3_C   ------> ADC3_INP1
//	  */
//	  GPIO_InitStruct.Pin = LL_GPIO_PIN_0 | LL_GPIO_PIN_3;
//	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
//	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//	  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//
//	  LL_SYSCFG_OpenAnalogSwitch(LL_SYSCFG_ANALOG_SWITCH_PC3);
//
//
//
	MBS_Board_ADC1_Init();
MBS_Board_SPI1_Init();		// +Ethernet
MBS_Board_USART1_Init();	// +RS485_1_Transceiver (MB2)
//MX_SPI1_Init();
//LL_SPI_Enable(SPI1);
//LL_SPI_StartMasterTransfer(SPI1);
//MBS_Board_HRTIM1_Init();		// PWM config

//#ifndef SINCOS
//MBS_Board_TIM2_Init(); 		// +Encoder_Mode In3, In4
//MBS_Board_TIM3_Init(); 		// +Encoder_Mode In1, In2
//#endif

//
//MBS_Board_TIM4_Init(); 		// +PWM Brake
//
//MBS_Board_ADC_Init();		// +ADC
//
Eeprom.SpiId    = 0;
Eeprom.SpiBaud  = 0x6;
Eeprom.Type     = M95256_TYPE;
Eeprom.BusyTime = (uint16_t)(0.02*MAIN_ISR_FREQ);
Eeprom.CsFunc   = EepromSetCs;
M95X_Init(&Eeprom);
////
ReadBoardData();

//// Modbus Communication driver initialization
#ifdef MB1
Mb1.Params.UartID      = 0;
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
Mb1.Params.TrEnable    = ModbusTxControl1;
Mb1.Params.GetData     = MBS_sGetData;
#if FILE_OP_ENABLE
Mb1.Params.GetRecord   = (TMbGetRecord)GetFileRecord;;
#else
Mb1.Params.GetRecord   = 0;
#endif
ModBusRTUInit(&Mb1);
#endif
//
}
//
//void MBS_Board_GPIO_Init(void)
//{
//	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//	  /* GPIO Ports Clock Enable */
//
//
//	  /* GPIO Ports Clock Enable */
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOG);
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
//
//
//	  //Led state//
//	  LL_GPIO_SetOutputPin(Led_RED_GPIO_Port, Led_RED_Pin);
//	  LL_GPIO_SetOutputPin(Led_GREEN_GPIO_Port, Led_GREEN_Pin);
//
//	  //OUT//
//	  LL_GPIO_SetOutputPin(Fault_reset_GPIO_Port, Fault_reset_Pin);
//
//	  //EN_PWMs//
//	  LL_GPIO_ResetOutputPin(Enable_PWM2_GPIO_Port, Enable_PWM2_Pin);
//	  LL_GPIO_ResetOutputPin(Enable_PWM1_GPIO_Port, Enable_PWM1_Pin);
//
//
//
//
//	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
//	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
//	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
//
//	  //Led Init//
//	  GPIO_InitStruct.Pin = Led_RED_Pin;
//	  	  	   LL_GPIO_Init(Led_RED_GPIO_Port, &GPIO_InitStruct);
//	  GPIO_InitStruct.Pin = Led_GREEN_Pin;
//	  	  	   LL_GPIO_Init(Led_GREEN_GPIO_Port, &GPIO_InitStruct);
//
//	  //EN_PWMs_Init//
//	  GPIO_InitStruct.Pin = Enable_PWM2_Pin;
//	           LL_GPIO_Init(Enable_PWM2_GPIO_Port, &GPIO_InitStruct);
//	  GPIO_InitStruct.Pin = Enable_PWM1_Pin;
//	    	   LL_GPIO_Init(Enable_PWM1_GPIO_Port, &GPIO_InitStruct);
//
//	  //reset_fault_Init//
//	  GPIO_InitStruct.Pin = Fault_reset_Pin;
//	   	  	   LL_GPIO_Init(Fault_reset_GPIO_Port, &GPIO_InitStruct);
//
//	  // Digit_Inputs
//	  /**/
//  	  GPIO_InitStruct.Pin = Fault_1_Pin;
//  	  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
//  	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//  	  	  	   LL_GPIO_Init(Fault_1_GPIO_Port, &GPIO_InitStruct);
//
// 	  /**/
//  	  GPIO_InitStruct.Pin = Fault_2_Pin;
//  	  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
//  	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//  	  	  	  LL_GPIO_Init(Fault_2_GPIO_Port, &GPIO_InitStruct);
//
//
//	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
//	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//#ifndef SINCOS
//	GPIO_InitStruct.Pin = In1_Pin;
//	LL_GPIO_Init(In1_GPIO_Port, &GPIO_InitStruct);
//	GPIO_InitStruct.Pin = In2_Pin;
//	LL_GPIO_Init(In2_GPIO_Port, &GPIO_InitStruct);
//	GPIO_InitStruct.Pin = In3_Pin;
//	LL_GPIO_Init(In3_GPIO_Port, &GPIO_InitStruct);
//	GPIO_InitStruct.Pin = In4_Pin;
//	LL_GPIO_Init(In4_GPIO_Port, &GPIO_InitStruct);
//#endif
//
//}
//
//
void MBS_Board_ADC1_Init(void)
{

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_PLL2P);

	  /* Peripheral clock enable */
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADC12);

	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
	  /**ADC1 GPIO Configuration
	  PA3   ------> ADC1_INP15
	  */
	  GPIO_InitStruct.Pin = ADC1_INP15_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(ADC1_INP15_GPIO_Port, &GPIO_InitStruct);
}

void MBS_Board_SPI1_Init(void)
{
	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  LL_RCC_SetSPIClockSource(LL_RCC_SPI123_CLKSOURCE_PLL1Q);

	  /* Peripheral clock enable */
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
	  /**SPI1 GPIO Configuration
	  PB3 (JTDO/TRACESWO)   ------> SPI1_SCK
	  PB4 (NJTRST)   ------> SPI1_MISO
	  PB5   ------> SPI1_MOSI
	  */
	  GPIO_InitStruct.Pin = SCK_SPI1_Pin|MISO_SPI1_Pin|MOSI_SPI1_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);


	  /**/
	  LL_GPIO_SetOutputPin(CS_SPI1_GPIO_Port, CS_SPI1_Pin);

	  /**/
	  GPIO_InitStruct.Pin = CS_SPI1_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(CS_SPI1_GPIO_Port, &GPIO_InitStruct);
}
//
////
void MBS_Board_USART1_Init(void)
{

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  LL_RCC_SetUSARTClockSource(LL_RCC_USART16_CLKSOURCE_PCLK2);

	  /* Peripheral clock enable */
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
	  /**USART1 GPIO Configuration
	  PB6   ------> USART1_TX
	  PB7   ------> USART1_RX
	  */
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_6|LL_GPIO_PIN_7;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /* GPIO Ports Clock Enable */
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);

	  /**/
	  LL_GPIO_ResetOutputPin(MB1_RE_DE_GPIO_Port, MB1_RE_DE_Pin);

	  /**/
	  LL_GPIO_ResetOutputPin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);

	  /**/
	  GPIO_InitStruct.Pin = MB1_RE_DE_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(MB1_RE_DE_GPIO_Port, &GPIO_InitStruct);

	  /**/
	  GPIO_InitStruct.Pin = LED_YELLOW_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(LED_YELLOW_GPIO_Port, &GPIO_InitStruct);

	  /**/
	  GPIO_InitStruct.Pin = LED_RED_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(LED_RED_GPIO_Port, &GPIO_InitStruct);

}
//
//void MBS_Board_TIM1_Init(void)
//{
//	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//	  /* USER CODE END TIM1_Init 2 */
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
//	  /**TIM1 GPIO Configuration
//	  PA8   ------> TIM1_CH1
//	  PA11   ------> TIM1_CH1N
//	  */
//	  GPIO_InitStruct.Pin = LL_GPIO_PIN_8;
//	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
//	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//	  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
//	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//	  GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
//	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
//	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//	  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
//	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//}
//
//void MBS_Board_HRTIM1_Init (void)
//{
//  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
//  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
//
//  /* Peripheral clock enable */
//
//  /**HRTIM1 GPIO Configuration
//  PB12     ------> HRTIM1_CHC1
//  PB13     ------> HRTIM1_CHC2
//  PB14     ------> HRTIM1_CHD1
//  PB15     ------> HRTIM1_CHD2
//  PA8     ------> HRTIM1_CHA1
//  PA9     ------> HRTIM1_CHA2
//  PA10     ------> HRTIM1_CHB1
//  PA11     ------> HRTIM1_CHB2
//  **/
//
//GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
//GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
//GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//GPIO_InitStruct.Alternate = GPIO_AF13_HRTIM1;
//GPIO_InitStruct.Pin = HRTIM1_CHC1_Pin;
//	LL_GPIO_Init(HRTIM1_CHC1_GPIO_Port, &GPIO_InitStruct);
//GPIO_InitStruct.Pin = HRTIM1_CHC2_Pin;
//	LL_GPIO_Init(HRTIM1_CHC2_GPIO_Port, &GPIO_InitStruct);
//GPIO_InitStruct.Pin = HRTIM1_CHD1_Pin;
//	LL_GPIO_Init(HRTIM1_CHD1_GPIO_Port, &GPIO_InitStruct);
//GPIO_InitStruct.Pin = HRTIM1_CHD2_Pin;
//	LL_GPIO_Init(HRTIM1_CHD2_GPIO_Port, &GPIO_InitStruct);
//GPIO_InitStruct.Pin = HRTIM1_CHA1_Pin;
//	LL_GPIO_Init(HRTIM1_CHA1_GPIO_Port, &GPIO_InitStruct);
//GPIO_InitStruct.Pin = HRTIM1_CHA2_Pin;
//	LL_GPIO_Init(HRTIM1_CHA2_GPIO_Port, &GPIO_InitStruct);
//GPIO_InitStruct.Pin = HRTIM1_CHB1_Pin;
//	LL_GPIO_Init(HRTIM1_CHB1_GPIO_Port, &GPIO_InitStruct);
//GPIO_InitStruct.Pin = HRTIM1_CHB2_Pin;
//	LL_GPIO_Init(HRTIM1_CHB2_GPIO_Port, &GPIO_InitStruct);
//
//}
//
//#ifndef SINCOS
//	// IN4, IN3 - ����� ��������
// void MBS_Board_TIM2_Init (void)
// {
//   LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//   /* Peripheral clock enable */
//
//   LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
//   /**TIM2 GPIO Configuration
//   PA1   ------> TIM2_CH2
//   PA5   ------> TIM2_CH1
//   */
//
//   GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
//   GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//   GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//   GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
//
//
//
//   GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
//   GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//   GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//   GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
//   GPIO_InitStruct.Pin = In4_Pin;
//   	   LL_GPIO_Init(In4_GPIO_Port, &GPIO_InitStruct);
//   GPIO_InitStruct.Pin = In3_Pin;
//  	   LL_GPIO_Init(In3_GPIO_Port, &GPIO_InitStruct);
//}
// // IN1, IN2 - ����� ��������
// void MBS_Board_TIM3_Init (void)
// {
//   LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//   LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
//   /**TIM3 GPIO Configuration
//   PA6   ------> TIM3_CH1
//   PA7   ------> TIM3_CH2
//   */
//
//   GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
//   GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//   GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//   GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//   GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
//   GPIO_InitStruct.Pin = In1_Pin;
//	  	   LL_GPIO_Init(In1_GPIO_Port, &GPIO_InitStruct);
//   GPIO_InitStruct.Pin = In2_Pin;
//	  	   LL_GPIO_Init(In2_GPIO_Port, &GPIO_InitStruct);
// }
//#endif
//
//// BRAKE PWM
//void MBS_Board_TIM4_Init (void)
//{
//  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
//  /**TIM4 GPIO Configuration
//  PB6     ------> TIM4_CH1
//  PB7     ------> TIM4_CH2
//  */
//
//  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
//  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
//  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
//  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
//  GPIO_InitStruct.Pin = Brake_PWM2_Pin;
//  	  LL_GPIO_Init(Brake_PWM2_GPIO_Port, &GPIO_InitStruct);
//  GPIO_InitStruct.Pin = Brake_PWM1_Pin;
//  	  LL_GPIO_Init(Brake_PWM1_GPIO_Port, &GPIO_InitStruct);
//}
//
//void MBS_Board_ADC_Init(void)
//{
//
// 	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//	  /* Peripheral clock enable */
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC12);
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC345);
//
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
//	  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
//
//
//	  /**ADC1 GPIO Configuration
//	  PA0   ------> ADC1_IN1
//	  PB0   ------> ADC1_IN15
//	  PB1   ------> ADC1_IN12
//	  */
//
//	  /**ADC2 GPIO Configuration
//	  PA4   ------> ADC2_IN17
//	  PB2   ------> ADC2_IN12
//	  */
//
//	  /**ADC3 GPIO Configuration
//	  PB0   ------> ADC3_IN12
//	  */
//
//
//	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
//	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
//	  GPIO_InitStruct.Pin = Udc_Pin;
//	  	  LL_GPIO_Init(Udc_GPIO_Port, &GPIO_InitStruct);
//	  GPIO_InitStruct.Pin = Current_1_Pin;
//	  	  LL_GPIO_Init(Current_1_GPIO_Port, &GPIO_InitStruct);
//	  GPIO_InitStruct.Pin = Temp_sens_Pin;
//	  	  LL_GPIO_Init(Temp_sens_GPIO_Port, &GPIO_InitStruct);
//  	  GPIO_InitStruct.Pin = Current_2_Pin;
//	  	  LL_GPIO_Init(Current_2_GPIO_Port, &GPIO_InitStruct);
//
//#ifdef SINCOS
//	  GPIO_InitStruct.Pin = In1_Pin;
//  	  	  LL_GPIO_Init(In1_GPIO_Port, &GPIO_InitStruct);
//	  GPIO_InitStruct.Pin = In2_Pin;
//  		  LL_GPIO_Init(In2_GPIO_Port, &GPIO_InitStruct);
//  	  GPIO_InitStruct.Pin = In3_Pin;
//  	   	  LL_GPIO_Init(In3_GPIO_Port, &GPIO_InitStruct);
//  	  GPIO_InitStruct.Pin = In4_Pin;
//   		  LL_GPIO_Init(In4_GPIO_Port, &GPIO_InitStruct);
//#endif
//
//}
//
void ExecuteBoardBackgroundTask(void)
{
}
//
uint8_t num = 0xAA;
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
//
//void Fast_ExecuteBoardInterruptTask(void)
//{
//
// M95X_Update(&Eeprom);
// DataProject_Update(&BrdData);
// //CAN1_Update();
// //CAN2_Update();
//}
//
///////////////////////////MODBUS///////////////////////////////////////////////////
 void USART1_IRQHandler(void)
 {
   if (USART1->ISR & (USART_ISR_NE|USART_ISR_FE|USART_ISR_PE|USART_ISR_ORE))
   {
  	   LL_USART_ClearFlag_FE(USART1);
   	   LL_USART_ClearFlag_NE(USART1);
   	   LL_USART_ClearFlag_ORE(USART1);
   }

   if (LL_USART_IsActiveFlag_RXNE(USART1) != RESET)
   {
     ModBusRTURxIsr(&Mb1);
   }

   if (LL_USART_IsActiveFlag_TC(USART1)  != RESET)
   {
	 LL_USART_ClearFlag_TC(USART1);
     ModBusRTUTxIsr(&Mb1);
   }
 }

 static void ModbusTxControl1(char State)
 {
  if (State) { LL_GPIO_SetOutputPin(MB1_RE_DE_GPIO_Port, MB1_RE_DE_Pin); }
  else 	   { LL_GPIO_ResetOutputPin(MB1_RE_DE_GPIO_Port, MB1_RE_DE_Pin); }
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
//#if FILE_OP_ENABLE
//static short *GetFileRecord(short FileNum, short RecNum, short RecSize, char *AckFlag, char *Exception)
//{
//  #define MB_FILE_REC_SIZE  10000
//  uint32_t FileAddr;
//
//  if (RecSize > MB_RTU_WORD_MAX) { *Exception = EX_ILLEGAL_DATA_VALUE; return 0; }
//  if (RecNum >= MB_FILE_REC_SIZE) { *Exception = EX_ILLEGAL_DATA_ADDRESS; return 0; }
//  if ((RecNum + RecSize) > MB_FILE_REC_SIZE) { *Exception = EX_ILLEGAL_DATA_ADDRESS; return 0; }
//
//  FileAddr = (uint32_t)FileNum * MB_FILE_REC_SIZE + RecNum;
//  if ((FileAddr + RecSize) > FILE_SIZE) { *Exception = EX_ILLEGAL_DATA_ADDRESS; return 0; }
//
//  return ((short *)FILE_ADDR + FileAddr);
//}
//#endif
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
/////////////EEPROM/////////////////////////////////////////////////////////////
int16_t GetBoardMemoryStatus(void)
{
 return Eeprom.Status;
// return 0;
}

int16_t IsBoardMemoryReady(void)
{
 return M95X_IsReady(&Eeprom);
// return 0;
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
if (State) {   LL_GPIO_SetOutputPin(CS_SPI1_GPIO_Port, CS_SPI1_Pin); }
else 	   { LL_GPIO_ResetOutputPin(CS_SPI1_GPIO_Port, CS_SPI1_Pin); }
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

	    BrdData.Mb1.Slave      = MB1_ADR;
	    BrdData.Mb1.Speed      = MB1_SPEED;
	    BrdData.Mb1.Parity     = MB1_PARITY;
	    BrdData.Mb1.StopBits   = MB1_STOPBIT;
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
