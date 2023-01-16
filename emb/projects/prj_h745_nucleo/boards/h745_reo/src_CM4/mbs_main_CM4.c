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
static void Interrupt_setting (void);

extern void MBS_PWM_Init(PWM_STR *v);


/* USER CODE END PM */
/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
long   g_period=0;
long   g_start_capture=0;
long   g_end_capture=0;
long   g_MbsCpuLoad=0;

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
  InitBoardPeripherial();

  // MexBIOS start-up procedure

  adc_handler = ADC1;

  MexBiosStart();
  if (MbsError)
   {
	    Interrupt_setting();
   }
  /* Setup SysTick and enable interrupts */
  SysTickConfig();
  CfgBoardNVIC();
  LL_SYSTICK_EnableIT();

  LL_TIM_ClearFlag_CC4(TIM5);
  LL_TIM_ClearFlag_CC1(TIM3);
  LL_TIM_ClearFlag_CC1(TIM12);

  __enable_irq();

  while (1)
  {
     MBS_Init();
     MBS_IsrExecute(0);
     MexBiosControl();
     ExecuteBoardBackgroundTask();
  }
}


void TIM5_IRQHandler( void )
{
 if (LL_TIM_IsActiveFlag_CC1(TIM5) != RESET)
  {
   LL_TIM_ClearFlag_CC1(TIM5);
  } // EOF StartAdcConversion_1
  if (LL_TIM_IsActiveFlag_CC2(TIM5) != RESET)
  {
   LL_TIM_ClearFlag_CC2(TIM5);
  } // EOF StartAdcConversion_2
  if (LL_TIM_IsActiveFlag_CC3(TIM5) != RESET)
  {
	LL_TIM_ClearFlag_CC3(TIM5);
  } // EOF StartAdcConversion_3
  if (LL_TIM_IsActiveFlag_CC4(TIM5) != RESET)
  {
	g_start_capture = TIM3->CNT;//SysTick->VAL;
	// 5 | 10 | 20 kHz_High
	MBS_IsrExecute(0x32); // TIM5_IRQHandler
	// Monitor
	MBS_MonExecute();
	Fast_ExecuteBoardInterruptTask();
	g_end_capture=TIM3->CNT;//SysTick->VAL;
	if (g_start_capture > g_end_capture)
	{
		g_MbsCpuLoad = (uint32_t)(((g_end_capture + g_period_1kHz) - g_start_capture))*100/ g_period;
	} // EOF IF g_end_capture<g_start_capture
	else g_MbsCpuLoad = (uint32_t)(g_end_capture - g_start_capture)*100/g_period;
	LL_TIM_ClearFlag_CC4(TIM5);

	MbsCpuLoad = g_MbsCpuLoad;
	g_period  =  TIM5->ARR >> 1;
   } // EOF StartInterrupt
}

void TIM3_IRQHandler (void)
{
  if (LL_TIM_IsActiveFlag_CC1(TIM3) != RESET){
  g_start_capture_1kHz = TIM3->CNT ;
    // 1 kHz _ Medium
  MBS_IsrExecute(0x1D); //  TIM3

  // Execute board interrupt function
  Slow_ExecuteBoardInterruptTask();

  g_period_1kHz     = TIM3->ARR ;
  g_end_capture_1kHz   = TIM3->CNT ;
  if (g_start_capture_1kHz >= g_end_capture_1kHz)
  {
     g_MbsCpuLoad_1kHz = (uint32_t)(((g_end_capture_1kHz + g_period_1kHz) - g_start_capture_1kHz))*100/ g_period_1kHz;
  } // EOF IF g_end_capture<g_start_capture
  else g_MbsCpuLoad_1kHz = (uint32_t)(g_end_capture_1kHz - g_start_capture_1kHz)*100/g_period_1kHz;
  LL_TIM_ClearFlag_CC1(TIM3);
  }
}


void TIM8_BRK_TIM12_IRQHandler ( void )
{
  if (LL_TIM_IsActiveFlag_CC1(TIM12) != RESET){
    // 100 Hz _ Low
  LL_TIM_ClearFlag_CC1(TIM12);
  g_start_capture_100Hz = TIM12->CNT ;
  MBS_IsrExecute(0x2B); //   TIM1_BRK_TIM9
  g_period_100Hz     = TIM12->ARR ;
  g_end_capture_100Hz   = TIM12->CNT ;
  // Execute board interrupt function
  if (g_start_capture_100Hz >= g_end_capture_100Hz)
  {
    g_MbsCpuLoad_100Hz = (uint32_t)(((g_end_capture_100Hz + g_period_100Hz) - g_start_capture_100Hz))*100/ g_period_100Hz;
  } // EOF IF g_end_capture<g_start_capture
  else g_MbsCpuLoad_100Hz = (uint32_t)(g_end_capture_100Hz - g_start_capture_100Hz)*100/g_period_100Hz;
  }
}



