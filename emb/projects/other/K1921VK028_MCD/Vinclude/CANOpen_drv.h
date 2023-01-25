/*!
     Copyright 2017     �� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file      CANOpen_drv.h
 \brief     ������� CANOpen
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 3.19 2019_03_06

 \defgroup  CANOpen_drv ������� CANOpen
 @{
*/

#ifndef CAN_OPEN_DRV_H
#define CAN_OPEN_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

//********************************************************************************************
//

//!���������� CAN 1
#define CAN_1_ENABLE
//********************************************************************************************
//!���������� CAN 2
#define CAN_2_ENABLE
//********************************************************************************************
/*
 * ������� ������������� �������� ��� CAN1 � CAN2
 * ������� ���������� ������ � ���������������� ������� (��������� � ������� ������������ ��������� co_UserMemoryRead � co_UserMemoryWrite -
 * ��. ���� CANOpenUDfuncs.c), ������� � ������� ������ ������ � ��������� ������������ ������ �������������,
 * ��� ������� ���������������� ������ ������������������.
 */
extern Uint16 co1_Init(TCo_OdVars* ppc);//� ������ ���� ������������� �� ������� ������� ���������� 0, ����� 1.
extern Uint16 co2_Init(TCo_OdVars* ppc);//� ������ ���� ������������� �� ������� ������� ���������� 0, ����� 1.

//������� ����������������� CAN ��� �������������� ���������� �� ���������������� ������ (����� ���� ������������ ���� ��� ��������� �������������)
extern Uint16 co_ReInit(TCo_OdVars* ppc);//� ������ ���� ������������� �� ������� ������� ���������� 0, ����� 1.
extern void propReset (void);
//��������� �������
extern void co_UserMemoryRead (const T_UserMemoryContext *p);
extern void co_UserMemoryWrite (const T_UserMemoryContext *p);

#ifdef CAN_1_ENABLE
extern void co_CAN1GpioInit();
extern void co_CAN1INTEnable();
extern void co_CAN1INTDisable();
#endif

#ifdef CAN_2_ENABLE
extern void co_CAN2GpioInit();
extern void co_CAN2INTDisable();
extern void co_CAN2INTEnable();
#endif


//!������� �������� CANOpen ���������� � ���������� 1 �� �������, ������������ ������ ��������
extern void co_1ms_calc(TCo_OdVars*);

//!������� ����������� �������� CANOpen � ������� ���������
extern void co_background_calc(TCo_OdVars*);

//!������� �������������� �������� ���������� ������� �������� �� ���������
/*!
����������� ������ ������� �������� �������������� ���������� ����������
���� � ���������
type -  1 rw-���������
        2 rwp-���������
        3 rwps-���������
range - 1 �������������� �������� 1000h-1FFFh
        2,3,4,5
������� �� ������� ���������� ��������� � ������ (�������� ������� � ����) */
extern void co_ODexpositor_instaurationDefault(TCo_OdVars* ppc, Uint16 type, Uint16 range);

//!������� ���������� �������� ���������� ������� �������� � �����
/*!����������� ������ ������� �������� ���������� ���������� ����������
���� � ���������
type -  1 rw-���������
        2 rwp-���������
        3 rwps-���������
range - 1 �������������� �������� 1000h-1FFFh
        2,3,4,5
������� �� ������� ���������� ��������� � ������ (�������� ������� � ����).*/
extern void co_ODexpositor_paramConservation(TCo_OdVars* ppc, Uint16 type, Uint16 range);

//!������� �������������� �������� ���������� ������� �������� �� �����
/*! ����������� ������ ������� �������� �������������� ���������� ����������
���� � ���������
type -  1 rw-���������
        2 rwp-���������
        3 rwps-���������
range - 1 �������������� �������� 1000h-1FFFh
        2,3,4,5
��������!!!�������������� ���������� 2-�� � 3-�� ����� �������� ����
���������� co_protectBit = 0. ���� co_protectBit = 1 , �� ������� ������
�� "������".
���� �������������� ���������� ��������� ���� � ��������� ���������
��������(����������� ����� �� �������), �� �������������� ���������
���� � ��������� �����������.���� ����� ���� ������� ��������������
�� ����������� �������, �� ����������� �������������� ���������� ���������
���� � ��������� �� ���������.
������� �� ������� ���������� ��������� � ������ (�������� ������� � ����).*/
extern void co_ODexpositor_paramInstauration(TCo_OdVars* ppc, Uint16 type, Uint16 range);

// ������� ������� NMT
// ������� ����� ��������� NMT ��������, ���� ���� NMT �������
//! ������� ��� �������� NMT  (����� ������ ��� NMT �������)
void co_sendNMT(TCo_OdVars* ppc, Uint16 nmtCommand, Uint16 nmtNODE_ID);

//!������� ������������ ��� �������� SDO �������� �� ������ ���������� �������
extern void co_SDOrequestRead(TCo_OdVars*);     
//!������� ������������ ��� �������� SDO �������� �� ������ ���������� �������
extern void co_SDOrequestWrite(TCo_OdVars*);   

extern void Z_co_receiveSDOrequest(TCo_OdVars*, TZCanMsg*);
extern void co_CANToExtInterface_Send(TZCanMsg* MSG, Uint16 tag_CANnum);

/*!������� ���������� ����� ���������� �� ���������� �������
 � ����������. ���� "���������" ���������� 32-� ���������, ��
 ������������ ��������� �� ������� �����.
 ��������!!!���� ������������ ������� � ���������� �� ����������, ��
 ������� ���������� 0 (��� ����� ����������� �����������). */
extern Uint16 * co_getAddr(TCo_OdVars* ppc, Uint32 ind_subind);
// ������� ��������� ���������� �� ������� � �������� �������.
// ���������� 0, ���� ������ �� ������.
extern Uint16 co_getObjectInfo(
 TCo_OdVars* ppc,           // ��������� �� ��������� ������������� ������ CANopen
 Uint32 ind_subind,         // ���� 16-31 - ������, ���� 0-7 - ��������� �������
 TObjectInfo* pObjectInfo   // ��������� �� ���������, ���� ����� �������� ���������� �� �������
 );

extern void co_RPDO1_Callback(Uint16 nodeID, Uint16 tag_CANnum);
extern void co_RPDO2_Callback(Uint16 nodeID, Uint16 tag_CANnum);
extern void co_RPDO3_Callback(Uint16 nodeID, Uint16 tag_CANnum);
extern void co_RPDO4_Callback(Uint16 nodeID, Uint16 tag_CANnum);
extern void co_RPDO5_Callback(Uint16 nodeID, Uint16 tag_CANnum);
extern void co_RPDO6_Callback(Uint16 nodeID, Uint16 tag_CANnum);
extern void co_RPDO7_Callback(Uint16 nodeID, Uint16 tag_CANnum);
extern void co_RPDO8_Callback(Uint16 nodeID, Uint16 tag_CANnum);


//������� ������������, ������������ ��������, ��� ����� ����� ������ ����������� 
//������� ������� ��������
extern void CANBlockTransferInitTX(TCo_OdVars* ppc, Uint16 size, Uint16* source_ptr);
extern void CANBlockTransferInitRX(TCo_OdVars* ppc, Uint16 size, Uint16* dest_ptr);


#ifdef __cplusplus
}
#endif


#endif


/*@}*/

