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

 \file      V_QEP.h
 \brief     ������ ������ �������� � ��������� ��� ������ eQEP (��. TposspeedEqep)
 \author    ��� "��� ������". ��� ����� ��������. http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  V_QEP ������ ������ �������� � ��������� ��� ������ eQEP (��. TposspeedEqep)

 \addtogroup V_QEP
@{*/


#include "V_IQmath.h"
#include "filter.h"
#ifndef V_POSSPEED_EQEP_H
#define V_POSSPEED_EQEP_H

#ifdef __cplusplus
extern "C" {
    #endif


    struct SPOSSPEEDCTL_BITS {						// bits
Uint16 InitType:
        2;		// 0:1		 INPUT: ����� ������������� ��������� ��� �����:
        //                  0 - �� ������������ �������
        //					1 - ���������� ������ ����, ����� ���� � ��������� ������(�������� ��������� - 0 ������������� ��������);
        //					2 - ���� � ��������� ������(�������� ��������� - ��������� ����������)
Uint16 index_en:
        1;		// 2		 INPUT: ������� ������
        //					0 - ����� �����������
        //					1 - ����� ���������;
Uint16 dir:
        1;			// 3		 INPUT: ����������� ��������(� ������ ������������� �����������);
        //			        0 - (�� ���������)������ ���������;
        //			 		1 - ��������;
Uint16 CmdInit:
        1;		// 4		 INPUT: ��� ������ �������������
Uint16 Min_clk:
        4;		// 5:8		 INPUT: ����������� ����� ����� ��� ������� �� ������ �������� - �� ������!!!!!
        //					Min_clk=2 - 4 �����
        //							3 - 8 ����� - �� ���������
        // 							4 - 16 �����
        //							5 - 32 �����
        //							6 - 64 �����
        //							7 - 128 �����
        //							8 - 256 �����
        //							9 - 512 �����
        //							10 - 1024 �����
Uint16 rsvd:
        7;			// 9:15		 reserved;
    };

    union SPOSSPEED_CTL {
        Uint16              all;
        struct SPOSSPEEDCTL_BITS  bit;
    };

    struct SPOSSPEEDFLG1_BITS {						// bits
Uint16 UTO_tmp:
        1;		// 0		 TEMPORARY FLAG: ���� time-out;
Uint16 PCO_tmp:
        1;		// 1		 TEMPORARY FLAG: ���� �������������� ������������ ��������;
Uint16 PCU_tmp:
        1;		// 2		 TEMPORARY FLAG: ���� �������������� ������������ ��������;
Uint16 UPPS_tmp:
        4;		// 3:6       TEMPORARY: �������� �������� ������ ����������� ��� �������;
Uint16 CCPS_tmp:
        3;		// 7:9       TEMPORARY: �������� �������� ������������ �������;
Uint16 first_launch:
        2;	// 10:11	 FLAG: ������������� ������� �������;
Uint16 accuracy:
        2;		// 12:13	 FLAG: ���� ������������ ����������;
Uint16 first_theta:
        1;	// 14 		 FLAG: ���� ������� ������� �������� ����������;
Uint16 transit:
        1;		// 15		 FLAG: ���� �������� �� �������� ������� ���������;

    };

    union SPOSSPEED_FLG1 {
        Uint16              all;
        struct SPOSSPEEDFLG1_BITS  bit;
    };

    struct SPOSSPEEDFLG2_BITS {						// bits
Uint16 pos_ident:
        1;		// 0		 FLAG: ���� ������ ������������� ����������� ��������� ������;
Uint16 UTO_tmp2:
        1;		// 1		 TEMPORARY FLAG: ���� time-out;
Uint16 PCO_tmp2:
        1;		// 2		 TEMPORARY FLAG: ���� �������������� ������������ ��������;
Uint16 PCU_tmp2:
        1; 		// 3
Uint16 lost_UTO:
        1;		// 4
Uint16 Dir_prev:
        1;		// 5
Uint16 Cdef:
        1;			// 6
Uint16 Delay_flux:
        1;	// 7
Uint16 first_index:
        1;	// 8
Uint16 rsvd:
        8;			// 9:15		 reserved;
    };

    union SPOSSPEED_FLG2 {
        Uint16              all;
        struct SPOSSPEEDFLG2_BITS  bit;
    };

    
    
/*! \class TposspeedEqep
      \brief ������ ��������� ������������� �������� (��� ���� "�������")

      ����� \a TposspeedEqep, ���������� �� ��������� SposspeedEqep, 
      �������� ������� ��� ����������� �������� ��������� � �������� ������ 
      ��������� �� ������ �� ������������� ��������. ��� ������ � ��������
      ������������ ������������ ������ ���������� EQEP. ��������� ���� theta_elec ������������
      �� ����������� �������� QPOSCNT, ������� ����������� � ���������
      ���� �������� ������������� ��� �������� ����. ����� ��������� ����������
      ���������� ������� ��������� ���� �� ����� ���� ���������, ���� �� ����������
      ������� ���������� (��������� �������� �����). ������ �������� ���� Posspeed_FLG2.bit.pos_ident,
      ��� ������ ��� ����������. �� ����� ������� �������� �������� ��������� �� �������� � �� ������ ��������������
      �������� ����������. ��� ���������� ������� ��������� (�������� �������� ���������)
      ������������ ���������� AngleOffset.
      ��� ���������� �������� speed_elec ������������ ���������� ������� QCPRD,
      ������� �������� ����� ����� �������� �����������  ����� �������. ��� ����������� ����������
      �������� �� ������� � ������ ��������� "��������" ���������� ����� ������������� �� ���� ��� ������
      �������� UPPS. ��� ��� �������� �� ����� ��������� �������� ����������,
      ������� ����������� ������ �������� ������� �������, �������� ��������,
      speed.output, ����� ���� �������� ������������.
    */

//! ��. TposspeedEqep
    struct SposspeedEqep {
        Uint32 					resol;		//!<INPUT: ���������� ������� � ������/������;
        float					resol_inv;   //!<�������� �������� � ���������� ������� resol
        Uint16					pole_pairs;	//!<INPUT: ����� ��� �������;
        Uint16					SpeedCalcType; //!< ��� ������� �������� ��������: 0 - ���������, 1 - ���������� �� ����.
        float 					speed_nom;	//!<INPUT: ����������� �������� � ��/���;
        _iq 					speed_elec;	//!<OUTPUT: ������������� �������� � Q24(������������� �������)
        _iq 					theta_elec;	//!<OUTPUT: ������������� ���� � Q24(������������� �������)
        float 					k_low;		//!<PARAMETER;
        Uint32 					Poscnt_res;	//!<����������.���� � ������;
        Uint16 					Poscnt_res16;	//!<����������.���� � ������ 16�� ��������� ��� ����;
        Uint32 					Poscnt_resPrev;	//!<����������.���� � ������ ���������� ��������;
        int16					MoveK;		//!<TEMPORARY;
        _iq 					theta_mech;	//!<������������ ����;
        _iq						prevThetaMech; //!<������������ ���� ���������� ��������;
        _iq 					theta_el_tmp;	//!<TEMPORARY: ������������� ����;
        Uint16 					speed_calc_skip; //!<������� ������� ��������, ����
        _iq 					speedK;		//!<TEMPORARY: �������� �������, ����������� ������ �������;
        union {                                                               /*!< Status interrupt */
            Uint16 					Qcprdlat16_tmp;	//!<TEMPORARY: ����� ������� �������;
            Uint32 					Qcprdlat_tmp;	//!<TEMPORARY: ����� ������� �������;
        };  //!<��� ���������� � �������
        union {                                                               /*!< Status interrupt */
           uint16_t QEPSTS;                                               /*!< QEPSTS    : type used for word access */
           _QEP_QEPSTS_bits QEPSTS_bit;                                   /*!< QEPSTS_bit: structure used for bit access */
        };  //!<��� ���������� � �������
        Uint16 				DirPrev;
        _iq					speed_tmpIQ;	//!<TEMPORARY;
        TFilter					speed_filter;          //!<������ ��������
        Uint16					skip_counter;//!< ������� �������� ������� �������� ����� ����� UPPS
        union SPOSSPEED_CTL		        Posspeed_CTL;
        union SPOSSPEED_FLG1	                Posspeed_FLG1;
        union SPOSSPEED_FLG2	                Posspeed_FLG2;
        Uint16 					GPIOsValue;//!< ������� �������� ����� GPIO ������ QEP
        Uint16   				Index_eventCounter;
        Uint16                  UPPS_forWatch;//!< ������� �������� UPPS
        _iq                     AngleOffset;//!< �������� �������������� ���� � ��������
        int16					RevolutionCounter; // ���������� ������������ ��������;
        int16					Poscnt_resContinouosInt8;//!<����������.���� � ������ c ������ ���-�� �������� (���������� 8 �������� ����������)
        int16					Poscnt_resContinouosInt;//!<����������.���� � ������ c ������ ���-�� �������� (���������� 16 ��������)
        long					Poscnt_resContinouosLong;//!<����������.���� � ������ c ������ ���-�� �������� (���������� 32 ��������)
        _iq 					theta_mechContinouos;	//!<������������ ���� � �������� ����������;
        _iq 					theta_elecContinouos;	//!<������������� ���� � �������� ����������;

    	long speed_elec_temp; //�������� ���������������
    	long theta_start; //���������� �����������: ��������� ����
    	long theta_finish;//���������� �����������: �������� ����
    	long d_fi;//���������� �����������: ������� � ����
    	long KThetaToSpeed;	//���������� �����������: ����. ��������� ������. ���� � ��������
        void (*init)(volatile struct SposspeedEqep*);
        void (*calc)(volatile struct SposspeedEqep*);
        void (*slow_calc)(volatile struct SposspeedEqep*);
        void (*index)(volatile struct SposspeedEqep*);
    };




    typedef  volatile struct SposspeedEqep TposspeedEqep;

    //! ������������� ��-���������.
    #define POSSPEED_DEFAULTS {.speed_filter = FILTER_DEFAULTS,\
							   .init = TposspeedEqep_init,\
							   .calc = TposspeedEqep_Calc,\
							   .slow_calc = TposspeedEqep_SlowCalc,\
							   .index = TposspeedEqep_IndexEvent,\
                              }

//! \memberof TposspeedEqep
    void TposspeedEqep_init(TposspeedEqep*);
//! \memberof TposspeedEqep
    void TposspeedEqep_Calc(TposspeedEqep*);
//! \memberof TposspeedEqep
    void TposspeedEqep_SlowCalc(TposspeedEqep*);
//! \memberof TposspeedEqep
    void TposspeedEqep_IndexEvent(TposspeedEqep*);
    #ifdef __cplusplus
}
#endif

#endif
/*@}*/















