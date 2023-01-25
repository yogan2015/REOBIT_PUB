/*!
    Copyright 2018 	АО "НИИЭТ" и ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      startup.h
 \brief     Заголовочный файл с векторами прерываний
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 04/09/2018

 */


#ifndef ASM_STARTUP_H_
#define ASM_STARTUP_H_

#include "K1921VK028.h"
#include "core_cm4.h"

typedef unsigned char Uint8;
typedef unsigned short int Uint16;
typedef unsigned int Uint32;

// Символы из линкера
extern int _estack;
int main (void);

// Дефолтный обработчик
void defaultISRhandler (void) {
	while(1){};
};

// Функции прерываний, объявленные как "weak"
//void _estack(void) __attribute__ ((weak, alias("defaultISRhandler")));
void Reset_Handler(void) __attribute__((naked));
void NMI_Handler(void) __attribute__ ((weak, alias("defaultISRhandler")));
void HardFault_Handler(void) __attribute__ ((weak, alias("defaultISRhandler")));
void MemManage_Handler(void) __attribute__ ((weak, alias("defaultISRhandler")));
void BusFault_Handler(void) __attribute__ ((weak, alias("defaultISRhandler")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("defaultISRhandler")));
//void 0(void) __attribute__ ((weak, alias("defaultISRhandler")));
//void 0(void) __attribute__ ((weak, alias("defaultISRhandler")));
//void 0(void) __attribute__ ((weak, alias("defaultISRhandler")));
//void 0(void) __attribute__ ((weak, alias("defaultISRhandler")));
void SVC_Handler(void) __attribute__ ((weak, alias("defaultISRhandler")));
void DebugMon_Handler(void) __attribute__ ((weak, alias("defaultISRhandler")));
//void 0(void) __attribute__ ((weak, alias("defaultISRhandler")));
void PendSV_Handler(void) __attribute__ ((weak, alias("defaultISRhandler")));
void SysTick_Handler(void) __attribute__ ((weak, alias("defaultISRhandler")));
void WDT_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void RCU_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void RTC_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void MFLASH_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void BFLASH_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOA_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOB_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOC_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOE_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOF_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOG_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOH_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOJ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOK_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOL_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void GPIOM_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH4_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH5_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH6_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH7_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH8_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH9_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH10_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH11_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH12_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH13_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH14_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH15_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH16_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH17_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH18_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH19_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH20_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH21_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH22_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH23_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH24_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH25_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH26_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH27_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH28_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH29_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH30_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void DMA_CH31_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TMR0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TMR1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TMR2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TMR3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ETMR0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ETMR1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ETMR2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ETMR3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART0_TD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART0_MS_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART0_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART0_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART0_RT_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART0_E_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART1_TD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART1_MS_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART1_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART1_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART1_RT_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART1_E_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART2_TD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART2_MS_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART2_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART2_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART2_RT_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART2_E_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART3_TD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART3_MS_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART3_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART3_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART3_RT_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART3_E_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void UART3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART0_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART0_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART0_RO_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART0_TO_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART1_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART1_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART1_RO_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART1_TO_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TUART1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI0_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI0_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI0_RO_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI0_RT_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI1_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI1_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI1_RO_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI1_RT_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI2_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI2_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI2_RO_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI2_RT_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI3_RX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI3_TX_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI3_RO_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPI3_RT_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void I2C0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void I2C1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPWR0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SPWR1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void MILSTD0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void MILSTD1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ECAP0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ECAP1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ECAP2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ECAP3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ECAP4_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ECAP5_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM0_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM0_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM1_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM1_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM2_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM2_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM3_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM3_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM4_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM4_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM4_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM5_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM5_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM5_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM6_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM6_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM6_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM7_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM7_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM7_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM8_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM8_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM8_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM9_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM9_HD_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void PWM9_TZ_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void QEP0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void QEP1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void QEP2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void QEP3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ADC_SEQ0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ADC_SEQ1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ADC_SEQ2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ADC_SEQ3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ADC_SEQ4_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ADC_SEQ5_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ADC_SEQ6_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ADC_SEQ7_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ADC_DC_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void ETH_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN2_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN3_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN4_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN5_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN6_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN7_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN8_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN9_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN10_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN11_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN12_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN13_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN14_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void CAN15_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void FPU_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void TMU_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void LAU_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void SDFM_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void OWI0_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));
void OWI1_IRQHandler (void) __attribute__ ((weak, alias("defaultISRhandler")));


