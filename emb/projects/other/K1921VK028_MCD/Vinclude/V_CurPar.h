/*!
     Copyright 2017 	�� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 
 \file      V_CurPar.h
 \brief     ������ ����������� ������� ����������  (��. TCurPar)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  V_CurPar ������ ����������� ������� ���������� (��. TCurPar)

 @{
*/


#ifndef V_CURPAR_H
#define V_CURPAR_H

#include "filter.h"

#ifdef __cplusplus
extern "C" {
#endif


    /*! \class TCurPar
      \brief ������ ����������� ������� ���������� 

      ����� \a TCurPar, ���������� �� ��������� SCurPar, ��������
      ��� ������������ ���������� ��� ����������� ������� ���������� �������.
      ��������, ������ ����������� ����� ���, ������� �������� � �.�.
      */

//! ��. TCurPar
struct SCurPar{
    long speed; //!< ������� ������� ��������
    long power; //!< ������� ��������
    long Is; //!< ������� ��� ������� ����������� ����������
    long ThetaRefCurr; //!< �������� ������� ���������
    long ThetaCurr; //!< ������� ������� ���������

    long IsRef; //!< ��� ������� ��������
    long Ialpha; //!< ��� �� ��� �����
    long Ibeta; //!< ��� �� ��� �����

    long Ualpha; //!< ���������� �� ��� �����
    long Ubeta; //!< ���������� �� ��� �����
    long PowerK; //!< ��������� �������� ��� ��������������� ��������

    TFilter fPower; //!< ������ ��������

    void (*init)(volatile struct SCurPar*);//!< ��������� �������������
    void (*calc)(volatile struct SCurPar*);//!<������
    void (*slow_calc)(volatile struct SCurPar*);//!<��������� ������
};

typedef volatile struct SCurPar TCurPar;


//!������������� ��-���������
#define TCUR_PAR_DEFAULTS \
{\
	0,0,0,0,0,\
	0,0,0,\
	0,0,0,\
	FILTER_DEFAULTS,\
	&CurPar_init, \
	&CurPar_calc, \
	&CurPar_slow_calc, \
}


//! \memberof TCurPar
void CurPar_init(TCurPar*);
//! \memberof TCurPar
void CurPar_calc(TCurPar*);
//! \memberof TCurPar
void CurPar_slow_calc(TCurPar*);



#ifdef __cplusplus
}
#endif	// extern "C"

#endif	// V_UF_H

/*@}*/


