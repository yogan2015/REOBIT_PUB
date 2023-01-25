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
 
 \file      V_PWM_Module.c
 \brief     Модуль реализации векторной ШИМ (см. TPWM_Module)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \addtogroup V_PWM_Module 
 @{*/


#include "V_IQmath.h"
#include "V_PWM_Module.h"
#include "main.h"

//! Инициализация

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *p) {
	SIU->PWMSYNC_bit.PRESCRST = 0; //синхронизация таймеров - сброс внутренних счетчиков

	// Настройка периода
	if (p->Frequency < PWM_FREQ_MIN)
		p->Frequency = PWM_FREQ_MIN;
	if (p->Frequency > PWM_FREQ_MAX)
		p->Frequency = PWM_FREQ_MAX;
	PWM0->TBPRD = _IQ10div(_IQ10(SystemCoreClock/1000.0), p->Frequency << 1) >> 10; //период

	p->k_pwm = PWM0->TBPRD;
	p->FreqPrev = p->Frequency;                 //предыдущая частота

// ------------------------------------------------------------------------
	// Настраиваем модуль ePWM0
	// ------------------------------------------------------------------------
	PWM0->TBPHS_bit.TBPHS = 0x0000;            // Phase is 0
	PWM0->TBCTR = 0x0000;                       // Clear counter

	// Настройка счётчика. в комментарии расписано по полям, но для ускорения всё грузится за один раз
	//PWM0->TBCTL_bit.PRDLD = TB_SHADOW;        	// Загрузка TBPRD при TBCTR = 0
	//PWM0->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  	// Счёт вверх-вниз
	//PWM0->TBCTL_bit.PHSEN = TB_DISABLE;         	// Не синхронизировать этот таймер ни с чем
	//PWM0->TBCTL_bit.HSPCLKDIV = 0;     			// Первый делитель частоты (нет деления)
	//PWM0->TBCTL_bit.CLKDIV = 0;                 	// Второй делитель частоты (нет деления)
	//PWM0->TBCTL_bit.SYNCOSEL = TB_CTR_ZERO; 		// Выдаём синхро-сигнал при TBCTR = 0
	//PWM0->TBCTL_bit.FREESOFT = 2; 				// Продолжать счёт при дебажном останове процессора
	//PWM0->TBCTL_bit.SHADOWGLOB = 1; 				// Разрешить нормальную работу теневых регистров

	PWM0->TBCTL = (TB_SHADOW << PWM_TBCTL_PRDLD_Pos) |
				  (TB_COUNT_UPDOWN << PWM_TBCTL_CTRMODE_Pos) |
				  (TB_DISABLE << PWM_TBCTL_PHSEN_Pos) |
				  (0 << PWM_TBCTL_HSPCLKDIV_Pos) |
				  (0 << PWM_TBCTL_CLKDIV_Pos) |
				  (TB_CTR_ZERO << PWM_TBCTL_SYNCOSEL_Pos) |
				  (2 << PWM_TBCTL_FREESOFT_Pos) |
				  (1 << PWM_TBCTL_SHDWGLOB_Pos);

	// Настройка теневых загрузок регистров
	//PWM0->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   	// Использовать теневой регистр для CMPA
	//PWM0->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   	// Загружать в активный из теневого по нулю счётчика
	//PWM0->CMPCTL_bit.SHDWBMODE = CC_SHADOW;  		// Использовать теневой регистр для CMPB
	//PWM0->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   	// Загружать в активный из теневого по нулю счётчика
	PWM0->CMPCTL = (CC_SHADOW << PWM_CMPCTL_SHDWAMODE_Pos) |
				   (CC_CTR_ZERO << PWM_CMPCTL_LOADAMODE_Pos) |
				   (CC_SHADOW << PWM_CMPCTL_SHDWBMODE_Pos) |
				   (CC_CTR_ZERO << PWM_CMPCTL_LOADBMODE_Pos);

	// Обнуление уставки сравнения
	PWM0->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Настройка действий при сравнении счётчика с уставками
	//PWM0->AQCTLA_bit.ZRO = AQ_CLEAR; //обнуляем при нуле счетчика
	//PWM0->AQCTLA_bit.CAU = AQ_SET; //включаем при сравнении и инкрементиовании
	//PWM0->AQCTLA_bit.CAD = AQ_CLEAR; //обнуляем при сравнении и декрементровании
	PWM0->AQCTLA = (AQ_CLEAR << PWM_AQCTLA_ZRO_Pos) |
				   (AQ_SET << PWM_AQCTLA_CAU_Pos) |
				   (AQ_CLEAR << PWM_AQCTLA_CAD_Pos);

	//Для PWMB настройка не нужна, так как он при помощи блока мёртвого времени будет инверсией от канала A

	PWM0->AQSFRC_bit.RLDCSF = 0; //по ТО надо писать 0

	// Настройка блока мёртвого времени
	// DBRED = DBFED = 150 * Tм_мкс / 4
	PWM0->DBRED = _IQ4mpy(_IQ4(150 / 4), p->DeadBand >> 20) >> 4;
	PWM0->DBFED = PWM0->DBRED;

	// Настройка модуля мёртвого времени:
	// INMODE: S5=0 S4=0 - сигнал с задержанным передним фронтом и сигнал с задержанным задним фронтом
	// 		   формируются из сигнала PWMA
	// POLSEL: S3 = 1 S2 = 1 - сигнал с задержанным передним фронтом идёт как есть, а сигнал
	//		   с задержанным задним фронтом инвертируется
	// OUTMODE:S0 = 1 S1 = 1 на канал PWMA выходит исходный сигнал PWMA, но с задержанным передним фронтом
	//		   На канал PWMB выходит сигнал PWMA с задержанным задним фронтом да ещё и с инверсией
	//PWM0->DBCTL_bit.INMODE = DBA_ALL;
	//PWM0->DBCTL_bit.POLSEL = DB_ACTV_HIC;
	//PWM0->DBCTL_bit.OUTMODE = DB_FULL_ENABLE;
	PWM0->DBCTL = (DBA_ALL << PWM_DBCTL_INMODE_Pos) |
				  (DB_ACTV_HIC << PWM_DBCTL_POLSEL_Pos) |
				  (DB_FULL_ENABLE << PWM_DBCTL_OUTMODE_Pos);

	// Настройка Trip-Zone
	//PWM0->TZCTL_bit.TZA = TZ_STATE;   	// по событию "One-Shot Trip" переводим
	//PWM0->TZCTL_bit.TZB = TZ_STATE;     // ШИМ выходы в нужное состояние (третье)
	PWM0->TZCTL = (TZ_STATE << PWM_TZCTL_TZA_Pos) |
				  (TZ_STATE << PWM_TZCTL_TZB_Pos);

	// ------------------------------------------------------------------------
	// Настраиваем модуль ePWM1
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM1->TBPRD = PWM0->TBPRD;              		//период такой же
	PWM1->TBPHS_bit.TBPHS = 0x0001;            		// Фаза равна 1 из-за задержки в один такт на синхронизацию
	PWM1->TBCTR = 0x0000;                       	// Clear counter

	// Настройка счётчика
	//PWM1->TBCTL_bit.PRDLD = TB_SHADOW;        	// Загрузка TBPRD при TBCTR = 0
	//PWM1->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  	// Счёт вверх-вниз
	//PWM1->TBCTL_bit.PHSEN = TB_ENABLE;        	// Разрешить синхронизацию
	//PWM1->TBCTL_bit.PHSDIR = TB_UP;      			// Считать вверх после загрузки фазы
	//PWM1->TBCTL_bit.HSPCLKDIV = 0;     			// Первый делитель частоты (нет деления)
	//PWM1->TBCTL_bit.CLKDIV = 0;           		// Второй делитель частоты (нет деления)
	//PWM1->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; 		// Пропускаем синхро-сигнал "насквозь"
	//PWM1->TBCTL_bit.FREESOFT = 2; 				// Продолжать счёт при дебажном останове процессора
	//PWM1->TBCTL_bit.SHADOWGLOB = 1; 				// Разрешить нормальную работу теневых регистров
	PWM1->TBCTL = (TB_SHADOW << PWM_TBCTL_PRDLD_Pos) |
				  (TB_COUNT_UPDOWN << PWM_TBCTL_CTRMODE_Pos) |
				  (TB_ENABLE << PWM_TBCTL_PHSEN_Pos) |
				  (TB_UP << PWM_TBCTL_PHSDIR_Pos) |
				  (0 << PWM_TBCTL_HSPCLKDIV_Pos) |
				  (0 << PWM_TBCTL_CLKDIV_Pos) |
				  (TB_SYNC_IN << PWM_TBCTL_SYNCOSEL_Pos) |
	  	  	  	  (2 << PWM_TBCTL_FREESOFT_Pos) |
	  	  	  	  (1 << PWM_TBCTL_SHDWGLOB_Pos);

	// Теневые регистры, изменения выходных сигналов, мёртвое время
	// TZ и прерывания настраиваются так же, как у PWM0
	PWM1->CMPCTL = PWM0->CMPCTL;
	PWM1->AQCTLA = PWM0->AQCTLA;
	PWM1->DBRED = PWM0->DBRED;
	PWM1->DBFED = PWM0->DBFED;
	PWM1->DBCTL = PWM0->DBCTL;
	PWM1->TZCTL = PWM0->TZCTL;
	PWM1->ETSEL = PWM0->ETSEL;

	// Обнуление уставок
	PWM1->CMPA_bit.CMPA = 0;
	PWM1->AQSFRC_bit.RLDCSF = 0;

	// ------------------------------------------------------------------------
	// Настраиваем модуль ePWM2
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM2->TBPRD = PWM0->TBPRD;
	PWM2->TBPHS_bit.TBPHS = 0x0001;            // Фаза равна 1 из-за задержки в один такт на синхронизацию
	PWM2->TBCTR = 0x0000;                       // Clear counter

	// Настройка счётчика такая же, как у PWM1
	//PWM2->TBCTL_bit.PRDLD = TB_SHADOW;        		// загрузка TBPRD при TBCTR = 0
	//PWM2->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  	// Count up-down
	//PWM2->TBCTL_bit.PHSEN = TB_ENABLE;         		// Enable phase loading
	//PWM2->TBCTL_bit.PHSDIR = TB_UP;      			// Считать вверх после загрузки фазы
	//PWM2->TBCTL_bit.HSPCLKDIV = 0;     				// High Speed Time-base Clock Prescale
	//PWM2->TBCTL_bit.CLKDIV = 0;          			// Time-base Clock Prescale
	//PWM2->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; 			// разрешаем выдачу синхро-сигнала
	//PWM2->TBCTL_bit.FREESOFT = 2; 				// Продолжать счёт при дебажном останове процессора
	//PWM2->TBCTL_bit.SHADOWGLOB = 1; 				// Разрешить нормальную работу теневых регистров
	PWM2->TBCTL = PWM1->TBCTL;

	// Теневые регистры, изменения выходных сигналов, мёртвое время
	// TZ и прерывания настраиваются так же, как у PWM0 и PWM1
	PWM2->CMPCTL = PWM0->CMPCTL;
	PWM2->AQCTLA = PWM0->AQCTLA;
	PWM2->DBRED = PWM0->DBRED;
	PWM2->DBFED = PWM0->DBFED;
	PWM2->DBCTL = PWM0->DBCTL;
	PWM2->TZCTL = PWM0->TZCTL;
	PWM2->ETSEL = PWM0->ETSEL;

	// Обнуление уставок
	PWM2->CMPA_bit.CMPA = 0;
	PWM2->AQSFRC_bit.RLDCSF = 0;


	// Отключаем ключи
	PWM0->TZFRC_bit.OST = 1;
	PWM1->TZFRC_bit.OST = 1;
	PWM2->TZFRC_bit.OST = 1;

	//ШИМ 6 выводов
	GPIOA->ALTFUNCSET = (1 << 8) + (1 << 9) + (1 << 10) + (1 << 11) + (1 << 12) + (1 << 13);

	//Синхронный запуск ШИМ
	SIU->PWMSYNC_bit.PRESCRST= 0b111;

}