struct SisrVectors;
typedef volatile struct SisrVectors TisrVectors;

struct SisrVectors {
	void (*_estack)(void);
	void (*Reset_Handler)(void);
	void (*NMI_Handler)(void);
	void (*HardFault_Handler)(void);
	void (*MemManage_Handler)(void);
	void (*BusFault_Handler)(void);
	void (*UsageFault_Handler)(void);
	void (*reserved1)(void);
	void (*reserved2)(void);
	void (*reserved3)(void);
	void (*reserved4)(void);
	void (*SVC_Handler)(void);
	void (*DebugMon_Handler)(void);
	void (*reserved5)(void);
	void (*PendSV_Handler)(void);
	void (*SysTick_Handler)(void);
	void (*WDT_IRQHandler)(void);
	void (*RCU_IRQHandler)(void);
	void (*RTC_IRQHandler)(void);
	void (*MFLASH_IRQHandler)(void);
	void (*BFLASH_IRQHandler)(void);
	void (*GPIOA_IRQHandler)(void);
	void (*GPIOB_IRQHandler)(void);
	void (*GPIOC_IRQHandler)(void);
	void (*GPIOD_IRQHandler)(void);
	void (*GPIOE_IRQHandler)(void);
	void (*GPIOF_IRQHandler)(void);
	void (*GPIOG_IRQHandler)(void);
	void (*GPIOH_IRQHandler)(void);
	void (*GPIOJ_IRQHandler)(void);
	void (*GPIOK_IRQHandler)(void);
	void (*GPIOL_IRQHandler)(void);
	void (*GPIOM_IRQHandler)(void);
	void (*DMA_CH0_IRQHandler)(void);
	void (*DMA_CH1_IRQHandler)(void);
	void (*DMA_CH2_IRQHandler)(void);
	void (*DMA_CH3_IRQHandler)(void);
	void (*DMA_CH4_IRQHandler)(void);
	void (*DMA_CH5_IRQHandler)(void);
	void (*DMA_CH6_IRQHandler)(void);
	void (*DMA_CH7_IRQHandler)(void);
	void (*DMA_CH8_IRQHandler)(void);
	void (*DMA_CH9_IRQHandler)(void);
	void (*DMA_CH10_IRQHandler)(void);
	void (*DMA_CH11_IRQHandler)(void);
	void (*DMA_CH12_IRQHandler)(void);
	void (*DMA_CH13_IRQHandler)(void);
	void (*DMA_CH14_IRQHandler)(void);
	void (*DMA_CH15_IRQHandler)(void);
	void (*DMA_CH16_IRQHandler)(void);
	void (*DMA_CH17_IRQHandler)(void);
	void (*DMA_CH18_IRQHandler)(void);
	void (*DMA_CH19_IRQHandler)(void);
	void (*DMA_CH20_IRQHandler)(void);
	void (*DMA_CH21_IRQHandler)(void);
	void (*DMA_CH22_IRQHandler)(void);
	void (*DMA_CH23_IRQHandler)(void);
	void (*DMA_CH24_IRQHandler)(void);
	void (*DMA_CH25_IRQHandler)(void);
	void (*DMA_CH26_IRQHandler)(void);
	void (*DMA_CH27_IRQHandler)(void);
	void (*DMA_CH28_IRQHandler)(void);
	void (*DMA_CH29_IRQHandler)(void);
	void (*DMA_CH30_IRQHandler)(void);
	void (*DMA_CH31_IRQHandler)(void);
	void (*TMR0_IRQHandler)(void);
	void (*TMR1_IRQHandler)(void);
	void (*TMR2_IRQHandler)(void);
	void (*TMR3_IRQHandler)(void);
	void (*ETMR0_IRQHandler)(void);
	void (*ETMR1_IRQHandler)(void);
	void (*ETMR2_IRQHandler)(void);
	void (*ETMR3_IRQHandler)(void);
	void (*UART0_TD_IRQHandler)(void);
	void (*UART0_MS_IRQHandler)(void);
	void (*UART0_RX_IRQHandler)(void);
	void (*UART0_TX_IRQHandler)(void);
	void (*UART0_RT_IRQHandler)(void);
	void (*UART0_E_IRQHandler)(void);
	void (*UART0_IRQHandler)(void);
	void (*UART1_TD_IRQHandler)(void);
	void (*UART1_MS_IRQHandler)(void);
	void (*UART1_RX_IRQHandler)(void);
	void (*UART1_TX_IRQHandler)(void);
	void (*UART1_RT_IRQHandler)(void);
	void (*UART1_E_IRQHandler)(void);
	void (*UART1_IRQHandler)(void);
	void (*UART2_TD_IRQHandler)(void);
	void (*UART2_MS_IRQHandler)(void);
	void (*UART2_RX_IRQHandler)(void);
	void (*UART2_TX_IRQHandler)(void);
	void (*UART2_RT_IRQHandler)(void);
	void (*UART2_E_IRQHandler)(void);
	void (*UART2_IRQHandler)(void);
	void (*UART3_TD_IRQHandler)(void);
	void (*UART3_MS_IRQHandler)(void);
	void (*UART3_RX_IRQHandler)(void);
	void (*UART3_TX_IRQHandler)(void);
	void (*UART3_RT_IRQHandler)(void);
	void (*UART3_E_IRQHandler)(void);
	void (*UART3_IRQHandler)(void);
	void (*TUART0_RX_IRQHandler)(void);
	void (*TUART0_TX_IRQHandler)(void);
	void (*TUART0_RO_IRQHandler)(void);
	void (*TUART0_TO_IRQHandler)(void);
	void (*TUART0_IRQHandler)(void);
	void (*TUART1_RX_IRQHandler)(void);
	void (*TUART1_TX_IRQHandler)(void);
	void (*TUART1_RO_IRQHandler)(void);
	void (*TUART1_TO_IRQHandler)(void);
	void (*TUART1_IRQHandler)(void);
	void (*SPI0_IRQHandler)(void);
	void (*SPI0_RX_IRQHandler)(void);
	void (*SPI0_TX_IRQHandler)(void);
	void (*SPI0_RO_IRQHandler)(void);
	void (*SPI0_RT_IRQHandler)(void);
	void (*SPI1_IRQHandler)(void);
	void (*SPI1_RX_IRQHandler)(void);
	void (*SPI1_TX_IRQHandler)(void);
	void (*SPI1_RO_IRQHandler)(void);
	void (*SPI1_RT_IRQHandler)(void);
	void (*SPI2_IRQHandler)(void);
	void (*SPI2_RX_IRQHandler)(void);
	void (*SPI2_TX_IRQHandler)(void);
	void (*SPI2_RO_IRQHandler)(void);
	void (*SPI2_RT_IRQHandler)(void);
	void (*SPI3_IRQHandler)(void);
	void (*SPI3_RX_IRQHandler)(void);
	void (*SPI3_TX_IRQHandler)(void);
	void (*SPI3_RO_IRQHandler)(void);
	void (*SPI3_RT_IRQHandler)(void);
	void (*I2C0_IRQHandler)(void);
	void (*I2C1_IRQHandler)(void);
	void (*SPWR0_IRQHandler)(void);
	void (*SPWR1_IRQHandler)(void);
	void (*MILSTD0_IRQHandler)(void);
	void (*MILSTD1_IRQHandler)(void);
	void (*ECAP0_IRQHandler)(void);
	void (*ECAP1_IRQHandler)(void);
	void (*ECAP2_IRQHandler)(void);
	void (*ECAP3_IRQHandler)(void);
	void (*ECAP4_IRQHandler)(void);
	void (*ECAP5_IRQHandler)(void);
	void (*PWM0_IRQHandler)(void);
	void (*PWM0_HD_IRQHandler)(void);
	void (*PWM0_TZ_IRQHandler)(void);
	void (*PWM1_IRQHandler)(void);
	void (*PWM1_HD_IRQHandler)(void);
	void (*PWM1_TZ_IRQHandler)(void);
	void (*PWM2_IRQHandler)(void);
	void (*PWM2_HD_IRQHandler)(void);
	void (*PWM2_TZ_IRQHandler)(void);
	void (*PWM3_IRQHandler)(void);
	void (*PWM3_HD_IRQHandler)(void);
	void (*PWM3_TZ_IRQHandler)(void);
	void (*PWM4_IRQHandler)(void);
	void (*PWM4_HD_IRQHandler)(void);
	void (*PWM4_TZ_IRQHandler)(void);
	void (*PWM5_IRQHandler)(void);
	void (*PWM5_HD_IRQHandler)(void);
	void (*PWM5_TZ_IRQHandler)(void);
	void (*PWM6_IRQHandler)(void);
	void (*PWM6_HD_IRQHandler)(void);
	void (*PWM6_TZ_IRQHandler)(void);
	void (*PWM7_IRQHandler)(void);
	void (*PWM7_HD_IRQHandler)(void);
	void (*PWM7_TZ_IRQHandler)(void);
	void (*PWM8_IRQHandler)(void);
	void (*PWM8_HD_IRQHandler)(void);
	void (*PWM8_TZ_IRQHandler)(void);
	void (*PWM9_IRQHandler)(void);
	void (*PWM9_HD_IRQHandler)(void);
	void (*PWM9_TZ_IRQHandler)(void);
	void (*QEP0_IRQHandler)(void);
	void (*QEP1_IRQHandler)(void);
	void (*QEP2_IRQHandler)(void);
	void (*QEP3_IRQHandler)(void);
	void (*ADC_SEQ0_IRQHandler)(void);
	void (*ADC_SEQ1_IRQHandler)(void);
	void (*ADC_SEQ2_IRQHandler)(void);
	void (*ADC_SEQ3_IRQHandler)(void);
	void (*ADC_SEQ4_IRQHandler)(void);
	void (*ADC_SEQ5_IRQHandler)(void);
	void (*ADC_SEQ6_IRQHandler)(void);
	void (*ADC_SEQ7_IRQHandler)(void);
	void (*ADC_DC_IRQHandler)(void);
	void (*ETH_IRQHandler)(void);
	void (*CAN0_IRQHandler)(void);
	void (*CAN1_IRQHandler)(void);
	void (*CAN2_IRQHandler)(void);
	void (*CAN3_IRQHandler)(void);
	void (*CAN4_IRQHandler)(void);
	void (*CAN5_IRQHandler)(void);
	void (*CAN6_IRQHandler)(void);
	void (*CAN7_IRQHandler)(void);
	void (*CAN8_IRQHandler)(void);
	void (*CAN9_IRQHandler)(void);
	void (*CAN10_IRQHandler)(void);
	void (*CAN11_IRQHandler)(void);
	void (*CAN12_IRQHandler)(void);
	void (*CAN13_IRQHandler)(void);
	void (*CAN14_IRQHandler)(void);
	void (*CAN15_IRQHandler)(void);
	void (*FPU_IRQHandler)(void);
	void (*TMU_IRQHandler)(void);
	void (*LAU_IRQHandler)(void);
	void (*SDFM_IRQHandler)(void);
	void (*OWI0_IRQHandler)(void);
	void (*OWI1_IRQHandler)(void);
};

