/*==============================================================================
 * хМХЖХЮКХГЮЖХЪ й1921бй028
 *------------------------------------------------------------------------------
 * мххщр, аНЦДЮМ йНКАНБ <kolbov@niiet.ru>
 *==============================================================================
 * дюммне опнцпюллмне наеяоевемхе опеднярюбкъеряъ ╚йюй еярэ╩, аег йюйху-кхан
 * цюпюмрхи, ъбмн бшпюфеммшу хкх ондпюгслебюелшу, бйкчвюъ цюпюмрхх рнбюпмни
 * опхцндмнярх, яннрберярбхъ он ецн йнмйпермнлс мюгмювемхч х нрясрярбхъ
 * мюпсьемхи, мн ме нцпюмхвхбюъяэ хлх. дюммне опнцпюллмне наеяоевемхе
 * опедмюгмювемн дкъ нгмюйнлхрекэмшу жекеи х мюопюбкемн рнкэйн мю
 * опеднярюбкемхе днонкмхрекэмни хмтнплюжхх н опндсйре, я жекэч янупюмхрэ бпелъ
 * онрпеахрекч. мх б йюйнл яксвюе юбрнпш хкх опюбннакюдюрекх ме меяср
 * нрберярбеммнярх он йюйхл-кхан хяйюл, гю опълни хкх йнябеммши сыепа, хкх
 * он хмшл рпеанбюмхъл, бнгмхйьхл хг-гю хяонкэгнбюмхъ опнцпюллмнцн наеяоевемхъ
 * хкх хмшу деиярбхи я опнцпюллмшл наеяоевемхел.
 *
 *                              2018 юн "мххщр"
 *==============================================================================
 */

#ifndef SYSTEM_K1921VK028_H
#define SYSTEM_K1921VK028_H

#ifdef __cplusplus
extern "C" {
#endif

//-- Includes ------------------------------------------------------------------
#include <stdint.h>

//-- Defines -------------------------------------------------------------------
#ifndef CPE
#define CPE 0
#endif

#define SYSCLK_PLL
#define OSICLK_VAL 16000000
#ifndef OSECLK_VAL
#define OSECLK_VAL 12000000
#endif
#ifndef EXTCLK_VAL
#define EXTCLK_VAL 0
#endif
#define SYSCLK_SWITCH_TIMEOUT 0x100000

#if (CPE == 0)
#define REFCLK_VAL OSICLK_VAL
#define SRCCLK_VAL OSECLK_VAL
#elif (CPE == 1)
#define REFCLK_VAL OSECLK_VAL
#define SRCCLK_VAL OSICLK_VAL
#else
#error "Please define CPE with correct state!"
#endif
#define SRCCLK_STARTUP_TIMEOUT 0x100000

#ifndef TRACEEXTCLK_VAL
#define TRACEEXTCLK_VAL OSECLK_VAL
#endif

#ifndef PLLEXTCLK_VAL
#define PLLEXTCLK_VAL OSECLK_VAL
#endif

//-- Variables -----------------------------------------------------------------
extern uint32_t SystemCoreClock; // System Clock Frequency (Core Clock)
extern uint32_t APB0BusClock;    // APB0 Bus Clock Frequency
extern uint32_t APB1BusClock;    // APB1 Bus Clock Frequency

//-- Functions -----------------------------------------------------------------
// Initialize the System
extern void SystemInit(void);
// Updates the SystemCoreClock with current core Clock retrieved from registers
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_K1921VK028_H
