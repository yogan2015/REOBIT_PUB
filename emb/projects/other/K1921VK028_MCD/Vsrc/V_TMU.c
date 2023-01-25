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

 \file      V_TMU.c
 \brief     Модуль блока тригонометрических преобразований (см. TTMU, TTMUPark, TTMUIPark)
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 1.0 24/06/2019

 \addtogroup V_TMU
 @{*/


#include "main.h"

//Функция преобразования Парка. Принимает на вход аргументы в относительных единицах в IQ24. По величине аргументы ограничены только самим форматом IQ24.
void TMU_park_calc_IQ24PU (TTMUPark *p) {
    TMU->PHIN = _IQ24mpy(((p->ang & 0x00FFFFFF) << 4), _IQ24(2.0*_PI));     //ограничиваем угол единицей в IQ24, преобразуем в IQ28, а затем в абсолютный угол в радианах, как требует того блок TMU

    TMU->YIN = (p->ds >> 3);                //преобразуем неограниченное число в формате IQ24 в ограниченное единицей в формате IQ28
    TMU->XIN = (p->qs >> 3);                //то же

    TMU->CMD = (3 << TMU_CMD_FUNC_Pos) |    // Повернуть вектор
               (0 << TMU_CMD_ARGT_Pos) |    // Аргументы в IQ28
               (1 << TMU_CMD_START_Pos);    // Поехали

    //Ждем, пока блок TMU закончит вычисления
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    p->de = ((int32)TMU->YOUT << 3);        //преобразуем реультат обратно от максимально возможной единицы для блока TMU в IQ28 до максимально возможного числа в IQ24
    p->qe = ((int32)TMU->XOUT << 3);        //то же
}


//Функция обратного преобразования Парка. Принимает на вход аргументы в относительных единицах в IQ24. По величине аргументы ограничены только самим форматом IQ24.
void TMU_ipark_calc_IQ24PU (TTMUIPark *p) {
    TMU->PHIN = _IQ24mpy(((p->ang & 0x00FFFFFF) << 4), _IQ24(2.0*_PI));     //ограничиваем угол единицей в IQ24, преобразуем в IQ28, а затем в абсолютный угол в радианах, как требует того блок TMU

    TMU->YIN = (p->qe >> 3);                //преобразуем неограниченное число в формате IQ24 в ограниченное единицей в формате IQ28
    TMU->XIN = (p->de >> 3);                //то же

    TMU->CMD = (3 << TMU_CMD_FUNC_Pos) |    // Повернуть вектор
               (0 << TMU_CMD_ARGT_Pos) |    // Аргументы в IQ28
               (1 << TMU_CMD_START_Pos);    // Поехали

    //Ждем, пока блок TMU закончит вычисления
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    p->qs = ((int32)TMU->YOUT << 3);        //преобразуем реультат обратно от максимально возможной единицы для блока TMU в IQ28 до максимально возможного числа в IQ24
    p->ds = ((int32)TMU->XOUT << 3);        //то же
}


//Функция синуса. Принимает на вход угол в относительных единицах в IQ24. По величине угол ограничен только самим форматом IQ24.
_iq TMU_sin_IQ24PU (_iq angle) {
    TMU->PHIN = _IQ24mpy(angle & 0x00FFFFFF, _IQ24(2.0*_PI));         //ограничиваем угол единицей в IQ24 и преобразуем в абсолютный угол в радианах, как требует того блок TMU

    TMU->CMD =  (0 << TMU_CMD_FUNC_Pos) |   // Вычислить синус/косинус
                (4 << TMU_CMD_ARGT_Pos) |   // Аргументы в IQ24
                (1 << TMU_CMD_START_Pos);   // Поехали

    //Ждем, пока блок TMU закончит вычисления
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    return (TMU->YOUT);
}


//Функция косинуса. Принимает на вход угол в относительных единицах в IQ24. По величине угол ограничен только самим форматом IQ24.
_iq TMU_cos_IQ24PU (_iq angle) {
    TMU->PHIN = _IQ24mpy(angle & 0x00FFFFFF, _IQ24(2.0*_PI));         //ограничиваем угол единицей в IQ24 и преобразуем в абсолютный угол в радианах, как требует того блок TMU

    TMU->CMD =  (0 << TMU_CMD_FUNC_Pos) |   // Вычислить синус/косинус
                (4 << TMU_CMD_ARGT_Pos) |   // Аргументы в IQ24
                (1 << TMU_CMD_START_Pos);   // Поехали

    //Ждем, пока блок TMU закончит вычисления
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    return (TMU->XOUT);
}


//Функция арктангенса. Принимает на вход аргументы в относительных единицах в IQ24. По величине аргументы ограничены только самим форматом IQ24.
_iq TMU_atan2_IQ24PU (_iq inY, _iq inX) {
    TMU->XIN = (inX >> 3);                      //преобразуем неограниченное число в формате IQ24 в ограниченное единицей в формате IQ28
    TMU->YIN = (inY >> 3);                      //то же

    TMU->CMD =  (1 << TMU_CMD_FUNC_Pos) |       // Перевод из прямоугольной системы координат в полярную
                (0 << TMU_CMD_ARGT_Pos) |       // Аргументы в IQ28
                (1 << TMU_CMD_START_Pos);       // Поехали

    //Ждем, пока блок TMU закончит вычисления
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    return (_IQ24mpy((((int32)TMU->PHOUT) >> 4), _IQ24(0.15915494309189533576)));      //преобразуем угол из IQ28 в IQ24 и затем делим на 2Пи для преобразования в относительный угол
}


//Функция преобразования координат из прямоугольной системы в полярную. Принимает на вход аргументы в относительных единицах в IQ24. По величине аргументы ограничены только самим форматом IQ24.
void TMU_cartesianToPolar_calc_IQ24PU (TTMUCarToPol *p) {
    TMU->XIN = (p->x >> 3);                      //преобразуем неограниченное число в формате IQ24 в ограниченное единицей в формате IQ28
    TMU->YIN = (p->y >> 3);                      //то же

    TMU->CMD = (1 << TMU_CMD_FUNC_Pos) |    // Перевод из прямоугольной системы координат в полярную
               (0 << TMU_CMD_ARGT_Pos) |    // Аргументы в IQ28
               (1 << TMU_CMD_START_Pos);    // Поехали

    //Ждем, пока блок TMU закончит вычисления
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    p->r = ((int32) TMU->XOUT << 3);                                                  //преобразуем реультат обратно от максимально возможной единицы для блока TMU в IQ28 до максимально возможного числа в IQ24
    p->phi = _IQ24mpy((((int32)TMU->PHOUT) >> 4), _IQ24(0.15915494309189533576));     //преобразуем угол из IQ28 в IQ24 и затем делим на 2Пи для преобразования в относительный угол
}


//Функция преобразования координат из полярной системы в прямоугольную. Принимает на вход аргументы в относительных единицах в IQ24. По величине аргументы ограничены только самим форматом IQ24.
void TMU_polarToCartesian_calc_IQ24PU (TTMUPolToCar *p) {
    TMU->XIN = (p->r >> 3);                                                     //преобразуем неограниченное число в формате IQ24 в ограниченное единицей в формате IQ28
    TMU->PHIN = _IQ24mpy(((p->phi & 0x00FFFFFF) << 4), _IQ24(2.0*_PI));         //ограничиваем угол единицей в IQ24, преобразуем в IQ28, а затем в абсолютный угол в радианах, как требует того блок TMU

    TMU->CMD = (2 << TMU_CMD_FUNC_Pos) |    // Перевод из полярной системы координат в прямоугольную
               (0 << TMU_CMD_ARGT_Pos) |    // Аргументы в IQ28
               (1 << TMU_CMD_START_Pos);    // Поехали

    //Ждем, пока блок TMU закончит вычисления
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");

    p->x = ((int32) TMU->XOUT << 3) ;      //преобразуем реультат обратно от максимально возможной единицы для блока TMU в IQ28 до максимально возможного числа в IQ24
    p->y = ((int32) TMU->YOUT << 3);       //то же
}

/*@}*/
