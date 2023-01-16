/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */


/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "header.h"
/* USER CODE END Includes */
#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
static void MexBiosStart (void);
static void MexBiosControl (void);
static void SysTickConfig (void);
static void CfgBoardNVIC (void);
//static void TIM4Config(void);
//static void HRTIM_Tim_Master_Config(void);
void TIM1Config (void);

//static void Interrupt_setting (void);

/* USER CODE END PM */
/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
long   g_StartMemWrite = 0;
long   g_period=0;
long   g_start_capture=0;
long   g_end_capture=0;
long   g_MbsCpuLoad=0;
long   g_FLASHLogRdyFlag;
short  g_ResetAfterWDG = 0;

long   g_period_1kHz=0;
long   g_start_capture_1kHz;
long   g_end_capture_1kHz;
long   g_MbsCpuLoad_1kHz;

long   g_period_100Hz = 0;
long   g_start_capture_100Hz = 0;
long   g_end_capture_100Hz = 0;
long   g_MbsCpuLoad_100Hz = 0;
HRTIM_TypeDef *hrtim_handler = HRTIM1;
ADC_TypeDef *adc_handler = ADC1;
MBS_Handle KernelPtr;

/* USER CODE END PV */

int main(void)
{
	/* USER CODE BEGIN Boot_Mode_Sequence_1 */
	/*HW semaphore Clock enable*/
	__HAL_RCC_HSEM_CLK_ENABLE();
	/* Activate HSEM notification for Cortex-M4*/
	HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	/*
	Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
	perform system initialization (system clock config, external memory configuration.. )
	*/
	HAL_PWREx_ClearPendingEvent();
	HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
	/* Clear HSEM flag */
	__HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

	/* USER CODE END Boot_Mode_Sequence_1 */
	/* MCU Configuration--------------------------------------------------------*/

//  int32_t timeout;
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
/* USER CODE BEGIN Boot_Mode_Sequence_2 */
  __disable_irq();

  // MexBIOS initialization
  MBS_Create();
//  Kernel.menuCfg = (void *)&menuCfg;
  KernelPtr = &Kernel;
  InitBoardPeripherial();

  // MexBIOS start-up procedure

  adc_handler = ADC1;
  TIM1Config();

  MexBiosStart();
  if (MbsError)
   {

   }
  /* Setup SysTick and enable interrupts */
  SysTickConfig();
  CfgBoardNVIC();
  LL_SYSTICK_EnableIT();
  __enable_irq();

  while (1)
  {
     MBS_Init();
     MBS_IsrExecute(0);
     MexBiosControl();
     ExecuteBoardBackgroundTask();
  }
}

void TIM1Config (void)
{
  LL_TIM_InitTypeDef base_timer;

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);

  LL_TIM_DeInit(TIM1);

    // 84000 Рєв€љС† / 84 = 10 Рєв€љС† ( 0,5 Р�?РєСЃ )
  base_timer.Prescaler = 0;
  base_timer.CounterMode = LL_TIM_COUNTERMODE_UP;
  base_timer.Autoreload = ((uint32_t)0xFFFF ) - 1;
  base_timer.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init( TIM1, &base_timer );
    // СЂР°Р·СЂРµС€Р°РµР�? РїСЂРµСЂС‹РІР°РЅРёРµ РїРѕ РѕР±РЅРѕРІР»РµРЅРёСЋ (РІ РґР°РЅРЅРѕР�? СЃР»СѓС‡Р°Рµ -
    // РїРѕ РїРµСЂРµРїРѕР»РЅРµРЅРёСЋ)

  LL_TIM_ClearFlag_CC1(TIM1);
  LL_TIM_ClearFlag_CC2(TIM1);
  LL_TIM_ClearFlag_CC3(TIM1);
  LL_TIM_ClearFlag_CC4(TIM1);
  LL_TIM_ClearFlag_UPDATE(TIM1);

  LL_TIM_DisableIT_UPDATE(TIM1);
  LL_TIM_EnableIT_CC1(TIM1);
  LL_TIM_DisableIT_CC2(TIM1);
  LL_TIM_DisableIT_CC3(TIM1);
  LL_TIM_DisableIT_CC4(TIM1);

  LL_TIM_SetCounter( TIM1, 0 );
  LL_TIM_SetAutoReload(TIM1, (240000000/1000));
  LL_TIM_OC_SetCompareCH1(TIM1, (240000000/1000));
  LL_TIM_EnableCounter(TIM1);

}

