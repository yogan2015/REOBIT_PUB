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


#define GPIO_INV_ON
#define GPIO_INV_OFF



//! Инициализация

//! \memberof TPWM_Module
void PWM_Module_Init(TPWM_Module *p) {
	SIU->PWMSYNC_bit.PRESCRST = 0; //синхронизация таймеров - сброс внутренних счетчиков

// ------------------------------------------------------------------------
	// Настраиваем модуль ePWM1
	// ------------------------------------------------------------------------
	if (p->Frequency < PWM_FREQ_MIN)
		p->Frequency = PWM_FREQ_MIN;
	if (p->Frequency > PWM_FREQ_MAX)
		p->Frequency = PWM_FREQ_MAX;
	PWM0->TBPRD = _IQ10div(_IQ10(APB0BusClock/1000.0), p->Frequency << 1) >> 10; //период

	p->k_pwm = PWM0->TBPRD;
	p->FreqPrev = p->Frequency;                 //предыдущая частота
	PWM0->TBPHS_bit.TBPHS = 0x0000;            // Phase is 0
	PWM0->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	PWM0->TBCTL_bit.PRDLD = TB_SHADOW;        // загрузка TBPRD при TBCTR = 0
	PWM0->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	PWM0->TBCTL_bit.PHSEN = TB_DISABLE;         // Disable phase loading
	PWM0->TBCTL_bit.PHSDIR = TB_UP;      // Считать вверх после загрузки фазы
	PWM0->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	PWM0->TBCTL_bit.CLKDIV = 0;                 // Time-base Clock Prescale
	PWM0->TBCTL_bit.SYNCOSEL = TB_CTR_ZERO; // выдаём синхро-сигнал при TBCTR = 0

	// Setup shadowing
	PWM0->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   //включить SHADOW для сравнения
	PWM0->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   // Load on zero

	PWM0->CMPCTL_bit.SHDWBMODE = CC_SHADOW;   //включить SHADOW для сравнения
	PWM0->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   // Load on zero

	// Set Compare values
	PWM0->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Set actions
	PWM0->AQCTLA = AQ_EPWM_DISABLE; // для начала события для PWM1A запрещены
	PWM0->AQCTLA_bit.ZRO = 1; //обнуляем при нуле счетчика
	PWM0->AQCTLA_bit.CAU = 2; //включаем при сравнении и инкрементиовании
	PWM0->AQCTLA_bit.CAD = 1; //обнуляем при сравнении и декрементровании

	//Для PWMB тоже самое, что для PWMА. Без инверсии. Инверсия далее в модуле МВ
	PWM0->AQCTLB = PWM0->AQCTLA; // для начала события для PWM1B запрещены
	PWM0->AQCTLB_bit.ZRO = PWM0->AQCTLA_bit.ZRO; //обнуляем при нуле счетчика
	PWM0->AQCTLB_bit.CAU = PWM0->AQCTLA_bit.CAU; //включаем при сравнении и инкрементиовании
	PWM0->AQCTLB_bit.CAD = PWM0->AQCTLA_bit.CAD; //обнуляем при сравнении и декрементровании

	PWM0->AQSFRC_bit.RLDCSF = 0; //по ТО надо писать 0

	// Setup Deadband
	// DBRED = DBFED = 150 * Tм_мкс / 4
	PWM0->DBRED = _IQ4mpy(_IQ4(150 / 4), p->DeadBand >> 20) >> 4;
	PWM0->DBFED = PWM0->DBRED;
	PWM0->DBCTL_bit.INMODE = DBA_RED_DBB_FED;    //s4=0, s5=1 на картинке DT
	PWM0->DBCTL_bit.OUTMODE = DB_FULL_ENABLE;    //S1=1, S2=2 на картинке DT
	PWM0->DBCTL_bit.POLSEL = DB_ACTV_HIC;       // PWM1B = !PWM1A; S2=0, S3=1

	PWM0->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT (шимовское)
	PWM0->ETSEL_bit.INTEN = 0;                  // Disable INT


	//разрешаем TZ быть источником аппаратной аварии (one-shot)
	//   PWM0->TZSEL_bit.OSHT1 = TZ_ENABLE;
//    PWM0->TZSEL_bit.OSHT2 = TZ_ENABLE;
//    PWM0->TZSEL_bit.OSHT3 = TZ_ENABLE;

	// Trip-Zone
	PWM0->TZCTL_bit.TZA = TZ_STATE;   // по событию "One-Shot Trip" переводим
	PWM0->TZCTL_bit.TZB = TZ_STATE;          // ШИМ выходы в нужное состояние

	//Для VectorCARD от ШИМа запускается ADC
	//PWM0->ETSEL_bit.SOCAEN = 1;		// Разрешить запуск ацп
	//PWM0->ETSEL_bit.SOCASEL = 1;		// Запускать при CTR == 0 (Underflow)

	// ------------------------------------------------------------------------
	// Настраиваем модуль ePWM2
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM1->TBPRD = PWM0->TBPRD;              //период такой же
	PWM1->TBPHS_bit.TBPHS = 0x0001;            // Фаза равна 1 из-за задержки в один такт на синхронизацию
	PWM1->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	PWM1->TBCTL_bit.PRDLD = TB_SHADOW;        // загрузка TBPRD при TBCTR = 0
	PWM1->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	PWM1->TBCTL_bit.PHSEN = TB_ENABLE;         // Enable phase loading
	PWM1->TBCTL_bit.PHSDIR = TB_UP;      // Считать вверх после загрузки фазы
	PWM1->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	PWM1->TBCTL_bit.CLKDIV = 0;           // Time-base Clock Prescale
	PWM1->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; // пропускаем синхро-сигнал "насквозь"

	// Setup shadowing
	PWM1->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   //включить SHADOW для сравнения
	PWM1->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   // Load on zero

	PWM1->CMPCTL_bit.SHDWBMODE = CC_SHADOW;   //включить SHADOW для сравнения
	PWM1->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   // Load on zero

	// Set Compare values
	PWM1->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Set actions
	PWM1->AQCTLA = AQ_EPWM_DISABLE; // для начала события запрещены
	PWM1->AQCTLA_bit.ZRO = 1; //обнуляем при нуле счетчика
	PWM1->AQCTLA_bit.CAU = 2; //включаем при сравнении и инкрементиовании
	PWM1->AQCTLA_bit.CAD = 1; //обнуляем при сравнении и декрементровании

	//Для PWMB тоже самое, что для PWMА. Без инверсии. Инверсия далее в модуле МВ
	PWM1->AQCTLB = PWM0->AQCTLA; // для начала события для PWM1B запрещены
	PWM1->AQCTLB_bit.ZRO = PWM0->AQCTLA_bit.ZRO; //обнуляем при нуле счетчика
	PWM1->AQCTLB_bit.CAU = PWM0->AQCTLA_bit.CAU; //включаем при сравнении и инкрементиовании
	PWM1->AQCTLB_bit.CAD = PWM0->AQCTLA_bit.CAD; //обнуляем при сравнении и декрементровании

	PWM1->AQSFRC_bit.RLDCSF = 0; //по ТО надо писать 0

	// Active high complementary PWMs - Setup Deadband
	PWM1->DBRED = PWM0->DBRED;
	PWM1->DBFED = PWM1->DBRED;
	PWM1->DBCTL_bit.INMODE = PWM0->DBCTL_bit.INMODE;
	PWM1->DBCTL_bit.OUTMODE = PWM0->DBCTL_bit.OUTMODE;
	PWM1->DBCTL_bit.POLSEL = PWM0->DBCTL_bit.POLSEL;

	// Interrupt where we will change the Compare Values
	PWM1->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT
	PWM1->ETSEL_bit.INTEN = 0;                  // Disable INT

	//разрешаем TZ быть источником аппаратной аварии (one-shot)
	//   PWM1->TZSEL_bit.OSHT1 = TZ_ENABLE;
	//   PWM1->TZSEL_bit.OSHT2 = TZ_ENABLE;
	//   PWM1->TZSEL_bit.OSHT3 = TZ_ENABLE;

	// Trip-Zone
	PWM1->TZCTL_bit.TZA = TZ_STATE;   // по событию "One-Shot Trip" переводим
	PWM1->TZCTL_bit.TZB = TZ_STATE;          // ШИМ выходы в нужное состояние

	// ------------------------------------------------------------------------
	// Настраиваем модуль ePWM3
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM2->TBPRD = PWM0->TBPRD;
	PWM2->TBPHS_bit.TBPHS = 0x0001;            // Фаза равна 1 из-за задержки в один такт на синхронизацию
	PWM2->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	PWM2->TBCTL_bit.PRDLD = TB_SHADOW;        // загрузка TBPRD при TBCTR = 0
	PWM2->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	PWM2->TBCTL_bit.PHSEN = TB_ENABLE;         // Enable phase loading
	PWM2->TBCTL_bit.PHSDIR = TB_UP;      // Считать вверх после загрузки фазы
	PWM2->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	PWM2->TBCTL_bit.CLKDIV = 0;           // Time-base Clock Prescale
	PWM2->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; // разрешаем выдачу синхро-сигнала

	// Setup shadowing
	PWM2->CMPCTL_bit.SHDWAMODE = CC_SHADOW;   //включить SHADOW для сравнения
	PWM2->CMPCTL_bit.LOADAMODE = CC_CTR_ZERO;   // Load on zero

	PWM2->CMPCTL_bit.SHDWBMODE = CC_SHADOW;   //включить SHADOW для сравнения
	PWM2->CMPCTL_bit.LOADBMODE = CC_CTR_ZERO;   // Load on zero

	// Set Compare values
	PWM2->CMPA_bit.CMPA = 0;                   // Set compare A value

	// Set actions
	PWM2->AQCTLA = AQ_EPWM_DISABLE; // для начала события запрещены
	PWM2->AQCTLA_bit.ZRO = 1; //обнуляем при нуле счетчика
	PWM2->AQCTLA_bit.CAU = 2; //включаем при сравнении и инкрементиовании
	PWM2->AQCTLA_bit.CAD = 1; //обнуляем при сравнении и декрементровании

	//Для PWMB тоже самое, что для PWMА. Без инверсии. Инверсия далее в модуле МВ
	PWM2->AQCTLB = PWM0->AQCTLA; // для начала события для PWM1B запрещены
	PWM2->AQCTLB_bit.ZRO = PWM0->AQCTLA_bit.ZRO; //обнуляем при нуле счетчика
	PWM2->AQCTLB_bit.CAU = PWM0->AQCTLA_bit.CAU; //включаем при сравнении и инкрементиовании
	PWM2->AQCTLB_bit.CAD = PWM0->AQCTLA_bit.CAD; //обнуляем при сравнении и декрементровании

	PWM2->AQSFRC_bit.RLDCSF = 0; //по ТО надо писать 0

	// Active high complementary PWMs - Setup Deadband
	PWM2->DBRED = PWM0->DBRED;
	PWM2->DBFED = PWM2->DBRED;
	PWM2->DBCTL_bit.INMODE = PWM0->DBCTL_bit.INMODE;
	PWM2->DBCTL_bit.OUTMODE = PWM0->DBCTL_bit.OUTMODE;
	PWM2->DBCTL_bit.POLSEL = PWM0->DBCTL_bit.POLSEL;

	// Interrupt where we will change the Compare Values
	PWM2->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT
	PWM2->ETSEL_bit.INTEN = 0;                  // Disable INT

	//разрешаем TZ быть источником аппаратной аварии (one-shot)
	//  PWM2->TZSEL_bit.OSHT1 = TZ_ENABLE;
	//  PWM2->TZSEL_bit.OSHT2 = TZ_ENABLE;
	//  PWM2->TZSEL_bit.OSHT3 = TZ_ENABLE;


	// Trip-Zone
	PWM2->TZCTL_bit.TZA = TZ_STATE;   // по событию "One-Shot Trip" переводим
	PWM2->TZCTL_bit.TZB = TZ_STATE;          // ШИМ выходы в нужное состояние

	// ------------------------------------------------------------------------
	// Настраиваем модуль ePWM3 под АЦП
	// ------------------------------------------------------------------------
	// Setup TBCLK
	PWM3->TBPRD = PWM0->TBPRD;
	PWM3->TBPHS_bit.TBPHS = 0x0001;      // Фаза равна 1 из-за задержки в один такт на синхронизацию
	PWM3->TBCTR = 0x0000;                       // Clear counter

	// Setup counter mode
	PWM3->TBCTL_bit.PRDLD = TB_SHADOW;        // загрузка TBPRD при TBCTR = 0
	PWM3->TBCTL_bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up-down
	PWM3->TBCTL_bit.PHSEN = TB_ENABLE;         // Enable phase loading
	PWM3->TBCTL_bit.PHSDIR = TB_UP;      // Считать вверх после загрузки фазы
	PWM3->TBCTL_bit.HSPCLKDIV = 0;     // High Speed Time-base Clock Prescale
	PWM3->TBCTL_bit.CLKDIV = 0;           // Time-base Clock Prescale
	PWM3->TBCTL_bit.SYNCOSEL = TB_SYNC_IN; // разрешаем выдачу синхро-сигнала

	// Interrupt where we will change the Compare Values
	PWM3->ETSEL_bit.INTSEL = ET_DISABLE;        // Disable INT
	PWM3->ETSEL_bit.INTEN = 0;                  // Disable INT


	PWM3->ETSEL_bit.SOCAEN = 1;		// Разрешить запуск ацп
	PWM3->ETSEL_bit.SOCASEL = 1;		// Запускать при CTR == 0 (Underflow)

	//сбрасываем все флаги аварий
	PWM0->TZCLR = 0x7;
	PWM1->TZCLR = 0x7;
	PWM2->TZCLR = 0x7;

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
        PWM0->CMPA_bit.CMPA=(Uint16)p->GammaA;
        PWM1->CMPA_bit.CMPA=(Uint16)p->GammaB;
        PWM2->CMPA_bit.CMPA=(Uint16)p->GammaC;
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


	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;

}

