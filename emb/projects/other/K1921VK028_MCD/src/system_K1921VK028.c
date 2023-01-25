/*==============================================================================
 * Инициализация К1921ВК028
 *------------------------------------------------------------------------------
 * НИИЭТ, Богдан Колбов <kolbov@niiet.ru>
 *==============================================================================
 * ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО
 * ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ
 * ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И ОТСУТСТВИЯ
 * НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ
 * ПРЕДНАЗНАЧЕНО ДЛЯ ОЗНАКОМИТЕЛЬНЫХ ЦЕЛЕЙ И НАПРАВЛЕНО ТОЛЬКО НА
 * ПРЕДОСТАВЛЕНИЕ ДОПОЛНИТЕЛЬНОЙ ИНФОРМАЦИИ О ПРОДУКТЕ, С ЦЕЛЬЮ СОХРАНИТЬ ВРЕМЯ
 * ПОТРЕБИТЕЛЮ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ
 * ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА ПРЯМОЙ ИЛИ КОСВЕННЫЙ УЩЕРБ, ИЛИ
 * ПО ИНЫМ ТРЕБОВАНИЯМ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ
 * ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.
 *
 *                              2018 АО "НИИЭТ"
 *==============================================================================
 */

//-- Includes ------------------------------------------------------------------
#include "system_K1921VK028.h"
#include "K1921VK028.h"

//-- Variables -----------------------------------------------------------------
uint32_t SystemCoreClock; // System Clock Frequency (Core Clock)
uint32_t APB0BusClock;    // APB0 Bus Clock Frequency
uint32_t APB1BusClock;    // APB1 Bus Clock Frequency
uint32_t programMemType;  // Memory Region That Program Is Written To


//-- Functions -----------------------------------------------------------------
uint16_t SystemCoreClockUpdate(void)
{
    uint32_t current_sysclk;
    uint32_t pll_div1, pll_div2, pll_fbdiv, pll_refdiv, pll_refclk, pll_div = 1;

    current_sysclk = RCU->SYSCLKSTAT_bit.SYSSTAT;

    switch (current_sysclk) {
    case RCU_SYSCLKSTAT_SYSSTAT_REFCLK:
        SystemCoreClock = REFCLK_VAL;
        break;
    case RCU_SYSCLKSTAT_SYSSTAT_SRCCLK:
        SystemCoreClock = SRCCLK_VAL;
        break;
    case RCU_SYSCLKSTAT_SYSSTAT_PLLDIVCLK:
    case RCU_SYSCLKSTAT_SYSSTAT_PLLCLK:
        if (current_sysclk == RCU_SYSCLKSTAT_SYSSTAT_PLLDIVCLK)
            pll_div = RCU->PLLDIV_bit.DIV + 1;
        pll_div1 = RCU->PLLCFG_bit.DIV1;
        pll_div2 = RCU->PLLCFG_bit.DIV2;
        pll_fbdiv = RCU->PLLCFG_bit.FBDIV;
        pll_refdiv = RCU->PLLCFG_bit.REFDIV;
        if (RCU->PLLCFG_bit.REFSRC == RCU_PLLCFG_REFSRC_OSICLK)
            pll_refclk = OSICLK_VAL;
        else if (RCU->PLLCFG_bit.REFSRC == RCU_PLLCFG_REFSRC_OSECLK)
            pll_refclk = OSECLK_VAL;
        else // (RCU->PLLCFG_bit.REFSRC == RCU_PLLCFG_REFSRC_PLLEXTCLK)
            pll_refclk = PLLEXTCLK_VAL;
        SystemCoreClock = (pll_refclk * pll_fbdiv) / (pll_refdiv * pll_div1 * pll_div2 * pll_div);
        break;
    }

    APB0BusClock = SystemCoreClock / (1 << RCU->APBCFG_bit.DIV);
    APB1BusClock = SystemCoreClock;

    // Проверка, что тактирование не сбоит
    if (RCU->SYSCLKSTAT_bit.SYSFAIL == 1) return 1;
    else return 0;
}

