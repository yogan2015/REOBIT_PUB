/*!
 \file      v_data_log.c
 \brief     4-� ��������� ������ ��� ������������������� � �������� ������� TDataLog (��. TDataLog)

 \author	��������� ��� ��� ������
 \version   v 2.01 18/09/2012
 */

/** \addtogroup v_data_log */
/*@{*/

#include "DSP.h"
#include "co_ODvars.h"
#include "V_data_log.h"
#include "CANOpen_drv.h"

//! ������� ����������.

/*! �������� � ����. ����� ��� ��������� ������� ���������� ����� CAN.
 ���� ��� CAN, ����� �������� ������ ������ ������� � TDataLog.dlog_iptr  */
//! \memberof TDataLog
void dlog_background_analizer(TDataLog *p) {
	//������� ����� ����������� �� % � �����
	p->trig_shift_int = (p->trig_shift&0xFFFFFF)>>16;	//������ ���������� �����
	if (p->trig_shift_int > 255)	//���������
		p->trig_shift_int = 255;

	unsigned char mode;

	//���� �� ����� ���� ���� �� ������ ����� ��� control,
	//�� ������ ������������� � ������ �� ����
	if (!(p->control & 0x3F))
		return;
	//� ����� ������ ����� ����� �����������
	//�������� ����������. ����� �� ����� ������ ���������� ������ �� ����������,
	//���� ���, � ����, ����, ������, ������ �������.
	//� ����� � ������ ������ ����� ���� �� ������, � ������ - ������� �����������
	//��� ��������� �� ������������� ������.
	p->mode_reset = 0;
	p->valid_points_num = 0;	//�.�. ���������� �������������� (mode = 0), �� ����������� �����������, �.�.
								//1) �� ����� ����� ����������� ����� ���������� ������������ � ������ ������� ����� ������ �� ������� �
								//2) ��������� ������������ ���������� ������ ����� ��������� � ����������� ��������� �� ������, � ����� ������ - �� �����
	//���������� ������ � �������� CANopen
#if DLOG_DATA_SIZE == 16
	if (p->control & 1)
		if (!(p->dlog_iptr1 = (type_data*)co_getAddr(p->pco_vars, p->ind_subind1))) //���� �����=0
			p->dlog_iptr1 = (type_data*)&p->ind_subind1; //����� ��������� �� ind_subind
	if (p->control & 2)
		if (!(p->dlog_iptr2 = (type_data*)co_getAddr(p->pco_vars, p->ind_subind2)))
			p->dlog_iptr2 = (type_data*)&p->ind_subind2;
	if (p->control & 4)
		if (!(p->dlog_iptr3 = (type_data*)co_getAddr(p->pco_vars, p->ind_subind3)))
			p->dlog_iptr3 = (type_data*)&p->ind_subind3;
	if (p->control & 8)
		if (!(p->dlog_iptr4 = (type_data*)co_getAddr(p->pco_vars, p->ind_subind4)))
			p->dlog_iptr4 = (type_data*)&p->ind_subind4;
#endif
#if DLOG_DATA_SIZE == 32
	if (p->control & 1)
	{
		if (co_getObjectInfo(p->pco_vars, p->ind_subind1, (TObjectInfo*)&p->object1Info) == 0)
		{
			p->object1Info.varAddr = (void*)(&p->ind_subind1);
			p->object1Info.varSize = 32;
		}
	}
	if (p->control & 2)
	{
		if (co_getObjectInfo(p->pco_vars, p->ind_subind2, (TObjectInfo*)&p->object2Info) == 0)
		{
			p->object2Info.varAddr = (void*)(&p->ind_subind2);
			p->object2Info.varSize = 32;
		}
	}
	if (p->control & 4)
	{
		if (co_getObjectInfo(p->pco_vars, p->ind_subind3, (TObjectInfo*)&p->object3Info) == 0)
		{
			p->object3Info.varAddr = (void*)(&p->ind_subind3);
			p->object3Info.varSize = 32;
		}
	}
	if (p->control & 8)
	{
		if (co_getObjectInfo(p->pco_vars, p->ind_subind4, (TObjectInfo*)&p->object4Info) == 0)
		{
			p->object4Info.varAddr = (void*)(&p->ind_subind4);
			p->object4Info.varSize = 32;
		}
	}
	p->highPartOfValue = 0;
#endif
	p->WriteDelimiter = (p->control >> 16) & 0xFF; //������������. �������������� 8� ������
	mode = (p->control >> 4) & 3; //����� - 2 ����
	p->control = 0; //��� ����������, ��������, ����� ��� ����. ������ �� ������ ������������ �����
	dlog_set_mode(mode, p); //��� ��������� ������ ���������� ����. �������. �������� ������

}