//! Нормирование входных величин.

//!Учитывает компенсацию напряжения при изменении Ud,
//!выполняет вписывание вектора в окружность, если требуется, и
//!выполняет смену базиса, относительно которого идет нормировка.
//! \memberof TPWM_Module
void PWM_Module_NormInput(TPWM_Module* p) {
    _iq knorm;

    p->UalphaNorm=p->UalphaRef;
    p->UbetaNorm=p->UbetaRef;

    //находим амплитуду (без учета ограничения)
    p->U_mag=_IQmag(p->UalphaNorm,p->UbetaNorm);


    p->UdCorTmp=_IQdiv(_IQ(1.0),(_IQ(1.0)+_IQmpy((adc.Udc_meas-_IQ(1.0)),p->UdCompK)));
    //учет пульсаций напряжения на Ud
    if (p->UdCompEnable&1) { //он включен?
        p->UalphaNorm=_IQmpy(p->UalphaNorm, p->UdCorTmp);//изменим пропорционально коэфф-ту коррекции
        p->UbetaNorm=_IQmpy(p->UbetaNorm, p->UdCorTmp);//и это тоже
    }

    //вписывание заданной амплитуды напряжения в окружность, вписываемую в шестиугольник базывых векторов
    //когда U_lim=1.0, это и есть такая окружность. Бывает, что мы хотим вписывать в шестиугольник. Тогда просто задираем вверх огрианичение U_lim
    if (p->U_lim>_IQ(1.0/0.866)) //но нет смысла задирать выше максимально-реализ. напряжения (больше базового вектора)
        p->U_lim=_IQ(1.0/0.866);
    /* рассчитываем амплитуду вектора, который хотим отработать*/
    knorm=_IQmag(p->UalphaNorm,p->UbetaNorm);//плюс нормируем от 540 к 311
    if (knorm>=p->U_lim) { //он больше, чем наше ограничение?
        knorm=_IQdiv(p->U_lim,knorm);//в эту же переменную, для экономии, рассчитываем нормировку
        p->UalphaNorm=_IQmpy(knorm,p->UalphaNorm);//уменьшаем пропорционально нормировке
        p->UbetaNorm=_IQmpy(knorm,p->UbetaNorm);//и это
        p->ULimitation=1;//флаг о том, что идет ограничение напряжения
    } else
        p->ULimitation=0;

    /* рассчитываем приведенные вектора*/
    /* До этого момента напряжение нормировалось относительно
    базиса фазного амплитудного значения, например, 220*sqrt(2)
    Теперь производится переход, где за единицу принимается максимально
    реализуемое напряжение (длина базового вектора)
    */
    p->UalphaNorm=_IQmpy(p->UalphaNorm,_IQ(0.866));
    p->UbetaNorm=_IQmpy(p->UbetaNorm,_IQ(0.866));
}