void ClkInit()
{
    uint32_t timeout_counter = 0;
    uint32_t sysclk_source;

//clockout control
#ifndef CKO_NONE
    //D0 clockout
    RCU->HCLKCFG_bit.GPIODEN = 1;
    RCU->HRSTCFG_bit.GPIODEN = 1;
    GPIOD->ALTFUNCNUM0_bit.PIN0 = 2;
    GPIOD->ALTFUNCSET_bit.PIN0 = 1;
    GPIOD->DENSET_bit.PIN0 = 1;
#endif

#if defined CKO_REF
    RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_REFCLK << RCU_CLKOUTCFG_CLKSEL_Pos) |
                     (RCU_CLKOUTCFG_CLKEN_Msk); //CKO = REFCLK
#elif defined CKO_SRC
    RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_SRCCLK << RCU_CLKOUTCFG_CLKSEL_Pos) |
                     (RCU_CLKOUTCFG_CLKEN_Msk); //CKO = SRCCLK
#elif defined CKO_SYS
    RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_SYSCLK << RCU_CLKOUTCFG_CLKSEL_Pos) |
                     (3 << RCU_CLKOUTCFG_DIVN_Pos) |
                     (RCU_CLKOUTCFG_DIVEN_Msk) |
                     (RCU_CLKOUTCFG_CLKEN_Msk); //CKO = SYSCLK/8
#elif defined CKO_PLL
    RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_PLLCLK << RCU_CLKOUTCFG_CLKSEL_Pos) |
                     (3 << RCU_CLKOUTCFG_DIVN_Pos) |
                     (RCU_CLKOUTCFG_DIVEN_Msk) |
                     (RCU_CLKOUTCFG_CLKEN_Msk); //CKO = PLLCLK/8
#endif

//wait till oscillator is ready
#if defined OSECLK_VAL && (OSECLK_VAL != 0) && (CPE == 0)
    while ((!RCU->SYSCLKSTAT_bit.SRCCLKOK) && (timeout_counter < SRCCLK_STARTUP_TIMEOUT))
        timeout_counter++;
    if (timeout_counter == SRCCLK_STARTUP_TIMEOUT)
        while (1) {
        };
#endif

//select system clock
#ifdef SYSCLK_PLL
    //PLLCLK = (REFSRC/REFDIV) * (FBDIV/(DIV1*DIV2))
    uint32_t pllcfg_clr = (RCU_PLLCFG_REFSRC_Msk |
                           RCU_PLLCFG_REFDIV_Msk |
                           RCU_PLLCFG_DIV1_Msk |
                           RCU_PLLCFG_DIV2_Msk);
    RCU->PLLCFG_bit.BP = 0;
#if (OSECLK_VAL == 8000000)
    RCU->PLLCFG_bit.FBDIV = 100;
    RCU->PLLCFG_bit.PD = 0;
    RCU->PLLCFG |= (RCU_PLLCFG_REFSRC_OSECLK << RCU_PLLCFG_REFSRC_Pos) |
                   (1 << RCU_PLLCFG_REFDIV_Pos) |
                   (4 << RCU_PLLCFG_DIV1_Pos) |
                   (1 << RCU_PLLCFG_DIV2_Pos);
#elif (OSECLK_VAL == 12000000)
    // SYSCLKOUT = Fclk / REFDIV * FBDIV / (DIV1 * DIV2)
    // SYSCLKOUT = 12 / 3 * 100 / (2 * 1) = 200 МГц
    // При этом Fvco = 400 МГц
    RCU->PLLCFG_bit.FBDIV = 100;	// Множитель входной частоты
    RCU->PLLCFG_bit.PD = 0;			// Энергосбереженеи запрещено
    RCU->PLLCFG = (RCU->PLLCFG & (~pllcfg_clr)) |
                  (RCU_PLLCFG_REFSRC_OSECLK << RCU_PLLCFG_REFSRC_Pos) |
                  (3 << RCU_PLLCFG_REFDIV_Pos) |
                  (2 << RCU_PLLCFG_DIV1_Pos) |
                  (1 << RCU_PLLCFG_DIV2_Pos);
