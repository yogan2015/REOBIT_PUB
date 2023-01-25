/*!
 \file      v_data_log.h
 \brief     4-� ��������� ������ ��� ������������������� � �������� ������� (��. TDataLog)
� ������ 2.0 ���������� 32-������ ����� ������. �������� ���������:
��� ������ ����������� ������������ ���������� ���������� � ������������ ����� 'V_data_log.h'
(���� �� ��������� ����� �����������������):
//#define DLOG_DATA_SIZE 16
#define DLOG_DATA_SIZE 32
��� 16-������� ������ ���������� �������� "������������" �������. ������ ������ �������� ��� ����.
����� ������ ��� ���� �� �������� ���� 32-������� ������ (��. ����) � �������� �� "�������������" ���������
(������, ����� ����������� ������ � ���� ������ 32-������, �� ��� ��������). ��� �������� �������� ������
����� ���������, ��� � ������, ����� ��������.
32-������ �����:
� ���������� 'dlog.control' �������� ���� '32-������ ������', �� �������� ����� ������ ����� ��� �����������.
��� SDO-������ ������������ ������, ��� � ������, ����������� ����� 32-������ ���������� 'dlog.next_value_var'
(���, ����� 16-������� ��������, ���� ������ ����). � �� ��������� ��� �����:
- ����, ��� � ���� "��������" - ������� 16 ��� �����
- ����, ��� ���������� 16-���������
������ ������� ����������� ������� ����� ��������, ����� - ������� � �.�. �� ���� ������.
���� ���������� 16-���������, �� ������� ����� �� �������������. ��� �������� ��������:
�.�. ���� �������� ������ ��������� � ��� 256-��� 16-������� �������, �� ������ ������� �����������
������ 256 ���� (128 32-������ �����), ����� - ��������� 256 ����. �.�. ������������ ��� �������� �������.

 \author	��������� ��� ��� ������
 \version   v 2.0 10/04/2017
 \defgroup  v_data_log �������� ����������� (��. TDataLog)
 @{
*/


#ifndef V_DATA_LOG_H
#define V_DATA_LOG_H

#include "CANOpen_drv.h"