//! Функция 6ти секторной векторной ШИМ

//! \memberof TPWM_Module
void PWM_Module_No_SV_Update(TPWM_Module *p) {
    _iq lambda1;
    _iq lambda2;
    _iq lambda3;

    int16 gamma;
    int16 gamma1;
    long tmp_pwm;

    //Присвоение трех уставок сравнения только если счетчик таймера далек от нуля, чтобы
    //предотвратить частичное применение скважностей, что в векторной ШИМ может быть критично и испортить период ШИМ.
    DINT;
    if (PWM0->TBCTR>30) {
        PWM0->CMPA_bit.CMPA=(Uint16)p->GammaA;
        PWM1->CMPA_bit.CMPA=(Uint16)p->GammaB;
        PWM2->CMPA_bit.CMPA=(Uint16)p->GammaC;
    }
    EINT;

    PWM_Module_NormInput(p);

    //Расчет скважностей по методу Изосимова.
    //Подробнее см. диссертацию Чуева П.В. http://motorcontrol.ru/wp-content/uploads/2015/11/Chuev_vector_control.pdf
    tmp_pwm = _IQmpy(_1_SQRT3,p->UbetaNorm);  /*делим на корень из 3*/
    lambda1 = _IQmpy(p->k_pwm,(p->UalphaNorm - tmp_pwm));
    lambda2 = _IQmpy(p->k_pwm,2*tmp_pwm);
    lambda3 = _IQmpy(p->k_pwm,p->UalphaNorm + tmp_pwm);


    if (lambda1<=0)
        if (lambda3>0) {
            gamma=lambda3;
            gamma1=-lambda1;
            p->sector=1; /*110 начало */
            p->GammaA=p->k_pwm-gamma;
            p->GammaB=p->k_pwm-(gamma+gamma1+1);
            p->GammaC=p->k_pwm-0;

        } else if (lambda2>0) {
            gamma=lambda2;
            gamma1=-lambda3;
            p->sector=2; /*011 начало */
            p->GammaA=p->k_pwm-0;
            p->GammaB=p->k_pwm-(gamma+gamma1+1);
            p->GammaC=p->k_pwm-gamma1;
            /*011 начало */
        } else if (lambda1!=0) {
            gamma=-lambda1;
            gamma1=-lambda2;
            p->sector=3; /*011 начало */
            p->GammaA=p->k_pwm-0;
            p->GammaB=p->k_pwm-gamma;
            p->GammaC=p->k_pwm-(gamma+gamma1+1);
            /*011 начало */
        } else {
            gamma=-lambda3;
            gamma1 = lambda1;
            p->sector= 4; /*101 начало */
            p->GammaA=p->k_pwm-gamma1;
            p->GammaB=p->k_pwm-0;
            p->GammaC=p->k_pwm-(gamma+gamma1+1);
            /*101 начало */

        }
    else if (lambda2>0) {
        gamma=lambda1;
        gamma1=lambda2;
        p->sector= 0; /*110 начало */
        p->GammaA=p->k_pwm-(gamma+gamma1+1);
        p->GammaB=p->k_pwm-gamma1;
        p->GammaC=p->k_pwm-0;
        /*110 начало */
    } else if (lambda3<0) {
        gamma=-lambda3;
        gamma1 = lambda1;
        p->sector= 4; /*101 начало */
        p->GammaA=p->k_pwm-gamma1;
        p->GammaB=p->k_pwm-0;
        p->GammaC=p->k_pwm-(gamma+gamma1+1);
        /*101 начало */
    } else {
        gamma=-lambda2;
        gamma1=lambda3;
        p->sector=5; /*101 начало */
        p->GammaA=p->k_pwm-(gamma+gamma1+1);
        p->GammaB=p->k_pwm-0;
        p->GammaC=p->k_pwm-gamma;
        /*101 начало */
    }


    /*насыщения */

    if (p->GammaA<0) p->GammaA=0;
    if (p->GammaB<0) p->GammaB=0;
    if (p->GammaC<0) p->GammaC=0;

    if (p->GammaA>p->k_pwm) p->GammaA=p->k_pwm+1;
    if (p->GammaB>p->k_pwm) p->GammaB=p->k_pwm+1;
    if (p->GammaC>p->k_pwm) p->GammaC=p->k_pwm+1;

    //Присвоение трех уставок сравнения только если счетчик таймера далек от нуля, чтобы
    //предотвратить частичное применение скважностей, что в векторной ШИМ может быть критично и испортить период ШИМ.
    //Второй раз - чтобы предотвратить ситуацию с постоянной "незагрузкой" при равенстве частот расчета и ШИМ
    DINT;
    if (PWM0->TBCTR>30) {
        PWM0->CMPA_bit.CMPA=(Uint16)p->GammaB;
        PWM1->CMPA_bit.CMPA=(Uint16)p->GammaC;
        PWM2->CMPA_bit.CMPA=(Uint16)p->GammaA;
    }
    EINT;
}

