/*!
    Copyright 2017  �� "�����" � ��� "��� ������"

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

 \file    SMCtrl.c
 \brief   �������� �� ������������ ������ ���������� (��. TSM_Ctrl)
 \author    ��� "��� ������". http://motorcontrol.ru
 \version   v 2.0 25/03/2016
 
 */

/** \addtogroup SMCtrl */
/*@{*/

#include "DSP.h"
#include "V_IQmath.h"
#include "main.h"


//!�������������
//!������ ���������
//! \memberof TSM_Ctrl
void SM_Ctrl_Init(TSM_Ctrl *p) {
    p->state_prev = 0xff;
    p->state = 0x00;
}

//!������� ������

//! \memberof TSM_Ctrl
void SM_Ctrl_Slow_Calc(TSM_Ctrl *p) {

}

//!�������������� ������

//! \memberof TSM_Ctrl
void SM_Ctrl_ms_Calc(TSM_Ctrl *p) {

}

//!������� ������

//!��������� ��� ��������� ���������� (������ ������), ����� ��� 
//!��������� ����������, ���������, ����� ����������� ���� � �.�.
//!����� ���������� �������� �� ������������ ������ ����������.
//!����� ����, ���������� ������ ��������� ��������������� �������.
//!����� �������, ����� ��������� "����" ���� ������� ����������,
//!� ������ � ���� ������� ���������� ���������������� ���������� ���������� �
//!�������������� ���� ��������� �������.