//! ������� ��� ��������� mode_reset.

//! �������������� ��� ���������� �������� �� ������ �������
//! ��������� mode_reset �� ���������� � �������� ��������
//! \memberof TDataLog

void dlog_set_mode(Uint16 mode_reset, TDataLog *p) {
	if (mode_reset > 3)
		return;
	//� 1 ��������� ������ ���� ������� ����� 2, ���� ������������������
	//�� ������� ������� (����� ������� ����� ������� �����)
	if (p->OneShotOperation == 1) {
		if ((mode_reset == 1)) {
			if (p->mode_reset == 2)
				p->mode_reset = mode_reset;
			else
				return;
		}
	} else
		p->mode_reset = mode_reset;

	if (mode_reset == 3)	//����� ������� � ����� ����������� ������ 1024 �����.
		p->Wcounter = 0;	//� ���� ������ ����� ������ � ������ ����� ������� �������. ���������� �������.


	//��� ����� ������ � ����� ������ ���������� ���� "������ ������"
	p->control &= ~(1 << 6);
	p->WriteDelimiterCounter = 0;
#if DLOG_DATA_SIZE == 32
	p->highPartOfValue = 0;
#endif
}

//! ���������� ��������� ����� � ������� �������������.

//!������ ���������� � �������� �������������� � ���������� ������� ��������,
//! �.�. ��������������� ��������������������. ����� ���������� ������
//! � ������� ��-������� � ����������� �� ���������� ������ ������ ������������
//! \memberof TDataLog