//! Функция синусоидальной ШИМ

//! \memberof TPWM_Module
void PWM_Module_Sin_Update(TPWM_Module *p) {
	_iq PhasePtsA;
	_iq PhasePtsB;
	_iq PhasePtsC;
	_iq knorm;


	p->UalphaNorm = p->UalphaRef;
	p->UbetaNorm = p->UbetaRef;

	//находим амплитуду (без учета ограничения)
	p->U_mag = _IQmag(p->UalphaNorm, p->UbetaNorm);

	/* рассчитываем амплитуду вектора, который хотим отработать*/
	knorm = _IQmag(p->UalphaNorm, p->UbetaNorm);
	if (knorm >= p->U_lim) { //он больше, чем наше ограничение?
		knorm = _IQdiv(p->U_lim, knorm); //в эту же переменную, для экономии, рассчитываем нормировку
		p->UalphaNorm = _IQmpy(knorm, p->UalphaNorm); //уменьшаем пропорционально нормировке
		p->UbetaNorm = _IQmpy(knorm, p->UbetaNorm); //и это
		p->ULimitation = 1; //флаг о том, что идет ограничение напряжения
	} else
		p->ULimitation = 0;

	//Нормирование входного напряжения. Так как синусоидальная ШИМ формирует на 0.866 меньшее напряжение,
	//чем векторная ШИМ (270В амплитудного фазного напряжения вместо 311В), то для того, чтобы при том же задании в переменных
	//p->UalphaNorm, p->UbetaNorm получилось то же самое напряжение на выходе, что и в векторной ШИМ, нужно задания увеличить в 1/0.866 раз.
	//Деление на два нужно для последующих формул, чтобы переменые менялись в половинном от максимального диапазоне.
	p->UalphaNorm = _IQmpy(p->UalphaNorm, _IQ(1/0.866/2));
	p->UbetaNorm = _IQmpy(p->UbetaNorm, _IQ(1/0.866/2));

	/*фазное преобразование из системы альфа, бетта в a,b,c */

	PhasePtsA = _IQ(0.5) - (p->UalphaNorm);
	PhasePtsB = _IQ(0.5) - (_IQmpy(p->UbetaNorm,_IQ(0.8660254)) - (p->UalphaNorm >> 1));
	PhasePtsC = _IQ(0.5) - (-_IQmpy(p->UbetaNorm, _IQ(0.8660254)) - (p->UalphaNorm >> 1));

	p->GammaA = _IQmpy(p->k_pwm, PhasePtsA);
	p->GammaB = _IQmpy(p->k_pwm, PhasePtsB);
	p->GammaC = _IQmpy(p->k_pwm, PhasePtsC);

	/*насыщения */

	if (p->GammaA < 0)
		p->GammaA = 0;
	if (p->GammaB < 0)
		p->GammaB = 0;
	if (p->GammaC < 0)
		p->GammaC = 0;

	if (p->GammaA > p->k_pwm)
		p->GammaA = p->k_pwm + 1;
	if (p->GammaB > p->k_pwm)
		p->GammaB = p->k_pwm + 1;
	if (p->GammaC > p->k_pwm)
		p->GammaC = p->k_pwm + 1;


	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaC;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaA;

}