#elif (OSECLK_VAL == 16000000)
    RCU->PLLCFG_bit.FBDIV = 50;
    RCU->PLLCFG_bit.PD = 0;
    RCU->PLLCFG = (RCU->PLLCFG & (~pllcfg_clr)) |
                  (RCU_PLLCFG_REFSRC_OSECLK << RCU_PLLCFG_REFSRC_Pos) |
                  (1 << RCU_PLLCFG_REFDIV_Pos) |
                  (4 << RCU_PLLCFG_DIV1_Pos) |
                  (1 << RCU_PLLCFG_DIV2_Pos);
#elif (OSECLK_VAL == 20000000)
    RCU->PLLCFG_bit.FBDIV = 40;
    RCU->PLLCFG_bit.PD = 0;
    RCU->PLLCFG = (RCU->PLLCFG & (~pllcfg_clr)) |
                  (RCU_PLLCFG_REFSRC_OSECLK << RCU_PLLCFG_REFSRC_Pos) |
                  (1 << RCU_PLLCFG_REFDIV_Pos) |
                  (4 << RCU_PLLCFG_DIV1_Pos) |
                  (1 << RCU_PLLCFG_DIV2_Pos);
#elif (OSECLK_VAL == 24000000)
    RCU->PLLCFG_bit.FBDIV = 50;
    RCU->PLLCFG_bit.PD = 0;
    RCU->PLLCFG = (RCU->PLLCFG & (~pllcfg_clr)) |
                  (RCU_PLLCFG_REFSRC_OSECLK << RCU_PLLCFG_REFSRC_Pos) |
                  (2 << RCU_PLLCFG_REFDIV_Pos) |
                  (3 << RCU_PLLCFG_DIV1_Pos) |
                  (1 << RCU_PLLCFG_DIV2_Pos);
#elif defined EXTCLK_VAL && (EXTCLK_VAL != 0)
    //for example, if EXTCLK = 10000000
    RCU->PLLCFG_bit.FBDIV = 60;
    RCU->PLLCFG_bit.PD = 0;
    RCU->PLLCFG = (RCU->PLLCFG & (~pllcfg_clr)) |
                  (RCU_PLLCFG_REFSRC_EXTCLK << RCU_PLLCFG_REFSRC_Pos) |
                  (2 << RCU_PLLCFG_REFDIV_Pos) |
                  (3 << RCU_PLLCFG_DIV1_Pos) |
                  (1 << RCU_PLLCFG_DIV2_Pos);
#else
#error "Please define OSECLK_VAL or EXTCLK_VAL with correct values!"
#endif
    RCU->PLLCFG_bit.OUTDIS = 0;			// Включение PLL
    while (!RCU->PLLCFG_bit.LOCK) {		// Ожидание, пока он зафиксируется
    };
    // additional waitstates
    MFLASH->CTRL = (7 << MFLASH_CTRL_LAT_Pos);
    BFLASH->CTRL = (7 << BFLASH_CTRL_LAT_Pos);
    //apb0 div by 2
    RCU->APBCFG_bit.DIV = 1;			// Fapb = SYSCLKOUT / (2 ^ DIV) = 100 МГц
    //select PLL as source system clock
    sysclk_source = RCU_SYSCLKCFG_SYSSEL_PLLCLK;
#elif defined SYSCLK_REF
    sysclk_source = RCU_SYSCLKCFG_SYSSEL_REFCLK;
#elif defined SYSCLK_SRC
    sysclk_source = RCU_SYSCLKCFG_SYSSEL_SRCCLK;
#else
#error "Please define SYSCLK source (SYSCLK_PLL | SYSCLK_REF | SYSCLK_SRC)!"
#endif

    //switch sysclk
    RCU->SYSCLKCFG = (sysclk_source << RCU_SYSCLKCFG_SYSSEL_Pos);
    // Wait switching done
    timeout_counter = 0;
    while ((RCU->SYSCLKSTAT_bit.SYSSTAT != RCU->SYSCLKCFG_bit.SYSSEL) && (timeout_counter < SYSCLK_SWITCH_TIMEOUT))
        timeout_counter++;
    if (timeout_counter == SYSCLK_SWITCH_TIMEOUT) //SYSCLK failed to switch
        while (1) {
        };

    //flush and enable cache
    MFLASH->CTRL_bit.IFLUSH = 1;
    while (MFLASH->ICSTAT_bit.BUSY) {
    };
    MFLASH->CTRL_bit.DFLUSH = 1;
    while (MFLASH->DCSTAT_bit.BUSY) {
    };
    MFLASH->CTRL |= (MFLASH_CTRL_DCEN_Msk) | (MFLASH_CTRL_ICEN_Msk);
}

