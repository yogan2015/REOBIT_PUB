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
 
 \file      SMSys.c
 \brief     Модуль-обертка для расчета остальных модулей. (см. TSM_Sys)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 */

/** \addtogroup SMSys */
/*@{*/
#include "main.h"

/* Объявление адреса размещения таблицы векторов прерываний */
#if   defined ( __CMCPPARM__ )
	extern const Uint32 __Vectors;
#elif defined (__GNUC__)

#endif

//! Инициализация системы управления после включения

//!Инициализация некоторых модулей и настройка прерываний системы.
//!Здесь настраивается большинство прерываний
//! \memberof TSM_Sys
void SM_Sys_Init(TSM_Sys *p) {
//TODO: добавить тексты перечислений для конфигураций в CODEEDIT
#if defined (HW_MCB3)
	sw.HardwareType = 4;
#elif defined (HW_MCB3_SIMULATOR)
	sw.HardwareType = 5;
#endif
	cmd.all = 0;
	drv_status.all = 0;
	adc.init(&adc); //Инициализация АЦП
	sm_net.init(&sm_net); //Сетевая часть
	sm_prot.init(&sm_prot); //Защиты
	sm_cmd_logic.init(&sm_cmd_logic); //Логика включения/выключения
	sm_ctrl.init(&sm_ctrl); //Структура системы управления
	pwm.init(&pwm); //Модуль ШИМ
	cur_par.init(&cur_par); //Расчет текущих показателей привода
	leds.init(&leds);//светодиоды
	udControl.init(&udControl); //плавная зарядка ЗПТ через термисторы
	FanControl.init(&FanControl); //вентилятор
	//глобальное времЯ (внешние или внутр. часы)
	global_time.init(&global_time);
	dio.init(&dio); //дискретные входы/выходы
	if (drv_params.sens_type == POS_SENSOR_TYPE_HALL){ //В типе датчика выбран ДПР на элементах Холла
		DPReCAP.Init(&DPReCAP); //ДПР иниц.
	}
	if (drv_params.sens_type == POS_SENSOR_TYPE_ENCODER){ //В типе датчика выбран энкодер
		//настроим квадратурный декодер
		posspeedEqep.speed_nom = drv_params.speed_nom;    //базовая скорость
		posspeedEqep.pole_pairs = drv_params.p;    //кол-во пар полюсов дригателя
		posspeedEqep.Posspeed_CTL.bit.dir = 1;    //направление движения
		posspeedEqep.RevolutionCounter=0;
		posspeedEqep.init(&posspeedEqep);//инициализация модуля энкодера
	}
	if (drv_params.sens_type == POS_SENSOR_TYPE_SSI){ //В типе датчика выбран датчик с SSI интерфейсом. Читайте заголовочник модуля перед использованием!
		//настроим модуль датчика положения SSI
		SSI_Encoder.speed_nom = drv_params.speed_nom;    //базовая скорость
		SSI_Encoder.pole_pairs = drv_params.p;    //кол-во пар полюсов дригателя
		SSI_Encoder.rotation_dir = 0;    //направление движения
		SSI_Encoder.RevolutionCounter=0;
		SSI_Encoder.init(&SSI_Encoder);//Датчик положения SSI
	}
	if (drv_params.sens_type == POS_SENSOR_TYPE_ENC_HALL){
		//настроим квадратурный декодер
		DPReCAP.Init(&DPReCAP); //ДПР иниц.
		posspeedEqep.speed_nom = drv_params.speed_nom;    //базовая скорость
		posspeedEqep.pole_pairs = drv_params.p;    //кол-во пар полюсов дригателя
		posspeedEqep.Posspeed_CTL.bit.dir = 1;    //направление движения
		posspeedEqep.RevolutionCounter=0;
		posspeedEqep.init(&posspeedEqep);//инициализация модуля энкодера
	}

	//листалка аварий для отображения на пульте управления (UniCON)
	pult_faults_lister.num_of_words = 2;
	pult_faults_lister.out_refresh_devisor = 1000; //при вызове в мс таймере период обновления будет равен 1сек
	pult_faults_lister.w_ptrs[0] = (Uint16*) &sm_prot.masked_bit_fault1;//перебираются эти флаги аварий модуля защит
	pult_faults_lister.w_ptrs[1] = (Uint16*) &sm_prot.masked_bit_fault2;

	AutoOffset.FilterK = _IQ(0.00001);//постоянная времени фильтра для автосмещения АЦП
	AutoOffset.init(&AutoOffset); //авто смещение некоторых каналов АЦП (токи)

#if defined (HW_MCB3_SIMULATOR)
	//model.motorInternals.udc = 540; //задается через словарь объектов
	model.tpr = _IQ10div(_IQ10(APB0BusClock/1000.0), pwm.Frequency << 1) >> 10; //период частоты ШИМ
	model.dt = _IQ4mpy(_IQ4(150 / 4), pwm.DeadBand >> 20) >> 4; //величина мертвого времени
	model.Init(&model); //Модель двигателя
#endif

	// Настройка таймера 0 на 10 кГц
	TMR0->INTSTATUS_bit.INT = 1;
	TMR0->LOAD_bit.VAL = (APB0BusClock / 10000L) - 1; //9999 надо чтобы не плыло отностильно прерывания ШИМа, когда у того частота 10кГц
	TMR0->CTRL = ((1 << 0) | (1 << 3)); // Запуск и разрешение прерываний

	// Настройка таймера 1 на 1 кГц
	TMR1->INTSTATUS_bit.INT = 1;
	TMR1->LOAD_bit.VAL = (APB0BusClock / 1000L) - 1;
	TMR1->CTRL = ((1 << 0) | (1 << 3)); // Запуск и разрешение прерываний

	//Для подсчета тактов
	TMR2->LOAD_bit.VAL = 0xFFFFFFFF;
	TMR2->CTRL = (1 << 0); // Запуск

	extern int *g_pfnVectors; //там, где-то в стартап файле есть такой символ
	//Надо показать в этом регистре, где лежит таблица прерываний.
	//А лежит она там, куда записал её линкер, в зависимости от файла компоновки.
	//Поэтому берем адрес от массива g_pfnVectors и кладем туда
#if defined (__CMCPPARM__)
	SCB->VTOR = (uint32_t) (&__Vectors);
#elif defined (__GNUC__)
	extern int *g_pfnVectors;
	SCB->VTOR = (uint32_t) (&g_pfnVectors);
#endif

	/*
	У микроконтроллера К1921ВК028 производителем заложено 4 бита из 8-ми битного поля PRI_n [7:0] для настройки приоритетов прерываний и
	задается это в стандартном армовском макросе __NVIC_PRIO_BITS. Получается, что младшие биты [3:0] не используются и для настройки
	предназначены только биты [7:4]. В зависимосоти от другого параметра PRIGROUP мы можем сказать как использовать эти 4 бита, сколько бит из 4-х
	отвести под группы, а сколько под подгруппы, т.е. как бы ставя разделяющую точку, где часть справа от точки кодирует подгруппу, а левая - группу.
	Если PRIGROUP = 0, то поле PRI_n интерпритируется как 0bxxxxxxxx, где x - биты задания уровня приоритета групп. Если PRIGROUP = 3, то поле PRI_n
	интерпритируется как 0bxxxx.yyyy, где x - биты задания уровня приоритета групп, y - биты задания уровня приоритета подгрупп. И т.д.
	Выходит, что задание PRIGROUP от 0 до 3 будет иметь один и тот же результат, отсавляя во всех этих случаях 4 бита под группу и 0 под подгруппу
	(не забываем, что у нас используются только 4 крайних слева бита поля PRI_n, т.е. биты [7:4]), когда как PRIGROUP от 4 до 7 уже будет иметь влияние
	на соотношения между максимальным возможным количеством групп и подгрупп.
	*/
	NVIC_SetPriorityGrouping(3); // 4 бита под группу, 0 под подгруппу. После этого мы можем передавать аргумент priority в функцию NVIC_SetPriority от 0 до 15 для задания уровня приоритета прерывания. 0 - наивысший, 15 - самый низкий приоритет.

	NVIC_DisableIRQ(TMR0_IRQn);
	NVIC_DisableIRQ(TMR1_IRQn);
	NVIC_DisableIRQ(ECAP0_IRQn);
	NVIC_DisableIRQ(ECAP1_IRQn);
	NVIC_DisableIRQ(ECAP2_IRQn);
	NVIC_DisableIRQ(PWM0_TZ_IRQn);
	NVIC_DisableIRQ(QEP0_IRQn);

	NVIC_ClearPendingIRQ(TMR0_IRQn);
	NVIC_ClearPendingIRQ(TMR1_IRQn);
	NVIC_ClearPendingIRQ(ECAP0_IRQn);
	NVIC_ClearPendingIRQ(ECAP1_IRQn);
	NVIC_ClearPendingIRQ(ECAP2_IRQn);
	NVIC_ClearPendingIRQ(PWM0_TZ_IRQn);
	NVIC_ClearPendingIRQ(QEP0_IRQn);

	/* Прерывание 10 кГц */
	NVIC_EnableIRQ(TMR0_IRQn);
	NVIC_SetPriority(TMR0_IRQn, IRQ_PRIORITY_10K);

	/* Прерывание 1 кГц */
	NVIC_EnableIRQ(TMR1_IRQn);
	NVIC_SetPriority(TMR1_IRQn, IRQ_PRIORITY_1K);

	NVIC_EnableIRQ(ECAP0_IRQn); //CAP0
	NVIC_SetPriority(ECAP0_IRQn, IRQ_PRIORITY_CAP);

	NVIC_EnableIRQ(ECAP1_IRQn); //CAP1
	NVIC_SetPriority(ECAP1_IRQn, IRQ_PRIORITY_CAP);

	NVIC_EnableIRQ(ECAP2_IRQn); //CAP2
	NVIC_SetPriority(ECAP2_IRQn, IRQ_PRIORITY_CAP);

	NVIC_EnableIRQ(PWM0_TZ_IRQn); //PDP (в инверторе тексас нету такого пина)
	NVIC_SetPriority(PWM0_TZ_IRQn, IRQ_PRIORITY_TZ);

	NVIC_EnableIRQ(QEP0_IRQn); //QEP
	NVIC_SetPriority(QEP0_IRQn, IRQ_PRIORITY_EQEP);

	sm_sys.state = SYS_READY;

	gpioPeripheralInit();
#ifdef WATCHDOG_ON
	WatchDog.init(WATCHDOG_PERIOD);	//если сторожевой таймер используется, инициализируем
#endif //WATCHDOG_ON
}