//! Функция ШИМ с раздельными фазами (для модели SRM)

//! \memberof TPWM_Module
void PWM_Module_Separate_Update(TPWM_Module *p) {
	// Закомментировано для экономии места
/*	_iq PhasePtsA;
	_iq PhasePtsB;
	_iq PhasePtsC;
	_iq knorm;

	p->UPhARef = _IQmpy(p->UPhARef, _IQ(0.5));
	p->UPhBRef = _IQmpy(p->UPhBRef, _IQ(0.5));
	p->UPhCRef = _IQmpy(p->UPhCRef, _IQ(0.5));

	PhasePtsA = _IQ(0.5) - p->UPhARef;
	PhasePtsB = _IQ(0.5) - p->UPhBRef;
	PhasePtsC = _IQ(0.5) - p->UPhCRef;

	p->GammaA = _IQmpy(p->k_pwm, PhasePtsA);
	p->GammaB = _IQmpy(p->k_pwm, PhasePtsB);
	p->GammaC = _IQmpy(p->k_pwm, PhasePtsC);

	//насыщения

	if (p->GammaA < 0)
		p->GammaA = 0;
	if (p->GammaB < 0)
		p->GammaB = 0;
	if (p->GammaC < 0)
		p->GammaC = 0;

	if  (p->GammaA > p->k_pwm)
		p->GammaA = p->k_pwm + 1;
	if (p->GammaB > p->k_pwm)
		p->GammaB = p->k_pwm + 1;
	if (p->GammaC > p->k_pwm)
		p->GammaC = p->k_pwm + 1;

	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaC;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaA;
*/
}