void Interrupt_setting (void)
{
  PWM_STR MASTER_TIM1 = {0};
  PWM_STR FAST_TIM5 = {0};
  PWM_STR MEDIUM_TIM3 = {0};
  PWM_STR SLOW_TIM12 = {0};

  MASTER_TIM1.Id            = 0;
  MASTER_TIM1.CountMode        = 0;
  MASTER_TIM1.Frequency        = MAIN_ISR_FREQ;
  MASTER_TIM1.CountCMP        = 15;
  MASTER_TIM1.Polarity        = 0;
  MASTER_TIM1.OutInverted      = 1;
  MASTER_TIM1.DeadTime        = _IQ13(0);
  MASTER_TIM1.Pulse          = _IQ24(0.125);
  MASTER_TIM1.MasterTimer      = 0;
  MASTER_TIM1.MasterSlaveMode    = 1;
  MASTER_TIM1.InputTrigger      = 0;
  MASTER_TIM1.IntEnable        = 30;
  MASTER_TIM1.BreakPolarity      = 0;

  FAST_TIM5.Id            = 4;
  FAST_TIM5.CountMode        = 0;
  FAST_TIM5.Frequency        = MAIN_ISR_FREQ;
  FAST_TIM5.CountCMP        = 15;
  FAST_TIM5.Polarity        = 0;
  FAST_TIM5.OutInverted      = 1;
  FAST_TIM5.DeadTime        = _IQ13(0);
  FAST_TIM5.Pulse          = _IQ24(0.125);
  FAST_TIM5.MasterTimer      = 0;
  FAST_TIM5.MasterSlaveMode    = 1;
  FAST_TIM5.InputTrigger      = 0;
  FAST_TIM5.IntEnable        = 30;
  FAST_TIM5.BreakPolarity      = 0;

  MEDIUM_TIM3.Id            = 2;
  MEDIUM_TIM3.CountMode      = 0;
  MEDIUM_TIM3.Frequency      = 1000;
  MEDIUM_TIM3.CountCMP      = 1;
  MEDIUM_TIM3.Polarity      = 0;
  MEDIUM_TIM3.OutInverted      = 1;
  MEDIUM_TIM3.DeadTime      = _IQ13(0);
  MEDIUM_TIM3.Pulse        = _IQ24(0.125);
  MEDIUM_TIM3.MasterTimer      = 0;
  MEDIUM_TIM3.MasterSlaveMode    = 2;
  MEDIUM_TIM3.InputTrigger    = 0;
  MEDIUM_TIM3.IntEnable      = 2;
  MEDIUM_TIM3.BreakPolarity    = 0;

  SLOW_TIM12.Id            = 8;
  SLOW_TIM12.CountMode      = 0;
  SLOW_TIM12.Frequency      = 200;
  SLOW_TIM12.CountCMP        = 1;
  SLOW_TIM12.Polarity        = 0;
  SLOW_TIM12.OutInverted      = 1;
  SLOW_TIM12.DeadTime        = _IQ13(0);
  SLOW_TIM12.Pulse        = _IQ24(0.125);
  SLOW_TIM12.MasterTimer      = 4;
  SLOW_TIM12.MasterSlaveMode    = 2;
  SLOW_TIM12.InputTrigger      = 1;
  SLOW_TIM12.IntEnable      = 2;
  SLOW_TIM12.BreakPolarity    = 0;

  MBS_PWM_Init(&SLOW_TIM12);
  MBS_PWM_Init(&MEDIUM_TIM3);
  MBS_PWM_Init(&FAST_TIM5);
  MBS_PWM_Init(&MASTER_TIM1);
}



void CfgBoardNVIC(void){
/*___________________________ NVIC Config Table ______________________________________________________________
 *
 *    Priority        Irq
 *       0        SysTick  (1ms HALL Timer)
 *       1        ----
 *       2        ----
 *       3        ----
 *       4        USART7_IRQn (Modbus)
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

/* Configure the UART7 handler priority */
	NVIC_SetPriority(UART7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),4, 0));
	NVIC_EnableIRQ(UART7_IRQn);

/*Configure the TIM5_IRQn interrupt Init */
	NVIC_SetPriority(TIM5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5, 0));
	NVIC_EnableIRQ(TIM5_IRQn);

/*Configure the TIM3 handler priority */
	NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),6, 0));
	NVIC_EnableIRQ(TIM3_IRQn);

/*Configure the TIM12 handler priority */
	NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),7, 0));
	NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);

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
////   MbsMemStatus = MBS_ReadConfiguration();
//   if (MbsMemStatus < 0) return;
//
//     // start MexBIOS
//   MbsAppVersion = VERSION;
//   MbsEnable = 1;
//
//   MBS_Init();
//  if (MbsError != 0) return;
//  MbsMemStatus = MBS_ReadGlobalData();
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
