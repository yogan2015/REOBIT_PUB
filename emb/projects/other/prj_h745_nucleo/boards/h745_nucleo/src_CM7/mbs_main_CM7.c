/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "kernel.h"
#include "modbus_rtu.h"
// by ADK: YAHZ it has to be in another place
//#include "board_h745_nucleo.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define MB_ADR			1
#define DEVICE_NUMBER   1
#define VERSION         006
#define VERSION_DATE	((21<<9)|(3<<5)|2) // YY:7 / MM:4 / DD::5

#define MAIN_ISR_FREQ_1kHz  1000
#define MAIN_ISR_FREQ   	5000
#define MEMORY_SIZE  		0x4000

TMbRTUPort Mb7;
void MBS_Board_UART7_Init(void);
extern unsigned short* MBS_sGetData(unsigned short Addr,unsigned short Count,unsigned short *Mode);
static void ModbusTxControl7(char);
const TMbSlaveInfo SlaveInfo = {MB_ADR, DEVICE_NUMBER, VERSION, VERSION_DATE, "h745_nucleo", "STM32H745ZI" };
void TIM2Config(void);
static void CfgBoardNVIC (void);
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const MBS_Handle __attribute__((section (".externData"))) KernelPtr;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
  int32_t timeout;
/* USER CODE END Boot_Mode_Sequence_0 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /* Wait until CPU2 boots and enters in stop mode or timeout*/
  timeout = 0xFFFF;
  while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
  if ( timeout < 0 )
  {
  Error_Handler();
  }
/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  __disable_irq();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  PeriphCommonClock_Config();
/* USER CODE BEGIN Boot_Mode_Sequence_2 */
/* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
HSEM notification */
/*HW semaphore Clock enable*/
__HAL_RCC_HSEM_CLK_ENABLE();
/*Take HSEM */
HAL_HSEM_FastTake(HSEM_ID_0);
/*Release HSEM in order to notify the CPU2(CM4)*/
HAL_HSEM_Release(HSEM_ID_0,0);
/* wait until CPU2 wakes up from stop mode */
timeout = 0xFFFF;
while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
if ( timeout < 0 )
{
Error_Handler();
}
/* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */


MBS_Board_UART7_Init();

	Mb7.Params.UartID      = 6;
	Mb7.Params.Mode        = MB_MODE;
	Mb7.Params.Slave       = MB1_ADR;
	Mb7.Params.BaudRate    = MB1_SPEED;
	Mb7.Params.BrrValue    = MB1_SPEED;
	Mb7.Params.Parity      = MB1_PARITY;
	Mb7.Params.StopBits    = MB1_STOPBIT;
	Mb7.Params.UserMode    = 0;
	Mb7.Params.RetryCount  = 0;
	Mb7.Params.Scale       = (MAIN_ISR_FREQ)/1000;
	Mb7.Params.RxDelay     = 5;
	Mb7.Params.TxDelay     = 2;
	#if MB_MODE == MB_RTU_SLAVE
	Mb7.Params.ConnTimeout = (uint16_t)(3.0*MAIN_ISR_FREQ);
	#elif MB_MODE == MB_RTU_MASTER
	Mb7.Params.ConnTimeout = (uint16_t)(0.2*MAIN_ISR_FREQ);
	#endif
	Mb7.Params.AckTimeout  = 1*MAIN_ISR_FREQ;
	Mb7.Params.SlaveInfo   = (TMbSlaveInfo *)&SlaveInfo;
	Mb7.Params.TrEnable    = ModbusTxControl7;
	Mb7.Params.GetData     = MBS_sGetData;
	#if FILE_OP_ENABLE
	Mb7.Params.GetRecord   = (TMbGetRecord)GetFileRecord;;
	#else
	Mb7.Params.GetRecord   = 0;
	#endif
	ModBusRTUInit(&Mb7);

	TIM2Config();
	CfgBoardNVIC();
	  LL_SYSTICK_EnableIT();
	__enable_irq();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

void CfgBoardNVIC(void)
{

NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);

/* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(SysTick_IRQn);


	/* Configure the USART7 handler priority */
		NVIC_SetPriority(UART7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 0));
		NVIC_EnableIRQ(UART7_IRQn);

	    NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	    NVIC_EnableIRQ(TIM2_IRQn);


}

