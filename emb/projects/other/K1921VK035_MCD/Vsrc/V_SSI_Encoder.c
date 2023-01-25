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

//! \memberof TSSI_Encoder
void SSI_Encoder_init(TSSI_Encoder *p) {
	volatile long delay;
	volatile Uint32 tempREG;

	// Настройка ножек под SPI
	GPIOB->ALTFUNCSET = (1 << 5) | (1 << 6); // Тактирование (SPI_SCK)

	// Настройка модуля SPI
	// Тактирование модуля SPI в файле "src/system_K1921VK035.c" настроено на fIN = 25 МГц
	// Эта частота проходит ещё через два делителя.
	// SSPCPSR - первый делитель, в диапазоне 2 ... 254, может быть только чётным (младший бит всегда аппаратно равен 0)
	// SSPCR0.bit.SCR - второй делитель от 0 до 255.
	// Битрейт в итоге BitRate = fIN / ( CPSR * (SCR + 1) )

	SPI->IMSC = 0x0;	// Запретить все прерывания
	SPI->DMACR = 0;		// Запретить DMA
	SPI->ICR = 0x3;		// Сброс прерываний на всякий случай ("переполнение FIFO приёма" и "необслуженное FIFO приёма")

	SPI->CPSR = 4;				// Деление входной частоты на 4



	// В CR0 настраивается второй делитель частоты, разрешение и режим работы энкодера.
	//
	// Второй делитель = 62, итого f_ssp = 25 МГц / (4 * (62 + 1)) = 99,2 кГц
	//
	// Настройка фазы и полярности для работы в режиме SPI
	// По описанию на датчик дела такие: по первому падающему фронту он загружает в свой
	// внутренний регистр новые данные, а с каждым растущим фронтов выводит их на линию.
	// Стало быть данные на линии меняются на растущем фронте, а значит считывать их надо
	// на падающем. Но при этом по самому первому фронту ничего вычитывать не надо, а значит
	// старший бит принятых данных надо обнулять.
	// Кроме того на ОИ клок инвертируется, и это надо учитывать в настройке.
	//
	// Размер кадра на 1 больше, чем число в регитсре, стало быть (12 + 1) = 13 бит, из которых первый выкинем
	//
	// В целях экономии места, запись одной строкой
	//SPI->CR0_bit.FRF = 0x0;		// SSI работает в режиме SPI, что позволяет задать, по какому фронту читать данные
	//SPI->CR0_bit.SPO = 0x0;		// В режиме ожидания CLK в нуле (после инверсии получится в единице)
	//SPI->CR0_bit.SPH = 0x0;		// Выборка данных по растущему фронту синхросигнала (после инверсии получится по падающему)
	//SPI->CR0_bit.SCR = 62;		// Второй делитель = 62 + 1 = 63
	//SPI->CR0_bit.DSS = SSI_ENC_RESOLUTION; // Размер кадра 12 + 1 = 13 бит
	SPI->CR0 = (SSI_ENC_RESOLUTION << SPI_CR0_DSS_Pos) | (62 << SPI_CR0_SCR_Pos);

	// В этих комментариях расписано по каждому полю, что как присваивается, но
	// для экономии на инструкциях записывается одним действием
	//SPI->CR1_bit.MS = 0;		// Режим - мастер
	//SPI->CR1_bit.RXIFLSEL = 0;	// Глубина FIFO на приём = 0 (FIFO не используется)
	//SPI->CR1_bit.TXIFLSEL = 0;	// Глубина FIFO на отправку = 0 (FIFO не используется)
	//SPI->CR1_bit.SSE = 1;		// Разрешить работу SPI
	SPI->CR1 = (1 << SPI_CR1_SSE_Pos);
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

	if (SPI->SR_bit.BSY == 0){//SPI свободен
		Data_read = SPI->DR & SSI_ENC_DATA_MASK;//код с датчика (число от 0 до resol) с обнулённым старшим разрядом
		SPI->DR = 0xff;//отправляем что угодно, главное, чтобы тактирование шло


		if (p->rotation_dir)//обратное направление вращения
			Data_read=(p->resol-1)-Data_read;//период - текущее
		p->Poscnt_res=Data_read;
	}

	//перевод угла в метках на обороте в механический угол
	//Здесь расчет во float - желательно переделать в IQ
	p->theta_mech = _IQ((float )p->Poscnt_res * p->resol_inv); //расчёт механического угла
	p->theta_mech &= 0x00FFFFFF;
	//Фильтр угла
	if (p->theta_mech_filterK!=0){
        p->theta_mech_filtered=p->theta_mech_filtered+_IQmpy(p->theta_mech_filterK,((p->theta_mech-p->theta_mech_filtered+_IQ(0.5))&0x00FFFFFF)-_IQ(0.5));
        p->theta_mech_filtered&=0x00FFFFFF;
	}else
		p->theta_mech_filtered=p->theta_mech;

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

