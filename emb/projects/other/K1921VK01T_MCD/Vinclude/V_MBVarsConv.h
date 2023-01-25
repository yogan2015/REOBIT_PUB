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

 \file		v_MBVarsConv.h
 \brief		������ �������������� ������ Modbus
 \author	��� "��� ������"
 \version	v.1.1. 02/03/2017

 \addtogroup v_ModBus

 @{
*/



#ifndef V_MBVARSCONV_H
#define V_MBVARSCONV_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "DSP.h"

/*! \class TMBVarsConv
  \brief ������ �������������� ������ Modbus

  ����� \a TMBVarsConv, ���������� �� ��������� SMBVarsConv, ������������
  ��� �������������� ������ �� ������� 16 �������� Modbus � ������ ������� ���������� (IQ 24).
*/


struct SMBVars{
	int	Command;
	int	CommandPrev;
	int speed_ref;
	int CurIs;
	int CurSpeed;
	int Main_ErrorCode;
	int Umax_protect;
	};
//!��. TMBVarsConv	MBVars
#define SMBVARS_DEFAULTS {0,0,0,0,0,0}


struct SMBVarsConv{
				struct SMBVars Vars;
				Uint16 NeedForSave;
                void (*init)(volatile struct SMBVarsConv*);
                void (*calc)(volatile struct SMBVarsConv*);
                void (*slow_calc)(volatile struct SMBVarsConv*);
               };

typedef volatile struct SMBVarsConv TMBVarsConv;

//!������������� �� ���������
#define MBVARSCONV_DEFAULTS { SMBVARS_DEFAULTS,\
				0,\
                MBVarsConv_init,\
                MBVarsConv_calc,\
                MBVarsConv_slow_calc\
                }

//! \memberof TMBVarsConv
void MBVarsConv_init(TMBVarsConv *p);
//! \memberof TMBVarsConv
void MBVarsConv_calc(TMBVarsConv *p);
//! \memberof TMBVarsConv
void MBVarsConv_slow_calc(TMBVarsConv *p);


#ifdef __cplusplus
}
#endif

#endif

/*@}*/