//! Функция ШИМ для начальной зарядки будстрепных конденсаторов инвертора

//! \memberof TPWM_Module
void PWM_Module_ChargingMode(TPWM_Module *p) {
	p->GammaA = p->k_pwm;
	p->GammaB = p->k_pwm;
	p->GammaC = p->k_pwm;

	DINT;
	if (PWM0->TBCTR > 30) {
		PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
		PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
		PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;
	}
	EINT;
}

//! Общая функция-обертка для расчета ШИМ

//Вызывающает ту версию ШИМ (ту функцию), что выбрана в настройках.

//! \memberof TPWM_Module
void PWM_Module_Update(TPWM_Module *p) {

	if (p->ChargingMode)
		PWM_Module_ChargingMode(p);
	else {
		switch (p->PWM_type) {
		case PWM_TYPE_6SECT_NO_SV: {
			PWM_Module_No_SV_Update(p);
			break;
		}
		case PWM_TYPE_SIN_PWM: {
			PWM_Module_Sin_Update(p);
			break;
		}
		default: {
			// Защита от неправильных типов ШИМ
			p->PWM_type = PWM_TYPE_6SECT_NO_SV;
			PWM_Module_No_SV_Update(p);
			break;
		}
		}
	}

}

//! Медленный расчет

//! Пересчитываются введенные пользователем величины
//! Величина мертвого времени, частота ШИМ и т.п.

