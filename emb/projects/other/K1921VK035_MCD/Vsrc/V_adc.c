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
 \brief     Модуль обработки АЦП (см. TAdcDrv)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_adc 
 @{*/


#include "main.h"

//!Инициализация.

//! Настраиваются секвенсоры и тип оцифровки данных. каналы для оцифровки, частота.
//! В данном случае оцифровка происходит по событию таймера,частота которого
//! равна частоте ШИМ, чтобы измерять ровно посередине периода ШИМ (требуется для шунтовых
//! датчиков тока)
//Запуск оцифровки производится по таймеру NT_PWM3, который синхронизирован с другими таймерами ШИМ.
//Оцифрованные измерения складываются в ФИФО. Каждый канал АЦП настроен на отдельный секвенсор с ФИФО длиной до 16 измерений.
//В прерывании с частотой 10 кГц данные забираются из ФИФО и складываются в кольцевые массивы (старые затираются новыми).
//В том же прерывании из кольцевого массива берется N последних точек и из них вычисляется среднее арифметическое.
//Число выборок для усреднения N зависит от частоты ШИМ и равна Fшим/10кГц. Если частоты ШИМ меньше 10 кГц, то берется одна выборка, если больше 40 кГц - 4 выборки.
//К вычисленному среднему значению добавляется калибровочный сдвиг, и оно умножается на коэффициент измерения, в результате получается окончательный результат измерения.

//! \memberof TAdcDrv
void AdcDrv_init(TAdcDrv *p) {
	PWM0->ETSEL_bit.SOCAEN = 1;
	PWM0->ETSEL_bit.SOCASEL = ET_CTR_ZERO;
	PWM0->ETPS_bit.SOCAPRD = 2;

	Uint32 AdcClock, AdcDiv, trash;
	Uint32 pwmPrd = PWM0->TBPRD;	// Предположим, частота 10 кГц

	if (pwmPrd < 1000) pwmPrd = 1000;
    //Инициализация ADC
    RCU->ADCCFG_bit.CLKSEL = RCU_ADCCFG_CLKSEL_PLLCLK;	// Тактирование от PLL
    RCU->ADCCFG_bit.DIVN = 0x1; 						// N = 2 * (DIVN + 1) = 4 -> ACLK = 25 MHz
    RCU->ADCCFG_bit.DIVEN = 0x1;						// Разрешить делитель
    AdcDiv = 2 * (RCU->ADCCFG_bit.DIVN + 1);			// Итого деление частоты
    AdcClock = SystemCoreClock / AdcDiv;
    RCU->ADCCFG_bit.CLKEN = 0x1;						// Разрешить тактирование
    RCU->ADCCFG_bit.RSTDIS = 0x1;						// Снимаем сброс
    ADC->ACTL_bit.ADCEN = 0x1;							// Разрешаем работу АЦП

    //Настройка секвенсора 0
    // CH0, CH1, CH2, CH3.
    ADC->EMUX_bit.EM0 = ADC_EMUX_EM0_PWM012A;		// Запуск от таймера
    ADC->SEQSYNC = ADC_SEQSYNC_SYNC0_Msk;			// Разрешить секвенсор SEQ0
    ADC->SEQ[0].SRQCTL_bit.RQMAX = 0x3;				// Опрашивать 4 канала за раз = RQMAX + 1
    ADC->SEQ[0].SRQSEL_bit.RQ0 = 0x0;				// Какой вход АЦП когда опрашивается
    ADC->SEQ[0].SRQSEL_bit.RQ1 = 0x1;				//	--//--
    ADC->SEQ[0].SRQSEL_bit.RQ2 = 0x2;				//  --//--
    ADC->SEQ[0].SRQSEL_bit.RQ3 = 0x3;				//  --//--
    ADC->SEQ[0].SCCTL_bit.RCNT = 3;					// Делать ещё три перезапуска после первого запуска
    ADC->SEQ[0].SRTMR_bit.VAL = (pwmPrd / AdcDiv) / (ADC->SEQ[0].SCCTL_bit.RCNT + 1);	// Пауза между пусами	 АЦП на период ШИМ
    ADC->SEQ[0].SCCTL_bit.ICNT = 3;					// Вызов прерывания через каждые (ICNT + 1) оцифровки
    ADC->SEQ[0].SCCTL_bit.RAVGEN = 1;				// Разрешить усреднять по 4 точкам
    ADC->SEQEN_bit.SEQEN0 = 1;						// Разрешить секвенсор 0


	// Очистка FIFO
	while (ADC->SEQ[0].SFLOAD)
		trash = ADC->SEQ[0].SFIFO;

    // Разрешить EPWM0 запускать АЦП по нулю


    // Ждём, пока АЦП выставит флаг "ГОТОВ" (можно вставить этот цикл после "ADCEN = 1")
    while (!ADC->ACTL_bit.ADCRDY) {};

    // Разрешить прерывание от первого секвенсера
    ADC->IM_bit.SEQIM0 = 1;
    NVIC_EnableIRQ(ADC_SEQ0_IRQn);
    NVIC_SetPriority(ADC_SEQ0_IRQn, IRQ_PRIORITY_ADC);
}


//!Расчет АЦП с частотой основного расчета всей системы управления (обычно 10кГц).

//! Занимается обработкой измеренных АЦП значений и преобразует в формат IQ24.
//! Токи фаз для повышения точности усредняются за несколько измерений

//! \memberof TAdcDrv

void AdcDrv_fast_calc(TAdcDrv *p) {
	Uint32 trash;
	// Если всё пошло хорошо, то в ФИФЕ будут уже усреднённые результаты - 4 штуки.
	p->IA_temp = ADC->SEQ[0].SFIFO;
	p->IB_temp = ADC->SEQ[0].SFIFO;
	p->Udc_temp = ADC->SEQ[0].SFIFO;
	p->AI_temp = ADC->SEQ[0].SFIFO;

	// Очистка FIFO на случай, если почему-то там оказалось больше чем надо значений (бывает после остановки житагом)
	while (ADC->SEQ[0].SFLOAD)
		trash = ADC->SEQ[0].SFIFO;

	p->Imeas_a = p->IaGainNom * ((p->IA_temp<< 4) + p->Imeas_a_offset);
	p->Imeas_b = p->IbGainNom * ((p->IB_temp<< 4) + p->Imeas_b_offset);
	p->Udc_meas = p->UdcGainNom * (p->Udc_temp + p->Udc_meas_offset);
	p->Imeas_c = -p->Imeas_a - p->Imeas_b;
	p->AI_meas = p->AI_temp *  p->AIGainNom;

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
	// Пересчёт пауз между перезапусками
	volatile Uint16 pwmPrd = PWM0->TBPRD;

	// Если считает вверх-вниз, то период на деле в два раза больше
	if (PWM0->TBCTL_bit.CTRMODE == TB_COUNT_UPDOWN)
		pwmPrd = pwmPrd << 1;

	// Делитель частоты АЦП
	Uint16 AdcDiv = 2 * (RCU->ADCCFG_bit.DIVN + 1);
	if (pwmPrd < 1000) pwmPrd = 1000;

	ADC->SEQ[0].SRTMR_bit.VAL = (pwmPrd / AdcDiv) / (ADC->SEQ[0].SCCTL_bit.RCNT + 1);

	p->IaGainNom = _IQ16mpy(p->Imeas_a_gain, drv_params._1_I_nom) << 1;
	p->IbGainNom = _IQ16mpy(p->Imeas_b_gain, drv_params._1_I_nom) << 1;
	p->UdcGainNom = _IQ16mpy(p->Udc_meas_gain, drv_params._1_Udc_nom) << 4;
	p->AIGainNom = _IQ16mpy(p->AI_meas_gain, _IQ(1)) << 4;
}

//! Миллисекундный расчет

//! \memberof TAdcDrv
void AdcDrv_ms_calc(TAdcDrv *p) {

}

/*@}*/

