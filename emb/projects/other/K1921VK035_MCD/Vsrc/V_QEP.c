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
 
 \file      V_QEP.c
 \brief     Модуль оценки скорости и положения при помощи eQEP (см. TposspeedEqep)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_QEP
 @{*/

#include "DSP.h"
#include "V_IQmath.h"
#include "V_QEP.h"
#include "math.h"
#include "stdlib.h"
#include "main.h"

#define FIRST_LAUNCH_UP		1//!< первый пуск при переходе с низкой скорости на более высокую
#define NOT_FIRST_LAUNCH	0//!< не первый пуск
#define SCALE_IQ_K 10
#define LOWEST_UPSS 0


//Как рассчитывать скорость -
//Таймеров QEP между метками аппаратно
#define SPEED_CALC_TYPE_BY_QEP 0
//Программно по производной угла
#define SPEED_CALC_TYPE_BY_SOFT 1


//! Инициализация

//! \memberof TposspeedEqep
void TposspeedEqep_init(TposspeedEqep *p) {

	QEP->QCAPCTL_bit.UPPS = LOWEST_UPSS;
	QEP->QCAPCTL_bit.CCPS = 4;
	QEP->QDECCTL_bit.QSRC = 0;			//Вкл. режим квадратурного счёта
	QEP->QEPCTL_bit.FREESOFT = 0;		//Режим отладчика
	QEP->QPOSINIT = 0;					//Значение счётчика положения после инициализации или положительного переполнения
	QEP->QEPCTL_bit.SWI = 1;			//Сброс счётчика
	QEP->QPOSMAX = (p->resol << 2) - 1;	//Максимальное значение счётчика, после чего обнуление
	if (p->Posspeed_CTL.bit.dir == 1) {	//Проверка направления движения
		QEP->QDECCTL_bit.QAP = 1;
	}

	QEP->QEPCTL_bit.QPEN = 1;	//Вкл. квадратурного счётчика
	QEP->QCLR = 0xFFFF;	//Отчистка всех флагов
	QEP->QEPCTL_bit.QCLM = 0;	//Режим захвата - по умолчанию, по событию отработки заданного числа импульсов

	if (p->Posspeed_CTL.bit.index_en == 1) {	//если индексная метка есть
		QEP->QEPCTL_bit.PCRM = 0;
		QEP->QEINT_bit.IEL = 1;
	} else {
		QEP->QEPCTL_bit.PCRM = 1;		//Режим обнуления счётчика - по максимальному значению
	}
	QEP->QWDPRD = 200000 / (1 << 2);	//Ввод периода сторожевого таймера
	QEP->QEPCTL_bit.WDE = 1;	//Вкл. сторожевого таймера

	/*Расчёт вспомогательного коэффициента для расчёта скорости,
	 где 15=60/4, 60 - для перевода в об/мин; 4 - для получения интерполяции разрешения датчика (1 период дает 4 фронта);
	 SystemCoreClock - частота процессора*/
	p->k_low = SystemCoreClock / ((float) p->resol * p->speed_nom) * 15.0;
	//В iq формате уменьшаем число в 1<<(24-SCALE_IQ_K),  где 24 - дробная часть iq, а SCALE_IQ_K - то, насколько сдвигается величина
	//с которой speedK дальше участвует в формуле
	p->speedK = _IQ(p->k_low / (1 << (24 - 10)));

	p->resol_inv = 1.0 / ((float) p->resol);

	p->Index_eventCounter = 0;

    //Инициализация портов ввода вывода
	GPIOB->ALTFUNCSET = (1 << 11) + (1 << 12) + (1 << 13);
	SIU->REMAPAF_bit.QEPEN = 1;
}

//! Функция расчёта скорости и положения, вызывается с необходимой дискретностью

//! \memberof TposspeedEqep
void TposspeedEqep_Calc(TposspeedEqep *p) {
    long temp;
	//Текущее значение GPIO для отладки. Можно смотреть в осцах
	p->GPIOsValue = (GPIOB->DATA >> 12) & 3;

	//если скорость высокая, а делитель  UPEVNT не высокий
	if ((labs(p->speed_elec) > _IQ(2)) && (QEP->QCAPCTL_bit.UPPS != 5)) {
		QEP->QCAPCTL_bit.UPPS = 5;    //делаем делитель UPEVNT высокий
		p->skip_counter = 2;    //два такта пропустим расчет скорости
	}

	//если скорость низкая, а делитель не низкий
	if ((labs(p->speed_elec) < _IQ(1.5)) && (QEP->QCAPCTL_bit.UPPS != LOWEST_UPSS)) {
		QEP->QCAPCTL_bit.UPPS = LOWEST_UPSS;    //делаем делитель UPEVNT низкий
		p->skip_counter = 2;    //два такта пропустим расчет скорости
	}

	p->UPPS_forWatch = QEP->QCAPCTL_bit.UPPS;  //для отображения UPPS наружу

	if (p->Posspeed_CTL.bit.CmdInit == 1) { //Команда переинициализации - все обнуляем
		QEP->QEPCTL_bit.SWI = 1;
		p->Posspeed_FLG1.bit.first_theta = 1;
		p->Posspeed_FLG2.bit.pos_ident = 0;
		p->Posspeed_CTL.bit.CmdInit = 0;
		p->theta_elec = 0;
		p->Poscnt_res = 0;
	}
	p->Poscnt_resPrev=p->Poscnt_res;
	p->Poscnt_res = (unsigned long) QEP->QPOSCNT;    //захват положения


	p->Poscnt_res16=p->Poscnt_res;//Для наблюдения на осциллографе
	p->Posspeed_FLG1.bit.PCO_tmp = QEP->QFLG_bit.PCO; //копия флага положительного переполнения счётчика
	p->Posspeed_FLG1.bit.PCU_tmp = QEP->QFLG_bit.PCU; //копия флага отрицательного переполнения счётчика
	QEP->QCLR_bit.PCO = 1; //отчистка флага положительного переполнения счётчика
	QEP->QCLR_bit.PCU = 1; //отчистка флага отрицательного переполнения счётчика

	//перевод угла в метках на обороте в механический угол
	//Здесь расчет во float - желательно переделать в IQ
	p->theta_mech = _IQ((float )p->Poscnt_res * p->resol_inv * 0.25); //расчёт механического угла
	p->theta_mech &= 0x00FFFFFF;


    // Подсчёт количества полных оборотов. Через PCO и PCU получается как-то глючно
    if (p->prevThetaMech - p->theta_mech > _IQ(0.5))
		p->RevolutionCounter++;
	if (p->prevThetaMech - p->theta_mech < _IQ(-0.5))
		p->RevolutionCounter--;
	p->prevThetaMech=p->theta_mech;

	//угол в метках без обнуления на обороте, абсолютный
	p->Poscnt_resContinouosLong=p->Poscnt_res+((QEP->QPOSMAX+1)*p->RevolutionCounter);
	p->Poscnt_resContinouosInt=p->Poscnt_resContinouosLong;//чтобы было уднобно смотреть в 16ти разрядном осциллографе
	p->Poscnt_resContinouosInt8=p->Poscnt_resContinouosLong&0xF;//чтобы видеть метки в крупном масштабе


	//перевод угла в метках абсолютных (не обнуляемых наобороте) в механический угол
	//на 127 оборотах всё переполнится, но для демо сгодится
	p->theta_mechContinouos = _IQ((float )p->Poscnt_resContinouosLong * p->resol_inv * 0.25); //расчёт механического угла
	p->theta_elecContinouos = p->theta_mechContinouos*p->pole_pairs+ p->AngleOffset;//электрический угол абсолютный (не обнуляемый)

	//Расчёт электрического положения обнулемого по достижению 360 градусов
	p->theta_el_tmp = p->theta_mech*p->pole_pairs + p->AngleOffset;
	p->theta_elec = p->theta_el_tmp & 0x00FFFFFF;

	//рассчитывать скорость аппаратно, засекая время между метками средствами QEP
	if (p->SpeedCalcType==SPEED_CALC_TYPE_BY_QEP){

		/*Проверка на срабатывание сторожевого таймера - не пришло не единого импульса*/
		if (QEP->QFLG_bit.WTO == 1) {
			p->Posspeed_FLG1.bit.first_launch = FIRST_LAUNCH_UP; //указатель первого запуска алгоритма после срабатывания таймера
			p->speed_elec = 0;    //обнуление скорости
			QEP->QCLR_bit.WTO = 1;    //отчистка флага
			QEP->QWDTMR = 0;    //обнуление таймера
		} else {
			/*переключение по первому запуску для инициализации*/
			if (p->Posspeed_FLG1.bit.first_launch == FIRST_LAUNCH_UP) {
				//Откл. блока захвата
				QEP->QCAPCTL_bit.CEN = 0;
				QEP->QCAPCTL_bit.CEN = 1;
				p->Posspeed_FLG1.bit.first_launch = NOT_FIRST_LAUNCH;
			}

			p->QEPSTS=QEP->QEPSTS;//копия регистра статуса

			if (p->QEPSTS_bit.UPEVNT == 1) { //есть событие UPEVNT, значит в таймере захвачено время
				p->Qcprdlat_tmp = QEP->QCPRD;    //копия счетчика времени
				p->speed_calc_skip = 0;   //пропуск расчета скорости - не пропускать

				if (p->QEPSTS_bit.COEF == 1) { //проверка флага переполнения таймера
					p->speed_elec = 0;
					p->speed_calc_skip = 1;      //пропустить расчет скорости
					QEP->QEPSTS = 1 << 3;
				}

				if (p->QEPSTS_bit.CDEF == 1) { //проверка на изменения направления движения во время захвата
					p->speed_elec = 0;
					p->speed_calc_skip = 1;      //пропустить расчет скорости
					QEP->QEPSTS = 1 << 2;
				}

				if (p->Qcprdlat_tmp<7){//ложный фронт
					p->speed_calc_skip = 1;      //пропустить расчет скорости
				}

				if (p->QEPSTS_bit.QDF!=p->DirPrev){//сменилось направление движения
					p->speed_elec = 0;
					p->speed_calc_skip = 1; //пропустить расчет скорости
				}
				p->DirPrev=p->QEPSTS_bit.QDF;

				if (p->skip_counter != 0) { //Сменился UPPS
					p->skip_counter--;
					p->speed_calc_skip = 1; //пропустить расчет скорости
				}


				if (p->Qcprdlat_tmp > ((1<<(32-SCALE_IQ_K-1)))) { //Счетчик 32 разряда, а драйвер предназначен для меньшего числа, определяемого SCALE_IQ_K
					p->speed_elec = 0;
					p->speed_calc_skip = 1; //пропустить расчет скорости
				}

				if (!p->speed_calc_skip) { //если расчет скорости пропускать не надо
					if (p->QEPSTS_bit.QDF == 1) //в зависимости от направления движения
						p->speed_tmpIQ = _IQdiv(p->speedK, p->Qcprdlat_tmp << SCALE_IQ_K); //коэффициет скорости делется на 16ти разрядное время, подвинутое вверх на 15
					else
						p->speed_tmpIQ = -_IQdiv(p->speedK, p->Qcprdlat_tmp << SCALE_IQ_K);

					//На сколько нужно подвинуть результат в зависимости от
					//делителей на UPEVNT и тактировании счетчика времени
					p->MoveK = QEP->QCAPCTL_bit.UPPS
							- QEP->QCAPCTL_bit.CCPS;

					if (p->MoveK >= 0) //надо подвинуть вверх
						p->speed_tmpIQ = p->speed_tmpIQ << p->MoveK;
					else
						//вниз
						p->speed_tmpIQ = p->speed_tmpIQ >> -p->MoveK;
					p->speed_elec = p->speed_tmpIQ; //готовая скорость в формате 8.24
				}

				QEP->QEPSTS = 1 << 7;
			}
			else if (QEP->QCTMR > QEP->QCPRD)
			{ //нет события UPEVNT, считаем по таймеру QCTMR, а не по периоду QCPRD
				p->Qcprdlat_tmp = QEP->QCTMR;    //копия счетчика

				if (p->QEPSTS_bit.COEF == 1) { //проверка флага переполнения таймера
					p->speed_elec = 0;
					p->speed_calc_skip = 1;      //пропустить расчет скорости
				}

				if (p->QEPSTS_bit.CDEF == 1) { //проверка на изменения направления движения во время захвата
					p->speed_elec = 0;
					p->speed_calc_skip = 1;      //пропустить расчет скорости
				}
				if (p->Qcprdlat_tmp<7){//ложный фронт
					p->speed_calc_skip = 1;      //пропустить расчет скорости
				}

				if (p->Qcprdlat_tmp > ((1<<(32-SCALE_IQ_K-1)))) { //Счетчик 32 разряда, а драйвер предназначен для меньшего числа, определяемого SCALE_IQ_K
					p->speed_elec = 0;
					p->speed_calc_skip = 1; //пропустить расчет скорости
				}

				if (!p->speed_calc_skip) { //если расчет скорости пропускать не надо
					if (p->QEPSTS_bit.QDF == 1) //в зависимости от направления движения
						p->speed_tmpIQ = _IQdiv(p->speedK, p->Qcprdlat_tmp << SCALE_IQ_K); //коэффициет скорости делется на 16ти разрядное время, подвинутое вверх на 15
					else
						p->speed_tmpIQ = -_IQdiv(p->speedK, p->Qcprdlat_tmp << SCALE_IQ_K);

					//На сколько нужно подвинуть результат в зависимости от
					//делителей на UPEVNT и тактировании счетчика времени
					p->MoveK = QEP->QCAPCTL_bit.UPPS
							- QEP->QCAPCTL_bit.CCPS;

					if (p->MoveK >= 0) //надо подвинуть вверх
						p->speed_tmpIQ = p->speed_tmpIQ << p->MoveK;
					else
						//вниз
						p->speed_tmpIQ = p->speed_tmpIQ >> -p->MoveK;
					p->speed_elec = p->speed_tmpIQ; //готовая скорость в формате 8.24
				}
			}
		}

	}

	//рассчитывать скорость программно через производную угла
	if (p->SpeedCalcType==SPEED_CALC_TYPE_BY_SOFT){
		//Сначала легкий фильтр на сам угол
		//0.5 и маски - это магия нечувствительности фильтра к разнице углов больше 360
		//Чтобы при обнулении угла при переходе через 360 градусов при
		//вычитании из 5 градусов 355 получилось 10 (в IQ формате)
		p->theta_finish=p->theta_finish+_IQmpy(_IQ(0.5),((p->theta_elec-p->theta_finish+_IQ(0.5))&0x00FFFFFF)-_IQ(0.5));
		p->theta_finish&=0x00FFFFFF;
		//расчитываем приращение угла
		temp = (p->theta_finish << 8) - (p->theta_start << 8);
		p->d_fi = (temp >> 8);
		p->theta_start = p->theta_finish;

		//скорость нефильтрованная, рассчитанная из производной угла за один период
		p->speed_elec_temp=_IQmpy(p->d_fi,p->KThetaToSpeed)<<3;

		//инерционный фильтр для скорости
		p->speed_filter.input = p->speed_elec_temp;
		p->speed_filter.calc(&p->speed_filter);
		p->speed_elec=p->speed_filter.output;
	}
}

//! Функция обработки репера (событие индекса)

//! \memberof TposspeedEqep
void TposspeedEqep_IndexEvent(TposspeedEqep *p) {
	p->Posspeed_FLG2.bit.pos_ident = 1;
	p->Index_eventCounter++;
}

//! \memberof TposspeedEqep
void TposspeedEqep_SlowCalc(TposspeedEqep *p) {
	//коэффициент перевода производной от угла (вычисляемую неизвестно в чем) в скорость
	//сдвиг на 3 чтобы результат деления не переполнил 127, потом при использовании коэфа
	//сдвинется назад на 3
	p->KThetaToSpeed=_IQdiv(_IQ(1.0),_IQmpyI32(drv_params.freq_nom,FAST_CALC_TS)<<3);
}
/*@}*/