//!Быстрый расчет (обычно 10кГц).

//!Вызов быстрых расчетов модулей системы управления
//! \memberof TSM_Sys
void SM_Sys_Fast_Calc(TSM_Sys *p) {
	sm_net.fast_calc(&sm_net);//расчет коммуникационных драйверов
	adc.fast_calc(&adc);//расчет АЦП
	if (drv_params.sens_type == POS_SENSOR_TYPE_ENCODER) //В типе датчика выбран энкодер
		posspeedEqep.calc(&posspeedEqep); 	//ДПР энкодер
	if (drv_params.sens_type == POS_SENSOR_TYPE_HALL){ //В типе датчика выбран ДПР Холла
		DPReCAP.AngleCalc(&DPReCAP); 		//ДПР Холл, интерполяция угла положения (результат в DPReCAP.Angle)
		DPReCAP.Angle6Calc(&DPReCAP); 		//ДПР Холл, получение угла с точнгстью 60 градусов (результат в DPReCAP.Angle6)
		DPReCAP.SpeedCalc(&DPReCAP); 		//ДПР Холл, расчет скорости вращения (DPReCAP.speed)
		DPReCAP.calc_10k(&DPReCAP); 		//ДПР Холл, служебные функции
	}
	if (drv_params.sens_type == POS_SENSOR_TYPE_SSI){ //Датчик с интерфейсом SSI. Перед употреблением читайте заголовочный файл!
		SSI_Encoder.calc(&SSI_Encoder);//Датчик положения SSI
	}

	dlog.update(&dlog); //Осциллографирование данных
	sm_prot.fast_calc(&sm_prot); //Защиты
	sm_ctrl.fast_calc(&sm_ctrl); //Главный дискретный автомат системы управления
	udControl.calc(&udControl);//Плавная зарядка ЗПТ через термисторы

#if defined (HW_MCB3_SIMULATOR)
	//Передача текущих скважностей таймеров ШИМ в модель
	model.cmpr0 = PWM0->CMPA_bit.CMPA;
	model.cmpr1 = PWM1->CMPA_bit.CMPA;
	model.cmpr2 = PWM2->CMPA_bit.CMPA;
	model.InvertorEna=pwm.Enabled;//Флаг разрешения работы инвертора
	model.Execute(&model);
#endif

	global_time.calc(&global_time);

	cur_par.calc(&cur_par); //Расчет текущих показателей привода
	drv_params.sens_type = drv_params.sens_type & 7; //Отсекаем верхнюю часть переменной, там мусор

	ADC->SEQSYNC_bit.GSYNC = 1; // Запуск АЦП

#ifdef WATCHDOG_ON
	WatchDog.calc();//если сторожевой таймер используется, сбрасываем его здесь
#endif //WATCHDOG_ON
}

