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
 
 \file      V_SSI_Encoder.h
 \brief     ������ ������ �������� � ��������� ��� ������ ��������� ��������, ����������� �� ���������� SSI (��. TSSI_Encoder)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 1.0 25/04/2016

 \defgroup  V_SSI_Encoder ������ ������ �������� � ��������� ��� ������ SSI Encoder (��. TSSI_Encoder)

 \addtogroup V_SSI_Encoder
@{*/


#include "V_IQmath.h"
#include "filter.h"
#ifndef V_SSI_ENCODER_H
#define V_SSI_ENCODER_H

#ifdef __cplusplus
extern "C" {
    #endif

/*! \class TSSI_Encoder
      \brief ������ ��������� ��������, ����������� �� SSI (���������� SPI). � ������ ��� ������� HENGSTLER absolute encoder AC 58.

      ����� \a TSSI_Encoder, ���������� �� ��������� SSI_Encoder,
      �������� ������� ��� ����������� �������� ��������� � �������� ������ 
      ��������� �� ������ �� ��������, ����������� �� SSI.
      ������ �������������� ���������� �� ������ J8 ����� �� ��������� DRV8301-HC-EVM.
      ��� ������ ���������� �������������� �������� (U5) Texas ���� ��������� ������-�� ����� ��������, ��� ��������������
      �������� ��� slave ���������. ����� ������� ��� ��������, ����� ��������� ������ ����������� ����������, ���...
      ����������� U5 ����� ������, �������� ����������� ����, ������� � ����� :)
    */

//! ��. TSSI_Encoder
    struct S_SSI_Encoder {
        Uint32 					resol;		//!<INPUT: ���������� ������� � ������/������;
        float					resol_inv;   //!<�������� �������� � ���������� ������� resol
        Uint16					pole_pairs;	//!<INPUT: ����� ��� �������;
        Uint16					rotation_dir; //!<INPUT: ����������� ��������

        float 					speed_nom;	//!<INPUT: ����������� �������� � ��/���;
        _iq 					speed_elec;	//!<OUTPUT: ������������� �������� � Q24(������������� �������)
        _iq 					theta_elec;	//!<OUTPUT: ������������� ���� � Q24(������������� �������)
        Uint16 					Poscnt_res;	//!<����������.���� � ������;

        Uint16 					Poscnt_resPrev;	//!<����������.���� � ������ ���������� ��������;
        _iq 					theta_mech;	//!<������������ ����;
        _iq						prevThetaMech; //!<������������ ���� ���������� ��������;
        _iq 					theta_el_tmp;	//!<TEMPORARY: ������������� ����;
        _iq						theta_mech_filtered; //!<������������ ���� �������������;
        _iq						theta_mech_filterK; //!<����������� ������� ���. ����;

        _iq                     AngleOffset;//!< �������� �������������� ���� � ��������
        int16					RevolutionCounter; // ���������� ������������ ��������;

        int16					Poscnt_resContinouosInt8;//!<����������.���� � ������ c ������ ���-�� �������� (���������� 8 �������� ����������)
        int16					Poscnt_resContinouosInt;//!<����������.���� � ������ c ������ ���-�� �������� (���������� 16 ��������)
        long					Poscnt_resContinouosLong;//!<����������.���� � ������ c ������ ���-�� �������� (���������� 32 ��������)
        _iq 					theta_mechContinouos;	//!<������������ ���� � �������� ����������;
        _iq 					theta_elecContinouos;	//!<������������� ���� � �������� ����������;

        void (*init)(volatile struct S_SSI_Encoder*);
        void (*calc)(volatile struct S_SSI_Encoder*);
        void (*read)(volatile struct S_SSI_Encoder*);
    };



    typedef  volatile struct S_SSI_Encoder TSSI_Encoder;

    //! ������������� ��-���������.
    #define SSI_ENCODER_DEFAULTS {0,0,0,0, 0,0,0,0, 0,0,0,0,0,0, 0,0, 0,0,0,0,0,\
                               SSI_Encoder_init,\
                               SSI_Encoder_Calc,\
							   SSI_Encoder_Read,\
                              }

//! \memberof TSSI_Encoder
    void SSI_Encoder_init(TSSI_Encoder*);
//! \memberof TSSI_Encoder
    void SSI_Encoder_Calc(TSSI_Encoder*);
//! \memberof TSSI_Encoder
    void SSI_Encoder_Read(TSSI_Encoder*);

    #ifdef __cplusplus
}
#endif

#endif
/*@}*/















