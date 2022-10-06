#ifndef __BORLANDC__
#include "stm32f4xx.h"
#include "boards.h"
#endif
// Do not initialize inputs!
void Init(void)
{

}

void Exec(void)
{
#ifndef __BORLANDC__
 v->ImesA = ImesA.Value;
 v->ImesB = ImesB.Value;
 v->ImesC = ImesC.Value;
 v->Sin_mes_n = Sin_mes_n.Value;
 v->Sin_mes_p = Sin_mes_p.Value;
 v->Cos_mes_n = Cos_mes_n.Value;
 v->Cos_mes_p = Cos_mes_p.Value;
 v->Udc_mes = Udc_mes.Value;
 v->analogDip_mes = analogDip_mes.Value;
 v->Usup_mes = Usup_mes.Value;
 v->Vfo_mes = Vfo_mes.Value;

 v->pImesA = ImesA.Value;
 v->pImesB = ImesB.Value;
 v->pImesC = ImesC.Value;
 v->pSin_mes_n = Sin_mes_n.Value;
 v->pSin_mes_p = Sin_mes_p.Value;
 v->pCos_mes_n = Cos_mes_n.Value;
 v->pCos_mes_p = Cos_mes_p.Value;
 v->pUdc_mes = Udc_mes.Value;
 v->pAnalogDip_mes = analogDip_mes.Value;
 v->pUsup_mes = Usup_mes.Value;
 v->pVfo_mes = Vfo_mes.Value;

 #endif
}
