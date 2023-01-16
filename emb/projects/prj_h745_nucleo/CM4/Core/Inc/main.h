/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h7xx_ll_adc.h"
#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_crs.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_system.h"
#include "stm32h7xx_ll_exti.h"
#include "stm32h7xx_ll_cortex.h"
#include "stm32h7xx_ll_utils.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_dma.h"
#include "stm32h7xx_ll_spi.h"
#include "stm32h7xx_ll_tim.h"
#include "stm32h7xx_ll_usart.h"
#include "stm32h7xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32h745xx.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC1_INP15_Pin LL_GPIO_PIN_3
#define ADC1_INP15_GPIO_Port GPIOA
#define CS_SPI1_Pin LL_GPIO_PIN_4
#define CS_SPI1_GPIO_Port GPIOA
#define LED_RED_Pin LL_GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOB
#define MB1_RE_DE_Pin LL_GPIO_PIN_14
#define MB1_RE_DE_GPIO_Port GPIOG
#define SCK_SPI1_Pin LL_GPIO_PIN_3
#define SCK_SPI1_GPIO_Port GPIOB
#define MISO_SPI1_Pin LL_GPIO_PIN_4
#define MISO_SPI1_GPIO_Port GPIOB
#define MOSI_SPI1_Pin LL_GPIO_PIN_5
#define MOSI_SPI1_GPIO_Port GPIOB
#define MB1_TX_Pin LL_GPIO_PIN_6
#define MB1_TX_GPIO_Port GPIOB
#define MB1_RX_Pin LL_GPIO_PIN_7
#define MB1_RX_GPIO_Port GPIOB
#define LED_YELLOW_Pin LL_GPIO_PIN_1
#define LED_YELLOW_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