//!Миллисекундный расчет 1кГц.

//!Вызов расчетов модулей системы управления, требующих миллисекундной дискретизации
//! \memberof TSM_Sys
void SM_Sys_ms_Calc(TSM_Sys* p) {
	sm_cmd_logic.ms_calc(&sm_cmd_logic); //Обработка команд управления
	sm_net.ms_calc(&sm_net); //обертка для вызова коммуникационных драйверов
	adc.ms_calc(&adc); //АЦП
	sm_prot.ms_calc(&sm_prot); //Защиты
	AutoOffset.ms_calc(&AutoOffset); //авто смещение некоторых каналов АЦП
	//блочная передача драйвера CANopen. Через неё, в частности, грузятся осциллограммы dlog
	Can1BTInterface.ms_calc(&Can1BTInterface, TMR2->VALUE, &co1_vars);
	Can2BTInterface.ms_calc(&Can2BTInterface, TMR2->VALUE, &co2_vars);
	leds.msCalc(&leds);//светодиоды
	RTCclock.msCalc(&RTCclock);//часы
	UserMem.ms_calc(&UserMem);//пользовательская память в МК
	if ((drv_params.sens_type == 2) || (drv_params.sens_type == 3)){ //В типе датчика выбран ДПР Холла
		DPReCAP.ms_calc(&DPReCAP);
	}
	global_time.ms_calc(&global_time);
	dio.ms_calc(&dio); //дискретные входы/выходы
}