/**
  * @brief This function handles TIM1 capture compare interrupt.
  */
void TIM1_CC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */
	if (LL_TIM_IsActiveFlag_CC1(TIM1) != RESET)
	{
		g_start_capture = TIM1->CNT ;
		// 1 kHz _ Medium
//		LL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		// Execute board interrupt function

		  MBS_IsrExecute(0x5B); //  TIM8_BRK_TIM12

		  // Execute board interrupt function
		  Slow_ExecuteBoardInterruptTask();
		  g_end_capture = TIM1->CNT ;
		g_period     = TIM1->ARR ;
		if (g_start_capture >= g_end_capture)
		{
			g_MbsCpuLoad = (uint32_t)(((g_end_capture + g_period) - g_start_capture))*100/ g_period;
		} // EOF IF g_end_capture<g_start_capture
		else g_MbsCpuLoad = (uint32_t)(g_end_capture - g_start_capture)*100/g_period;
		MbsCpuLoad = g_MbsCpuLoad;
		LL_TIM_ClearFlag_CC1(TIM1);
	}
  /* USER CODE END TIM1_CC_IRQn 0 */
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */

  /* USER CODE END TIM1_CC_IRQn 1 */
}


//void TIM4_IRQHandler( void )
//{
//  if(LL_TIM_IsActiveFlag_UPDATE(TIM4))
//  {
//   LL_TIM_ClearFlag_UPDATE(TIM4);
//  }
//  if (LL_TIM_IsActiveFlag_CC1(TIM4) != RESET)
//  {
//   LL_TIM_ClearFlag_CC1(TIM4);
//  } // EOF StartAdcConversion_1
//  if (LL_TIM_IsActiveFlag_CC2(TIM4) != RESET)
//  {
//   LL_TIM_ClearFlag_CC2(TIM4);
//  } // EOF StartAdcConversion_2
//  if (LL_TIM_IsActiveFlag_CC3(TIM4) != RESET)
//  {
//   LL_TIM_ClearFlag_CC3(TIM4);
//  } // EOF StartAdcConversion_3
//  if (LL_TIM_IsActiveFlag_CC4(TIM4) != RESET)
//  {
//   LL_TIM_ClearFlag_CC4(TIM4);
//  } // EOF StartInterrupt
//  if (LL_TIM_IsActiveFlag_TRIG(TIM4) != RESET)
//  {
//	  LL_TIM_ClearFlag_TRIG(TIM4);
//  }
//}

//void HRTIM1_Master_IRQHandler(void)
//{
//	if(LL_HRTIM_IsActiveFlag_UPDATE(HRTIM1, LL_HRTIM_TIMER_MASTER))
//	{
//		LL_HRTIM_ClearFlag_UPDATE(HRTIM1, LL_HRTIM_TIMER_MASTER);
//	}
//	if(LL_HRTIM_IsActiveFlag_REP(HRTIM1, LL_HRTIM_TIMER_MASTER))
//	{
//		LL_HRTIM_ClearFlag_REP(HRTIM1, LL_HRTIM_TIMER_MASTER);
//	}
//	if(LL_HRTIM_IsActiveFlag_CMP1(HRTIM1, LL_HRTIM_TIMER_MASTER))
//	{
//		LL_HRTIM_ClearFlag_CMP1(HRTIM1, LL_HRTIM_TIMER_MASTER);
//	}
//	if(LL_HRTIM_IsActiveFlag_CMP2(HRTIM1, LL_HRTIM_TIMER_MASTER))
//	{
//		g_start_capture = HRTIM1->sMasterRegs.MCNTR;//SysTick->VAL;
//
//		// 5 | 10 | 20 kHz_High
//		MBS_IsrExecute(0x5B); // TIM4_IRQHandler
//
//		// Monitor
//		MBS_MonExecute();
//
//		Fast_ExecuteBoardInterruptTask();
//
//		g_end_capture = HRTIM1->sMasterRegs.MCNTR;//SysTick->VAL;
//
//		if (g_start_capture > g_end_capture)
//		{
//			g_MbsCpuLoad = (uint32_t)(((g_end_capture + g_period) - g_start_capture))*100/ g_period;
//		} // EOF IF g_end_capture<g_start_capture
//		else g_MbsCpuLoad = (uint32_t)(g_end_capture - g_start_capture)*100/g_period;
//		MbsCpuLoad = g_MbsCpuLoad;
//		int32_t i=0;
//		i=(5 - (HRTIM1->sMasterRegs.MCR & 0x7));
//		if (i < 0 )
//		{
//			g_period  =  TIM1->ARR >> (i + 2);
//		}
//		else
//		{
//			g_period  =  TIM1->ARR << (i - 2);
//		}
//
//		LL_HRTIM_ClearFlag_CMP2(HRTIM1, LL_HRTIM_TIMER_MASTER);
//	}
//	if(LL_HRTIM_IsActiveFlag_CMP3(HRTIM1, LL_HRTIM_TIMER_MASTER))
//	{
//		LL_HRTIM_ClearFlag_CMP3(HRTIM1, LL_HRTIM_TIMER_MASTER);
//	}
//	if(LL_HRTIM_IsActiveFlag_CMP4(HRTIM1, LL_HRTIM_TIMER_MASTER))
//	{
//		LL_HRTIM_ClearFlag_CMP4(HRTIM1, LL_HRTIM_TIMER_MASTER);
//	}
//}