// Заполнитель массива векторов
#define ISR_VECTORS {\
   (void(*)(void))&_estack,\
   Reset_Handler,\
   NMI_Handler,\
   HardFault_Handler,\
   MemManage_Handler,\
   BusFault_Handler,\
   UsageFault_Handler,\
   0,\
   0,\
   0,\
   0,\
   SVC_Handler,\
   DebugMon_Handler,\
   0,\
   PendSV_Handler,\
   SysTick_Handler,\
   WDT_IRQHandler,\
   RCU_IRQHandler,\
   RTC_IRQHandler,\
   MFLASH_IRQHandler,\
   BFLASH_IRQHandler,\
   GPIOA_IRQHandler,\
   GPIOB_IRQHandler,\
   GPIOC_IRQHandler,\
   GPIOD_IRQHandler,\
   GPIOE_IRQHandler,\
   GPIOF_IRQHandler,\
   GPIOG_IRQHandler,\
   GPIOH_IRQHandler,\
   GPIOJ_IRQHandler,\
   GPIOK_IRQHandler,\
   GPIOL_IRQHandler,\
   GPIOM_IRQHandler,\
   DMA_CH0_IRQHandler,\
   DMA_CH1_IRQHandler,\
   DMA_CH2_IRQHandler,\
   DMA_CH3_IRQHandler,\
   DMA_CH4_IRQHandler,\
   DMA_CH5_IRQHandler,\
   DMA_CH6_IRQHandler,\
   DMA_CH7_IRQHandler,\
   DMA_CH8_IRQHandler,\
   DMA_CH9_IRQHandler,\
   DMA_CH10_IRQHandler,\
   DMA_CH11_IRQHandler,\
   DMA_CH12_IRQHandler,\
   DMA_CH13_IRQHandler,\
   DMA_CH14_IRQHandler,\
   DMA_CH15_IRQHandler,\
   DMA_CH16_IRQHandler,\
   DMA_CH17_IRQHandler,\
   DMA_CH18_IRQHandler,\
   DMA_CH19_IRQHandler,\
   DMA_CH20_IRQHandler,\
   DMA_CH21_IRQHandler,\
   DMA_CH22_IRQHandler,\
   DMA_CH23_IRQHandler,\
   DMA_CH24_IRQHandler,\
   DMA_CH25_IRQHandler,\
   DMA_CH26_IRQHandler,\
   DMA_CH27_IRQHandler,\
   DMA_CH28_IRQHandler,\
   DMA_CH29_IRQHandler,\
   DMA_CH30_IRQHandler,\
   DMA_CH31_IRQHandler,\
   TMR0_IRQHandler,\
   TMR1_IRQHandler,\
   TMR2_IRQHandler,\
   TMR3_IRQHandler,\
   ETMR0_IRQHandler,\
   ETMR1_IRQHandler,\
   ETMR2_IRQHandler,\
   ETMR3_IRQHandler,\
   UART0_TD_IRQHandler,\
   UART0_MS_IRQHandler,\
   UART0_RX_IRQHandler,\
   UART0_TX_IRQHandler,\
   UART0_RT_IRQHandler,\
   UART0_E_IRQHandler,\
   UART0_IRQHandler,\
   UART1_TD_IRQHandler,\
   UART1_MS_IRQHandler,\
   UART1_RX_IRQHandler,\
   UART1_TX_IRQHandler,\
   UART1_RT_IRQHandler,\
   UART1_E_IRQHandler,\
   UART1_IRQHandler,\
   UART2_TD_IRQHandler,\
   UART2_MS_IRQHandler,\
   UART2_RX_IRQHandler,\
   UART2_TX_IRQHandler,\
   UART2_RT_IRQHandler,\
   UART2_E_IRQHandler,\
   UART2_IRQHandler,\
   UART3_TD_IRQHandler,\
   UART3_MS_IRQHandler,\
   UART3_RX_IRQHandler,\
   UART3_TX_IRQHandler,\
   UART3_RT_IRQHandler,\
   UART3_E_IRQHandler,\
   UART3_IRQHandler,\
   TUART0_RX_IRQHandler,\
   TUART0_TX_IRQHandler,\
   TUART0_RO_IRQHandler,\
   TUART0_TO_IRQHandler,\
   TUART0_IRQHandler,\
   TUART1_RX_IRQHandler,\
   TUART1_TX_IRQHandler,\
   TUART1_RO_IRQHandler,\
   TUART1_TO_IRQHandler,\
   TUART1_IRQHandler,\
   SPI0_IRQHandler,\
   SPI0_RX_IRQHandler,\
   SPI0_TX_IRQHandler,\
   SPI0_RO_IRQHandler,\
   SPI0_RT_IRQHandler,\
   SPI1_IRQHandler,\
   SPI1_RX_IRQHandler,\
   SPI1_TX_IRQHandler,\
   SPI1_RO_IRQHandler,\
   SPI1_RT_IRQHandler,\
   SPI2_IRQHandler,\
   SPI2_RX_IRQHandler,\
   SPI2_TX_IRQHandler,\
   SPI2_RO_IRQHandler,\
   SPI2_RT_IRQHandler,\
   SPI3_IRQHandler,\
   SPI3_RX_IRQHandler,\
   SPI3_TX_IRQHandler,\
   SPI3_RO_IRQHandler,\
   SPI3_RT_IRQHandler,\
   I2C0_IRQHandler,\
   I2C1_IRQHandler,\
   SPWR0_IRQHandler,\
   SPWR1_IRQHandler,\
   MILSTD0_IRQHandler,\
   MILSTD1_IRQHandler,\
   ECAP0_IRQHandler,\
   ECAP1_IRQHandler,\
   ECAP2_IRQHandler,\
   ECAP3_IRQHandler,\
   ECAP4_IRQHandler,\
   ECAP5_IRQHandler,\
   PWM0_IRQHandler,\
   PWM0_HD_IRQHandler,\
   PWM0_TZ_IRQHandler,\
   PWM1_IRQHandler,\
   PWM1_HD_IRQHandler,\
   PWM1_TZ_IRQHandler,\
   PWM2_IRQHandler,\
   PWM2_HD_IRQHandler,\
   PWM2_TZ_IRQHandler,\
   PWM3_IRQHandler,\
   PWM3_HD_IRQHandler,\
   PWM3_TZ_IRQHandler,\
   PWM4_IRQHandler,\
   PWM4_HD_IRQHandler,\
   PWM4_TZ_IRQHandler,\
   PWM5_IRQHandler,\
   PWM5_HD_IRQHandler,\
   PWM5_TZ_IRQHandler,\
   PWM6_IRQHandler,\
   PWM6_HD_IRQHandler,\
   PWM6_TZ_IRQHandler,\
   PWM7_IRQHandler,\
   PWM7_HD_IRQHandler,\
   PWM7_TZ_IRQHandler,\
   PWM8_IRQHandler,\
   PWM8_HD_IRQHandler,\
   PWM8_TZ_IRQHandler,\
   PWM9_IRQHandler,\
   PWM9_HD_IRQHandler,\
   PWM9_TZ_IRQHandler,\
   QEP0_IRQHandler,\
   QEP1_IRQHandler,\
   QEP2_IRQHandler,\
   QEP3_IRQHandler,\
   ADC_SEQ0_IRQHandler,\
   ADC_SEQ1_IRQHandler,\
   ADC_SEQ2_IRQHandler,\
   ADC_SEQ3_IRQHandler,\
   ADC_SEQ4_IRQHandler,\
   ADC_SEQ5_IRQHandler,\
   ADC_SEQ6_IRQHandler,\
   ADC_SEQ7_IRQHandler,\
   ADC_DC_IRQHandler,\
   ETH_IRQHandler,\
   CAN0_IRQHandler,\
   CAN1_IRQHandler,\
   CAN2_IRQHandler,\
   CAN3_IRQHandler,\
   CAN4_IRQHandler,\
   CAN5_IRQHandler,\
   CAN6_IRQHandler,\
   CAN7_IRQHandler,\
   CAN8_IRQHandler,\
   CAN9_IRQHandler,\
   CAN10_IRQHandler,\
   CAN11_IRQHandler,\
   CAN12_IRQHandler,\
   CAN13_IRQHandler,\
   CAN14_IRQHandler,\
   CAN15_IRQHandler,\
   FPU_IRQHandler,\
   TMU_IRQHandler,\
   LAU_IRQHandler,\
   SDFM_IRQHandler,\
   OWI0_IRQHandler,\
   OWI1_IRQHandler,\
}

#endif

/*@}*/