void data_log_update(TDataLog *p) {
//����� ����������� p-> , � �� p* - ��� �������

//������������ ������. ���� �� �������� ������� WriteDelimiter, �������
//WriteDelimiter=1 - �� �����
//WriteDelimiter=2 - ����� ������ ������
	if ((p->WriteDelimiterCounter++ + 1) < p->WriteDelimiter)
		return;
	else
		p->WriteDelimiterCounter = 0;

	if (p->mode_reset != p->mode_reset_prev) p->E=1;
    else p->E=0;
	p->mode_reset_prev = p->mode_reset;

	switch (p->mode_reset) {
	case 0: {
		p->Wcounter = 0;
		return;
	}

	case 1:  //����������� ������ - ����� �� ����� � ���� (����� 0)
	{
		//��� ����� � ����� �������� ����� ������������ �������� (��� ������� Wcounter, � ������� �� ���� �����) � ������������ ������ �����, ����������� � ������ ���� (������ �� ������� ����� � �������� ����� �����������)
        if (p->E==1)
        {
        	p->prehistory_length = p->valid_points_num;		//����� ����������� ����� ���������� �������� �����
        	if (p->prehistory_length > p->trig_shift_int)	//���� ����������� ������� ���������, ���������
        		p->prehistory_length = p->trig_shift_int;
#if DLOG_DATA_SIZE == 16
        	p->Wcounter &= 0xFE;
        	p->prehistory_length &= 0xFE;
        	p->first_point_written = (p->Wcounter - p->prehistory_length) & 0xFE;
#endif
#if DLOG_DATA_SIZE == 32
        	p->first_point_written = (p->Wcounter - p->prehistory_length) & 0xFF;
        	p->highPartOfValue = 0;
#endif
        }
		p->Wcounter &= 0xFF; //������ - ���� ����� � counter �� �������� ��������
#if DLOG_DATA_SIZE == 16
		p->dl_buffer1_adr[p->Wcounter] = *p->dlog_iptr1;
		p->dl_buffer2_adr[p->Wcounter] = *p->dlog_iptr2;
		p->dl_buffer3_adr[p->Wcounter] = *p->dlog_iptr3;
		p->dl_buffer4_adr[p->Wcounter] = *p->dlog_iptr4;
#endif
#if DLOG_DATA_SIZE == 32
		p->dl_buffer1_adr[p->Wcounter] = p->object1Info.varSize == 16 ?
			*((int16*)p->object1Info.varAddr) : *((int32*)p->object1Info.varAddr);
		p->dl_buffer2_adr[p->Wcounter] = p->object2Info.varSize == 16 ?
			*((int16*)p->object2Info.varAddr) : *((int32*)p->object2Info.varAddr);
		p->dl_buffer3_adr[p->Wcounter] = p->object3Info.varSize == 16 ?
			*((int16*)p->object3Info.varAddr) : *((int32*)p->object3Info.varAddr);
		p->dl_buffer4_adr[p->Wcounter] = p->object4Info.varSize == 16 ?
			*((int16*)p->object4Info.varAddr) : *((int32*)p->object4Info.varAddr);
#endif
		p->Wcounter++;
		p->Wcounter &= 0xFF;  //���� ������ 256 �����, ���������
		if (p->Wcounter == p->first_point_written)  //���� ����� �� ��������� ������������ �����
		{
			p->mode_reset = 0;                 //����� ����

	#if DLOG_DATA_SIZE == 16
			p->control |= 192;				// "������ ������" + "�������������� ������� ��������"
	#else
			p->control |= 192 | (1 << 8);	// "������ ������" + "�������������� ������� ��������" + "32-������ ������"
	#endif

		}
		return;
	}

	case 2: //���������� ��� �� �����
	{
		if (p->E == 1)
		{
#if DLOG_DATA_SIZE == 32
        	p->highPartOfValue = 0;
#endif
		}
		p->valid_points_num++;	//������� ���������� ���������� �������� ����� �����������
		if (p->valid_points_num > 256)	//������������
			p->valid_points_num = 256;
		p->Wcounter &= 0xFF; //������ - ���� ����� � counter �� �������� ��������
#if DLOG_DATA_SIZE == 16
		p->dl_buffer1_adr[p->Wcounter] = *p->dlog_iptr1;
		p->dl_buffer2_adr[p->Wcounter] = *p->dlog_iptr2;
		p->dl_buffer3_adr[p->Wcounter] = *p->dlog_iptr3;
		p->dl_buffer4_adr[p->Wcounter] = *p->dlog_iptr4;
#endif
#if DLOG_DATA_SIZE == 32
		p->dl_buffer1_adr[p->Wcounter] = p->object1Info.varSize == 16 ?
			*((int16*)p->object1Info.varAddr) : *((int32*)p->object1Info.varAddr);
		p->dl_buffer2_adr[p->Wcounter] = p->object2Info.varSize == 16 ?
			*((int16*)p->object2Info.varAddr) : *((int32*)p->object2Info.varAddr);
		p->dl_buffer3_adr[p->Wcounter] = p->object3Info.varSize == 16 ?
			*((int16*)p->object3Info.varAddr) : *((int32*)p->object3Info.varAddr);
		p->dl_buffer4_adr[p->Wcounter] = p->object4Info.varSize == 16 ?
			*((int16*)p->object4Info.varAddr) : *((int32*)p->object4Info.varAddr);
#endif
		p->Wcounter++;
		p->Wcounter &= 0xFF;  //���� ������ 256 �����, ���������
		return;
	}

	case 3: //����� ����������� ������ 1024 �����
	{
        if (p->E==1)
        {
        	p->first_point_written = 0;		//����� � ������ �����, ����������� �� �����.
#if DLOG_DATA_SIZE == 32
        	p->highPartOfValue = 0;
#endif
        }
		//� ������ ����, ��� ������ � ������ ����������� ���������������,
		//���������� � ������, "�������" �� ��������� ���
#if DLOG_DATA_SIZE == 16
		p->dl_buffer1_adr[p->Wcounter] = *p->dlog_iptr1;
#endif
#if DLOG_DATA_SIZE == 32
		p->dl_buffer1_adr[p->Wcounter] = p->object1Info.varSize == 16 ?
			*((int16*)p->object1Info.varAddr) : *((int32*)p->object1Info.varAddr);
#endif
		p->Wcounter++;
		if (p->Wcounter >= 1024)  //���� ����� �� �����
		{
			p->mode_reset = 0;                 //����� ����

	#if DLOG_DATA_SIZE == 16
			p->control |= 192;				// "������ ������" + "�������������� ������� ��������"
	#else
			p->control |= 192 | (1 << 8);	// "������ ������" + "�������������� ������� ��������" + "32-������ ������"
	#endif

		}
		return;
	}
	}
}

/*@}*/