//void TIM1_CC_IRQHandler( void )
//{
//  if (LL_TIM_IsActiveFlag_CC1(TIM1) != RESET)
//  {
//   LL_TIM_ClearFlag_CC1(TIM1);
//  } // EOF StartAdcConversion_1
//  if (LL_TIM_IsActiveFlag_CC2(TIM1) != RESET)
//  {
//   LL_TIM_ClearFlag_CC2(TIM1);
//  } // EOF StartAdcConversion_2
//  if (LL_TIM_IsActiveFlag_CC3(TIM1) != RESET)
//  {
//   LL_TIM_ClearFlag_CC3(TIM1);
//  } // EOF StartAdcConversion_3
//  if (LL_TIM_IsActiveFlag_CC4(TIM1) != RESET)
//  {
//   LL_TIM_ClearFlag_CC4(TIM1);
//  }
//}

//void TIM3_IRQHandler (void)
//{
//  if (LL_TIM_IsActiveFlag_CC1(TIM3) != RESET)
//  {
//	  g_start_capture_1kHz = TIM3->CNT ;
//		// 1 kHz _ Medium
//	  MBS_IsrExecute(0x1D); //  TIM8_BRK_TIM12
//
//	  // Execute board interrupt function
//	  Slow_ExecuteBoardInterruptTask();
//
//	  g_end_capture_1kHz   = TIM3->CNT ;
//	  g_period_1kHz     = TIM3->ARR ;
//	  if (g_start_capture_1kHz >= g_end_capture_1kHz)
//	  {
//		 g_MbsCpuLoad_1kHz = (uint32_t)(((g_end_capture_1kHz + g_period_1kHz) - g_start_capture_1kHz))*100/ g_period_1kHz;
//	  } // EOF IF g_end_capture<g_start_capture
//	  else g_MbsCpuLoad_1kHz = (uint32_t)(g_end_capture_1kHz - g_start_capture_1kHz)*100/g_period_1kHz;
//	  LL_TIM_ClearFlag_CC1(TIM3);
//  }
//}


//void TIM8_UP_IRQHandler ( void )
//{
//  if (LL_TIM_IsActiveFlag_UPDATE(TIM8) != RESET)
//  {
//    // 100 Hz _ Low
//	  g_start_capture_100Hz = TIM8->CNT ;
//	  MBS_IsrExecute(0x2C); //   TIM1_BRK_TIM9
//	  g_period_100Hz     = TIM8->ARR ;
//	  g_end_capture_100Hz   = TIM8->CNT ;
//	  // Execute board interrupt function
//	  if (g_start_capture_100Hz >= g_end_capture_100Hz)
//	  {
//		g_MbsCpuLoad_100Hz = (uint32_t)(((g_end_capture_100Hz + g_period_100Hz) - g_start_capture_100Hz))*100/ g_period_100Hz;
//	  } // EOF IF g_end_capture<g_start_capture
//	  else g_MbsCpuLoad_100Hz = (uint32_t)(g_end_capture_100Hz - g_start_capture_100Hz)*100/g_period_100Hz;
//
//	  LL_TIM_ClearFlag_UPDATE(TIM8);
//
//  }
//}



