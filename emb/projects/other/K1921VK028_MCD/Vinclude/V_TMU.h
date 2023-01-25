/*!
    Copyright 2017  АО "НИИЭТ" и ООО "НПФ ВЕКТОР"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      V_TMU.h
 \brief     Модуль блока тригонометрических преобразований (см. TTMU, TTMUPark, TTMUIPark)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 24/06/2019

 \defgroup  V_TMU

 @{
*/

#ifndef V_TMU_H_
#define V_TMU_H_


typedef volatile struct STMUPark {
    _iq ds, qs;
    _iq ang;
    _iq de, qe;
    void (*calc)(volatile struct STMUPark*);
}TTMUPark;

typedef volatile struct STMUIPark {
    _iq ds, qs;
    _iq ang;
    _iq de, qe;
    void (*calc)(volatile struct STMUIPark*);
}TTMUIPark;

typedef volatile struct STMUCarToPol {
    _iq x, y;
    _iq r, phi;
    void (*calc)(volatile struct STMUCarToPol*);
}TTMUCarToPol;

typedef volatile struct STMUPolToCar {
    _iq x, y;
    _iq r, phi;
    void (*calc)(volatile struct STMUPolToCar*);
}TTMUPolToCar;

typedef volatile struct STMU {
    _iq (*sin)(_iq);
    _iq (*cos)(_iq);
    _iq (*atan2)(_iq, _iq);
    TTMUCarToPol carToPol;
    TTMUPolToCar polToCar;
}TTMU;



void TMU_park_calc_IQ24PU (TTMUPark*);
void TMU_ipark_calc_IQ24PU (TTMUIPark*);
_iq TMU_sin_IQ24PU (_iq);
_iq TMU_cos_IQ24PU (_iq);
_iq TMU_atan2_IQ24PU (_iq, _iq);
void TMU_cartesianToPolar_calc_IQ24PU (TTMUCarToPol*);
void TMU_polarToCartesian_calc_IQ24PU (TTMUPolToCar*);



#define TMUPARK_DEFAULTS {  0, \
                            0, \
                            0, \
                            0, \
                            0, \
                            TMU_park_calc_IQ24PU }

#define TMUIPARK_DEFAULTS { 0, \
                            0, \
                            0, \
                            0, \
                            0, \
                            TMU_ipark_calc_IQ24PU }

#define TMUCARTOPOL_DEFAULTS {.calc = TMU_cartesianToPolar_calc_IQ24PU}
#define TMUPOLTOCAR_DEFAULTS {.calc = TMU_polarToCartesian_calc_IQ24PU}
#define TMU_DEFAULTS {  .sin = TMU_sin_IQ24PU,\
                        .cos = TMU_cos_IQ24PU,\
                        .atan2 = TMU_atan2_IQ24PU,\
                        .carToPol = TMUCARTOPOL_DEFAULTS,\
                        .polToCar = TMUPOLTOCAR_DEFAULTS }


#endif /* V_TMU_H_ */

/*@}*/