//! \memberof TSM_Ctrl
void SM_Ctrl_Fast_Calc(TSM_Ctrl *p) {
    long Temp1;

//���� ������� ��������� � ������������������,
//�� ���������� ������ ����������
    if (sm_sys.state == SYS_INIT) {
        return;
    }

//���� ������� ����������, �� ���������
//� ����� ����������
    if (cmd.bit.stop == 1)
        p->state = CTRL_STOP;
// ���� ���� ������, �� ��������� � ����
    if (sm_prot.state == PROT_FAIL)
        p->state = CTRL_STOP;

//������� ���������� �������
    if (p->state_prev != p->state)
        p->E = 1;
    else
        p->E = 0;
//����� ��� ����������� ��������, �����������
//������� ���������
    p->state_prev = p->state;

    switch (p->state) {
    case CTRL_STOP: { //��������� �������
        if (p->E == 1) { //���� ������ ��������� � ���������
            cmd.bit.start = 0;
            DPReCAP.speed = 0;
            DPReCAP.Ts = 0;
            DPReCAP.Tspeed = 0;
            global_time.WtiteSPI_flag = 1;    //�������� ����� ������
            //��� �������� � ���� � ����������
            //������������ ��������� ��� � �����
            //����������� ������, ����� ��������. ��������� ������.
            if (dlog.StartBits & (1 << 8))    //���� ������������ ����� ���� ���
                dlog.set_mode(1, &dlog); //��������� ����������� �� ����� �������

            if (sm_prot.state==PROT_FAIL)//���� �� ������� � ����, � ������ ����� � ������
                if (dlog.mode_reset==2)//� ���������� ��������
                    dlog.mode_reset=1;//�� ��������� ���, ����� ����� ���� ������
        }
        pwm.Off(&pwm);            //���� ���
        //   refs.theta_elec=0;

        //��������� ����� ��������
        pwm.UalphaRef = 0;
        pwm.UbetaRef = 0;
        pwm.update(&pwm);
        pid_id.reset(&pid_id);
        pid_iq.reset(&pid_iq);
        pid_ia.reset(&pid_ia);
        pid_spd.reset(&pid_spd);
        pid_pos.reset(&pid_pos);
        cur_par.Is = 0;
        cur_par.power = 0;
        cur_par.speed = 0;
        //  cur_par.ThetaRefCurr=0;

        /* ����� */
        break;
    }

    case CTRL_RUN: {     //��������� �������
        if (p->E == 1) {
            /*ENTRY START*/
            drv_status.bit.running = 1;
            pwm.On(&pwm);//��������� ������ ���
            p->ctrl_counter = 0;
            if (dlog.StartBits & (1 << 0))    //���� ������������ ����� ���� ���
                dlog.set_mode(1, &dlog); //��������� ����������� �� ����� �������
            /*ENTRY END*/
        }
        /*DO START*/

        p->ctrl_counter++;

        if (p->ctrl_counter < 100) { //�������� 10 �� ��� ������ ����������� �������
            pwm.ChargingMode = 1;//����. ����� ������ �������������
            pwm.update(&pwm);
            break;
        }
        pwm.ChargingMode = 0;

        if (p->run_mode == CTRL_RUN_U2F) {//��������� �����
            p->state = CTRL_RUN_U2F;
        }
        if (p->run_mode == CTRL_FLUXING) {//����� ��������� (���������� ���)
            p->state = CTRL_FLUXING;
        }
        if (p->run_mode == CTRL_RUN_I2F) {//��������-������� ����� (�������� ������� ����)
            p->state = CTRL_RUN_I2F;
        }
        if (p->run_mode == CTRL_RUN_VECTOR_SM) {//��������� �� ���������� ������ � ����� ���������
            p->state = CTRL_RUN_VECTOR_SM;
        }
        if (p->run_mode == CTRL_RUN_VECTOR_SM_ENCODER_POS) {//��������� �� ���������� ������  � �������� ������ �� �������� � �������� ���������
            p->state = CTRL_RUN_VECTOR_SM_ENCODER_POS;
        }
        if (p->run_mode == CTRL_RUN_VECTOR_IM_ENCODER) {//��������� �� ���������� ������  � �������� ������ �� �������� � �������� ���������
            p->state = CTRL_RUN_VECTOR_IM_ENCODER;
        }
        if (p->run_mode == CTRL_RUN_VECTOR_IM_ENCODER_POS) {//��������� �� ���������� ������  � �������� ������ �� �������� � �������� ���������
            p->state = CTRL_RUN_VECTOR_IM_ENCODER_POS;
        }
        if (p->run_mode == CTRL_AUTO_SENSOR_TUNING) {//�������������� ��������� �������� � ��� (��������-�������+���. ������)
            p->state = CTRL_AUTO_SENSOR_TUNING;
        }
        if (p->run_mode == CTRL_DC_DRIVE) {// ���
            p->state = CTRL_DC_DRIVE;
        }
        if (p->run_mode == CTRL_DC_DRIVE_FB) {// ��� �����.
            p->state = CTRL_DC_DRIVE_FB;
        }
        if (p->run_mode == CTRL_RUN_SRM_AUTOCOMMUTATION) { //�������������� SRM
            p->state = CTRL_RUN_SRM_AUTOCOMMUTATION;
        }

        /*DO END*/
        break;
    }

    case CTRL_FLUXING: { //����� ���������� ���
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);
            pid_id.ui_reg3 = 0; //��������� ������������ ������
            pid_iq.ui_reg3 = 0; //����� �� �������������
            pid_spd.ui_reg3 = 0;
            refs.theta_elec = 0;//�������� ���� - 0. �� �� ���� � ������ �������, ��� ����� ������ �� ����!

            if (dlog.StartBits & (1 << 1))
                dlog.set_mode(1, &dlog);
            /*ENTRY END*/
        }
        /*DO START*/

        //��� ���� ��� �� ��� � ������ ������ ��������������
        clarke.as = adc.Imeas_a;
        clarke.bs = adc.Imeas_b;
        clarke.calc(&clarke);//������

        //�� ������ �������������� � ������������ ��������������.
        //������������ ������ �� �������� ���� refs.theta_elec
        park.ds = clarke.ds;
        park.qs = clarke.qs;
        park.ang = refs.theta_elec;
        park.calc(&park);

        //��������� ���� "��� ��" ��� d (�� ����� ���� ��� ��� � ��������� � ��� d �� ���������, ��� ��������� ���)
        pid_id.pid_ref_reg3 = refs.i_flux_ref; //������� �� ��� ��������������
        pid_id.pid_fdb_reg3 = park.de;//�������� ����� - �� ��� ������ � ������ ��������������
        pid_id.calc(&pid_id);

        //��������� ���� "��� ��" ��� q (�� ����� ���� ��� ��� � ��������� � ��� q �� ���������, ��� ��������� ���)
        pid_iq.pid_ref_reg3 = 0;//������� - ����
        pid_iq.pid_fdb_reg3 = park.qe;//�������� ����� - �� ��� ������ � ������ ��������������
        pid_iq.calc(&pid_iq);

        //�������� ������ ��������������.
        //������ ������ ����������, ������� ������ ���������� ����� ������� �� ���� refs.theta_elec
        ipark.de = pid_id.pid_out_reg3;
        ipark.qe = pid_iq.pid_out_reg3;
        ipark.ang = refs.theta_elec;
        ipark.calc(&ipark);

        //������������ ������� ���������� �� ���� ����� � ���� ���������� �� ������ ���
        pwm.UalphaRef = ipark.ds;
        pwm.UbetaRef = ipark.qs;
        pwm.update(&pwm);

        //� ����������� ���������� - ������� ����������� ��� � ������� (�������� ����� ���������� d)
        cur_par.Is = pid_id.pid_fdb_reg3;

        break;
    }

    case CTRL_RUN_U2F: { //����� ��������� ���������� U(f)
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);
            rmp.output = 0;

            if (dlog.StartBits & (1 << 2)) //���� ������������ ����� ���� ��� �������������������
                dlog.set_mode(1, &dlog); //��������� ����������� �� ����� �������

            /*ENTRY END*/
        }
        /*DO START*/
        //������� �������� �� ���� ��������� �������������
        rmp.input = refs.speed_ref;
        rmp.calc(&rmp);//������ ���������
        cur_par.speed = rmp.output; //�������� (������� ��������) ���������� � ���������� ����������, ������� ������

        //���� refs.theta_elec - �������� �� �������� rmp.output.
        //��������� FAST_CALC_TS - ������ �������������
        //drv_params.freq_nom ����������� ������� (������� �������� ������� ��� ������������� ������ ���������)
        refs.theta_elec += _IQmpy(_IQmpyI32(drv_params.freq_nom,FAST_CALC_TS),
                rmp.output);
        refs.theta_elec &= 0x00FFFFFF; //��������� ������ ������� �����, ���� ���� ������ ������� � IQ (360 ��������)
        //�� ���� ������ U/f �������� ������� �������� (�������)
        vhz.freq = rmp.output;
        vhz.calc(&vhz);

        //� ������ ������������ ������������� ������ �������� ��������� ���������� vhz.vout � ������ U/f
        //���������� ������ �������������� ��� "��������" ������� ����������
        ipark.de = vhz.vout;
        ipark.qe = 0;
        ipark.ang = refs.theta_elec;
        ipark.calc(&ipark);

        //������������ ������� ���������� �� ���� ����� � ���� ���������� �� ������ ���
        pwm.UalphaRef = ipark.ds;
        pwm.UbetaRef = ipark.qs;
        pwm.update(&pwm);

        /*DO END*/
        break;
    }

    case CTRL_RUN_I2F: { //����� ��������-�������� ���������� - ����������� ������ ����.
        if (p->E == 1) {
            /*ENTRY START*/
            pid_id.ui_reg3 = 0; //��������� ������������ ������
            pid_iq.ui_reg3 = 0; //����� �� �������������
            pid_spd.ui_reg3 = 0;
            pid_id.pid_ref_reg3 = 0;
            pid_iq.pid_ref_reg3 = 0;

            pwm.On(&pwm);//�������� ���
            rmp.output = 0;
            if (dlog.StartBits & (1 << 3))
                dlog.set_mode(1, &dlog);
            /*ENTRY END*/
        }
        /*DO START*/
        {

            //��� ���� ��� �� ��� � ������ ������ ��������������
            clarke.as = adc.Imeas_a;
            clarke.bs = adc.Imeas_b;
            clarke.calc(&clarke);

            //������� ������ ���� - � ����������� ��������� (����� �� ���� ��������)
            cur_par.Ialpha = clarke.ds;
            cur_par.Ibeta = clarke.qs;

            //������� �������� �� ���� ��������� �������������
            rmp.input = refs.speed_ref;
            rmp.calc(&rmp);//������ ���������

            //���� refs.theta_elec - �������� �� �������� rmp.output.
            //��������� FAST_CALC_TS - ������ �������������
            //drv_params.freq_nom ����������� ������� (������� �������� ������� ��� ������������� ������ ���������)
            refs.theta_elec += _IQmpy(
                    _IQmpyI32(drv_params.freq_nom,FAST_CALC_TS), rmp.output);
            cur_par.ThetaRefCurr = refs.theta_elec;
            refs.theta_elec &= 0x00FFFFFF;//��������� ������ ������� �����, ���� ���� ������ ������� � IQ (360 ��������)

            //������� ���� � ������� ���������, ������������ � ������������� �� �������������
            //cur_par.ThetaCurr = posspeedEqep.theta_elecContinouos;

            //������� ���� - �������� ����
            cur_par.ThetaCurr = refs.theta_elec;

            //�� ������ �������������� � ������������ ��������������.
            //������������ ������ �� �������� ���� refs.theta_elec
            park.ds = clarke.ds;
            park.qs = clarke.qs;
            park.ang = refs.theta_elec;
            park.calc(&park);

            //��������� ���� "��� ��" ��� d (�� ����� ���� ��� ��� � ��������� � ��� d �� ���������, ��� ��������� ���)
            pid_id.pid_ref_reg3 = refs.i_flux_ref;
            pid_id.pid_fdb_reg3 = park.de;
            pid_id.calc(&pid_id);

            //��������� ���� "��� ��" ��� q (�� ����� ���� ��� ��� � ��������� � ��� q �� ���������, ��� ��������� ���)
            pid_iq.pid_ref_reg3 = 0;
            pid_iq.pid_fdb_reg3 = park.qe;
            pid_iq.calc(&pid_iq);

            //�������� ������ ��������������.
            //������ ������ ����������, ������� ������ ���������� ����� ������� �� ���� refs.theta_elec
            ipark.de = pid_id.pid_out_reg3;
            ipark.qe = pid_iq.pid_out_reg3;
            ipark.ang = refs.theta_elec;
            ipark.calc(&ipark);

            //������������ ������� ���������� �� ���� ����� � ���� ���������� �� ������ ���
            pwm.UalphaRef = ipark.ds;
            pwm.UbetaRef = ipark.qs;
            pwm.update(&pwm);

            //� ����������� ���������� - ������� ����������� ��� � ������� (�������� ����� ���������� d)
            cur_par.Is = pid_id.pid_fdb_reg3;
            //� ������� ������� (��������)
            cur_par.speed = rmp.output;

            if (sw.excitation_ena)
            {
                pwm_ex.ref = refs.uf_ref;
                pwm_ex.calc(&pwm_ex);
            }

            /*DO END*/
        }
        break;
    }

    case CTRL_RUN_VECTOR_SM: {            //���������� �� ��� ���������� ������
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);            //��������� ���
            rmp.output = 0;            //��������� ��������� �������������
            if (dlog.StartBits & (1 << 4)) //���� ������������ ����� ���� ��� �������������������
                dlog.set_mode(1, &dlog);  //������ ������������ �� ����� �������
            /*ENTRY END*/
        }
        /*DO START*/
        {
            if (drv_params.sens_type == POS_SENSOR_TYPE_HALL){  //� ���� ������� ������ ��� �� ��������� �����
                cur_par.speed = DPReCAP.speed; //������� �������� - � ���
                refs.theta_elec = DPReCAP.Angle; //������� ������� ��������� - � ���
            }
            if (drv_params.sens_type == POS_SENSOR_TYPE_ENCODER){  //� ���� ������� ������ ��� �� ��������� �����
                cur_par.speed = posspeedEqep.speed_elec; //������� �������� - � ���
                refs.theta_elec = posspeedEqep.theta_elec; //������� ������� ��������� - � ���
            }
            if (drv_params.sens_type == POS_SENSOR_TYPE_SSI){  //� ���� ������� ������ ��� �������� � SSI �����������
                cur_par.speed = SSI_Encoder.speed_elec; //������� �������� - � ���
                refs.theta_elec = SSI_Encoder.theta_elec; //������� ������� ��������� - � ���
            }

            cur_par.Is = pid_iq.pid_fdb_reg3; //������� ��� ������� - ��� �� ��� q

            //�������������� ����� �� ���������� ������� ��������� � ����������
            clarke.as = adc.Imeas_a;
            clarke.bs = adc.Imeas_b;
            clarke.calc(&clarke);
            cur_par.Ialpha = clarke.ds;
            cur_par.Ibeta = clarke.qs;

            // ������� �������� �� ��������� ������������� (��)
            rmp.input = refs.speed_ref;
            rmp.calc(&rmp);//������ ��

            pid_spd.pid_ref_reg3 = rmp.output; //�� ����� ���������� �������� - ����� ��
            pid_spd.pid_fdb_reg3 = cur_par.speed; //�������� ����� ���������� �������� - �������� ���


            pid_spd.pid_out_max = refs.Iq_ref; //�������� ������ ���������� �������� - �������� ���

            if (sw.recuperation_ena & 1)            //���� ��������� �����������
                pid_spd.pid_out_min = -refs.Iq_ref; //������� ���. ����. - ������������� ���
            else
                //�����
                pid_spd.pid_out_min = 0; //������� ��� �� ���� ���������� ��� �������� � ������������� �������
            pid_spd.calc(&pid_spd); //������ ���������� ��������


            cur_par.ThetaRefCurr = refs.theta_elec;
            refs.theta_elec &= 0x00FFFFFF; //����������� ���� �� 1.0 � ������� 8.24

            //������� ����� ��� �� ���� refs.theta_elec
            park.ds = clarke.ds;
            park.qs = clarke.qs;
            park.ang = refs.theta_elec;
            park.calc(&park); //������ �������������� ���������

            //������� ���. ���� �� ��� q (��� �������) - ����� ���������� ��������
            pid_iq.pid_ref_reg3 = pid_spd.pid_out_reg3;
            pid_iq.pid_fdb_reg3 = park.qe; //�������� ����� ���. ���� ��� q - ����������� ��� �� ���� q
            pid_iq.calc(&pid_iq); //������ ���������� ���� ��� q

            pid_id.pid_ref_reg3 = 0; //������� ���� �� ��� d - ��� ����������
            pid_id.pid_fdb_reg3 = park.de; //�������� ����� ���. ���� ��� d - ����������� ��� �� ���� d
            pid_id.calc(&pid_id); //������ ���������� ���� ��� d

            //�������� ������� �� ���� refs.theta_elec ���
            //������� ����������� ���� (���������� �� ���� d � q)
            ipark.de = pid_id.pid_out_reg3;
            ipark.qe = pid_iq.pid_out_reg3;
            ipark.ang = refs.theta_elec;
            ipark.calc(&ipark);            //������ �������������� ���������

            //������� ���������� �� ������ ��� ����� �������������� ���������
            pwm.UalphaRef = ipark.ds;            //��� �����
            pwm.UbetaRef = ipark.qs;            //��� ����
            pwm.update(&pwm);            //������ ������ ���

            if (sw.excitation_ena)
            {
                pwm_ex.ref = refs.uf_ref;
                pwm_ex.calc(&pwm_ex);
            }

            /*DO END*/
        }
        break;
    }

    case CTRL_RUN_VECTOR_SM_ENCODER_POS: {            //���������� �� � ��������� � � �������� ���������
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);            //��������� ���
            rmp.output = 0;            //��������� ��������� �������������
            if (dlog.StartBits & (1 << 4)) //���� ������������ ����� ���� ��� �������������������
                dlog.set_mode(1, &dlog);  //������ ������������ �� ����� �������
            /*ENTRY END*/
        }
        /*DO START*/
        {
            cur_par.Is = pid_iq.pid_fdb_reg3; //������� ��� ������� - ��� �� ��� q
            cur_par.speed = posspeedEqep.speed_elec; //������� �������� - � ��� �������������

            //�������������� ����� �� ���������� ������� ��������� � ����������
            clarke.as = adc.Imeas_a;
            clarke.bs = adc.Imeas_b;
            clarke.calc(&clarke);
            cur_par.Ialpha = clarke.ds;
            cur_par.Ibeta = clarke.qs;


/*          //��� ����-������ ������� ��������� ������� ������� ���������, ������������� �� ������
            //��� ������ ������ ������� - ����� ����������� �� ���������� ��� ������� DebugW1

            if (DebugW1!=0){//���� �����-�� �������� �������� ������
                p->AngleDemo+=(DebugW1>>10);//�������������� ����������
                if (p->AngleDemo>_IQ(2))//������ ����� 2, ��� � �.�. ���� 360*2 ��������
                    p->AngleDemo=0;

                //������� ���� � ������ ���������
                //����� ����� ����� �� ������� ��������������� ����������, �� ��� � � 4 ���� ��������
                refs.theta_elec=_IQsinPU(p->AngleDemo)<<2;
            }
*/

            /*
//������ ����-����� ������� ��������� - �������� ��������� �� ��������� �������, ����������� �������� � ����������� SSI
//��� ������ ������� ��� �����, ����������, ���������� (� �������� �������� �� ������!),
//� ����� ������� ��� � ����������

#define REVOLUTION_DROP_NUMBER 3
            //����� ����� ���� ������� ������������� � ���� ������� � �� ������������� ���������� �� ���������
            //�� ����� ������ ���� ��������� 100500 �������� ������ ������� � �� ������ �� ������ � ������
            //��������� ������������ ����������� � �������� ������ REVOLUTION_DROP_NUMBER
            if (labs(SSI_Encoder.RevolutionCounter-posspeedEqep.RevolutionCounter)>REVOLUTION_DROP_NUMBER){
                if (posspeedEqep.RevolutionCounter>SSI_Encoder.RevolutionCounter){
                    posspeedEqep.RevolutionCounter=SSI_Encoder.RevolutionCounter+REVOLUTION_DROP_NUMBER;
                }
                if (SSI_Encoder.RevolutionCounter>posspeedEqep.RevolutionCounter){
                    SSI_Encoder.RevolutionCounter=posspeedEqep.RevolutionCounter+REVOLUTION_DROP_NUMBER;
                }
            }
            if ((posspeedEqep.RevolutionCounter>10) || (SSI_Encoder.RevolutionCounter>10)){
                posspeedEqep.RevolutionCounter-=10;
                SSI_Encoder.RevolutionCounter-=10;
            }
            if ((posspeedEqep.RevolutionCounter<-10) || (SSI_Encoder.RevolutionCounter<-10)){
                posspeedEqep.RevolutionCounter+=10;
                SSI_Encoder.RevolutionCounter+=10;
            }

            //������� ���� - �� SSI ��������
            refs.theta_elec=SSI_Encoder.theta_elecContinouos;
*/


            //������� ���� � ������� ���������, ������������ � ������������� �� �������������
            cur_par.ThetaCurr = posspeedEqep.theta_elecContinouos;
            cur_par.ThetaRefCurr=refs.theta_elec;//�������� ���� ������������� (������������ � ��� ���������� ������� ��� �������� ����������)

            //������ - ������� ����� �������� � ������� �����. ��� ������� ������ ��������� ������ ��� ����������,
            //������ � ������ ������ ����� ����� ������� ���������� �����������, ����� � ���������� ������ �� �������������
            long posRefError=refs.theta_elec - cur_par.ThetaCurr;


            //��������� ������ - ����� ��� ������� ���������� ������ ���� �� ���� ������������.
            if (posRefError>_IQ(1))
                posRefError=_IQ(1);
            if (posRefError<-_IQ(1))
                posRefError=-_IQ(1);


            //������ �� ��� ��������� �������� ������� � �������� �����, � ������ ��������� �� �������.
            //�� ������� �� ��������� ���� (� ����������). ������ ����� ������� �� ��������� ����� �� ����� �������,
            //� � �������� ����� ������� ��� ����������� � ������������ ������ (�� ������ �����)
            pid_pos.pid_ref_reg3 = 0;//�������� ������� �� ��������� ���� ����� refs.theta_elec (������ �������)
            pid_pos.pid_fdb_reg3 = -posRefError;//�������� �����
            pid_pos.pid_out_max=refs.speed_ref;//����������� ���. ��������� - �������� ���������� ��������
            pid_pos.pid_out_min=-refs.speed_ref;//� � �����
            pid_pos.saterr_reg3Add=pid_spd.saterr_reg3;//��� ����������. ��������� ��������� ���. �������� � �������� ��� � ���. ���������.
            pid_pos.calc(&pid_pos); //������ ���������� ���������

            pid_spd.pid_ref_reg3 = pid_pos.pid_out_reg3; //�� ���� ���������� �������� - ����� ���. ���������
//          pid_spd.pid_fdb_reg3 = posspeedEqep.speed_filter.output; //�������� ����� ���������� �������� - �������� ���
            pid_spd.pid_fdb_reg3 = cur_par.speed;

            pid_spd.pid_out_max = refs.Iq_ref; //�������� ������ ���������� �������� - �������� ���
            pid_spd.pid_out_min = -refs.Iq_ref; //������� ���. ����. - ������������� ���
            pid_spd.calc(&pid_spd); //������ ���������� ��������


            //������� ����� ��� �� ���� refs.theta_elec
            park.ds = clarke.ds;
            park.qs = clarke.qs;
            park.ang = posspeedEqep.theta_elec;
            park.calc(&park); //������ �������������� ���������

            //������� ���. ���� �� ��� q (��� �������) - ����� ���������� ��������
            pid_iq.pid_ref_reg3 = pid_spd.pid_out_reg3;
            pid_iq.pid_fdb_reg3 = park.qe; //�������� ����� ���. ���� ��� q - ����������� ��� �� ���� q
            pid_iq.calc(&pid_iq); //������ ���������� ���� ��� q

            pid_id.pid_ref_reg3 = 0; //������� ���� �� ��� d - ��� ����������
            pid_id.pid_fdb_reg3 = park.de; //�������� ����� ���. ���� ��� d - ����������� ��� �� ���� d
            pid_id.calc(&pid_id); //������ ���������� ���� ��� d

            //�������� ������� �� ���� refs.theta_elec ���
            //������� ����������� ���� (���������� �� ���� d � q)
            ipark.de = pid_id.pid_out_reg3;
            ipark.qe = pid_iq.pid_out_reg3;
            ipark.ang = posspeedEqep.theta_elec;
            ipark.calc(&ipark);            //������ �������������� ���������

            //������� ���������� �� ������ ��� ����� �������������� ���������
            pwm.UalphaRef = ipark.ds;            //��� �����
            pwm.UbetaRef = ipark.qs;            //��� ����
            pwm.update(&pwm);            //������ ������ ���

            /*DO END*/
        }
        break;
    }


    case CTRL_RUN_VECTOR_IM_ENCODER: { //���������� �� ��� �� � ��������� � �������� ��������
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);            //��������� ���
            RotorObserver.psi_d=0;
            RotorObserver.psi_q=0;
            rmp.output = 0;            //��������� ��������� �������������
            if (dlog.StartBits & (1 << 4)) //���� ������������ ����� ���� ��� �������������������
                dlog.set_mode(1, &dlog);  //������ ������������ �� ����� �������
            /*ENTRY END*/
        }
        /*DO START*/
        {
            cur_par.Is = _IQmag(pid_iq.pid_fdb_reg3,pid_id.pid_fdb_reg3) ; //������� ��� ������� - ��������� �� ����� d � q
            cur_par.speed = posspeedEqep.speed_elec; //posspeedEqep.speed.output;//������� �������� - � ��� �������������

            //�������������� ����� �� ���������� ������� ��������� � ����������
            clarke.as = adc.Imeas_a;
            clarke.bs = adc.Imeas_b;
            clarke.calc(&clarke);
            cur_par.Ialpha = clarke.ds;
            cur_par.Ibeta = clarke.qs;

            // ������� �������� �� ��������� ������������� (��)
            rmp.input = refs.speed_ref;
            rmp.calc(&rmp);//������ ��

            pid_spd.pid_ref_reg3 = rmp.output; //�� ����� ���������� �������� - ����� ��
            pid_spd.pid_fdb_reg3 = posspeedEqep.speed_elec; //�������� ����� ���������� �������� - �������� ���


            pid_spd.pid_out_max = refs.Iq_ref; //�������� ������ ���������� �������� - �������� ���

            if (sw.recuperation_ena & 1)            //���� ��������� �����������
                pid_spd.pid_out_min = -refs.Iq_ref; //������� ���. ����. - ������������� ���
            else
                //�����
                pid_spd.pid_out_min = 0; //������� ��� �� ���� ���������� ��� �������� � ������������� �������
            pid_spd.calc(&pid_spd); //������ ���������� ��������


            //������� ����� ��� �� ���� refs.theta_elec
            park.ds = clarke.ds;
            park.qs = clarke.qs;
            park.ang = posspeedEqep.theta_elec;
            park.calc(&park); //������ �������������� ���������

            RotorObserver.id=park.de;//�� ����������� ������ �� - ���� �������, ���������� �� ���� ����
            RotorObserver.iq=park.qe;
            RotorObserver.calc(&RotorObserver);

            refs.theta_elec = RotorObserver.theta_psi_elec+posspeedEqep.theta_elec; //������� ������� ��������� - � ��� � ����������� ������ (��� x,y)
            refs.theta_elec &= 0x00FFFFFF; //����������� ���� �� 1.0 � ������� 8.24
            cur_par.ThetaRefCurr = refs.theta_elec;


            //������ refs.theta_elec - ���� ��������������� ������. ��������� ��������� ������� �� ���������� ������ ��� ����� ����
            park.ds = clarke.ds;
            park.qs = clarke.qs;
            //������ ��������� - ������� ��� ������������ ����������� �� ������� ��������. ������������� ������ ��� ��� ipark �� ������!
            park.ang = refs.theta_elec;
            park.calc(&park);

            //���������� ����� d, q ������������ ��� ������������� ���� x, y (����� �� ������ ������ ��������)
            //������� ���. ���� �� ��� y (��� �������) - ����� ���������� ��������
            pid_iq.pid_ref_reg3 = pid_spd.pid_out_reg3;
            pid_iq.pid_fdb_reg3 = park.qe; //�������� ����� ���. ���� ��� y - ����������� ��� �� ���� y
            pid_iq.calc(&pid_iq); //������ ���������� ���� ��� y

            pid_id.pid_ref_reg3 = _IQmpy(RotorObserver.FluxCurrentRatio,labs(pid_iq.pid_ref_reg3)); //������� ���� �� ��� x - ��� ����������. ��������������� ��������� ������� ���� �������
            if (pid_id.pid_ref_reg3 < RotorObserver.FluxCurrentMin)
                pid_id.pid_ref_reg3=RotorObserver.FluxCurrentMin;
            pid_id.pid_fdb_reg3 = park.de; //�������� ����� ���. ���� ��� x - ����������� ��� �� ���� x
            pid_id.calc(&pid_id); //������ ���������� ���� ��� x


            //�������� ������� �� ���� refs.theta_elec ���
            //������� ����������� ���� (���������� �� ���� x � y)
            ipark.de = pid_id.pid_out_reg3;
            ipark.qe = pid_iq.pid_out_reg3;
            ipark.ang = refs.theta_elec;
            ipark.calc(&ipark);            //������ �������������� ���������

            //������� ���������� �� ������ ��� ����� �������������� ���������
            pwm.UalphaRef = ipark.ds;            //��� �����
            pwm.UbetaRef = ipark.qs;            //��� ����
            pwm.update(&pwm);            //������ ������ ���

            /*DO END*/
        }
        break;
    }

    case CTRL_RUN_VECTOR_IM_ENCODER_POS: { //���������� �� ��� �� � ��������� � ��������� �������� � ���������
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);            //��������� ���
            RotorObserver.psi_d=0;
            RotorObserver.psi_q=0;
            rmp.output = 0;            //��������� ��������� �������������
            if (dlog.StartBits & (1 << 4)) //���� ������������ ����� ���� ��� �������������������
                dlog.set_mode(1, &dlog);  //������ ������������ �� ����� �������
            /*ENTRY END*/
        }
        /*DO START*/
        {
            cur_par.Is = _IQmag(pid_iq.pid_fdb_reg3,pid_id.pid_fdb_reg3) ; //������� ��� ������� - ��������� �� ����� d � q
            cur_par.speed = posspeedEqep.speed_elec; //posspeedEqep.speed.output;//������� �������� - � ��� �������������

            //�������������� ����� �� ���������� ������� ��������� � ����������
            clarke.as = adc.Imeas_a;
            clarke.bs = adc.Imeas_b;
            clarke.calc(&clarke);
            cur_par.Ialpha = clarke.ds;
            cur_par.Ibeta = clarke.qs;


/*          //��� ����-������ ������� ��������� ������� ������� ���������, ������������� �� ������
            //��� ������ ������ ������� - ����� ����������� �� ���������� ��� ������� DebugW1

            if (DebugW1!=0){//���� �����-�� �������� �������� ������
                p->AngleDemo+=(DebugW1>>10);//�������������� ����������
                if (p->AngleDemo>_IQ(2))//������ ����� 2, ��� � �.�. ���� 360*2 ��������
                    p->AngleDemo=0;

                //������� ���� � ������ ���������
                //����� ����� ����� �� ������� ��������������� ����������, �� ��� � � 4 ���� ��������
                refs.theta_elec=_IQsinPU(p->AngleDemo)<<2;
            }
*/

            /*
//������ ����-����� ������� ��������� - �������� ��������� �� ��������� �������, ����������� �������� � ����������� SSI
//��� ������ ������� ��� �����, ����������, ���������� (� �������� �������� �� ������!),
//� ����� ������� ��� � ����������

#define REVOLUTION_DROP_NUMBER 3
            //����� ����� ���� ������� ������������� � ���� ������� � �� ������������� ���������� �� ���������
            //�� ����� ������ ���� ��������� 100500 �������� ������ ������� � �� ������ �� ������ � ������
            //��������� ������������ ����������� � �������� ������ REVOLUTION_DROP_NUMBER
            if (labs(SSI_Encoder.RevolutionCounter-posspeedEqep.RevolutionCounter)>REVOLUTION_DROP_NUMBER){
                if (posspeedEqep.RevolutionCounter>SSI_Encoder.RevolutionCounter){
                    posspeedEqep.RevolutionCounter=SSI_Encoder.RevolutionCounter+REVOLUTION_DROP_NUMBER;
                }
                if (SSI_Encoder.RevolutionCounter>posspeedEqep.RevolutionCounter){
                    SSI_Encoder.RevolutionCounter=posspeedEqep.RevolutionCounter+REVOLUTION_DROP_NUMBER;
                }
            }
            if ((posspeedEqep.RevolutionCounter>10) || (SSI_Encoder.RevolutionCounter>10)){
                posspeedEqep.RevolutionCounter-=10;
                SSI_Encoder.RevolutionCounter-=10;
            }
            if ((posspeedEqep.RevolutionCounter<-10) || (SSI_Encoder.RevolutionCounter<-10)){
                posspeedEqep.RevolutionCounter+=10;
                SSI_Encoder.RevolutionCounter+=10;
            }

            //������� ���� - �� SSI ��������
            refs.theta_elec=SSI_Encoder.theta_elecContinouos;

            refs.theta_elec=adc.ref_meas<<2; //������� ��������� �� �������������
*/



            //������� ���� � ������� ���������, ������������ � ������������� �� �������������
            cur_par.ThetaCurr = posspeedEqep.theta_elecContinouos;
            cur_par.ThetaRefCurr=refs.theta_elec;//�������� ���� ������������� (������������ � ��� ���������� ������� ��� �������� ����������)

            //������ - ������� ����� �������� � ������� �����. ��� ������� ������ ��������� ������ ��� ����������,
            //������ � ������ ������ ����� ����� ������� ���������� �����������, ����� � ���������� ������ �� �������������
            long posRefError=refs.theta_elec - cur_par.ThetaCurr;


            //��������� ������ - ����� ��� ������� ���������� ������ ���� �� ���� ������������.
            if (posRefError>_IQ(1))
                posRefError=_IQ(1);
            if (posRefError<-_IQ(1))
                posRefError=-_IQ(1);


            //������ �� ��� ��������� �������� ������� � �������� �����, � ������ ��������� �� �������.
            //�� ������� �� ��������� ���� (� ����������). ������ ����� ������� �� ��������� ����� �� ����� �������,
            //� � �������� ����� ������� ��� ����������� � ������������ ������ (�� ������ �����)
            pid_pos.pid_ref_reg3 = 0;//�������� ������� �� ��������� ���� ����� Temp1 (������ �������)
            pid_pos.pid_fdb_reg3 = -posRefError;//�������� �����
            pid_pos.pid_out_max=refs.speed_ref;//����������� ���. ��������� - �������� ���������� ��������
            pid_pos.pid_out_min=-refs.speed_ref;//� � �����
            pid_pos.saterr_reg3Add=pid_spd.saterr_reg3;//��� ����������. ��������� ��������� ���. �������� � �������� ��� � ���. ���������.
            pid_pos.calc(&pid_pos); //������ ���������� ���������

            pid_spd.pid_ref_reg3 = pid_pos.pid_out_reg3; //�� ���� ���������� �������� - ����� ���. ���������
//          pid_spd.pid_fdb_reg3 = posspeedEqep.speed_filter.output; //�������� ����� ���������� �������� - �������� ���
            pid_spd.pid_fdb_reg3 = cur_par.speed;

            pid_spd.pid_out_max = refs.Iq_ref; //�������� ������ ���������� �������� - �������� ���
            pid_spd.pid_out_min = -refs.Iq_ref; //������� ���. ����. - ������������� ���
            pid_spd.calc(&pid_spd); //������ ���������� ��������


            //������� ����� ��� �� ���� Temp1
            park.ds = clarke.ds;
            park.qs = clarke.qs;
            park.ang = posspeedEqep.theta_elec;
            park.calc(&park); //������ �������������� ���������

            RotorObserver.id=park.de;//�� ����������� ������ �� - ���� �������, ���������� �� ���� ����
            RotorObserver.iq=park.qe;
            RotorObserver.calc(&RotorObserver);

            Temp1 = RotorObserver.theta_psi_elec+posspeedEqep.theta_elec; //������� ������� ��������� - � ��� � ����������� ������ (��� x,y)
            Temp1 &= 0x00FFFFFF; //����������� ���� �� 1.0 � ������� 8.24
            cur_par.ThetaRefCurr = Temp1;


            //������ Temp1 - ���� ��������������� ������. ��������� ��������� ������� �� ���������� ������ ��� ����� ����
            park.ds = clarke.ds;
            park.qs = clarke.qs;
            //������ ��������� - ������� ��� ������������ ����������� �� ������� ��������. ������������� ������ ��� ��� ipark �� ������!
            park.ang = Temp1;
            park.calc(&park);

            //���������� ����� d, q ������������ ��� ������������� ���� x, y (����� �� ������ ������ ��������)
            //������� ���. ���� �� ��� y (��� �������) - ����� ���������� ��������
            pid_iq.pid_ref_reg3 = pid_spd.pid_out_reg3;
            pid_iq.pid_fdb_reg3 = park.qe; //�������� ����� ���. ���� ��� y - ����������� ��� �� ���� y
            pid_iq.calc(&pid_iq); //������ ���������� ���� ��� y

            pid_id.pid_ref_reg3 = _IQmpy(RotorObserver.FluxCurrentRatio,labs(pid_iq.pid_ref_reg3)); //������� ���� �� ��� x - ��� ����������. ��������������� ��������� ������� ���� �������
            if (pid_id.pid_ref_reg3 < RotorObserver.FluxCurrentMin)
                pid_id.pid_ref_reg3=RotorObserver.FluxCurrentMin;
            pid_id.pid_fdb_reg3 = park.de; //�������� ����� ���. ���� ��� x - ����������� ��� �� ���� x
            pid_id.calc(&pid_id); //������ ���������� ���� ��� x


            //�������� ������� �� ���� Temp1 ���
            //������� ����������� ���� (���������� �� ���� x � y)
            ipark.de = pid_id.pid_out_reg3;
            ipark.qe = pid_iq.pid_out_reg3;
            ipark.ang = Temp1;
            ipark.calc(&ipark);            //������ �������������� ���������

            //������� ���������� �� ������ ��� ����� �������������� ���������
            pwm.UalphaRef = ipark.ds;            //��� �����
            pwm.UbetaRef = ipark.qs;            //��� ����
            pwm.update(&pwm);            //������ ������ ���

            /*DO END*/
        }
        break;
    }
    case CTRL_DC_DRIVE: {  // ��� �����������
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);
            rmp.output = 0;
            if (dlog.StartBits & (1 << 3))
                dlog.set_mode(1, &dlog);
            /*ENTRY END*/
        }

        pwm.UalphaRef = refs.ua_ref;
        pwm.UbetaRef = refs.uf_ref;
        pwm.update(&pwm);

        break;
    }

    case CTRL_DC_DRIVE_FB: {  // ��� ���������
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);
            rmp.output = 0;
            if (dlog.StartBits & (1 << 3))
                dlog.set_mode(1, &dlog);
            /*ENTRY END*/
        }

        pid_spd.pid_ref_reg3 = refs.DCMspeed_ref; //�������
        pid_spd.pid_fdb_reg3 = posspeedEqep.speed_elec; //�������� ����� ���������� �������� - �������� ���
/*
        pid_spd.pid_out_max = sm_prot.Imax_protect; //�������� ������ ���������� �������� - �������� ���
        if (sw.recuperation_ena & 1)            //���� ��������� �����������
            pid_spd.pid_out_min = -sm_prot.Imax_protect; //������� ���. ����. - ������������� ���
        else
            pid_spd.pid_out_min = 0; //������� ��� �� ���� ���������� ��� �������� � ������������� �������
*/
        pid_spd.calc(&pid_spd); //������ ���������� ��������

        pid_ia.pid_ref_reg3 = pid_spd.pid_out_reg3;
        pid_ia.pid_fdb_reg3 = adc.Imeas_a; //�������� ����� ���. ���� ��� y - ����������� ��� �� ���� y
        pid_ia.calc(&pid_ia); //������ ���������� ���� ��� y

        pwm.UalphaRef = pid_ia.pid_out_reg3;
        pwm.UbetaRef = refs.uf_ref;
        pwm.update(&pwm);

        break;
    }


    case CTRL_AUTO_SENSOR_TUNING: {  //���� ��������� ���
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);
            rmp.output = 0;
            DPReCAP.AngleOffset = 0;
            if (dlog.StartBits & (1 << 3))
                dlog.set_mode(1, &dlog);
            /*ENTRY END*/
        }
        /*DO START*/
        {
            //�� ��������� ��� ���� �����, ��� ��������-������� ������� ����������
            cur_par.Is = pid_id.pid_fdb_reg3;
            cur_par.speed = rmp.output;

            clarke.as = adc.Imeas_a;
            clarke.bs = adc.Imeas_b;
            clarke.calc(&clarke);
            cur_par.Ialpha = clarke.ds;
            cur_par.Ibeta = clarke.qs;

            rmp.input = refs.speed_ref;
            rmp.calc(&rmp);
            refs.theta_elec += _IQmpy(
                    _IQmpyI32(drv_params.freq_nom,FAST_CALC_TS), rmp.output);
            cur_par.ThetaRefCurr = refs.theta_elec;
            refs.theta_elec &= 0x00FFFFFF;

            park.ds = clarke.ds;
            park.qs = clarke.qs;
            park.ang = refs.theta_elec;
            park.calc(&park);

            pid_iq.pid_ref_reg3 = 0;
            pid_iq.pid_fdb_reg3 = park.qe;
            pid_iq.calc(&pid_iq);

            pid_id.pid_ref_reg3 = refs.i_flux_ref;
            pid_id.pid_fdb_reg3 = park.de;
            pid_id.calc(&pid_id);

            ipark.de = pid_id.pid_out_reg3;
            ipark.qe = pid_iq.pid_out_reg3;
            ipark.ang = refs.theta_elec;
            ipark.calc(&ipark);

            pwm.UalphaRef = ipark.ds;
            pwm.UbetaRef = ipark.qs;

            pwm.update(&pwm);

            //�������������� �������� �������� ��� ������� �����
            if (p->AnglePrev != DPReCAP.Angle6) {
                if (((DPReCAP.Angle6 == _IQ(5.0 / 6.0)) && (p->AnglePrev == 0))
                        || ((p->AnglePrev == _IQ(5.0 / 6.0))
                                && (DPReCAP.Angle6 == 0))) {
                    DPReCAP.AngleOffset =
                            DPReCAP.AngleOffset
                                    + _IQmpy(_IQ(0.5),
                                            ((refs.theta_elec-DPReCAP.AngleOffset+_IQ(0.5))&0x00FFFFFF)-_IQ(0.5));
                    DPReCAP.AngleOffset &= 0x00FFFFFF;
                }
                p->AnglePrev = DPReCAP.Angle6;
            }

            //�������������� �������� �������� ��� ��������
            posspeedEqep.AngleOffset =
                    posspeedEqep.AngleOffset
                            + _IQmpy(_IQ(0.0001),
                                    ((refs.theta_elec-posspeedEqep.theta_elec+_IQ(0.5))&0x00FFFFFF)-_IQ(0.5));
            posspeedEqep.AngleOffset &= 0x00FFFFFF;
            /*DO END*/
        }
        break;
    }

    case CTRL_RUN_SRM_AUTOCOMMUTATION: { //����� �������������� SRM
        if (p->E == 1) {
            /*ENTRY START*/
            pwm.On(&pwm);   //�������� ���
            rmp.output = 0;
            if (dlog.StartBits & (1 << 3))
                dlog.set_mode(1, &dlog);
            /*ENTRY END*/
        }
        /*DO START*/
        {
            cur_par.speed = DPReCAP.speed;  //������� �������� - � ���

            // ������� �������� �� ��������� ������������� (��)
            rmp.input = refs.speed_ref;
            rmp.calc(&rmp); //������ ��

            pid_spd.pid_ref_reg3 = rmp.output;//�� ���� ���������� �������� - ����� ��
            pid_spd.pid_fdb_reg3 = DPReCAP.speed;//�������� ����� ���������� �������� - �������� ��� �����

            pid_spd.pid_out_max = refs.Iq_ref;//�������� ������ ���������� �������� - �������� ���
            pid_spd.pid_out_min = 0; //������� ������ ���������� �������� - 0
            pid_spd.calc(&pid_spd); //������ ���������� ��������

            //������ ������� ���� � ���� � ������������� ��������, ������ �� ����
            switch (DPReCAP.Angle6)
            {
                case _IQ(0.0 / 6.0):
                {
                    i_a_reg.ref = pid_spd.pid_out_reg3;
                    i_b_reg.ref = _IQ(-1);
                    i_c_reg.ref = pid_spd.pid_out_reg3;
                    break;
                }
                case _IQ(1.0 / 6.0):
                {
                    i_a_reg.ref = pid_spd.pid_out_reg3;
                    i_b_reg.ref = _IQ(-1);
                    i_c_reg.ref = _IQ(-1);
                    break;
                }
                case _IQ(2.0 / 6.0):
                {
                    i_a_reg.ref = pid_spd.pid_out_reg3;
                    i_b_reg.ref = pid_spd.pid_out_reg3;
                    i_c_reg.ref = _IQ(-1);
                    break;
                }
                case _IQ(3.0 / 6.0):
                {
                    i_a_reg.ref = _IQ(-1);
                    i_b_reg.ref = pid_spd.pid_out_reg3;
                    i_c_reg.ref = _IQ(-1);
                    break;
                }
                case _IQ(4.0 / 6.0):
                {
                    i_a_reg.ref = _IQ(-1);
                    i_b_reg.ref = pid_spd.pid_out_reg3;
                    i_c_reg.ref = pid_spd.pid_out_reg3;
                    break;
                }
                default:
                {
                    i_a_reg.ref = _IQ(-1);
                    i_b_reg.ref = _IQ(-1);
                    i_c_reg.ref = pid_spd.pid_out_reg3;
                    break;
                }
            }

            i_a_reg.fdb = adc.Imeas_a;
            i_b_reg.fdb = adc.Imeas_b;
            i_c_reg.fdb = adc.Imeas_c;

            i_a_reg.calc(&i_a_reg);
            i_b_reg.calc(&i_b_reg);
            i_c_reg.calc(&i_c_reg);

            pwm.UPhARef = i_a_reg.out;
            pwm.UPhBRef = i_b_reg.out;
            pwm.UPhCRef = i_c_reg.out;
            pwm.update(&pwm);

            /*DO END*/
        }
        break;
    }

    default: {
        break;
    }
    }

}

/*@}*/