void TIM2Config(void)
{
  LL_TIM_InitTypeDef base_timer;

  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

  LL_TIM_DeInit(TIM2);

    // 84000 Рєв€љС† / 84 = 10 Рєв€љС† ( 0,5 Р�?РєСЃ )
  base_timer.Prescaler = 0;
  base_timer.CounterMode = LL_TIM_COUNTERMODE_UP;
  base_timer.Autoreload = ((uint32_t)0xFFFF ) - 1;
  base_timer.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init( TIM2, &base_timer );
    // СЂР°Р·СЂРµС€Р°РµР�? РїСЂРµСЂС‹РІР°РЅРёРµ РїРѕ РѕР±РЅРѕРІР»РµРЅРёСЋ (РІ РґР°РЅРЅРѕР�? СЃР»СѓС‡Р°Рµ -
    // РїРѕ РїРµСЂРµРїРѕР»РЅРµРЅРёСЋ)

  LL_TIM_ClearFlag_CC1(TIM2);
  LL_TIM_ClearFlag_CC2(TIM2);
  LL_TIM_ClearFlag_CC3(TIM2);
  LL_TIM_ClearFlag_CC4(TIM2);
  LL_TIM_ClearFlag_UPDATE(TIM2);

  LL_TIM_DisableIT_UPDATE(TIM2);
  LL_TIM_EnableIT_CC1(TIM2);
  LL_TIM_DisableIT_CC2(TIM2);
  LL_TIM_DisableIT_CC3(TIM2);
  LL_TIM_DisableIT_CC4(TIM2);

  LL_TIM_SetCounter( TIM2, 0 );
  LL_TIM_SetAutoReload(TIM2, (240000000/1000));
  LL_TIM_OC_SetCompareCH1(TIM2, (240000000/1000));
  LL_TIM_EnableCounter(TIM2);

}

/**
  * @brief This function handles TIM1 capture compare interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */
	if (LL_TIM_IsActiveFlag_CC1(TIM2) != RESET)
	{
		ModBusRTUTimings(&Mb7);
		ModBusRTUInvoke(&Mb7);
		LL_TIM_ClearFlag_CC1(TIM2);
	}
  /* USER CODE END TIM1_CC_IRQn 0 */
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

  /* USER CODE END TIM1_CC_IRQn 1 */
}

/* USER CODE BEGIN 4 */

#define CheckRange(sAddr, Cnt, Val, sMod) \
  if((Addr >= sAddr) && (lAddr < (sAddr + Cnt))) { \
    Data = (unsigned short *)(Val) + (Addr - sAddr); *Mode = sMod; }


unsigned short* MBS_sGetData(unsigned short Addr,unsigned short Count,unsigned short *Mode)
{
	unsigned short *Data = 0;
	unsigned short  lAddr = Addr + Count - 1;
	CheckRange(0x400, sizeof(struct MBS_CONTROL) / sizeof(short), &KernelPtr->control, 0) else
	CheckRange(0x0, KernelPtr->glCount * sizeof(long) / sizeof(short), KernelPtr->glData, 1) else
	CheckRange(0x3120, 0x800 / sizeof(short), KernelPtr->monAddr, 0) else
	CheckRange(0x420, 0x5A00 / sizeof(short), KernelPtr->cfg, 0)
	return Data;
}

void MBS_Board_UART7_Init(void)
{

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  LL_RCC_SetUSARTClockSource(LL_RCC_USART234578_CLKSOURCE_PCLK1);

	  /* Peripheral clock enable */
	  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);

	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF);
	  /**UART7 GPIO Configuration
	  PF6   ------> UART7_RX
	  PF7   ------> UART7_TX
	  */
	  GPIO_InitStruct.Pin = MB7_RX_Pin|MB7_TX_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	  LL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	  /* GPIO Ports Clock Enable */
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
	  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);

	  /**/
	  LL_GPIO_ResetOutputPin(MB7_RE_DE_GPIO_Port, MB7_RE_DE_Pin);

	  /**/
	  GPIO_InitStruct.Pin = MB7_RE_DE_Pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(MB7_RE_DE_GPIO_Port, &GPIO_InitStruct);

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
//	 LL_USART_ClearFlag_RXNE(USART2);
    ModBusRTURxIsr(&Mb7);
  }

  if (LL_USART_IsActiveFlag_TC(UART7)  != RESET)
  {
	 LL_USART_ClearFlag_TC(UART7);
    ModBusRTUTxIsr(&Mb7);
  }
}

static void ModbusTxControl7(char State)
{
 if (State) { LL_GPIO_SetOutputPin(MB7_RE_DE_GPIO_Port, MB7_RE_DE_Pin); }
 else 	   { LL_GPIO_ResetOutputPin(MB7_RE_DE_GPIO_Port, MB7_RE_DE_Pin); }
}
/* USER CODE END 4 */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