#ifdef __cplusplus
extern "C"
{
#endif

// ������ ��������, ������������ ����� ������ (���)
//#define DLOG_DATA_SIZE 16
#define DLOG_DATA_SIZE 32


#if DLOG_DATA_SIZE == 16
typedef int16 type_data;
#elif DLOG_DATA_SIZE == 32
typedef int32 type_data;
#endif


//! ������ �������� ��� �������������������.

//!���� ����� ������, �� ��� ������ ���� �� ������ ��� - ������� ����� �������� �� ��� �����
//!���������� ������, ��� ��� �� ��� ����� ������� ���������: ��������, ��� ��������� ������
//!����������� ����� �����������: p->Wcounter&=0xFF; ��� FF - ����� (������������� 256 �����)
#define NUMBER_SAMPLES  256

  /*! \class TDataLog
    \brief 4-� ��������� ������ ��� ������������������� � �������� �������

    ����� \a TDataLog, ���������� �� ��������� SDataLog, ��������� ���������� ��������� 4 ���������� � �������
    �� 255 ����� � �������� �������������� �� �������. ����� ����, �����
    ����� � ��������� CANOpen ��� ������������� �������� ���� ����������: �����
    "��������" � ���������� ����� ������������ ������� �������.*/

//! ��. TDataLog
  struct SDataLog
  {
    type_data buff[(NUMBER_SAMPLES*4)];	//4 ������� ��� �������� ������������, ���������� � ���� �������
#if DLOG_DATA_SIZE == 16
    type_data  *dlog_iptr1; 	//!< ��������� �� ���������� ��� ������ (��������. ��� ���� A, �������� � �.�.)
    type_data  *dlog_iptr2;		//!< Input: Second input pointer (Q15)
    type_data  *dlog_iptr3;
    type_data  *dlog_iptr4;
#endif
    int  dlog_cntr_max;  		//!< Parameter: Maximum number of samples
    Uint16 Wcounter;            //!< ������� �� ������� ��� ������
    Uint16 Rcounter;            //!< ������� �� ������� ��� ������
    type_data*  dl_buffer1_adr;  	//!< ��������� �� �������, ��� ����� �������� �������������
    type_data*  dl_buffer2_adr;  	//!< Parameter: Buffer starting address 2
    type_data*  dl_buffer3_adr;
    type_data*  dl_buffer4_adr;

    type_data upload_buff[NUMBER_SAMPLES];	//������ ��� �������� ������������� � ������. ���� ���������� ������������� �� ������ �� ������� �������� buff �� ���������, ����� ������ ������������� ���� � ������ �������.
    type_data*  dl_upload_buffer_adr;		//��������� �� ������ ��� ��������.
    Uint32 trig_shift;						//����� ������ ����� ����� ������������ ��������. ������������, ����� ������, ������� ����� ����������� ���������.
    Uint16 trig_shift_int;					//�� ��, ������������ � �����
    Uint16 first_point_written;				//������ �����, ����������� � ������������ ������������� � ������ ����� ����������� � ����� ������������ ��������
    Uint16 prehistory_length;				//����� ���������� ����������� (���� ���������� ��������������������� ������� "��������", ��� ����������)
    Uint16 valid_points_num;				//������� �������� ����� �����������, ���������� ����� ����������������� ������� "��������" � �������

    /*!  ������� ������ ������:\n
    0 - ����\n
    1 - ����������� ������\n
    2 - ������ �� ����� ��� ���������\n
    3 - ����������� ������ ����� ���������� �� ��� 4 ������� ���������������, ��� ��������� ������� �������������.\n
    ������������� ���������� ���� ������ ������� ������� set_mode! */
    Uint16 mode_reset;             //!< �������� ����� ������
    Uint16 mode_reset_prev;        //!< ���������� ����� ������
    int E;							// ���� �����

    /*! "control" ����� 32 �������. ������ 16 ��� - �����, ��������� 16 ��� - ��������� ������������.\n
      9   8   7   6   5   4   3   2   1   0\n
    | x | x | x | x | x | x | x | x | x | x |\n
      |   |   |   |   |   |   ������ 4 ���� - ����� �� 4� ��������� ���������� (����� ������ ���������, ����� ������ ����������)\n
      |   |   |   |   2 ���� - �������� ����� �����������: 0, 1, 2\n
      |   |   |   ��� "������ ������" - ��������������� ������������\n
      |   |   ��� "�������������� ������� ��������"\n
      |   ��� "32-������ ������"\n
      ������ */
    long control;                  //!< ���������� ������������ ����� ������� ���������

    unsigned int WriteDelimiter;        //!<�������� ������ ��� ������
    unsigned int WriteDelimiterCounter; //!<������� ��� ��������
    long ind_subind1;              //!<������������ ������ � ��������� ��� �������
    long ind_subind2;
    long ind_subind3;
    long ind_subind4;
    unsigned long next_value_var;	//!<����� ��� ���������� ����������� ���������� �������� ��� ����������:
    								//!<���� 0-15: �������� �����
    								//!<���� 16-23: Rcounter (���������� �����)
    								//!<���� 24-25: buff_num
    								//!<��� 26: ����, ��� � ���� "��������" - ������� 16 ��� ����� (������������ ��� DLOG_DATA_SIZE = 32)
    								//!<��� 27: ����, ��� ���������� 16-��������� (������������ ��� DLOG_DATA_SIZE = 32)
    Uint16 StartBits;
    int buff_num;              	//!<����� �������, �� �������� ���� ���������� �������� � next_value_var
    int ResetAfterStart; 		//!<���� ��������� �������� ������ ��� �������
    Uint16 OneShotOperation;	//!<���� ������������� ������������ ������ �� ������� ������� (������� � 1 �������� ������ �� 2)
    TCo_OdVars *pco_vars;       //!<����� ��������� �������� CANopen
#if DLOG_DATA_SIZE == 32
    int highPartOfValue;		//!<���� ������ ������� �����
    TObjectInfo object1Info;	//!<���������� � ������������ ������� �1
    TObjectInfo object2Info;	//!<���������� � ������������ ������� �2
    TObjectInfo object3Info;	//!<���������� � ������������ ������� �3
    TObjectInfo object4Info;	//!<���������� � ������������ ������� �4
#endif
    void (*update)(volatile struct SDataLog *);			//!<Pointer to update function
    void (*set_mode)(Uint16 mode_reset,volatile struct SDataLog *);	//!<Pointer to set_mode function
    void (*background_analizer)(volatile struct SDataLog *);	//!<Pointer to background_analizer function
  } ;

typedef volatile struct SDataLog TDataLog;



#if defined(CAN_1_ENABLE)
#define COX_VARS co1_vars
#elif defined(CAN_2_ENABLE)
#define COX_VARS co2_vars
#endif

//! ������������� ��-��������� ��� ������� ������
#if DLOG_DATA_SIZE == 16
#define DATALOG_DEFAULTS {  {0},\
    (type_data *)0x00000300, \
    (type_data *)0x00000300, \
    (type_data *)0x00000300, \
    (type_data *)0x00000300, \
    NUMBER_SAMPLES, \
    0,0,\
    ((type_data *)&dlog.buff), \
    ((type_data *)&dlog.buff+NUMBER_SAMPLES), \
    ((type_data *)&dlog.buff+NUMBER_SAMPLES*2), \
    ((type_data *)&dlog.buff+NUMBER_SAMPLES*3), \
    {0}, ((type_data *)&dlog.upload_buff), 0, 0, 0, 0, 0,\
    2, 2, 0,\
    0,\
    0,0,\
    0,0,0,0,\
    0,0,\
    0,\
	1,\
    0,\
	&COX_VARS,\
    data_log_update,\
    dlog_set_mode,\
    dlog_background_analizer }
#endif

#if DLOG_DATA_SIZE == 32
#define DATALOG_DEFAULTS {  {0},\
    NUMBER_SAMPLES, \
    0,0,\
    ((type_data *)&dlog.buff), \
    ((type_data *)&dlog.buff+NUMBER_SAMPLES), \
    ((type_data *)&dlog.buff+NUMBER_SAMPLES*2), \
    ((type_data *)&dlog.buff+NUMBER_SAMPLES*3), \
    {0}, ((type_data *)&dlog.upload_buff), 0, 0, 0, 0, 0,\
    2, 2, 0,\
    0,\
    0,0,\
    0,0,0,0,\
    0,0,\
    0,\
	1,\
    0,\
	&COX_VARS,\
	0,\
	{ 0 }, { 0 }, { 0 }, { 0 },\
    data_log_update,\
    dlog_set_mode,\
    dlog_background_analizer }
#endif



//! \memberof TDataLog
  void data_log_update(TDataLog *);
//! \memberof TDataLog
  void dlog_set_mode(Uint16 mode_reset,TDataLog *);
//! \memberof TDataLog
  void dlog_background_analizer(TDataLog *);

#ifdef __cplusplus
}
#endif

#endif

/*@}*/