void PeripheralsClockEnable () {
	// Разрешение тактирования
	RCU->PCLKCFG0_bit.ECAP0EN = 1;
	RCU->PCLKCFG0_bit.ECAP1EN = 1;
	RCU->PCLKCFG0_bit.ECAP2EN = 1;
	RCU->PCLKCFG0_bit.ECAP3EN = 1;
	RCU->PCLKCFG0_bit.ECAP4EN = 1;
	RCU->PCLKCFG0_bit.ECAP5EN = 1;
	RCU->PCLKCFG0_bit.ETMR0EN = 1;
	RCU->PCLKCFG0_bit.ETMR1EN = 1;
	RCU->PCLKCFG0_bit.ETMR2EN = 1;
	RCU->PCLKCFG0_bit.ETMR3EN = 1;
	RCU->PCLKCFG0_bit.I2C0EN = 1;
	RCU->PCLKCFG0_bit.I2C1EN = 1;
	RCU->PCLKCFG0_bit.RTCEN = 1;
	RCU->PCLKCFG0_bit.TMR0EN = 1;
	RCU->PCLKCFG0_bit.TMR1EN = 1;
	RCU->PCLKCFG0_bit.TMR2EN = 1;
	RCU->PCLKCFG0_bit.TMR3EN = 1;
	RCU->PCLKCFG0_bit.TUART0EN = 1;
	RCU->PCLKCFG0_bit.TUART1EN = 1;

	RCU->PCLKCFG1_bit.LAUEN = 1;
	RCU->PCLKCFG1_bit.OWI0EN = 1;
	RCU->PCLKCFG1_bit.OWI1EN = 1;
	RCU->PCLKCFG1_bit.PWM0EN = 1;
	RCU->PCLKCFG1_bit.PWM1EN  = 1;
	RCU->PCLKCFG1_bit.PWM2EN  = 1;
	RCU->PCLKCFG1_bit.PWM3EN  = 1;
	RCU->PCLKCFG1_bit.PWM4EN  = 1;
	RCU->PCLKCFG1_bit.PWM5EN  = 1;
	RCU->PCLKCFG1_bit.PWM6EN  = 1;
	RCU->PCLKCFG1_bit.PWM7EN  = 1;
	RCU->PCLKCFG1_bit.PWM8EN  = 1;
	RCU->PCLKCFG1_bit.PWM9EN  = 1;
	RCU->PCLKCFG1_bit.QEP0EN = 1;
	RCU->PCLKCFG1_bit.QEP1EN = 1;
	RCU->PCLKCFG1_bit.QEP2EN = 1;
	RCU->PCLKCFG1_bit.QEP3EN = 1;

	RCU->HCLKCFG_bit.CANEN = 1;
	RCU->HCLKCFG_bit.ETHEN = 1;
	RCU->HCLKCFG_bit.EXTMEMEN = 1;
	RCU->HCLKCFG_bit.GPIOAEN = 1;
	RCU->HCLKCFG_bit.GPIOBEN = 1;
	RCU->HCLKCFG_bit.GPIOCEN = 1;
	RCU->HCLKCFG_bit.GPIODEN = 1;
	RCU->HCLKCFG_bit.GPIOEEN = 1;
	RCU->HCLKCFG_bit.GPIOFEN = 1;
	RCU->HCLKCFG_bit.GPIOGEN = 1;
	RCU->HCLKCFG_bit.GPIOHEN = 1;
	RCU->HCLKCFG_bit.GPIOJEN = 1;
	RCU->HCLKCFG_bit.GPIOKEN = 1;
	RCU->HCLKCFG_bit.GPIOLEN = 1;
	RCU->HCLKCFG_bit.GPIOMEN = 1;
	RCU->HCLKCFG_bit.MILSTD0EN = 1;
	RCU->HCLKCFG_bit.MILSTD1EN = 1;
	RCU->HCLKCFG_bit.SDFMEN = 1;
	RCU->HCLKCFG_bit.SPWR0EN = 1;
	RCU->HCLKCFG_bit.SPWR1EN = 1;

	// Вывод из сброса
	RCU->HRSTCFG_bit.CANEN = 1;
	RCU->HRSTCFG_bit.ETHEN = 1;
	RCU->HRSTCFG_bit.EXTMEMEN = 1;
	RCU->HRSTCFG_bit.GPIOAEN = 1;
	RCU->HRSTCFG_bit.GPIOBEN = 1;
	RCU->HRSTCFG_bit.GPIOCEN = 1;
	RCU->HRSTCFG_bit.GPIODEN = 1;
	RCU->HRSTCFG_bit.GPIOEEN = 1;
	RCU->HRSTCFG_bit.GPIOFEN = 1;
	RCU->HRSTCFG_bit.GPIOGEN = 1;
	RCU->HRSTCFG_bit.GPIOHEN = 1;
	RCU->HRSTCFG_bit.GPIOJEN = 1;
	RCU->HRSTCFG_bit.GPIOKEN = 1;
	RCU->HRSTCFG_bit.GPIOLEN = 1;
	RCU->HRSTCFG_bit.GPIOMEN = 1;
	RCU->HRSTCFG_bit.MILSTD0EN = 1;
	RCU->HRSTCFG_bit.MILSTD1EN = 1;
	RCU->HRSTCFG_bit.SDFMEN = 1;
	RCU->HRSTCFG_bit.SPWR0EN = 1;
	RCU->HRSTCFG_bit.SPWR1EN = 1;

	RCU->PRSTCFG0_bit.ECAP0EN = 1;
	RCU->PRSTCFG0_bit.ECAP1EN = 1;
	RCU->PRSTCFG0_bit.ECAP2EN = 1;
	RCU->PRSTCFG0_bit.ECAP3EN = 1;
	RCU->PRSTCFG0_bit.ECAP4EN = 1;
	RCU->PRSTCFG0_bit.ECAP5EN = 1;
	RCU->PRSTCFG0_bit.ETMR0EN = 1;
	RCU->PRSTCFG0_bit.ETMR1EN = 1;
	RCU->PRSTCFG0_bit.ETMR2EN = 1;
	RCU->PRSTCFG0_bit.ETMR3EN = 1;
	RCU->PRSTCFG0_bit.I2C0EN = 1;
	RCU->PRSTCFG0_bit.I2C1EN = 1;
	RCU->PRSTCFG0_bit.RTCEN = 1;
	RCU->PRSTCFG0_bit.TMR0EN = 1;
	RCU->PRSTCFG0_bit.TMR1EN = 1;
	RCU->PRSTCFG0_bit.TMR2EN = 1;
	RCU->PRSTCFG0_bit.TMR3EN = 1;
	RCU->PRSTCFG0_bit.TUART0EN = 1;
	RCU->PRSTCFG0_bit.TUART1EN = 1;

	RCU->PRSTCFG1_bit.LAUEN = 1;
	RCU->PRSTCFG1_bit.OWI0EN = 1;
	RCU->PRSTCFG1_bit.OWI1EN = 1;
	RCU->PRSTCFG1_bit.OWI1EN = 1;
	RCU->PRSTCFG1_bit.PWM0EN = 1;
	RCU->PRSTCFG1_bit.PWM1EN = 1;
	RCU->PRSTCFG1_bit.PWM2EN = 1;
	RCU->PRSTCFG1_bit.PWM3EN = 1;
	RCU->PRSTCFG1_bit.PWM4EN = 1;
	RCU->PRSTCFG1_bit.PWM5EN = 1;
	RCU->PRSTCFG1_bit.PWM6EN = 1;
	RCU->PRSTCFG1_bit.PWM7EN = 1;
	RCU->PRSTCFG1_bit.PWM8EN = 1;
	RCU->PRSTCFG1_bit.PWM9EN = 1;
	RCU->PRSTCFG1_bit.QEP0EN = 1;
	RCU->PRSTCFG1_bit.QEP1EN = 1;
	RCU->PRSTCFG1_bit.QEP2EN = 1;
	RCU->PRSTCFG1_bit.QEP3EN = 1;

	// Включение АЦП в блоке PMU (управление энергосбережением)
    PMU->ADCPC = PMU_ADCPC_LDOEN0_Msk | PMU_ADCPC_LDOEN1_Msk |
                 PMU_ADCPC_LDOEN2_Msk | PMU_ADCPC_LDOEN3_Msk;
    //ждем готовности LDO в АЦП
    while (!(PMU->ADCPC_bit.LDORDY0 &&
             PMU->ADCPC_bit.LDORDY1 &&
             PMU->ADCPC_bit.LDORDY2 &&
             PMU->ADCPC_bit.LDORDY3)) {
    };


	// Включение тактирования АЦП (выбор частоты по доке)
	RCU->ADCCFG_bit.CLKSEL = 1;	// PLL
	RCU->ADCCFG_bit.DIVN = 2;	// F_ACLK = F_PLL / (2 * (DIVN + 1)) = 33.3 МГц
	RCU->ADCCFG_bit.DIVEN = 1;
	RCU->ADCCFG_bit.CLKEN = 1;
	RCU->ADCCFG_bit.RSTDIS = 1;

	// Тактирование SPI 0 / 1 / 2 / 3
	RCU->SPICFG[0].SPICFG_bit.CLKSEL = 1;	// PLL
	RCU->SPICFG[0].SPICFG_bit.DIVN = 3;		// F_SPICLK = F_PLL / (2 * (DIVN + 1)) = 25 МГц
	RCU->SPICFG[0].SPICFG_bit.DIVEN = 1;
	RCU->SPICFG[0].SPICFG_bit.CLKEN = 1;
	RCU->SPICFG[0].SPICFG_bit.RSTDIS = 1;

	RCU->SPICFG[1].SPICFG_bit.CLKSEL = 1;	// PLL
	RCU->SPICFG[1].SPICFG_bit.DIVN = 3;		// F_SPICLK = F_PLL / (2 * (DIVN + 1)) = 25 МГц
	RCU->SPICFG[1].SPICFG_bit.DIVEN = 1;
	RCU->SPICFG[1].SPICFG_bit.CLKEN = 1;
	RCU->SPICFG[1].SPICFG_bit.RSTDIS = 1;

	RCU->SPICFG[2].SPICFG_bit.CLKSEL = 1;	// PLL
	RCU->SPICFG[2].SPICFG_bit.DIVN = 3;		// F_SPICLK = F_PLL / (2 * (DIVN + 1)) = 25 МГц
	RCU->SPICFG[2].SPICFG_bit.DIVEN = 1;
	RCU->SPICFG[2].SPICFG_bit.CLKEN = 1;
	RCU->SPICFG[2].SPICFG_bit.RSTDIS = 1;

	RCU->SPICFG[3].SPICFG_bit.CLKSEL = 1;	// PLL
	RCU->SPICFG[3].SPICFG_bit.DIVN = 3;		// F_SPICLK = F_PLL / (2 * (DIVN + 1)) = 25 МГц
	RCU->SPICFG[3].SPICFG_bit.DIVEN = 1;
	RCU->SPICFG[3].SPICFG_bit.CLKEN = 1;
	RCU->SPICFG[3].SPICFG_bit.RSTDIS = 1;


	// Тактирование UART 0 / 1 / 2 / 3
	RCU->UARTCFG[0].UARTCFG_bit.CLKSEL = 1;	// PLL
	RCU->UARTCFG[0].UARTCFG_bit.DIVN = 3;	// F_UARTCLK = F_PLL / (2 * (DIVN + 1)) = 25 МГц
	RCU->UARTCFG[0].UARTCFG_bit.DIVEN = 1;
	RCU->UARTCFG[0].UARTCFG_bit.CLKEN = 1;
	RCU->UARTCFG[0].UARTCFG_bit.RSTDIS = 1;

	RCU->UARTCFG[1].UARTCFG_bit.CLKSEL = 1;	// PLL
	RCU->UARTCFG[1].UARTCFG_bit.DIVN = 3;	// F_UARTCLK = F_PLL / (2 * (DIVN + 1)) = 25 МГц
	RCU->UARTCFG[1].UARTCFG_bit.DIVEN = 1;
	RCU->UARTCFG[1].UARTCFG_bit.CLKEN = 1;
	RCU->UARTCFG[1].UARTCFG_bit.RSTDIS = 1;

	RCU->UARTCFG[2].UARTCFG_bit.CLKSEL = 1;	// PLL
	RCU->UARTCFG[2].UARTCFG_bit.DIVN = 3;	// F_UARTCLK = F_PLL / (2 * (DIVN + 1)) = 25 МГц
	RCU->UARTCFG[2].UARTCFG_bit.DIVEN = 1;
	RCU->UARTCFG[2].UARTCFG_bit.CLKEN = 1;
	RCU->UARTCFG[2].UARTCFG_bit.RSTDIS = 1;

	RCU->UARTCFG[3].UARTCFG_bit.CLKSEL = 1;	// PLL
	RCU->UARTCFG[3].UARTCFG_bit.DIVN = 3;	// F_UARTCLK = F_PLL / (2 * (DIVN + 1)) = 25 МГц
	RCU->UARTCFG[3].UARTCFG_bit.DIVEN = 1;
	RCU->UARTCFG[3].UARTCFG_bit.CLKEN = 1;
	RCU->UARTCFG[3].UARTCFG_bit.RSTDIS = 1;


//	RCU->WDTCFG_bit.CLKEN = 1;

}


