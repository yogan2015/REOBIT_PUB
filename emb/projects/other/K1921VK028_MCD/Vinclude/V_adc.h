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

 \file      V_adc.h
 \brief     ������ ��������� ��� (��. TAdcDrv)
 \author    ��� "��� ������".  http://motorcontrol.ru
 \version   v 2.0 25/03/2016

 \defgroup  V_adc ������ ��������� ��� (��. TAdcDrv)

 @{
*/


#ifndef V_ADC_H
#define V_ADC_H

#ifdef __cplusplus
extern "C"
{
#endif

  /*! \class TAdcDrv
      \brief ������ ��������� ���

      ����� \a TAdcDrv, ���������� �� ��������� SAdcDrv, �������� � ����
      ������ ��� ��������� ����������� ���. � ������: ����������, ���������� �
      ���������� � ������������� ��������, ����������. � ������� ����������� �������
      ���� ��� ������� ��� ��������� ��� ���������: ����������� �������� � ��������.
      ��������� �������� ���������� ����������� ���: ������ ������� ������ � ���������
      ��������, ����� ���������� �������� ���������� ����. ������ ������� �������, �������
      � ������������ � ��������� ����������� ��������, ����� ���������� �������� ���������������
      ����������������.*/

//! ��. TAdcDrv
  struct SAdcDrv
  {
    int16 Imeas_a_gain;    //!< ����������� ��������.
    int16 Imeas_a_offset;  //!< �������� ����.
    int32 Imeas_a;        //!< ���������� �������� �����������.
    int32 IaGainNom;      //!< ��������������� �����. ��������.
    int32 IA_temp;        //!<��������� ����������

    int16 IASampleLength;			//����� ������� (���-�� ����� �� ������� ���)
	int16 IAPointer;				//����� ��������� �������
	int16 IABuf[4];					//������ ����� ��� ����������


    int16 Imeas_b_gain; 
    int16 Imeas_b_offset;  
    int32 Imeas_b;       
    int32 IbGainNom;
    int32 IB_temp;

    int16 IBSampleLength;			//����� ������� (���-�� ����� �� ������� ���)
	int16 IBPointer;				//����� ��������� �������
	int16 IBBuf[4];					//������ ����� ��� ����������


    int16 Imeas_c_gain;    
    int16 Imeas_c_offset; 
    int32 Imeas_c;        
    int32 IcGainNom;
    int32 IC_temp;

    int16 ICSampleLength;			//����� ������� (���-�� ����� �� ������� ���)
	int16 ICPointer;				//����� ��������� �������
	int16 ICBuf[4];					//������ ����� ��� ����������

    int16 Imeas_d_gain;
    int16 Imeas_d_offset;
    int32 Imeas_d;
    int32 IdGainNom;
    int16 ID_temp;

    int16 IDSampleLength;			//����� ������� (���-�� ����� �� ������� ���)
	int16 IDPointer;				//����� ��������� �������
	int16 IDBuf[4];					//������ ����� ��� ����������


    int16 Udc_meas_gain;
    int16 Udc_meas_offset;
    int32 Udc_meas;
    int32 UdcGainNom;
    int16 Udc_temp;

    int16 UdcSampleLength;			//����� ������� (���-�� ����� �� ������� ���)
	int16 UdcPointer;				//����� ��������� �������
	int16 UdcBuf[4];				//������ ����� ��� ����������

    int16 T_meas_gain;				//!< ����������� ��������.
    int32 T_meas;					//!< ���������� �������� �����������.
    int32 TGainNom;					//!< ��������������� �����. ��������.
    int16 T_temp;					//!<��������� ����������

    int16 ref_meas_gain;
    int16 ref_meas_offset;
    int32 ref_meas;
    int32 refGainNom;
    int16 ref_temp;

    void (*init)(struct SAdcDrv *);
    void (*fast_calc)(struct SAdcDrv*);
    void (*ms_calc)(struct SAdcDrv*);   
    void (*slow_calc)(struct SAdcDrv*);
  };


  typedef struct SAdcDrv TAdcDrv;

//!������������� �� ���������.
#define ADC_DRV_DEFAULTS {\
    54,0,0,0,0, \
	4,0,{0}, \
    54,0,0,0,0, \
	4,0,{0}, \
    54,0,0,0,0, \
	4,0,{0}, \
    54,0,0,0,0, \
	4,0,{0}, \
    800,0,0,0,0, \
	4,0,{0}, \
	100,0,0,0, \
    54,0,0,0,0, \
    AdcDrv_init,\
    AdcDrv_fast_calc,\
    AdcDrv_ms_calc,\
    AdcDrv_slow_calc,\
  }


//! \memberof TAdcDrv
  void AdcDrv_init(TAdcDrv*);
//! \memberof TAdcDrv
  void AdcDrv_slow_calc(TAdcDrv*);
//! \memberof TAdcDrv
  void AdcDrv_fast_calc(TAdcDrv*);
//! \memberof TAdcDrv
  void AdcDrv_ms_calc(TAdcDrv*);
  
#ifdef __cplusplus
}
#endif

#endif

/*@}*/




