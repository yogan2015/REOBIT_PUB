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

 \file      V_DIO.h
 \brief     Модуль дискретных входов/выходов
 \author    ООО "НПФ Вектор". http://motorcontrol.ru
 \version   v 2.0 25/09/2019

 \addtogroup
 @{*/


#ifndef V_DIO_H
#define V_DIO_H

#ifdef __cplusplus
extern "C" {
#endif




typedef struct SDIO {

	union {						//!<Вектор управления дискретными выходами
		Uint16 out;
		struct {
			Uint16 n0:1;
			Uint16 n1:1;
			Uint16 n2:1;
			Uint16 n3:1;
			Uint16 n4:1;
			Uint16 n5:1;
			Uint16 n6:1;
			Uint16 n7:1;
			Uint16 n8:1;
			Uint16 n9:1;
			Uint16 n10:1;
			Uint16 n11:1;
			Uint16 n12:1;
			Uint16 n13:1;
			Uint16 n14:1;
			Uint16 n15:1;
		}out_bit;
	};

	union {						//!<Вектор состояния дискретных входов с учетом инверсии маски
		Uint16 in;
		struct {
			Uint16 n0:1;
			Uint16 n1:1;
			Uint16 n2:1;
			Uint16 n3:1;
			Uint16 n4:1;
			Uint16 n5:1;
			Uint16 n6:1;
			Uint16 n7:1;
			Uint16 n8:1;
			Uint16 n9:1;
			Uint16 n10:1;
			Uint16 n11:1;
			Uint16 n12:1;
			Uint16 n13:1;
			Uint16 n14:1;
			Uint16 n15:1;
		}in_bit;
	};

	_iq inputKf;				//!<Коэффициент фильтрации дискретных входов Kf = 0.001/Tф (Tф - постоЯннаЯ времени фильтра, сек)
	_iq inputOff;				//!<Порог перехода дискретного входа в состоЯние OFF (0)
	_iq inputOn;				//!<Порог перехода дискретного входа в состоЯние ON (1)

	// Фильтры дискретных входов
	TFilter fIn0;
	TFilter fIn1;
	TFilter fIn2;
	TFilter fIn3;
	TFilter fIn4;
	TFilter fIn5;
	TFilter fIn6;
	TFilter fIn7;
	TFilter fIn8;
	TFilter fIn9;
	TFilter fIn10;
	TFilter fIn11;
	TFilter fIn12;
	TFilter fIn13;
	TFilter fIn14;
	TFilter fIn15;

	void (*init)(struct SDIO*);
	void (*slow_calc)(struct SDIO*);
	void (*ms_calc)(struct SDIO*);
}TDIO;




//!Инициализатор по-умолчанию.
#define DIO_DEFAULTS { 	.out = 0, .in = 0, \
						.inputKf = 0, .inputOff = 0, .inputOn = 0, \
						.fIn0 = FILTER_DEFAULTS, \
						.fIn1 = FILTER_DEFAULTS, \
						.fIn2 = FILTER_DEFAULTS, \
						.fIn3 = FILTER_DEFAULTS, \
						.fIn4 = FILTER_DEFAULTS, \
						.fIn5 = FILTER_DEFAULTS, \
						.fIn6 = FILTER_DEFAULTS, \
						.fIn7 = FILTER_DEFAULTS, \
						.fIn8 = FILTER_DEFAULTS, \
						.fIn9 = FILTER_DEFAULTS, \
						.fIn10 = FILTER_DEFAULTS, \
						.fIn11 = FILTER_DEFAULTS, \
						.fIn12 = FILTER_DEFAULTS, \
						.fIn13 = FILTER_DEFAULTS, \
						.fIn14 = FILTER_DEFAULTS, \
						.fIn15 = FILTER_DEFAULTS, \
						.init = DIO_init, \
						.slow_calc = DIO_slow_calc, \
						.ms_calc = DIO_ms_calc, \
}


//! \memberof TDIO
void DIO_init(TDIO* p);
//! \memberof TDIO
void DIO_slow_calc(TDIO* p);
//! \memberof TDIO
void DIO_ms_calc(TDIO* p);


#ifdef __cplusplus
}
#endif

#endif

/*@}*/