//!Медленный расчет (фоновый).

//!Вызов медленных расчетов остальных модулей
//! \memberof TSM_Sys
void SM_Sys_Slow_Calc(TSM_Sys *p) {
	Can1BTInterface.slow_calc(&Can1BTInterface);//интерфейс блочной передачи CANopen, медленный расчет
	Can2BTInterface.slow_calc(&Can2BTInterface);//интерфейс блочной передачи CANopen, медленный расчет
	UserMem.slow_calc(&UserMem);//пользовательская память в МК
	RTCclock.slowCalc(&RTCclock);//часы реального времени
	sm_prot.slow_calc(&sm_prot);//модуль защит
	sm_net.slow_calc(&sm_net); //обертка для вызова коммуникационных драйверов
	dlog.background_analizer(&dlog); //фоновый обработчик модуля осциллографирования
	global_time.slow_calc(&global_time);
	rmp.slow_calc(&rmp); //пересчет интенсивности разгона из пользовтельской во внутреннее представление
	pwm.slow_calc(&pwm); //фоновый обработчик модуля ШИМ (пересчет пользовательских заданий)
	adc.slow_calc(&adc); //Фоновый обработчик АЦП
	cur_par.slow_calc(&cur_par); //Расчет текущих показателей привода
	AutoOffset.slow_calc(&AutoOffset);
	posspeedEqep.slow_calc(&posspeedEqep);//инициализация модуля энкодера
	RotorObserver.slow_calc(&RotorObserver);//наблюдатель потока ротора АД
	dio.slow_calc(&dio); //дискретные входы/выходы
	FanControl.slow_calc(&FanControl);//вентилятор


	//Пересчет коэффициентов для масштабирования токов и напряжений
	drv_params._1_Udc_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.Udc_nom));
	drv_params._1_I_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.I_nom));
	drv_params._1_U_nom = _IQdiv(_IQ16(1), _IQ16(drv_params.U_nom));

	if (sw.Reboot & 1) { //команда перезагрузки
		sw.Reboot = 0; //сбрасываем её
		if (sm_ctrl.state == CTRL_STOP) { //перезагружаемся только в останове
			//выполняем сброс проца
			//Перезагружает во флеш!
			Watchdog.resetCPU();
		}
	}

	//вызов расчета смещения АЦП для токов фаз
	//Делаем расчет только в останове и отсутствии аварии
	if ((sw.AutoOffset & 1) && (sm_ctrl.state == CTRL_STOP))
	    AutoOffset.Enabled=1;
	else
		AutoOffset.Enabled=0;

}
/*@}*/

