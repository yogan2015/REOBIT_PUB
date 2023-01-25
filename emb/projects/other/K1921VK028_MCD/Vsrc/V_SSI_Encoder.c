/*!
     Copyright 2017 	АО "НИИЭТ" и ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 
 \file      V_SSI_Encoder.c
 \brief     Модуль оценки скорости и положения при помощи цифрового энкодера, работающего по интерфейсу SSI (см. TSSI_Encoder)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 25/04/2016

 \addtogroup V_QEP
 @{*/

#include "DSP.h"
#include "V_IQmath.h"
#include "V_SSI_Encoder.h"
#include "math.h"
#include "stdlib.h"
#include "main.h"

//! Инициализация

#define SSI_NT_SPI SPI0 //Настройка номера SPI

//! \memberof TSSI_Encoder
void SSI_Encoder_init(TSSI_Encoder *p) {
	volatile long delay;
	volatile Uint32 tempREG;

	// Настройка самого модуля SPI
	// Продолжение настройки тактирования.
	// Полученная ранее частота f_SSP_IN проходит ещё через два делителя.
	// SSPCPSR - первый делитель, в диапазоне 2 ... 254, может быть только чётным (младший бит всегда хардварно равен 0)
	// SSPCR0.bit.SCR - второй делитель от 0 до 255.
	// Битрейт в итоге BitRate = f_SSP_IN / ( SSPCPSR * (SCR + 1) )
	// Тактирование 25 МГц задано в system_K1921VK028.c

	SSI_NT_SPI->CR1 = 0;// Режим - мастер, LoopBack отключён, сам модуль SSP тоже отключён
	SSI_NT_SPI->IMSC = 0x0;		// Запретить все прерывания
	SSI_NT_SPI->DMACR = 0;		// Запретить DMA
	SSI_NT_SPI->ICR = 0x3;	// Очистка прерываний ("переполнение FIFO приёма" и "необслуженное FIFO приёма")

	SSI_NT_SPI->CPSR_bit.CPSDVSR = 4;			// Деление входной частоты на 4 -> 6,25 MHz
	SSI_NT_SPI->CR0_bit.SCR = 0x3F;	// Второй делитель
	SSI_NT_SPI->CR0_bit.DSS = 12;	// Размер данных - 12 бит
	SSI_NT_SPI->CR0_bit.FRF = 0x0;	// Выбор протокола: 0 = SPI
	SSI_NT_SPI->CR0_bit.SPO = 0x0;	// При неактивной линии держать клок в "0"
	SSI_NT_SPI->CR0_bit.SPH = 0x0;	// Читать данные по заднему фронту клока
	SSI_NT_SPI->CR1_bit.SSE = 1;	// Разрешить работу

	p->resol_inv = 1.0 / ((float) p->resol);

	p->read(p);
}


//! Функция расчёта скорости и положения, вызывается с необходимой дискретностью

//! \memberof TSSI_Encoder
void SSI_Encoder_Calc(TSSI_Encoder *p) {
	p->read(p);
}



void SSI_Encoder_Read(TSSI_Encoder*p) {
	_iq theta_elec_temp;
	Uint16 Data_read=0;
	_iq theta_mech_temp;

	if (SSI_NT_SPI->SR_bit.BSY == 0){
		//SPI свободен
		Data_read = SSI_NT_SPI->DR;	//код с датчика (число от 0 до resol)
		SSI_NT_SPI->DR = 0xff;		//отправляем что угодно, главное, чтобы тактирование шло


		if (p->rotation_dir)//обратное направление вращения
			Data_read = (p->resol - 1) - Data_read;//период - текущее
		p->Poscnt_res=Data_read;
	}

	//перевод угла в метках на обороте в механический угол
	//Здесь расчет во float - желательно переделать в IQ
	p->theta_mech = _IQ((float )p->Poscnt_res * p->resol_inv); //расчёт механического угла
	p->theta_mech &= 0x00FFFFFF;
	//Фильтр угла
	if (p->theta_mech_filterK!=0) {
        p->theta_mech_filtered=p->theta_mech_filtered+_IQmpy(p->theta_mech_filterK,((p->theta_mech-p->theta_mech_filtered+_IQ(0.5))&0x00FFFFFF)-_IQ(0.5));
        p->theta_mech_filtered&=0x00FFFFFF;
	} else {
		p->theta_mech_filtered=p->theta_mech;
	}
    // Подсчёт количества полных оборотов.
    if (p->prevThetaMech - p->theta_mech_filtered > _IQ(0.5))
		p->RevolutionCounter++;
	if (p->prevThetaMech - p->theta_mech_filtered < _IQ(-0.5))
		p->RevolutionCounter--;
	p->prevThetaMech=p->theta_mech_filtered;

	//угол в метках без обнуления на обороте, абсолютный
	p->Poscnt_resContinouosLong=p->Poscnt_res+(p->resol*p->RevolutionCounter);
	p->Poscnt_resContinouosInt=p->Poscnt_resContinouosLong;//чтобы было уднобно смотреть в 16ти разрядном осциллографе
	p->Poscnt_resContinouosInt8=p->Poscnt_resContinouosLong&0xF;//чтобы видеть метки в крупном масштабе

	//перевод угла в метках абсолютных (не обнуляемых наобороте) в механический угол
	//на 127 оборотах всё переполнится, но для демо сгодится
	p->theta_mechContinouos = p->theta_mech_filtered + _IQ(p->RevolutionCounter); //расчёт механического угла
	p->theta_elecContinouos = p->theta_mechContinouos*p->pole_pairs+ p->AngleOffset;//электрический угол абсолютный (не обнуляемый)

	//Расчёт электрического положения обнулемого по достижению 360 градусов
	p->theta_el_tmp = p->theta_mech_filtered*p->pole_pairs + p->AngleOffset;
	p->theta_elec = p->theta_el_tmp & 0x00FFFFFF;

}



/*@}*/

