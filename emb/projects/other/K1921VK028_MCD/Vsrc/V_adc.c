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
 
 \file      V_adc.c
 \brief     Модуль обработки АЦП (см. TAdcDrv) MCB_028
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 22/03/2019

 \addtogroup V_adc 
 @{*/

/* Расписание каналов
 * ADC13	Ia
 * ADC19		Ic
 * ADC1	Udc
 * ADC31	0.75V
 * ADC18	0.03V
 * ADC20	Pot
 * ADC15	AIN1
 * ADC27	AIN2
 * ADC29	TempSens
 */

#include "main.h"

//! \memberof TAdcDrv
//!
void AdcDrv_init(TAdcDrv *p) {

//! Инициализация АЦП при программном запуске без использовании прерываний и фифо

    Uint32 trash;
    // Запрет всех секвенсоров
    ADC->SEQSYNC = 0;

    // Сброс Счетчиков прерывний и измерений
    ADC->SEQ[0].SCVAL = 0;
    ADC->SEQ[1].SCVAL = 0;
    ADC->SEQ[2].SCVAL = 0;
    ADC->SEQ[3].SCVAL = 0;
    ADC->SEQ[4].SCVAL = 0;
    ADC->SEQ[5].SCVAL = 0;
    ADC->SEQ[6].SCVAL = 0;
    ADC->SEQ[7].SCVAL = 0;

    //Включаем секвенсор
    ADC->SEQSYNC_bit.SYNC0 = 1;
    //Ставим маску прерывания
    ADC->IM_bit.SEQIM0 = 1;
    //Настраиваем источник запуска программный
    ADC->EMUX_bit.EM0 = ADC_EMUX_EM0_SwReq;
    // Разрешить секвенсоров
    ADC->SEQEN_bit.SEQEN0 = 1;
    //Настраиваем количество перезапусков секвенсора RCNT + 1
    ADC->SEQ[0].SCCTL_bit.RCNT = 3;
    ADC->SEQ[0].SCCTL_bit.RAVGEN = 1;   // Разрешено усреднение
    // Нет прерывания
    ADC->SEQ[0].SCCTL_bit.ICNT = 0;
    ADC->SEQ[0].SRQCTL_bit.RQMAX = 0x6;


    ADC->ACTL[0].ACTL_bit.ADCEN = 0x1;                            // Разрешаем работу АЦП
    ADC->ACTL[0].ACTL_bit.SELRES = ADC_ACTL_ACTL_SELRES_12bit;
    ADC->ACTL[1].ACTL_bit.ADCEN = 0x1;                          // Разрешаем работу АЦП
    ADC->ACTL[1].ACTL_bit.SELRES = ADC_ACTL_ACTL_SELRES_12bit;
    ADC->ACTL[2].ACTL_bit.ADCEN = 0x1;                          // Разрешаем работу АЦП
    ADC->ACTL[2].ACTL_bit.SELRES = ADC_ACTL_ACTL_SELRES_12bit;
    ADC->ACTL[3].ACTL_bit.ADCEN = 0x1;                          // Разрешаем работу АЦП
    ADC->ACTL[3].ACTL_bit.SELRES = ADC_ACTL_ACTL_SELRES_12bit;


    ADC->SEQ[0].SRQSEL0_bit.RQ0 = 13;               // Какой вход АЦП когда опрашивается
    ADC->SEQ[0].SRQSEL0_bit.RQ1 = 19;               //  --//--
    ADC->SEQ[0].SRQSEL0_bit.RQ2 = 1;                //  --//--
    ADC->SEQ[0].SRQSEL0_bit.RQ3 = 20;               //  --//--
    ADC->SEQ[0].SRQSEL1_bit.RQ4 = 15;               //  --//--
    ADC->SEQ[0].SRQSEL1_bit.RQ5 = 27;               //  --//--
    ADC->SEQ[0].SRQSEL1_bit.RQ6 = 29;               //  --//--


    // Ждём, пока АЦП выставит флаг "ГОТОВ" (можно вставить этот цикл после "ADCEN = 1")
    while (!ADC->ACTL[0].ACTL_bit.ADCRDY) {};
    while (!ADC->ACTL[1].ACTL_bit.ADCRDY) {};
    while (!ADC->ACTL[2].ACTL_bit.ADCRDY) {};
    while (!ADC->ACTL[3].ACTL_bit.ADCRDY) {};

}


//!Расчет АЦП с частотой основного расчета всей системы управления (обычно 10кГц).

//! Занимается обработкой измеренных АЦП значений и преобразует в формат IQ24.
//! Токи фаз для повышения точности усредняются за несколько измерений

//! \memberof TAdcDrv

void AdcDrv_fast_calc(TAdcDrv *p) {
	Uint32 trash;
	Uint16 pot, ain1, ain2, temper;

	p->IA_temp = (int16) ADC->SEQ[0].SFIFO_bit.DATA;
	p->IC_temp = (int16) ADC->SEQ[0].SFIFO_bit.DATA;

	p->Udc_temp = (int16) ADC->SEQ[0].SFIFO_bit.DATA;

	pot = (int16) ADC->SEQ[0].SFIFO_bit.DATA;
	ain1 = (int16) ADC->SEQ[0].SFIFO_bit.DATA;
	ain2 = (int16) ADC->SEQ[0].SFIFO_bit.DATA;

	p->T_temp = (int16) ADC->SEQ[0].SFIFO_bit.DATA;

	// Преобразование
	p->Imeas_a = p->IaGainNom * (((p->IA_temp<< 4) + p->Imeas_a_offset));
	p->Imeas_c = p->IcGainNom * (((p->IC_temp<< 4) + p->Imeas_c_offset));
	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);
	p->Imeas_b = -p->Imeas_a - p->Imeas_c;
	p->T_meas = p->TGainNom*(p->T_temp);

// Очистка ФИФО
    while (ADC->SEQ[0].SFLOAD)
        trash = ADC->SEQ[0].SFIFO;

}