#define GLOBMEM(ADDR) *(volatile uint32_t*)(ADDR)       //макрос для обращения к учейке по адресу

void remapCheck()
{
    //Данная функция определяет из какой области памяти происходит запуск программы. Делает она это путем "простукивания" памяти.
    //Функция обращается к самым крайним ячейкам областей памяти (MFLASH, BLASH, RAM0) с заранее известными размерами.
    //При обращении к несуществующей ячейке, просиходит BusFault, который мы игнорируем, и выставляется флаг BusFault'a в регистре SCB->CFSR,
    //и таким образом мы вычленяем память, из которой работает программа.

    programMemType = 0;

    static const uint32_t BFARVALID_MASK = (0x80 << SCB_CFSR_BUSFAULTSR_Pos);

    SCB->CFSR |= BFARVALID_MASK;                    //сбрасываем флаг, который взводится по событию BusFault

    uint32_t mask = __get_FAULTMASK();              //сохраняем значения регистра с масками для фолтов
    __disable_fault_irq();                          //отлючяем прерывания по фолтам
    SCB->CCR |= SCB_CCR_BFHFNMIGN_Msk;              //игнорировать BusFault

    GLOBMEM(MEM_MFLASH_SIZE);
    if (!(SCB->CFSR & BFARVALID_MASK)) {
        programMemType = 0x1;                       //программа во внешней памяти (EXT_MEM)
    }
    else {
        SCB->CFSR |= BFARVALID_MASK;
        GLOBMEM(MEM_BFLASH_SIZE);
        if (!(SCB->CFSR & BFARVALID_MASK)) {
            programMemType = 0x2;                   //программа в основной памяти (MFLASH)
        }
        else {
            SCB->CFSR |= BFARVALID_MASK;
            GLOBMEM(MEM_RAM0_SIZE);
            if (!(SCB->CFSR & BFARVALID_MASK)) {
                programMemType = 0x4;               //программа в загрузочной памяти (BFLASH)
            }
            else {
                SCB->CFSR |= BFARVALID_MASK;
                programMemType = 0x8;               //программа в оперативной памяти (RAM0)
            }
        }
    }

    SCB->CCR &= ~SCB_CCR_BFHFNMIGN_Msk;             //сбросываем игнорирование BusFault
    __set_FAULTMASK(mask);                          //восстанавливаем занчения регистра с масками для фолтов
    __enable_fault_irq();                           //включаем прерывания по фолтам
}


void FPUInit()
{
    SCB->CPACR = 0x00F00000;
    __DSB();
    __ISB();
}
void SystemInit(void)
{
    ClkInit();
    FPUInit();
    PeripheralsClockEnable();
    remapCheck();
}