//! \memberof TPWM_Module
void PWM_Module_SlowCalc(TPWM_Module *p) {
	Uint16 tmp;
	//проверка ограничений величины мертвого времени
	if (p->DeadBand < DEAD_BAND_MIN)
		p->DeadBand = DEAD_BAND_MIN;
	if (p->DeadBand > DEAD_BAND_MAX)
		p->DeadBand = DEAD_BAND_MAX;
	//пересчет МВ из формата IQ в мкс в такты таймера на 100мГц
	PWM0->DBRED = _IQ4mpy(_IQ4(100), p->DeadBand >> 20) >> 4;
	//во все ключи то же самое
	PWM0->DBFED = PWM0->DBRED;

	PWM1->DBFED = PWM0->DBRED;
	PWM1->DBRED = PWM0->DBRED;
	PWM2->DBFED = PWM0->DBRED;
	PWM2->DBRED = PWM0->DBRED;

	if (p->MinGammaLimit < DEAD_BAND_MIN)
		p->MinGammaLimit = GAMMA_LIMIT_MIN;
	if (p->MinGammaLimit > DEAD_BAND_MAX)
		p->MinGammaLimit = GAMMA_LIMIT_MAX;
	PWM0->FWDTH = _IQ4mpy(_IQ4(100), p->MinGammaLimit >> 20) >> 4;
	PWM1->FWDTH = PWM0->FWDTH;
	PWM2->FWDTH = PWM0->FWDTH;
	//частота ШИМ. Смена "на лету".
	if (p->FreqPrev != p->Frequency) { //сменили частоту
		DINT; //запрещение прерываний
		//проверка максимума/минимума
		if (p->Frequency < PWM_FREQ_MIN)
			p->Frequency = PWM_FREQ_MIN;
		if (p->Frequency > PWM_FREQ_MAX)
			p->Frequency = PWM_FREQ_MAX;
		//изменяем период
		p->k_pwm = _IQ10div(_IQ10(SystemCoreClock/1000.0), p->Frequency << 1) >> 10; //период
		PWM0->TBPRD = p->k_pwm;
		//для всех стоек то же самое
		PWM1->TBPRD = p->k_pwm;
		PWM2->TBPRD = p->k_pwm;



		p->FreqPrev = p->Frequency; //предыдущая частота
		EINT;
	}
}

//! Функция включения ШИМ (включение инвертора)

//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *p) {
	p->Enabled = 1;	//флаг "включено"

	// Снимаем принудительную установку выходов
	PWM0->TZCLR_bit.OST = 1;
	PWM1->TZCLR_bit.OST = 1;
	PWM2->TZCLR_bit.OST = 1;
}

//! Функция выключения ШИМ (выключение инвертора)

//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *p) {

	p->Enabled = 0;	//флаг "выключено"
	// Принудительно обнулим все ножки
	PWM0->TZFRC_bit.OST = 1;
	PWM1->TZFRC_bit.OST = 1;
	PWM2->TZFRC_bit.OST = 1;
}

/*@}*/