//!Медленный расчет.

//!Занимается пересчетом коэффициентов, используемых в скоростной функции расчета,
//!чтобы не занимать процессорное время там. Находит коэффициенты,
//!на которые надо умножить полученное с АЦП значение, чтобы получить
//!относительные единицы с заданной базой.

//! Пример   p->PvalveGainNom=_IQ16mpy(p->Pvalve_gain,_IQ(1.0/100));
//! Pvalve_gain - значение в формате int. задается пользователем в UniCON.
//!Определяет, скольким процентам соответствует полный диапазон АЦП. В простейшем случае
//!равен 100. Т.е. когда на АЦП максимальный сигнал, это соответствует 100%.

//!_IQ(1.0/100) обратное значение для масштабирующего коэффициента. Так как величину процентов
//!естественнее всего перевести в относительные единицы так, что 100% соответствут 1.0,
//!то масштабирующий коэффициент (база) равен 100. Т.е. UniCON, прочитав из системы управления
//! число 1.0 в формате 8.24 должен умножить его на 100, чтобы отобразились проценты.
//! Здесь коэффициент задан явно как 1.0/100, но для ряда случаев базовое значение нужно менять.
//!Так, для токов фаз используется значение _1_I_nom, в формате 8.24, соответствующее единице деленной на
//базовое значение тока, например, 200 А. Так как в зависимости от мощности преобразователя базовый ток может меняться,
//то это значение, в отличие от процентов, сделано настраиваемым. Расчет _1_I_nom идет в другом месте, так как
//занимает много тактов расчета.

//Для беззнакового значения АЦП измеряет число от 0 до 65535. (16 разрядов, где заполнены верхние).
//Для примера с процентами необходимо сделать так, чтобы получилось результирующее значение в формате 8.24,
//где 1.0 это 65535. Таким образом, нужно сдвинуть число 65535 на 24-16=8 разрядов.
//Сдвиг на 8 разрядов - это умножение на число 255. Число 255 - это 1.0 в формате 24.8.

//Таким образом, PvalveGainNom - это коэффициент в формате 24.8. он получается в результате использования функции
//_IQ16mpy, аргумены которой Pvalve_gain (int) и 1.0/100 в формате 8.24. Функция IQ множения
//по сути представляет собой обычное оуможение в 64 разрядах со сдвигом результата вправо на Q разрядов.
//Т.е. _IQ16mpy умножает число в формате IQ24 9второй аргумент) на целочисленный коэффициент (первый аргумент),
//а потом сдвигате результат на 16 разрядов вправо.
//Так, в результате _IQ16mpy(p->Pvalve_gain,_IQ(1.0/100)); получается целочисленное число 255, являющейся
//1.0 в формате 24.8 из-за сдвига на 16 разрядов вправо.

//Всё вышеприведенное мутево сделано с одной целью - увеличить производитлеьность обработки АЦП.

//! \memberof TAdcDrv
void AdcDrv_slow_calc(TAdcDrv *p) {

	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain, drv_params._1_I_nom) << 1;
	p->IbGainNom = _IQ16mpy(p->Imeas_b_gain, drv_params._1_I_nom) << 1;
	p->IcGainNom = _IQ16mpy(p->Imeas_c_gain, drv_params._1_I_nom) << 1;
	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain, drv_params._1_Udc_nom) << 4;
	p->TGainNom = _IQ16mpy(p->T_meas_gain, _IQ(0.05)) << 4; //0.05 = 1/20
}

//! Миллисекундный расчет

//! \memberof TAdcDrv
void AdcDrv_ms_calc(TAdcDrv *p) {

}

/*@}*/

