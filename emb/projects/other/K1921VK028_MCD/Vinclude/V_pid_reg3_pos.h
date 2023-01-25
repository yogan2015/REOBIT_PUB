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

 \file      V_pid_reg3.h
 \brief     ���-��������� (��. TPidReg3)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016

\defgroup  V_pid_reg3 ���-���������

@{*/



#ifndef PID_REG3_POS_H
#define PID_REG3_POS_H

#ifdef __cplusplus
extern "C" {
#endif

  /*! \class TPidReg3
    \brief ������ ���-����������

    ����� \a TPidReg3, ���������� �� ��������� SPidReg3, ������������
    ����� ��������������� - ����������� - ���������������� ���������.
    ��� ������������ �������������, ���������������� ����� ����� ������������� ������.
  
  */

//! ��. TPidReg3
typedef struct SPidReg3_pos{  long  pid_ref_reg3; //!< Input: Reference input
				  long  pid_fdb_reg3;//!< Input: Feedback input  
				  long  e_reg3;//!<Variable: Error
				  long  e_reg3Dz;//!<Variable: Error after dead zone
				  long  Kp_reg3;//!< Parameter: Proportional gain 
				  long  up_reg3;//!< Variable: Proportional output  
				  long  ui_reg3;//!< Variable: Integral output    
				  long  ud_reg3;//!< Variable: Derivative output    
				  long  uprsat_reg3;//!< Variable: Pre-saturated output  
				  long  saterr_reg3Add;//!< Variable: �������������� ������ ��������� �� "�������� ������"
				  long  pid_out_max;//!< Parameter: Maximum output    
				  long  pid_out_min;//!< Parameter: Minimum output    
				  long  pid_out_reg3;//!< Output: PID output    */
				  long  saterr_reg3;//!< Variable: Saturated difference 
				  long  Ki_reg3;//!< Parameter: Integral gain   
				  long  Kc_reg3;//!< Parameter: Integral correction gain  
				  long  Kd_reg3;//!< Parameter: Derivative gain   
				  long  up1_reg3;//!< History: Previous proportional output
				  long  pid_out_test;//!< Output: PID output for test   
				  long  DeadZone;//!< ������� ����
				  long  Kf_d;//!<������ ���������������� �����
				  long  e_reg3_filterOut;//!<����� ������� ���������������� �����
				  long  DiffDelim;//!<�������� ��� ������������ ������� �����������
				  long  DiffCounter;//!<������� ��� ��������
				  int   KdFilterInitFlag;//!<���� ������� ������� ��� ������������� ������� ����. �����
		 	 	  void  (*calc)(struct SPidReg3_pos*);//!< Pointer to calculation function
		 	 	  void  (*reset)(struct SPidReg3_pos*);//!< Pointer to reset function
				 }TPidReg3_pos;


//! ������������� ��-���������
#define PIDREG3_DEFAULTS_POS { 0,0, \
                           0, \
                           0, \
                           0, \
                           0, \
                           0, \
                           0, \
                           0,0, \
                           _IQ(1), \
                           _IQ(-1), \
						   0, \
                           0, \
                           _IQ(0.05), \
                           _IQ(0.5), \
                           _IQ(0), \
                           0,0,0,0,0,0,0,0,\
              			  pid_reg3_calc_pos,\
						  pid_reg3_reset_pos}



//! \memberof TPidReg3
void pid_reg3_calc_pos(TPidReg3_pos*);
void pid_reg3_reset_pos(TPidReg3_pos*);



#ifdef __cplusplus
}
#endif

#endif

/*@}*/