void CfgBoardNVIC(void){
/*___________________________ NVIC Config Table ______________________________________________________________
 *
 *    Priority        Irq
 *       0        SysTick  (1ms HALL Timer)
 *       1        XTI0
 *       2              TIM2, SPI3,  (SSI/ENC/������ ����������   Counter for SSI Driver)
 *       3              CAN1; CAN2
 *       4              USART2_IRQn, USART1_IRQn, USART3_IRQn/USART6_IRQn (Modbus)
 *       5        TIM5
 *       6        TIM3
 *       7        TIM12
 *
 *
*/
/* Configure the NVIC Preemption Priority Bits */

NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);

/* Configure the SysTick handler priority */
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(SysTick_IRQn);

/* Configure the USART1 handler priority */
    NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 0));
    NVIC_EnableIRQ(USART1_IRQn);

/*Configure the TIM5_IRQn interrupt Init */
	NVIC_SetPriority(HRTIM1_Master_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1, 0));
	NVIC_EnableIRQ(HRTIM1_Master_IRQn);;

/*Configure the TIM8_BRK_TIM12 handler priority */
    NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),2, 0));
    NVIC_EnableIRQ(TIM3_IRQn);


    NVIC_SetPriority(TIM1_CC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
    NVIC_EnableIRQ(TIM1_CC_IRQn);



/*Configure the TIM8_BRK_TIM12 handler priority */
//    NVIC_SetPriority(TIM8_UP_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),3, 0));
//    NVIC_EnableIRQ(TIM8_UP_IRQn);
//
//    /*Configure the TIM8_BRK_TIM12 handler priority */
//    NVIC_SetPriority(ADC1_2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
//    NVIC_EnableIRQ(ADC1_2_IRQn);



}

static void SysTickConfig(void)
{
  g_period=480000000/MAIN_ISR_FREQ;
}


void MexBiosStart(void)
{
#ifdef FLASH_MBS_CFG
 if (BrdData.Status.bit.NewVersion) { MBS_ReadConfiguration();}
 else
 {
  MbsMemStatus = MBS_FLASH_ReadConfiguration();
  if (MbsMemStatus < 0) return;
 }
// start MexBIOS
 MbsAppVersion = VERSION;
 MbsEnable = 1;

 MBS_Init();

 if (MbsError != 0) return;
 if (!BrdData.Status.bit.NewVersion) { MbsMemStatus =  MBS_FLASH_ReadGlobalData();}
#endif

#ifndef FLASH_MBS_CFG
   MbsMemStatus = MBS_ReadConfiguration();
   if (MbsMemStatus < 0) return;

     // start MexBIOS
   MbsAppVersion = VERSION;
   MbsEnable = 1;

   MBS_Init();
  if (MbsError != 0) return;
  MbsMemStatus = MBS_ReadGlobalData();
#endif
}

void MexBiosControl(void)
{
#ifdef FLASH_MBS_CFG
  uint16_t mbs_mem_cmd;
  int16_t status_flash;
  MbsMemStatus = GetBoardMemoryStatus();
  if (MbsMemCmd & 0x0001)
  {
  __disable_irq();
    MbsMemStatus = 1;
    mbs_mem_cmd = MbsMemCmd;
    MbsMemCmd &= ~0x0001;
    // Write_to_FLASH
    status_flash = EraseBoardMemory();
    if ((mbs_mem_cmd & 0x1) && !status_flash)  status_flash = MBS_FLASH_WriteConfiguration();
    MbsMemStatus = status_flash;
    mbs_mem_cmd = 0;
  __enable_irq();
  }
  // Write_to_EEPROM
  if (IsBoardMemoryReady())
  {
    if (MbsMemCmd & 0x0002) { MBS_FLASH_WriteGlobalData();    MbsMemCmd &= ~0x0002; } else
    if (MbsMemCmd & 0x0004) { MBS_FLASH_WriteGlobalVar();     MbsMemCmd &= ~0x0004; } else
    if (MbsMemCmd & 0x0008) { MBS_WriteProjectVar();      MbsMemCmd &= ~0x0008; }
  }

#else
//  MbsMemStatus = GetBoardMemoryStatus();
//  if (IsBoardMemoryReady())
//  {
//    if (MbsMemCmd & 0x0001) { MBS_WriteConfiguration(); MbsMemCmd &= ~0x0001; } else
//    if (MbsMemCmd & 0x0002) { MBS_WriteGlobalData();    MbsMemCmd &= ~0x0002; } else
//    if (MbsMemCmd & 0x0004) { MBS_WriteGlobalVar();     MbsMemCmd &= ~0x0004; } else
//    if (MbsMemCmd & 0x0008) { MBS_WriteProjectVar();    MbsMemCmd &= ~0x0008; }
//  }
#endif
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