//! Функция ШИМ с раздельными фазами (для модели SRM)

//! \memberof TPWM_Module
void PWM_Module_Separate_Update(TPWM_Module *p) {
	_iq PhasePtsA;
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

	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;

}

void PWM_Module_DC_Update(TPWM_Module *p)
{
	int32 UalphaRef = 0, UbetaRef = 0;
	int32 gamma1_DC = 0, gamma2_DC = 0;
	int32 temp32;

	UalphaRef = p->UalphaRef;
	UbetaRef = p->UbetaRef;

	if (UalphaRef > _IQ(1))
		UalphaRef = _IQ(1);
	else if (UalphaRef < _IQ(-1))
		UalphaRef = _IQ(-1);

	if (UbetaRef > _IQ(1))
		UbetaRef = _IQ(1);
	else if (UbetaRef < _IQ(0))
		UbetaRef = _IQ(0);

	//данное преобразование даёт возможность отрабатывать напряжения в диапазоне -1 - 0 - +1 (в относительных единицах)
	//Напряжение 1 - скважность (1/2 + 0.5) = 1, Напряжение 0 - скважность 0,5 и т.д.
	gamma1_DC = -(UalphaRef >> 1) + _IQ(0.5); // (IQ), Приводим заданное напряжение к соответствующей скважности.

	//На низких частотах величина p->k_pwm большая, значит большой может быть и temp32.
	//по-этому для расчётов целесообразно использовать формат iq16.
	gamma1_DC = gamma1_DC >> 8; // (IQ16) переводим то, что выше, в iq16.
	temp32 = _IQ16mpy(gamma1_DC, _IQ16(p->k_pwm)); // (IQ16) переводим скважность в величину для загрузки в регистр сравнения.
	p->GammaA = temp32 >> 16; // (IQ0) Загружем целую часть в регистр сравнения.
	p->GammaB = p->k_pwm - p->GammaA; // в регистре сравнения EPwm2 то же, что и в EPwm1.

	//На низких частотах величина p->k_pwm большая, значит большой может быть и temp32.
	//по-этому для расчётов целесообразно использовать формат iq16.
	gamma2_DC = UbetaRef >> 8; // (IQ16) переводим то, что выше, в iq16.
	temp32 = _IQ16mpy(gamma2_DC, _IQ16(p->k_pwm)); // (IQ16) переводим скважность в величину для загрузки в регистр сравнения.
	p->GammaC = p->k_pwm - (temp32 >> 16); // (IQ0) Загружем целую часть в регистр сравнения.

	PWM0->CMPA_bit.CMPA = (Uint16) p->GammaA;
	PWM1->CMPA_bit.CMPA = (Uint16) p->GammaB;
	PWM2->CMPA_bit.CMPA = (Uint16) p->GammaC;
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
		case PWM_TYPE_DC_DRIVE: {
			PWM_Module_DC_Update(p);
			break;
		}
		case PWM_TYPE_SRD: {
			PWM_Module_Separate_Update(p);
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
		p->k_pwm = _IQ10div(_IQ10(APB0BusClock/1000.0), p->Frequency << 1) >> 10; //период
		PWM0->TBPRD = p->k_pwm;
		//для всех стоек то же самое
		PWM1->TBPRD = p->k_pwm;
		PWM2->TBPRD = p->k_pwm;
		PWM3->TBPRD = p->k_pwm;        //таймер АЦП

		//посчитаем длину выборки для усреднения токов, исходя из частоты ШИМ
		adc.IASampleLength = (p->Frequency >> 10) / 10;	//Частота ШИМ в формате 22.10, приводим к инту и делим на 10 - частоту расчета системы управления
		if (adc.IASampleLength > 4)	//не более 4 точек
			adc.IASampleLength = 4;
		if (adc.IASampleLength < 1)	//не менее 1 точки
			adc.IASampleLength = 1;
		adc.IBSampleLength = adc.IASampleLength;
		adc.ICSampleLength = adc.IASampleLength;
		adc.UdcSampleLength = adc.IASampleLength;

		p->FreqPrev = p->Frequency; //предыдущая частота
		EINT;
	}

	PWM3->TBPHS_bit.TBPHS = 1;//подбор сдвига для запуска АЦП: 1 - ровно на нуле таймера

}

//! Функция включения ШИМ (включение инвертора)

//! \memberof TPWM_Module
void PWM_Module_On(TPWM_Module *p) {
	p->Enabled = 1;	//флаг "включено"

	// Снимаем принудительную установку выходов
	PWM0->AQCSFRC = 0;
	PWM1->AQCSFRC = 0;
	PWM2->AQCSFRC = 0;
	GPIO_INV_ON;

}

//! Функция выключения ШИМ (выключение инвертора)

//! \memberof TPWM_Module
void PWM_Module_Off(TPWM_Module *p) {

	p->Enabled = 0;	//флаг "выключено"
	// Принудительно обнулим все ножки

	PWM0->AQCSFRC = 9;  // 0x1 - 0 на выходе PWMxA, 0x8 - 1 на выходе PWMxB
	PWM1->AQCSFRC = 9;  // 0x1 - 0 на выходе PWMxA, 0x8 - 1 на выходе PWMxB
	PWM2->AQCSFRC = 9;  // 0x1 - 0 на выходе PWMxA, 0x8 - 1 на выходе PWMxB
	GPIO_INV_OFF;

}

/*@}*/
